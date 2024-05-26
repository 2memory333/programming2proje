#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char mevcutluk[2];
    char isim[30];
    char fiyat[4];
    char sure[4];
}yemek;

yemek yemekler[30];
int yemeksayisi = 0;

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

//////// EN FAZLA BULMA ///////////////////////////////////////////////////////////////
// siparisler.txt'deki her siparisten belli verileri bellege kaydeder, en fazla gecme sirasina gore fazlayi bulur.
// !bellek kullanimi yuksek!, buyuk boyutlu txt icin problem yasatir, max-1000 siparis icin arama yapabilir
int aindeks = 0;
char arananlar[1000][30] = { 0 }; 
int elemansayi[1000] = { 0 }; //txt icinde kac defa geciyor

int kontroldizi(char* dizi) //arananlar dizisi icinde var mi yok mu? varsa kacinci sirada
{
    for (int i = 0; i <= 30; i++)
    {
        if (!strcmp(dizi, arananlar[i]))
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

void encoksiparis(char metin[], int secim) //veritabanlarında aranan elemanlari arananlar dizisine kaydeder ve onlarin kac kez gectiklerini elemansayiya kaydeder.
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

void arac1(char path[],int param)
{
    FILE* fileptr = fopen(path, "r"); //bura surekli degisebilir 
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

                encoksiparis(buffer, param);
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
    }
}

void araclar(int param1)
{
    aindeks = 0;
    memset(arananlar, 0, sizeof(arananlar));
    memset(elemansayi, 0, sizeof(elemansayi));
    char path[100];

    int gun = 1;
    int ay = 1;
    int yil = 2024;
    while (!(gun == 31 && ay == 6 && yil == 2024)) //tarih2'ye ulasana kadar tarih1'e 1 gun ekler.
    {
        if (gun == 32)
        {
            gun = 1;
            ay++;
            if (ay == 13)
            {
                ay = 1;
                yil++;
            }
        }
        memset(path, 0, 100);
        sprintf(path, "C:\\veritabani\\kayitlar\\%02d%02d%04d.txt", gun, ay, yil);
        arac1(path, param1);
        gun++;
    }
}

///////////////////////////////////////////////////////////////////////////////////////

int kazancbul(char path[]) //verilen txt icerisindeki toplam kazanclari bulur
{
    int toplamkazanc = 0;
    FILE* fileptr = fopen(path, "r"); //bura surekli degisebilir
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
                toplamkazanc += atoi(parcala(buffer, 8));
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
    }
    return toplamkazanc;
}

int aykazanci(int ay)
{
    int toplamkazanc = 0;
    int kazanc = 0;
    char path[100];
    for (int gun = 1; gun <= 31; gun++)
    {
        memset(path, 0, 100);
        sprintf(path, "C:\\veritabani\\kayitlar\\%02d%02d%04d.txt", gun, ay, 2024);
        kazanc = kazancbul(path);
        toplamkazanc += kazanc;
    }
    return toplamkazanc;
}

int tarihkazanci(int tarih, int tarih2)
{
    int toplamkazanc = 0;
    int kazanc = 0;
    char path[100];

    int gun = tarih / 1000000;
    int yil = tarih % 10000;
    int ay = (tarih / 10000) - (gun * 100);

    int bitisgun = tarih2 / 1000000;
    int bitisyil = tarih2 % 10000;
    int bitisay = (tarih2 / 10000) - (bitisgun * 100);

    while (!(gun == bitisgun + 1 && ay == bitisay && yil == bitisyil)) //tarih2'ye ulasana kadar tarih1'e 1 gun ekler.
    {
        if (gun == 32)
        {
            gun = 1;
            ay++;
            if (ay == 13)
            {
                ay = 1;
                yil++;
            }
        }
        memset(path, 0, 100);
        sprintf(path, "C:\\veritabani\\kayitlar\\%02d%02d%04d.txt", gun, ay, yil);
        kazanc = kazancbul(path);
        toplamkazanc += kazanc;
        gun++;
    }
    return toplamkazanc;
}

