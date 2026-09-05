#define STB_IMAGE_IMPLEMENTATION
#include "..\includes.h"

ImTextureID load_texture_from_file(const char* filename, ID3D11Device* device)
{
    if (!device || !filename)
        return NULL;

    int width, height, channels;
    unsigned char* image_data = stbi_load(filename, &width, &height, &channels, 4); // RGBA
    if (!image_data)
        return NULL;

    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
    desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = image_data;
    initData.SysMemPitch = width * 4;

    ID3D11Texture2D* texture = nullptr;
    HRESULT hr = device->CreateTexture2D(&desc, &initData, &texture);
    stbi_image_free(image_data);
    if (FAILED(hr))
        return NULL;

    ID3D11ShaderResourceView* srv = nullptr;
    hr = device->CreateShaderResourceView(texture, NULL, &srv);
    texture->Release();
    if (FAILED(hr))
        return NULL;

    return (ImTextureID)srv;
}

void c_utils::create_folder()
{
    if (_mkdir("VideoFolder") == 0)
    {
        folder_exist = true;
        return;
    }

    folder_exist = (errno == EEXIST);
}

void c_utils::get_startup_bat_path(wchar_t* bat_path_buffer)
{
    wchar_t startup_path[MAX_PATH];
    if (FAILED(SHGetFolderPathW(NULL, CSIDL_STARTUP, NULL, 0, startup_path)))
        return;
    
    PathCombineW(bat_path_buffer, startup_path, L"WallpaperLoader.bat");
}

std::optional< wallpaper_folder_t > c_utils::scan_folder(const std::filesystem::directory_entry& entry, ID3D11Device* device)
{
    wallpaper_folder_t wall{ };
    wall.folder_name = entry.path().filename().string();

    bool found_video = false;
    bool found_preview = false;

    for (const auto& file_entry : std::filesystem::directory_iterator(entry))
    {
        if (!file_entry.is_regular_file())
            continue;

        auto to_lowercase = [](const std::filesystem::path& p)
        {
            std::string ext = p.extension().string();
            std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
            return ext;
        };

        const std::string ext = to_lowercase(file_entry.path());

        if (!found_video && video_extensions.count(ext))
        {
            wall.file_path = file_entry.path().string();
            wall.file_name = file_entry.path().filename().string();
            found_video = true;
        }

        if (!found_preview && photo_extensions.count(ext))
        {
            wall.preview = load_texture_from_file(file_entry.path().string().c_str(), device);
            found_preview = true;
        }

        if (found_video && found_preview)
            break;
    }

    if (!found_video)
        return std::nullopt;

    return wall;
}

void c_utils::update_folder(ID3D11Device* device)
{
    if (!folder_exist)
    {
        create_folder();
        return;
    }

    std::unordered_set<std::string> existing_folders;
    for (const auto& wallpaper : wallpapers)
        existing_folders.insert(wallpaper.folder_name);

    std::vector<wallpaper_folder_t> new_wallpapers;

    try
    {
        for (const auto& entry : std::filesystem::directory_iterator("VideoFolder"))
        {
            if (!entry.is_directory())
                continue;

            const std::string folder_name = entry.path().filename().string();

            if (existing_folders.count(folder_name))
            {
                auto it = std::find_if(wallpapers.begin(), wallpapers.end(),
                    [&folder_name](const wallpaper_folder_t& w) {
                        return w.folder_name == folder_name;
                    });

                if (it != wallpapers.end())
                    new_wallpapers.push_back(*it);

                continue;
            }

            if (auto scanned = scan_folder(entry, device))
                new_wallpapers.push_back(std::move(*scanned));
        }
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        throw std::runtime_error("[!] std::filesystem error: " + std::string(e.what()));
    }

    // cleanup
    std::unordered_set< std::string > kept;
    for (const auto& w : new_wallpapers)
        kept.insert(w.folder_name);

    for (const auto& old_wallpaper : wallpapers)
    {
        if (!kept.count(old_wallpaper.folder_name) && old_wallpaper.preview)
            reinterpret_cast<ID3D11ShaderResourceView*>(old_wallpaper.preview)->Release();
    }

    wallpapers = std::move(new_wallpapers);
}

