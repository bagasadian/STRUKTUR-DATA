#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};
typedef struct node node;

void createQueue(node **front, node **rear, int *count);
void enqueue(node **front, node **rear, int *count, int maxQueue);
void dequeue(node **front, node **rear, int *count);
void peekFront(node *front);
void peekRear(node *rear);
int isEmpty(node *front);
int isFull(int count, int maxQueue);
void queueCount(int count);
void destroyQueue(node **front, node **rear, int *count);
void displayQueue(node *front);

int main() {
    node *front = NULL, *rear = NULL;
    int count = 0;
    int maxQueue = 10;
    char choice;

    do {
        system("cls");
        printf("Operasi Queue:\n");
        printf("1. Create Queue\n");
        printf("2. Enqueue (Tambahkan data ke queue)\n");
        printf("3. Dequeue (Hapus data dari queue)\n");
        printf("4. Queue Front (Lihat elemen depan queue)\n");
        printf("5. Queue Rear (Lihat elemen belakang queue)\n");
        printf("6. Empty Queue (Periksa apakah queue kosong)\n");
        printf("7. Full Queue (Periksa apakah queue penuh)\n");
        printf("8. Queue Count (Jumlah elemen dalam queue)\n");
        printf("9. Destroy Queue (Hancurkan queue)\n");
        printf("0. Display Queue (Tampilkan semua data dalam queue)\n");
        printf("q. Keluar\n");
        printf("Pilih operasi: ");
        fflush(stdin);
        scanf("%c", &choice);

        switch (choice) {
            case '1':
                createQueue(&front, &rear, &count);
                break;
            case '2':
                enqueue(&front, &rear, &count, maxQueue);
                break;
            case '3':
                dequeue(&front, &rear, &count);
                break;
            case '4':
                peekFront(front);
                break;
            case '5':
                peekRear(rear);
                break;
            case '6':
                printf("Queue %s.\n", isEmpty(front) ? "kosong" : "tidak kosong");
                getch();
                break;
            case '7':
                printf("Queue %s.\n", isFull(count, maxQueue) ? "penuh" : "tidak penuh");
                getch();
                break;
            case '8':
                queueCount(count);
                break;
            case '9':
                destroyQueue(&front, &rear, &count);
                break;
            case '0':
                displayQueue(front);
                getch();
                break;
            case 'q':
                printf("Keluar dari program, bye bye.\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
                getch();
        }
    } while (choice != 'q');

    return 0;
}

void createQueue(node **front, node **rear, int *count) {
    destroyQueue(front, rear, count);
    printf("Queue baru telah dibuat.\n");
    getch();
}

void enqueue(node **front, node **rear, int *count, int maxQueue) {
    if (isFull(*count, maxQueue)) {
        printf("Queue penuh, tidak dapat menambahkan elemen baru.\n");
        getch();
        return;
    }

    int value;
    printf("Masukkan data: ");
    scanf("%d", &value);

    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL) {
        printf("Alokasi memori gagal!\n");
        getch();
        return;
    }

    newNode->data = value;
    newNode->next = NULL;

    if (*rear == NULL) {
        *front = *rear = newNode;
    } else {
        (*rear)->next = newNode;
        *rear = newNode;
    }

    (*count)++;
    printf("Data %d berhasil ditambahkan ke queue.\n", value);
    getch();
}

void dequeue(node **front, node **rear, int *count) {
    if (isEmpty(*front)) {
        printf("Queue kosong, tidak ada elemen untuk dihapus.\n");
        getch();
        return;
    }

    node *temp = *front;
    printf("Data %d dihapus dari queue.\n", temp->data);
    *front = (*front)->next;
    free(temp);

    if (*front == NULL) {
        *rear = NULL;
    }

    (*count)--;
    getch();
}

void peekFront(node *front) {
    if (front == NULL) {
        printf("Queue kosong.\n");
    } else {
        printf("Elemen di depan queue: %d\n", front->data);
    }
    getch();
}

void peekRear(node *rear) {
    if (rear == NULL) {
        printf("Queue kosong.\n");
    } else {
        printf("Elemen di belakang queue: %d\n", rear->data);
    }
    getch();
}

int isEmpty(node *front) {
    return front == NULL;
}

int isFull(int count, int maxQueue) {
    return count >= maxQueue;
}

void queueCount(int count) {
    printf("Jumlah elemen dalam queue: %d\n", count);
    getch();
}

void destroyQueue(node **front, node **rear, int *count) {
    node *temp;
    while (*front != NULL) {
        temp = *front;
        *front = (*front)->next;
        free(temp);
    }
    *rear = NULL;
    *count = 0;
    printf("Queue telah dihancurkan.\n");
    getch();
}

void displayQueue(node *front) {
    if (front == NULL) {
        printf("Queue kosong.\n");
    } else {
        printf("Isi queue: ");
        while (front != NULL) {
            printf("%d -> ", front->data);
            front = front->next;
        }
        printf("NULL\n");
    }
}
