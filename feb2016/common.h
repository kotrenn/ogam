#ifndef __COMMON_H
#define __COMMON_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>


#include "geometry.h"

#define EPSILON 0.0001

using namespace std;

double clamp(double x, double a, double b);
#define signum(X) (((X) > 0) - ((X) < 0))

int randint(int a, int b);
double randdbl(double a, double b);
double random();

int rand_value_dict(int *count, int n);
int avg_value(int *vals, int n);
int avg_theta(int *theta, int n);

/* generate continuous approximation
   of geometric distribution of p
*/
double geometric(double p);

#endif
