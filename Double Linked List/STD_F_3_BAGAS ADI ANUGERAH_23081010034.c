#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//========================================================

struct node {
    int data;
    struct node *next;
    struct node *prev; // Tambahkan pointer prev untuk doubly linked list
};
typedef struct node node;

// Fungsi-fungsi untuk doubly linked list
void tambahAwal(node **head);
void tambahAkhir(node **head);
void tambahData(node **head);
void hapusAwal(node **head);
void hapusTengah(node **head);
void hapusAkhir(node **head);
void cariData(node *head);
void jumlahData(node *head);
void jumlahTotalData(node *head);
void tranverse(node *head, int reverse);  // Satu fungsi untuk maju dan mundur
void insertNode(node **head, node *pPre, node *pNew);

//========================================================

int main() {
    node *head;
    char pilih;

    head = NULL;
    do {
        system("cls");
        printf("Masukkan pilihan\n");
        printf("1. Tambah data di awal\n");
        printf("2. Tambah data di tengah list\n");
        printf("3. Tambah data di akhir\n");
        printf("4. Hapus data di awal\n");
        printf("5. Hapus data di tengah\n");
        printf("6. Hapus data di akhir\n");
        printf("7. Pencarian data\n");
        printf("8. Jumlah data di linked list\n");
        printf("9. Jumlah total data di linked list\n");
        printf("0. Cetak isi list (dari awal)\n");
        printf("MASUKKAN PILIHAN (tekan q untuk keluar) : ");
        fflush(stdin);
        scanf("%c", &pilih);

        if (pilih == '1')
            tambahAwal(&head);
        else if (pilih == '2')
            tambahData(&head);
        else if (pilih == '3')
            tambahAkhir(&head);
        else if (pilih == '4')
            hapusAwal(&head);
        else if (pilih == '5')
            hapusTengah(&head);
        else if (pilih == '6')
            hapusAkhir(&head);
        else if (pilih == '7')
            cariData(head);
        else if (pilih == '8')
            jumlahData(head);
        else if (pilih == '9')
            jumlahTotalData(head);
        else if (pilih == '0') {
            tranverse(head, 0);
            getch();}
        }
     while (pilih != 'q');

    return 0;
}

//========================================================

void tambahAwal(node **head) {
    int bil;
    node *pNew;

    system("cls");
    fflush(stdin);
    printf("Masukkan bilangan: ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = *head;
        pNew->prev = NULL;

        if (*head != NULL)
            (*head)->prev = pNew;

        *head = pNew;
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void tambahAkhir(node **head) {
    int bil;
    node *pNew, *pCur;

    system("cls");
    fflush(stdin);
    printf("Masukkan bilangan: ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = NULL;

        if (*head == NULL) {
            pNew->prev = NULL;
            *head = pNew;
        } else {
            pCur = *head;
            while (pCur->next != NULL) {
                pCur = pCur->next;
            }
            pCur->next = pNew;
            pNew->prev = pCur;
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void tambahData(node **head) {
    int pos, bil;
    node *pNew, *pCur;

    system("cls");
    tranverse(*head, 0);
    printf("\nPosisi penyisipan setelah data bernilai: ");
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nBilangan: ");
    fflush(stdin);
    scanf("%d", &bil);

    pCur = *head;
    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->next;
    }

    pNew = (node *)malloc(sizeof(node));

    if (pCur == NULL) {
        printf("\nNode tidak ditemukan");
        getch();
    } else if (pNew == NULL) {
        printf("\nAlokasi memori gagal");
        getch();
    } else {
        pNew->data = bil;
        pNew->next = pCur->next;
        pNew->prev = pCur;

        if (pCur->next != NULL)
            pCur->next->prev = pNew;

        pCur->next = pNew;
    }
}

//========================================================

void hapusAwal(node **head) {
    node *pHapus;
    if (*head == NULL) {
        printf("List kosong!\n");
        getch();
    } else {
        pHapus = *head;
        *head = (*head)->next;

        if (*head != NULL)
            (*head)->prev = NULL;

        free(pHapus);
        printf("Node di awal berhasil dihapus\n");
        getch();
    }
}

//========================================================

void hapusTengah(node **head) {
    int bil;
    node *pCur, *pHapus;

    system("cls");
    tranverse(*head, 0);
    printf("\nMasukkan data yang ingin dihapus: ");
    scanf("%d", &bil);

    pCur = *head;
    if (pCur == NULL) {
        printf("List kosong!\n");
        getch();
        return;
    }

    while (pCur != NULL && pCur->data != bil) {
        pCur = pCur->next;
    }

    if (pCur == NULL) {
        printf("Data tidak ditemukan!\n");
        getch();
    } else {
        if (pCur->prev != NULL)
            pCur->prev->next = pCur->next;

        if (pCur->next != NULL)
            pCur->next->prev = pCur->prev;

        if (pCur == *head)  // Jika node yang dihapus adalah head
            *head = pCur->next;

        free(pCur);
        printf("Node di tengah berhasil dihapus\n");
        getch();
    }
}

//========================================================

void hapusAkhir(node **head) {
    node *pCur, *pHapus;

    if (*head == NULL) {
        printf("List kosong!\n");
        getch();
    } else if ((*head)->next == NULL) {
        hapusAwal(head);
    } else {
        pCur = *head;
        while (pCur->next != NULL) {
            pCur = pCur->next;
        }
        pHapus = pCur;
        pCur = pCur->prev;
        pCur->next = NULL;

        free(pHapus);
        printf("Node di akhir berhasil dihapus\n");
        getch();
    }
}

//========================================================

void cariData(node *head) {
    int bil, posisi = 0;
    node *pCur = head;

    system("cls");
    printf("Masukkan data yang ingin dicari: ");
    scanf("%d", &bil);

    while (pCur != NULL) {
        if (pCur->data == bil) {
            printf("Data %d ditemukan pada posisi %d\n", bil, posisi);
            getch();
            return;
        }
        pCur = pCur->next;
        posisi++;
    }

    printf("Data tidak ditemukan\n");
    getch();
}

//========================================================

void jumlahData(node *head) {
    int count = 0;
    node *pCur = head;

    while (pCur != NULL) {
        count++;
        pCur = pCur->next;
    }

    printf("Jumlah data di linked list: %d\n", count);
    getch();
}

//========================================================

void jumlahTotalData(node *head) {
    int total = 0;
    node *pCur = head;

    system("cls");
    while (pCur != NULL) {
        total += pCur->data;
        pCur = pCur->next;
    }

    printf("Jumlah total dari semua data: %d\n", total);
    getch();
}

//========================================================

void tranverse(node *head, int reverse) {
    node *pWalker = head;

    if (head == NULL) {
        printf("List kosong!\n");
        return;
    }

    system("cls");
    if (reverse == 0) {
        printf("NULL <- ");
        while (pWalker != NULL) {
            printf("%d", pWalker->data);
            if (pWalker->next != NULL) {
                printf(" <-> ");
            }
            pWalker = pWalker->next;
        }
        printf(" -> NULL\n");

    }
}

//========================================================

void insertNode(node **head, node *pPre, node *pNew) {
    if (pPre == NULL) {
        pNew->next = *head;
        pNew->prev = NULL;

        if (*head != NULL)
            (*head)->prev = pNew;

        *head = pNew;
    } else {
        pNew->next = pPre->next;
        pNew->prev = pPre;

        if (pPre->next != NULL)
            pPre->next->prev = pNew;

        pPre->next = pNew;
    }
}
