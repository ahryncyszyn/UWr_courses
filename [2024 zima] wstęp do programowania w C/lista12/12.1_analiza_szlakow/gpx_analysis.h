
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "gpx_stack.h"

#define LAT_TO_M 30.72
#define LON_TO_M 19.22
#define DEGREE_TO_SECONDS 3600

typedef struct Trail
{
    char* name;
    double length;
    double direct_distance;
    double ratio;
    char* filename;
} Trail;

// weryfikuje poprawnosc formatowania pliku gpx
bool is_gpx_valid(char* filename);

// zczytuje z pliku gpx nazwe trasy, jej dlugosc i dlugosc w prostej linii miedzy poczatkiem a koncem
// zapisuje te informacje jako struct Trail w tablicy structow trail
int analyse_trail_from_gpx(char* filename, Trail* trail);

// oblicza odleglosc na podstawie twierdzenia pitagorasa w 3d
double calculate_distance(double lat, double lon, double ele, 
                          double prev_lat, double prev_lon, double prev_ele);