#include "../headers/global.h"
#include "../headers/timer.h"

void on_timer(int value)
{
    /* U slucaju da smo usli u funkciju pozivom za pomeranje pozicije svetslosti */
    if (value == timer_id_0) {
        
        /* Odredjivanje u kom smeru treba da se krece pozicija svetlosti i pomeranje ugla te pozicije */
        if (dir_of_light_position == 1){
            beta += 0.01*(PI);
            if(beta >= (PI)/4){
                dir_of_light_position = 0;
            }
        }
        else {
            beta -= 0.01*(PI);
            if(beta <= -(PI)/4){
                dir_of_light_position = 1;
            }
        }
        
        /* Pozivanje display funkcije */
        glutPostRedisplay();

        /* Ponovno pozivanje tajmera */
        glutTimerFunc(milliseconds_0, on_timer, timer_id_0);
    }
    
    /* U slucaju da smo usli u funkciju pozivom za brojac sekundi */
    else if (value == timer_id_1){

        /* Ukoliko broj sekundi treba povecati za jedan pozivaju se ponovo display funkcija i tajmer */
        if(sec_timer < 180 && animation_ongoing == 1){
            sec_timer += 1;
            glutPostRedisplay();
            glutTimerFunc(milliseconds_1, on_timer, timer_id_1);
        }
        
        /* Ukoliko je broj sekundi dostigao svoj maksimum */
        else if (sec_timer >= 180 && animation_ongoing == 1){
            animation_ongoing = 0;
        }
        
    }
    
    /* U funkciju se nije uslo iz nekog od prethodna dva razloga */
    else{
        return;
    }
}