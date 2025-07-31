#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Folder {
    char Name[100];
    struct Folder* left;
    struct Folder* right;
} Folder;

Folder* createFolder(char* name){
    Folder* newFolder = (Folder*) malloc(sizeof(Folder));
    strcpy(newFolder->Name, name);
    newFolder->left = NULL;
    newFolder->right = NULL;
    return newFolder;
}

Folder* insert(Folder* root, char* name){
    if (root == NULL) {
        printf("Da them thu muc vao cay.\n");
        return createFolder(name);
    }
    if (strcmp(root->Name, name) == 0) {
        printf("Thu muc '%s' da ton tai!\n", name);
    } else if (strcmp(name, root->Name) < 0) {
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
    printf("\n");
}

int countHeight(Folder* root){
    if (root == NULL) return 0;
    int leftHeight = countHeight(root->left);
    int rightHeight = countHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

Folder* search(Folder* root, char* name){
    if (root == NULL) return NULL;
    if (strcmp(root->Name, name) == 0) return root;
    if (strcmp(name, root->Name) < 0)
        return search(root->left, name);
    else
        return search(root->right, name);
}

int printPath(Folder* root, char* target){
    if (root == NULL) return 0;

    if (strcmp(root->Name, target) == 0) {
        printf("%s", root->Name);
        return 1;
    }

    if (printPath(root->left, target) || printPath(root->right, target)) {
        printf(" <- %s", root->Name);
        return 1;
    }

    return 0;
}

void freeTree(Folder* root){
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void showMenu(){
    printf("\n=== FOLDER MANAGER ===\n");
    printf("1. Tao thu muc goc\n");
    printf("2. Them thu muc con\n");
    printf("3. In cau truc thu muc\n");
    printf("4. Tim kiem thu muc theo ten\n");
    printf("5. Tinh chieu cao he thong thu muc\n");
    printf("6. In duong dan tu goc den thu muc con\n");
    printf("7. Thoat\n");
}

int main(){
    int choice;
    char name[100];
    Folder* root = NULL;

    do {
        showMenu();
        printf("\nNhap lua chon: ");
        scanf("%d", &choice);
        getchar(); // xoa dau enter sau scanf

        switch (choice) {
            case 1:
                if (root != NULL) {
                    printf("Thu muc goc da ton tai!\n");
                    break;
                }
                printf("Nhap ten thu muc goc: ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0';
                root = insert(NULL, name);
                break;

            case 2:
                if (root == NULL) {
                    printf("Ban can tao thu muc goc truoc!\n");
                    break;
                }
                printf("Nhap ten thu muc con muon them: ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0';
                root = insert(root, name);
                break;

            case 3:
                printf("Cau truc thu muc (duyet theo level):\n");
                levelOrder(root);
                break;

            case 4:
                printf("Nhap ten thu muc can tim: ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0';
                if (search(root, name)) {
                    printf("Tim thay thu muc '%s'.\n", name);
                } else {
                    printf("Khong tim thay thu muc '%s'.\n", name);
                }
                break;

            case 5:
                printf("Chieu cao cua he thong thu muc: %d\n", countHeight(root));
                break;

            case 6:
                printf("Nhap ten thu muc dich: ");
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0';
                printf("Duong dan: ");
                if (!printPath(root, name)) {
                    printf("Khong tim thay thu muc '%s'.", name);
                }
                printf("\n");
                break;

            case 7:
                freeTree(root);
                printf("Da thoat chuong trinh.\n");
                break;

            default:
                printf("Lua chon khong hop le!\n");
                break;
        }
    } while (choice != 7);

    return 0;
}
