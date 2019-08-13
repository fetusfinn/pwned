/*  frame_stage_notify.cpp
 *
 *
 */
#include "common.h"
#include "visuals.h" // g_visuals

void frame_stage_notify_hook(void* thisptr, frame_stage_t frame_stage)
{
    print_hook();
    
    bool in_game = g_engine->is_in_game();
    qangle_t *view_punch = nullptr, *aim_punch = nullptr;
    qangle_t  orig_view, orig_aim;
    
    
    if(frame_stage == FRAME_START)
    {
        if(global::local && in_game)
        {
            if(set.misc.thirdperson)
            {
                // todo
                // *local->get_view_angles() = fake / real
            }
            
            
            if(set.misc.remove_view_punch)
            {
                aim_punch   = global::local->get_aim_punch_angle();
                view_punch  = global::local->get_view_punch_angle();
                orig_aim    = *aim_punch;
                orig_view   = *view_punch;
                
                aim_punch->init();
                view_punch->init();
            }
        }
    }
    
    if(frame_stage == FRAME_NET_UPDATE_START)
    {
        
    }
    
    if(frame_stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START)
    {
        if(in_game)
        {
            g_visuals->remove_flash();
        }
    }
    
    if(frame_stage == FRAME_NET_UPDATE_POSTDATAUPDATE_END)
    {
        if(in_game)
        {
            g_visuals->remove_smoke();
        }
    }
    
    if(frame_stage == FRAME_NET_UPDATE_END)
    {
        
    }
    
    client_vmt->get_original_method<frame_stage_notify_fn>(INDEX_FRAME_STAGE_NOTIFY)(thisptr, frame_stage);
    
    if(frame_stage == FRAME_RENDER_START)
    {
        
    }
    
    if(frame_stage == FRAME_RENDER_END)
    {
        
    }
    
    
    // clean up
    if(view_punch)
    {
        *view_punch = orig_view;
        view_punch = nullptr;
        delete view_punch;
    }
    
    if(aim_punch)
    {
        *aim_punch = orig_aim;
        aim_punch = nullptr;
        delete aim_punch;
    }
}
