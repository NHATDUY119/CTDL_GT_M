#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �?nh nghia c?u tr�c SinhVien
struct SinhVien {
    int maSV;
    char tenSV[50];
    int tuoi;
    struct SinhVien* next;
};

// Khai b�o danh s�ch li�n k?t don
struct SinhVien* head = NULL;

// H�m t?o n�t m?i
struct SinhVien* taoSinhVien(int maSV, char tenSV[], int tuoi) {
    struct SinhVien* sv = (struct SinhVien*)malloc(sizeof(struct SinhVien));
    sv->maSV = maSV;
    strcpy(sv->tenSV, tenSV);
    sv->tuoi = tuoi;
    sv->next = NULL;
    return sv;
}

// H�m th�m sinh vi�n v�o cu?i danh s�ch
void themSinhVien(int maSV, char tenSV[], int tuoi) {
    struct SinhVien* sv = taoSinhVien(maSV, tenSV, tuoi);
    if (head == NULL) {
        head = sv;
    } else {
        struct SinhVien* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = sv;
    }
    printf("Them sinh vien thanh cong.\n");
}

// H�m hi?n th? danh s�ch sinh vi�n
void hienThiDanhSach() {
    struct SinhVien* temp = head;
    printf("Danh sach sinh vien:\n");
    while (temp != NULL) {
        printf("Ma SV: %d - Ten SV: %s - Tuoi: %d\n", temp->maSV, temp->tenSV, temp->tuoi);
        temp = temp->next;
    }
}

// H�m x�a sinh vi�n kh?i danh s�ch
void xoaSinhVien(int maSV) {
    struct SinhVien *prev = NULL, *curr = head;
    while (curr != NULL) {
        if (curr->maSV == maSV) {
            if (prev == NULL) {
                head = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            printf("Da xoa sinh vien co ma SV %d.\n", maSV);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("Khong tim thay sinh vien co ma SV %d.\n", maSV);
}

// H�m s?p x?p danh s�ch sinh vi�n theo m� s? sinh vi�n (s? d?ng phuong ph�p insertion sort)
void sapXep() {
    struct SinhVien *i, *j;
    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->maSV > j->maSV) {
                int temp_maSV = i->maSV;
                i->maSV = j->maSV;
                j->maSV = temp_maSV;

                char temp_tenSV[50];
                strcpy(temp_tenSV, i->tenSV);
                strcpy(i->tenSV, j->tenSV);
                strcpy(j->tenSV, temp_tenSV);

                int temp_tuoi = i->tuoi;
                i->tuoi = j->tuoi;
                j->tuoi = temp_tuoi;
            }
        }
    }
    printf("Da sap xep danh sach sinh vien theo ma SV.\n");
}

// H�m h?y danh s�ch li�n k?t
void huyDanhSach() {
    struct SinhVien* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("Da huy danh sach lien ket.\n");
}

// H�m nh?p danh s�ch sinh vi�n t? ngu?i d�ng
void nhapDanhSach() {
    int n;
    printf("Nhap so luong sinh vien: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int maSV, tuoi;
        char tenSV[50];
        printf("Nhap thong tin cho sinh vien thu %d:\n", i + 1);
        printf("Ma SV: ");
        scanf("%d", &maSV);
        printf("Ten SV: ");
        scanf("%s", tenSV);
        printf("Tuoi: ");
        scanf("%d", &tuoi);
        themSinhVien(maSV, tenSV, tuoi);
    }
}

int main() {
    int choice, maSV, tuoi;
    char tenSV[50];

    do {
        printf("\nMenu:\n");
        printf("1. Nhap danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Xoa sinh vien\n");
        printf("4. Sap xep danh sach theo ma SV\n");
        printf("5. Huy danh sach lien ket\n");
        printf("6. Hien thi danh sach sinh vien\n");
        printf("7. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
			    nhapDanhSach();
                break;
               
            case 2:
                 printf("Nhap ma SV: ");
                scanf("%d", &maSV);
                printf("Nhap ten SV: ");
                scanf("%s", tenSV);
                printf("Nhap tuoi: ");
                scanf("%d", &tuoi);
                themSinhVien(maSV, tenSV, tuoi);
                break;
            case 3:
                printf("Nhap ma SV can xoa: ");
                scanf("%d", &maSV);
                xoaSinhVien(maSV);
                break;
            case 4:
                sapXep();
                break;
            case 5:
                huyDanhSach();
                break;
            case 6:
                hienThiDanhSach();
                break;
            case 7:
                printf("Ket thuc chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
                break;
        }
    } while (choice != 7);

    return 0;
}

