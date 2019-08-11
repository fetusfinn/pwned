/*
 *  model_render.h
 */
#pragma once

typedef unsigned short model_instance_handle_t;

struct model_render_info_t
{
    vec3_t              m_origin;
    qangle_t            m_angles;
    char                m_pad[0x4];
    void*               m_renderable;
    const model_t*      m_model;
    const matrix3x4_t*  m_model_to_world;
    const matrix3x4_t*  m_lighting_offset;
    const vec3_t*       m_lighting_origin;
    int                 m_flags;
    int                 m_entity_index;
    int                 m_skin;
    int                 m_body;
    int                 m_hitbox_set;
    model_instance_handle_t m_instance;
    
    model_render_info_t() : m_model_to_world(nullptr), m_lighting_offset(nullptr), m_lighting_origin(nullptr)
    {
    }
};

class model_render_t
{
public:
    
    void forced_material_override(material_t* mat)
    {
        typedef void (*o_forced_material_override)(void*, material_t*, int, int);
        return getvfunc<o_forced_material_override>(this, 1)(this, mat, 0, 0);
    }
    
    void draw_model_execute(void* ctx, void *state, const model_render_t& info, matrix3x4_t* matrix = NULL)
    {
        typedef void (*o_draw_model_execute)(void*, void*, void*, const model_render_t&, matrix3x4_t*);
        return getvfunc<o_draw_model_execute>(this, 21)(this, ctx, state, info, matrix);
    }    
};
