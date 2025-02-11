#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char yemekadlari[30][30];
char yemeksureleri[30][4];
int index = 0; //parcala yemek listesi fonksiyonunda sirayla dizilere yerlestirmek icin

int ascisayisi;
int* ascilarsure; //asci sayisina bagli ascisureleri olusturmak icin bellekte bo? pointer tanimliyoruz.

int guncelsaat()
{
    time_t t;
    struct tm* zaman;
    t = time(NULL);
    zaman = localtime(&t);
    int saat = zaman->tm_hour;
    int dakika = zaman->tm_min;
    saat = saat * 100;
    return saat + dakika;
}

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

int hazirlamasuresibul(char* dizi) //yemek adini kullanarak o yemegin suresini bulur
{
    for (int i = 0; i < 20; i++)
    {
        if (!strcmp(yemekadlari[i], dizi))
            return atoi(yemeksureleri[i]);
    }
    return 0;
}

char* parcala(char metin[], int parca) {
    static char buffer[100];
    int i = 0;
    int bufferindeks = 0;
    int parcasayac = 0;

    while (1)
    {
        if (metin[i] == NULL) { //sonuncu parcaya geldigimizde
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
            memset(buffer, 0, sizeof(buffer));
            bufferindeks = 0;
        }
        else {
            buffer[bufferindeks] = metin[i];
            bufferindeks++;
        }
        i++;
    }
}

int gecmissipariskontrol(int okunansaat)
{
    int gecmis = 0;

    int osaat = okunansaat / 100;
    int odakika = okunansaat % 100;

    time_t t;
    struct tm* zamanstruct;
    t = time(NULL);
    zamanstruct = localtime(&t);
    int gsaat = zamanstruct->tm_hour;
    int gdakika = zamanstruct->tm_min;
    if (gsaat < osaat)
        return 0;
    if (gsaat > osaat)
        return 1;
    if (gsaat = osaat)
        if (gdakika < odakika)
            return 0;
    return 1; //eger saat ve dakika esit ise
}

void siparisbitir(int pos, char okunanparca[])
{
    FILE* fileptr;
    fileptr = fopen("C:\\veritabani\\siparisler.txt", "r+");
    pos -= strlen(okunanparca);
    pos += strlen(parcala(okunanparca, 1));
    fseek(fileptr, pos, SEEK_SET);
    fprintf(fileptr, "0"); //gecmis siparis olarak ayarlanir
    fclose(fileptr);
}

