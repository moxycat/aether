#ifndef _BATTLE_HPP_
#define _BATTLE_HPP_
#include "util.hpp"
#include "entity.hpp"

void battle(player_state_t *pst, enemy_state_t *est);

void victory(player_state_t *pst, enemy_state_t *est);

void defeat(player_state_t *pst, enemy_state_t *est);

void escape(player_state_t *pst, enemy_state_t *est);

void player_turn(player_state_t *pst, enemy_state_t *est);

void enemy_turn(player_state_t *pst, enemy_state_t *est);

#endif
