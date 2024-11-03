#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

// Struktur node
struct node {
    int data;
    struct node *next;
};
typedef struct node node;

// Prototipe fungsi
void tambahAwal(node **list);
void tambahData(node **list);
void tambahAkhir(node **list);
void hapusAwal(node **list);
void hapusData(node **list);
void hapusAkhir(node **list);
void cariData(node *list);
void jumlahData(node *list);
void penjumlahan(node *list);
void tranverse(node *list);
void clearScreen();  // Fungsi untuk membersihkan layar

// Fungsi utama
int main() {
    node *list = NULL;
    char pilih;

    do {
        clearScreen();
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
            clearScreen();
            tranverse(list);
            getch();
        } else if (pilih == '1') {
            clearScreen();
            tambahAwal(&list);
        } else if (pilih == '2') {
            clearScreen();
            tambahData(&list);
        } else if (pilih == '3') {
            clearScreen();
            tambahAkhir(&list);
        } else if (pilih == '4') {
            clearScreen();
            hapusAwal(&list);
        } else if (pilih == '5') {
            clearScreen();
            hapusData(&list);
        } else if (pilih == '6') {
            clearScreen();
            hapusAkhir(&list);
        } else if (pilih == '7') {
            clearScreen();
            cariData(list);
        } else if (pilih == '8') {
            clearScreen();
            jumlahData(list);
        } else if (pilih == '9') {
            clearScreen();
            penjumlahan(list);
        }

    } while (pilih != 'q');

    return 0;
}

// Fungsi untuk membersihkan layar
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Tambah data di awal
void tambahAwal(node **list) {
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

        if (*list == NULL) {
            // Jika list kosong, node menunjuk pada dirinya sendiri
            *list = pNew;
            pNew->next = pNew;
        } else {
            node *temp = *list;
            while (temp->next != *list) {
                temp = temp->next;
            }
            pNew->next = *list; // Node baru menunjuk ke head
            temp->next = pNew;  // Node terakhir menunjuk ke node baru
            *list = pNew;       // Update head ke node baru
        }
    }
}

// Tambah data di tengah
void tambahData(node **list) {
    int pos, bil;
    node *pNew, *pCur;

    tranverse(*list);
    printf("\nposisi penyisipan setelah data bernilai: ");
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nbilangan: ");
    fflush(stdin);
    scanf("%d", &bil);

    pCur = *list;
    while (pCur != NULL && pCur->data != pos) {
        pCur = pCur->next;
        if (pCur == *list) break; // Jika sudah kembali ke awal
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
        pCur->next = pNew;
    }
}

// Tambah data di akhir
void tambahAkhir(node **list) {
    int bil;
    node *pNew = (node *)malloc(sizeof(node));

    fflush(stdin);
    printf("Masukkan bilangan: ");
    fflush(stdin);
    scanf("%d", &bil);

    if (pNew != NULL) {
        pNew->data = bil;
        if (*list == NULL) {
            // Jika list kosong
            *list = pNew;
            pNew->next = *list; // Node baru menunjuk pada dirinya sendiri
        } else {
            node *pCur = *list;
            while (pCur->next != *list) {
                pCur = pCur->next; // Mencari node terakhir
            }
            pCur->next = pNew; // Node terakhir menunjuk ke node baru
            pNew->next = *list; // Node baru menunjuk ke head
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

// Hapus data di awal
void hapusAwal(node **list) {
    if (*list == NULL) {
        printf("Data kosong, tidak ada yang dihapus.");
        getch();
        return;
    }

    node *temp = *list;
    if (temp->next == *list) { // Jika hanya ada satu node
        free(temp);
        *list = NULL;
    } else {
        node *pCur = *list;
        while (pCur->next != *list) {
            pCur = pCur->next;
        }
        *list = (*list)->next; // Update head
        pCur->next = *list; // Node terakhir menunjuk ke head yang baru
        free(temp);
    }
    printf("Node awal berhasil dihapus.");
    getch();
}

// Hapus data di tengah
void hapusData(node **list) {
    int bil, pos, count = 1;
    node *pCur, *pPre;

    tranverse(*list);
    printf("\nMasukkan bilangan node yang ingin dihapus: ");
    fflush(stdin);
    scanf("%d", &bil);
    printf("Masukkan posisi bilangan node tersebut: ");
    fflush(stdin);
    scanf("%d", &pos);
    pCur = *list;
    pPre = NULL;

    if (*list == NULL) {
        printf("Data kosong, tidak ada yang dihapus.\n");
        getch();
        return;
    }

    do {
        if (pCur->data == bil && count == pos) {
            break;
        }
        pPre = pCur;
        pCur = pCur->next;
        count++;
    } while (pCur != *list);

    if (pCur == *list && pCur->data != bil) {
        printf("\nNode dengan bilangan %d di posisi %d tidak ditemukan.\n", bil, pos);
        getch();
        return;
    }

    if (pPre == NULL) { // Menghapus head
        hapusAwal(list);
    } else {
        pPre->next = pCur->next;
        free(pCur);
        printf("\nNode dengan bilangan %d di posisi %d berhasil dihapus.\n", bil, pos);
        getch();
    }
}

// Hapus data di akhir
void hapusAkhir(node **list) {
    if (*list == NULL) {
        printf("Data kosong, tidak ada yang dihapus.");
        getch();
        return;
    }

    node *pCur = *list;
    if (pCur->next == *list) { // Jika hanya ada satu node
        free(*list);
        *list = NULL;
    } else {
        node *pPre = NULL;
        while (pCur->next != *list) {
            pPre = pCur;
            pCur = pCur->next;
        }
        pPre->next = *list; // Node sebelum terakhir menunjuk ke head
        free(pCur);
    }
    printf("Node akhir berhasil dihapus.");
    getch();
}

// Cari data
void cariData(node *list) {
    int pos = 1, bil;
    node *pCur = list;

    printf("Masukkan bilangan yang ingin dicari: ");
    fflush(stdin);
    scanf("%d", &bil);

    do {
        if (pCur->data == bil) {
            printf("Node dengan bilangan %d ditemukan pada posisi %d.\n", bil, pos);
            getch();
            return;
        }
        pCur = pCur->next;
        pos++;
    } while (pCur != list);

    printf("Node dengan bilangan %d tidak ditemukan.\n", bil);
    getch();
}

// Tampilkan jumlah data
void jumlahData(node *list) {
    int count = 0;
    node *pCur = list;

    if (list == NULL) {
        printf("Data kosong, jumlah data adalah 0.\n");
        getch();
        return;
    }

    do {
        count++;
        pCur = pCur->next;
    } while (pCur != list);

    printf("Jumlah data (tidak termasuk NULL): %d\n", count);
    getch();
}

// Tampilkan hasil penjumlahan data
void penjumlahan(node *list) {
    int total = 0;
    node *pCur = list;

    if (list == NULL) {
        printf("Data kosong, tidak ada yang dijumlahkan.\n");
        getch();
        return;
    }

    do {
        total += pCur->data;
        pCur = pCur->next;
    } while (pCur != list);

    printf("Hasil penjumlahan data: %d\n", total);
    getch();
}

// Tampilkan isi list
void tranverse(node *list) {
    if (list == NULL) {
        printf("Data kosong.\n");
        return;
    }
    node *pCur = list;

    do {
        printf("%d -> ", pCur->data);
        pCur = pCur->next;
    } while (pCur != list);
    printf("(kembali ke %d)\n", list->data);
}