//yemeklistesi.txt'nin parcasi okunup bu fonksiyona verildiginde o parcayi ayristirip ilgili degiskende kaydeder.
void parcalayemeklistesi(char okunanparca[]) {
    if (strcmp(parcala(okunanparca, 1), "0"))
    {
        strcpy(yemekler[yemeksayisi].mevcutluk, parcala(okunanparca, 1));
        strcpy(yemekler[yemeksayisi].isim, parcala(okunanparca, 2));
        strcpy(yemekler[yemeksayisi].fiyat, parcala(okunanparca, 3));
        strcpy(yemekler[yemeksayisi].sure, parcala(okunanparca, 4));
        yemeksayisi++;
    }
}

//siparisler.txt parcalar
void parcalasiparisler(char okunanparca[])
{
    if (!strcmp(parcala(okunanparca, 2), "2")) //onay durumunda ise
    {
        printf("[%s] [ONAY BEKLIYOR] ", parcala(okunanparca, 1));
        printf("| KULLANICI:%s ", parcala(okunanparca, 3));
        printf("| YEMEK:%s ", parcala(okunanparca, 4));
        printf("| SAAT:%s ", parcala(okunanparca, 5));
        printf("| TAHMINI TESLIM SAATI:%s ", parcala(okunanparca, 6));
        printf("| SIPARIS TARIHI:%s ", parcala(okunanparca, 7));
        printf("| ODENMIS TUTAR:%s\n", parcala(okunanparca, 8));
    }
}

int onayver(char siparisid[], int onaykodu)
{
    FILE* fileptr = fopen("C:\\Users\\Efe\\Desktop\\proje\\bin\\Debug\\siparisler.txt", "r+");
    if (fileptr != NULL)
    {
        char buffer[100];
        int indeksbuffer = 0;
        int karakter;
        int pos = 0;
        while ((karakter = fgetc(fileptr)) != EOF)
        {
            pos++;
            if (karakter == '*')
            {
                buffer[indeksbuffer] = '\0';//bufferi sonlandir
                if (!strcmp(parcala(buffer, 1), siparisid))
                {
                    pos -= strlen(buffer);
                    pos += strlen(parcala(buffer, 1));
                    fseek(fileptr, pos, SEEK_SET);
                    fprintf(fileptr, "%d", onaykodu);
                    fclose(fileptr);
                    return 1;
                }
                memset(buffer, 0, 100);
                indeksbuffer = 0;
            }
            else
            {
                buffer[indeksbuffer] = karakter;
                indeksbuffer++;
            }
        }
        fclose(fileptr);
        return 0;
    }
}

//ilgili txt'yi okur. * * arasindaki metinleri bulup ilgili fonksiyona ayristirma icin gonderir
void listeyioku(int k) {

    FILE* fileptr;
    if (!k)
        fileptr = fopen("C:\\veritabani\\yemeklistesi.txt", "r");
    else
        fileptr = fopen("C:\\veritabani\\siparisler.txt", "r");

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
                    parcalayemeklistesi(buffer);
                if (k == 1)
                    parcalasiparisler(buffer);
                memset(buffer, 0, sizeof(buffer)); //bufferi resetlemek icin fonk
                indeks = 0; //buffere yazarken en basindan baslamak icin
            }
            else {
                buffer[indeks] = karakter; //okunan chari bufferin belirli indeksine yaz
                indeks++; //indeksi arttir
            }
        }
        fclose(fileptr);
    }
}

