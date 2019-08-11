/*      draw_model_execute.cpp
 *
 *
 */
#include "common.h"
#include "chams.h"

void draw_model_execute_hook(void* thisptr, void* context, void* state, const model_render_info_t& model_info, matrix3x4_t* matrix)
{
    print_hook();
    
    if(model_info.m_model)
    {
        g_chams->player(thisptr, context, state, model_info, matrix);
    }
    
    model_vmt->get_original_method<draw_model_execute_fn>(INDEX_DRAW_MODEL_EXE)(thisptr, context, state, model_info, matrix);
    g_model_render->forced_material_override(NULL);
}
