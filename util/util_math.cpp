/*      util_math.cpp
 *
 *
 */
#include "common.h"

/*
 *  world_to_screen
 *  Converts a point in the game to a point on the screen
 */
bool world_to_screen(vec3_t& in, vec3_t& out)
{
    return !g_overlay->screen_position(in, out);
}

/*
 *  get_player_box
 *  Returns the bounds of the player as a box
 */
player_box_t get_player_box(base_entity_t* entity)
{
    player_box_t box;
    
    if (!entity)
        return box;
    
    vec3_t origin = entity->get_origin();
    vec3_t min = entity->get_collidable()->obb_min() + origin;
    vec3_t max = entity->get_collidable()->obb_max() + origin;
    
    vec3_t points[] =
    {
        vec3_t(min.x, min.y, min.z),
        vec3_t(min.x, max.y, min.z),
        vec3_t(max.x, max.y, min.z),
        vec3_t(max.x, min.y, min.z),
        vec3_t(max.x, max.y, max.z),
        vec3_t(min.x, max.y, max.z),
        vec3_t(min.x, min.y, max.z),
        vec3_t(max.x, min.y, max.z)
    };
    
    vec3_t flb, brt, blb, frt, frb, brb, blt, flt;
    
    if (!world_to_screen(points[0], blb) || !world_to_screen(points[1], brb) || !world_to_screen(points[2], frb) ||
        !world_to_screen(points[3], flb) || !world_to_screen(points[4], frt) || !world_to_screen(points[5], brt) ||
        !world_to_screen(points[6], blt) || !world_to_screen(points[7], flt))
        return box;
    
    vec3_t arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };
    
    float left   = flb.x;   // left
    float top    = flb.y;   // top
    float right  = flb.x;   // right
    float bottom = flb.y;   // bottom
    
    for (int i = 1; i < 8; i++)
    {
        if (left > arr[i].x)
            left = arr[i].x;
        if (bottom < arr[i].y)
            bottom = arr[i].y;
        if (right < arr[i].x)
            right = arr[i].x;
        if (top > arr[i].y)
            top = arr[i].y;
    }
    
    box.x = left;
    box.y = top;
    box.w = right - left;
    box.h = bottom - top;
    box.valid = true;
}
