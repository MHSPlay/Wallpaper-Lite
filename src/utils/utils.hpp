#pragma once

typedef struct WallpaperFile
{
	void* preview;
	std::string name;
} WallpaperFile;

class c_utils
{
public:

	void OpenFolder( );

	void UpdateFolder( );

	void SetupWallpaper( std::string path );

	std::vector< WallpaperFile > files;

private:

	// default
	bool folder_exist = false;
	int itemsInFolder = 0;
	void CreateFolder( );

};

extern c_utils g_utils;
