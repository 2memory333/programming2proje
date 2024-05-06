#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int yemeksayisi = 0;
char yemekmevcutluk[30][2];
char yemekadlari[30][50];
char yemekfiyatlari[30][4];
char yemeksureleri[30][4];

int index = 0; //yemek dizileri icin id;

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
// !bellek kullanimi yuksek!, buyuk boyutlu txt icin problem yasatir
int aindeks = 0;
char arananlar[100][30] = { 0 };
int elemansayi[100] = { 0 }; //txt icinde kac defa geciyor

int kontroldizi(char* dizi) //idler dizisi icinde var mi yok mu? varsa kacinci sirada
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

void encoksiparis(char metin[], int secim) //yuksek bellek kullanimi
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

///////////////////////////////////////////////////////////////////////////////////////

int belirliaykazanc(char metin[], int secilenay)
{
    char ay[3];
    char* temp = parcala(metin, 7);
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

int araclar(int islemkodu, int param1, int param2)
{
    aindeks = 0;
    memset(arananlar, 0, sizeof(arananlar));
    memset(elemansayi, 0, sizeof(elemansayi));
    int toplamkazanc = 0;
    FILE* fileptr = fopen("C:\\Users\\Efe\\Desktop\\proje\\bin\\Debug\\siparisler.txt", "r");
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
                    encoksiparis(buffer, param1);
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

//yemeklistesi.txt'nin parcasi okunup bu fonksiyona verildiginde o parcayi ayristirip ilgili degiskende kaydeder.
void parcalayemeklistesi(char okunanparca[]) {
    if (strcmp(parcala(okunanparca, 1), "0"))
    {
        strcpy(yemekmevcutluk[index], parcala(okunanparca, 1));
        strcpy(yemekadlari[index], parcala(okunanparca, 2));
        strcpy(yemekfiyatlari[index], parcala(okunanparca, 3));
        strcpy(yemeksureleri[index], parcala(okunanparca, 4));
        index++;
        yemeksayisi++;
    }
}

//siparisler.txt parcalar
void parcalasiparisler(char okunanparca[])
{
    if (!strcmp(parcala(okunanparca, 2), "2")) //onay durumunda ise
    {
        printf("[%s] [ONAY BEKLIYOR] ", parcala(okunanparca, 1));
        printf("KULLANICI:%s ", parcala(okunanparca, 3));
        printf("YEMEK:%s ", parcala(okunanparca, 4));
        printf("SAAT:%s ", parcala(okunanparca, 5));
        printf("TAHMINI TESLIM SAATI:%s ", parcala(okunanparca, 6));
        printf("SIPARIS TARIHI:%s ", parcala(okunanparca, 7));
        printf("ODENMIS TUTAR:%s\n", parcala(okunanparca, 8));
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
    printf("[1] Yemek Listesini Duzenle\n[2] Onay Bekleyen Siparisleri Goruntule\n[3] Diger\n\n");
    scanf("%d", &islemkodu);
    while (getchar() != '\n'); //ustteki scanf cagrisindan kalan karakterleri temizlemek icin
    if (islemkodu == 1) {
        devam = 1;
        while (devam) {
            system("cls");;
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            for (int i = 0; i < yemeksayisi; i++) {
                printf("[SIRA]:%d [MEVCUTLUK]:%s [YEMEK ADI]:%s [FIYATI]:%s [HAZIRLANMA SURESI]:%s\n", i, yemekmevcutluk[i], yemekadlari[i], yemekfiyatlari[i], yemeksureleri[i]);
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
                strcpy(yemekmevcutluk[sirakodu], key);
            }
            if (*key == 'a') { //ad uzunsa hata ver
                sirakodu = atoi(strtok(NULL, "-"));
                key = strtok(NULL, "-");
                strcpy(yemekadlari[sirakodu], key);
            }
            if (*key == 'f') { //eger fiyat harfse hata ver
                sirakodu = atoi(strtok(NULL, "-"));
                key = strtok(NULL, "-");
                strcpy(yemekfiyatlari[sirakodu], key);
            }
            if (*key == 's') { //sure harfse hata ver
                sirakodu = atoi(strtok(NULL, "-"));
                key = strtok(NULL, "-");
                strcpy(yemeksureleri[sirakodu], key);
            }
            if (*key == 'e') { //sure harfse hata ver
                strcpy(yemekmevcutluk[yemeksayisi], strtok(NULL, "-"));
                strcpy(yemekadlari[yemeksayisi], strtok(NULL, "-"));
                strcpy(yemekfiyatlari[yemeksayisi], strtok(NULL, "-"));
                strcpy(yemeksureleri[yemeksayisi], strtok(NULL, "-"));
                yemeksayisi++;
            }
            if (*key == 'k') { //yemek listesini kaydeder.
                FILE* dosya;
                dosya = fopen("C:\\Users\\Efe\\Desktop\\proje\\bin\\Debug\\yemeklistesi.txt", "w");
                for (int i = 0; i < yemeksayisi; i++) {
                    fprintf(dosya, "%s,%s,%s,%s*", yemekmevcutluk[i], yemekadlari[i], yemekfiyatlari[i], yemeksureleri[i]);
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
        printf("Beliri ay icin kazanilan para [1]\n");
        printf("Beliri tarih icin kazanilan para [2]\n");
        printf("Tarihler arasi para kazanmayi goruntule [3]\n");
        printf("En fazla siparis veren kullanici [4]\n");
        printf("En cok tercih edilen yemek [5]\n");
        printf("En cok siparis alinan tarih [6]\n");
        printf("Calisan asci sayisini belirle [7]\n");
        printf("Yemek yapim suresini belirle [8]\n");
        printf("\nGunun siparis kaydini al [9]\n");
        printf("-------------------------------------------\n");
        scanf("%d", &islemkodu);
        if (islemkodu == 1)
        {
            system("cls");
            printf("Ay giriniz (ornek subat icin 2, ekim icin 10): ");
            scanf("%d", &param1);
            printf("Secilen aydaki toplam kazanc: %d\n\n", araclar(1, param1, 0));
            goto islemlerbaslangic;
        }
        if (islemkodu == 2)
        {
            system("cls");
            printf("Tarih giriniz (ornek 05112024): ");
            scanf("%d", &param1);
            printf("Girilen tarihdeki toplam kazanc: %d\n\n", araclar(2, param1, 0));
            goto islemlerbaslangic;
        }
        if (islemkodu == 3)
        {
            system("cls");
            printf("Sirayla iki tarih giriniz (ornek 05112024 06112024): ");
            scanf("%d %d", &param1, &param2);
            printf("Girilen tarihler arasi toplam kazanc: %d\n\n", araclar(3, param1, param2));
            goto islemlerbaslangic;
        }
        if (islemkodu == 4)
        {
            system("cls");
            araclar(4, 3, 0);
            printf("En fazla siparis veren kullanici: %s\n", arananlar[dizienbuyuk(elemansayi)]);
            printf("Verdigi siparis sayisi: %d\n\n", elemansayi[dizienbuyuk(elemansayi)]);
            goto islemlerbaslangic;
        }
        if (islemkodu == 5)
        {
            system("cls");
            araclar(4, 4, 0);
            printf("En fazla siparis edilen yemek: %s \nTercih sayisi: %d\n\n", arananlar[dizienbuyuk(elemansayi)], elemansayi[dizienbuyuk(elemansayi)]);
            goto islemlerbaslangic;
        }
        if (islemkodu == 6)
        {
            system("cls");
            araclar(4, 7, 0);
            printf("En fazla siparis verilen tarih: %s\n", arananlar[dizienbuyuk(elemansayi)]);
            printf("Verilen toplam siparis: %d\n", elemansayi[dizienbuyuk(elemansayi)]);
            printf("Toplanan kazanc: %d\n\n", araclar(2, atoi(arananlar[dizienbuyuk(elemansayi)]), 0));
            goto islemlerbaslangic;
        }
        if (islemkodu == 7)
        {

        }
        if (islemkodu == 8)
        {

        }
        if (islemkodu == 9)
        {
            char saveislemtarih[16];
            printf("\nKayit tarihini gun ay yil giriniz ornek(02112024): ");
            scanf("%s", saveislemtarih);
            strcat(saveislemtarih,".txt");

            char path[50] = "kayitlar\\siparisler_";
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

            char komut[300] = "copy siparisler.txt kayitlar\\siparisler_";
            strcat(komut, saveislemtarih);
            system(komut);
            system("cls");
            printf("Kayit alindi.\n\n");
            goto islemlerbaslangic;
        }
    }
}
