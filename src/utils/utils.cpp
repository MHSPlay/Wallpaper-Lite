#include "../includes.hpp"

c_utils g_utils{};

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

void c_utils::UpdateFolder( ) 
{
	if ( !folder_exist ) {
		CreateFolder( );
		return;
	}

	static const std::vector<std::string> video_extensions = {
		".mp4", ".webm", ".mkv", ".flv", ".avi",
		".mov", ".wmv", ".mpg", ".mpeg", ".3gp"
	};

    int curExistFiles = 0;
    for ( const auto& entry : std::filesystem::directory_iterator( "VideoFolder" ) )
    {
        if ( entry.is_regular_file( ) )
        {
            std::string ext = entry.path( ).extension( ).string( );
            std::transform( ext.begin( ), ext.end( ), ext.begin( ), ::tolower );

            if ( std::find( video_extensions.begin( ), video_extensions.end( ), ext ) != video_extensions.end( ) )
            {
                std::string filename = entry.path( ).filename( ).string( );

                bool already_exists = false;
                for ( const auto& file : files ) 
				{
                    if ( file.name == filename ) 
					{
                        already_exists = true;
                        curExistFiles++;
                        break;
                    }
                }

                if ( !already_exists ) 
				{
                    WallpaperFile wall = { NULL, filename };
                    files.push_back( wall );
                    curExistFiles++;
                }

            }

        }

    }

    if ( curExistFiles < files.size( ) )
        files.clear( );

}

void FindAndKill(const wchar_t* processName) {
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

    std::string arguments = "VideoFolder\\" + path;

    ShellExecuteA(
        NULL,
        "open",
        "wallpaperLite-CLI.exe",
        arguments.c_str( ),
        NULL,
        SW_HIDE
    );


}
