#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char kisiid[16] = "122312";
char okunantarih[10];
char okunanID[20];

char yemekadlari[20][30];
char yemekfiyatlari[20][4];
char yemeksureleri[20][4];
int index = 0;
int gecmis; //gecmis veya mevcut siparislerin goruntulenmesi icin bool
int yemeksayisi = 0; //kaç tane yemek oldugunu gosterir.

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

int siparisidolustur(char kisiid[]) {

    int intkisiid = atoi(kisiid);
    time_t t;

    srand((unsigned)time(&t));

    return intkisiid + rand();
}

int guncelzaman(int isaret) {

    time_t t;
    struct tm* zaman;
    int gsaat, gdakika;

    // Şu anki zamanı al
    t = time(NULL);
    zaman = localtime(&t);
    
    switch (isaret) {
    case 1:
        gsaat = zaman->tm_hour;
        gdakika = zaman->tm_min;
        return gsaat * 100 + gdakika;
        break;
    case 2:
        return zaman->tm_mday;
        break;
    case 3:
        return zaman->tm_mon + 1;
        break;
    case 4:
        return zaman->tm_year + 1900;
        break;
    }
}

int dakikatopla(int saat, int dakika) {

    int toplamsaat = saat / 100 + (saat % 100 + dakika) / 60;
    toplamsaat %= 24;

    int toplamdk = (saat % 100 + dakika) % 60;

    int sayihalindesaat = toplamsaat * 100 + toplamdk;

    return sayihalindesaat;
}

//siparisler.txt parcalar
void parcalasiparisler(char okunanparca[]) {

    if (!strcmp(parcala(okunanparca, 3), kisiid)) {
        if (gecmis == 1)
        {
            if (!strcmp(parcala(okunanparca, 2), "0") || !strcmp(parcala(okunanparca, 2), "3"))
            {
                if (!strcmp(parcala(okunanparca, 2), "0"))
                {
                    printf("[GECMIS]");
                    printf("SIPARIS EDILMIS YEMEK:%s ", parcala(okunanparca, 4));
                    printf("SIPARIS SAATI:%s ", parcala(okunanparca, 5));
                    printf("TESLIM SAATI:%s ", parcala(okunanparca, 6));
                    printf("SIPARIS TARIHI:%s ", parcala(okunanparca, 7));
                    printf("ODENMIS TUTAR:%s\n", parcala(okunanparca, 8));
                }
                else
                {
                    printf("[IPTAL]");
                    printf("IPTAL EDILMIS YEMEK:%s ", parcala(okunanparca, 4));
                    printf("SIPARIS SAATI:%s ", parcala(okunanparca, 5));
                    printf("SIPARIS TARIHI:%s ", parcala(okunanparca, 7));
                }
            }
        }
        if (gecmis == 0)
        {
            if (!strcmp(parcala(okunanparca, 2), "1") || !strcmp(parcala(okunanparca, 2), "2"))
            {
                if (!strcmp(parcala(okunanparca, 2), "1"))
                {
                    printf("[AKTIF SIPARIS]");
                    printf(" Yemek:%s", parcala(okunanparca, 4));
                    printf(" Siparis Saat:%s", parcala(okunanparca, 5));
                    printf(" Teslim edilcek saat:%s", parcala(okunanparca, 6));
                    printf(" Tarih:%s", parcala(okunanparca, 7));
                    printf(" Tutar:%s\n", parcala(okunanparca, 8));
                }
                if (!strcmp(parcala(okunanparca, 2), "2"))
                {
                    printf("[ONAY BEKLIYOR]");
                    printf(" Yemek:%s", parcala(okunanparca, 4));
                    printf(" Siparis Saat:%s", parcala(okunanparca, 5));
                    printf(" Tarih:%s", parcala(okunanparca, 7));
                    printf(" Tutar:%s\n", parcala(okunanparca, 8));
                }
            }
        }
    }
}

//yemeklistesi.txt'nin parcasi okunup bu fonksiyona verildiginde o parcayi ayristirip ilgili degiskende kaydeder.
void parcalayemeklistesi(char okunanparca[]) {
    if (strcmp(parcala(okunanparca, 1), "0")) 
    {
        strcpy(yemekadlari[index], parcala(okunanparca, 2));
        strcpy(yemekfiyatlari[index], parcala(okunanparca, 3));
        strcpy(yemeksureleri[index], parcala(okunanparca, 4));
        index++;
        yemeksayisi++;
    }
}

