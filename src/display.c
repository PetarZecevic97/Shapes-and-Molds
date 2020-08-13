#include "../headers/global.h"
#include "../headers/mold.h"
#include "../headers/shape.h"
#include "../headers/screentext.h"
#include "../headers/display.h"

void on_display(void){
    
    /* Promenljive koje cuvaju informacije o svetlosti i materijalima */
    /* Pozicija svetlosti se menja u odnosu na ugao koji se menja u tajmeru */
    GLfloat lightning_position[] = { 0, 7.5*sin(beta), 7.5*cos(beta), 1 };
    GLfloat ambient_lightning[] = { 0.1, 0.0, 0.0, 1 };
    GLfloat dif_lightning[] = { 1, 0.9, 0.9, 1 };
    GLfloat spec_lightning[] = { 1, 0.9, 0.9, 1 }; 
    GLfloat ambient_plane[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat dif_plane[] = { 0.1, 0.0, 0.0, 1 };
    GLfloat spec_plane[] = { 1, 1, 1, 1 };
    GLfloat plane_lightning = 10;
    GLfloat ambient_mold[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat dif_mold[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat spec_mold[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat mold_lightning = 50;
    GLfloat ambient_shape[] = { 0.4, 0.1, 0.1, 1 };
    GLfloat dif_shape[] = { 0.5, 0.1, 0.3, 1 };
    GLfloat spec_shape[] = { 0.8, 0.7, 0.8, 1 };
    GLfloat shape_lightning = 100;
    GLfloat ambient_shade[] = { 0.9, 0.6, 0.6, 1 };
    GLfloat dif_shade[] = { 0.9, 0.6, 0.6, 1 };
    GLfloat spec_shade[] = { 0.9, 0.6, 0.6, 1 };
    GLfloat shade_lightning = 100;
    GLfloat shade_lightning_position[] = { 0, 10, 0, 1 };
    GLfloat ambient_lightning_shade[] = { 0.1, 0.0, 0.0, 1 };
    GLfloat dif_lightning_shade[] = { 1, 0.9, 0.9, 1 };
    GLfloat spec_lightning_shade[] = { 1, 0.9, 0.9, 1 }; 
    
    /* Brisanje predhodnog sadrzaja prozora */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Podesavanje viewport-a */
    glViewport(0, 0, window_width, window_height);
    
    /* Podesavanje projekcije */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, window_width/(float)window_height, 1, 25);
    
    /* Poziva se funkcija za postavljanje teksta */
    screentext_render();
    
    /* Podesavanje vidne tacke */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.25*9*cos(ro)*sin(phi), 1.25*9*sin(ro)*sin(phi), 1.25*9*sqrt(2)*cos(phi), 0, 0, 0, 0, 0, 1);
    
     /* Dozvoljava se upotreba svetlosti */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    /* Postavljanje svetlosti */
    glLightfv(GL_LIGHT0, GL_POSITION, lightning_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_lightning);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif_lightning);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec_lightning);
    
    /* Postavljanje materijala za pravougaonik */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_plane);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, dif_plane);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spec_plane);
    glMaterialf(GL_FRONT, GL_SHININESS, plane_lightning);
    
    /* Pravougaonik sa kalupima */
    glBegin(GL_POLYGON);
        glNormal3f(0,0,1);
        glVertex3f(6, 6, 0);
        glVertex3f(6, -6, 0);
        glVertex3f(-6, -6, 0);
        glVertex3f(-6, 6, 0);
    glEnd();
    
    /* Ispituje se da li je isteklo vreme */
    if(sec_timer < 180 && animation_ongoing == 1){
    
        /* Postavljanje materijala za kalupe */
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_mold);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, dif_mold);
        glMaterialfv(GL_FRONT, GL_SPECULAR, spec_mold);
        glMaterialf(GL_FRONT, GL_SHININESS, mold_lightning);
        
        /* Postavljanje offset-a tako da kalupi bolje vide u pravougaoniku */
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(-1.0, 1.0);
        
        /* Poziva se funkcija za pravljenje kalupa */
        mold_render();
        
        /* Postavljanje materijala za oblike */
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_shape);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, dif_shape);
        glMaterialfv(GL_FRONT, GL_SPECULAR, spec_shape);
        glMaterialf(GL_FRONT, GL_SHININESS, shape_lightning);
        
        /* Ukljucuje se kliping ravan koja se nalazi u ravni pravougaonika sa kalupa */
        double clip_plane[] = {0, 0, 1, 0};
        glClipPlane(GL_CLIP_PLANE0, clip_plane);
        glEnable(GL_CLIP_PLANE0);
        
        /*Iskljucujemo offset kad pravimo oblike */
        glDisable(GL_POLYGON_OFFSET_FILL);
        
        /* Poziva se funkcija za pravljenje oblika */
        shape_render();
        
        /* Iskljucije se kliping ravan */
        glDisable(GL_CLIP_PLANE0);
        
        
        /* Postavljanje offset-a za ocrtavanje objekata tako da je prioritet vidljivosti veca
         od prioriteta za pravougaonik sa kalupima a manja od prioriteta za kalupe */
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(-0.5, 0.5);
        
        /* Postavljanje materijala za ocrtavanja oblika */
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_shade);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, dif_shade);
        glMaterialfv(GL_FRONT, GL_SPECULAR, spec_shade);
        glMaterialf(GL_FRONT, GL_SHININESS, shade_lightning);
        
        /*Iskljucujemo svetlo iz tacke koja se pomera i ukljucujemo i ukljucujemo iz 
         staticne tacke kako bi se ocrtavanja objekata lepse videla */
        glDisable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        
    
        /* Postavljanje svetlosti za ocrtavanje objekata*/
        glLightfv(GL_LIGHT1, GL_POSITION, shade_lightning_position);
        glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_lightning_shade);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, dif_lightning_shade);
        glLightfv(GL_LIGHT1, GL_SPECULAR, spec_lightning_shade);
        
        /*Pozivamo funkciju za ocrtavanje objekata na pravougaoniku sa kalupima */
        shadow_render();
        
        /* Iskljucuje se svetlost */
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHTING);
         
        /* Iskljucivanje offset-a */
        glDisable(GL_POLYGON_OFFSET_FILL);
    
    }
    
    /* Nova slika se salje na ekran */
    glutSwapBuffers();
    
}