void c_utils::find_and_kill(const wchar_t* name) {
    // Create process snapshot
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
        return;

    PROCESSENTRY32W pe = { 0 };
    pe.dwSize = sizeof(PROCESSENTRY32W);

    // Get first process
    if (!Process32FirstW(hSnapshot, &pe)) {
        CloseHandle(hSnapshot);
        return;
    }

    bool found = false;
    do {
        if (_wcsicmp(pe.szExeFile, name) == 0) {
            // Open the process with terminate rights
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
            if (hProcess != NULL) {
                // Try to terminate gracefully first
                if (!TerminateProcess(hProcess, 0)) {
                    // If graceful termination fails, force kill
                    system(("taskkill /F /PID " + std::to_string(pe.th32ProcessID)).c_str());
                }
                CloseHandle(hProcess);
                found = true;
            }
        }
    } while (Process32NextW(hSnapshot, &pe));

    CloseHandle(hSnapshot);

    // If no process was found, try taskkill as fallback
    if (!found) {
        std::wstring cmd = L"taskkill /F /IM \"";
        cmd += name;
        cmd += L"\"";
        _wsystem(cmd.c_str());
    }
}

void c_utils::setup_wallpaper(std::string path, int volume)
{
    find_and_kill(L"wallpaperLite-CLI.exe");

    std::string args = "\"" + path + "\"";
    args += " --volume=" + std::to_string(volume);

    ShellExecuteA(
        NULL,
        "open",
        "wallpaperLite-CLI.exe",
        args.c_str(),
        NULL,
        SW_HIDE
    );
}

void c_utils::delete_wallpaper(const std::string& filePath)
{
    const std::filesystem::path file_path = filePath;

    std::error_code err;
    std::filesystem::remove_all(file_path.parent_path(), err);
    if (!err)
        return;

    // Most likely our own CLI still has the video file open. Kill it and
    // retry once. Note this second attempt uses `err` too now instead of
    // the throwing overload - this is called directly from a delete-button
    // click in the render loop, and an uncaught filesystem_error there would
    // take the whole app down rather than just failing the delete.
    find_and_kill(L"wallpaperLite-CLI.exe");
    Sleep(1000);
    std::filesystem::remove_all(file_path.parent_path(), err);
}

void c_utils::set_as_startup(const std::string& path, int volume)
{
    wchar_t bat_path[MAX_PATH];
    get_startup_bat_path(bat_path);

    std::wofstream bat_file(bat_path);
    if (!bat_file.is_open())
        return;

    const std::filesystem::path wp_path =
        std::filesystem::absolute(path);

    // Assumed to be wherever wallpaperLite-CLI.exe lives, same assumption
    // every other path in this file makes (CreateFolder, OpenFolder,
    // Save/LoadWallpaperVolume all resolve relative to current_path()).
    const std::filesystem::path workingDir =
        std::filesystem::current_path();

    const std::filesystem::path exePath =
        workingDir / L"wallpaperLite-CLI.exe";

    bat_file << L"@echo off\n";
    bat_file << L"setlocal\n";

    bat_file << L"set \"BAT_PATH=%~f0\"\n";
    bat_file << L"set \"EXE_PATH=" << exePath.wstring() << L"\"\n";
    bat_file << L"set \"WP_PATH=" << wp_path.wstring() << L"\"\n";
    bat_file << L"set \"WORK_DIR=" << workingDir.wstring() << L"\"\n\n";

    bat_file << L"if not exist \"%EXE_PATH%\" (\n";
    bat_file << L"    del \"%BAT_PATH%\"\n";
    bat_file << L"    exit /b\n";
    bat_file << L")\n\n";

    bat_file << L"pushd \"%WORK_DIR%\" || (\n";
    bat_file << L"    del \"%BAT_PATH%\"\n";
    bat_file << L"    exit /b\n";
    bat_file << L")\n\n";

    bat_file << L"powershell.exe -NoProfile -WindowStyle Hidden -Command ";
    bat_file << L"\"Start-Process -WindowStyle Hidden ";
    bat_file << L"-FilePath '%EXE_PATH%' ";
    bat_file << L"-WorkingDirectory '%WORK_DIR%' ";
    bat_file << L"-ArgumentList '";
    bat_file << L"\\\"%WP_PATH%\\\"";
    bat_file << L" --volume=" << volume;

    bat_file << L"'\"\n";

    bat_file << L"popd\n";
    bat_file << L"endlocal\n";

    bat_file.close();
}

void c_utils::disable_startup()
{
    wchar_t bat_path[MAX_PATH];
    get_startup_bat_path(bat_path);
    std::filesystem::remove(std::filesystem::path(bat_path));
}
