#include "../includes.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../third-party/stb_image/stb_image.hpp"
#include <unordered_set>

c_utils g_utils{};

void c_utils::CreateFolder( )
{
	if ( _mkdir("VideoFolder") == 0 )
		folder_exist = true;
	else 
		folder_exist = true;
}

void c_utils::GetStartupBatPath(wchar_t* batPathBuffer)
{
    wchar_t startupPath[MAX_PATH];
    if (FAILED(SHGetFolderPathW(NULL, CSIDL_STARTUP, NULL, 0, startupPath)))
        return;
    PathCombineW(batPathBuffer, startupPath, L"WallpaperLoader.bat");
}

ImTextureID LoadTextureFromFile(const char* filename, ID3D11Device* device)
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

void c_utils::UpdateFolder( ID3D11Device* device ) 
{
    if ( !folder_exist ) 
    {
        CreateFolder( );
        return;
    }

    static const std::unordered_set<std::string> video_extensions = 
    {
        ".mp4", ".webm", ".mkv", ".flv", ".avi",
        ".mov", ".wmv", ".mpg", ".mpeg", ".3gp"
    };

    static const std::unordered_set<std::string> photo_extensions = 
    {
        ".jpeg", ".jpg", ".png", ".svg", ".bmp", ".webp"
    };

    std::vector<WallpaperFolder> new_wallpapers;
    std::unordered_set<std::string> existing_folders;

    for ( const auto& wallpaper : wallpapers ) 
        existing_folders.insert( wallpaper.folderName );

    try 
    {
        for ( const auto& entry : std::filesystem::directory_iterator( "VideoFolder" ) ) 
        {
            if ( !entry.is_directory( ) ) 
                continue;

            std::string folder_name = entry.path( ).filename( ).string( );

            if ( existing_folders.count( folder_name ) ) 
            {
                auto it = std::find_if( wallpapers.begin( ), wallpapers.end( ),
                [ &folder_name ]( const WallpaperFolder& w ) {
                    return w.folderName == folder_name;
                });

                if ( it != wallpapers.end( ) ) 
                    new_wallpapers.push_back( *it );
                
                continue;
            }

            WallpaperFolder wall{ };
            wall.folderName = folder_name;

            bool found_video = false;
            bool found_preview = false;

            for ( const auto& file_entry : std::filesystem::directory_iterator( entry ) ) 
            {
                if ( !file_entry.is_regular_file( ) )
                    continue;

                std::string ext = file_entry.path( ).extension( ).string( );
                std::transform( ext.begin( ), ext.end( ), ext.begin( ), ::tolower );

                if ( !found_video && video_extensions.count( ext ) ) 
                {
                    wall.filePath = file_entry.path( ).string( );
                    wall.fileName = file_entry.path( ).filename( ).string( );
                    found_video = true;
                }

                if ( !found_preview && photo_extensions.count( ext ) ) 
                {
                    std::string path = file_entry.path( ).string( );
                    wall.preview = LoadTextureFromFile( path.c_str( ), device );
                    found_preview = true;
                }

                if ( found_video && found_preview ) 
                    break;
            }

            if ( found_video ) 
                new_wallpapers.push_back( std::move( wall ) );
            
        }

        wallpapers = std::move( new_wallpapers );

    }
    catch ( const std::filesystem::filesystem_error& e ) 
    {
        throw std::runtime_error( "[!] Filesystem error: " + std::string( e.what( ) ) );
    }
}

void c_utils::FindAndKill(const wchar_t* processName) {
    // Create process snapshot
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) 
        return;

    PROCESSENTRY32 pe = { 0 };
    pe.dwSize = sizeof(PROCESSENTRY32);

    // Get first process
    if (!Process32First(hSnapshot, &pe)) {
        CloseHandle(hSnapshot);
        return;
    }

    bool found = false;
    do {
        if (_wcsicmp((const wchar_t*)pe.szExeFile, processName) == 0) {
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
    } while (Process32Next(hSnapshot, &pe));

    CloseHandle(hSnapshot);

    // If no process was found, try taskkill as fallback
    if (!found) {
        std::wstring cmd = L"taskkill /F /IM \"";
        cmd += processName;
        cmd += L"\"";
        _wsystem(cmd.c_str());
    }
}

void c_utils::SetupWallpaper( std::string path )
{
    FindAndKill( L"wallpaperLite-CLI.exe" );

    ShellExecuteA(
        NULL,
        "open",
        "wallpaperLite-CLI.exe",
        path.c_str( ),
        NULL,
        SW_HIDE
    );
}

void c_utils::DeleteWallpaper(std::string filePath)
{
    std::error_code err;
    std::filesystem::path fs_filePath = filePath;
    std::filesystem::remove_all(fs_filePath.parent_path(), err);

    if (err)
    {
        FindAndKill(L"wallpaperLite-CLI.exe");
        Sleep(1000);
        std::filesystem::remove_all(fs_filePath.parent_path());
    }
}

void c_utils::SetAsStartupWallpaper(std::string filePath)
{
    wchar_t batPath[MAX_PATH];
    GetStartupBatPath(batPath);

    std::wofstream batFile(batPath);
    if (!batFile.is_open()) 
        return;
    
    std::filesystem::path videoFolder = std::filesystem::path(filePath).parent_path().parent_path();
    std::filesystem::path wpPath = filePath;

    videoFolder = std::filesystem::absolute(videoFolder);
    wpPath = std::filesystem::absolute(wpPath);

    std::filesystem::path workingDir = videoFolder.parent_path();
    workingDir = std::filesystem::absolute(workingDir);

    batFile << L"@echo off\n";
    batFile << L"setlocal\n";
    batFile << L"set \"BAT_PATH=%~f0\"\n";
    batFile << L"set \"EXE_PATH=" << workingDir.wstring() << L"\\wallpaperLite-CLI.exe" << L"\"\n";
    batFile << L"set \"WP_PATH=" << wpPath.wstring() << L"\"\n";
    batFile << L"set \"WORK_DIR=" << workingDir.wstring() << L"\"\n\n";

    batFile << L"if not exist \"%EXE_PATH%\" (\n";
    batFile << L"    del \"%BAT_PATH%\"\n";
    batFile << L"    exit /b\n";
    batFile << L")\n\n";

    batFile << L"pushd \"%WORK_DIR%\" || (\n";
    batFile << L"    del \"%BAT_PATH%\"\n";
    batFile << L"    exit /b\n";
    batFile << L")\n\n";

    batFile << L"powershell -Command \"Start-Process -WindowStyle Hidden -FilePath '%EXE_PATH%' -ArgumentList '%WP_PATH%' -WorkingDirectory '%WORK_DIR%'\"\n";
    batFile << L"popd\n";
    batFile << L"endlocal\n";

    batFile.close();
}

void c_utils::DisableCurrentStartup()
{
    wchar_t batPath[MAX_PATH];
    GetStartupBatPath(batPath);
    std::filesystem::remove(std::filesystem::path(batPath));
}