int main()
{
    int param1;
    int param2;

    int islemkodu;
    char giris[100];
    char* key;
    int devam;
    int sirakodu;
    listeyioku(0);
bas:
    system("cls");
    printf("[1] Yemek Listesini Duzenle\n[2] Onay Bekleyen Siparisleri Goruntule\n[3] Analizler\n\n");
    scanf("%d", &islemkodu);
    while (getchar() != '\n'); //ustteki scanf cagrisindan kalan karakterleri temizlemek icin
    if (islemkodu == 1) {
        devam = 1;
        while (devam) {
            system("cls");;
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            for (int i = 0; i < yemeksayisi; i++) {
                printf("[SIRA]:%d | [MEVCUTLUK]:%s | [YEMEK ADI]:%s | [FIYATI]:%sTL | [HAZIRLANMA SURESI]:%sDK\n", i, yemekler[i].mevcutluk, yemekler[i].isim, yemekler[i].fiyat, yemekler[i].sure);
            }
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("\nKomutlar: k kaydet, e ekle \nkomut kodlari: m mevcutluk , a yemek adi, f fiyat, s hazirlanma suresi   komutkodu-(sira)-(birim)\n");
            printf("Geri donmek icin [1]\n");

            int i = 0;
            char c;
            while (scanf("%c", &c) == 1 && c != '\n') {
                giris[i++] = c;
            }
            giris[i] = '\0';

            if (!strcmp(giris, "1"))
                goto bas;
            key = strtok(giris, "-");

            if (*key == 'm') { //0 veya 1 olmali degilse hata verdirt
                sirakodu = atoi(strtok(NULL, "-"));
                key = strtok(NULL, "-");
                strcpy(yemekler[sirakodu].mevcutluk, key);
            }
            if (*key == 'a') { //ad uzunsa hata ver
                sirakodu = atoi(strtok(NULL, "-"));
                key = strtok(NULL, "-");
                strcpy(yemekler[sirakodu].isim, key);
            }
            if (*key == 'f') { //eger fiyat harfse hata ver
                sirakodu = atoi(strtok(NULL, "-"));
                key = strtok(NULL, "-");
                strcpy(yemekler[sirakodu].fiyat, key);
            }
            if (*key == 's') { //sure harfse hata ver
                sirakodu = atoi(strtok(NULL, "-"));
                key = strtok(NULL, "-");
                strcpy(yemekler[sirakodu].sure, key);
            }
            if (*key == 'e') { //sure harfse hata ver
                strcpy(yemekler[yemeksayisi].mevcutluk, strtok(NULL, "-"));
                strcpy(yemekler[yemeksayisi].isim, strtok(NULL, "-"));
                strcpy(yemekler[yemeksayisi].fiyat, strtok(NULL, "-"));
                strcpy(yemekler[yemeksayisi].sure, strtok(NULL, "-"));
                yemeksayisi++;
            }
            if (*key == 'k') { //yemek listesini kaydeder.
                FILE* dosya;
                dosya = fopen("C:\\veritabani\\yemeklistesi.txt", "w");
                for (int i = 0; i < yemeksayisi; i++) {
                    fprintf(dosya, "%s,%s,%s,%s*", yemekler[i].mevcutluk, yemekler[i].isim, yemekler[i].fiyat, yemekler[i].sure);
                }
                fclose(dosya);
            }
        }
    }
    if (islemkodu == 2) {
        system("cls");
        while (1) {
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            listeyioku(1);
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            printf("\nGeri donmek icin [1]");
            printf("\nonaylamak icin o-(siparisid) , reddetmek icin r-(siparisid)\n");
            scanf("%s", giris);
            key = strtok(giris, "-");

            if (!strcmp(giris, "1")) //geri donme tusu
                goto bas;

            if (!strcmp(key, "o")) { //siparis onaylanirsa
                key = strtok(NULL, "-");
                onayver(key, 1);
                system("cls");
                printf("%s kodlu siparis onaylandi.\n\n", key);
            }
            if (!strcmp(key, "r")) { //siparis reddedilirse
                key = strtok(NULL, "-");
                onayver(key, 3);
                system("cls");
                printf("%s kodlu siparis reddedildi.\n\n", key);
            }
        }
    }
    if (islemkodu == 3) {
        system("cls");
    islemlerbaslangic:
        printf("-------------------------------------------\n");
        printf("Secebileceginiz islemler:\n");
        printf("[1] Belirli aydaki kazanc\n");
        printf("[2] Belirli tarihteki kazanc\n");
        printf("[3] Tarihler arasi kazanc\n");
        printf("[4] En cok siparis veren kullanici\n");
        printf("[5] En cok tercih edilen yemek\n");
        printf("[6] En cok siparis alinan tarih\n");
        printf("[7] Calisan asci sayisini belirle\n");
        printf("[8] Gunun siparis kaydini al\n");
        printf("\n[9] Geri don\n");
        printf("-------------------------------------------\n");
        scanf("%d", &islemkodu);
        if (islemkodu == 1)
        {
            system("cls");
            printf("Ay giriniz (ornek subat icin 2, ekim icin 10): ");
            scanf("%d", &param1);
            printf("Secilen aydaki toplam kazanc: %dTL\n\n", aykazanci(param1));
            goto islemlerbaslangic;
        }
        if (islemkodu == 2)
        {
            system("cls");
            printf("Tarih giriniz (GGAAYYYY): ");
            scanf("%d", &param1);
            printf("Girilen tarihdeki toplam kazanc: %dTL\n\n", tarihkazanci(param1,param1));
            goto islemlerbaslangic;
        }
        if (islemkodu == 3)
        {
            system("cls");
            printf("Sirayla iki tarih giriniz (ornek GGAAYYYY GGAAYYYY): ");
            scanf("%d %d", &param1, &param2);
            printf("Girilen tarihler arasi toplam kazanc: %dTL\n\n", tarihkazanci(param1, param2));
            goto islemlerbaslangic;
        }
        if (islemkodu == 4)
        {
            system("cls");
            araclar(3);
            printf("En fazla siparis veren kullanici: %s\n", arananlar[dizienbuyuk(elemansayi)]);
            printf("Verdigi siparis sayisi: %d\n\n", elemansayi[dizienbuyuk(elemansayi)]);

            goto islemlerbaslangic;
        }
        if (islemkodu == 5)
        {
            system("cls");
            araclar(4);
            printf("En fazla siparis edilen yemek: %s \nTercih sayisi: %d\n\n", arananlar[dizienbuyuk(elemansayi)], elemansayi[dizienbuyuk(elemansayi)]);
            goto islemlerbaslangic;
        }
        if (islemkodu == 6)
        {
            system("cls");
            araclar(7);
            printf("En fazla siparis verilen tarih: %s (GGAAYYYY)\n", arananlar[dizienbuyuk(elemansayi)]);
            printf("Verilen toplam siparis: %d\n", elemansayi[dizienbuyuk(elemansayi)]);
            printf("Toplanan kazanc: %dTL\n\n", tarihkazanci(atoi(arananlar[dizienbuyuk(elemansayi)]), atoi(arananlar[dizienbuyuk(elemansayi)])));
            goto islemlerbaslangic;
        }
        if (islemkodu == 7)
        {
            printf("Calisacak asci sayisini giriniz: ");
            scanf("%d", &islemkodu);
            FILE* ptr = fopen("C:\\veritabani\\degiskenler.txt", "r + ");
            fseek(ptr, 0, SEEK_SET);
            fprintf(ptr, "%02d", islemkodu);
            fclose(ptr);
            system("cls");
            printf("Asci sayisi %d olarak ayarlandi.\n",islemkodu);
            goto islemlerbaslangic;

        }
        if (islemkodu == 8)
        {
            char saveislemtarih[16];
            printf("\nKayit tarihini gun ay yil giriniz ornek(GGAAYYYY): ");
            scanf("%s", saveislemtarih);
            strcat(saveislemtarih,".txt");
     
            char path[50] = "C:\\veritabani\\kayitlar\\siparisler";
            strcat(path, saveislemtarih);
            FILE* fileptr = fopen(path,"r");
            if (fileptr != NULL)
            {
                system("cls");
                printf("Hata !\n");
                printf("Girilen tarihe ait bir kayit zaten mevcut!\n\n");
                fclose(fileptr);
                goto islemlerbaslangic;
            }

            char komut[300] = "copy C:\\veritabani\\siparisler.txt C:\\veritabani\\kayitlar\\";
            strcat(komut, saveislemtarih);
            system(komut);
            system("del C:\\veritabani\\siparisler.txt");
            system("type nul > C:\\veritabani\\siparisler.txt");
            system("cls");
            printf("Kayit alindi.\n\n");
            goto islemlerbaslangic;
        }
        if (islemkodu == 9)
        {
            goto bas;
        }
    }
}
