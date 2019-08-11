/*
 *  material.h
 */
#pragma once

#pragma once

class material_var_t;
typedef uint64_t vertex_format_t;

enum material_var_flags_t
{
    MATERIAL_VAR_DEBUG = ( 1 << 0 ),
    MATERIAL_VAR_NO_DEBUG_OVERRIDE = ( 1 << 1 ),
    MATERIAL_VAR_NO_DRAW = ( 1 << 2 ),
    MATERIAL_VAR_USE_IN_FILLRATE_MODE = ( 1 << 3 ),
    MATERIAL_VAR_VERTEXCOLOR = ( 1 << 4 ),
    MATERIAL_VAR_VERTEXALPHA = ( 1 << 5 ),
    MATERIAL_VAR_SELFILLUM = ( 1 << 6 ),
    MATERIAL_VAR_ADDITIVE = ( 1 << 7 ),
    MATERIAL_VAR_ALPHATEST = ( 1 << 8 ),
    // MATERIAL_VAR_UNUSED  = (1 << 9),
    MATERIAL_VAR_ZNEARER = ( 1 << 10 ),
    MATERIAL_VAR_MODEL = ( 1 << 11 ),
    MATERIAL_VAR_FLAT = ( 1 << 12 ),
    MATERIAL_VAR_NOCULL = ( 1 << 13 ),
    MATERIAL_VAR_NOFOG = ( 1 << 14 ),
    MATERIAL_VAR_IGNOREZ = ( 1 << 15 ),
    MATERIAL_VAR_DECAL = ( 1 << 16 ),
    // MATERIAL_VAR_ENVMAPSPHERE = ( 1 << 17 ), // OBSOLETE
    // MATERIAL_VAR_UNUSED  = (1 << 18),
    // MATERIAL_VAR_ENVMAPCAMERASPACE = ( 1 << 19 ), // OBSOLETE
    MATERIAL_VAR_BASEALPHAENVMAPMASK = ( 1 << 20 ),
    MATERIAL_VAR_TRANSLUCENT = ( 1 << 21 ),
    MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = ( 1 << 22 ),
    // MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = ( 1 << 23 ), // OBSOLETE
    MATERIAL_VAR_OPAQUETEXTURE = ( 1 << 24 ),
    // MATERIAL_VAR_ENVMAPMODE = ( 1 << 25 ), // OBSOLETE
    MATERIAL_VAR_SUPPRESS_DECALS = ( 1 << 26 ),
    MATERIAL_VAR_HALFLAMBERT = ( 1 << 27 ),
    MATERIAL_VAR_WIREFRAME = ( 1 << 28 ),
    MATERIAL_VAR_ALLOWALPHATOCOVERAGE = ( 1 << 29 ),
    MATERIAL_VAR_ALPHA_MODIFIED_BY_PROXY = ( 1 << 30 ),
    MATERIAL_VAR_VERTEXFOG = ( 1 << 31 ),
};

enum preview_image_ret_val_t
{
    MATERIAL_PREVIEW_IMAGE_BAD = 0,
    MATERIAL_PREVIEW_IMAGE_OK,
    MATERIAL_NO_PREVIEW_IMAGE,
};

enum image_format_t
{
    IMAGE_FORMAT_UNKNOWN = -1,
    IMAGE_FORMAT_RGBA8888 = 0,
    IMAGE_FORMAT_ABGR8888,
    IMAGE_FORMAT_RGB888,
    IMAGE_FORMAT_BGR888,
    IMAGE_FORMAT_RGB565,
    IMAGE_FORMAT_I8,
    IMAGE_FORMAT_IA88,
    IMAGE_FORMAT_P8,
    IMAGE_FORMAT_A8,
    IMAGE_FORMAT_RGB888_BLUESCREEN,
    IMAGE_FORMAT_BGR888_BLUESCREEN,
    IMAGE_FORMAT_ARGB8888,
    IMAGE_FORMAT_BGRA8888,
    IMAGE_FORMAT_DXT1,
    IMAGE_FORMAT_DXT3,
    IMAGE_FORMAT_DXT5,
    IMAGE_FORMAT_BGRX8888,
    IMAGE_FORMAT_BGR565,
    IMAGE_FORMAT_BGRX5551,
    IMAGE_FORMAT_BGRA4444,
    IMAGE_FORMAT_DXT1_ONEBITALPHA,
    IMAGE_FORMAT_BGRA5551,
    IMAGE_FORMAT_UV88,
    IMAGE_FORMAT_UVWQ8888,
    IMAGE_FORMAT_RGBA16161616F,
    IMAGE_FORMAT_RGBA16161616,
    IMAGE_FORMAT_UVLX8888,
    IMAGE_FORMAT_R32F,            // Single-channel 32-bit floating point
    IMAGE_FORMAT_RGB323232F,    // NOTE: D3D9 does not have this format
    IMAGE_FORMAT_RGBA32323232F,
    IMAGE_FORMAT_RG1616F,
    IMAGE_FORMAT_RG3232F,
    IMAGE_FORMAT_RGBX8888,
    
