#include "../includes.hpp"

c_menu g_menu{};

void EmbraceTheDarkness()
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

#include <shobjidl.h> 

void ShowFileDialogButton(const char* buttonName, char* text, size_t bufferSize)
{
    if (ImGui::Button(buttonName))
    {
        HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
            COINIT_DISABLE_OLE1DDE);
        if (SUCCEEDED(hr))
        {
            IFileOpenDialog* pFileOpen;

            // Create the FileOpenDialog object.
            hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
                IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

            if (SUCCEEDED(hr))
            {
                // Show the Open dialog box.
                hr = pFileOpen->Show(NULL);

                // Get the file name from the dialog box.
                if (SUCCEEDED(hr))
                {
                    IShellItem* pItem;
                    hr = pFileOpen->GetResult(&pItem);
                    if (SUCCEEDED(hr))
                    {
                        PWSTR pszFilePath;
                        hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                        // Display the file name to the user.
                        if (SUCCEEDED(hr))
                        {
                            WideCharToMultiByte(CP_UTF8, 0, pszFilePath, -1, text, bufferSize, NULL, NULL);
                            CoTaskMemFree(pszFilePath);
                        }
                        pItem->Release();
                    }
                }
                pFileOpen->Release();
            }
            CoUninitialize();
        }
    }
    ImGui::SameLine();
}

void c_menu::OnRender() 
{
    // setup style
    EmbraceTheDarkness();

    //ImGui::ShowDemoWindow();

    ImGui::SetWindowPos( ImVec2( ( GetSystemMetrics( SM_CXSCREEN) / 2 ), ( GetSystemMetrics( SM_CYSCREEN ) / 2 ) ) );
    ImGui::SetNextWindowSize( ImVec2( 640, 540 ) );
    ImGui::Begin( "Wallpaper Lite - GUI", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysVerticalScrollbar );
	{

        // menu bar
        {
            static bool openPopup = false;

            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("file"))
                {
                    if (ImGui::MenuItem("new wallpaper"))
                    {
                        openPopup = true;
                    }

                    if (ImGui::MenuItem("open folder"))
                    {
                        g_utils.OpenFolder();
                    }

                    ImGui::EndMenu();
                }

                ImGui::Separator();

                if (ImGui::BeginMenu("options"))
                {
                    if (ImGui::MenuItem("exit app"))
                        exit(1);

                    ImGui::EndMenu();
                }

                ImGui::Separator();

                if (ImGui::BeginMenu("help"))
                {
                    ImGui::EndMenu();
                }

                ImGui::EndMenuBar();
            }

            if (openPopup)
            {
                ImGui::OpenPopup("wallpaper editor popup");
                openPopup = false;
            }

            if (ImGui::BeginPopup("wallpaper editor popup"))
            {
                ImGui::Text("new wallpaper");

                ShowFileDialogButton("Browse video path", g_utils.wallpaperEditor.videoPath, MAX_PATH);
                ImGui::InputText("video path", g_utils.wallpaperEditor.videoPath, MAX_PATH);
                ShowFileDialogButton("Browse preview path", g_utils.wallpaperEditor.previewPath, MAX_PATH);
                ImGui::InputText("preview path", g_utils.wallpaperEditor.previewPath, MAX_PATH);
                ImGui::Checkbox("use preview", &g_utils.wallpaperEditor.hasPreview);

                if (ImGui::Button("save"))
                {
                    g_utils.CreateWallpaper();
                    ImGui::CloseCurrentPopup();
                }

                if (ImGui::Button("cancel"))
                    ImGui::CloseCurrentPopup();

                ImGui::EndPopup();
            }

        }


        // main
        {
            size_t counter = 0;
            for ( WallpaperFolder& file : g_utils.wallpapers )
            {
                if ( counter % 4 != 0 ) 
                    ImGui::SameLine();
                
                ImGui::PushID(counter);

                ImGui::BeginChild( "file_child", ImVec2( 148, 200 ), true );
                {
                    // Здесь ваша логика отображения файла
                    ImGui::ImageWithBg(
                        file.preview,                  // ID текстуры для этого файла
                        ImVec2(132, 100),              // Размеры изображения
                        ImVec2(0, 0),                  // UV мин
                        ImVec2(1, 1),                  // UV макс
                        ImVec4(0.0f, 0.0f, 0.0f, 1.0f) // Цвет фона
                    );

                    if ( ImGui::IsMouseClicked( ImGuiMouseButton_Left ) && ImGui::IsWindowHovered( ) )
                    {
                        g_utils.SetupWallpaper( file.filePath );
                    }

                    ImGui::Text( "%s", file.fileName.c_str( ) );
                }
                ImGui::EndChild( );

                ImGui::PopID( );

                counter++;
            }
        }
	}
    ImGui::End( );
}