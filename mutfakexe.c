#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char yemekadlari[20][30];
char yemeksureleri[20][4];
int index = 0; //parcala yemek listesi fonksiyonunda sirayla dizilere yerlestirmek icin

int ascisayisi;
FILE* ptr = fopen("C:\\Users\\Efe\\Desktop\\proje\\bin\\Debug\\degiskenler.txt", "r");
int result = fscanf(ptr, "%d,", &ascisayisi);
int* ascilarsure = (int*)malloc(ascisayisi * sizeof(int)); //?

int dakikatopla(int saat, int dakika) {

    int toplamsaat = saat / 100 + (saat % 100 + dakika) / 60;
    toplamsaat %= 24;

    int toplamdk = (saat % 100 + dakika) % 60;

    int sayihalindesaat = toplamsaat * 100 + toplamdk;

    return sayihalindesaat;

}

int enazmesgulasci(int ascilarsure[])
{
    int temp = ascilarsure[0];
    int musaitasci = 0;
    for (int i = 1; i < ascisayisi; i++)
    {
        if (ascilarsure[i] < temp)
        {
            temp = ascilarsure[i];
            musaitasci = i;
        }
    }
    return musaitasci;
}

int hazirlamasuresibul(char *dizi) //yemek adini kullanarak o yemegin suresini bulur
{
    for (int i = 0; i < 20; i++)
    {
        if(!strcmp(yemekadlari[i], dizi))
            return atoi(yemeksureleri[i]);
    }
    return 0;
}

char* parcala(char buffer[], int parca)
{
    int count = 0;
    char kelime[30];
    int kind = 0;
    int ind = 0;
    while (buffer[ind] != '\0')
    {
        if (buffer[ind] == ',')
        {
            count++;
            kelime[kind] = '\0';
            if (count == parca)
            {
                return kelime;
                break;
            }
            memset(kelime, 0, sizeof(kelime));
            kind = 0;
        }
        else
        {
            kelime[kind] = buffer[ind];
            kind++;
        }
        ind++;
    }
    kelime[kind] = '\0'; //en son parcayi alirken ',' olmadigi icin sonsuz donguye girmesi engellenir
    return kelime;
}

void aktifsiparisgor()
{
    FILE* fileptr;
    fileptr = fopen("C:\\Users\\Efe\\Desktop\\proje\\bin\\Debug\\siparisler.txt", "r");
    if (fileptr != NULL) {
        char buffer[100];
        int karakter;
        int bufferindeks = 0;
        while ((karakter = fgetc(fileptr)) != EOF) {
            if (karakter == '*')
            {
                buffer[bufferindeks] = '\0';
                if (!strcmp(parcala(buffer, 2), "1")) //aktif siparis ise
                {
                    printf("[%s]", parcala(buffer, 1));
                    printf(" | Yemek:%s", parcala(buffer, 4));
                    printf(" | Siparis Saat:%s", parcala(buffer, 5));
                    printf(" | Tahmini teslim saati:%s\n", parcala(buffer, 6));
                }
                memset(buffer, 0, sizeof(buffer));
                bufferindeks = 0;
            }
            else {
                buffer[bufferindeks] = karakter;
                bufferindeks++;
            }
        }
        fclose(fileptr);
    }
}

void parcalayemeklistesi(char okunanparca[]) {
    if (strcmp(parcala(okunanparca, 1), "0"))
    {
        strcpy(yemekadlari[index], parcala(okunanparca, 2));
        strcpy(yemeksureleri[index], parcala(okunanparca, 4));
        index++;
    }
}

