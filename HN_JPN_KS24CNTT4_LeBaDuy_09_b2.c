#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Folder {
    char* Name[100];
    struct Folder* left;
    struct Folder* right;
} Folder;

Folder* createFolder(char* name){
    Folder* newFolder = (Folder*) malloc(sizeof (Folder));
    strcpy(newFolder->Name,name);
    newFolder->left = NULL;
    newFolder->right = NULL;
    return newFolder;
}

Folder* insert(Folder* root, char* name){
    if (root == NULL) {
        printf("Da them phan tu vao dau cay\n");
        return createFolder(name);
    }
    if (strcmp(root->Name,name)==0 ){
        printf("Phan tu co gia %s da ton tai trong cay!", name);
    } else if (strcmp(root->Name,name)>0){

        root->left = insert(root->left, name);
    } else {

        root->right = insert(root->right, name);
    }
    return root;
}

void levelOrder(Folder* root) {
    if (root == NULL) return;
    Folder* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        Folder* current = queue[front++];
        printf("%s ", current->Name);
        if (current->left != NULL) queue[rear++] = current->left;
        if (current->right != NULL) queue[rear++] = current->right;
    }
}



int countHeight(Folder* root){
    if (root == NULL) {
        return 0;
    }
    int leftHeight = countHeight(root->left);

    int rightHeight = countHeight(root->right);

    if (leftHeight > rightHeight){
        return leftHeight + 1;
    } else {
        return rightHeight + 1;
    }
}

void freeTree(Folder* root){
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void showMenu(){
    printf("\n===  FOLDER MANAGER ===\n");
    printf("1.Tao thu muc goc \n");
    printf("2. Them thu muc con \n");
    printf("3. In cau truc thu muc \n");
    printf("4. Tim kiem thu muc theo ten\n");
    printf("5. Tinh chieu dai he thong thu muc\n");
    printf("6. In duong dan tu thu muc goc toi thu muc con\n");
    printf("7. Thoat\n");
}

int main(){
    int choice;
    char name[100];
    Folder* root = NULL;
    do {
        showMenu();
        printf("\n");
        printf("Vui long nhap lua chon: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                getchar();
                printf("moi ban nhap ten thu muc goc: ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0';
                insert(root, name);
                printf("%s , %s\n",name,root);
                break;
            case 2:
                printf("ten thu muc con\n");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0';
                break;
            case 3:
                printf("Duyet cay theo levelOrder: ");
                levelOrder(root);
                printf("\n");
                break;
            case 4:

                break;
            case 5:
                printf("Chieu cao cua cay la: %d\n", countHeight(root));
                break;
            case 6:
                break;
            case 7:
                freeTree(root);
                printf("Thoat chuong trinh\n");
                break;
            default:
                printf("Lua chon khong hop le\n");
                break;
        }
    } while (choice != 7);
    return 0;
}