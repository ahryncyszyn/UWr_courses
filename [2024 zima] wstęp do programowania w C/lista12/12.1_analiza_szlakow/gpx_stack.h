#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// stos na elementy otwarte w pliku gpx
// gdy trafimy na element zamykajacy, sprawdzamy czy na stosie jest jego zamykajacy odpowiednik
typedef struct gpxNode gpxNode;
struct gpxNode
{
    char* name;
    gpxNode* next;
};

gpxNode* create_node(char* name);

void push(gpxNode** stack, char* name);

char* pop(gpxNode** stack);

char* peek(gpxNode* stack);

int isEmpty(gpxNode* top);





