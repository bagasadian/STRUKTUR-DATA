#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};
typedef struct node node;

int max_size = 5;
void push(node **head, int *size);
void pop(node **head, int *size);
void stackTop(node *head);
void traverse(node *head);
int isEmpty(node *head);
int isFull(int size);
void destroyStack(node **head, int *size);
void stackCount(int size);

int main() {
    node *head = NULL;
    char pilih;
    int size = 0;

    printf("Masukkan batas maksimum: ");
    scanf("%d", &max_size);

    do {
        system("cls");
        printf("Ayo dipilih\n");
        printf("0. Tampilkan isi stack\n");
        printf("1. Tambah data diatas (Push)\n");
        printf("2. Hapus data diatas (Pop)\n");
        printf("3. Tampilkan data teratas (Stack Top)\n");
        printf("4. Cek apakah stack kosong (Empty Stack)\n");
        printf("5. Cek apakah stack penuh (Full Stack)\n");
        printf("6. Tampilkan jumlah data di stack (Stack count)\n");
        printf("7. Hancurkan semua data di stack (Destroy stack)\n");
        printf("MASUKKAN PILIHAN (tekan q untuk keluar): ");
        fflush(stdin);
        scanf("%c", &pilih);

        if (pilih == '0') {
            traverse(head);
            getch();
        }
        else if (pilih == '1') {
            push(&head, &size);
        }
        else if (pilih == '2') {
            pop(&head, &size);
        }
        else if (pilih == '3') {
            stackTop(head);
            getch();
        }
        else if (pilih == '4') {
            if (isEmpty(head)) {
                printf("Stack kosong.\n");
            } else {
                printf("Stack tidak kosong.\n");
            }
            getch();
        }
        else if (pilih == '5') {
            if (isFull(size)) {
                printf("Stack penuh.\n");
            } else {
                printf("Stack tidak penuh.\n");
            }
            getch();
        }
        else if (pilih == '6') {
            stackCount(size);
            getch();
        }
        else if (pilih == '7') {
            destroyStack(&head, &size);
            printf("Stack berhasil dihapus.\n");
            getch();
        }

    } while (pilih != 'q');

    return 0;
}

void push(node **head, int *size) {
    if (isFull(*size)) {
        printf("Stack penuh! Tidak bisa menambah data lagi.\n");
        getch();
        return;
    }

    int bil;
    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL) {
        printf("Alokasi memori gagal.\n");
        getch();
        return;
    }

    printf("Masukkan bilangan: ");
    scanf("%d", &bil);

    newNode->data = bil;
    newNode->next = *head;
    *head = newNode;
    (*size)++;

    printf("Data berhasil ditambahkan ke stack.\n");
    getch();
}

void pop(node **head, int *size) {
    if (isEmpty(*head)) {
        printf("Stack kosong. Tidak ada data yang di-pop.\n");
        getch();
        return;
    }

    node *temp = *head;
    *head = (*head)->next;
    printf("Data %d berhasil di-pop dari stack.\n", temp->data);
    free(temp);
    (*size)--;
    getch();
}

void stackTop(node *head) {
    if (isEmpty(head)) {
        printf("Stack kosong.\n");
    } else {
        printf("Data teratas di stack: %d\n", head->data);
    }
}

void traverse(node *head) {
    node *current = head;
    system("cls");
    printf("Isi stack (top -> bottom): ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int isEmpty(node *head) {
    return head == NULL;
}

int isFull(int size) {
    return size >= max_size;
}

void destroyStack(node **head, int *size) {
    node *current = *head;
    node *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *head = NULL;
    *size = 0;
}

void stackCount(int size) {
    printf("Jumlah data di stack: %d\n", size);
}
