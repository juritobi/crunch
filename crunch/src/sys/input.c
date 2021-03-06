#include "input.h"
#include <man/man_ent.h>
#include <man/app.h>
#include <sys/anim.h>

#define swordCD 7
#define swordDuration 7
#define jumpCD 7
#define PiumPiumCD  15

const i8 jumptable[] = {-8, -8, -8, -8, -8, 0, 0};

i8 swordUp;
i8 swordCooling;
i8 jumpCont;
i8 PiumPiumCont;

void sys_Input_init(){
    swordUp = 0;
    swordCooling = 0;
    jumpCont = 1;
    PiumPiumCont = 15;
}

void sys_input_one(ent_t* ent){
    
    ent->vx = 0;
    ent->vy = 8;
    // MONYECO
    if(cpct_isKeyPressed(*right)){
        ent->vx = 2;
        ent->action |= 0x01;
        if(!swordUp){
            ent->move_dir = dir_right;
        }
    }
    else if(cpct_isKeyPressed(*left)){
        ent->vx = -2;
        ent->action |= 0x01;
        if(!swordUp){
            ent->move_dir = dir_left;
        }
    }

    //SALTO Y SUS MIERDAS
    if(cpct_isKeyPressed(*up) && ent->on_ground && ent->jumping == -1 && jumpCont == jumpCD){
        ent->jumping = 0;
    }
    ent->on_ground = 0;
    if(cpct_isKeyPressed(*down)){
        ent->on_ground=2;
    }

    if(jumpCont < jumpCD){
        jumpCont++;
    }

    if(ent->jumping != -1){
        ent->vy = jumptable[ent->jumping];
        if(ent->jumping < sizeof(jumptable)-1){
            ent->on_ground=2;
            ent->jumping++;
            ent->action &= 0xF0;
            ent->action |= 0x02;
        }
        else{
            ent->jumping = -1;
            jumpCont=0;
        }
    }
    // PIUM PIUM

    if(cpct_isKeyPressed(*fire2) && PiumPiumCont == PiumPiumCD && ent->mp > 0){
        man_ent_resurrect(ent, 2);
        PiumPiumCont = 0;
        ent->mp = ent->mp -1;
        ent->action &= 0xF0;
        ent->action |= 0x03;
        cpct_akp_SFXPlay(2,0xf, 32, 0, 0, 0x04);
    }

    if(PiumPiumCont < PiumPiumCD){
        PiumPiumCont++;
    }
    
    // ESPADA
    if(cpct_isKeyPressed(*fire1) && !swordUp && !swordCooling){
        cpct_akp_SFXPlay(1,0xf, 0, 0, 0, 0x04);
        swordUp = swordDuration;
    }
    if(swordCooling){
        swordCooling--;
    }
    if(swordUp){ // si la espada activa
        ent->action &= 0xF0;
        ent->action |= 0x03;
        swordUp--;
        if(!swordUp){ // si la espada NO esta activa
            ent_t* to_kill = ent + 1;
            swordCooling = swordCD;
            to_kill->death(to_kill);
        }
    }
}

void sys_input_sword_move(){
    if(swordUp){
        man_ent_resurrect(player, 1);
    }
}

void sys_input_update(){
    sys_input_one(player);
}