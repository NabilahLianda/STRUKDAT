#include <stdio.h>
#include <conio.h>

struct biodata
{
char nama [10];
char tempat [10];
int umur;
}bio[10];
int main()
{
int i;
int n=0;
printf("Masukan jumlah data: ");
scanf("%d", &n);
for(i=0;i<n;i++)
{
getchar();
printf("\nNama=");scanf("%[^\n]",bio[i].nama);
getchar();
printf("Tempat lahir=");scanf("%[^\n]",bio[i].tempat);
printf("Umur=");scanf("%d", &bio[i].umur);
printf("\n");
}
for(i=0;i<n;i++)
{
printf("\nNama=%s",bio[i].nama);
printf("\nTempat lahir=%s",bio[i].tempat);
printf("\nUmur=%d",bio[i].umur);
printf("\n");
}
}
