// Aleksandra Hryncyszyn, 353636

// mamy wczytac pliki ktorych nazwy sa podane jako arguementy wywolania
// pliki w formacie .gpx, zawieraja tylko znaki ascii, 
    // wpt - waypoint
        // atrybuty lat i lon - latitude i longitude
        // ele - elevation - napis
    // kolejne wierzchloki lini lamanej to trkpt

// ma weryfikowac poprawnosc pliku gpx - nawiasy, atrybuty itp
// ma wypisywac max, min i mediane dlugosc szlakow i ich nazwy z name w trk
// oraz najwiekszy skonczony stosunek miedzy prawdziwa dlugoscia a prosta miedzy poczatkiem a koncem

#include <float.h>
#include "gpx_analysis.h"

int compare_trails(const void* a, const void* b);

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Poprawne uzycie: %s plik1.gpx [plik2.gpx ...\n", argv[0]);
        return 1;
    }

    // alokowanie tablicy na szlaki
    Trail* trails = malloc((argc - 1) * sizeof(Trail));

    // na wypadek gdyby nie wszystkie szlaki byly poprawne
    int trails_count = 0;

    // przechowywanie informacji o maksymalnych i  minimalnych szlakach
    Trail min_trail, max_trail, median_trail, max_ratio_trail;
    min_trail.length = DBL_MAX;
    max_trail.length = 0;
    max_ratio_trail.ratio = 0;

    // parsowanie szlakow i wyznaczanie min/max
    for (int i = 1; i < argc; i++)
    {
        if (!is_gpx_valid(argv[i])) continue;
        if (analyse_trail_from_gpx(argv[i], &trails[trails_count]) == 0)
        {
            if (trails[trails_count].length < min_trail.length) min_trail = trails[trails_count];
            if (trails[trails_count].length > max_trail.length) max_trail = trails[trails_count];
            if (trails[trails_count].ratio > max_ratio_trail.ratio) max_ratio_trail = trails[trails_count];
            trails_count++;
        }
    }

    // obliczanie mediany
    qsort(trails, trails_count, sizeof(Trail), compare_trails);
    median_trail = trails[trails_count / 2];

    // wypisywanie wynikow
    printf("Najkrótszy szlak: %.2f m, %s (%s)\n", min_trail.length, min_trail.name, min_trail.filename);
    printf("Najdłuższy szlak: %.2f m, %s (%s)\n", max_trail.length, max_trail.name, max_trail.filename);
    printf("Mediana długości: %.2f m, %s (%s)\n", median_trail.length, median_trail.name, median_trail.filename);
    printf("Największy stosunek długości do odcinka prostego: %.2f, %s (%s) \n", max_ratio_trail.ratio, max_ratio_trail.name, max_ratio_trail.filename);

    // zwalnianie pamieci
    for (int i = 0; i < trails_count; i++) 
    {
        free(trails[i].filename);
        free(trails[i].name);
    }
    free(trails);
}

int compare_trails(const void* a, const void* b)
{
    Trail* trail_a = (Trail*)a;
    Trail* trail_b = (Trail*)b;

    if (trail_a -> length < trail_b -> length) return -1;
    else if (trail_a -> length > trail_b -> length) return 1;
    else return 0;
}
