#pragma once
#include <cpctelera.h>


#define e_t_invalid 0x00
#define e_t_render 0x01
#define e_t_physics 0x02
#define e_t_input 0x04
#define e_t_AI 0x08

#define e_t_dead 0x80

typedef struct et{
   u8 type;
   u8 x, y;
   u8 prevx, prevy;
   u8 w, h;
   i8 vx, vy;
   i8 prevvx, prevvy;
   i8 jumping;
   u8* sprite;
} ent_t;

void man_ent_init();
void man_ent_update();

ent_t* man_ent_create();
void man_ent_setdead(ent_t* dead_ent);

void man_ent_forall(void (*ptrfunc)(ent_t*));
void man_ent_forall_type( void (*ptrfunc)(ent_t*), u8 types);