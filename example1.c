/* Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf */

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantele/locatiile
/// ex: 1 - restaurantul 1 si tot asa

typedef struct Graph
{
    int verticies;
    int *visited;
    struct Node **adjacency_list;
} GPH;

typedef struct Stack
{
    int t;
    int scap;
    int *arr;
} STK;

NODE *createNode(int verticies)
{
    NODE *nn = malloc(sizeof(NODE));
    nn->data = verticies;
    nn->next = NULL;
    return nn;
}

void addEdge(GPH *Graph, int src, int dest)
{
    NODE *nn = createNode(dest);
    nn->next = Graph->adjacency_list[src];
    Graph->adjacency_list[src] = nn;
}

GPH *createGraph(int verticies)
{
    GPH *Graph = malloc(sizeof(GPH));
    Graph->verticies = verticies;
    Graph->adjacency_list = malloc(sizeof(NODE *));
    Graph->visited = malloc(sizeof(int) * verticies);

    for (int i = 0; i < verticies; i++)
    {
        Graph->adjacency_list[i] = NULL;
        Graph->visited[i] = 0;
    }
    return Graph;
}

STK *createStack(int scap)
{
    STK *Stack = malloc(sizeof(STK));
    Stack->arr = malloc(scap * sizeof(int));
    Stack->t = -1;
    Stack->scap = scap;

    return Stack;
}

void push(int pushed, STK *Stack)
{
    Stack->t = Stack->t + 1;
    Stack->arr[Stack->t] = pushed;
}

void DFS(GPH *Graph, STK *Stack, int v_nr)
{
    NODE *adj_list = Graph->adjacency_list[v_nr];
    NODE *aux = adj_list;
    Graph->visited[v_nr] = 1;
    printf("%d ", v_nr);
    push(v_nr, Stack);
    while (aux != NULL)
    {
        int con_ver = aux->data;
        if (Graph->visited[con_ver] == 0)
            DFS(Graph, Stack, con_ver);
        aux = aux->next;
    }
}

void insertEdges(GPH *Graph, int number_of_edges, int number_of_verticies)
{
    int src, dest, i;
    printf("adauga %d munchii (de la 1 la %d)\n", number_of_edges, number_of_verticies);
    for (i = 0; i < number_of_edges; i++)
    {
        scanf("%d%d", &src, &dest);
        printf("addEdge\n");
        addEdge(Graph, src, dest);
    }
}

void wipe(GPH *Graph, int number_of_verticies)
{
    for (int i = 0; i < number_of_verticies; i++)
    {
        Graph->visited[i] = 0;
    }
}

void isReachable(GPH *Graph, int number_of_verticies, STK *s1, STK *s2) // 0 sau 1 daca poate fi sau nu ajuns
{
    printf("isReachable\n");
    int canbe = 0;
    
    for (int i = 0; i < number_of_verticies; i++) // aici i tine loc de numar adica de restaurant
    {
        for (int j = 0; j < number_of_verticies; j++)
        {
            DFS(Graph, s1, i);
            wipe(Graph, number_of_verticies);
            DFS(Graph, s2, j);
            for (int j = 0; j < number_of_verticies && !canbe; j++)
            {
                for (int i = 0; i < number_of_verticies && !canbe; i++)
                {
                    if ((s1->arr[i] == j) && (s2->arr[j] == i))
                        canbe = 1;
                }
            }
        }
    }

    if(canbe)
        printf("can be reached");
    else
        printf("cannot be reached");
}

int main()
{
    int number_of_verticies;
    int number_of_edges;
    int src, dest;
    int i;
    int starting_vertex;
    int virtex_2; // unused?
    int ans;

    printf("cate noduri are graful?");
    scanf("%d", &number_of_verticies);

    printf("cate muchii are graful?");
    scanf("%d", &number_of_edges);

    GPH *Graph = createGraph(number_of_verticies);

    printf("1\n");
    STK *s1 = createStack(2 * number_of_verticies);
    printf("2\n");
    STK *s2 = createStack(2 * number_of_verticies);
    printf("3\n");

    insertEdges(Graph, number_of_edges, number_of_verticies);
    printf("4\n");

    isReachable(Graph, number_of_verticies, s1, s2);
    printf("5\n");
}