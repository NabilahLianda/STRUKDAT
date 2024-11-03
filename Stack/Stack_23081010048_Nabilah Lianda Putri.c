#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define MAX_CAPACITY 5

struct Stack {
    struct node *top;
    int count;
};
typedef struct Stack Stack;

struct node {
    int data;
    struct node *next;
};
typedef struct node node;

void push(Stack *stack, int data);
void pop(Stack *stack);
void stackTop(Stack *stack);
int isEmpty(Stack *stack);
int isFull(Stack *stack);
int stackCount(Stack *stack);
void destroyStack(Stack *stack);
void clearScreen();

int main() {
    Stack stack = {NULL, 0};
    char pilih;
    int data;

    do {
        clearScreen();
        printf("List pilihan:\n");
        printf("1. Push Stack (Menambah data)\n");
        printf("2. Pop Stack (Menghapus data)\n");
        printf("3. Stack Top (Menampilkan data paling atas)\n");
        printf("4. Empty Stack (Cek apakah stack kosong)\n");
        printf("5. Full Stack (Cek apakah stack penuh)\n");
        printf("6. Stack Count (Hitung jumlah data)\n");
        printf("7. Destroy Stack (Hapus seluruh data)\n");
        printf("Masukkan pilihan dalam angka (tekan q untuk keluar): ");
        fflush(stdin);
        scanf("%c", &pilih);

        if (pilih == '1') {
            clearScreen();
            printf("Masukkan data yang ingin ditambahkan: ");
            scanf("%d", &data);
            push(&stack, data);
        }
        else if (pilih == '2') {
            clearScreen();
            pop(&stack);
        }
        else if (pilih == '3') {
            clearScreen();
            stackTop(&stack);
            getch();
        }
        else if (pilih == '4') {
            clearScreen();
            if (isEmpty(&stack))
                printf("Stack masih kosong.\n");
            else
                printf("Stack belum kosong.\n");
            getch();
        }
        else if (pilih == '5') {
            clearScreen();
            if (isFull(&stack))
                printf("Stack sudah penuh.\n");
            else
                printf("Stack belum penuh.\n");
            getch();
        }
        else if (pilih == '6') {
            clearScreen();
            printf("Jumlah elemen di dalam stack: %d\n", stackCount(&stack));
            getch();
        }
        else if (pilih == '7') {
            clearScreen();
            destroyStack(&stack);
            printf("Seluruh data dalam stack berhasil dihapus.\n");
            getch();
        }
    } while (pilih != 'q');

    return 0;
}

// Fungsi untuk ganti layar
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Push Stack
void push(Stack *stack, int data) {
    if (isFull(stack)) {
        printf("Stack penuh, tidak dapat menambah data.\n");
        getch();
        return;
    }

    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL) {
        printf("Alokasi memori gagal.\n");
        getch();
        return;
    }

    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->count += 1;
    printf("Data '%d' berhasil ditambahkan ke stack.\n", data);
    getch();
}

// Pop Stack
void pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack masih kosong, tidak ada yang dihapus.\n");
        getch();
        return;
    }

    node *temp = stack->top;
    stack->top = stack->top->next;
    printf("Data '%d' berhasil dihapus dari stack.\n", temp->data);
    free(temp);
    stack->count -= 1;
    getch();
}

// Stack Top
void stackTop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack kosong.\n");
    } else {
        printf("Data paling atas pada stack adalah '%d'\n", stack->top->data);
    }
}

// Empty Stack
int isEmpty(Stack *stack) {
    return stack->top == NULL;
}

// Full Stack
int isFull(Stack *stack) {
    return stack->count >= MAX_CAPACITY;
}

// Stack Count
int stackCount(Stack *stack) {
    return stack->count;
}

// Destroy Stack
void destroyStack(Stack *stack) {
    node *temp;
    while (stack->top != NULL) {
        temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
    stack->count = 0;
}
