#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Ð?nh nghia c?u trúc d? li?u cho m?t tam giác
typedef struct {
    float canh1, canh2, canh3;
    float chu_vi;
    float dien_tich;
} TamGiac;

// Ð?nh nghia c?u trúc cho m?t node trong cây nh? phân tìm ki?m (theo di?n tích)
typedef struct Node {
    TamGiac data;
    struct Node *left;
    struct Node *right;
} Node;

// Kh?i t?o các c?u trúc d? li?u: list, stack, queue
#define MAX_SIZE 100
TamGiac listTamGiac[MAX_SIZE];
int top = -1;
int front = -1, rear = -1;
Node *root = NULL;

// Hàm ki?m tra xem 3 c?nh có t?o thành tam giác không
int laTamGiac(float a, float b, float c) {
    if (a <= 0 || b <= 0 || c <= 0) return 0; // Các c?nh ph?i duong
    if (a + b > c && a + c > b && b + c > a) return 1; // Ði?u ki?n hình thành tam giác
    return 0;
}

// Hàm tính di?n tích c?a tam giác b?ng công th?c Heron
float tinhDienTich(float a, float b, float c) {
    float p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

// Hàm tính chu vi c?a tam giác
float tinhChuVi(float a, float b, float c) {
    return a + b + c;
}

// Hàm thêm m?t tam giác vào stack
void push(TamGiac tg) {
    if (top == MAX_SIZE - 1) {
        printf("Stack overflow\n");
        return;
    }
    listTamGiac[++top] = tg;
}

// Hàm l?y m?t tam giác ra kh?i stack
TamGiac pop() {
    if (top == -1) {
        printf("Stack underflow\n");
        exit(1);
    }
    return listTamGiac[top--];
}

// Hàm thêm m?t tam giác vào queue
void enqueue(TamGiac tg) {
    if (rear == MAX_SIZE - 1) {
        printf("Queue overflow\n");
        return;
    }
    if (front == -1) front = 0;
    listTamGiac[++rear] = tg;
}

// Hàm l?y m?t tam giác ra kh?i queue
TamGiac dequeue() {
    if (front == -1 || front > rear) {
        printf("Queue underflow\n");
        exit(1);
    }
    return listTamGiac[front++];
}

// Hàm thêm m?t tam giác vào cây nh? phân tìm ki?m theo di?n tích
Node* insertByArea(Node* root, TamGiac tg) {
    if (root == NULL) {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = tg;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (tg.dien_tich < root->data.dien_tich)
        root->left = insertByArea(root->left, tg);
    else
        root->right = insertByArea(root->right, tg);

    return root;
}

// Hàm duy?t và in ra các tam giác theo th? t? tang d?n di?n tích (inorder traversal)
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("Tam giac co cac canh %.2f, %.2f, %.2f | Chu vi: %.2f | Dien tich: %.2f\n",
               root->data.canh1, root->data.canh2, root->data.canh3,
               root->data.chu_vi, root->data.dien_tich);
        inorder(root->right);
    }
}

int main() {
    int choice;
    float a, b, c;
    TamGiac tamGiac;

    do {
        printf("\nMenu:\n");
        printf("1. Nhap tam giac\n");
        printf("2. In danh sach tam giac tu List\n");
        printf("3. In danh sach tam giac tu Stack\n");
        printf("4. In danh sach tam giac tu Queue\n");
        printf("5. In danh sach tam giac tu Cay nhi phan theo dien tich\n");
        printf("0. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Yeu cau nhap 3 canh tam giac
                printf("Nhap 3 canh cua tam giac (cach nhau boi dau cach): ");
                scanf("%f %f %f", &a, &b, &c);

                // Kiem tra tam giac va tinh chu vi, dien tich neu hop le
                if (laTamGiac(a, b, c)) {
                    tamGiac.canh1 = a;
                    tamGiac.canh2 = b;
                    tamGiac.canh3 = c;
                    tamGiac.chu_vi = tinhChuVi(a, b, c);
                    tamGiac.dien_tich = tinhDienTich(a, b, c);

                    // Them tam giac vao List
                    listTamGiac[++top] = tamGiac;

                    // Them tam giac vao Stack
                    push(tamGiac);

                    // Them tam giac vao Queue
                    enqueue(tamGiac);

                    // Them tam giac vao Cay nhi phan theo dien tich
                    root = insertByArea(root, tamGiac);

                    printf("Da them tam giac vao cac cau truc du lieu thanh cong.\n");
                } else {
                    printf("Ba canh vua nhap khong tao thanh tam giac.\n");
                }
                break;

            case 2:
                // In danh sach tam giac tu List
                printf("Danh sach tam giac tu List:\n");
                for (int i = 0; i <= top; ++i) {
                    printf("Tam giac co cac canh %.2f, %.2f, %.2f | Chu vi: %.2f | Dien tich: %.2f\n",
                           listTamGiac[i].canh1, listTamGiac[i].canh2, listTamGiac[i].canh3,
                           listTamGiac[i].chu_vi, listTamGiac[i].dien_tich);
                }
                break;

            case 3:
                // In danh sach tam giac tu Stack
                printf("Danh sach tam giac tu Stack:\n");
                while (top != -1) {
                    TamGiac tg = pop();
                    printf("Tam giac co cac canh %.2f, %.2f, %.2f | Chu vi: %.2f | Dien tich: %.2f\n",
                           tg.canh1, tg.canh2, tg.canh3, tg.chu_vi, tg.dien_tich);
                }
                break;

            case 4:
                // In danh sach tam giac tu Queue
                printf("Danh sach tam giac tu Queue:\n");
                while (front <= rear) {
                    TamGiac tg = dequeue();
                    printf("Tam giac co cac canh %.2f, %.2f, %.2f | Chu vi: %.2f | Dien tich: %.2f\n",
                           tg.canh1, tg.canh2, tg.canh3, tg.chu_vi, tg.dien_tich);
                }
                break;

            case 5:
                // In danh sach tam giac tu Cay nhi phan theo dien tich
                printf("Danh sach tam giac tu Cay nhi phan theo dien tich (inorder traversal):\n");
                inorder(root);
                break;

            case 0:
                printf("Thoat chuong trinh.\n");
                break;

            default:
                printf("Lua chon khong hop le. Vui long nhap lai.\n");
        }
    } while (choice != 0);

    return 0;
}

