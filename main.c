#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char yemekadlari[10][30];
char yemefiyatlari[10][30];
char yemeksureleri[10][30];
int dizilericinindeks = 0;
void diziyeaktar(char dizi[][30],int indeks,char *yemekadi[]){
strcpy(dizi[indeks],yemekadi);
}

//yemeklistesi.txt'nin parcasi okunup bu fonksiyona verildiginde o parcayi ayristirip ilgili degiskende kaydeder.
void parcalayemeklistesi(char okunanparca[]){

//verilen txt'de her * * arasindaki metini okuyup ilgili fonksiyonlara dagitir.
int i = 0;
char *key;
key = strtok(okunanparca, ","); //strtok fonksiyonunu kullanip okunan parcayi tanitiriz.

if(strcmp(key,"0")){ //eger key 1'e eşitse yani yemek mevcutsa, parcayi okumaya baslar
while (key != NULL){
    switch(i)
    {
    case 0: //mevcutluk
       break;
    case 1: //yemek adi
        diziyeaktar(yemekadlari,dizilericinindeks,key);
        break;
    case 2: //fiyati
        diziyeaktar(yemefiyatlari,dizilericinindeks,key);
        break;
    case 3: //hazirlanma suresi
        diziyeaktar(yemeksureleri,dizilericinindeks,key);
        break;
    }
    key = strtok(NULL, ","); //null ile strtok'a daha once parcaladigi dizinin kalan kismini kullanir
    i++;
    }}
    dizilericinindeks++;
}

//ilgili txt'yi okur. * * arasindaki metinleri bulup ilgili fonksiyona ayristirma icin gonderir
void listeyioku(int k){

FILE *fileptr;
if(!k)
fileptr = fopen("yemeklistesi.txt","r");
else
fileptr = fopen("siparisler.txt","r");


if (fileptr == NULL){
    printf("error");
}

   char buffer[100];
   int karakter;
   int indeks = 0;
   while ((karakter = fgetc(fileptr)) != EOF) { //tek tek karakter oku
        if(karakter == '*') //ilgili metin okundugunda
        {
            if(!k)
            parcalayemeklistesi(buffer);
            //else
            memset(buffer, 0, sizeof(buffer)); //bufferi resetlemek icin fonk
            indeks = 0; //buffere yazarken en basindan baslamak icin
        }
        else{
        buffer[indeks] = karakter; //okunan chari bufferin belirli indeksine yaz
        indeks++; //indeksi arttir
        }
    }

fclose(fileptr);
}

int mainsoru(){
int key;
printf("Ne yapmak istiyorsunuz?\n\n");
printf("[1] yemek listesini goruntule\n[2] siparis durumunu gor\n[3] onceki siparislerine bak\n");
scanf("%d",&key);
return key;
}

int main()
{
/*int key;
baslangic:
system("cls");
key = mainsoru();
switch(key)
{
case 1: //siparis ver
    system("cls");
    listeyioku();
    printf("\n[1] siparis ver \n[2] geri don\n");
    scanf("%d",&key);
    if(key == 1){
        char siparisyemek[20];
        printf("yemek adi: ");
        printf("%s%s",yemekadlari[0],yemekadlari[1]);
        scanf("%s",siparisyemek);
    }
    if(key == 2)
        goto baslangic; //geri donme icin
    break;
case 2: //siparis durumu
    break;
case 3: //siparislerim
    break;
}*/
listeyioku(0);
for(int i = 0; i < 3; i++)
{
    printf("%s %s %s\n",yemekadlari[i],yemefiyatlari[i],yemeksureleri[i]);
}
}

