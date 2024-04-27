#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define NODE_NUMBER 10

typedef struct Queue {
    int front;
    int rear;
    int numberOfElements;
    int capacity;
    int* array;
}Queue;

int graf[NODE_NUMBER][NODE_NUMBER] = {};
void AddEdge(int v1,int v2);
void ShowMatris();
void BFS(int start);

Queue* createQueue(int size);
int isFull(Queue* queue);
int isEmpty(Queue* queue);
void enqueue(Queue* queue, int item);
int dequeue(Queue* queue);

int main()
{
    /*AddEdge(0,1);
    AddEdge(0,4);
    AddEdge(1,4);
    AddEdge(1,3);
    AddEdge(3,4);
    AddEdge(1,2);
    AddEdge(2,3);
    ShowMatris();
    BFS(0);*/
    AddEdge(0,1);
    AddEdge(0,2);
    AddEdge(0,3);
    AddEdge(1,4);
    AddEdge(2,5);
    AddEdge(2,6);
    AddEdge(3,7);
    AddEdge(4,8);
    AddEdge(5,9);
    ShowMatris();
    BFS(5);
    return 0;
}

void AddEdge(int v1,int v2)
{
    graf[v1][v2] = 1;
    graf[v2][v1] = 1;
}

void ShowMatris()
{
    int i,j;
    for(i = 0; i < NODE_NUMBER; i++)
    {
        for(j = 0; j < NODE_NUMBER; j++)
        {
            printf("%d ",graf[i][j]);
        }
        printf("\n");
    }
}

void BFS(int start)
{
    int n;
    int i;
    int visited[NODE_NUMBER] = {};
    Queue* myQueue = createQueue(NODE_NUMBER);
    enqueue(myQueue,start);
    visited[start] = 1;
    while(!isEmpty(myQueue))
    {
        n = dequeue(myQueue);
        printf("Node %d is visited.\n",n);
        for(i = 0; i < NODE_NUMBER; i++)
        {
            if(graf[n][i] == 1 && !visited[i])
            {
                enqueue(myQueue,i);
                visited[i] = 1;
            }
        }
    }
}

struct Queue* createQueue(int size)
{
    Queue* queue = (Queue*)malloc(sizeof(struct Queue));
    queue->capacity = size;
    queue->front = 0;
    queue->numberOfElements = 0;
    queue->rear = 0;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

int isFull(Queue* queue)
{
    return (queue->numberOfElements == queue->capacity);
}

int isEmpty(Queue* queue)
{
    return (queue->numberOfElements == 0);
}

void enqueue(Queue* queue, int item)
{
    if (isFull(queue))
    {
        printf("Ekleme yapilamaz, sira dolu!\n");
        return;
    }
    queue->array[queue->rear] = item;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->numberOfElements = queue->numberOfElements + 1;
}

int dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
    {
        printf("Sira bos! Program sonlandiriliyor!\n");
        exit(-1);
    }
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->numberOfElements = queue->numberOfElements - 1;
    return item;
}
