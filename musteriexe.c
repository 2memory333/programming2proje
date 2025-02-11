#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char isim[30];
    char fiyat[4];
    char sure[4];
}yemek;

const char kisiid[16] = "555330";
yemek yemekler[30];
int yemeksayisi = 0;
int gecmis; //gecmis veya mevcut siparislerin goruntulenmesi icin bool

char* parcala(char metin[], int parca) {            //geriye string döndürmek için kullanılır
    static char buffer[100];            // fonk disi cagrilar arasinda degeri korunur
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

int siparisidolustur() {
    static int seed = 1;
    int rastgele = 0;
    int random = 0;
    int carpim = 10;
    time_t t;
    srand((unsigned)seed + time(&t)); // Her çağrıda farklı bir seed değeri al
    int i;
    for (i = 0; i < 5; i++) {
        while (rastgele == 0) {
            rastgele = rand() % 10;
        }
        random += rastgele * carpim;
        carpim *= 10;
        rastgele = 0;
    }
    seed++;
    return random;
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

int kalandk(int st2)
{
    int st1 = guncelzaman(1); //guncel saati cek
    int st1saat = st1 / 100;
    int st1dk = st1 % 100;

    int st2saat = st2 / 100;
    int st2dk = st2 % 100;

    int st1toplamdk = st1saat * 60 + st1dk; //st1'in toplam dakikasi
    int st2toplamdk = st2saat * 60 + st2dk; //st2'nin toplam dakikasi

    int farkdk = st2toplamdk - st1toplamdk; //ikisi arasindaki fark

    if (farkdk >= 0)
    {
        return farkdk;
    }
    else
    {
        return 0;
    }
}

//siparisler.txt parcalar
void parcalasiparisler(char okunanparca[]) {

    if (!strcmp(parcala(okunanparca, 3), kisiid)) {
        if (gecmis == 1)
        {
            if (!strcmp(parcala(okunanparca, 2), "0"))
            {
                printf("[GECMIS]");
                printf(" SIPARIS EDILMIS YEMEK:%s ", parcala(okunanparca, 4));
                printf(" | SIPARIS SAATI:%s ", parcala(okunanparca, 5));
                printf(" | TESLIM SAATI:%s ", parcala(okunanparca, 6));
                printf(" | SIPARIS TARIHI:%s ", parcala(okunanparca, 7));
                printf(" | ODENMIS TUTAR:TL%s\n", parcala(okunanparca, 8));
            }
            if (!strcmp(parcala(okunanparca, 2), "3"))
            { 
                printf("[IPTAL]");
                printf(" IPTAL EDILMIS YEMEK:%s ", parcala(okunanparca, 4));
                printf(" | SIPARIS SAATI:%s ", parcala(okunanparca, 5));
                printf(" | SIPARIS TARIHI:%s \n", parcala(okunanparca, 7));
            }
        }
        if (gecmis == 0)
        {
            if (!strcmp(parcala(okunanparca, 2), "1"))
            {
                printf("[AKTIF SIPARIS]");
                printf(" Yemek:%s", parcala(okunanparca, 4));
                printf(" | Siparis Saat:%s", parcala(okunanparca, 5));
                printf(" | Tahmini teslim saati:%s", parcala(okunanparca, 6));
                printf(" | Tarih:%s", parcala(okunanparca, 7));
                printf(" | Tutar:%sTL\n", parcala(okunanparca, 8));
            }
            if (!strcmp(parcala(okunanparca, 2), "2"))
            {
                printf("[ONAY BEKLIYOR]");
                printf(" Yemek:%s", parcala(okunanparca, 4));
                printf(" | Siparis Saat:%s", parcala(okunanparca, 5));
                printf(" | Tarih:%s", parcala(okunanparca, 7));
                printf(" | Tutar:%sTL\n", parcala(okunanparca, 8));
            }
            if (!strcmp(parcala(okunanparca, 2), "4"))
            {
                printf("[MUTFAKTA]");
                printf(" Yemek:%s", parcala(okunanparca, 4));
                printf(" | Siparis Saat:%s", parcala(okunanparca, 5));
                printf(" | Teslim Saati:%s", parcala(okunanparca, 6));
                printf(" | Tarih:%s", parcala(okunanparca, 7));
                printf(" | Tutar:%sTL", parcala(okunanparca, 8));
                printf(" | KALAN DK: %d\n", kalandk(atoi(parcala(okunanparca, 6))));
            }
        }
    }
}

//yemeklistesi.txt'nin parcasi okunup bu fonksiyona verildiginde o parcayi ayristirip ilgili degiskende kaydeder.
void parcalayemeklistesi(char okunanparca[]) {
    if (strcmp(parcala(okunanparca, 1), "0"))
    {
        strcpy(yemekler[yemeksayisi].isim, parcala(okunanparca, 2));              //yemeksayisi + 1 olmasinin sebebi kodlari 1 den baslatarak geri don kodunu 0 yapmak
        strcpy(yemekler[yemeksayisi].fiyat, parcala(okunanparca, 3));
        strcpy(yemekler[yemeksayisi].sure, parcala(okunanparca, 4));
        yemeksayisi++;
    }
}

//ilgili txt'yi okur. * * arasindaki metinleri bulup ilgili fonksiyona ayristirma icin gonderir
void listeyioku(int k) {

    FILE* fileptr;
    if (k == 0) {
        fileptr = fopen("C:\\veritabani\\yemeklistesi.txt", "r");
        if (fileptr == NULL)
            printf("Yemeklistesi.txt acilamadi");
    }
    else {
        fileptr = fopen("C:\\veritabani\\siparisler.txt", "r");
        if (fileptr == NULL)
            printf("Siparisler.txt acilamadi.");
    }
    if (fileptr != NULL) {
        char parca[100];
        int karakter;
        int indeks = 0;
        yemeksayisi = 0; //parcala yemeklistesi fonksiyonunda uygun indeksli dizilere dagitir.
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
}

int mainsoru() {
    int secenek;

    printf("Hosgeldiniz! Ne yapmak istiyorsunuz?\n\n");
    printf("[1] yemek listesini goruntule\n[2] siparis durumunu gor\n[3] onceki siparislerimi goruntule\n[4] Programdan cik\n");
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
        printf("KOD:[%d] YEMEK:%s YEMEK FIYATI:%sTL HAZIRLANMA SURESI:%sDK\n", i, yemekler[i].isim, yemekler[i].fiyat, yemekler[i].sure);
    }
    int kod;
siparis:
    printf("\nGeri donmek icin [0], Siparis edilecek yemek kodu: ");
    scanf("%d", &kod);
    if (kod == 0)
        return 0;
    FILE* dosya;
    dosya = fopen("C:\\veritabani\\siparisler.txt", "a"); //txt'ye ekleme yapar
    fprintf(dosya, "SIP%s_%d,2,%s,%s,%04d,%04d,%02d%02d%d,%s,AX*", kisiid, siparisidolustur(), kisiid, yemekler[kod].isim, guncelzaman(1), dakikatopla(guncelzaman(1), atoi(yemekler[kod].sure)), guncelzaman(2), guncelzaman(3), guncelzaman(4), yemekler[kod].fiyat);
    fclose(dosya);
    printf("%s siparisi basariyla alindi.\n", yemekler[kod].isim);
    goto siparis;
}

int siparisdurumu()
{
    char key;
    system("cls");
    gecmis = 0;
    listeyioku(1);
    printf("\n[g] geri don\n");
    while (getchar() != '\n');
    scanf("\n%c", &key);
    if (key == 'g') {
        return 0;
    }
}

int gecmissiparisler()
{
    char key;
    system("cls");
    gecmis = 1;
    listeyioku(1);
    printf("\n[g] geri don\n");
    scanf("\n%c", &key);
    if (key == 'g') {
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
    case 4:
        break;
    }
}
