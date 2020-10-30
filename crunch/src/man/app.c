#include "app.h"
#include <man/man_game.h>
#include <sys/UI.h>
#include <sprites/g_palette.h>
#include <tilemaps/main_screen_pack.h>
#include <sprites/UI.h>
#include <sprites/door.h>
#include <sprites/char.h>
#include <sprites/mouse.h>
#include <sprites/fountain.h>
#include <sprites/converting1.h>
#include <sprites/converting2.h>

#include <music/sfx.h>
#include <music/intro.h>
#include <music/game.h>
#include <music/rym.h>

u8 render_count;
u8 music_play;
u16 music_sync;
u8 intro_state;

u8 x,y;
u16 activate;
const u8* spr;
void interrupt_1(){
    cpct_scanKeyboard();
    cpct_setInterruptHandler(interrupt_2);
}
void interrupt_2(){
    if(music_play){
        music_sync++;
        cpct_akp_musicPlay();
    }
    cpct_setInterruptHandler(interrupt_3);
}
void interrupt_3(){
    cpct_setInterruptHandler(interrupt_4);
}
void interrupt_4(){
    cpct_setInterruptHandler(interrupt_5);
}
void interrupt_5(){
    cpct_setInterruptHandler(interrupt_6);
}
void interrupt_6(){
    render_count--;
    if(!render_count){
        activate_render_signal();
        render_count = 2;
    }
    cpct_setInterruptHandler(interrupt_1);
}

const player_t character_sets[] = {
    {10 ,5  ,1  ,1},
    {15 ,1  ,1  ,1},
    {5  ,10 ,1  ,2},
    {5  ,2  ,3  ,1},
    {2  ,10 ,2  ,2},
};

typedef void (*Ptrf_v_v)(void);
Ptrf_v_v executing_state;

cpct_keyID left_value;
cpct_keyID right_value;
cpct_keyID up_value;
cpct_keyID down_value;
cpct_keyID fire1_value;
cpct_keyID fire2_value;

cpct_keyID* left;
cpct_keyID* right;
cpct_keyID* up;
cpct_keyID* down;
cpct_keyID* fire1;
cpct_keyID* fire2;

void man_app_draw_stats(u8 x, u8 y, player_t* stats){
    sys_UI_hp_mp_bars(x+12, y, spr_UI_00, stats->hp);
    sys_UI_hp_mp_bars(x+12, y+10, spr_UI_05, stats->mp);
    sys_UI_draw_damage(x, y, spr_UI_04, stats->ad);
    sys_UI_draw_damage(x, y+10, spr_UI_09, stats->ap);
}

void app_draw_sprite(u8 x, u8 y, const u8* spr, u8 w, u8 h){
    u8* pos = cpct_getScreenPtr (CPCT_VMEM_START,x, y);
    cpct_drawSprite (spr, pos, w, h);
}
void app_draw_box(u8 x, u8 y, u8 color, u8 w, u8 h){
    u8* pos = cpct_getScreenPtr (CPCT_VMEM_START,x, y);
    cpct_drawSolidBox (pos, color, w, h);
}
void app_draw_string(u8 x, u8 y, void* string){
    u8* pos = cpct_getScreenPtr (CPCT_VMEM_START,x, y);
    cpct_drawStringM1(string, pos);
}

//INTRO
void man_app_intro(){
    x = 28;
    activate = 330;
    spr = spr_mouse_1;
    cpct_zx7b_decrunch_s((u8*)0xFFFF,main_screen_pack_end);

    app_draw_sprite(20,128,spr_door_0, 8,48);
    app_draw_sprite(56,162,spr_fountain_0, 4,12);
    app_draw_box(20,174,0xFF, 40,2);
    app_draw_box(20,176,0xF0, 40,2);

    app_draw_string(32,182,"[space]" );

    cpct_akp_musicInit ((u8*)intro_address);
    executing_state = man_app_intro_update;
}
void man_app_intro_update(){
    if(cpct_isKeyPressed(Key_Esc)){
        executing_state = man_app_main;
    }
    if(intro_state == 0){
        if(cpct_isKeyPressed(Key_Space)){
            music_play = 1;
            intro_state = 1;
            app_draw_box(32,182,0x00, 14,8);
        }
    }
    else if(intro_state == 1){
        if(music_sync == 156){
            app_draw_sprite(20,128,spr_door_1,8,48);
        }
        else if(music_sync == 210){
            app_draw_sprite(20,128,spr_door_2,8,48);
        }
        else if(music_sync == 252){
            app_draw_sprite(20,128,spr_door_0,8,48);
            app_draw_sprite(28,166,spr_mouse_0,4,8);
        }
        else if(music_sync>252 && music_sync < 463){
            if(music_sync == activate){
                app_draw_box(x,166, 0x00, 4,8);
                app_draw_sprite(x+1,166,spr,4,8);
                ++x;
                if(spr == spr_mouse_1){
                    spr = spr_mouse_0;
                }
                else{
                    spr = spr_mouse_1;
                }
                activate+=6;
            }
        }
        else if(music_sync == 510){
            app_draw_sprite(51,158,spr_converting1,4,16);
            app_draw_sprite(56,162,spr_fountain_1,4,12);
        }
        else if(music_sync == 534){
            app_draw_sprite(51,150,spr_converting2,4,24);
            app_draw_sprite(56,162,spr_fountain_2,4,12);
        }
        else if(music_sync == 558){
            app_draw_sprite(51,150,spr_char_0,4,24);
            app_draw_sprite(56,162,spr_fountain_3,4,12);
        }
        else if(music_sync == 606){
            app_draw_sprite(51,150,spr_char_4,4,24);
        }
        else if(music_sync == 666){
            intro_state = 2;
            music_sync=0;
            x = 51;
            activate = 0;
            spr = spr_char_5;
        }
    }
    else if(intro_state == 2){
        if(music_sync < 144){
            if(music_sync == activate){
                app_draw_box(x,150, 0x00, 4,24);
                app_draw_sprite(x-1,150,spr,4,24);
                --x;
                if(spr == spr_char_5){
                    spr = spr_char_4;
                }
                else{
                    spr = spr_char_5;
                }
                activate+=6;
            }
        }
        if(music_sync == 228){
            executing_state = man_app_main;
        }
    }
}
//INTRO

