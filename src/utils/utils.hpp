#pragma once

typedef struct WallpaperFolder
{
	std::string filePath;
	std::string folderName;
	std::string fileName;
	ImTextureID preview;

} WallpaperFolder;

typedef struct WallpaperEditor
{
	char videoPath[ MAX_PATH ];
	char previewPath[ MAX_PATH ];
	bool hasPreview = false;

    void clear( ) noexcept {
        videoPath[ 0 ] = '\0';
        previewPath[ 0 ] = '\0';
        hasPreview = false;
    }

} WallpaperEditor;

class c_utils
{
public:

	auto CreateWallpaper( ) -> void
    {
        if ( !wallpaperEditor.videoPath ) 
            throw std::invalid_argument( "[!] Video path cannot be null" );
    
        if ( wallpaperEditor.hasPreview && !wallpaperEditor.previewPath ) 
            throw std::invalid_argument( "[!] Preview path cannot be null when preview is required" );
    
        try {
            const std::filesystem::path videoPath = wallpaperEditor.videoPath;
            const std::filesystem::path previewPath = wallpaperEditor.previewPath;

            if ( !std::filesystem::exists( videoPath ) ) 
                throw std::runtime_error( "[!] Video file does not exist: " + videoPath.string( ) );
        
            if ( wallpaperEditor.hasPreview && !std::filesystem::exists( previewPath ) ) 
                throw std::runtime_error( "[!] Preview file does not exist: " + previewPath.string( ) );
        
            const std::filesystem::path wallpaperDir =
                std::filesystem::path( "VideoFolder" ) / videoPath.stem( );

            std::filesystem::create_directories( wallpaperDir );

            const std::filesystem::path targetVideoPath = wallpaperDir / videoPath.filename( );
            std::filesystem::copy_file( videoPath, targetVideoPath,
                std::filesystem::copy_options::overwrite_existing );

            if ( wallpaperEditor.hasPreview ) {
                const std::filesystem::path targetPreviewPath = wallpaperDir / previewPath.filename( );
                std::filesystem::copy_file( previewPath, targetPreviewPath,
                    std::filesystem::copy_options::overwrite_existing );
            }

        }
        catch ( const std::filesystem::filesystem_error& e ) 
        {
            throw std::runtime_error( "[!] Filesystem error: " + std::string( e.what( ) ) );
        }
        catch ( const std::exception& e ) 
        {
            throw std::runtime_error( "[!] Failed to create wallpaper: " + std::string( e.what( ) ) );
        }

    }

    auto OpenFolder( const std::string& name = "\0" ) -> bool
    {
        try 
        {
            std::filesystem::path targetPath = name.empty( ) ?
                std::filesystem::current_path( ) / "VideoFolder" :
                std::filesystem::current_path( ) / "VideoFolder" / name;

            if ( !std::filesystem::exists( targetPath ) )
                return false;
            
            if ( !std::filesystem::is_directory( targetPath ) ) 
                return false;
            
            std::filesystem::path absolutePath = std::filesystem::absolute( targetPath );

            HINSTANCE result = ShellExecuteA(
                nullptr,
                "open",
                absolutePath.string( ).c_str( ),
                nullptr,
                nullptr,
                SW_SHOWNORMAL
            );

            // ShellExecuteA returns a value > 32 if successful
            return reinterpret_cast< intptr_t >( result ) > 32;
        }
        catch ( const std::filesystem::filesystem_error& e ) 
        {
            throw std::runtime_error( "[!] Filesystem error: " + std::string( e.what( ) ) );
        }
        catch ( const std::exception& e ) 
        {
            throw std::runtime_error( "[!] Error opening folder: " + std::string( e.what( ) ) );
        }

    }

	void UpdateFolder( ID3D11Device* device );

	void SetupWallpaper( std::string path );

	void DeleteWallpaper(std::string filePath);

	void SetAsStartupWallpaper(std::string filePath);

	void DisableCurrentStartup();

	void FindAndKill(const wchar_t* processName);

	std::vector< WallpaperFolder > wallpapers;

	WallpaperEditor wallpaperEditor;

private:

	// default
	bool folder_exist = false;
	int itemsInFolder = 0;
	void CreateFolder( );
	void GetStartupBatPath(wchar_t* batPathBuffer);
};

extern c_utils g_utils;
