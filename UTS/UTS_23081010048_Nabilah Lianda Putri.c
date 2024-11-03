#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct node {
    char nama[50];
    char jenis_kelamin;
    struct node *next;
};
typedef struct node node;

void tambahData(node **head, int *perempuan);
void hapusData(node **head, int *perempuan);
void tranverse(node *head);
node* cari(node *head, char nama[]);
void pisahkan(node *head);
void kembar(node **head, char nama1[], char nama2[]);

int main() {
    node *head = NULL;
    char pilih;
    int perempuan = 0;

    do {
        system("cls");
        printf("List pilihan:\n0. Munculkan daftar mahasiswa\n1. Tambah mahasiswa\n2. Hapus mahasiswa\n3. Pisahkan berdasarkan jenis kelamin\nMasukkan pilihan dalam angka (tekan q untuk keluar): ");
        fflush(stdin);
        scanf("%c", &pilih);

        switch (pilih) {
            case '0':
                tranverse(head);
                break;
            case '1':
                tambahData(&head, &perempuan);
                break;
            case '2':
                hapusData(&head, &perempuan);
                break;
            case '3':
                pisahkan(head);
                break;
            case 'q':
                break;
            default:
                printf("Pilihan tidak valid!\n");
                getch();
        }
    } while (pilih != 'q');

    return 0;
}

//========================================================

