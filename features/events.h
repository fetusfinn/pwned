/*
 *  events.h
 */
#pragma once

void hitmarker_event_player_hurt(game_event_t* event);

void bullet_impact(game_event_t* event);
void player_hurt(game_event_t* event);
void round_end(game_event_t* event);
void item_purchase(game_event_t* event);
