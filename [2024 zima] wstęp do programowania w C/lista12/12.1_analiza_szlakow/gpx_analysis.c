#include "gpx_analysis.h"

bool is_gpx_valid(char* filename)
{
    // otwieranie pliku
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Can't open file %s\n", filename);
        return 1;
    }

    // weryfikowanie otwartych i zamknietych nawiasow i atrybutow
    char c, prev_c = '.';
    int open_bracket_cnt = 0, closed_bracket_cnt = 0;
    int open_attrib_cnt = 0, closed_attrib_cnt = 0;
    while ((c = fgetc(file)) != EOF)
    {
        if (c == '<') open_bracket_cnt++;
        else if (c == '>') closed_bracket_cnt++;
        else if (prev_c == '=' && c == '"') open_attrib_cnt++;
        else if (prev_c != '\\' && c == '"') closed_attrib_cnt++;
        prev_c = c;
    }
    if (open_bracket_cnt != closed_bracket_cnt) return false;
    if (open_attrib_cnt != closed_attrib_cnt) return false;
    rewind(file);

    // weryfikowanie zagniezdzen tagow i wystapien kluczowych tagow/atrybutow
    gpxNode* stack = NULL;
    bool is_there_trk = false, is_there_trkpt = false;
    double lat, lon;
    int curr_tag_size = 5;
    char* curr_tag = (char*)malloc(sizeof(char) * curr_tag_size);
    char* temp_tag = NULL;
    char *line = NULL, *pos = NULL, *end = NULL, *end1 = NULL, *end2 = NULL, *prev_tag = NULL;
    size_t line_len = 0;
    while ((getline(&line, &line_len, file)) != -1)
    {
        // szuka wszystkich wystapien <
        for (pos = strchr(line, '<'); pos != NULL; pos = strchr(end + 1, '<'))
        {
            // tag moze byc zakonczony albo > albo spacja (jezeli ma atrybuty)
            // wybieramy to zakonczenie ktore wystepuje wczesniej
            end1 = strchr(pos, '>');
            end2 = strchr(pos, ' ');
            if (end1 == NULL) end = end2;
            else if (end2 == NULL) end = end1;
            else end = (end1 < end2) ? end1 : end2;

            // zwiekszanie pamieci na nazwe elementu
            if ((end - pos - 1) > curr_tag_size)
            {
                curr_tag_size = end - pos;
                temp_tag = realloc(curr_tag, curr_tag_size);
                if (temp_tag == NULL)
                {
                    fprintf(stderr, "Memory allocation failed\n");
                    free(line); free(curr_tag); free(prev_tag); 
                    return false;
                }
                curr_tag = temp_tag;
            }

            // kopiowanie tagu do osobnego stringa
            strncpy(curr_tag, pos + 1, end - pos - 1);
            curr_tag[end - pos - 1] = '\0';

            // ominiecie tagow "wyjatkow"
            if (strcmp(curr_tag, "?xml") == 0) continue;
            if (strcmp(curr_tag, "bounds") == 0) continue;

            // weryfikowanie odstepstw of schematu gpx
            if (strcmp(curr_tag, "trk") == 0)
            {
                if (is_there_trk) 
                {
                    fprintf(stderr, "There should be only one trk tag\n");
                    free(line); free(curr_tag); free(prev_tag);
                    return false;
                }
                is_there_trk = true;
            }
            if (strcmp(curr_tag, "trkpt") == 0)
            {
                is_there_trkpt = true;
                if (sscanf(pos, " <trkpt lat=\"%lf\" lon=\"%lf\"", &lat, &lon) != 2)
                {
                    fprintf(stderr, "Missing lat and lon values after trkpt tag\n");
                    free(line); free(curr_tag); free(prev_tag);
                    return false;
                }
            }

            // obsluga stosu w zaleznosci od rodzaju tagu
            if (curr_tag[0] == '/') // tag zamykajacy
            {   
                prev_tag = pop(&stack);
                if (prev_tag == NULL || strcmp(prev_tag, curr_tag + 1) != 0)
                {   
                    fprintf(stderr, "Closing tag %s is mismatched with the opening one: %s\n", curr_tag, prev_tag);
                    free(line); free(curr_tag); free(prev_tag); 
                    return false;
                }
            }
            else // tag otwierajacy
            {
                push(&stack, curr_tag);
            }
        }
    }

    // weryfikowanie czy nie zostaly niepolaczone tagi na stosie
    if (!isEmpty(stack))
    {
        fprintf(stderr, "Found unmatched tags:\n");
        while (!isEmpty(stack))
        {
            char* unmatched = pop(&stack);
            printf("Unmatched tag: <%s>\n", unmatched);
            free(unmatched);
        }
        free(line); free(curr_tag); free(prev_tag);
        return false;
    }

    // weryfikowanie czy wystapily tagi trk i trkpt
    if (!is_there_trk || !is_there_trkpt)
    {
        if (!is_there_trk) fprintf(stderr, "Missing trk tag\n");
        if (!is_there_trkpt) fprintf(stderr, "Missing trkpt tag\n");
        free(line); free(curr_tag); free(prev_tag);
        return false;
    }

    printf("File %s is correct!\n", filename);
    free(line); free(curr_tag); free(prev_tag);
    return true;
}

