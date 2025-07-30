#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

#define MAX 5
typedef struct Operation
{
    char url[100];
    char timeStamp[30];
}Operation;
typedef struct Node
{
    Operation ope;
    struct Node *next;
}Node;
typedef struct NodeDouble
{
    Operation *ope;
    struct NodeDouble *next;
    struct NodeDouble *prev;
}NodeDouble;
typedef struct Stack
{
    Node *top;
}Stack;
typedef struct Queue
{
    Operation *Ope[MAX];
    int front, rear,count;
}Queue;
typedef struct HistoryList
{
    NodeDouble *head;
    NodeDouble *tail;
}HistoryList;
void renderMenu()
{
    printf("\n        MENU\n");
    printf("1. VISIT url\n");
    printf("2. BACKWARD\n");
    printf("3. FORWARD\n");
    printf("4.CURRENT\n");
    printf("5. RECENT\n");
    printf("6. HISTORY\n");
    printf("7. CLEAR HISTORY\n");
    printf("8.EXIT\n");
    printf("lua chon cua ban: ");
}
void initQueue(Queue *q)
{
    q->front = q->rear =q->count= 0;

}
void getTime(char *timeStamp)
{
    time_t now=time(NULL);
    strftime(timeStamp, 30,"%Y-%m-%d %H:%M:%S", localtime(&now));
}
int isEmpty(Stack* s)
{
    return s->top == NULL;
}
Operation createOperation(char *url)
{
    Operation operation;
    strcpy(operation.url, url);
    getTime(operation.timeStamp);
    return operation;
}
void push(Stack* s, Operation *op) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->ope = *op;
    temp->next = s->top;
    s->top = temp;
}
Operation pop(Stack* s) {
    Operation op = {"", ""};
    if (!isEmpty(s)) {
        Node* temp = s->top;
        op = temp->ope;
        s->top = temp->next;
        free(temp);
    }
    return op;
}
void clearStack(Stack *s)
{
    while (s->top != NULL) pop(s);
}
void insertHistory(HistoryList *history, Operation *ope)
{
    NodeDouble *newNode = (NodeDouble *)malloc(sizeof(NodeDouble));
    newNode->ope = ope;
    newNode->next = NULL;
    newNode->prev = history->tail;
    if (history->tail) history->tail->next = newNode;
    else history->head = newNode;
    history->tail = newNode;
}
void enqueueRecent(Queue* q, Operation *op) {
    if (q->count == MAX) {
        q->front = (q->front + 1) % MAX;
        q->count--;
    }
    Operation* newOp = (Operation*)malloc(sizeof(Operation));
    if (newOp == NULL) return;
    *newOp = *op;
    q->Ope[q->rear] = newOp;
    q->rear = (q->rear + 1) % MAX;
    q->count++;
}
void printRecent(Queue* q) {
    if (q->count==0){
        printf("khong co trang nao gan day dc tim kiem\n");
        return;
    }
    printf("Cac trang dc tim kiem gan day\n");
    int i, idx = q->front;
    for (i = 0; i < q->count; i++) {
        printf("%s | %s\n", q->Ope[idx]->url, q->Ope[idx]->timeStamp);
        idx = (idx + 1) % MAX;
    }
}
void printHistory(HistoryList* list)
{
    if (list->head == NULL)
    {
        printf("lich su trong\n");
        return;
    }
    NodeDouble* temp = list->head;
    while (temp != NULL)
    {
        printf("%s | %s\n", temp->ope->url, temp->ope->timeStamp);
        temp = temp->next;
    }
}
void clearHistory(HistoryList* list) {
    NodeDouble* temp = list->head;
    while (temp) {
        NodeDouble* next = temp->next;
        free(temp);
        temp = next;
    }
    list->head = list->tail = NULL;
    printf("xoa lich su thanh cong\n");
}
int main()
{
    Stack back = {NULL}, forward = {NULL};
    HistoryList history = {NULL, NULL};
    Queue recent;
    initQueue(&recent);
    Operation current = {"", ""};
    char url[100];
    int choice;
    do
    {
        renderMenu();
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("url: ");
                scanf("%s",url);
                if (strlen(current.url)) push(&back,&current);
                current = createOperation(url);
                Operation* newOp = malloc(sizeof(Operation));
                *newOp = current;
                clearStack(&forward);
                enqueueRecent(&recent,newOp);
                insertHistory(&history,newOp);
                printf("Da truy cap: %s\n", url);
                break;
            case 2:
            if (isEmpty(&back)) {
                printf("Khong the quay lai\n");
            } else {
                push(&forward, &current);
                current = pop(&back);
                enqueueRecent(&recent, &current);
                printf("Da quay lai: %s\n", current.url);
            }
                break;
            case 3:
            if (isEmpty(&forward)) {
                printf("Khong the quay lai\n");
            } else {
                push(&back, &current);
                current = pop(&forward);
                enqueueRecent(&recent, &current);
                printf("Da quay lai: %s\n", current.url);
            }
                break;
            case 4:
                printf("Trang hien tai: %s\n", current.url);
                break;
            case 5:
                printRecent(&recent);
                break;
            case 6:
                printHistory(&history);
                break;
            case 7:
                clearHistory(&history);
                break;
            case 8:
                printf(":da thoat truong trinh thanh cong!\n");
                break;
            default:
                printf("lua chon khong hop le!\n");
        }
    }
    while (choice!=8);
    return 0;
}