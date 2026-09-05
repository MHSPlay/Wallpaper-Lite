#pragma once

class ComInitializer {
public:

    ComInitializer() : m_initialized(false)
    {
        HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
        m_initialized = SUCCEEDED(hr);
    }

    ~ComInitializer()
    {
        if (m_initialized)
            CoUninitialize();
    }

    bool IsInitialized() const { return m_initialized; }

private:
    bool m_initialized;
};


class c_gui
{
public:

	void on_render(bool& exit);

private:
    const int window_width = 640;
    const int window_height = 540;

    // grid
    const float k_item_width = 148.0f;
    const float k_Item_height = 200.0f;
    const int   k_items_per_row = 4;
    const float k_preview_width = 132.0f;
    const float k_preview_height = 100.0f;
    const float k_options_button_offset_x = 25.0f;
    const float k_options_button_offset_y = 8.0f;
    const float k_options_slider_width = 150.0f;

    const float k_modal_button_width = 80.0f;

private:
    struct menu_state_t
    {
        bool        open_new_wallpaper_popup = false;
        bool        open_delete_confirmation = false;
        std::string wallpaper_to_delete;
    };

    menu_state_t s_state;

private:
    void setup_style();
	void menu_bar();

    void truncated_text(const std::string& text, float max_width);

    // wallpaper
    void new_wallpaper();
    void wallpaper_grid();
    void wallpaper_options(wallpaper_folder_t& wallpaper);
    void wallpaper_item(wallpaper_folder_t& wallpaper, size_t index);
    void delete_confirmation();

    auto file_select(const char* buttonName, char* text, size_t bufferSize) -> bool
    {
        if (!ImGui::Button(buttonName))
            return false;

        if (!text || bufferSize == NULL)
            return false;

        ComInitializer comInit;
        if (!comInit.IsInitialized())
            return false;

        _com_ptr_t< _com_IIID< IFileOpenDialog, &__uuidof(IFileOpenDialog)>> pFileOpen;

        HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL,
            IID_IFileOpenDialog,
            reinterpret_cast<void**>(&pFileOpen));

        if (FAILED(hr))
            return false;

        hr = pFileOpen->Show(nullptr);
        if (hr == HRESULT_FROM_WIN32(ERROR_CANCELLED))
            return false;

        if (FAILED(hr))
            return false;

        _com_ptr_t< _com_IIID< IShellItem, &__uuidof(IShellItem)>> pItem;
        hr = pFileOpen->GetResult(&pItem);
        if (FAILED(hr))
            return false;

        PWSTR pszFilePath = nullptr;
        hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
        if (FAILED(hr))
            return false;

        std::unique_ptr< wchar_t, decltype(&CoTaskMemFree)> filePathGuard(pszFilePath, CoTaskMemFree);

        int requiredSize = WideCharToMultiByte(CP_UTF8, 0, pszFilePath, -1, nullptr, 0, nullptr, nullptr);
        if (requiredSize <= 0 || static_cast<size_t>(requiredSize) > bufferSize)
            return false;

        int result = WideCharToMultiByte(CP_UTF8, 0, pszFilePath, -1, text, static_cast<int>(bufferSize), nullptr, nullptr);

        return result > 0;
    }

};

inline const std::unique_ptr<c_gui> gui{ new c_gui() };