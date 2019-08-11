/*  g_offsets.cpp
 *
 *
 */
#include "common.h"
#include "offsets.h"
#include "netvar.h"

offsets_t g_offsets;

void offsets_t::init()
{
    string table_name = "";
    
    table_name = "DT_BaseEntity";
    g_offsets.base_entity.m_team        = g_netvar.get_offset(table_name, "m_iTeamNum");
    g_offsets.base_entity.m_collision   = g_netvar.get_offset(table_name, "m_Collision");
    g_offsets.base_entity.m_origin      = g_netvar.get_offset(table_name, "m_vecOrigin");
    
    table_name = "DT_BasePlayer";
    g_offsets.base_player.m_health      = g_netvar.get_offset(table_name, "m_iHealth");
    g_offsets.base_player.m_lifestate   = g_netvar.get_offset(table_name, "m_lifeState");
    g_offsets.base_player.m_view_offset = g_netvar.get_offset(table_name, "m_vecViewOffset");
    g_offsets.base_player.m_tick_base   = g_netvar.get_offset(table_name, "m_nTickBase");
    
    table_name = "DT_BaseCombatWeapon";
    g_offsets.base_combat_weapon.m_clip1= g_netvar.get_offset(table_name, "m_iClip1");
    
    table_name = "DT_PlantedC4";
    g_offsets.planted_c4.m_bomb_ticking = g_netvar.get_offset(table_name, "m_bBombTicking");
    g_offsets.planted_c4.m_blow_time    = g_netvar.get_offset(table_name, "m_flC4Blow");
    g_offsets.planted_c4.m_bomb_defused = g_netvar.get_offset(table_name, "m_bBombDefused");
    g_offsets.planted_c4.m_bomb_defuser = g_netvar.get_offset(table_name, "m_hBombDefuser");
    g_offsets.planted_c4.m_defuse_count_down = g_netvar.get_offset(table_name, "m_flDefuseCountDown");
}
