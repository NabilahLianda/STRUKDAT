#include <stdio.h>
#include <stdlib.h>

//========================================================

struct node {
    int data;
    struct node *next;
    struct node *prev;
};
typedef struct node node;

// Function prototypes
void tambahAwal(node **head);
void tambahData(node **head);
void tambahAkhir(node **head);
void hapusAwal(node **head);
void hapusData(node **head);
void hapusAkhir(node **head);
void cariData(node *head);
void jumlahData(node *head);
void penjumlahan(node *head);
void tranverse(node *head);

//========================================================

int main() {
    node *head = NULL;
    char pilih;

    do {
        system("cls");
        printf("List pilihan:\n");
        printf("0. Cetak isi list\n");
        printf("1. Tambah data di awal\n");
        printf("2. Tambah data di tengah\n");
        printf("3. Tambah data di akhir\n");
        printf("4. Hapus data di awal\n");
        printf("5. Hapus data di tengah\n");
        printf("6. Hapus data di akhir\n");
        printf("7. Pencarian data\n");
        printf("8. Tampilkan jumlah data\n");
        printf("9. Tampilkan hasil penjumlahan data\n");
        printf("Masukkan pilihan dalam angka (tekan q untuk keluar): ");
        fflush(stdin);
        scanf("%c", &pilih);

        if (pilih == '0') {
            tranverse(head);
            getch();
        } else if (pilih == '1') {
            tambahAwal(&head);
        } else if (pilih == '2') {
            tambahData(&head);
        } else if (pilih == '3') {
            tambahAkhir(&head);
        } else if (pilih == '4') {
            hapusAwal(&head);
        } else if (pilih == '5') {
            hapusData(&head);
        } else if (pilih == '6') {
            hapusAkhir(&head);
        } else if (pilih == '7') {
            cariData(head);
        } else if (pilih == '8') {
            jumlahData(head);
        } else if (pilih == '9') {
            penjumlahan(head);
        }

    } while (pilih != 'q');

    return 0;
}

//========================================================

void tambahAwal(node **head) {
    int bil;
    node *pNew = (node *)malloc(sizeof(node));
    if (pNew == NULL) {
        printf("Alokasi memori gagal");
        getch();
    } else {
        printf("Masukkan bilangan: ");
        fflush(stdin);
        scanf("%d", &bil);

        pNew->data = bil;
        pNew->next = *head;
        pNew->prev = NULL;

        if (*head != NULL) {
            (*head)->prev = pNew; // Mengatur prev dari node pertama
        }
        *head = pNew;
    }
}

//========================================================

void tambahData(node **head) {
    int pos, bil;
    node *pNew, *pCur;

    system("cls");
    tranverse(*head);
    printf("\nposisi penyisipan setelah data bernilai: ");
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nbilangan: ");
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
        printf("\nalokasi memori gagal");
        getch();
    } else {
        pNew->data = bil;
        pNew->next = pCur->next;
        pNew->prev = pCur;

        if (pCur->next != NULL) {
            pCur->next->prev = pNew; // Mengatur prev dari node berikutnya
        }
        pCur->next = pNew;
    }
}

//========================================================

