/* klondike, Copyright (c) 2024  Joshua Timmons <josh@developerx.com>
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation.  No representations are made about the suitability of this
 * software for any purpose.  It is provided "as is" without express or
 * implied warranty.
 */

#ifndef __KLONDIKE_GAME_H__
#define __KLONDIKE_GAME_H__

#include "gltrackball.h"

#define NUM_SUITS 4
#define NUM_RANKS 13
#define NUM_CARDS 52
#define MAX_WASTE 24
#define MAX_FOUNDATION 13
#define MAX_TABLEAU 20

// random position offset for sloppy mode
#define RANDOM_POSITION_OFFSET (bp->sloppy ? (((float)random()) / ((float)RAND_MAX) - 0.5) * 0.0125 : 0)

typedef enum { DIAMONDS, CLUBS, HEARTS, SPADES } Suit;
typedef enum { NONE=0, ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING } Rank;

typedef enum {
  REDEAL_COLLECT_DECK, //0
  REDEAL_CENTER_DECK,  //1
  REDEAL_ROTATE_DECK, //2
  REDEAL_SPLIT_DECK,  //3
  REDEAL_SHUFFLE_DECK, //4
  REDEAL_COMBINE_DECKS, //5
  REDEAL_HOME_DECK, //6
  REDEAL_DEAL, //7
  REDEAL_PLAY //8
} redeal_state;

typedef struct {
    Suit suit;
    Rank rank;
    int is_face_up; // 0 for face down, 1 for face up

    int pile;
    int pile_index;    // Current interpolated pile index during animation
    int start_pile_index;  // Starting pile index when animation begins
    int end_pile_index;    // Target pile index for animation
    
    float x;
    float y;
    float z;
    float start_x;
    float start_y;
    float dest_x;
    float dest_y;
    float start_frame;
    float end_frame;
    float angle;
    float start_angle;
    float end_angle;
    float xy_angle;
    float start_xy_angle;
    float end_xy_angle;
    float start_z;    
    float xz_angle;
    float start_xz_angle;
    float end_xz_angle;
    float animation_lift_factor
} card_struct;

typedef struct {
    card_struct deck[NUM_CARDS];
    card_struct tableau[7][MAX_TABLEAU];
    int tableau_size[7];
    card_struct waste[MAX_WASTE];
    int waste_size;
    card_struct foundation[4][MAX_FOUNDATION];
    int foundation_size[4];

    int moves;
    int moves_since_waste_flip;

    // todo: the tableaus do not track the number of face up cards. This is a bug.
} game_state_struct;

typedef struct {
  GLXContext *glx_context;
  card_struct foundation_placeholders[4];
  card_struct tableau_placeholders[7];
  float waste_x;
  float waste_y;
  float deck_x;
  float deck_y;

  float scale;

  int tick;
  int universe_tick;
  float camera_phase;

  int final_animation;
  redeal_state redeal_state;
    
  game_state_struct *game_state;

  GLuint fronts[52];
  GLuint back;

  trackball_state *trackball;
  Bool button_down_p;

  // Preferences
  GLuint animation_ticks;
  int draw_count;
  int camera_speed;
  Bool sloppy;
  int add_lift_to_animation;

} klondike_configuration;


void klondike_initialize_deck(klondike_configuration *bp);
void klondike_shuffle_deck(card_struct deck[]);
void klondike_deal_cards(klondike_configuration *bp);
void klondike_free_game_state(game_state_struct *game_state);
int klondike_deck_size(game_state_struct *game_state);
void klondike_reset_board(klondike_configuration *bp);
game_state_struct *klondike_next_move(klondike_configuration *bp);

#endif /* __KLONDIKE_GAME_H__ */
