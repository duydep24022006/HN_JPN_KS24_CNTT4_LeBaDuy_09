#include <stdio.h>
#include <stdlib.h>

// Khởi tạo cấu trúc của một Node
typedef struct Node {
    int data; // Dữ liệu của mỗi Node
    struct Node* left; // Con trỏ bên trái
    struct Node* right; // Con trỏ bên phải
} Node;

// Hàm khởi tạo một Node
Node* createNode(int value){
    // Cấp phát bộ nhớ
    Node* newNode = (Node*) malloc(sizeof (Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Thao tác thêm phần tử trong cây
Node* insert(Node* root, int value){
    // Kiểm tra xem trong cây đã có phần tử chưa
    if (root == NULL) {
        // Nếu như chưa có phần tử nào thì sẽ thêm vào ầu
        printf("Da them phan tu vao dau cay\n");
        return createNode(value);
    }
    if (root->data == value){
        printf("Phan tu co gia %d da ton tai trong cay!", value);
    } else if (root->data > value){
        // Thêm vào bên trái
        root->left = insert(root->left, value);
    } else {
        // Thêm vào bên phải
        root->right = insert(root->right, value);
    }
    // Trả về root vừa tạo ra
    return root;
}

// Hàm xóa 1 phần tử trong cây
Node* delete(Node* root, int value){
    if (root == NULL){
        printf("Cay rong! Khong the xoa\n");
        return NULL;
    }
    if (value < root->data){
        root->left = delete(root->left, value);
    } else if (value > root->data){
        root->right = delete(root->right, value);
    } else {
        // Nếu tìm  thấy phần tử cần xóa
        // Nếu như trong cây chỉ có 1 nút
        if (root->left == NULL && root->right == NULL){
            free(root);
            printf("Da xoa phan tu %d khoi cay\n", value);
        } else if (root->left == NULL){
            Node* temp = root->right;
            free(root);

            printf("Da xoa phan tu %d khoi cay\n", value);
            return temp;
        } else if (root->right == NULL){
            Node* temp = root->left;
            free(root);

            printf("Da xoa phan tu %d khoi cay\n", value);
            return temp;
        } else {
            Node* successor = root->right;
            while (successor->left != NULL) {
                successor = successor->left;
            }
            // Gán giá trị successor cho node hiện tại
            root->data = successor->data;
            // Xóa node successor
            root->right = delete(root->right, successor->data);
        }
    }
}

// Hàm duyệt cây (Sử dụng 4 cách)

// Duyệt bằng preorder (N - L - R)
void levelOrder(Node* root) {
    if (root == NULL) return;
    Node* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        Node* current = queue[front++];
        printf("%d ", current->data);
        if (current->left != NULL) queue[rear++] = current->left;
        if (current->right != NULL) queue[rear++] = current->right;
    }
}

// Duyệt bằng inorder (L - N - R)
void inorder(Node* root){
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

// Duyệt bằng postorder (L - R - N)
void postorder(Node* root){
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

// Đếm lá của cây - (Lá: là các node mà không có node con)
int countLeaves(Node* root){
    if (root == NULL) {
        return 0;
    }

    // Nếu như chỉ có 1 nút chính
    if (root->left == NULL && root->right == NULL){
        return 1;
    }

    // Nếu như cây có nhiều lá
    return countLeaves(root->left) + countLeaves(root->right);
}

// Hàm tính chiều cao của cây
int countHeight(Node* root){
    if (root == NULL) {
        return 0;
    }

    // Tính chiều cao của các node bên tay trái
    int leftHeight = countHeight(root->left);

    // Tính chiều cao của các node bên tay phải
    int rightHeight = countHeight(root->right);

    if (leftHeight > rightHeight){
        return leftHeight + 1;
    } else {
        return rightHeight + 1;
    }
}

// Hàm giải phóng bộ nhớ
void freeTree(Node* root){
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Hàm hiển thij menu các chức năng
void showMenu(){
    printf("\n=== BINARY SEARCH TREE MANAGER ===\n");
    printf("1. INSERT\n");
    printf("2. DELETE \n");
    printf("3. TRAVERSE\n");
    printf("4. COUNT LEAVES\n");
    printf("5. COUNT HEIGHT\n");
    printf("6. EXIT\n");
}

int main(){
    int choice, value;
    Node* root = NULL;
    do {
        showMenu(); // Gọi hàm để hiển thị menu
        printf("\n");
        printf("Vui long nhap lua chon: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhap gia tri cho Node: ");
                scanf("%d", &value);
                root =  insert(root, value);
                break;
            case 2:
                printf("Nhap gia tri can xoa: ");
                scanf("%d", &value);
                delete(root,value);
                break;
            case 3:
                printf("Duyet cay theo Inorder: ");
                inorder(root);
                printf("\n");

                printf("Duyet cay theo Postorder: ");
                postorder(root);
                printf("\n");

                printf("Duyet cay theo levelOrder: ");
                levelOrder(root);
                printf("\n");
                break;
            case 4:
                printf("Tong so la co trong cay la: %d\n", countLeaves(root));
                break;
            case 5:
                printf("Chieu cao cua cay la: %d\n", countHeight(root));
                break;
            case 6:
                freeTree(root);
                printf("Thoat chuong trinh\n");
                break;
            default:
                printf("Lua chon khong hop le\n");
                break;
        }
    } while (choice != 6);
    return 0;
}