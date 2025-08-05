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
	char videoPath[MAX_PATH];
	char previewPath[MAX_PATH];
	bool hasPreview = true;
} WallpaperEditor;

class c_utils
{
public:

	void CreateWallpaper();

	void OpenFolder( );

	void UpdateFolder( ID3D11Device* device );

	void SetupWallpaper( std::string path );

	void DeleteWallpaper(std::string filePath);

	void SetAsStartupWallpaper(std::string filePath);

	void DisableCurrentStartup();

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
