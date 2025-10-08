#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct stack {
    int data;
    struct stack *next;
};
typedef struct stack stack;

void push(stack **top, int value);
int pop(stack **top);
int peek(stack *top);
int isEmpty(stack *top);
int precedence(char op);
void infixToPostfix(char *infix, char *postfix);
int evaluatePostfix(char *postfix);

int main() {
    char infix[100];
    char postfix[100];
    char choice;

    do {
        system("cls");
        printf("Masukkan ekspresi infix (angka dan operator): ");
        scanf("%s", infix);

        infixToPostfix(infix, postfix);
        printf("Ekspresi postfix: %s\n", postfix);

        int result = evaluatePostfix(postfix);
        printf("Hasil eval postfix: %d\n", result);

        printf("Apakah Anda ingin mengonversi lagi? (Y/N): ");
        getchar();
        choice = getchar();

    } while (choice == 'Y' || choice == 'y');

    return 0;
}

void push(stack **top, int value) {
    stack *newNode = (stack *)malloc(sizeof(stack));
    if (newNode != NULL) {
        newNode->data = value;
        newNode->next = *top;
        *top = newNode;
    } else {
        printf("Alokasi memori gagal\n");
    }
}

int pop(stack **top) {
    if (*top == NULL) {
        printf("Stack kosong, tidak dapat pop\n");
        return -1;
    }
    stack *temp = *top;
    int data = temp->data;
    *top = (*top)->next;
    free(temp);
    return data;
}

int peek(stack *top) {
    if (top == NULL) {
        return -1;
    }
    return top->data;
}

int isEmpty(stack *top) {
    return top == NULL;
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void infixToPostfix(char *infix, char *postfix) {
    stack *top = NULL;
    char *ptr = infix;
    int j = 0;

    while (*ptr != '\0') {
        if (isdigit(*ptr)) {
            while (isdigit(*ptr)) {
                postfix[j++] = *ptr;
                ptr++;
            }
            postfix[j++] = ' ';
            continue;
        }
        else if (*ptr == '(') {
            push(&top, *ptr);
        }
        else if (*ptr == ')') {
            while (!isEmpty(top) && peek(top) != '(') {
                postfix[j++] = pop(&top);
                postfix[j++] = ' ';
            }
            pop(&top);
        }
        else if (*ptr == '+' || *ptr == '-' || *ptr == '*' || *ptr == '/') {
            while (!isEmpty(top) && precedence(peek(top)) >= precedence(*ptr)) {
                postfix[j++] = pop(&top);
                postfix[j++] = ' ';
            }
            push(&top, *ptr);
        }
        ptr++;
    }

    while (!isEmpty(top)) {
        postfix[j++] = pop(&top);
        postfix[j++] = ' ';
    }

    postfix[j] = '\0';
}

int evaluatePostfix(char *postfix) {
    stack *top = NULL;
    char *ptr = postfix;
    int a, b, result;

    while (*ptr != '\0') {
        if (isdigit(*ptr)) {
            int num = 0;
            while (isdigit(*ptr)) {
                num = num * 10 + (*ptr - '0');
                ptr++;
            }
            push(&top, num);
        }
        else if (*ptr == '+' || *ptr == '-' || *ptr == '*' || *ptr == '/') {
            b = pop(&top);
            a = pop(&top);

            switch (*ptr) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
            }
            push(&top, result);
        }
        ptr++;
    }

    return pop(&top);
}
