#include "..\includes.h"

void c_gui::on_render(bool& exit)
{
	bool window_state = !exit;

    setup_style();
    auto setup_window_at_center = [](int width, int height)
    { 
        const float screenW = static_cast<float>(GetSystemMetrics(SM_CXSCREEN));
        const float screenH = static_cast<float>(GetSystemMetrics(SM_CYSCREEN));

        ImGui::SetNextWindowPos(ImVec2((screenW - width) * 0.5f, (screenH - height) * 0.5f), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(static_cast<float>(width), static_cast<float>(height)), ImGuiCond_FirstUseEver);
    };

    setup_window_at_center(window_width, window_height);
    ImGui::Begin("Wallpaper Lite - GUI", &window_state, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysVerticalScrollbar);
    {
        menu_bar();
        new_wallpaper();
        wallpaper_grid();

    }
    ImGui::End();

    exit = !window_state;
}

void c_gui::setup_style()
{
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
    colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
    colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    //colors[ImGuiCol_DockingPreview]         = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    //colors[ImGuiCol_DockingEmptyBg]         = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.WindowPadding = ImVec2(8.00f, 8.00f);
    style.FramePadding = ImVec2(4.00f, 2.00f);
    style.CellPadding = ImVec2(6.00f, 6.00f);
    style.ItemSpacing = ImVec2(6.00f, 6.00f);
    style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
    style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
    style.IndentSpacing = 25;
    style.ScrollbarSize = 15;
    style.GrabMinSize = 10;
    style.WindowBorderSize = 1;
    style.ChildBorderSize = 1;
    style.PopupBorderSize = 1;
    style.FrameBorderSize = 1;
    style.TabBorderSize = 1;
    style.WindowRounding = 0;
    style.ChildRounding = 0;
    style.FrameRounding = 0;
    style.PopupRounding = 0;
    style.ScrollbarRounding = 0;
    style.GrabRounding = 0;
    style.LogSliderDeadzone = 4;
    style.TabRounding = 0;
}

void c_gui::menu_bar()
{
    if (!ImGui::BeginMenuBar())
        return;

    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("Create New Wallpaper"))
            s_state.open_new_wallpaper_popup = true;

        if (ImGui::MenuItem("Open Wallpaper Folder"))
            utils->open_folder();

        ImGui::EndMenu();
    }

    ImGui::Separator();

    if (ImGui::BeginMenu("Options"))
    {
        if (ImGui::MenuItem("Disable Startup"))
            utils->disable_startup();

        if (ImGui::MenuItem("Disable Wallpaper"))
            utils->find_and_kill(L"wallpaperLite-CLI.exe");

        ImGui::EndMenu();
    }

    ImGui::EndMenuBar();


}