int analyse_trail_from_gpx(char* filename, Trail* trail)
{
    // otwieranie pliku
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Can't open file %s\n", filename);
        return 1;
    }

    // inicjalizowanie zmiennych structa trail
    trail -> length = 0;
    trail -> direct_distance = 0;
    trail -> filename = malloc(strlen(filename) + 1);
    if ((trail -> filename) == NULL) 
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    strcpy(trail -> filename, filename);

    // zmienne na wczytywanie wartosci
    double first_lat, first_lon, first_ele;
    double lat, lon, ele, prev_lat = 0, prev_lon = 0, prev_ele = 0;
    bool inside_trk = false, first_coords = true;
    char *pos, *end;
    int name_len;
    
    // wczytywanie pliku linijka po linijce
    char* line = NULL;
    size_t line_len = 0;
    while (getline(&line, &line_len, file) != -1)
    {
        if (strstr(line, "<trk>")) inside_trk = true;

        // wczytywanie nazwy szlaku
        if (inside_trk && (pos = strstr(line, "<name>")) != NULL)
        { 
            end = strstr(line, "</name>");
            name_len = (end - pos - 6);
            trail -> name = (char*)malloc(sizeof(char) * (name_len + 1));
            strncpy(trail -> name, pos + 6, name_len);
            trail -> name[name_len] = '\0';
        }

        // wczytywanie wspolrzednych
        if (strstr(line, "<trkpt"))
        {
            if (sscanf(line, " <trkpt lat=\"%lf\" lon=\"%lf\" ", &lat, &lon) != 2)
            {
                printf("Reading in the lat and lon values didnt succeed\n");
                return 1;
            }
        }
        // dodawanie odleglosci dopiero po wczytaniu wysokosci
        // (wspolrzedne i wysokosc sa w innych linijkach)
        if (inside_trk && strstr(line, "<ele>"))
        {
            if (sscanf(line, " <ele>%lf</ele> ", &ele) != 1)
            {
                printf("Reading in the elevation value didnt succeed\n");
                return 1;
            }
            if (first_coords)
            {
                first_coords = false;
                first_lat = lat;
                first_lon = lon;
                first_ele = ele;
            } else
            {
                trail -> length += calculate_distance(lat, lon, ele, prev_lat, prev_lon, prev_ele);
            }

            prev_lat = lat;
            prev_lon = lon;
            prev_ele = ele;
        }
    }

    // obliczanie stosunku miedzy obliczona dlugoscia a bezposrednim dystansem
    trail -> direct_distance = calculate_distance(lat, lon, ele, first_lat, first_lon, first_ele);
    if (trail -> direct_distance != 0) trail -> ratio = (trail -> length) / (trail -> direct_distance);
    else trail -> ratio = 0;

    free(line);
    return 0;
}

double calculate_distance(double lat, double lon, double ele,
                          double prev_lat, double prev_lon, double prev_ele)
{
    double lat_diff = (prev_lat - lat) * DEGREE_TO_SECONDS * LAT_TO_M;
    double lon_diff = (prev_lon - lon) * DEGREE_TO_SECONDS * LON_TO_M;
    double ele_diff = (prev_ele - ele);

    return sqrt((lat_diff * lat_diff) + (lon_diff * lon_diff) + (ele_diff * ele_diff));
}