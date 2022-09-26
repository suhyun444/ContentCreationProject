//-------------------------------------------------------------------------------------
// DirectXTex.inl
//
// DirectX Texture Library
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
//
// http://go.microsoft.com/fwlink/?LinkId=248926
//-------------------------------------------------------------------------------------

#pragma once

//=====================================================================================
// Bitmask flags enumerator operators
//=====================================================================================
DEFINE_ENUM_FLAG_OPERATORS(DirectX::CP_FLAGS);
DEFINE_ENUM_FLAG_OPERATORS(DirectX::DDS_FLAGS);
DEFINE_ENUM_FLAG_OPERATORS(DirectX::TGA_FLAGS);
DEFINE_ENUM_FLAG_OPERATORS(DirectX::WIC_FLAGS);
DEFINE_ENUM_FLAG_OPERATORS(DirectX::TEX_FR_FLAGS);
DEFINE_ENUM_FLAG_OPERATORS(DirectX::TEX_FILTER_FLAGS);
DEFINE_ENUM_FLAG_OPERATORS(DirectX::TEX_PMALPHA_FLAGS);
DEFINE_ENUM_FLAG_OPERATORS(DirectX::TEX_COMPRESS_FLAGS);
DEFINE_ENUM_FLAG_OPERATORS(DirectX::CNMAP_FLAGS);
DEFINE_ENUM_FLAG_OPERATORS(DirectX::CMSE_FLAGS);

// WIC_FILTER modes match TEX_FILTER modes
constexpr DirectX::WIC_FLAGS operator|(DirectX::WIC_FLAGS a, DirectX::TEX_FILTER_FLAGS b) { return static_cast<DirectX::WIC_FLAGS>(static_cast<unsigned long>(a) | static_cast<unsigned long>(b & DirectX::TEX_FILTER_MODE_MASK)); }
constexpr DirectX::WIC_FLAGS operator|(DirectX::TEX_FILTER_FLAGS a, DirectX::WIC_FLAGS b) { return static_cast<DirectX::WIC_FLAGS>(static_cast<unsigned long>(a & DirectX::TEX_FILTER_MODE_MASK) | static_cast<unsigned long>(b)); }

// TEX_PMALPHA_SRGB match TEX_FILTER_SRGB
constexpr DirectX::TEX_PMALPHA_FLAGS operator|(DirectX::TEX_PMALPHA_FLAGS a, DirectX::TEX_FILTER_FLAGS b) { return static_cast<DirectX::TEX_PMALPHA_FLAGS>(static_cast<unsigned long>(a) | static_cast<unsigned long>(b & DirectX::TEX_FILTER_SRGB_MASK)); }
constexpr DirectX::TEX_PMALPHA_FLAGS operator|(DirectX::TEX_FILTER_FLAGS a, DirectX::TEX_PMALPHA_FLAGS b) { return static_cast<DirectX::TEX_PMALPHA_FLAGS>(static_cast<unsigned long>(a & DirectX::TEX_FILTER_SRGB_MASK) | static_cast<unsigned long>(b)); }

// TEX_COMPRESS_SRGB match TEX_FILTER_SRGB
constexpr DirectX::TEX_COMPRESS_FLAGS operator|(DirectX::TEX_COMPRESS_FLAGS a, DirectX::TEX_FILTER_FLAGS b) { return static_cast<DirectX::TEX_COMPRESS_FLAGS>(static_cast<unsigned long>(a) | static_cast<unsigned long>(b & DirectX::TEX_FILTER_SRGB_MASK)); }
constexpr DirectX::TEX_COMPRESS_FLAGS operator|(DirectX::TEX_FILTER_FLAGS a, DirectX::TEX_COMPRESS_FLAGS b) { return static_cast<DirectX::TEX_COMPRESS_FLAGS>(static_cast<unsigned long>(a & DirectX::TEX_FILTER_SRGB_MASK) | static_cast<unsigned long>(b)); }


//=====================================================================================
// DXGI Format Utilities
//=====================================================================================

_Use_decl_annotations_
constexpr bool __cdecl IsValid(DXGI_FORMAT fmt) noexcept
{
    return (static_cast<size_t>(fmt) >= 1 && static_cast<size_t>(fmt) <= 190);
}

