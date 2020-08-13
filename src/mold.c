#include "../headers/global.h"
#include "../headers/mold.h"

/* Funkcija odredjuje gde ce se nalziti kalupi pri pokretanju igrice */
void mold_init(void){
    
    /* Inicijalizacija matrice polozaja centara kalupa */
    int i, j;
    for (i = 0; i < dim_of_mold_matrix; i++){
        for (j = 0; j < dim_of_mold_matrix; j++){
            mold_matrix[i][j] = false;
        }
    }
    
    /* Generisanje random mesta za polozaj kalupa */
    /* Ovo se radi tako sto izaberemo random mesto za jedan a zatim za sledece biramo mesto tako sto proveravamo da li na tom mestu
       vec postoji neki kalup */
    srand(time(NULL));
    for (i = 0; i < num_of_molds; i++) {
        helper_vector[0] = rand()%dim_of_mold_matrix;
        helper_vector[1] = rand()%dim_of_mold_matrix;
        while (mold_matrix[helper_vector[0]][helper_vector[1]] == true){
            helper_vector[0] = rand()%dim_of_mold_matrix;
            helper_vector[1] = rand()%dim_of_mold_matrix;
        }
        mold_matrix[helper_vector[0]][helper_vector[1]] = true;
        mold_center_x[i] = -4.5 + (float)helper_vector[0]*3.0;
        mold_center_y[i] = -4.5 + (float)helper_vector[1]*3.0;
    }
}

/* Pravljenje kalupa cije su pozicije definisane u funkciji postavljanje_kalupa */
void mold_render(void){
    
    /* Pravljenje kalupa u obliku kvadrata */
    glBegin(GL_POLYGON);
        glNormal3f(0,0,1);
        glVertex3f(mold_center_x[0] + 0.5, mold_center_y[0] + 0.5, 0);
        glVertex3f(mold_center_x[0] + 0.5, mold_center_y[0] - 0.5, 0);
        glVertex3f(mold_center_x[0] - 0.5, mold_center_y[0] - 0.5, 0);
        glVertex3f(mold_center_x[0] - 0.5, mold_center_y[0] + 0.5, 0);
    glEnd();
    
    /* Pravljenje kalupa u obliku kruga */
    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0,0,1);
        glVertex3f(mold_center_x[1], mold_center_y[1], 0);
        float alpha;
        for(alpha = 0; alpha < 2*(PI) + 0.1; alpha += 0.1){
            glVertex3f(mold_center_x[1] + cos(alpha)*0.6, mold_center_y[1] + sin(alpha)*0.6, 0);
        }
    glEnd();
    
    /* Pravljenje kalupa za valjak */
    glBegin(GL_POLYGON);
        glNormal3f(0,0,1);
        glVertex3f(mold_center_x[2] + 0.4, mold_center_y[2] + 0.7, 0);
        glVertex3f(mold_center_x[2] + 0.4, mold_center_y[2] - 0.7, 0);
        glVertex3f(mold_center_x[2] - 0.4, mold_center_y[2] - 0.7, 0);
        glVertex3f(mold_center_x[2] - 0.4, mold_center_y[2] + 0.7, 0);
    glEnd();
    
    /* Pravljenje kalupa za zvezdu */
    int i;
    float u;
    glBegin(GL_POLYGON);
        glNormal3f(0,0,1);
        for(i = 0, u = 0; u < 2*(PI); i++, u+= 0.2*(PI)){
            if(i%2==0)
                glVertex3f(mold_center_x[3]+0.35*cos(u), mold_center_y[3]+0.35*sin(u), 0);
            else
                glVertex3f(mold_center_x[3]+0.7*cos(u), mold_center_y[3]+0.7*sin(u), 0);
        }
    glEnd();
    
    /* Pravljenje kalupa za tetraedar */
    glBegin(GL_POLYGON);
        glNormal3f(0,0,1);
        for (i = 0; i < 3; i++){
            glVertex3f(mold_center_x[4] + 0.9*cos(-(PI)/6+2*(PI)/3*i), mold_center_y[4] + 0.9*sin(-(PI)/6+2*(PI)/3*i), 0);
        }
    glEnd();
    
     /* Pravljenje kalupa u obliku elipse */
    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0,0,1);
        glVertex3f(mold_center_x[5], mold_center_y[5], 0);
        float beta;
        for(beta = 0; beta < 2*(PI) + 0.1; beta += 0.1){
            glVertex3f(mold_center_x[5] + cos(beta)*0.7, mold_center_y[5] + sin(beta)*0.5, 0);
        }
    glEnd();
    
}