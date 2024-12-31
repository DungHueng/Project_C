#include "function.h"
#include <stdio.h>
#include <string.h>

void lobbyMenu(int choice){
    printf("*******HE THONG QUAN LY DANH MUC HANG HOA*******\n");
    printf("_____________THONG TIN DANH MUC________________\n");
    printf("===============================================\n");
    printf("[1] Quan ly danh muc\n");
    printf("[2] Khach hang\n");
    printf("[3] Thoat\n");
    printf("===============================================\n");
        printf("Lua chon cua ban: ");
}

void danhmucMenu(int choiceDanhmuc){
    printf("================================================\n");
    printf("[1] Xem thong tin danh muc\n"); 
    printf("[2] Them danh muc\n"); 
    printf("[3] Sua danh muc\n"); 
    printf("[4] Xoa danh muc\n"); 
    printf("[5] Tim kiem danh muc\n"); 
    printf("[6] Thoat\n"); 
    printf("================================================\n");
    printf("Moi nhap lua chon: ");
}

// Hien thi danh muc
void viewdanhmuc(){
    FILE *ptr = fopen("danhmuc.dat", "rb");
    if (ptr == NULL){
        printf("Loi mo tep.\n");
        return;
    }
    danhmuc view;
    // In bang thong bao san pham 
    printf("*=======|===========================|=============*\n");
    printf("|  ID   |       Ten danh muc        |   So luong  |\n");
    printf("|=======|===========================|=============|\n");
    while (fread(&view, sizeof(danhmuc), 1, ptr) != NULL){
        printf("|%6d | %-25s | %11d |\n",
            view.id,
            view.namedanhmuc,
            view.quantity);
        printf("|-------|---------------------------|-------------|\n");    
    }
    printf("*=======|===========================|=============*\n");
    fclose(ptr);
}

void adddanhmuc(){
    FILE *ptr = fopen("danhmuc.dat", "ab+");
    if (ptr == NULL){
        printf("Loi mo tep.\n");
        return;
    }
    danhmuc add[50];
    int n;
    printf("Nhap so luong danh muc muon nhap:\n");
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++){
        printf("*Nhap thong tin danh muc*\n");
        printf("ID: ");
        scanf("%d", &add[i].id);
        getchar();
        printf("Ten danh muc: ");
        fgets(add[i].namedanhmuc, sizeof(add[i].namedanhmuc), stdin);
        add[i].namedanhmuc[strcspn(add[i].namedanhmuc, "\n")] = '\0';
        fflush(stdin);
        printf("So luong danh muc: ");
        scanf("%d", &add[i].quantity);
        getchar();
    }
    fwrite(add, sizeof(danhmuc), n, ptr);
    printf("\nCac san pham da duoc them thanh cong.\n");
    fclose(ptr);
}

void editdanhmuc() {
    int addEdit;
    danhmuc edit;
    FILE *ptr = fopen("danhmuc.dat", "rb+");
    
    if (ptr == NULL) {
        printf("Khong the mo tep.\n");
        return;
    }

    fseek(ptr, 0, SEEK_END);
    int totalProducts = ftell(ptr) / sizeof(danhmuc);
    fseek(ptr, 0, SEEK_SET);

    // Kiem tra xem quan tri vien muon sua danh muc nao
    printf("Ban muon sua danh muc nao, vui long nhap ID: ");
    scanf("%d", &addEdit);
    while (addEdit < 1 || addEdit > totalProducts) {
        printf("khong co id %d ban muon sua): ", totalProducts);
        scanf("%d", &addEdit);
    }

    // In ra chi tiet danh muc truoc khi sua
    printf("\nChi tiet danh muci:\n");
    fseek(ptr, (addEdit - 1) * sizeof(danhmuc), SEEK_SET);
    fread(&edit, sizeof(danhmuc), 1, ptr);
    printf("*=======|===========================|=============*\n");
    printf("|  ID   |       Ten danh muc        |   So luong  |\n");
    printf("|=======|===========================|=============|\n");
    printf("|%6d | %-25s | %11d |\n",
        edit.id,
        edit.namedanhmuc,
        edit.quantity);
    printf("|-------|---------------------------|-------------|\n");
    printf("*=======|===========================|=============*\n");

    // Sua san pham
    printf("\n*Dang tien hanh sua san pham*\n");
    getchar();
    printf("Ten moi cua danh muc: ");
    fgets(edit.namedanhmuc, sizeof(edit.namedanhmuc), stdin);
    edit.namedanhmuc[strcspn(edit.namedanhmuc, "\n")] = '\0';
    fflush(stdin);

    printf("So luong danh muc: ");
    scanf("%d", &edit.quantity);
    getchar();

    // Luu danh mucda chinh sua vao tep
    fseek(ptr, (addEdit - 1) * sizeof(danhmuc), SEEK_SET);
    fwrite(&edit, sizeof(danhmuc), 1, ptr);

    fclose(ptr);
}

void deleteDanhMuc() {
    int delID, found = 0;
    danhmuc temp;
    FILE *ptr = fopen("danhmuc.dat", "rb+");
    FILE *tempPtr = fopen("temp.dat", "wb");

    if (ptr == NULL || tempPtr == NULL) {
        printf("Khong the mo tep.\n");
        return;
    }

    printf("Ban muon xoa danh muc nao, vui long nhap ID: ");
    scanf("%d", &delID);

    // Sao chep tat ca danh muc ngoai tru danh muc can xoa vao tep tam thoi
    while (fread(&temp, sizeof(danhmuc), 1, ptr) != NULL) {
        if (temp.id != delID) {
            fwrite(&temp, sizeof(danhmuc), 1, tempPtr);
        } else {
            found = 1; // Danh dau rang da tim thay danh muc can xoa
        }
    }

    fclose(ptr);
    fclose(tempPtr);

    if (found) {
        remove("danhmuc.dat");
        rename("temp.dat", "danhmuc.dat");
        printf("Danh muc da duoc xoa thanh cong.\n");
    } else {
        remove("temp.dat");
        printf("Khong tim thay danh muc co ID: %d.\n", delID);
    }
}

