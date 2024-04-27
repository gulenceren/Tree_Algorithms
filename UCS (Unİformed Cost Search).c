#include <stdio.h>
#include <stdlib.h>

#define NODE_NUMBER 20
#define Arad            0
#define Zerind          1
#define Sibiu           2
#define Timisoare       3
#define Oradea          4
#define Fagaras         5
#define RimnicuVilcea   6
#define Lugej           7
#define Bucharest       8
#define Pitesti         9
#define Craiova         10
#define Mehadia         11
#define Dobreta         12
#define Giurglu         13
#define Urziceni        14
#define Vaslui          15
#define Hirsova         16
#define Lasi            17
#define Neamt           18
#define Eforie          19

typedef struct node
{
    int action;
	struct node* parent;
    int durum;
    int path_cost;
}node;

typedef struct Queue {
    int front;
    int rear;
    int numberOfElements;
    int capacity;
    node* array[NODE_NUMBER];
}Queue;

int graf[NODE_NUMBER][NODE_NUMBER] = {};
int cost[NODE_NUMBER][NODE_NUMBER] = {};/*Maliyet bilgilerini tutar*/
char* NodeName[]={"Arad","Zerind","Sibiu","Timisoare","Oradea","Fagaras","RimnicuVilcea","Lugej","Bucharest","Pitesti","Craiova","Mehadia","Dobreta","Giurglu","Urziceni","Vaslui","Hirsova","Lasi","Neamt","Eforie"};
void AddEdge(int v1,int v2,int wgth);

void ShowMatris();
void UCS(int start,int end);

Queue* createQueue(int size);
int isFull(Queue* queue);
int isEmpty(Queue* queue);
void enqueue(Queue* queue, node* item);
node* dequeue(Queue* queue);

void PrintSolution(node* n);
node* CreateNewNode(int a, node* p, int d,int path_cost);

int main()
{
    AddEdge(Arad, Zerind, 75);
    AddEdge(Arad, Sibiu, 140);
    AddEdge(Arad, Timisoare, 118);
    AddEdge(Zerind, Oradea, 71);
    AddEdge(Sibiu, Fagaras, 90);
    AddEdge(Sibiu, RimnicuVilcea, 80);
    AddEdge(Timisoare, Lugej, 111);
    AddEdge(Oradea, Sibiu, 151);
    AddEdge(Fagaras, Bucharest, 211);
    AddEdge(RimnicuVilcea, Pitesti, 97);
    AddEdge(RimnicuVilcea, Craiova, 146);
    AddEdge(Lugej, Mehadia, 70);
    AddEdge(Bucharest, Giurglu, 90);
    AddEdge(Bucharest, Urziceni, 85);
    AddEdge(Pitesti, Bucharest, 101);
    AddEdge(Craiova, Pitesti, 138);
    AddEdge(Mehadia, Dobreta, 75);
    AddEdge(Dobreta, Craiova, 120);
    AddEdge(Urziceni, Vaslui, 142);
    AddEdge(Urziceni, Hirsova, 98);
    AddEdge(Hirsova, Eforie, 86);
    AddEdge(Vaslui, Lasi, 92);
    AddEdge(Lasi, Neamt, 97);
    ShowMatris();
    UCS(Arad,Craiova);
    return 0;
}

void AddEdge(int v1,int v2,int wgth)
{
    graf[v1][v2] = 1;
    graf[v2][v1] = 1;
    cost[v1][v2] = wgth;/*Baðlantý maliyeti*/
    cost[v2][v1] = wgth;
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

void UCS(int start,int end)
{
    int nodeNum = 0;
    node* n;
    int i;
    node* newNode;
    int visited[NODE_NUMBER] = {};
    Queue* myQueue = createQueue(NODE_NUMBER);
    node* root = CreateNewNode(0,NULL,start,0);
    nodeNum++;
    enqueue(myQueue,root);
    visited[start] = 1;
    while(!isEmpty(myQueue))
    {
        n = dequeue(myQueue);
        for(int x = 0; x < NODE_NUMBER; x++)/*Düðüm isim karþýlýklarýný getirir*/
        {
            if (n-> durum == x)
            {
                printf("Dugum  %s  Ziyaret Edildi.\n",NodeName[x]);
            }
        }
        if(n->durum == end) /*Hedef testi */
        {
            PrintSolution(n);
            printf("\nOlusturulan Dugum Sayisi: %d\n",nodeNum);
            return;
        }
        for(i = 0; i < NODE_NUMBER; i++)
        {
            if(graf[n->durum][i] == 1 && !visited[i])
            {
                newNode = CreateNewNode(0,n,i,n->path_cost+cost[n->durum][i]);/*n->path_cost+cost[n->durum][i] => Maliyet bilgilerini topluyor*/
                nodeNum++;
                enqueue(myQueue,newNode);
                visited[i] = 1;
            }
        }
    }
}

node* CreateNewNode(int a, node* p, int d,int path_cost)
{
    node* newNode = malloc(sizeof(node));
    newNode->action = a;
    newNode->parent = p;
    newNode->durum = d;
    newNode->path_cost = path_cost;
    return newNode;
}

void PrintSolution(node* n)
{
    printf("Yol maliyeti: %d\n",n->path_cost);
    printf("Yol: ");
    while(n != NULL)
    {
        for(int x = 0; x < NODE_NUMBER; x++)/*Düðüm isim karþýlýklarýný getirir*/
        {
            if (n-> durum == x)
            {
                printf("%s ",NodeName[x]);
            }
        }
        n = n->parent;
    }

}

struct Queue* createQueue(int size)
{
    Queue* queue = (Queue*)malloc(sizeof(struct Queue));
    queue->capacity = size;
    queue->front = 0;
    queue->numberOfElements = 0;
    queue->rear = 0;
    //queue->array = (node*)malloc(queue->capacity * sizeof(node));
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

void enqueue(Queue* queue, node* item)
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

node* dequeue(Queue* queue)
{
    if (isEmpty(queue))
    {
        printf("Sira bos! Program sonlandiriliyor!\n");
        exit(-1);
    }
    node* item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->numberOfElements = queue->numberOfElements - 1;
    return item;
}
