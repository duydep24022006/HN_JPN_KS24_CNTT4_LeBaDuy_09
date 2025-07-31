#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 100
typedef struct Employee
{
    int Id;
    char Name[MAX_LEN];
    int Age;
    char Hometown[MAX_LEN];
    char Division[MAX_LEN];
    char Phone[20];
}Employee;

typedef struct Node
{
    Employee data;
    struct Node* next;
}Node;
typedef struct DoubleNode
{
    Employee data;
    struct DoubleNode* next;
    struct DoubleNode* prev;
}DoubleNode;

Node* createNode(Employee data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
DoubleNode* createDoubleNode(Employee data)
{
    DoubleNode* newNode = (DoubleNode*)malloc(sizeof(DoubleNode));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}
void insertNode(Node** head,Employee* data)
{
    if (*head == NULL)
    {
        *head = createNode(*data);
        (*head)->next = NULL;
    }else
    {
        Node* temp = *head;
        Node* prev= NULL;
        while (temp != NULL)
        {
            if (temp->data.Id == data->Id)
            {
                printf("Id da ton tai\n");
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        Node* newNode = createNode(*data);
        prev->next = newNode;
        newNode->next = NULL;
    }
    printf("them nhan vien moi thanh cong\n");
}
void render(Node* head)
{
    if (head == NULL)
    {
        printf("khong co nhan vien trong danh sach\n");
        return;
    }
    Node* temp = head;
    int count = 0;
    while (temp != NULL)
    {
        printf("nha vien thu: %d\n",++count);
        printf("Id: %d\n",temp->data.Id);
        printf("Name: %s\n",temp->data.Name);
        printf("Age: %d\n",temp->data.Age);
        printf("Hometown: %s\n",temp->data.Hometown);
        printf("Division: %s\n",temp->data.Division);
        printf("Phone: %s\n",temp->data.Phone);
        printf("\n");
        temp = temp->next;
    }
}
void deleteNode(Node** head,int Id)
{
    if (*head == NULL)
    {
        printf("khong co nhan vien trong danh sach\n");
        return;
    }
    Node* temp = *head;
    Node* prev = NULL;
    while (temp != NULL)
    {
        if (temp->data.Id == Id)
        {
            if (prev == NULL)
            {
                *head=NULL;
                free(temp);
            }else
            {
                prev->next = temp->next;
                free(temp);
            }
            printf("xoa nhan vien thanh cong!\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("xoa nhan vien thanh cong!\n");
}
void editEmployee(Node** head,int Id)
{
    if ((*head) == NULL)
    {
        printf("khong co nhan vien trong danh sach\n");
        return;
    }
    Node* temp = *head;
    Node* prev = NULL;
    while (temp != NULL)
    {
        if (temp->data.Id == Id)
        {
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("khong tim thay nhan vien nhan vien thanh cong!\n");
        return;
    }
    printf("moi ban cap nhat thong tin\n");
    getchar();
    printf("Name: ");
    fgets(temp->data.Name,MAX_LEN,stdin);
    temp->data.Name[strcspn(temp->data.Name,"\n")] = '\0';
    printf("Age: ");
    scanf("%d",&temp->data.Age);
    getchar();
    printf("Hometown: ");
    fgets(temp->data.Hometown,MAX_LEN,stdin);
    temp->data.Hometown[strcspn(temp->data.Hometown,"\n")] = '\0';
    printf("Division: ");
    fgets(temp->data.Division,MAX_LEN,stdin);
    temp->data.Division[strcspn(temp->data.Division,"\n")] = '\0';
    printf("Phone: ");
    fgets(temp->data.Phone,MAX_LEN,stdin);
    temp->data.Phone[strcspn(temp->data.Phone,"\n")] = '\0';
    printf("cap nhat nhan vien thanh cong!\n");

}
void bubbleSort(Node *head)
{
    if (head == NULL||head->next == NULL)
    {
        return;
    }
    int swapped;
    Node *ptr;
    Employee tempStack;
    do
    {
        swapped = 0;
        ptr = head;
        while (ptr->next != NULL)
        {
            if (strcmp(ptr->next->data.Division,ptr->data.Division)<0)
            {
                tempStack = ptr->data;
                ptr->data = ptr->next->data;
                ptr->next->data = tempStack;
                swapped = 1;
            }
            ptr = ptr->next;
        }
    }while (swapped);
    printf("Da xap xep thanh cong!\n");
}
void submitEmployee(Node** headSingly,DoubleNode** headDouble,char* name)
{
    if (headSingly == NULL )
    {
        printf("khong co nhan vien trong danh sach\n");
        return;
    }
    Node* temp = *headSingly;
    Node* prev = NULL;
    while (temp != NULL)
    {
        if (strcmp(temp->data.Name,name)==0)
        {
            DoubleNode* newNode = createDoubleNode(temp->data);
            if (*headDouble != NULL)
            {
                *headDouble=newNode;
                (*headDouble)->next=NULL;
            }else
            {
                DoubleNode* current = *headDouble;
                while (current != NULL)
                {
                    current = current->next;
                }
                current = newNode;
                newNode->next = NULL;
                newNode->prev = current;
            }
            printf("di chuyen nhan vien nghi viec thanh cong\n");
            deleteNode(headSingly,temp->data.Id);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("khong tim thay nhan vien\n");
}
void searchName(Node* head,char* name)
{
    if (head == NULL)
    {
        printf("khong co nhan vien trong danh sach\n");
        return;
    }
    Node* temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->data.Name,name)==0)
        {
            break;
        }
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("khong co tim thay nhan vien!\n");
        return;
    }
    printf("Id: %d\n",temp->data.Id);
    printf("Name: %s\n",temp->data.Name);
    printf("Age: %d\n",temp->data.Age);
    printf("Hometown: %s\n",temp->data.Hometown);
    printf("Division: %s\n",temp->data.Division);
    printf("Phone: %s\n",temp->data.Phone);
}
void renderMenu()
{
    printf("\n-----------EMPLOYEE MANAGER---------\n");
    printf("1. Them nhan vien\n");
    printf("2. Hien thi danh sach nhan vien\n");
    printf("3. Xoa nhan vien\n");
    printf("4. Cap nhat thong tin nhan vien\n");
    printf("5. Di chuyen nhan vien nghi viec\n");
    printf("6. Sap xep nhan vien\n");
    printf("7. Tim kiem nhan vien\n");
    printf("8. Thoat chuong trinh\n");
    printf("Lua chon cua ban: ");

}

int main()
{
    Node* headSingly = NULL;
    DoubleNode* headDouble = NULL;
    int choice,id;
    char name[100];
    do
    {
        renderMenu();
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                Employee* employee=malloc(sizeof(Employee));
                printf("Id: ");
                scanf("%d",&employee->Id);
                getchar();
                printf("Name: ");
                fgets(employee->Name,MAX_LEN,stdin);
                employee->Name[strcspn(employee->Name,"\n")] = '\0';
                printf("Age: ");
                scanf("%d",&employee->Age);
                getchar();
                printf("Hometown: ");
                fgets(employee->Hometown,MAX_LEN,stdin);
                employee->Hometown[strcspn(employee->Hometown,"\n")] = '\0';
                printf("Division: ");
                fgets(employee->Division,MAX_LEN,stdin);
                employee->Division[strcspn(employee->Division,"\n")] = '\0';
                printf("Phone: ");
                fgets(employee->Phone,MAX_LEN,stdin);
                employee->Phone[strcspn(employee->Phone,"\n")] = '\0';
                insertNode(&headSingly,employee);
                break;
            case 2:
                render(headSingly);
                break;
            case 3:
                printf("Id: ");
                scanf("%d",&id);
                deleteNode(&headSingly,id);
                break;
            case 4:
                printf("Id: ");
                scanf("%d",&id);
                editEmployee(&headSingly,id);
                break;
            case 5:
                getchar();
                printf("Name: ");
                fgets(name,MAX_LEN,stdin);
                name[strcspn(name,"\n")] = '\0';
                submitEmployee(&headSingly,&headDouble,name);
                break;
            case 6:
                bubbleSort(headSingly);
                break;
            case 7:
                getchar();
                printf("Name: ");
                fgets(name,MAX_LEN,stdin);
                name[strcspn(name,"\n")] = '\0';
                searchName( headSingly, name);
                break;
            case 8:
                printf("thoat truong trinh thanh cong!\n");
                break;
            default:
                printf("loi cu phap\n");
        }
    }
    while (choice!=8);
    return 0;
}