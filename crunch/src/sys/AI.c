#include "AI.h"

#define rate_of_fire 40
#define zombi_rate 15
#define ghost_rate 3
#define dasher_rate 15
#define move_rate 5

#define boss_inter_attack_time 70

const attack_t horizontal = {
    35,
    att_hor
};
const attack_t rain = {
    45,
    att_rain
};
const attack_t pilar = {
    35,
    att_pilar
};
const attack_t none = {
    20,
    att_none
};

u8 boss_timer;
u8 boss_attack_timer;
u8 boss_attack_index;
attack_t const *  attacks[3];
attack_t const *  attack;

void sys_AI_shoot(ent_t* e){
    e->Ai_counter--;
    e->type &= ~e_t_render;
    if(e->Ai_counter == 0){
        e->Ai_counter = rate_of_fire;
        man_ent_resurrect(e, 1);
    }
    if(e->Ai_counter >= rate_of_fire-2){
        e->type |= e_t_render;
    }

}
void sys_AI_zombi(ent_t* e){
    e->vy = 4;

    if(!e->Ai_counter){
        if (!e->vx){
            if(e->prev_vx <0 ){
                e->prev_vx = 2;
                e->move_dir = dir_right;
            }
            else {
                e->prev_vx = -2;
                e->move_dir = dir_left;
            }
        }
        e->Ai_counter = zombi_rate;
    }

    if(e->Ai_counter==1){
        e->vx = e->prev_vx;
    }
    else e->vx = 0;

    e->Ai_counter--;
}

void sys_AI_ghost(ent_t* e){
    
    e->vy = 0;
    e->vx = 0;
    if(e->Ai_counter == 0){
        if(e->x!=player->x){
            if(e->x < player->x){
                e->vx = 1;
                e->move_dir = dir_right;
            }
            else{
                e->vx = -1;
                e->move_dir = dir_left;
            }
        }
        if(e->y!=player->y){
            if(e->y < player->y){
                e->vy = 4;
            }
            else{
                e->vy = -4;
            }
        }
        e->Ai_counter = ghost_rate;
    }
    e->Ai_counter--;
}

void sys_AI_sonic(ent_t* e){
    e->vy = 4;

    if(e->prev_vy){
        e->action |= 2;
    }
    if(e->vx){
        e->vx = e->prev_vx;
        e->action |= 1;
    }
    else if(!e->Ai_counter){

        if(e->x > player->x) e->move_dir = dir_left;
        else e->move_dir = dir_right;

        if(e->prev_vy){
            if(e->x > player->x){
                e->vx = -2;
                e->prev_vx = -2;
            }
            else{
                e->vx = 2;
                e->prev_vx = 2;
            }
            e->action |= 1;
            e->prev_vy = 0;
        }
        else if(e->prev_vx){
            e->prev_vx = 0;
        }
        else if(!(player->y+player->h <= e->y  ||  player->y >= e->y+e->h) ){
                e->action |= 2;
                e->prev_vy = 1;
        }

        e->Ai_counter = dasher_rate;
    } 
    e->Ai_counter--;
    if(e->Ai_counter>dasher_rate){
        e->Ai_counter= dasher_rate;
    }
}

void sys_AI_boss(ent_t* e){
    e->move_dir = dir_right;
    if(!boss_timer){
        u8 rand = cpct_getRandom_lcg_u8(player->x);
        rand = rand%4;
        if(rand==boss_attack_index){
            if(rand==0) rand++;
            else rand--;
        }
        boss_attack_index = rand;
        boss_attack_timer = attacks[rand]->total_time;
        boss_timer = boss_inter_attack_time;
        attack = attacks[rand];
    }
//going tio use original x careful for breaks
    e->vy = 0;
    e->vx = 0;
    e->Ai_counter--;
    if(!e->Ai_counter){
        e->Ai_counter = move_rate;
        if(e->x == 32 && e->y == 72){
            e->originalvx = 1;
            e->originalvy = 0;
        }
        else if(e->x == 36 && e->y == 72){
            e->originalvx = 1;
            e->originalvy = 4;
        }
        else if(e->x == 40 && e->y == 88){
            e->originalvx = -1;
            e->originalvy = 4;
        }
        else if(e->x == 36 && e->y == 104){
            e->originalvx = -1;
            e->originalvy = 0;
        }
        else if(e->x == 32 && e->y == 104){
            e->originalvx = -1;
            e->originalvy = -4;
        }
        else if(e->x == 28 && e->y == 88){
            e->originalvx = 1;
            e->originalvy = -4;
        }
        e->vx = e->originalvx;
        e->vy = e->originalvy;
    }
    boss_timer--;
    if(boss_timer>boss_inter_attack_time) boss_timer =boss_inter_attack_time;
    attack->funct(e);// attack_function();
}
void att_none(ent_t* e){
    ent_t* en = e;
}

