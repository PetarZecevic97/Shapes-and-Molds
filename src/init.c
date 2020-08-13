#include "../headers/global.h"
#include "../headers/init.h"

/* Pocetna inicijalizacija */
void initialize(void){
    
    /* Postavljanje pocetnog ugla */
    ro = (PI)/4;
    phi = (PI)/4;
    
    /* Postavljanje pocetnog ugla i smera kretanja pozicije svetlosti */
    beta = 0;
    dir_of_light_position = 1;
    
    /* Postavljanje pocetnih pomeraja */
    position_x = 0;
    position_y = 0;
    position_z = 2;
    
    /* Sakrivanje centara kalupa */
    int i;
    for (i = 0; i < num_of_molds; i++) {
        mold_center_x[i] = 100;
        mold_center_y[i] = 100;
    }
    
    /* Inicijalizacija animacije, broja sekundi i osvojenih poena */
    animation_ongoing = 0;    
    sec_timer = 0;
    score = 0;
}