void siparisgor(int kontrol) //eger kontrol 0 ise bekleyen siparisleri, eger 1 ise ascilarin siparislerini yazdirir
{
    FILE* fileptr;
    fileptr = fopen("C:\\veritabani\\siparisler.txt", "r");
    if (fileptr != NULL) {
        int pos = 0;
        char okunanparca[100];
        int karakter;
        int bufferindeks = 0;
        while ((karakter = fgetc(fileptr)) != EOF) {
            pos++;
            if (karakter == '*')
            {
                okunanparca[bufferindeks] = '\0';
                if (kontrol == 0)
                {
                    if (!strcmp(parcala(okunanparca, 2), "1")) //bekleyen siparisler
                    {
                        printf("[%s]", parcala(okunanparca, 1));
                        printf(" | Yemek:%s", parcala(okunanparca, 4));
                        printf(" | Siparis saati:%s", parcala(okunanparca, 5));
                        printf(" | Tahmini teslim saati:%s\n", parcala(okunanparca, 6));
                    }
                }
                if (kontrol == 1)
                {
                    if (!strcmp(parcala(okunanparca, 2), "4")) //ascilarin siparisleri
                    {
                        if (gecmissipariskontrol(atoi(parcala(okunanparca, 6)))) //eger siparis hazirlanma saati gecmis ise
                        {
                            siparisbitir(pos, okunanparca);
                        }
                        else
                        {
                            printf("Asci%d", atoi(parcala(okunanparca, 9)));
                            printf(" | [%s]", parcala(okunanparca, 1));
                            printf(" | YEMEK:%s", parcala(okunanparca, 4));
                            printf(" | FIYAT:%sTL", parcala(okunanparca, 8));
                            printf(" | SIPARIS ZAMANI:%s", parcala(okunanparca, 5));
                            printf(" | KULLANICI:%s \n", parcala(okunanparca, 3));
                        }
                    }
                }
                memset(okunanparca, 0, sizeof(okunanparca));
                bufferindeks = 0;
            }
            else
            {
                okunanparca[bufferindeks] = karakter;
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

void hazirlanmasuredegis(char okunanparca[], int hazirlamazamani, int position, int asci) //siparislerin yeni hazirlanma surelerini verir, siparisin durumunu degisir, verilen asciyi yazar
{
    int zamanpos = position; //tahmini teslim baslangic pozisyonu
    int durumpos = position; //siparis durumu baslangic pozisyonu
    int ascipos = position;
    FILE* fileptr;
    fileptr = fopen("C:\\veritabani\\siparisler.txt", "r+");
    if (fileptr != NULL)
    {
        zamanpos -= strlen(okunanparca);
        zamanpos += strlen(parcala(okunanparca, 1));
        zamanpos += strlen(parcala(okunanparca, 2));
        zamanpos += strlen(parcala(okunanparca, 3));
        zamanpos += strlen(parcala(okunanparca, 4));
        zamanpos += strlen(parcala(okunanparca, 5));
        zamanpos += 4;
        fseek(fileptr, zamanpos, SEEK_SET);
        fprintf(fileptr, "%04d", hazirlamazamani); //tahmini hazirlanma suresi degistirildi.

        durumpos -= strlen(okunanparca);
        durumpos += strlen(parcala(okunanparca, 1));
        fseek(fileptr, durumpos, SEEK_SET);
        fprintf(fileptr, "4"); //durum mutfakta olarak ayarlandi.

        ascipos -= strlen(parcala(okunanparca, 9));
        ascipos -= 1;
        fseek(fileptr, ascipos, SEEK_SET);
        fprintf(fileptr, "%02d", asci + 1);
        fclose(fileptr);
    }
}

void ascilarigorevlendir(char okunanparca[], int position)
{
    if (!strcmp(parcala(okunanparca, 2), "1")) //aktif siparis ise
    {
        int yemeksure = hazirlamasuresibul(parcala(okunanparca, 4)); //yemegin hazirlanma suresi
        int indeks = enazmesgulasci(ascilarsure);

        int hazirlamazamani = dakikatopla(guncelsaat(), ascilarsure[indeks]); //guncel saat + ascinin mesguliyeti
        hazirlamazamani = dakikatopla(hazirlamazamani, yemeksure); // ekstradan yemegin hazirlanma suresi eklenir
        hazirlanmasuredegis(okunanparca, hazirlamazamani, position, indeks); //hazirlama zamanini siprislertxt uzerinde degisir.
        ascilarsure[indeks] += yemeksure; //ascinin mesguliyetini arttir
    }
}

void listeyioku(int k) {

    FILE* fileptr;
    if (k == 0)
        fileptr = fopen("C:\\veritabani\\yemeklistesi.txt", "r");
    else
        fileptr = fopen("C:\\veritabani\\siparisler.txt", "r");

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
                    ascilarigorevlendir(buffer, position);
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
    FILE* degiskenlerptr = fopen("C:\\veritabani\\degiskenler.txt", "r");
    if (degiskenlerptr == NULL) {
        printf("Asci sayisi okunamadi!");
        return 1;
    }
    fscanf(degiskenlerptr, "%d,", &ascisayisi);
    fclose(degiskenlerptr);
    ascilarsure = (int*)malloc(ascisayisi * sizeof(int)); // ascilarsure sayi dizisi icin dinamik bellek tahsisi yapilir,
    for (int i = 0; i < ascisayisi; i++)
    {
        ascilarsure[i] = 0;
    }
    int secim;
bas:
    printf("-------GELEN SIPARISLER---------------------------------------------------------------\n");
    siparisgor(0);
    printf("--------------------------------------------------------------------------------------\n\n");
    printf("-------ASCILARIN GOREVLERI---------------------------------------------------------------\n");
    siparisgor(1);
    printf("----------------------------------------------------------------------------------------\n\n\n");
    printf("[1] Yenile\n[2] Ascilari dagit\n");
    scanf("%d", &secim);
    if (secim == 1)
    {
        system("cls");
        goto bas;
    }
    if (secim == 2)
    {
        listeyioku(0); //yemek adlarini ve hazirlanma surelerini okur
        listeyioku(1); //ascilari dagitir
        system("cls");
        goto bas;
    }
}