_Use_decl_annotations_
inline bool __cdecl IsCompressed(DXGI_FORMAT fmt) noexcept
{
    switch (fmt)
    {
        case DXGI_FORMAT_BC1_TYPELESS:
        case DXGI_FORMAT_BC1_UNORM:
        case DXGI_FORMAT_BC1_UNORM_SRGB:
        case DXGI_FORMAT_BC2_TYPELESS:
        case DXGI_FORMAT_BC2_UNORM:
        case DXGI_FORMAT_BC2_UNORM_SRGB:
        case DXGI_FORMAT_BC3_TYPELESS:
        case DXGI_FORMAT_BC3_UNORM:
        case DXGI_FORMAT_BC3_UNORM_SRGB:
        case DXGI_FORMAT_BC4_TYPELESS:
        case DXGI_FORMAT_BC4_UNORM:
        case DXGI_FORMAT_BC4_SNORM:
        case DXGI_FORMAT_BC5_TYPELESS:
        case DXGI_FORMAT_BC5_UNORM:
        case DXGI_FORMAT_BC5_SNORM:
        case DXGI_FORMAT_BC6H_TYPELESS:
        case DXGI_FORMAT_BC6H_UF16:
        case DXGI_FORMAT_BC6H_SF16:
        case DXGI_FORMAT_BC7_TYPELESS:
        case DXGI_FORMAT_BC7_UNORM:
        case DXGI_FORMAT_BC7_UNORM_SRGB:
            return true;

        default:
            return false;
    }
}

_Use_decl_annotations_
inline bool __cdecl IsPalettized(DXGI_FORMAT fmt) noexcept
{
    switch (fmt)
    {
        case DXGI_FORMAT_AI44:
        case DXGI_FORMAT_IA44:
        case DXGI_FORMAT_P8:
        case DXGI_FORMAT_A8P8:
            return true;

        default:
            return false;
    }
}

_Use_decl_annotations_
inline bool __cdecl IsSRGB(DXGI_FORMAT fmt) noexcept
{
    switch (fmt)
    {
        case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
        case DXGI_FORMAT_BC1_UNORM_SRGB:
        case DXGI_FORMAT_BC2_UNORM_SRGB:
        case DXGI_FORMAT_BC3_UNORM_SRGB:
        case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
        case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
        case DXGI_FORMAT_BC7_UNORM_SRGB:
            return true;

        default:
            return false;
    }
}


//=====================================================================================
// Image I/O
//=====================================================================================
_Use_decl_annotations_
inline HRESULT __cdecl SaveToDDSMemory(const DirectX::Image& image, DirectX::DDS_FLAGS flags, DirectX::Blob& blob) noexcept
{
    DirectX::TexMetadata mdata = {};
    mdata.width = image.width;
    mdata.height = image.height;
    mdata.depth = 1;
    mdata.arraySize = 1;
    mdata.mipLevels = 1;
    mdata.format = image.format;
    mdata.dimension = DirectX::TEX_DIMENSION_TEXTURE2D;

    return SaveToDDSMemory(&image, 1, mdata, flags, blob);
}

_Use_decl_annotations_
inline HRESULT __cdecl SaveToDDSFile(const DirectX::Image& image, DirectX::DDS_FLAGS flags, const wchar_t* szFile) noexcept
{
    DirectX::TexMetadata mdata = {};
    mdata.width = image.width;
    mdata.height = image.height;
    mdata.depth = 1;
    mdata.arraySize = 1;
    mdata.mipLevels = 1;
    mdata.format = image.format;
    mdata.dimension = DirectX::TEX_DIMENSION_TEXTURE2D;

    return SaveToDDSFile(&image, 1, mdata, flags, szFile);
}


//=====================================================================================
// Compatability helpers
//=====================================================================================
_Use_decl_annotations_
inline HRESULT __cdecl GetMetadataFromTGAMemory(const void* pSource, size_t size, DirectX::TexMetadata& metadata) noexcept
{
    return GetMetadataFromTGAMemory(pSource, size, DirectX::TGA_FLAGS_NONE, metadata);
}

_Use_decl_annotations_
inline HRESULT __cdecl GetMetadataFromTGAFile(const wchar_t* szFile, DirectX::TexMetadata& metadata) noexcept
{
    return GetMetadataFromTGAFile(szFile, DirectX::TGA_FLAGS_NONE, metadata);
}

_Use_decl_annotations_
inline HRESULT __cdecl LoadFromTGAMemory(const void* pSource, size_t size, DirectX::TexMetadata* metadata, DirectX::ScratchImage& image) noexcept
{
    return LoadFromTGAMemory(pSource, size, DirectX::TGA_FLAGS_NONE, metadata, image);
}

_Use_decl_annotations_
inline HRESULT __cdecl LoadFromTGAFile(const wchar_t* szFile, DirectX::TexMetadata* metadata, DirectX::ScratchImage& image) noexcept
{
    return LoadFromTGAFile(szFile, DirectX::TGA_FLAGS_NONE, metadata, image);
}

_Use_decl_annotations_
inline HRESULT __cdecl SaveToTGAMemory(const DirectX::Image& image, DirectX::Blob& blob, const DirectX::TexMetadata* metadata) noexcept
{
    return SaveToTGAMemory(image, DirectX::TGA_FLAGS_NONE, blob, metadata);
}

_Use_decl_annotations_
inline HRESULT __cdecl SaveToTGAFile(const DirectX::Image& image, const wchar_t* szFile, const DirectX::TexMetadata* metadata) noexcept
{
    return SaveToTGAFile(image, DirectX::TGA_FLAGS_NONE, szFile, metadata);
}
