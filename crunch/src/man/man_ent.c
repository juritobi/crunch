#include "man_ent.h"
#include <constants.h>
#include <man/man_game.h>
#include <man/level.h>
#include <sys/render.h>
#include <sys/AI.h>
#include <sys/anim.h>
#include <sprites/char.h>
#include <sprites/sword.h>
#include <sprites/shooter.h>
#include <sprites/zombi.h>
#include <sprites/proyectile.h>
#include <sprites/sword.h>
/*character-----------------------------------------------------*/
const ent_t init_player = {
   //generic
   e_t_physics | e_t_render | e_t_input | e_t_col |e_t_anim,             //u8 type;
   0,0,                                                        //u8 x, y;
   0,0,                                                        //u8 prevx, prevy;
   4,24,                                                       //u8 w, h;
   0,0,                                                        //i8 vx, vy;
   dir_right,                                                      //u8 move_dir;
   man_ent_char_death,                                         //Ptrf_v_ep death;
   //SONS
   0,0,                                                        //u8 originalx, originaly;
   0,0,                                                        //i8 originalvx, originalvy;
   //CHARACTERS
   5,5,0,                                                       //u8 hp, mp, damage;
   0,                                                          // invulnerable
   -1,                                                           // knockback
   1,                                                           //u8 dir;//0000-*-00-*-00 anim_action-*-anim_dir-*-knockback_dir
   //AI
   0,                                                          //Ptrf_v_ep act;
   0,0,                                                        //i8 prev_vx, prev_vy;
   //Input
   0,-1,                                                        //i8 on_ground, jumping;   
   //Animation
   4,                                                          //u8 anim_timer;
   0x00,                                                       //u8 action;  //action - dir  
   &c_s_0,                                                       //spr_frame_t* frame;      
   &c_spriteset,                                                       //spr_set_t* sprite_set;     
   //Collisions
   col_t_ally,                                                 //u8 col_type;                  
   //physics
   //render
   spr_char_0,                                                 //u8* sprite;                   
   0                                                          //u8* memory_pos;               
};
const ent_t init_sword = {
   //generic
   e_t_dead|e_t_render,                                        //u8 type;
   0,0,                                                        //u8 x, y;
   0,0,                                                        //u8 prevx, prevy;
   4,24,                                                       //u8 w, h;
   0,0,                                                        //i8 vx, vy;
   dir_right,                                                      //u8 move_dir;
   man_ent_generic_death,                                       //Ptrf_v_ep death;
   //SONS
   4,0,                                                        //u8 originalx, originaly;
   0,0,                                                        //i8 originalvx, originalvy;
   //CHARACTERS
   1,0,1,                                                       //u8 hp, mp, damage;
   50,                                                          // invulnerable
   -1,                                                           // knockback
   1,                                                           //u8 dir;//0000-*-00-*-00 anim_action-*-anim_dir-*-knockback_dir
   //AI
   0,                                                          //Ptrf_v_ep act;
   0,0,                                                        //i8 prev_vx, prev_vy;
   //Input
   0,0,                                                         //i8 on_ground, jumping;     
   //Animation
   0,                                                          //u8 anim_timer;
   0x00,                                                       //u8 action;  //action - dir  
   0x00,                                                       //spr_frame_t* frame;      
   0x00,                                                       //spr_set_t* sprite_set;  
   //Collisions
   col_t_ally_breaker,                                         //u8 col_type;                  
   //physics
   //render
   spr_sword,                                                  //u8* sprite;                   
   0                                                          //u8* memory_pos;               
};
const ent_t init_knife = {
   //generic
   e_t_dead | e_t_render | e_t_physics | e_t_col,               //u8 type;
   0,0,                                                        //u8 x, y;
   0,0,                                                        //u8 prevx, prevy;
   4,8,                                                        //u8 w, h;
   1,0,                                                        //i8 vx, vy;
   dir_right,                                                      //u8 move_dir;
   man_ent_generic_death,                                       //Ptrf_v_ep death;
   //SONS
   4,8,                                                        //u8 originalx, originaly;
   1,0,                                                        //i8 originalvx, originalvy;
   //CHARACTERS
   1,0,1,                                                       //u8 hp, mp, damage;
   50,                                                          // invulnerable
   0,                                                           // knockback
   1,                                                           //u8 dir;//0000-*-00-*-00 anim_action-*-anim_dir-*-knockback_dir
   //AI
   0,                                                          //Ptrf_v_ep act;
   0,0,                                                        //i8 prev_vx, prev_vy;
   //Input
   0,0,                                                         //i8 on_ground, jumping;        
   //Animation
   0,                                                          //u8 anim_timer;
   0x00,                                                       //u8 action;  //action - dir  
   0x00,                                                       //spr_frame_t* frame;      
   0x00,                                                       //spr_set_t* sprite_set;  
   //Collisions
   col_t_ally_breaker,                                         //u8 col_type;                  
   //physics
   //render
   spr_p_0,                                                //u8* sprite;                   
   0                                                          //u8* memory_pos;               
};
/*character-----------------------------------------------------*/
/*shoot-----------------------------------------------------*/
const ent_t init_shoot = {
   //generic
   e_t_AI | e_t_render |e_t_anim,                                         //u8 type;
   0,0,                                                        //u8 x, y;
   0,0,                                                        //u8 prevx, prevy;
   4,16,                                                       //u8 w, h;
   0,0,                                                        //i8 vx, vy;
   dir_left,                                                      //u8 move_dir;
   man_ent_generic_death,                                       //Ptrf_v_ep death;
   //SONS
   0,0,                                                        //u8 originalx, originaly;
   0,0,                                                        //i8 originalvx, originalvy;
   //CHARACTERS
   1,0,1,                                                       //u8 hp, mp, damage;
   50,                                                          // invulnerable
   0,                                                           // knockback
   1,                                                           //u8 dir;//0000-*-00-*-00 anim_action-*-anim_dir-*-knockback_dir
   //AI
   sys_AI_shoot,                                               //Ptrf_v_ep act;
   0,0,                                                        //i8 prev_vx, prev_vy;
   //Input
   0,0,                                                         //i8 on_ground, jumping;    
   //Animation
   1,                                                          //u8 anim_timer;
   0x00,                                                       //u8 action;  //action - dir  
   &s_w_0,                                                       //spr_frame_t* frame;      
   &s_spriteset,                                                //spr_set_t* sprite_set;  
   //Collisions
   col_t_enemy,                                                //u8 col_type;                  
   //physics
   //render
   spr_shooter_0,                                                //u8* sprite;                   
   0                                                          //u8* memory_pos;               

};
const ent_t init_shoot_son = {
   //generic
   e_t_dead | e_t_physics | e_t_render | e_t_col,              //u8 type;
   0,0,                                                        //u8 x, y;
   0,0,                                                        //u8 prevx, prevy;
   4,8,                                                        //u8 w, h;
   -1,0,                                                       //i8 vx, vy;
   dir_left,                                                      //u8 move_dir;
   man_ent_generic_death,                                      //Ptrf_v_ep death;
   //SONS
   -2,4,                                                       //u8 originalx, originaly;
   -1,0,                                                        //i8 originalvx, originalvy;
   //CHARACTERS
   1,0,1,                                                       //u8 hp, mp, damage;
   50,                                                          // invulnerable
   0,                                                           // knockback
   1,                                                           //u8 dir;//0000-*-00-*-00 anim_action-*-anim_dir-*-knockback_dir
   //AI
   0,                                                          //Ptrf_v_ep act;
   0,0,                                                        //i8 prev_vx, prev_vy;
   //Input
   0,0,                                                        //i8 on_ground, jumping;    
   //Animation
   0,                                                          //u8 anim_timer;
   0,                                                          //u8 action;  //action - dir  
   0x00,                                                       //spr_frame_t* frame;      
   0x00,                                                       //spr_set_t* sprite_set;   
   //Collisions
   col_t_enemy_breaker,                                        //u8 col_type;                  
   //physics
   //render
   spr_p_1,                                                    //u8* sprite;                   
   000                                                        //u8* memory_pos;                
};
/*shoot-----------------------------------------------------*/
/*zombi-----------------------------------------------------*/
const ent_t init_zombi = {

   //generic
   e_t_render | e_t_AI | e_t_col | e_t_physics,                //u8 type;
   0,0,                                                        //u8 x, y;
   0,0,                                                        //u8 prevx, prevy;
   4,16,                                                       //u8 w, h;
   0,0,                                                        //i8 vx, vy;
   dir_left,                                                      //u8 move_dir;
   man_ent_generic_death,                                       //Ptrf_v_ep death;
   //SONS
   0,0,                                                        //u8 originalx, originaly;
   0,0,                                                        //i8 originalvx, originalvy;
   //CHARACTERS
   2,0,1,                                                       //u8 hp, mp, damage;
   0,                                                          // invulnerable
   -1,                                                           // knockback
   1,                                                           //u8 dir;//0000-*-00-*-00 anim_action-*-anim_dir-*-knockback_dir
   //AI
   sys_AI_zombi,                                               //Ptrf_v_ep act;
   0,0,                                                        //i8 prev_vx, prev_vy;
   //Input
   0,0,                                                         //i8 on_ground, jumping;     
   //Animation
   0,                                                          //u8 anim_timer;
   0x00,                                                       //u8 action;  //action - dir  
   0x00,                                                       //spr_frame_t* frame;      
   0x00,                                                       //spr_set_t* sprite_set;     
   //Collisions
   col_t_enemy,                                                //u8 col_type;                  
   //physics
   //render
   spr_zombi_0,                                                //u8* sprite;                   
   0                                                          //u8* memory_pos;               
};
/*zombi-----------------------------------------------------*/
ent_t ents[20];
u8 invalid_at_end_of_ents;
ent_t*  next_free_ent;

