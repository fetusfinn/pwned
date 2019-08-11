/*  frame_stage_notify.cpp
 *
 *
 */
#include "common.h"

//FRAME_UNDEFINED     = -1,
//FRAME_START,
//FRAME_NET_UPDATE_START,
//FRAME_NET_UPDATE_POSTDATAUPDATE_START,
//FRAME_NET_UPDATE_POSTDATAUPDATE_END,
//FRAME_NET_UPDATE_END,
//FRAME_RENDER_START,
//FRAME_RENDER_END

void frame_stage_notify_hook(void* thisptr, frame_stage_t frame_stage)
{
    print_hook();
    
    client_vmt->get_original_method<frame_stage_notify_fn>(INDEX_FRAME_STAGE_NOTIFY)(thisptr, frame_stage);
}
