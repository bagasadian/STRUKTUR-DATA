#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//========================================================

struct node {
    int data;
    struct node *next;
};
typedef struct node node;

//node *createNode(void);
void tambahAwal(node **head);
void tambahAkhir(node **head);
void tambahData(node **head);
void hapusAwal(node **head);
void hapusTengah(node **head);
void hapusAkhir(node **head);
void cariData(node *head);
void jumlahData(node *head);
void jumlahTotalData(node *head);
void tranverse(node *head);
void insertNode(node **head, node *pPre, node *pNew);

//========================================================

int main() {
    node *head;
    char pilih;

    head = NULL;
    do {
        system("cls");
        printf("masukkan pilihan\n");
        printf("1. tambah data di awal\n");
        printf("2. tambah data di tengah list\n");
        printf("3. tambah data di akhir\n");
        printf("4. hapus data di awal\n");
        printf("5. hapus data di tengah\n");
        printf("6. hapus data di akhir\n");
        printf("7. pencarian data\n");
        printf("8. jumlah data di linked list\n");
        printf("9. jumlah total data di linked list\n");
        printf("0. cetak isi list\n");
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
            tranverse(head);
            getch();
        }
    } while (pilih != 'q');

    return 0;
}

//========================================================

void tambahAwal(node **head) {
    int bil;
    node *pNew;

    system("cls");
    fflush(stdin);
    printf("masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = NULL;
        pNew->next = *head;
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
    printf("masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = NULL;
        if (*head == NULL) {
            *head = pNew;
        } else {
            pCur = *head;
            while (pCur->next != NULL) {
                pCur = pCur->next;
            }
            pCur->next = pNew;
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
    tranverse(*head);
    printf("\nposisi penyisipan setelah data bernilai : ");
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nbilangan : ");
    fflush(stdin);
    scanf("%d", &bil);

    pCur = *head;
    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->next;
    }

    pNew = (node *)malloc(sizeof(node));

    if (pCur == NULL) {
        printf("\nnode tidak ditemukan");
        getch();
    } else if (pNew == NULL) {
        printf("\nalokasi memeori gagal");
        getch();
    } else {
        pNew->data = bil;
        pNew->next = NULL;
        pNew->next = pCur->next;
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
    tranverse(*head);
    printf("\nMasukkan data yang ingin dihapus: ");
    scanf("%d", &bil);

    pCur = *head;
    if (pCur == NULL) {
        printf("List kosong!\n");
        getch();
        return;
    }

    if (pCur->data == bil) {
        hapusAwal(head);
        return;
    }

    while (pCur->next != NULL && pCur->next->data != bil) {
        pCur = pCur->next;
    }

    if (pCur->next == NULL) {
        printf("Data tidak ditemukan!\n");
        getch();
    } else {
        pHapus = pCur->next;
        pCur->next = pHapus->next;
        free(pHapus);
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
        while (pCur->next->next != NULL) {
            pCur = pCur->next;
        }
        pHapus = pCur->next;
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

    while (pCur != NULL) {
        total += pCur->data;
        pCur = pCur->next;
    }

    printf("Jumlah total dari semua data: %d\n", total);
    getch();
}

//========================================================

void tranverse(node *head) {
    node *pWalker;

    system("cls");
    pWalker = head;
    while (pWalker != NULL) {
        printf("%d -> ", pWalker->data);
        pWalker = pWalker->next;
    }
    printf("NULL\n");
}

//========================================================

void insertNode(node **head, node *pPre, node *pNew) {
    if (pPre == NULL) {
        pNew->next = *head;
        *head = pNew;
    } else {
        pNew->next = pPre->next;
        pPre->next = pNew;
    }
}

//================================================
