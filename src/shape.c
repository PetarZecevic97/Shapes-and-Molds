#include "../headers/global.h"
#include "../headers/shape.h"

/* Pravi se random objekat */
void rand_shape(void){
    srand(time(NULL)); 
    shape = rand()%num_of_shapes+1;    
    rotation = (float)(rand()%60)*6;
    position_x = 0;
    position_y = 0;
    position_z = 2;
}

/* Pravljenje odgovarajuceg oblika u odnosu na to koji je izabran */
void shape_render(void){

    float u;
    
    /* Pravljenje/pomeranje izabranog oblika */
    switch (shape){
    case 1:
        /* Pravljenje/pomeranje kocke */
        glPushMatrix();
        glTranslatef(position_x,position_y,position_z);
        glRotatef(rotation, 0, 0, 1);
        glutSolidCube(1);
        glPopMatrix();
        break;
    case 2:
        /* Pravljenje/pomeranje sfere */
        glPushMatrix();
        glTranslatef(position_x,position_y,position_z);
        glRotatef(rotation, 0, 0, 1);
        glutSolidSphere(0.6,30,30);
        glPopMatrix();
        break;
    case 3:
        /* Pravljenje/pomeranje valjka i postavljanje normale za valjak */
        glPushMatrix();
        glTranslatef(position_x,position_y,position_z);
        glRotatef(rotation, 0, 0, 1);
        
        /* Pravljenje omotaca valjka */
        glBegin(GL_TRIANGLE_STRIP);
            for (u = 0; u < 2*(PI) + 0.1; u += 0.1) {
                glNormal3f(0.4*sin(u), 0, 0.4*cos(u));
                glVertex3f(0.4*sin(u), -0.7, 0.4*cos(u));
                glVertex3f(0.4*sin(u), 0.7, 0.4* cos(u));
            }
        glEnd();
        
        /* Pravljenje jedne baze valjka */
        glBegin(GL_TRIANGLE_FAN);
            glNormal3f(0,1,0);
            glVertex3f(0, 0.7, 0);
            for(u = 0; u < 2*(PI) + 0.1; u += 0.1){
                glNormal3f(0,1,0);
                glVertex3f(0.4*cos(u), 0.7, 0.4* sin(u));
            }
        glEnd();
        
        /* Pravljenje druge baze valjka */
        glBegin(GL_TRIANGLE_FAN);
            glNormal3f(0,-1,0);
            glVertex3f(0, -0.7, 0);
            for(u = 0; u < 2*(PI) + 0.1; u += 0.1){
                glNormal3f(0,-1,0);
                glVertex3f(0.4*cos(u), -0.7, 0.4* sin(u));
            }
        glEnd();
        glPopMatrix();
        break;
    case 4:
        /* Pravljenje/pomeranje zvezde i postavljanje njenih normala */
        glPushMatrix();
        glTranslatef(position_x,position_y,position_z);
        glRotatef(rotation, 0, 0, 1);      
        int i;  

        /* Pravljenje jedne baze zvezde */
        glBegin(GL_POLYGON);
            for(i = 0, u = 0; u < 2*(PI); i++, u+= 0.2*(PI)){
                if(i%2==0){
                    glNormal3f(0,0,-1);
                    glVertex3f(0.35*cos(u), 0.35*sin(u), -0.5);
                }
                else{
                    glNormal3f(0,0,-1);
                    glVertex3f(0.7*cos(u), 0.7*sin(u), -0.5);
                }
            }
        glEnd();
        
        /* Pravljenje omotaca zvezde */
        /* Omotac zvezde se sastoji od 10 pravougaonika koji su spojeni jednom stranicom i naizmenicno idu 
         u smeru spoljasnjost-unutrasnjost/unustrasnjost/spoljasnjost. Normale su nadjene preko vektorskog
         proizvoda dva vektora jednog pravougaonika (odnosno ravni u kojoj se on nalazi) */
        for(i = 0, u = 0; u < 2*(PI); i++, u+= 0.2*(PI)){
            if(i%2==0){
                glBegin(GL_POLYGON);
                    glNormal3f(-0.5*(0.7*sin(u+0.2*(PI))-0.35*sin(u)), 0.5*(0.7*cos(u+0.2*(PI))-0.35*cos(u)), 0);
                    glVertex3f(0.35*cos(u), 0.35*sin(u), -0.5);
                    glVertex3f(0.35*cos(u), 0.35*sin(u), 0);
                    glVertex3f(0.7*cos(u+0.2*(PI)), 0.7*sin(u+0.2*(PI)), 0);
                    glVertex3f(0.7*cos(u+0.2*(PI)), 0.7*sin(u+0.2*(PI)), -0.5);
                glEnd();
            }
            else{
                glBegin(GL_POLYGON);
                    glNormal3f(0.5*(0.35*sin(u+0.2*(PI))-0.7*sin(u)), -0.5*(0.35*cos(u+0.2*(PI))-0.7*cos(u)), 0);
                    glVertex3f(0.7*cos(u), 0.7*sin(u), -0.5);
                    glVertex3f(0.7*cos(u), 0.7*sin(u), 0);
                    glVertex3f(0.35*cos(u+0.2*(PI)), 0.35*sin(u+0.2*(PI)), 0);
                    glVertex3f(0.35*cos(u+0.2*(PI)), 0.35*sin(u+0.2*(PI)), -0.5);
                glEnd();
            }
        }
        
        /* Pravljenje druge baze zvezde */
        glBegin(GL_POLYGON);
            for(i = 0, u = 0; u < 2*(PI); i++, u+= 0.2*(PI)){
                if(i%2==0){
                    glNormal3f(0,0,1);
                    glVertex3f(0.35*cos(u), 0.35*sin(u), 0);
                }
                else{
                    glNormal3f(0,0,1);
                    glVertex3f(0.7*cos(u), 0.7*sin(u), 0);
                }
            }
        glEnd();
        glPopMatrix();
        break;
    case 5:
        /* Pravljenje/pomeranje tetraedra */
        glPushMatrix();
        glTranslatef(position_x,position_y,position_z);
        glRotatef(90,1.0,0.0,0.0);
        glRotatef(-90 + rotation,0.0,1.0,0.0);
        glRotatef(90,0.0,0.0,1.0);
        glutSolidTetrahedron();
        glPopMatrix();
        break;
    case 6:
        /* Pravljenje/pomeranje elipse i postavljanje njenih normala */
        glPushMatrix();
        glTranslatef(position_x,position_y,position_z);
        glRotatef(rotation, 0, 0, 1); 
        
        /* Pravljenje jedne baze */
        glBegin(GL_TRIANGLE_FAN);
            glNormal3f(0,0,1);
            glVertex3f(0, 0, 0);
            float beta;
            for(beta = 0; beta < 2*(PI) + 0.1; beta += 0.1){
                glVertex3f(cos(beta)*0.7, sin(beta)*0.5, 0);
            }
        glEnd();
    
        /* Pravljenje omotaca */
        glBegin(GL_TRIANGLE_STRIP);
            for (beta = 0; beta < 2*(PI) + 0.1; beta += 0.1) {
                glNormal3f(sin(beta), cos(beta), 0);
                glVertex3f(sin(beta)*0.7, cos(beta)*0.5, 0);
                glVertex3f(sin(beta)*0.7, cos(beta)*0.5, -0.5);
            }
        glEnd();
        
        /* Pravljenje druge baze */
        glBegin(GL_TRIANGLE_FAN);
            glNormal3f(0,0,-1);
            glVertex3f(0, 0, -0.5);
            for(beta = 0; beta < 2*(PI) + 0.1; beta += 0.1){
                glVertex3f(cos(beta)*0.7, sin(beta)*0.5, -0.5);
            }
        glEnd();
        glPopMatrix();
        break;
    
    default:
        break;
    }
}

