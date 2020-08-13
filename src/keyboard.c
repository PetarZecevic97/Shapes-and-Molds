#include "../headers/global.h"
#include "../headers/init.h"
#include "../headers/timer.h"
#include "../headers/mold.h"
#include "../headers/shape.h"
#include "../headers/keyboard.h"

void on_keyboard(unsigned char key, int x, int y){
    
    switch(key){
    
        /* Ako korisnik pritisne Esc program se zavrsava */
        case 27:
            exit(0);
            break;
           
        /* Igra se pokrece */
        case 'g':
            if (!animation_ongoing) {
                animation_ongoing = 1;
                score = 0;
                mold_init();
                rand_shape();
                glutTimerFunc(milliseconds_1, on_timer, timer_id_1);
            }
            break;

        /* Igra se prekida */
        case 'r':
            animation_ongoing = 0;
            initialize();
            glutPostRedisplay();
            break;
            
        /* Pritiskom tastera e kamera se pomera ulevo */
        case 'e':
            ro = ro + 0.1;
            if (ro >= 2*(PI)){
                ro = ro - 2*(PI);
            }
            glutPostRedisplay();
            break;
            
        /* Pritiskom tastera q kamera se pomera udesno */
        case 'q':
            ro = ro - 0.1;
            if (ro < 0){
                ro = ro + 2*(PI);
            }
            glutPostRedisplay();
            break;
        
        /* Kamera se pomera ka dole */
        case 's':
            if (phi < (PI)/2 - 0.1){
                phi = phi + 0.1;
            }
            glutPostRedisplay();
            break;
        
        /* Kamera se pomera ka gore */
        case 'w':
            if (phi > 0.2){
                phi = phi - 0.1;
            }
            glutPostRedisplay();
            break;
            
        /* Telo se rotira ulevo */
        case 'u':
            if ((position_z > 0.4 && shape != 5 && shape != 2 && shape != 0) 
                || (position_z > 0.2 && shape == 5) || (position_z > 0.5 && shape == 2)){
                rotation += 6;
                if(fabs(rotation - 360) <= 0.001){
                    rotation -= 360;
                }
            }
            glutPostRedisplay();
            break;
        
        /* Telo se rotira udesno */
        case 'o':
            if ((position_z > 0.4 && shape != 5 && shape != 2 && shape != 0)
                || (position_z > 0.2 && shape == 5) || (position_z > 0.5 && shape == 2)){
                rotation -= 6;
                if(fabs(rotation) <= 0.001){
                    rotation += 360;
                }
            }
            glutPostRedisplay();
            break;
            
        /* Telo se translira po x osi unapred */
        case 'i':
            if (position_x < 5 && ((shape != 0 && shape != 5 && shape != 2 && position_z > 0.4)
                || (shape == 5 && position_z > 0.2) || (shape == 2 && position_z > 0.5))){
                position_x += 0.1;
                glutPostRedisplay();
            }
            break;
           
        /* Telo se translira po x osi unazad */
        case 'k':
            if (position_x > -5 && ((shape != 0 && shape != 5 && shape != 2 && position_z > 0.4) 
                || (shape == 5 && position_z > 0.2) || (shape == 2 && position_z > 0.5))){
                position_x -= 0.1;
                glutPostRedisplay();
            }
            break;
        
        /* Telo se translira po y osi unapred */
        case 'j':
            if (position_y < 5 && ((shape != 0 && shape != 5 && shape != 2 && position_z > 0.4)
                || (shape == 5 && position_z > 0.2) || (shape == 2 && position_z > 0.5))){
                position_y += 0.1;
                glutPostRedisplay();
        }
            break;
        
        /* Telo se translira po y osi unapred */
        case 'l':
            if (position_y > -5 && ((shape != 0 && shape != 5 && shape != 2 && position_z > 0.4)
                || (shape == 5 && position_z > 0.2) || (shape == 2 && position_z > 0.5))){
                position_y -= 0.1;
                glutPostRedisplay();
            }
            break;
          
        /* Telo se translira po z osi ka gore */
        case 'y':
            if (position_z < 5 && shape != 0){
                position_z += 0.1;
                glutPostRedisplay();
            }
            break;
          
        /* Telo se translira po z osi ka dole
           Ako je telo iznad svog kalupa, moze da udje u kalup
           Ako se telo vise ne vidi, onda se brise */
        case 'h':
            
            switch(shape){
                /* Ako je trenutni shape kocka */
                case 1:
                    if ((position_z > 0.5 
                        || (position_z > -0.5  && (int)rotation % 90 == 0
                        && fabs(mold_center_x[0] - position_x) <= 0.001 
                        && fabs(mold_center_y[0] - position_y) <= 0.001))
                        && shape != 0){
                        position_z -= 0.1;
                        if (fabs(position_z + 0.5) <= 0.001){
                            if (sec_timer < 180){
                                score += 10;
                                rand_shape();
                            }
                        }
                        glutPostRedisplay();
                    }
                    break;
                    
                /* Ako je trenutni shape lopta */
                case 2:
                     if ((position_z > 0.6 
                        || (position_z > -0.6 
                        && fabs(mold_center_x[1] - position_x) <= 0.001
                        && fabs(mold_center_y[1] - position_y) <= 0.001))
                        && shape != 0){
                        position_z -= 0.1;
                        if (fabs(position_z + 0.6) <= 0.001){
                            if (sec_timer < 180){
                                score += 20;
                                rand_shape();
                            }
                        }
                        glutPostRedisplay();
                    }
                    break;
                  
                /* Ako je trenutni shape valjak */
                case 3:
                     if ((position_z > 0.5 
                        || (position_z > -0.5 && (int)rotation % 180 == 0
                        && fabs(mold_center_x[2] - position_x) <= 0.001
                        && fabs(mold_center_y[2] - position_y) <= 0.001))
                        && shape != 0){
                        position_z -= 0.1;
                        if (fabs(position_z + 0.5) <= 0.001){
                            if (sec_timer < 180){
                                score += 40;
                                rand_shape();
                            }
                        }
                        glutPostRedisplay();
                    }
                    break;
                    
                /* Ako je ternutni shape zvezda */
                case 4:
                     if ((position_z > 0.5 
                        || (position_z > -0.5 && (int)rotation % 72 == 0
                        && fabs(mold_center_x[3] - position_x) <= 0.001
                        && fabs(mold_center_y[3] - position_y) <= 0.001))
                        && shape != 0){
                        position_z -= 0.1;
                        if (fabs(position_z) <= 0.001){
                            if (sec_timer < 180){
                                score += 50;
                                rand_shape();
                            }
                        }
                        glutPostRedisplay();
                    }
                    break;
                
                /* Ako je ternutni shape tetraedar */
                case 5:
                     if ((position_z > 0.3
                        || (position_z > -0.8 && (int)rotation % 120 == 0
                        && fabs(mold_center_x[4] - position_x) <= 0.001
                        && fabs(mold_center_y[4] - position_y) <= 0.001))
                        && shape != 0){
                        position_z -= 0.1;
                        if (fabs(position_z + 0.8) <= 0.001){
                            if (sec_timer < 180){
                                score += 40;
                                rand_shape();
                            }
                        }
                        glutPostRedisplay();
                    }
                    break;
                    
                /* Ako je trenutni shape elipsa */
                case 6:
                     if ((position_z > 0.5 
                        || (position_z > -0.5 && (int)rotation % 180 == 0
                        && fabs(mold_center_x[5] - position_x) <= 0.001
                        && fabs(mold_center_y[5] - position_y) <= 0.001))
                        && shape != 0){
                        position_z -= 0.1;
                        if (fabs(position_z) <= 0.001){
                            if (sec_timer < 180){
                                score += 40;
                                rand_shape();
                            }
                        }
                        glutPostRedisplay();
                    }
                    break;
            }
        break;
    }
    
}