    IMAGE_FORMAT_NULL,            // Dummy format which takes no video memory
    
    // Compressed normal map formats
    IMAGE_FORMAT_ATI2N,            // One-surface ATI2N / DXN format
    IMAGE_FORMAT_ATI1N,            // Two-surface ATI1N format
    
    IMAGE_FORMAT_RGBA1010102,    // 10 bit-per component render targets
    IMAGE_FORMAT_BGRA1010102,
    IMAGE_FORMAT_R16F,            // 16 bit FP format
    
    // Depth-stencil texture formats
    IMAGE_FORMAT_D16,
    IMAGE_FORMAT_D15S1,
    IMAGE_FORMAT_D32,
    IMAGE_FORMAT_D24S8,
    IMAGE_FORMAT_LINEAR_D24S8,
    IMAGE_FORMAT_D24X8,
    IMAGE_FORMAT_D24X4S4,
    IMAGE_FORMAT_D24FS8,
    IMAGE_FORMAT_D16_SHADOW,    // Specific formats for shadow mapping
    IMAGE_FORMAT_D24X8_SHADOW,    // Specific formats for shadow mapping
    
    // supporting these specific formats as non-tiled for procedural cpu access (360-specific)
    IMAGE_FORMAT_LINEAR_BGRX8888,
    IMAGE_FORMAT_LINEAR_RGBA8888,
    IMAGE_FORMAT_LINEAR_ABGR8888,
    IMAGE_FORMAT_LINEAR_ARGB8888,
    IMAGE_FORMAT_LINEAR_BGRA8888,
    IMAGE_FORMAT_LINEAR_RGB888,
    IMAGE_FORMAT_LINEAR_BGR888,
    IMAGE_FORMAT_LINEAR_BGRX5551,
    IMAGE_FORMAT_LINEAR_I8,
    IMAGE_FORMAT_LINEAR_RGBA16161616,
    
    IMAGE_FORMAT_LE_BGRX8888,
    IMAGE_FORMAT_LE_BGRA8888,
    
    NUM_IMAGE_FORMATS
};

enum material_property_types_t
{
    MATERIAL_PROPERTY_NEEDS_LIGHTMAP = 0,               // bool
    MATERIAL_PROPERTY_OPACITY,                          // int (enum MaterialPropertyOpacityTypes_t)
    MATERIAL_PROPERTY_REFLECTIVITY,                     // vec3_t
    MATERIAL_PROPERTY_NEEDS_BUMPED_LIGHTMAPS            // bool
};

class material_t
{
public:
    
    const char* get_name()
    {
        typedef const char* (*o_get_name)(void*);
        return getvfunc<o_get_name>(this, 0)(this);
    }
    
    const char* get_texture_group_name()
    {
        typedef const char* (*o_get_texture_group_name)(void*);
        return getvfunc<o_get_texture_group_name>(this, 1)(this);
    }
    
    void alpha_modulate(float alpha)
    {
        typedef void (*o_alpha_modulate)(void*, float);
        return getvfunc<o_alpha_modulate>(this, 27)(this, alpha);
    }
    
    void color_modulate(float r, float g, float b)
    {
        typedef void (*o_color_modulate)(void*, float, float, float);
        return getvfunc<o_color_modulate>(this, 28)(this, r, g, b);
    }
    
    void color_modulate(color_t color)
    {
        typedef void (*o_color_modulate)(void*, float, float, float);
        return getvfunc<o_color_modulate>(this, 28)(this, color.r() / 255.0f, color.g() / 255.0f, color.b() / 255.0f);
    }
    
    void increment_reference_count()
    {
        typedef void (*o_increment_reference_count)(void*);
        return getvfunc<o_increment_reference_count>(this, 10)(this);
    }
    
    void set_material_var_flag(material_var_flags_t flag, bool on)
    {
        typedef void (*o_set_material_var_flag)(void*, material_var_flags_t, bool);
        return getvfunc<o_set_material_var_flag>(this, 29)(this, flag, on);
    }
    
    float get_alpha_modulation()
    {
        typedef float (*o_get_alpha_modulation)(void*);
        return getvfunc<o_get_alpha_modulation>(this, 44)(this);
    }
    
    void get_color_modulation(float* r, float* g, float* b)
    {
        typedef void (*o_get_color_modulation)(void*, float*, float*, float*);
        return getvfunc<o_get_color_modulation>(this, 45)(this, r, g, b);
    }
};
