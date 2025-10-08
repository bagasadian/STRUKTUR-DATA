#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

Node* nodeBaru(char value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = value;
        newNode->next = NULL;
    }
    return newNode;
}

int isEmpty(Node* top) {
    return top == NULL;
}

void push(Node** top, char value) {
    Node* newNode = nodeBaru(value);
    if (newNode == NULL) {
        printf("Gagal alokasi memori\n");
        return;
    }
    newNode->next = *top;
    *top = newNode;
}

char pop(Node** top) {
    if (isEmpty(*top)) {
        return '\0';
    }
    Node* temp = *top;
    char poppedValue = temp->data;
    *top = temp->next;
    free(temp);
    return poppedValue;
}

int kurung(char open, char close) {
    if ((open == '(' && close == ')') ||
        (open == '[' && close == ']') ||
        (open == '{' && close == '}') ||
        (open == '<' && close == '>')) {
        return 1;
    }
    return 0;
}

int validasiKurung(const char* sequence) {
    Node* stack = NULL;

    for (int i = 0; sequence[i] != '\0'; i++) {
        char current = sequence[i];

        if (current == '(' || current == '[' || current == '{' || current == '<') {
            push(&stack, current);
        } else if (current == ')' || current == ']' || current == '}' || current == '>') {
            if (isEmpty(stack) || !kurung(pop(&stack), current)) {
                return 0;
            }
        }
    }

    int valid = isEmpty(stack);
    while (!isEmpty(stack)) {
        pop(&stack);
    }
    return valid;
}

int main() {
    char input[100];
    char pilihan;

    do {
        system("cls");
        printf("Masukkan kurung: ");
        scanf("%s", input);

        if (validasiKurung(input)) {
            printf("Valid\n");
        } else {
            printf("Tidak Valid\n");
        }

        printf("\nCoba lagi? (Y untuk lanjut, N untuk keluar): ");
        scanf(" %c", &pilihan);
    } while (pilihan == 'Y' || pilihan == 'y');

    printf("Sampai ketemu nanti T_T\n");
    return 0;
}