//ilgili txt'yi okur. * * arasindaki metinleri bulup ilgili fonksiyona ayristirma icin gonderir
void listeyioku(int k) {

    FILE* fileptr;
    if (k == 0) {
        fileptr = fopen("C:\\Users\\Efe\\Desktop\\proje\\bin\\Debug\\yemeklistesi.txt", "r");
    }
    else{
        fileptr = fopen("C:\\Users\\Efe\\Desktop\\proje\\bin\\Debug\\siparisler.txt", "r");
    }

    if (fileptr == NULL) {
        printf("error");
    }
    char parca[100];
    int karakter;
    int indeks = 0;
    index = 0; //parcala yemeklistesi fonksiyonunda uygun indeksli dizilere dagitir.
    while ((karakter = fgetc(fileptr)) != EOF) { //tek tek karakter oku
        if (karakter == '*') //ilgili metin okundugunda
        {
            parca[indeks] = '\0';
            if (k == 0) {
                parcalayemeklistesi(parca);
            }
            else {
                parcalasiparisler(parca);
            }
            memset(parca, 0, sizeof(parca)); //bufferi resetlemek icin fonk
            indeks = 0; //buffere yazarken en basindan baslamak icin
        }
        else {
            parca[indeks] = karakter; //okunan chari bufferin belirli indeksine yaz
            indeks++; //indeksi arttir
        }
    }

    fclose(fileptr);
}

int mainsoru() {
    int secenek;

    printf("Hosgeldiniz! Ne yapmak istiyorsunuz?\n\n");
    printf("[1] yemek listesini goruntule\n[2] siparis durumunu gor\n[3] onceki siparislerine bak\n");
    scanf("%d", &secenek);

    return secenek;
}

int siparisolustur()
{
    int key;
    system("cls");
    yemeksayisi = 0;
    listeyioku(0);

    for (int i = 0; i < yemeksayisi; i++)
    {
        printf("KOD:[%d] YEMEK:%s YEMEK FIYATI:%s HAZIRLANMA SURESI:%s\n", i, yemekadlari[i], yemekfiyatlari[i], yemeksureleri[i]);
    }
        int siparisid;
        siparisid = siparisidolustur(kisiid);
        int kod;
        siparis:
        printf("\nGeri donmek icin [50], Siparis edilcek yemek kodu: ");
        scanf("%d", &kod);
        if (kod == 50)
            return 0;
        FILE* dosya;
        dosya = fopen("C:\\Users\\Efe\\Desktop\\proje\\bin\\Debug\\siparisler.txt", "a"); //txt'ye ekleme yapar
        fprintf(dosya, "SIP%d_%d,2,%s,%s,%04d,%04d,%02d%02d%d,%s*", guncelzaman(4), siparisid, kisiid, yemekadlari[kod], guncelzaman(1), dakikatopla(guncelzaman(1), atoi(yemeksureleri[kod])), guncelzaman(2), guncelzaman(3), guncelzaman(4), yemekfiyatlari[kod]);
        fclose(dosya);
        printf("%s siparisi basariyla alindi.\n",yemekadlari[kod]);
        goto siparis;   
}

int siparisdurumu()
{
    int key;
    system("cls");
    gecmis = 0;
    listeyioku(1);

    printf("\n[1] geri don\n");
    scanf("%d", &key);

    if (key == 1) {
        return 0;
    }
}

int gecmissiparisler()
{
    int key;
    system("cls");
    gecmis = 1;
    listeyioku(1);

    printf("\n[1] geri don\n");
    scanf("%d", &key);

    if (key == 1) {
        return 0;
    }
}

int main()
{
    int key;
baslangic:
    system("cls");
    key = mainsoru();
    switch (key)
    {

    case 1: //yemek listesi goruntuleme ve siparis verme
        key = siparisolustur();
        if (!key) 
            goto baslangic;
        break;

    case 2: //siparis durumu
        key = siparisdurumu();
        if (!key)
            goto baslangic;
        break;

    case 3: //geçmiş siparislerim
        key = gecmissiparisler();
        if (!key)
            goto baslangic;
        break;
    }
}