void att_hor(ent_t* e){
    if(boss_attack_timer==attack->total_time-1){//set entities to hit
        u8 xpos;
        u8 i = 3;
        cpct_akp_SFXPlay(8,0xf, 25, 0, 0, 0x04);
        if(player->x < 40){
            xpos = -(e+i)->w;
        }
        else{
            xpos = e->w;
        }
        while(i){
            (e + i)->originalx = xpos;
            i--;
        }
    }

    if(boss_attack_timer>10){
        e->action |= 0x01;
        if((e+3)->originalx < 40){
            e->move_dir = dir_right;
        }
        else{
            e->move_dir = dir_left;
        }
    }
    else{
        if(boss_attack_timer == 10){
            cpct_akp_SFXPlay(11,0xf, 37, 0, 0, 0x04);
            man_ent_resurrect(e, 1);
        }
        else if(boss_attack_timer == 9){
            cpct_akp_SFXPlay(11,0xf, 37, 0, 0, 0x04);
            man_ent_resurrect(e, 2);
        }
        else if(boss_attack_timer == 8){
            cpct_akp_SFXPlay(11,0xf, 37, 0, 0, 0x04);
            man_ent_resurrect(e, 3);
        }

        else if(boss_attack_timer==3){
            (e+1)->death(e+1);
        }
        else if(boss_attack_timer==2){
            (e+2)->death(e+2);
        }
        else if(boss_attack_timer==1){
            (e+3)->death(e+3);
        }

        else if(boss_attack_timer==0){
            attack = &none;
        }
    }
    boss_attack_timer--;
}

void att_rain(ent_t* e){

    if(boss_attack_timer==attack->total_time-1){//set entities to hit
        u8 i = 5;
        u8 xpos = player->x%4;
        xpos = xpos*4 + 8;
        cpct_akp_SFXPlay(8,0xf, 25, 0, 0, 0x04);
        while(i){
            (e + 3 + i)->originaly = 24;
            (e + 3 + i)->originalx = xpos;
            (e + 3 + i)->originalvy = 8;
            xpos+=12;
            i--;
        }
    }
    e->action |= 0x02;
    if(boss_attack_timer==28){
        cpct_akp_SFXPlay(9,0xf, 25, 0, 0, 0x04);
        man_ent_res_absolute(e, 3+1);
    }
    if(boss_attack_timer==27){
        cpct_akp_SFXPlay(9,0xf, 25, 0, 0, 0x04);
        man_ent_res_absolute(e, 3+2);
    }
    if(boss_attack_timer==26){
        cpct_akp_SFXPlay(9,0xf, 25, 0, 0, 0x04);
        man_ent_res_absolute(e, 3+3);
    }
    if(boss_attack_timer==25){
        cpct_akp_SFXPlay(9,0xf, 25, 0, 0, 0x04);
        man_ent_res_absolute(e, 3+4);
    }
    if(boss_attack_timer==24){
        cpct_akp_SFXPlay(9,0xf, 25, 0, 0, 0x04);
        man_ent_res_absolute(e, 3+5);
    }


    else if(boss_attack_timer==7){
        (e+3+1)->death(e+3+1);
    }
    else if(boss_attack_timer==6){
        (e+3+2)->death(e+3+2);
    }
    else if(boss_attack_timer==5){
        (e+3+3)->death(e+3+3);
    }
    else if(boss_attack_timer==4){
        (e+3+4)->death(e+3+4);
    }
    else if(boss_attack_timer==3){
        (e+3+5)->death(e+3+5);
    }
    else if(boss_attack_timer==0){
        attack = &none;
    }

    boss_attack_timer--;
}

void att_pilar(ent_t* e){

    if(boss_attack_timer==attack->total_time-1){//set entities to hit
        cpct_akp_SFXPlay(8,0xf, 25, 0, 0, 0x04);
        (e + 3 + 5 + 1)->originalx = player->x - 4;
        (e + 3 + 5 + 2)->originalx = player->x - 4;  
        man_ent_res_absolute(e, 3+5+2);
    }
    if(boss_attack_timer>6){
        e->action |= 0x03;
    }
    if(boss_attack_timer==7){
        (e+3+5+2)->death(e+3+5+2);
    }
    else if(boss_attack_timer==6){
        cpct_akp_SFXPlay(10,0xf, 25, 0, 0, 0x04);
        man_ent_res_absolute(e, 3+5+1);
    }
    else if(boss_attack_timer==1){
        (e+3+5+1)->death(e+3+5+1);
    }
    else if(boss_attack_timer==0){
        attack = &none;
    }

    boss_attack_timer--;
}

void sys_AI_one(ent_t* e){
    e->act(e);
}

void sys_AI_init(){
    boss_attack_timer = 0;
    boss_timer = boss_inter_attack_time;
    boss_attack_index = 0xFF;

    attacks[0] = &horizontal;
    attacks[1] = &rain;
    attacks[2] = &pilar;
    attack = &none;

}
void sys_AI_update(){
    man_ent_forall_type(sys_AI_one, e_t_AI);
}