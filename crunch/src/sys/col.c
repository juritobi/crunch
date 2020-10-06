#include "physics.h"
#include <man/man_ent.h>
#include <man/level.h>
#include <constants.h>


void sys_col_one(ent_t* e){
    u8 tile_x = e->x/4;
    u8 tile_y = e->y/8;
    u8 next_tile = tile_x + e->vx;
    u8 up_tile = tile_y - 1;
    u8 down_tile = tile_y + 3;
    u8* tilemap = man_level_get_tilemap();

    u16 array_pos= tile_y*tilemap_W + next_tile;
    if(tile_x != (e->x-1)/4){
        if(tilemap[array_pos] == 7 || tilemap[array_pos + tilemap_W] == 7 || tilemap[array_pos + tilemap_W +tilemap_W] == 7){
            e->vx = 0;
        }
    }

    array_pos = tile_y*tilemap_W + tile_x;
    if(tile_y != (e->y-1)/8){
        if(e->vy<0){
            
            array_pos = up_tile*tilemap_W + tile_x;
            if(tilemap[array_pos] == 7 || tilemap[array_pos+ 1] == 7 ){
                e->vy = 0;
            }
        }
        else if(e->vy>0){
            array_pos = down_tile*tilemap_W + tile_x;
            if(tilemap[array_pos] == 7 || tilemap[array_pos + 1] == 7 ){
                e->vy = 0;
            }
        }
    }

}

void sys_col_update(){
    man_ent_forall_type(sys_col_one, e_t_col);
}