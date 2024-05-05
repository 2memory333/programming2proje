#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* parcala(char metin[], int parca) {
    static char buffer[100];
    int i = 0;
    int bufferindeks = 0;
    int parcasayac = 0;

    while (1)
    {
        if (metin[i] == NULL) {
            buffer[bufferindeks] = '\0';
            return buffer;
        }
        if (metin[i] == ',') {
            parcasayac++;
            if (parcasayac == parca)
            {
                buffer[bufferindeks] = '\0';
                return buffer;
            }
            else {
                memset(buffer, 0, sizeof(buffer));
                bufferindeks = 0;
            }
        }
        else {
            buffer[bufferindeks] = metin[i];
            bufferindeks++;
        }
        i++;
    }
}

//////// EN FAZLA BULMA ///////
// siparislertxt icindeki idleri diziye kaydedip, aralarindan en fazla olani bulur.
// !bellek kullanimi yuksek!, buyuk boyutlu txt icin problem yasatir
int aindeks = 0;
char arananlar[30][30] = { 0 };
int elemansayi[30] = { 0 }; //txt icinde kac defa geciyor

int kontroldizi(char *dizi) //idler dizisi icinde var mi yok mu? varsa kacinci sirada
{
    for (int i = 0; i <= 30; i++)
    {
        if (!strcmp(dizi,arananlar[i]))
            return i;
    }
    return 50; //kontrol kodu
}

int dizienbuyuk(int dizi[])
{ //en buyuk elemanin indeksini bulur ! dizinin 0 ile bitmesi sart
    int x = dizi[0];
    int bindeks = 0;

    int i = 1;
    while (dizi[i] != 0)
    {
        if (dizi[i] > x)
        {
            x = dizi[i];
            bindeks = i;
        }
        i++;
    }
    return bindeks;
}

void encoksiparis(char metin[],int secim) //yuksek bellek kullanimi
{
    //secim 3 ise en fazla siparis veren kullanici
    //4 ise en fazla siparis edilen yemek
    //7 ise en fazla siparis alinan tarih
    int key = kontroldizi(parcala(metin, secim));
    if (key == 50) //eger var olan dizi icinde degilse
    {
        strcpy(arananlar[aindeks], parcala(metin, secim));
        elemansayi[aindeks]++;
        aindeks++;
    }
    else
        elemansayi[key]++;
}   

////////////////////////////////////////////////////////

int belirliaykazanc(char metin[],int secilenay)
{ 
     char ay[3];
     char *temp = parcala(metin, 7);
     ay[0] = temp[2];
     ay[1] = temp[3];
     ay[2] = '\0';
     if (secilenay == atoi(ay))
     {
          return (atoi(parcala(metin, 8)));
     }
     return 0;
}

int belirlitarihtekazanc(char metin[], int secilentarih)
{
    if (secilentarih == atoi(parcala(metin, 7)))
    {
        return (atoi(parcala(metin, 8)));
    }
    return 0;
}

int tarihlerarasikazanc(char metin[], int tarih1, int tarih2)
{
    int metintarih = atoi(parcala(metin, 7));
    if (tarih1 <= metintarih && metintarih <= tarih2)
    {
        return (atoi(parcala(metin, 8)));
    }
    return 0;
}

int araclar(int islemkodu,int param1,int param2)
{
    aindeks = 0;
    memset(arananlar, 0, sizeof(arananlar));
    memset(elemansayi, 0, sizeof(elemansayi));
    int toplamkazanc = 0;
    FILE  *fileptr = fopen("C:\\Users\\Efe\\Desktop\\proje\\bin\\Debug\\siparisler.txt", "r");
    if (fileptr != NULL)
    {
        int indeks = 0;
        int karakter;
        char buffer[100];
        while ((karakter = fgetc(fileptr)) != EOF)
        {
            if (karakter == '*')
            {
                buffer[indeks] = '\0';
                if (islemkodu == 1) //belirli ayda kazanilan
                {
                    toplamkazanc += belirliaykazanc(buffer, param1);
                }
                if (islemkodu == 2) //belirli tarihte kazanilan
                {
                    toplamkazanc += belirlitarihtekazanc(buffer, param1);
                }
                if (islemkodu == 3) //tarihler arasinda kazanilan
                {
                    toplamkazanc += tarihlerarasikazanc(buffer, param1, param2);
                }
                if (islemkodu == 4) //en cok siparis: edilen yemek, eden kullanici, edilen tarih
                {
                    encoksiparis(buffer,param1);
                }
                memset(buffer, 0, 100);
                indeks = 0;
            }
            else
            {
                buffer[indeks] = karakter;
                indeks++;
            }
        }
        fclose(fileptr);
        return toplamkazanc;
    }
}

