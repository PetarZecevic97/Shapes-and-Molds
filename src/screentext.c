#include "../headers/global.h"
#include "../headers/screentext.h"

/* Postavljanje teksta na ekran */
void screentext_render(void){
    
    /* Postavlja se broj sekundi na ekran */
    char seconds[50];
    sprintf(seconds, "%.0f", sec_timer);
    glColor3f( 1, 0, 0 );
    glWindowPos2i(10, 10);
    int len, i;
    len = (int)strlen(seconds);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, seconds[i]);
    }
    
    /* Postavlja se broj osvojenih poena na ekran */
    char points[50];
    sprintf(points, "%d", score);
    glColor3f( 1, 0, 0 );
    glWindowPos2i(10, 25);
    len = (int)strlen(points);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, points[i]);
    }
    
}