//MENU
void man_app_main(){
    cpct_setPALColour (0, HW_CYAN);

    cpct_zx7b_decrunch_s((u8*)0xFFFF, main_screen_pack_end);

    app_draw_string(20, 144,"[Esc]  Set controls");
    app_draw_string(18, 160,"[Space] Play");
    executing_state = man_app_main_update;
}
void man_app_main_update(){
    if(cpct_isKeyPressed(Key_Esc)){
        executing_state = man_app_controls;
    }
    if(cpct_isKeyPressed(Key_Space)){
        executing_state = man_app_sel;
    }
}
//MENU
//CONTROLS
void man_app_controls(){
    
    u8 increment= 24;
    u8 x2 = 46;
    cpct_clearScreen(0);
    y = 40;
    x = 26;
    app_draw_string(32,16, "CONTROLS");
    app_draw_box(32,26, 0x0f, 16, 2);
    app_draw_string(x,y, "Left:");
    app_draw_box(x2,y, 0xFF, 2, 8);
    y += increment;
    app_draw_string(x,y, "Right:");
    app_draw_box(x2,y, 0xFF, 2, 8);
    y += increment;
    app_draw_string(x,y, "Up:");
    app_draw_box(x2,y, 0xFF, 2, 8);
    y += increment;
    app_draw_string(x,y, "Down:");
    app_draw_box(x2,y, 0xFF, 2, 8);
    y += increment;
    app_draw_string(x,y, "Sword:");
    app_draw_box(x2,y, 0xFF, 2, 8);
    y += increment;
    app_draw_string(x,y, "Knife:");
    app_draw_box(x2,y, 0xFF, 2, 8);

    app_draw_string(20,190, "[Esc] Back to menu");
    app_draw_box(x2,y, 0xFF, 2, 8);

    executing_state = man_app_controls_update;
}
void man_app_controls_update(){
    executing_state = man_app_main;
}
//CONTROLS

//CHARACTER SELECT
void man_app_sel(){

    cpct_clearScreen(0x0);
    app_draw_string(20,8, "SELECT YOUR STATS");
    app_draw_box(20,18, 0x0f, 34, 2);

    app_draw_string(6,60, "[1]");
    app_draw_string(6,116, "[2]");
    app_draw_string(6,172, "[3]");

    man_app_draw_stats(24, 55, character_sets);
    man_app_draw_stats(24, 111, character_sets+1);
    man_app_draw_stats(24, 167, character_sets+2);

    executing_state = man_app_sel_update;
}
void man_app_sel_update(){
    if(cpct_isKeyPressed(Key_1)){
        man_game_create_player(character_sets);
        executing_state = man_app_game;
    }
    else if(cpct_isKeyPressed(Key_2)){
        man_game_create_player(character_sets+1);
        executing_state = man_app_game;
    }
    else if(cpct_isKeyPressed(Key_3)){
        man_game_create_player(character_sets+2);
        executing_state = man_app_game;
    }
}
//CHARACTER SELECT

//GAME
void man_app_game(){
    cpct_akp_musicInit ((u8*)game_address);
    man_game_init();
    executing_state = man_app_game_update;
}
void man_app_game_update(){
    u8 next = man_game_play();
    if(next == win){
        executing_state = man_app_main;
    }
    else if(next== lose){
        executing_state = man_app_main;
    }
}
//GAME


void man_app_init(){
    music_play=0;
    music_sync=0;
    intro_state=0;
    cpct_disableFirmware();
    cpct_setPalette(g_palette,4);
    cpct_setDrawCharM1(3, 0);
    cpct_setBorder(HW_BLACK);

    cpct_akp_musicInit ((u8*)intro_address);
    cpct_akp_SFXInit ((void*) sfx_address);
    render_count = 2;

    left_value  = Key_A;
    right_value = Key_D;
    up_value    = Key_W;
    down_value  = Key_S;
    fire1_value = Key_O;
    fire2_value = Key_P;

    left  = &left_value;
    right = &right_value;
    up    = &up_value;
    down  = &down_value;
    fire1 = &fire1_value;
    fire2 = &fire2_value;

    sys_UI_pre_init();

    executing_state = man_app_intro;
}

void man_app_update(){
    cpct_waitVSYNC();
    cpct_waitHalts(3);
    cpct_waitVSYNC();
    cpct_setInterruptHandler(interrupt_1);

    while(1){
        executing_state();
        cpct_waitHalts(3);
    }
}