void listeyioku(int k) {

    FILE* fileptr;
    if (!k)
        fileptr = fopen("C:\\Users\\Efe\\Desktop\\proje\\bin\\Debug\\yemeklistesi.txt", "r");
    else
        fileptr = fopen("C:\\Users\\Efe\\Desktop\\proje\\bin\\Debug\\siparisler.txt", "r");

    if (fileptr != NULL) {
        char buffer[100];
        int karakter;
        int indeks = 0;
        int position = 0; //metnin ilgili txt'de hangi sirada bittigini gosterir

        while ((karakter = fgetc(fileptr)) != EOF) { //tek tek karakter oku
            position++;
            if (karakter == '*') //ilgili metin okundugunda
            {
                buffer[indeks] = '\0';
                if (!k)
                    printf(buffer);
                if (k == 1)
                    printf(buffer);
                if (k == 2)
                    printf(buffer);
                memset(buffer, 0, sizeof(buffer)); //bufferi resetlemek icin fonk
                indeks = 0; //buffere yazarken en basindan baslamak icin
                //position = 0;
            }
            else {
                buffer[indeks] = karakter; //okunan chari bufferin belirli indeksine yaz
                indeks++; //indeksi arttir
            }
        }
        fclose(fileptr);
    }
}

int main() {
    int param1;
    int param2;
    int key;
    while (1)
    {
        scanf("%d", &key);
        if (key == 1)
        {
            system("cls");
            scanf("%d", &param1);
            printf("Secilen aydaki toplam kazanc: %d", araclar(1, param1, 0));
        }
        if (key == 2)
        {
            system("cls");
            scanf("%d", &param1);
            printf("Girilen tarihdeki toplam kazanc: %d", araclar(2, param1, 0));
        }
        if (key == 3)
        {
            system("cls");
            scanf("%d %d", &param1, &param2);
            printf("Girilen tarihler arasi toplam kazanc: %d", araclar(3, param1, param2));
        }
        if (key == 4) //en fazla siparis kullanici
        {
            system("cls");
            araclar(4, 3, 0);
            printf("En fazla siparis veren kullanici: %s\n", arananlar[dizienbuyuk(elemansayi)]);
            printf("Verdigi siparis sayisi: %d", elemansayi[dizienbuyuk(elemansayi)]);
        }
        if (key == 5) //en fazla siparis yemek
        {
            system("cls");
            araclar(4, 4, 0);
            printf("En fazla siparis edilen yemek: %s", arananlar[dizienbuyuk(elemansayi)]);
        }
        if (key == 6) //en fazla siparis tarihi
        {
            system("cls");
            araclar(4, 7, 0);
            printf("En fazla siparis verilen tarih: %s\n", arananlar[dizienbuyuk(elemansayi)]);
            printf("Verilen toplam siparis: %d\n", elemansayi[dizienbuyuk(elemansayi)]);
            printf("Toplanan kazanc: %d", araclar(2, atoi(arananlar[dizienbuyuk(elemansayi)]), 0));
        }
        if (key == 7)
        {
            char komut[130] = "copy C:\\Users\\Efe\\Desktop\\proje\\bin\\Debug\\siparisler.txt C:\\Users\\Efe\\Desktop\\proje\\bin\\Debug\\siparisler";
            system(komut);
        }
    }

}
