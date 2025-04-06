
#include "gpx_stack.h"

gpxNode* create_node(char* name)
{
    gpxNode* new_node = (gpxNode*)malloc(sizeof(gpxNode));
    if (new_node == NULL)
    {
        fprintf(stderr, "Allocating memory for a new node failed\n");
        return NULL;
    }
    new_node -> name = (char*)malloc(sizeof(char) * strlen(name));
    if (new_node -> name == NULL)
    {
        fprintf(stderr, "Allocating memory for a new node failed\n");
        free(new_node);
        return NULL;
    }
    strcpy(new_node -> name, name);
    new_node -> next = NULL;
    return new_node;
}

void push(gpxNode** stack, char* name)
{
    gpxNode* new_node = create_node(name);
    new_node -> next = (*stack);
    (*stack) = new_node;
}

char* pop(gpxNode** stack)
{
    if ((*stack) == NULL)
    {
        fprintf(stderr, "Can't pop from an empty stack!\n");
        return NULL;
    }
    gpxNode* temp = (*stack);

    // duplikowanie nazwy elementu - pamietac zeby zwolnic potem!
    char* popped_name = strdup(temp -> name);
    (*stack) = (*stack) -> next;
    free(temp -> name);
    free(temp);
    return popped_name;
}

char* peek(gpxNode* stack)
{
    if (stack == NULL)
    {
        fprintf(stderr, "Can't pop from an empty stack!\n");
        return NULL;
    }
    return stack -> name;
}

int isEmpty(gpxNode* stack)
{
    return stack == NULL;
}


