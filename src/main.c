#include "../headers/global.h"
#include "../headers/timer.h"
#include "../headers/display.h"
#include "../headers/init.h"
#include "../headers/keyboard.h"

int window_width, window_height;
int animation_ongoing;
float ro, phi;
float beta;
int dir_of_light_position;
float sec_timer;
int score;
float position_x, position_y, position_z;
float rotation;
float mold_center_x[num_of_molds];
float mold_center_y[num_of_molds];
int helper_vector[2];
bool mold_matrix[dim_of_mold_matrix][dim_of_mold_matrix];
int shape;

static void on_reshape(int width, int height){
    
    /* Azuriranje sirine i visine prozora */
    window_width = width;
    window_height = height;
    
}

int main(int argc, char** argv){
    
    /* Inicijalizacija GLUT-a */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    /* Kreiranje prozora */
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Shapes and Molds");
    glutFullScreen();
    
    /* Registrovanje callback funkcija */
    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutTimerFunc(milliseconds_0, on_timer, timer_id_0);
    
    /* Obavljanje OpenGL inicijalizacije */
    glClearColor(0.5, 0.5, 0.5, 0);
    glEnable(GL_DEPTH_TEST);
    
    /* Obavljanje inicijalizacije igrice */
    initialize();

    /* Ulazak u glavnu petlju */
    glutMainLoop();
    
    return 0;
    
}