void hazirlanmasuredegis(char okunanparca[], int hazirlamazamani,int position)
{
    int zamanpos = position; //tahmini teslim baslangic pozisyonu
    int durumpos = position; //siparis durumu baslangic pozisyonu

    FILE* fileptr;
    fileptr = fopen("C:\\Users\\Efe\\Desktop\\proje\\bin\\Debug\\siparisler.txt", "r+");
    if (fileptr != NULL)
    {
        zamanpos -= strlen(parcala(okunanparca, 8));
        zamanpos -= strlen(parcala(okunanparca, 7));
        zamanpos -= strlen(parcala(okunanparca, 6));
        zamanpos -= 3; //tahmini teslim zamani kismina getiriyoruz.
        fseek(fileptr, zamanpos, SEEK_SET);
        fprintf(fileptr, "%04d,", hazirlamazamani); //hazirlanma suresi degistirildi.

        durumpos -= strlen(okunanparca);
        durumpos += strlen(parcala(okunanparca, 1));
        fseek(fileptr, durumpos, SEEK_SET);
        fprintf(fileptr, "4"); //durum mutfakta olarak ayarlandi.
        fclose(fileptr);
        }
}

void ascilarigorevlendir(char okunanparca[],int position)
{
    if (!strcmp(parcala(okunanparca, 2), "1")) //aktif siparis ise
    {
        int yemeksure = hazirlamasuresibul(parcala(okunanparca, 4));
        int indeks = enazmesgulasci(ascilarsure);
        printf("Asci%d", indeks + 1);
        printf(" | [%s]", parcala(okunanparca, 1));
        printf(" | YEMEK:%s", parcala(okunanparca, 4));
        printf(" | FIYAT:%sTL", parcala(okunanparca, 8));
        printf(" | SIPARIS ZAMANI:%s", parcala(okunanparca, 5));

        int hazirlamazamani = dakikatopla(atoi(parcala(okunanparca, 6)), ascilarsure[indeks]); //tahmini sure + ascinin mesguliyeti
        printf(" | HAZIRLANMA ZAMANI: %04d", hazirlamazamani);

        hazirlanmasuredegis(okunanparca, hazirlamazamani,position); //hazirlama zamanini siprislertxt uzerinde degisir.

        printf(" | KULLANICI:%s \n", parcala(okunanparca, 3));
        ascilarsure[indeks] += yemeksure; //ascinin mesguliyetini arttir
    }
}


void listeyioku(int k) {

    FILE* fileptr;
    if (k == 0)
        fileptr = fopen("C:\\Users\\Efe\\Desktop\\proje\\bin\\Debug\\yemeklistesi.txt", "r");
    else
        fileptr = fopen("C:\\Users\\Efe\\Desktop\\proje\\bin\\Debug\\siparisler.txt", "r");

    if (fileptr != NULL) {
        char buffer[100];
        int karakter;
        int bufferindeks = 0;
        index = 0; //parcala yemek listesi fonksiyonunda sirayla dizilere yerlestirmek icin
        int position = 0; //ilgili metnin bitis pozisyonu
        while ((karakter = fgetc(fileptr)) != EOF) { //tek tek karakter oku
            position++;
            if (karakter == '*') //ilgili metin okundugunda
            {
                buffer[bufferindeks] = '\0';
                if (k == 0)
                    parcalayemeklistesi(buffer);
                if (k == 1)
                    ascilarigorevlendir(buffer,position);
                memset(buffer, 0, sizeof(buffer)); //bufferi resetlemek icin fonk
                bufferindeks = 0; //buffere yazarken en basindan baslamak icin
            }
            else {
                buffer[bufferindeks] = karakter; //okunan chari bufferin belirli indeksine yaz
                bufferindeks++; //indeksi arttir
            }
        }
        fclose(fileptr);
    }
}

int main()
{
    for (int i = 0; i < ascisayisi; i++)
    {
        ascilarsure[i] = 0;
    }
    printf("TOPLAMDA %d ASCI GOREV YAPMAKTADIR!\nSIPARIS GELDIGINDE ASCILAR OTOMATIK OLARAK GOREVLENDIRILECEKTIR\n\n", ascisayisi);
    while (1)
    {
        listeyioku(0); //yemek adlarini ve hazirlanma surelerini okur
        listeyioku(1); //ascilari dagitir
    }
}