void man_ent_init(){
   next_free_ent = ents;
   cpct_memset (ents, e_t_invalid, sizeof(ents)+1);
}

void man_ent_reset(){
   next_free_ent = ents+1;
   cpct_memset ((ents+1), e_t_invalid, sizeof(ents)-sizeof(ent_t));
}

void man_ent_update(ent_t* e){
   e->prevx = e->x;
   e->prevy = e->y;
   if(e->invulnerable > 0){
      e->invulnerable--;
   }
   
}

ent_t* man_ent_create(){
   ent_t* res = next_free_ent;
   ++next_free_ent;
   return res;
}
//tipo tiene en los 2 primeros bit el numero de entidades que crea y en los siguientes la entidad en la que empieza a crear
//la inicializacion de datos es para setear en ents el numro de entidades y class_main y class_init el puntero a la primera entidad que tiene que crear
//luego las crea en bucle y cambia la posicion de la entidad principal que sera siempre la primera de las 3

void man_ent_create_class(u8 type, u8 x, u8 y){
   u8 class_ents = (type & 0b11000000);
   const ent_t* class_init = &init_player;//contents of class init should NEVER be modified
   class_init += (type & 0b00111111);
   class_ents = class_ents >> 6;
   while(class_ents){
      ent_t* ent_in_class = man_ent_create_from_template(class_init);
      ent_in_class->x = x;
      ent_in_class->y = y;
      class_init++;
      class_ents--;
   }
}