void tambahData(node **head, int *perempuan) {
    char nama[50];
    char jenis_kelamin;
    node *pNew, *pCur, *pPrev, *pFriend;

    system("cls");
    fflush(stdin);
    printf("Masukkan nama mahasiswa: ");
    scanf("%s", nama);
    printf("Masukkan jenis kelamin (L/P): ");
    scanf(" %c", &jenis_kelamin);

    if (strcmp(nama, "Cindy") == 0) {
        pCur = *head;
        pFriend = NULL;

        if (*head != NULL) {
            do {
                if (pCur->jenis_kelamin == 'P') {
                    pFriend = pCur;
                    break;
                }
                pCur = pCur->next;
            } while (pCur != *head);
        }
        if (pFriend == NULL) {
            printf("Cindy hanya bisa masuk jika ada mahasiswa berjenis kelamin P.\n");
            getch();
            return;
        } else {
            pNew = (node *)malloc(sizeof(node));
            if (pNew != NULL) {
                strcpy(pNew->nama, "Cindy");
                pNew->jenis_kelamin = 'P';
                pNew->next = pFriend->next;
                pFriend->next = pNew;
                printf("Cindy berhasil ditambahkan di sebelah %s.\n", pFriend->nama);
                getch();
            }
            return;
        }
    }

    if (strcmp(nama, "Irsyad") == 0) {
        kembar(head, "Irsyad", "Arsyad");
        return;
    }
    if (strcmp(nama, "Arsyad") == 0) {
        kembar(head, "Arsyad", "Irsyad");
        return;
    }

    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        strcpy(pNew->nama, nama);
        pNew->jenis_kelamin = jenis_kelamin;

        if (jenis_kelamin == 'P') {
            (*perempuan)++;
        }

        if (*head == NULL) {
            *head = pNew;
            pNew->next = *head;
        } else {
            pCur = *head;
            while (pCur->next != *head) {
                pCur = pCur->next;
            }
            pCur->next = pNew;
            pNew->next = *head;
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void hapusData(node **head, int *perempuan) {
    char nama[50];
    node *pCur, *pPrev;

    system("cls");
    fflush(stdin);

    if (*head == NULL) {
        printf("Data kosong, tidak ada yang dihapus.");
        getch();
        return;
    }

    printf("Masukkan nama mahasiswa yang ingin dihapus: ");
    scanf("%s", nama);

    pCur = *head;
    pPrev = NULL;

    // Handling deletion of the only node in the circular linked list
    if (pCur->next == *head && strcmp(pCur->nama, nama) == 0) {
        if (pCur->jenis_kelamin == 'P') {
            (*perempuan)--;
        }
        free(pCur);
        *head = NULL;
        printf("Mahasiswa dengan nama %s berhasil dihapus.\n", nama);
        getch();
        return;
    }

    // Handling deletion of the head node
    if (strcmp(pCur->nama, nama) == 0) {
        while (pCur->next != *head) {
            pCur = pCur->next;
        }
        if ((*head)->jenis_kelamin == 'P') {
            (*perempuan)--;
        }
        pCur->next = (*head)->next;
        if (strcmp((*head)->next->nama, "Cindy") == 0) {
            node *cindyNode = (*head)->next;
            printf("Cindy juga dihapus karena teman sebelahnya dihapus.\n");
            free(cindyNode);
            // Adjust head if Cindy was the head or was after head
            (*head)->next = (*head)->next->next;
        }
        free(*head);
        *head = pCur->next;
        printf("Mahasiswa dengan nama %s berhasil dihapus.\n", nama);
        getch();
        return;
    }

    // Traverse the circular linked list to find the node to delete
    pCur = *head;
    do {
        pPrev = pCur;
        pCur = pCur->next;
    } while (pCur != *head && strcmp(pCur->nama, nama) != 0);

    // If found the node to delete
    if (strcmp(pCur->nama, nama) == 0) {
        if (pCur->jenis_kelamin == 'P') {
            (*perempuan)--;
        }
        pPrev->next = pCur->next; // Unlink the node from the list
        if (strcmp(pCur->next->nama, "Cindy") == 0) {
            node *cindyNode = pCur->next;
            printf("Cindy juga dihapus karena teman sebelahnya dihapus.\n");
            free(cindyNode);
            pPrev->next = pCur->next->next; // Bypass Cindy
        }
        free(pCur);
        printf("Mahasiswa dengan nama %s berhasil dihapus.\n", nama);
    } else {
        printf("Mahasiswa dengan nama %s tidak ditemukan.\n", nama);
    }

    getch();
}

//========================================================

void tranverse(node *head) {
    if (head == NULL) {
        printf("Data kosong\n");
        getch();
        return;
    }

    system("cls");
    printf("Daftar mahasiswa:\n");

    node *temp = head;
    do {
        printf("%s (%c) -> ", temp->nama, temp->jenis_kelamin);
        temp = temp->next;
    } while (temp != head);
    printf("(kembali ke %s)\n", head->nama);

    printf("\nTekan sembarang tombol untuk kembali...\n");
    getch();
}

//========================================================

node* cari(node *head, char nama[]) {
    if (head == NULL) {
        return NULL;
    }

    node *pCur = head;
    do {
        if (strcmp(pCur->nama, nama) == 0) {
            return pCur;
        }
        pCur = pCur->next;
    } while (pCur != head);
    return NULL;
}

//========================================================

void pisahkan(node *head) {
    if (head == NULL) {
        printf("Data kosong, tidak ada yang bisa dipisahkan.\n");
        getch();
        return;
    }
    node *pWalker = head;
    node *headMale = NULL;
    node *headFemale = NULL;
    node *lastMale = NULL;
    node *lastFemale = NULL;

    do {
        node *newNode = (node *)malloc(sizeof(node));
        if (newNode == NULL) {
            printf("Alokasi memori gagal.\n");
            getch();
            return;
        }

        strcpy(newNode->nama, pWalker->nama);
        newNode->jenis_kelamin = pWalker->jenis_kelamin;
        newNode->next = NULL;

        if (pWalker->jenis_kelamin == 'L') {
            if (headMale == NULL) {
                headMale = newNode;
                lastMale = newNode;
            } else {
                lastMale->next = newNode;
                lastMale = newNode;
            }
        } else {
            if (headFemale == NULL) {
                headFemale = newNode;
                lastFemale = newNode;
            } else {
                lastFemale->next = newNode;
                lastFemale = newNode;
            }
        }

        pWalker = pWalker->next;
    } while (pWalker != head);

    if (lastMale != NULL) {
        lastMale->next = headMale;
    }

    if (lastFemale != NULL) {
        lastFemale->next = headFemale;
    }

    printf("\nDaftar Mahasiswa Perempuan:\n");
    if (headFemale == NULL) {
        printf("Tidak ada mahasiswa perempuan.\n");
    } else {
        node *temp = headFemale;
        do {
            printf("%s (%c) -> ", temp->nama, temp->jenis_kelamin);
            temp = temp->next;
        } while (temp != headFemale);
        printf("(kembali ke %s)\n", headFemale->nama);
    }

    printf("\nDaftar Mahasiswa Laki-laki:\n");
    if (headMale == NULL) {
        printf("Tidak ada mahasiswa laki-laki.\n");
    } else {
        node *temp = headMale;
        do {
            printf("%s (%c) -> ", temp->nama, temp->jenis_kelamin);
            temp = temp->next;
        } while (temp != headMale);
        printf("(kembali ke %s)\n", headMale->nama);
    }

    getch();
}

//========================================================

void kembar(node **head, char nama1[], char nama2[]) {
    node *pNew, *pCur;

    // Membuat node baru untuk nama2
    pNew = (node *)malloc(sizeof(node));
    if (pNew == NULL) {
        printf("Alokasi memori gagal.\n");
        getch();
        return;
    }
    strcpy(pNew->nama, nama2);
    pNew->jenis_kelamin = 'L';

    if (*head == NULL) {
        *head = (node *)malloc(sizeof(node));
        if (*head == NULL) {
            printf("Alokasi memori gagal.\n");
            getch();
            return;
        }
        strcpy((*head)->nama, nama1);
        (*head)->jenis_kelamin = 'L';
        (*head)->next = *head;
        pNew->next = *head;
        (*head)->next = pNew;
        printf("%s dan %s berhasil ditambahkan.\n", nama1, nama2);
        getch();
        return;
    }

    pCur = *head;
    while (pCur->next != *head) {
        pCur = pCur->next;
    }
    pCur->next = pNew;
    pNew->next = *head;
    pNew = (node *)malloc(sizeof(node));
    if (pNew == NULL) {
        printf("Alokasi memori gagal.\n");
        getch();
        return;
    }
    strcpy(pNew->nama, nama1);
    pNew->jenis_kelamin = 'L';
    pCur->next = pNew;
    pNew->next = *head;
    *head = pNew;
    printf("%s dan %s berhasil ditambahkan.\n", nama1, nama2);
    getch();
}
