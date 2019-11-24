/*  events.cpp
 *
 *
 */
#include "common.h"
#include "events.h"
#include "visuals.h"
#include "notifications.h"

void bullet_impact(game_event_t* event)
{
    if(strcmp(event->get_name(), __FUNCTION__))
        return;
    
}

void player_hurt(game_event_t* event)
{
    if(strcmp(event->get_name(), __FUNCTION__))
        return;
    
    // we could just do everything here but the hitmarker_t struct
    // is defined in hitmarkers.cpp so we cant really access it from here
    hitmarker_event_player_hurt(event);
    
    if(set.misc.notifications.at(1))
    {
        int damage      = event->get_int("dmg_health");
        int remaining   = event->get_int("health");
        int hitgroup    = event->get_int("hitgroup");
        auto attacker   = g_ent_list->get_player(g_engine->get_player_for_user_id(event->get_int("attacker")));
        auto hurt       = g_ent_list->get_player(g_engine->get_player_for_user_id(event->get_int("userid")));
        
        string hg_str = "";
        
        switch(hitgroup)
        {
            case HITGROUP_HEAD:
                hg_str = "head";
            case HITGROUP_LEFTLEG:
            case HITGROUP_RIGHTLEG:
                hg_str = "leg";
            case HITGROUP_STOMACH:
                hg_str = "stomach";
            default:
                hg_str = "body";
        }
        
        // attacker hit hurt in the hitgroup for x damage (y hp remaining)
        g_notifications->add(std::string(util_get_player_info(attacker).name) + " hit " + std::string(util_get_player_info(hurt).name) + " in the " + hg_str + " for " + std::to_string(damage) + " damage (" + std::to_string(remaining) + "hp remaining)");
    }
}

void item_purchase(game_event_t* event)
{
    if(strcmp(event->get_name(), __FUNCTION__))
        return;
    
    if(set.misc.notifications.at(2))
    {
        auto player = g_ent_list->get_player(g_engine->get_player_for_user_id(event->get_int("userid")));
        g_notifications->add(std::string(util_get_player_info(player).name) + " bought " + std::string(event->get_string("weapon")));
    }
}

void round_end(game_event_t* event)
{
    if(strcmp(event->get_name(), __FUNCTION__))
        return;
    
    g_visuals->reset_player_alpha();
}