ent_t* man_ent_create_from_template(const ent_t* template){
   ent_t* res = man_ent_create();
   cpct_memcpy(res, template, sizeof(ent_t));
   return res;
}
void man_ent_hit(ent_t* hitted){
   hitted->hp--;
   if(hitted->hp==0){
      hitted->death(hitted);
      
      man_level_kill_enemy();
      return;
   }
   hitted->invulnerable = 50;
   hitted->knockback = 0;
}


void man_ent_char_death(ent_t* dead_ent){
   ent_t* e = dead_ent;
   man_game_exit();
}
//esto habra que mejorarlo
void man_ent_generic_death(ent_t* dead_ent){

   u8* tilemap = man_level_get_tilemap();
   u8 tile_x = dead_ent->x/4;
   u8 tile_y = dead_ent->y/8 - 3;// -3 para por que el hud son 3 tiles
   u8 tile_w = dead_ent->w/4;
   u8 tile_h = dead_ent->h/8;
   u8 not_exact_tile_x = dead_ent->x%4;
   u8 not_exact_tile_y = dead_ent->y%8;

   u16 tile_pointer = tile_y * tilemap_W + tile_x;
   u8 byte_tile_x;
   u8 byte_tile_y;

   dead_ent->type |= e_t_dead;
   if( not_exact_tile_y) ++tile_h;
   if( not_exact_tile_x) ++tile_w;
   while(tile_w){
      u8 h = tile_h;
      tile_w--;
      byte_tile_x = (tile_x + tile_w)*4;
      while(h){
         h--;
         byte_tile_y = (tile_y +3 + h)*8;
         sys_ren_set_tile( tilemap[tile_pointer + h*tilemap_W + tile_w], byte_tile_x, byte_tile_y);
      }
      h= tile_h;
   }
   if(dead_ent->col_type == col_t_enemy){
         if(man_ent_get_char()->mp < 5){
         man_ent_get_char()->mp++;
         }
      }
}

void man_ent_forall(Ptrf_v_ep fun){
   ent_t* res = ents;
   while(res->type != e_t_invalid){
      fun(res);
      ++res;
   }
}
void man_ent_forall_type( Ptrf_v_ep fun, u8 types){
   ent_t* res = ents;
   while(res->type != e_t_invalid){
      if(!(res->type & e_t_dead)){
         if((res->type & types) == types){
            fun(res);
         }
      }
      ++res;
   }
}

void man_ent_forall_col_type_individual( Ptrf_v_ep fun, u8 types){
   ent_t* res = ents;
   while(res->type != e_t_invalid){
      if(!(res->type & e_t_dead)){
         if(res->col_type & types){
            fun(res);
         }
      }
      ++res;
   }
}

void man_ent_forall_col_type( Ptrf_v_epep fun, u8 first_type, u8 second_type){
   ent_t* ents1 = ents;
   ent_t* ents2 = ents;
   while(ents1->type != e_t_invalid){
      if((!(ents1->type & e_t_dead)) && (ents1->col_type & first_type)){

         while( ents2->type != e_t_invalid ){
            if(!(ents2->type & e_t_dead) && (ents2->col_type & second_type)) {
               
               fun(ents1, ents2);
            }
            ++ents2;
         }

      }
      
      ++ents1;
      ents2 = ents;
   }
}

void man_ent_resurrect(ent_t* e, u8 displacement){
   ent_t* e_to_res = e + displacement;
   e_to_res->type &= ~e_t_dead;
   man_ent_move(e, displacement);
   e_to_res->vx = e_to_res->originalvx;
   e_to_res->vy = e_to_res->originalvy;
   
}
void man_ent_move(ent_t* e, u8 displacement){
   ent_t* e_to_move = e + displacement;
   e_to_move->x = e->x + e_to_move->originalx;
   e_to_move->y = e->y + e_to_move->originaly;
}

ent_t* man_ent_get_char(){
   return &ents[0];
}