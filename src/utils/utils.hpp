#pragma once

typedef struct WallpaperFolder
{

	std::string filePath;
	std::string folderName;
	std::string fileName;
	ImTextureID preview;

} WallpaperFolder;

class c_utils
{
public:

	void OpenFolder( );

	void UpdateFolder( ID3D11Device* device );

	void SetupWallpaper( std::string path );

	std::vector< WallpaperFolder > wallpapers;
private:

	// default
	bool folder_exist = false;
	int itemsInFolder = 0;
	void CreateFolder( );

};

extern c_utils g_utils;
