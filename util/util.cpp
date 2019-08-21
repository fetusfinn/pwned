/*      util.cpp
 *
 *
 */
#include "common.h"
#include "util.h"

/*
 *  sdk definitions, todo : move elsewhere
 */
base_weapon_t* base_player_t::get_weapon()
{
    void* handle = this->get_weapon_handle();
    
    if(!handle)
        return nullptr;
    
    return (base_weapon_t*)g_ent_list->get_entity_from_handle(handle);
}

/*
 *  cheat_print
 *  Prints a message to the csgo console
 */
void cheat_print(const string& msg, string prefix, color_t col)
{
    prefix = "[" + prefix + "] ";
    g_cvar->console_print_color(col, "%s", prefix.c_str());
    g_cvar->console_print("%s\n", msg.c_str());
}

/*
 *  util_get_player_info
 *  Returns a player_info_t for a given player
 */
player_info_t util_get_player_info(player_t* player)
{
    player_info_t info;
    
    if(!player)
        return info;
    
    g_engine->get_player_info(player->get_index(), &info);
    
    return info;
}

// is_visible, todo : bool skip_ent, pass thru players n shit

/*
 *
 *
 */
bool util_is_point_visible(vec3_t point)
{
    if(!global::local || !g_engine_trace)
        return false;
    
    ray_t ray(global::local->get_eye_position(), point);
    trace_t trace;
    trace_filter_t filter(global::local);
    
    g_engine_trace->trace_ray(ray, 0x4600400b, &filter, &trace);
    
    return (trace.m_fraction > 0.97f);
}

/*
 *
 *
 */
bool util_is_player_visible(player_t* player)
{
    if(!global::local || !g_engine_trace || !player)
        return false;
    
    ray_t ray(global::local->get_eye_position(), player->get_eye_position());
    trace_t trace;
    trace_filter_t filter(global::local);
    
    g_engine_trace->trace_ray(ray, 0x4600400b, &filter, &trace);
    
    return (trace.m_ent == player || trace.m_fraction > 0.99f);
}

/*
 *
 *
 */
bool util_is_hitbox_visible(player_t* player, int hitbox)
{
    if(!global::local || !g_engine_trace || !player)
        return false;
    
    ray_t ray(global::local->get_eye_position(), get_hitbox_position(player, hitbox));
    trace_t trace;
    trace_filter_t filter(global::local);
    
    g_engine_trace->trace_ray(ray, 0x4600400b, &filter, &trace);

    return (trace.m_ent == player || trace.m_fraction > 0.99f);
}

/*
 *
 *
 */
long util_timestamp()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

/*
 *
 *
 */
std::string util_execute_cmd(const std::string& cmd, bool pop)
{
    std::string result;
    std::array<char, 128> buffer;
    std::shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);
    
    if (!pipe)
        throw std::runtime_error("");
    
    while (!feof(pipe.get()))
    {
        if (fgets(buffer.data(), 128, pipe.get()) != NULL)
            result += buffer.data();
    }
    
    if(pop)
        result.pop_back();
    
    return result;
}

/*
 *  to_color
 *  Returns the color_t value
 */
color_t ImColor::to_color()
{
    return color_t(Value.x * 255.f, Value.y * 255.f, Value.z * 255.f, Value.w * 255.f);
}