void c_gui::new_wallpaper()
{

    if (s_state.open_new_wallpaper_popup)
    {
        ImGui::OpenPopup("wallpaper editor popup");
        s_state.open_new_wallpaper_popup = false;
    }

    if (!ImGui::BeginPopup("wallpaper editor popup"))
        return;

    ImGui::Text("Create Wallpaper");

    file_select("Browse##video", utils->wallpaper_editor.video_path, MAX_PATH);
    ImGui::InputText("Video Path", utils->wallpaper_editor.video_path, MAX_PATH);

    ImGui::Checkbox("Use Preview", &utils->wallpaper_editor.has_preview);
    if (utils->wallpaper_editor.has_preview)
    {
        file_select("Browse##preview", utils->wallpaper_editor.preview_path, MAX_PATH);
        ImGui::InputText("Preview Path", utils->wallpaper_editor.preview_path, MAX_PATH);
    }

    if (ImGui::Button("Save"))
    {
        utils->create_wallpaper();
        utils->wallpaper_editor.clear();
        ImGui::CloseCurrentPopup();
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel"))
        ImGui::CloseCurrentPopup();

    ImGui::EndPopup();


}

void c_gui::delete_confirmation()
{

    if (s_state.open_delete_confirmation)
    {
        ImGui::OpenPopup("Delete Confirmation");
        s_state.open_delete_confirmation = false;
    }

    if (!ImGui::BeginPopupModal("Delete Confirmation", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        return;

    ImGui::Text("Are you sure you want to delete this wallpaper?");
    ImGui::Separator();

    const float spacing = ImGui::GetStyle().ItemSpacing.x;
    const float totalWidth = k_modal_button_width * 2 + spacing;
    const float windowWidth = ImGui::GetWindowWidth();

    ImGui::SetCursorPosX((windowWidth - totalWidth) * 0.5f);

    if (ImGui::Button("Delete", ImVec2(k_modal_button_width, 0)))
    {
        utils->delete_wallpaper(s_state.wallpaper_to_delete);
        s_state.wallpaper_to_delete.clear();
        ImGui::CloseCurrentPopup();
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel", ImVec2(k_modal_button_width, 0)) || ImGui::IsKeyPressed(ImGuiKey_Escape))
    {
        s_state.wallpaper_to_delete.clear();
        ImGui::CloseCurrentPopup();
    }

    ImGui::EndPopup();


}

void c_gui::wallpaper_options(wallpaper_folder_t& wallpaper)
{
    if (ImGui::ArrowButton("options", ImGuiDir_Down))
        ImGui::OpenPopup("options_popup");

    if (!ImGui::BeginPopup("options_popup", ImGuiWindowFlags_NoMove))
        return;

    if (ImGui::MenuItem("Set as Startup"))
        utils->set_as_startup(wallpaper.file_path, wallpaper.volume);

    if (ImGui::MenuItem("Open Folder"))
        utils->open_folder(wallpaper.folder_name);

    ImGui::Separator();

    ImGui::SetNextItemWidth(k_options_slider_width);
    if (ImGui::SliderInt("Volume", &wallpaper.volume, 0, 100, "%d%%"))
        utils->save_volume(wallpaper);

    ImGui::Separator();

    if (ImGui::MenuItem("Delete"))
    {
        s_state.wallpaper_to_delete = wallpaper.file_path;
        s_state.open_delete_confirmation = true;
    }

    ImGui::EndPopup();
}

void c_gui::wallpaper_item(wallpaper_folder_t& wallpaper, size_t index)
{
    // TODO(perf): reloads volume from wherever LoadWallpaperVolume reads
    // from on every frame, for every tile. See note (7) at the top of
    // this file - almost certainly wants to move to a one-time load
    // when `wallpapers` is populated instead of living here.
    utils->load_volume(wallpaper);

    if (index % k_items_per_row != 0)
        ImGui::SameLine();

    ImGui::PushID(static_cast<int>(index));

    if (ImGui::BeginChild("wallpaper_item", ImVec2(k_item_width, k_Item_height), true))
    {
        ImGui::ImageWithBg(
            wallpaper.preview,
            ImVec2(k_preview_width, k_preview_height),
            ImVec2(0, 0),
            ImVec2(1, 1),
            ImVec4(0.0f, 0.0f, 0.0f, 1.0f)
        );

        const ImVec2 storedCursorPos = ImGui::GetCursorPos();
        const float windowWidth = ImGui::GetWindowWidth();

        ImGui::SetCursorPos(ImVec2(windowWidth - k_options_button_offset_x, k_options_button_offset_y));
        wallpaper_options(wallpaper);
        ImGui::SetCursorPos(storedCursorPos);

        if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::IsAnyItemHovered())
            utils->setup_wallpaper(wallpaper.file_path, wallpaper.volume);

        const float availableWidth = ImGui::GetWindowWidth() - ImGui::GetStyle().WindowPadding.x * 2;
        truncated_text(wallpaper.file_name, availableWidth);
    }

    ImGui::EndChild();
    ImGui::PopID();
}

void c_gui::wallpaper_grid()
{
    delete_confirmation();

    const size_t wallpaperCount = utils->wallpapers.size();
    for (size_t i = 0; i < wallpaperCount; ++i)
        wallpaper_item(utils->wallpapers[i], i);
}

void c_gui::truncated_text(const std::string& text, float max_width)
{
    if (ImGui::CalcTextSize(text.c_str()).x <= max_width)
    {
        ImGui::Text("%s", text.c_str());
        return;
    }

    std::string truncated = text;
    while (ImGui::CalcTextSize((truncated + "...").c_str()).x > max_width && truncated.length() > 1)
        truncated.pop_back();

    ImGui::TextWrapped("%s...", truncated.c_str());

    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::Text("%s", text.c_str());
        ImGui::EndTooltip();
    }
}
