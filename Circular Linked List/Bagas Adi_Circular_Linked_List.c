#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};
typedef struct node node;

// Deklarasi fungsi
void tambahAwal(node **pList);
void tambahData(node **pList);
void tambahAkhir(node **pList);
void hapusAwal(node **pList);
void hapusData(node **pList);
void hapusAkhir(node **pList);
void cariData(node *pList);
void hitungData(node *pList);
void jumlahData(node *pList);
void tranverse(node *pList);

int main() {
    node *pList = NULL;
    char pilih;

    do {
        system("cls");
        printf("Masukkan pilihan:\n");
        printf("1. Tambah data di awal list\n");
        printf("2. Tambah data di tengah list\n");
        printf("3. Tambah data di akhir list\n");
        printf("4. Hapus data di awal list\n");
        printf("5. Hapus data di tengah list\n");
        printf("6. Hapus data di akhir list\n");
        printf("7. Cari data list\n");
        printf("8. Hitung jumlah data list\n");
        printf("9. Hitung perjumlahan total dari semua data list\n");
        printf("0. Cetak isi list\n");
        printf("MASUKKAN PILIHAN (tekan q untuk keluar): ");
        fflush(stdin);
        scanf("%c", &pilih);

        switch(pilih) {
            case '1': tambahAwal(&pList); break;
            case '2': tambahData(&pList); break;
            case '3': tambahAkhir(&pList); break;
            case '4': hapusAwal(&pList); break;
            case '5': hapusData(&pList); break;
            case '6': hapusAkhir(&pList); break;
            case '7': cariData(pList); break;
            case '8': hitungData(pList); break;
            case '9': jumlahData(pList); break;
            case '0': tranverse(pList); getch(); break;
        }
    } while (pilih != 'q');

    return 0;
}

//========================================================
void tambahAwal(node **pList) {
    int bil;
    node *pNew, *pLast;

    system("cls");
    printf("masukkan bilangan: ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;
        if (*pList == NULL) {
            pNew->next = pNew;
            *pList = pNew;
        } else {
            pLast = *pList;
            while (pLast->next != *pList) {
                pLast = pLast->next;
            }
            pNew->next = *pList;
            *pList = pNew;
            pLast->next = *pList;
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================
void tambahData(node **pList) {
    int pos, bil;
    node *pNew, *pCur;

    if (*pList == NULL) {
        printf("List kosong, tidak bisa tambah di tengah.");
        getch();
        return;
    }

    system("cls");
    tranverse(*pList);
    printf("\nPosisi penyisipan setelah data bernilai: ");
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nBilangan: ");
    fflush(stdin);
    scanf("%d", &bil);

    pCur = *pList;
    do {
        if (pCur->data == pos) break;
        pCur = pCur->next;
    } while (pCur != *pList);

    if (pCur->data != pos) {
        printf("\nNode tidak ditemukan");
        getch();
    } else {
        pNew = (node *)malloc(sizeof(node));
        if (pNew == NULL) {
            printf("\nAlokasi memori gagal");
            getch();
        } else {
            pNew->data = bil;
            pNew->next = pCur->next;
            pCur->next = pNew;
        }
    }
}

//========================================================
void tambahAkhir(node **pList) {
    int bil;
    node *pNew, *pCur;

    system("cls");
    printf("Masukkan bilangan: ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;

        if (*pList == NULL) {
            pNew->next = pNew;
            *pList = pNew;
        } else {
            pCur = *pList;
            while (pCur->next != *pList) {
                pCur = pCur->next;
            }
            pCur->next = pNew;
            pNew->next = *pList; // Link last node to head
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================
void hapusAwal(node **pList) {
    if (*pList == NULL) {
        printf("List kosong, tidak ada yang dihapus.");
        getch();
        return;
    }

    node *temp = *pList, *pLast = *pList;

    if ((*pList)->next == *pList) { // Only one node
        free(*pList);
        *pList = NULL;
    } else {
        while (pLast->next != *pList) {
            pLast = pLast->next;
        }
        *pList = (*pList)->next;
        pLast->next = *pList;
        free(temp);
    }
}

//========================================================
void hapusData(node **pList) {
    int bil;
    node *pCur = *pList, *pPrev = NULL;

    if (*pList == NULL) {
        printf("List kosong, tidak ada yang dihapus.");
        getch();
        return;
    }

    system("cls");
    tranverse(*pList);
    printf("\nMasukkan data yang ingin dihapus: ");
    fflush(stdin);
    scanf("%d", &bil);

    do {
        if (pCur->data == bil) break;
        pPrev = pCur;
        pCur = pCur->next;
    } while (pCur != *pList);

    if (pCur->data != bil) {
        printf("Data tidak ditemukan.");
        getch();
        return;
    }

    if (pCur == *pList && pCur->next == *pList) {
        free(*pList);
        *pList = NULL;
    } else {
        if (pCur == *pList) {
            node *pLast = *pList;
            while (pLast->next != *pList) {
                pLast = pLast->next;
            }
            *pList = (*pList)->next;
            pLast->next = *pList;
        } else {
            pPrev->next = pCur->next;
        }
        free(pCur);
    }
}

//========================================================
void hapusAkhir(node **pList) {
    if (*pList == NULL) {
        printf("List kosong, tidak ada yang dihapus.");
        getch();
        return;
    }

    node *pCur = *pList, *pPrev = NULL;

    if ((*pList)->next == *pList) {
        free(*pList);
        *pList = NULL;
    } else {
        while (pCur->next != *pList) {
            pPrev = pCur;
            pCur = pCur->next;
        }
        pPrev->next = *pList;
        free(pCur);
    }
}

//========================================================
void cariData(node *pList) {
    int bil;
    node *pCur = pList;

    if (pList == NULL) {
        printf("List kosong.");
        getch();
        return;
    }

    system("cls");
    tranverse(pList);
    printf("\nMasukkan data yang dicari: ");
    fflush(stdin);
    scanf("%d", &bil);

    do {
        if (pCur->data == bil) {
            printf("Data %d ditemukan.\n", bil);
            getch();
            return;
        }
        pCur = pCur->next;
    } while (pCur != pList);

    printf("Data tidak ditemukan.\n");
    getch();
}

//========================================================
void hitungData(node *pList) {
    int count = 0;
    node *pCur = pList;

    if (pList == NULL) {
        printf("Jumlah data di list: 0\n");
        getch();
        return;
    }

    do {
        count++;
        pCur = pCur->next;
    } while (pCur != pList);

    printf("Jumlah data di list: %d\n", count);
    getch();
}

//========================================================
void jumlahData(node *pList) {
    int sum = 0;
    node *pCur = pList;

    if (pList == NULL) {
        printf("jumlah total semua data: 0\n");
        getch();
        return;
    }

    do {
        sum += pCur->data;
        pCur = pCur->next;
    } while (pCur != pList);

    printf("Perjumlah total semua data: %d\n", sum);
    getch();
}

//========================================================
void tranverse(node *pList) {
    node *pWalker;

    if (pList == NULL) {
        printf("List kosong.\n");
        return;
    }

    pWalker = pList;
    printf("List ada:\n");

    printf("%d -> ", pWalker->data);

    pWalker = pWalker->next;
    while (pWalker != pList) {
        printf("%d -> ", pWalker->data);
        pWalker = pWalker->next;
    }

    printf("%d\n", pList->data);
}
