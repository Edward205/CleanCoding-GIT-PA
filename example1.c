/* Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} NODE;
/// pentru simplitate, folosim int uri pt a numi restaurantele/locatiile
/// ex: 1 - restaurantul 1 si tot asa

typedef struct Graph {
  int verticies;
  int *visited;
  struct Node **adjacency_list;
} GPH;

typedef struct Stack {
  int top;
  int capacity;
  int *arr;
} STK;

NODE *createNode(int verticies) {
  NODE *new_node = malloc(sizeof(NODE));
  new_node->data = verticies;
  new_node->next = NULL;
  return new_node;
}

void addEdge(GPH *Graph, int src, int dest) {
  NODE *new_node = createNode(dest);
  new_node->next = Graph->adjacency_list[src];
  Graph->adjacency_list[src] = new_node;
}

GPH *createGraph(int verticies) {
  GPH *Graph = malloc(sizeof(GPH));
  Graph->verticies = verticies;
  Graph->adjacency_list = malloc(verticies * sizeof(NODE *));
  Graph->visited = malloc(sizeof(int) * verticies);

  for (int i = 0; i < verticies; i++) {
    Graph->adjacency_list[i] = NULL;
    Graph->visited[i] = 0;
  }
  return Graph;
}

STK *createStack(int capacity) {
  STK *Stack = malloc(sizeof(STK));
  Stack->arr = malloc(capacity * sizeof(int));
  Stack->top = -1;
  Stack->capacity = capacity;

  return Stack;
}

void push(int pushed, STK *Stack) {
  if (Stack->top + 1 < Stack->capacity) {
    Stack->top = Stack->top + 1;
    Stack->arr[Stack->top] = pushed;
  }
}

void DFS(GPH *Graph, STK *Stack, int v_nr) {
  NODE *adj_list = Graph->adjacency_list[v_nr];
  NODE *aux = adj_list;
  Graph->visited[v_nr] = 1;
  printf("%d ", v_nr);
  push(v_nr, Stack);
  while (aux != NULL) {
    int con_ver = aux->data;
    if (Graph->visited[con_ver] == 0)
      DFS(Graph, Stack, con_ver);
    aux = aux->next;
  }
}

void insertEdges(GPH *Graph, int number_of_edges, int number_of_verticies) {
  int src, dest, i;
  printf("adauga %d munchii (de la 1 la %d)\n", number_of_edges,
         number_of_verticies);
  for (i = 0; i < number_of_edges; i++) {
    scanf("%d%d", &src, &dest);
    printf("addEdge\n");
    addEdge(Graph, src - 1, dest - 1);
  }
}

void wipe(GPH *Graph, int number_of_verticies) {
  for (int i = 0; i < number_of_verticies; i++) {
    Graph->visited[i] = 0;
  }
}

void isReachable(GPH *Graph, int number_of_verticies, STK *s1,
                 STK *s2) // 0 sau 1 daca poate fi sau nu ajuns
{
  printf("isReachable\n");
  int canbe = 0;

  for (int i = 0; i < number_of_verticies;
       i++) // aici i tine loc de numar adica de restaurant
  {
    DFS(Graph, s1, i);
    wipe(Graph, number_of_verticies);

    for (int j = 0; j < number_of_verticies; j++) {
      DFS(Graph, s2, j);

      for (int k = 0; k <= s1->top && !canbe; k++) {
        for (int l = 0; l <= s2->top && !canbe; l++) {
          if ((s1->arr[k] == j) && (s2->arr[l] == i))
            canbe = 1;
        }
      }
      wipe(Graph, number_of_verticies);
      s2->top = -1;
    }
    s1->top = -1;
  }

  if (canbe)
    printf("can be reached\n");
  else
    printf("cannot be reached\n");
}

int main() {
  int number_of_verticies;
  int number_of_edges;

  printf("cate noduri are graful?");
  scanf("%d", &number_of_verticies);

  printf("cate muchii are graful?");
  scanf("%d", &number_of_edges);

  GPH *Graph = createGraph(number_of_verticies);

  STK *s1 = createStack(2 * number_of_verticies);
  STK *s2 = createStack(2 * number_of_verticies);

  insertEdges(Graph, number_of_edges, number_of_verticies);

  isReachable(Graph, number_of_verticies, s1, s2);
}
