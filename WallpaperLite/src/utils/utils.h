#pragma once

typedef struct wallpaper_folder_t
{
	std::string file_path;
	std::string file_name;
	std::string folder_name;
	ImTextureID preview = 0;

	int volume = 100;

} wallpaper_folder_t;

typedef struct wallpaper_editor_t
{
	char video_path[MAX_PATH] = { };
	char preview_path[MAX_PATH] = { };
	bool has_preview = false;

	void clear() noexcept {
		video_path[0] = '\0';
		preview_path[0] = '\0';
		has_preview = false;
	}

} wallpaper_editor_t;

class c_utils
{
public:

    void create_wallpaper()
    {
        if (wallpaper_editor.video_path[0] == '\0')
            throw std::invalid_argument("[!] Video path cannot be empty");

        if (wallpaper_editor.has_preview && wallpaper_editor.preview_path[0] == '\0')
            throw std::invalid_argument("[!] Preview path cannot be empty when preview is required");

        try {
            const std::filesystem::path video_path = wallpaper_editor.video_path;
            const std::filesystem::path preview_path = wallpaper_editor.preview_path;

            if (!std::filesystem::exists(video_path))
                throw std::runtime_error("[!] Video file does not exist: " + video_path.string());

            if (wallpaper_editor.has_preview && !std::filesystem::exists(preview_path))
                throw std::runtime_error("[!] Preview file does not exist: " + preview_path.string());

            const std::filesystem::path wallpaper_dir =
                std::filesystem::path("VideoFolder") / video_path.stem();

            std::filesystem::create_directories(wallpaper_dir);

            const std::filesystem::path target_video_path = wallpaper_dir / video_path.filename();
            std::filesystem::copy_file(video_path, target_video_path,
                std::filesystem::copy_options::overwrite_existing);

            if (wallpaper_editor.has_preview) {
                const std::filesystem::path target_preview_path = wallpaper_dir / preview_path.filename();
                std::filesystem::copy_file(preview_path, target_preview_path,
                    std::filesystem::copy_options::overwrite_existing);
            }

        }
        catch (const std::filesystem::filesystem_error& e)
        {
            throw std::runtime_error("[!] std::filesystem error: " + std::string(e.what()));
        }
    }

    auto open_folder(const std::string& name = "") -> bool
    {
        try
        {
            std::filesystem::path target_path = name.empty() ?
                std::filesystem::current_path() / "VideoFolder" :
                std::filesystem::current_path() / "VideoFolder" / name;

            if (!std::filesystem::exists(target_path))
                return false;

            if (!std::filesystem::is_directory(target_path))
                return false;

            std::filesystem::path absolute_path = std::filesystem::absolute(target_path);

            HINSTANCE result = ShellExecuteA(
                nullptr,
                "open",
                absolute_path.string().c_str(),
                nullptr,
                nullptr,
                SW_SHOWNORMAL
            );

            // ShellExecuteA returns a value > 32 if successful
            return reinterpret_cast<intptr_t>(result) > 32;
        }
        catch (const std::filesystem::filesystem_error& e)
        {
            throw std::runtime_error("[!] std::filesystem error: " + std::string(e.what()));
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("[!] Error opening folder: " + std::string(e.what()));
        }

    }

    void save_volume(const wallpaper_folder_t& wallpaper)
    {
        std::filesystem::path config_dir = std::filesystem::current_path() / "VideoFolder" / wallpaper.folder_name;
        std::filesystem::path config_file = config_dir / "volume.cfg";

        std::error_code ec;
        if (!std::filesystem::create_directories(config_dir, ec)) {
            if (ec && ec != std::errc::file_exists) {
                throw std::runtime_error("error: " + ec.message());
            }
        }

        std::ofstream file(config_file);
        if (file.is_open())
            file << wallpaper.volume << "\n";
        
    }

    void load_volume(wallpaper_folder_t& wallpaper)
    {
        std::filesystem::path config_dir = std::filesystem::current_path() / "VideoFolder" / wallpaper.folder_name;
        std::filesystem::path config_file = config_dir / "volume.cfg";

        std::ifstream file(config_file);
        if (file.is_open())
        {
            int vol = 100, mute = 0;
            file >> vol >> mute;
            wallpaper.volume = std::clamp(vol, 0, 100);
        }
        else
            wallpaper.volume = 100;

    }

    void update_folder(ID3D11Device* device);

    void setup_wallpaper(std::string path, int volume = 100);

    void delete_wallpaper(const std::string& path);

    void set_as_startup(const std::string& path, int volume);

    void disable_startup();

    void find_and_kill(const wchar_t* name);

    std::vector< wallpaper_folder_t > wallpapers;
    wallpaper_editor_t wallpaper_editor;

private:

    bool folder_exist = false;
    int itemsInFolder = 0;

    void create_folder();
    void get_startup_bat_path(wchar_t* bat_path_buffer);
    std::optional< wallpaper_folder_t > scan_folder(const std::filesystem::directory_entry& entry, ID3D11Device* device);

    const std::unordered_set<std::string> video_extensions =
    {
        ".mp4", ".webm", ".mkv", ".flv", ".avi",
        ".mov", ".wmv", ".mpg", ".mpeg", ".3gp"
    };

    const std::unordered_set<std::string> photo_extensions =
    {
        ".jpeg", ".jpg", ".png", ".svg", ".bmp", ".webp"
    };

};

inline const std::unique_ptr<c_utils> utils{ new c_utils() };