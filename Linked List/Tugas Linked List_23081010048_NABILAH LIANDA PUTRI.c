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
void tambahData(node **head);
void tambahAkhir(node **head);
void hapusAwal(node **head);
void hapusData(node **head);
void hapusAkhir(node **head);
void cariData(node *head);
void jumlahData(node *head);
void penjumlahan(node *head);
void tranverse(node *head);
void insertNode(node **head, node *pPre, node *pNew);

//========================================================

int main()
{
  node *head;
  char pilih;

  head = NULL;
  do{
     system("cls");
     printf("List pilihan:\n");
     printf("0. Cetak isi list\n");
     printf("1. Tambah data di awal\n");
     printf("2. Tambah data di tengah\n");
     printf("3. Tambahkan data di akhir\n");
     printf("4. Hapus data di awal\n");
     printf("5. Hapus data di tengah\n");
     printf("6. Hapus data di akhir\n");
     printf("7. Pencarian data\n");
     printf("8. Tampilkan informasi jumlah data\n");
     printf("9. Tampilkan hasil penjumlahan dari semua data\n");
     printf("Masukkan pilihan dalam angka (tekan q untuk keluar) : ");
     fflush(stdin);
     scanf("%c", &pilih);
    if (pilih == '0'){
        tranverse(head);
        getch();
    }
    else if (pilih == '1')
        tambahAwal(&head);
    else if (pilih == '2')
        tambahData(&head);
    else if (pilih == '3')
        tambahAkhir(&head);
    else if (pilih == '4')
        hapusAwal(&head);
    else if (pilih == '5')
        hapusData(&head);
    else if (pilih == '6')
        hapusAkhir(&head);
    else if (pilih == '7')
        cariData(head);
    else if (pilih == '8')
        jumlahData(head);
    else if (pilih == '9')
        penjumlahan(head);

  } while (pilih != 'q');

  return 0;
}

//========================================================

/*node *createNode(void){
  node *ptr;

  ptr = (node *)malloc(sizeof(node));
  return(ptr);
}*/

//========================================================

void tambahAwal(node **head){
  int bil;
  node *pNew;

  system("cls");
  fflush(stdin);
  printf("Masukkan bilangan : ");
  fflush(stdin);
  scanf("%d", &bil);
  pNew = (node *)malloc(sizeof(node));

  if (pNew != NULL){
  	  pNew->data = bil;
      pNew->next = NULL;
      //add before first logical node or to an empty list
	  pNew -> next = *head;
      *head = pNew;
  }
  else{
      printf("Alokasi memori gagal");
      getch();
  }
}

//========================================================

void tambahData(node **head){
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
  while (pCur != NULL && pCur -> data != pos) {
    pCur = pCur -> next;
  }

  pNew = (node *)malloc(sizeof(node));

  if (pCur == NULL){
     printf("\nnode tidak ditemukan");
     getch();
  }
  else if (pNew == NULL){
     printf("\nalokasi memeori gagal");
     getch();
  }
  else{
     pNew->data = bil;
     pNew->next = NULL;
     pNew -> next = pCur -> next;
     pCur -> next = pNew;
  }
}

//========================================================

void tambahAkhir(node **head){
    int bil;
    node *pNew, *pPre;

    system("cls");
    fflush(stdin);
    printf("Masukkan bilangan : ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if(pNew != NULL){
        pNew->data = bil;
        pNew->next = NULL;

        if(*head == NULL){
            *head = pNew;
        } else {
        pPre = *head;
        while (pPre->next != NULL){
            pPre = pPre->next;
        }
        pPre->next = pNew;
        }
    }
    else{
        printf("Alokasi memori gagal");
        getch();
    }

}

//========================================================

void hapusAwal(node **head){
    node *pHead, *pCur;

    system("cls");
    fflush(stdin);
    if(*head == NULL){
        printf("Data kosong, tidak ada yang dihapus.");
        getch();
        return;
    }
    node *temp = *head;
    *head = (*head)->next;
    free(temp);
    printf("Node awal berhasil dihapus.");
    getch();
}

//========================================================

void hapusData(node **head){
    int bil, pos, count=1;
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

    if(*head == NULL){
        printf("Data kosong, tidak ada yang dihapus.\n");
        getch();
        return;
    }

    while (pCur != NULL && (pCur->data != bil || count != pos)) {
        pPre = pCur;
        pCur = pCur->next;
        count++;
    }
    if (pCur == NULL) {
        printf("\nNode dengan bilangan %d di posisi %d tidak ditemukan.\n", bil, pos);
        getch();
        return;
    }

    if (pPre == NULL) {
        *head = (*head)->next;
    } else {
        pPre->next = pCur->next;
    }
    free(pCur);
    system("cls");
    tranverse(*head);
    printf("\nNode dengan bilangan %d di posisi %d berhasil dihapus.\n", bil, pos);
    getch();
}

//========================================================

void hapusAkhir(node **head){
    node *pNew, *pPre;

    system("cls");
    fflush(stdin);
    if(*head == NULL){
        printf("Data kosong, tidak ada yang dihapus.");
        getch();
        return;
    }
    if ((*head)->next == NULL){
        free(*head);
        printf("Node akhir berhasil dihapus.");
        getch();
        }

        pPre = *head;
        while(pPre->next->next != NULL){
            pPre=pPre->next;
        }
        free(pPre->next);
        pPre->next = NULL;
        printf("Node akhir berhasil dihapus.");
        getch();
}

//========================================================

void cariData(node *head){
    int pos=1, bil;
    node *pCur = head;

    system("cls");
    printf("Masukkan bilangan yang ingin dicari: ");
    fflush(stdin);
    scanf("%d", &bil);

    while(pCur != NULL){
        if(pCur->data == bil){
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

void jumlahData(node *head){
    int count=1;
    node *pCur = head;

    system("cls");
    fflush(stdin);
    while (pCur != NULL){
        count++;
        pCur = pCur->next;
    }
    printf("Jumlah data (beserta nilai NULL): %d\n", count);
    getch();
}

//========================================================

void penjumlahan(node *head){
    int sum=0;
    node *pCur = head;

    system("cls");
    fflush(stdin);
    while (pCur != NULL){
        sum += pCur->data;
        pCur = pCur->next;
    }
    printf("Hasil penjumlah seluruh data: %d\n", sum);
    getch();
}

//========================================================

void tranverse(node *head){
   //traverse a linked list
	node *pWalker;

   system("cls");
	pWalker = head;
	while (pWalker != NULL){
   	printf("%d\t", pWalker -> data);
   	pWalker = pWalker -> next;
      printf(" -> ");
	}
   printf("NULL");
}

//========================================================

void insertNode(node **head, node *pPre, node *pNew){
    if (pPre == NULL){
       //add before first logical node or to an empty list
	    pNew -> next = *head;
       *head = pNew;
    }
    else {
       //add in the middle or at the end
       pNew -> next = pPre -> next;
       pPre -> next = pNew;
   }
}

//========================================================


