#include "../includes.hpp"

// custom features
#include "custom/custom.hpp"

c_menu g_menu{ };

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

auto c_menu::OnRender( ) -> void
{
    // setup style
    EmbraceTheDarkness( );

    ImGui::SetWindowPos( ImVec2( ( GetSystemMetrics( SM_CXSCREEN ) / 2 ), ( GetSystemMetrics( SM_CYSCREEN ) / 2 ) ) );
    ImGui::SetNextWindowSize( ImVec2( 640, 540 ) );
    ImGui::Begin( "Wallpaper Lite - GUI", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysVerticalScrollbar );
	{

        // menu bar
        {
            static bool openPopup = false;

            if ( ImGui::BeginMenuBar( ) )
            {
                if ( ImGui::BeginMenu( "file" ) )
                {
                    if ( ImGui::MenuItem( "new wallpaper" ) )
                        openPopup = true;
                    
                    if ( ImGui::MenuItem( "open folder" ) )
                        g_utils.OpenFolder( );
                    
                    ImGui::EndMenu( );
                }

                ImGui::Separator( );

                if ( ImGui::BeginMenu( "options" ) )
                {
                    if ( ImGui::MenuItem( "exit app" ) )
                        exit( 1 );

                    if ( ImGui::MenuItem( "disable startup" ) )
                        g_utils.DisableCurrentStartup( );

                    if ( ImGui::MenuItem( "disable current wallpaper" ) )
                        g_utils.FindAndKill( L"wallpaperLite-CLI.exe" );

                    ImGui::EndMenu( );
                }

                ImGui::EndMenuBar( );
            }

            if ( openPopup )
            {
                ImGui::OpenPopup( "wallpaper editor popup" );
                openPopup = false;
            }

            if ( ImGui::BeginPopup( "wallpaper editor popup" ) )
            {
                ImGui::Text( "new wallpaper" );

                customGui::ShowFileSelectButton( "Browse video path", g_utils.wallpaperEditor.videoPath, MAX_PATH );
                ImGui::InputText( "video path", g_utils.wallpaperEditor.videoPath, MAX_PATH );

                ImGui::Checkbox( "use preview", &g_utils.wallpaperEditor.hasPreview );
                if ( g_utils.wallpaperEditor.hasPreview )
                {
                    customGui::ShowFileSelectButton( "Browse preview path", g_utils.wallpaperEditor.previewPath, MAX_PATH );
                    ImGui::InputText( "preview path", g_utils.wallpaperEditor.previewPath, MAX_PATH );
                }

                if ( ImGui::Button( "save" ) )
                {
                    g_utils.CreateWallpaper( );
                    g_utils.wallpaperEditor.clear( );
                    ImGui::CloseCurrentPopup( );
                }

                ImGui::SameLine( );

                if ( ImGui::Button( "cancel" ) )
                    ImGui::CloseCurrentPopup( );

                ImGui::EndPopup( );
            }

        }

        // main
        {
            static std::string wallpaperToDelete;
            static bool showDeleteConfirmation = false;

            const float itemWidth = 148.0f;
            const float itemHeight = 200.0f;
            const int itemsPerRow = 4;

            if ( showDeleteConfirmation )
            {
                ImGui::OpenPopup( "Delete Confirmation" );
                showDeleteConfirmation = false;
            }

            if ( ImGui::BeginPopup( "Delete Confirmation" ) )
            {
                ImGui::Text( "Are you sure you want to delete this wallpaper?" );
                ImGui::Separator( );

                const float buttonWidth = 80.0f;
                const float spacing = ImGui::GetStyle( ).ItemSpacing.x;
                const float totalWidth = buttonWidth * 2 + spacing;
                const float windowWidth = ImGui::GetWindowWidth( );

                ImGui::SetCursorPosX( ( windowWidth - totalWidth ) * 0.5f );

                if ( ImGui::Button( "Delete", ImVec2( buttonWidth, 0 ) ) )
                {
                    g_utils.DeleteWallpaper( wallpaperToDelete );
                    wallpaperToDelete.clear( );
                    ImGui::CloseCurrentPopup( );
                }

                ImGui::SameLine( );

                if ( ImGui::Button( "Cancel", ImVec2( buttonWidth, 0 ) ) || ImGui::IsKeyPressed( ImGuiKey_Escape ) )
                {
                    wallpaperToDelete.clear( );
                    ImGui::CloseCurrentPopup( );
                }

                ImGui::EndPopup();
            }

            const size_t wallpaperCount = g_utils.wallpapers.size( );

            for ( size_t i = 0; i < wallpaperCount; ++i )
            {
                const WallpaperFolder& wallpaper = g_utils.wallpapers[ i ];

                if ( i % itemsPerRow != 0 )
                    ImGui::SameLine();
                
                ImGui::PushID( static_cast< int >( i ) );

                if ( ImGui::BeginChild( "wallpaper_item", ImVec2( itemWidth, itemHeight ), true ) )
                {
                    ImGui::ImageWithBg(
                        wallpaper.preview,
                        ImVec2( 132, 100 ),
                        ImVec2( 0, 0 ),
                        ImVec2( 1, 1 ),
                        ImVec4( 0.0f, 0.0f, 0.0f, 1.0f )
                    );

                    const ImVec2 storedCursorPos = ImGui::GetCursorPos( );
                    const float windowWidth = ImGui::GetWindowWidth( );

                    ImGui::SetCursorPos( ImVec2( windowWidth - 25, 8 ) );

                    if ( ImGui::ArrowButton( "options", ImGuiDir_Down ) )
                        ImGui::OpenPopup( "options_popup" );

                    if ( ImGui::BeginPopup( "options_popup", ImGuiWindowFlags_NoMove ) )
                    {
                        if ( ImGui::MenuItem( "set as startup" ) )
                            g_utils.SetAsStartupWallpaper( wallpaper.filePath );
                        
                        if ( ImGui::MenuItem( "open folder" ) )
                            g_utils.OpenFolder( wallpaper.folderName );

                        if ( ImGui::MenuItem( "delete", nullptr, false, true ) )
                        {
                            wallpaperToDelete = wallpaper.filePath;
                            showDeleteConfirmation = true;
                        }

                        ImGui::EndPopup( );
                    }

                    ImGui::SetCursorPos( storedCursorPos );

                    if ( ImGui::IsWindowHovered( ) && ImGui::IsMouseClicked( ImGuiMouseButton_Left ) && !ImGui::IsAnyItemHovered( ) )
                        g_utils.SetupWallpaper( wallpaper.filePath );

                    const float availableWidth = ImGui::GetWindowWidth( ) - ImGui::GetStyle( ).WindowPadding.x * 2;
                    const std::string& fileName = wallpaper.fileName;

                    if ( ImGui::CalcTextSize( fileName.c_str( ) ).x > availableWidth )
                    {
                        std::string truncatedName = fileName;
                        while ( ImGui::CalcTextSize( ( truncatedName + "..." ).c_str( ) ).x > availableWidth && truncatedName.length( ) > 1 )
                            truncatedName.pop_back( );

                        ImGui::TextWrapped( "%s...", truncatedName.c_str( ) );

                        if ( ImGui::IsItemHovered( ) )
                        {
                            ImGui::BeginTooltip( );
                            ImGui::Text( "%s", fileName.c_str( ) );
                            ImGui::EndTooltip( );
                        }
                    }
                    else
                        ImGui::Text( "%s", fileName.c_str( ) );
                }

                ImGui::EndChild( );
                ImGui::PopID( );
            }
        }
	}
    ImGui::End( );
}