void tambahAkhir(node **head) {
    int bil;
    node *pNew = (node *)malloc(sizeof(node));
    node *pCur;

    system("cls");
    fflush(stdin);
    printf("Masukkan bilangan: ");
    fflush(stdin);
    scanf("%d", &bil);

    if (pNew != NULL) {
        pNew->data = bil;
        pNew->next = NULL; // Mengatur next untuk node akhir
        pNew->prev = NULL; // Mengatur prev untuk node baru

        if (*head == NULL) {
            *head = pNew; // Jika list kosong, node baru menjadi head
        } else {
            pCur = *head;
            while (pCur->next != NULL) {
                pCur = pCur->next; // Mencari node terakhir
            }
            pCur->next = pNew; // Menambahkan node baru di akhir
            pNew->prev = pCur; // Mengatur prev untuk node baru
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void hapusAwal(node **head) {
    if (*head == NULL) {
        printf("Data kosong, tidak ada yang dihapus.");
        getch();
        return;
    }

    node *temp = *head;
    *head = (*head)->next; // Memperbarui head
    if (*head != NULL) {
        (*head)->prev = NULL; // Mengatur prev untuk node baru head
    }
    free(temp);
    printf("Node awal berhasil dihapus.");
    getch();
}

//========================================================

void hapusData(node **head) {
    int bil, pos, count = 1;
    node *pCur, *pPre;

    system("cls");
    tranverse(*head);
    printf("\nMasukkan bilangan node yang ingin dihapus: ");
    fflush(stdin);
    scanf("%d", &bil);
    printf("Masukkan posisi bilangan node tersebut: ");
    fflush(stdin);
    scanf("%d", &pos);
    pCur = *head;
    pPre = NULL;

    if (*head == NULL) {
        printf("Data kosong, tidak ada yang dihapus.\n");
        getch();
        return;
    }

    while (pCur != NULL) {
        if (pCur->data == bil && count == pos) {
            break;
        }
        pPre = pCur;
        pCur = pCur->next;
        count++;
    }

    if (pCur == NULL) {
        printf("\nNode dengan bilangan %d di posisi %d tidak ditemukan.\n", bil, pos);
        getch();
        return;
    }

    if (pPre == NULL) { // Menghapus head
        hapusAwal(head);
    } else {
        pPre->next = pCur->next; // Memperbarui referensi prev
        if (pCur->next != NULL) {
            pCur->next->prev = pPre; // Memperbarui referensi prev dari node setelahnya
        }
        free(pCur);
        printf("\nNode dengan bilangan %d di posisi %d berhasil dihapus.\n", bil, pos);
        getch();
    }
}

//========================================================

void hapusAkhir(node **head) {
    if (*head == NULL) {
        printf("Data kosong, tidak ada yang dihapus.");
        getch();
        return;
    }

    node *pCur = *head;
    if (pCur->next == NULL) { // Jika hanya ada satu node
        free(*head);
        *head = NULL;
    } else {
        while (pCur->next != NULL) {
            pCur = pCur->next; // Mencari node terakhir
        }
        pCur->prev->next = NULL; // Menghapus referensi dari node sebelumnya
        free(pCur);
    }
    printf("Node akhir berhasil dihapus.");
    getch();
}

//========================================================

void cariData(node *head) {
    int pos = 1, bil;
    node *pCur = head;

    system("cls");
    printf("Masukkan bilangan yang ingin dicari: ");
    fflush(stdin);
    scanf("%d", &bil);

    while (pCur != NULL) {
        if (pCur->data == bil) {
            printf("Node dengan bilangan %d ditemukan pada posisi %d.\n", bil, pos);
            getch();
            return;
        }
        pCur = pCur->next;
        pos++;
    }

    printf("Node dengan bilangan %d tidak ditemukan.\n", bil);
    getch();
}

//========================================================

void jumlahData(node *head) {
    int count = 0;
    node *pCur = head;

    system("cls");
    if (head == NULL) {
        printf("Data kosong, jumlah data adalah 0.\n");
        getch();
        return;
    }

    while (pCur != NULL) {
        count++;
        pCur = pCur->next;
    }

    printf("Jumlah data (tidak termasuk NULL): %d\n", count);
    getch();
}

//========================================================

void penjumlahan(node *head) {
    int sum = 0;
    node *pCur = head;

    system("cls");
    if (head == NULL) {
        printf("Data kosong, tidak ada yang dijumlahkan.\n");
        getch();
        return;
    }

    while (pCur != NULL) {
        sum += pCur->data;
        pCur = pCur->next;
    }

    printf("Hasil penjumlahan seluruh data: %d\n", sum);
    getch();
}

//========================================================

void tranverse(node *head) {
    node *pWalker;

    system("cls");
    if (head == NULL) {
        printf("List kosong.\n");
        return;
    }

    pWalker = head;
    printf("NULL"); // Menampilkan NULL sebelum head

    while (pWalker != NULL) {
        if (pWalker == head) {
            printf(" <- %d", pWalker->data); // Node pertama
        } else if (pWalker->next != NULL) {
            printf(" <-> %d", pWalker->data); // Node tengah
        } else {
            printf(" <-> %d -> NULL", pWalker->data); // Node terakhir
        }
        pWalker = pWalker->next;
    }

    printf("\n");
}

