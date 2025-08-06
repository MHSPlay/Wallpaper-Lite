#include "../includes.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../third-party/stb_image/stb_image.hpp"

c_utils g_utils{};

void c_utils::CreateWallpaper()
{
    if (wallpaperEditor.videoPath == nullptr || 
        (wallpaperEditor.previewPath == nullptr && wallpaperEditor.hasPreview))
        return;

    std::filesystem::path fs_videoPath = wallpaperEditor.videoPath;
    std::filesystem::path fs_previewPath = wallpaperEditor.previewPath;
    
    std::string wallpaperFolderPath = "VideoFolder\\" + fs_videoPath.stem().string();

    _mkdir(wallpaperFolderPath.c_str());

    std::string newVideoPath = "VideoFolder\\" + fs_videoPath.stem().string() + "\\" + fs_videoPath.filename().string();
    std::filesystem::copy(fs_videoPath, newVideoPath, std::filesystem::copy_options::overwrite_existing);

    if (wallpaperEditor.hasPreview)
    {
        std::string newPreviewPath = "VideoFolder\\" + fs_videoPath.stem().string() + "\\" + fs_previewPath.filename().string();
        std::filesystem::copy(fs_previewPath, newPreviewPath, std::filesystem::copy_options::overwrite_existing);
    }
}

void c_utils::OpenFolder( )
{
	ShellExecuteA(
		NULL,
		"open",
		"VideoFolder",
		NULL,
		NULL,
		SW_SHOWNORMAL
	);

}

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
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

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
	if ( !folder_exist ) {
		CreateFolder( );
		return;
	}

	static const std::vector<std::string> video_extensions = {
		".mp4", ".webm", ".mkv", ".flv", ".avi",
		".mov", ".wmv", ".mpg", ".mpeg", ".3gp"
	};

    static const std::vector<std::string> photo_extensions = {
        ".jpeg", ".jpg", ".png", ".svg", ".bmp", 
        ".webp"
	};

    int curExistFiles = 0;
    for ( const auto& entry : std::filesystem::directory_iterator( "VideoFolder" ) )
    {
        WallpaperFolder wall = { };

        std::string filename = entry.path( ).filename( ).string( );

        bool already_exists = false;
        for ( const auto& file : wallpapers )
        {
            if ( file.folderName == filename )
            {
                already_exists = true;
                curExistFiles++;
                break;
            }
        }

        if ( !already_exists )
        {
            for ( const auto& insideFolder : std::filesystem::directory_iterator( entry ) )
            {
                // any files like txt or video
                if ( insideFolder.is_regular_file( ) )
                {
                    std::string ext = insideFolder.path( ).extension( ).string( );
                    std::transform( ext.begin( ), ext.end( ), ext.begin( ), ::tolower );
                
                    // SAVE FILE NAME AND PATH
                    if ( std::find( video_extensions.begin( ), video_extensions.end( ), ext ) != video_extensions.end( ) )
                    {
                        wall.filePath = insideFolder.path( ).string( );
                        wall.fileName = insideFolder.path( ).filename( ).string( );
                        wall.folderName = entry.path( ).filename( ).string( );
                    }

                    if ( std::find( photo_extensions.begin( ), photo_extensions.end( ), ext ) != photo_extensions.end( ) )
                    {
                        std::string path = insideFolder.path().string();
                        wall.preview = LoadTextureFromFile( path.c_str(), device );
                    }
            
                }

            }

            wallpapers.push_back( wall );
            curExistFiles++;
        }

    }

    if ( curExistFiles < wallpapers.size( ) )
        wallpapers.clear( );
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
        if (_wcsicmp(pe.szExeFile, processName) == 0) {
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
    if (!batFile.is_open()) {
        return;
    }

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
