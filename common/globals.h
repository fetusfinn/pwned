/*
 * globals.h
 */
#pragma once

namespace global
{
    extern bool*        send_packet;
    extern player_t*    local;
    extern user_cmd_t*  cmd;
}

/*
 *
 */

extern settings_t set;

/*
 *  interfaces
 */

extern panel_t*             g_panel;
extern surface_t*           g_surface;
extern base_client_dll_t*   g_client;
extern cvar_t*      	    g_cvar;
extern engine_t*            g_engine;
extern entity_list_t*       g_ent_list;
extern debug_overlay_t*     g_overlay;
extern global_vars_t*       g_globals;
extern client_mode_t*       g_client_mode;
extern engine_trace_t*      g_engine_trace;
extern input_system_t*      g_input_system;
extern game_event_manager2_t*   g_game_events;
extern model_render_t*      g_model_render;
extern model_info_t*        g_model_info;
extern material_system_t*   g_mat_system;

/*
 *  functions
 */

extern random_int_fn        random_int_func;
extern random_seed_fn       random_seed_func;
extern random_float_fn      random_float_func;

/*
 *  vmts
 */

extern vmt_t* panel_vmt;
extern vmt_t* surface_vmt;
extern vmt_t* client_vmt;
extern vmt_t* client_mode_vmt;
extern vmt_t* model_vmt;
extern vmt_t* material_vmt;