void shadow_render(void){

    int i;

    switch (shape){
    case 1:
        /* Pravljenje ocrtavanja kocke */
        glPushMatrix();
        glTranslatef(position_x,position_y,0);
        glRotatef(rotation, 0, 0, 1);
        glBegin(GL_POLYGON);
            glNormal3f(0,0,1);
            glVertex3f(0.5, 0.5, 0);
            glVertex3f(0.5, -0.5, 0);
            glVertex3f(-0.5, -0.5, 0);
            glVertex3f(-0.5, 0.5, 0);
        glEnd();
        glPopMatrix();
        break;
    case 2:
        /* Pravljenje ocrtavanja lopte */
        glPushMatrix();
        glTranslatef(position_x,position_y,0);
        glRotatef(rotation, 0, 0, 1);
        glBegin(GL_TRIANGLE_FAN);
            glNormal3f(0,0,1);
            glVertex3f(0, 0, 0);
            float alpha;
            for(alpha = 0; alpha < 2*(PI) + 0.1; alpha += 0.1){
                glVertex3f(cos(alpha)*0.6, sin(alpha)*0.6, 0);
            }
        glEnd();
        glPopMatrix();
        break;
    case 3:
        /* Pravljenje ocrtavanja valjka */
        glPushMatrix();
        glTranslatef(position_x,position_y,0);
        glRotatef(rotation, 0, 0, 1);
        glBegin(GL_POLYGON);
            glNormal3f(0,0,1);
            glVertex3f(0.4, 0.7, 0);
            glVertex3f(0.4,  -0.7, 0);
            glVertex3f(-0.4,  -0.7, 0);
            glVertex3f(-0.4, 0.7, 0);
        glEnd();
        glPopMatrix();
        break;
    case 4:
        /* Pravljenje ocrtavanja zvezde */
        glPushMatrix();
        glTranslatef(position_x,position_y,0);
        glRotatef(rotation, 0, 0, 1);
        float u;
        glBegin(GL_POLYGON);
            glNormal3f(0,0,1);
            for(i = 0, u = 0; u < 2*(PI); i++, u+= 0.2*(PI)){
                if(i%2==0)
                    glVertex3f(0.35*cos(u), 0.35*sin(u), 0);
                else
                    glVertex3f(0.7*cos(u), 0.7*sin(u), 0);
            }
        glEnd();
        glPopMatrix();
        break;
    case 5:
        /* Pravljenje ocrtavanja tetraedra */
        glPushMatrix();
        glTranslatef(position_x,position_y,0);
        glRotatef(rotation, 0, 0, 1);
        glBegin(GL_POLYGON);
            glNormal3f(0,0,1);
            for (i = 0; i < 3; i++){
                glVertex3f(0.9*cos(-(PI)/6+2*(PI)/3*i), 0.9*sin(-(PI)/6+2*(PI)/3*i), 0);
            }
        glEnd();
        glPopMatrix();
        break;
    case 6:
        /* Pravljenje ocrtavanja elipse */
        glPushMatrix();
        glTranslatef(position_x,position_y,0);
        glRotatef(rotation, 0, 0, 1);
        glBegin(GL_TRIANGLE_FAN);
            glNormal3f(0,0,1);
            glVertex3f(0, 0, 0);
            float beta;
            for(beta = 0; beta < 2*(PI) + 0.1; beta += 0.1){
                glVertex3f(cos(beta)*0.7, sin(beta)*0.5, 0);
            }
        glEnd();
        glPopMatrix();
        break;
    default:
        break;
    }
}