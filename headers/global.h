#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PI 3.1415926535
#define num_of_molds 6
#define dim_of_mold_matrix 4
#define timer_id_0 0
#define timer_id_1 1
#define milliseconds_0 100
#define milliseconds_1 1000
#define num_of_shapes 6

/* Dimenzije prozora */
extern int window_width, window_height;

extern int animation_ongoing;

/* Ugao rotacije kamere */
extern float ro, phi;

/* Ugao i smer pozicije svetlosti */
extern float beta;
extern int dir_of_light_position;

/* Broj sekundi i osvojeni poeni */
extern float sec_timer;
extern int score;

/* Pomeraj tela po svakoj osi*/
extern float position_x, position_y, position_z;

/* Rotacija tela po z osi */
extern float rotation;

/* Koordinate centra kalupa i niz koji pomaze u odredjivanju polozaja kalupa */
extern float mold_center_x[num_of_molds];
extern float mold_center_y[num_of_molds];
extern int helper_vector[2];

/* Matrica polozaja centara kalupa */
extern bool mold_matrix[dim_of_mold_matrix][dim_of_mold_matrix];

/* Izabrani oblik */
extern int shape;

#endif

