#pragma once

// imgui
#include "..\..\..\third-party\imgui\imgui.h"

// windows includes
#include <comdef.h>
#include <shobjidl.h>
#include <string>
#include <memory>

namespace customGui
{
    class ComInitializer {
    public:
        
        ComInitializer() : m_initialized( false ) 
        {
            HRESULT hr = CoInitializeEx( nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE );
            m_initialized = SUCCEEDED( hr );
        }

        ~ComInitializer( ) 
        {
            if ( m_initialized ) 
                CoUninitialize( );
        }

        bool IsInitialized( ) const { return m_initialized; }

    private:
        bool m_initialized;
    };

	auto ShowFileSelectButton( const char* buttonName, char* text, size_t bufferSize ) -> bool
    {
        if ( !ImGui::Button( buttonName ) ) 
            return false;
        
        if ( !text || bufferSize == NULL ) 
            return false;
     
        ComInitializer comInit;
        if ( !comInit.IsInitialized( ) ) 
            return false;
        
        _com_ptr_t< _com_IIID< IFileOpenDialog, &__uuidof( IFileOpenDialog )>> pFileOpen;

        HRESULT hr = CoCreateInstance( CLSID_FileOpenDialog, nullptr, CLSCTX_ALL,
            IID_IFileOpenDialog,
            reinterpret_cast< void** >( &pFileOpen ) );

        if ( FAILED( hr ) ) 
            return false;
        
        hr = pFileOpen->Show( nullptr );
        if ( hr == HRESULT_FROM_WIN32( ERROR_CANCELLED ) ) 
            return false; 
        
        if ( FAILED( hr ) ) 
            return false;
        
        _com_ptr_t< _com_IIID< IShellItem, &__uuidof( IShellItem )>> pItem;
        hr = pFileOpen->GetResult( &pItem );
        if ( FAILED( hr ) ) 
            return false;
        
        PWSTR pszFilePath = nullptr;
        hr = pItem->GetDisplayName( SIGDN_FILESYSPATH, &pszFilePath );
        if ( FAILED( hr ) ) 
            return false;
        
        std::unique_ptr< wchar_t, decltype( &CoTaskMemFree )> filePathGuard( pszFilePath, CoTaskMemFree );

        int requiredSize = WideCharToMultiByte( CP_UTF8, 0, pszFilePath, -1, nullptr, 0, nullptr, nullptr );
        if ( requiredSize <= 0 || static_cast< size_t >( requiredSize ) > bufferSize )
            return false;
        
        int result = WideCharToMultiByte( CP_UTF8, 0, pszFilePath, -1, text, static_cast< int >( bufferSize ), nullptr, nullptr );

        return result > 0;
    }






};