
// mamy n miast polaczonych m drogami dwukierunkowymi (n,m < 100 000)
// drogi sa lotnicze, kolejowe i autobusowe
// z miasta 1 mamy najpierw poleciec samolotem, potem koleja, a na koncu autobusem
// 1) ile jest miast do ktorych mozna dotrzec tymi trzeba srodkami w tej kolejnosci?
// 2) do ilu miast mozna dotrzec uzywajac tylko samolotow?

#define MAXN 100000
#include <stdio.h>
#include <stdlib.h>

// ------------------ graf ---------------------
typedef struct Edge Edge;
struct Edge
{
    int to;
    char type;
    Edge* next;
};

void add_edge(Edge*** graph, int from, int to, char type)
{
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e -> to = to;
    e -> type = type;
    e -> next = (*graph)[from];
    (*graph)[from] = e;
}

// ------------------ kolejka ---------------------
typedef struct Node Node;
struct Node
{
    int curr_city;
    Node* next;
};

typedef struct Queue Queue;
struct Queue
{
    Node* front;
    Node* rear;
};

Queue* create_queue(void)
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q -> front = q -> rear = NULL;
    return q;
}

int is_empty(Queue* q)
{
    return q -> front == NULL;
}

void enqueue(Queue* q, int city)
{
    Node* new = (Node*)malloc(sizeof(Node));
    new -> curr_city = city;
    new -> next = NULL;
    if (q -> rear == NULL)
    {
        q -> front = q -> rear = new;
        return;
    }
    q -> rear -> next = new;
    q -> rear = new;
}

int dequeue(Queue* q)
{
    if (is_empty(q)) return -1;
    Node* temp = q -> front;
    int curr_city = temp -> curr_city;
    q -> front = q -> front -> next;
    if (q -> front == NULL) q -> rear = NULL;
    free(temp);
    return curr_city;
}

void free_queue(Queue* q)
{
    while (!is_empty(q)) dequeue(q);
    free(q);
}

// ------------------ szukanie miast osiagalnych w sekwencji ---------------------

int bfs_for_sequence(int start, Edge*** graph, int cities_count)
{
    Queue* q = create_queue();
    enqueue(q, start);

    // 2d tablica visited zeby uwzglednic rozne formy transportu z danego miasta
    // kolumna 0 - lot, 1 - kolej, 2 - autobus
    // oznacza jakiej formy transportu uzyjemy zeby wyjechac z danego miasta
    char** visited = (char**)calloc(cities_count, sizeof(char*));
    for (int i = 0; i < cities_count; i++)
    {
        visited[i] = (char*)calloc(3, sizeof(char));
    }
    visited[start][0] = 1;

    int count = 0;
    int curr_city;
    Edge* curr_edge;
    while (!is_empty(q))
    {
        curr_city = dequeue(q);
        for (int transport = 0; transport < 3; transport++)
        {
            if (!visited[curr_city][transport]) continue;

            // sprawdzamy wszystkie drogi z danego miasta
            for (curr_edge = (*graph)[curr_city]; curr_edge != NULL; curr_edge = curr_edge -> next)
            {
                // istnieje transport ktorego szukamy
                if ((transport == 0 && curr_edge -> type == 'L') ||
                    (transport == 1 && curr_edge -> type == 'K') ||
                    (transport == 2 && curr_edge -> type == 'A'))
                {
                    if (transport < 2 && !visited[curr_edge -> to][transport + 1])
                    {
                        visited[curr_edge -> to][transport + 1] = 1;
                        enqueue(q, curr_edge -> to);
                    }
                    if (transport == 2) count++;
                }
            }

        }
    }

    // zwalnianie pamieci
    for (int i = 0; i < cities_count; i++) free(visited[i]);
    free(visited);
    free_queue(q);
    return count;
}

// ------------------ szukanie miast osiagalnych samolotem ---------------------
int bfs_for_planes(int start, Edge*** graph, int cities_count)
{
    Queue* q = create_queue();
    enqueue(q, start);
    char* visited = (char*)calloc(cities_count, sizeof(char));
    visited[start] = 1;

    int count = 0;
    int curr_city;
    Edge* curr_edge;
    while (!is_empty(q))
    {
        curr_city = dequeue(q);
        count++;

        for (curr_edge = (*graph)[curr_city]; curr_edge != NULL; curr_edge = curr_edge -> next)
        {
            if (curr_edge -> type == 'L' && !visited[curr_edge -> to])
            {
                visited[curr_edge -> to] = 1;
                enqueue(q, curr_edge -> to);
            }
        }
    }

    free_queue(q);
    free(visited);
    return count;
}


// ------------------ main ---------------------

int main(void)
{
    // wczytanie liczby miast i drog
    int cities_count = 0, roads_count = 0;
    scanf("%d %d", &cities_count, &roads_count);
    cities_count++; // bo nazwy miast zaczynaja sie od 1

    // wczytanie drog jako liste sasiedztwa
    Edge** graph = (Edge**)calloc(cities_count, sizeof(Edge*));
    int x, y; char z;
    for (int i = 0; i < roads_count; i++)
    {
        // wczytane drog w dwoch kierunkach
        scanf("%d %d %c", &x, &y, &z);
        add_edge(&graph, x, y, z);
        add_edge(&graph, y, x, z);
    }

    int cities_in_sequence = bfs_for_sequence(1, &graph, cities_count);
    int cities_by_plane = bfs_for_planes(1, &graph, cities_count);
    printf("%d %d", cities_in_sequence, cities_by_plane);

    // zwalnianie pamieci
    for (int i = 1; i <= cities_count; i++) 
    {
        Edge* current = graph[i];
        while (current != NULL) 
        {
            Edge* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph);
    return 0;
}
