/*  antiaim.cpp
 *
 *
 */
#include "common.h"
#include "antiaim.h"

float get_max_desync_delta()
{
    if(!global::local)
        return 0.f;
    
    anim_state_t* anim = global::local->get_anim_state();
    
    if(!anim)
        return 0.f;
    
    float speed_fraction = std::max(0.0f, std::min(anim->feet_shuffle_speed, 1.0f));
    
    float speed_factor = std::max(0.0f, std::min(1.0f, anim->feet_shuffle_Speed2));
    
    float unk1 = ((anim->running_accel_progress * -0.30000001) - 0.19999999) * speed_fraction;
    float unk2 = unk1 + 1.0f;
    float delta;
    
    if (anim->duck_progress > 0)
        unk2 += ((anim->duck_progress * speed_factor) * (0.5f - unk2));
    
    delta = *(float*)((uintptr_t)anim + 0x3A4) * unk2;
    
    return abs(delta);
}

bool will_lby_update()
{
    if(!global::local)
        return false;
    
    static float next_update = 0;
    
    float curtime = util_curtime_fixed();
    anim_state_t* anim = global::local->get_anim_state();
    
    if (!anim || !(global::local->get_flags() & FL_ONGROUND))
        return false;
    
    if (anim->speed_2d > 0.1f)
        next_update = curtime + 0.22f;
    
    if (next_update < curtime)
    {
        next_update = curtime + 1.1f;
        return true;
    }
    
    return false;
}

bool break_lby()
{
    if(will_lby_update())
    {
        // flick
        return true;
    }
    
    return false;
}

void desync(float& angle, const float& old_angle, bool& bSendPacket)
{
    float max_delta = get_max_desync_delta();
    
    bool  bb= false;
    bool* sp= &bb;
    bool& b = *sp;
    
    b = true;
}

void fake_duck()
{
    if(!global::cmd)
        return;
    
    global::cmd->m_buttons |= IN_BULLRUSH;
    
    if (global::choked > 7)
        global::cmd->m_buttons |= IN_DUCK;
    else
        global::cmd->m_buttons &= ~IN_DUCK;
}
