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
	char videoPath[MAX_WINDOWS_PATH_SIZE];
	char previewPath[MAX_WINDOWS_PATH_SIZE];
	bool hasPreview;
} WallpaperEditor;

class c_utils
{
public:

	void CreateWallpaper(WallpaperEditor* editor);

	void OpenFolder( );

	void UpdateFolder( ID3D11Device* device );

	void SetupWallpaper( std::string path );

	std::vector< WallpaperFolder > wallpapers;

	WallpaperEditor wallpaperEditor;

private:

	// default
	bool folder_exist = false;
	int itemsInFolder = 0;
	void CreateFolder( );

};

extern c_utils g_utils;
