#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char kisiid[16] = "434330";
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

    // Þu anki zamaný al
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

    char okunandurum[2];
    int i = 0;
    char* okunan;
    okunan = strtok(okunanparca, ","); //strtok fonksiyonunu kullanip okunan parcayi tanitiriz, ilk bolum alinir yani siparisid
    okunan = strtok(NULL, ",");    // durum atanýr
    strcpy(okunandurum, okunan);
    okunan = strtok(NULL, ","); //kisiid atanýr
    if (!strcmp(okunan, kisiid)) { //eger okunan parcadaki id, kisiid'e esitse
        if (gecmis) { //eðer gecmis siparis goruntuleme isteniyorsa
            if (!strcmp(okunandurum, "0"))
            {
                while (okunan != NULL) {
                    switch (i)
                    {
                    case 0: //durum
                        printf("[GECMIS]");
                        break;

                    case 1: //yemek adi
                        printf("SIPARIS EDILMIS YEMEK:%s ", okunan);
                        break;

                    case 2: //saat
                        printf("SIPARIS SAATI:%s ", okunan);
                        break;

                    case 3: //teslim saati
                        printf("TESLIM SAATI:%s ", okunan);
                        break;

                    case 4:
                        strcpy(okunantarih, okunan);
                        printf("SIPARIS TARIHI:%s ", okunan); //tarih
                        break;

                    case 5:
                        printf("ODENMIS TUTAR:%s\n", okunan); //yemek fiyati
                        break;

                        /*case 6:
                            strcpy(okunanID,(okunantarih,kisiid));
                            printf("SIP%s_00%s",okunantarih,siparisidolustur);
                            break;*/
                    }
                    okunan = strtok(NULL, ","); //null ile strtok'a daha once parcaladigi dizinin kalan kismini kullanir
                    i++;
                }
            }
        }

        if (!gecmis) { //eðer mevcut sipariþ görüntüleme istenirse
            if (!strcmp(okunandurum, "1") || !strcmp(okunandurum, "2")) {
                while (okunan != NULL) {
                    switch (i)
                    {
                    case 0: //durum
                        if (!strcmp(okunandurum, "2")) {
                            printf("[ONAY BEKLIYOR]");
                        }
                        if (!strcmp(okunandurum, "1")) {
                            printf("[AKTIF SIPARIS]");
                        }
                        break;

                    case 1: //yemek adi
                        printf(" Yemek:%s", okunan);
                        break;

                    case 2: //saat
                        printf(" Saat:%s", okunan);
                        break;

                    case 3: //tahmini teslim
                        printf(" Tahmini teslim:%s", okunan);
                        break;

                    case 4:
                        strcpy(okunantarih, okunan);
                        printf(" Tarih:%s", okunan); //tarih
                        break;

                    case 5:
                        printf(" Tutar:%s\n", okunan); //yemek fiyati
                        break;

                        /*case 6:
                            strcpy(okunanID,(okunantarih,kisiid));
                            printf("SIP%s_00%s",okunantarih,siparisidolustur);
                            break;*/
                    }
                    okunan = strtok(NULL, ","); //null ile strtok'a daha once parcaladigi dizinin kalan kismini kullanir
                    i++;
                }
            }
        }
    }
}

//yemeklistesi.txt'nin parcasi okunup bu fonksiyona verildiginde o parcayi ayristirip ilgili degiskende kaydeder.
void parcalayemeklistesi(char okunanparca[]) {

    //verilen txt'de her * * arasindaki metini okuyup ilgili fonksiyonlara dagitir.
    int i = 0;
    char* okunan;
    okunan = strtok(okunanparca, ","); //strtok fonksiyonunu kullanip okunan parcayi tanitiriz.

    if (strcmp(okunan, "0")) { //eger key 1'e eþitse yani yemek mevcutsa, parcayi okumaya baslar
        while (okunan != NULL) {
            switch (i)
            {
            case 0: //mevcutluk
                break;

            case 1: //yemek adi
                yemeksayisi++;
                strcpy(yemekadlari[index], okunan);
                break;

            case 2: //fiyati
                strcpy(yemekfiyatlari[index], okunan);
                break;

            case 3: //hazirlanma suresi
                strcpy(yemeksureleri[index], okunan);
                break;
            }
            okunan = strtok(NULL, ","); //null ile strtok'a daha once parcaladigi dizinin kalan kismini kullanir
            i++;
        }
        index++;
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
    index = 0;
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
    printf("\n[1] siparis ver \n[2] geri don\n");
    scanf("%d", &key);

    if (key == 1) {
        int kod;
        printf("Siparis edilcek yemek kodu: ");
        scanf("%d", &kod);
        FILE* dosya;
        dosya = fopen("C:\\Users\\Efe\\Desktop\\proje\\bin\\Debug\\siparisler.txt", "a"); //txt'ye ekleme yapar

        fprintf(dosya, "SIP%d_%d,2,%s,%s,%04d,%04d,%02d%02d%d,%s*", guncelzaman(4), siparisidolustur(kisiid), kisiid, yemekadlari[kod], guncelzaman(1), dakikatopla(guncelzaman(1), atoi(yemeksureleri[kod])), guncelzaman(2), guncelzaman(3), guncelzaman(4), yemekfiyatlari[kod]);
        fclose(dosya);
        printf("%s siparisi basariyla alindi. geri donmek icin: [1]\n", yemekadlari[kod]);
        scanf("%d", &key);

        if (key == 1) {
            return key;
        }
    }

    if (key == 2) {
        return key; //geri donmek icin
    }
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
        return key;
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
        return key;
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
        if (key == 2) {
            goto baslangic;
        }
        /*siparisolustur();*/
        else if (key == 1) {
            if (key == 1) {
                goto baslangic;
            }
        }

        break;

    case 2: //siparis durumu
        key = siparisdurumu();
        if (key == 1) {
            goto baslangic;
        }
        break;

    case 3: //geçmiþ siparislerim
        key = gecmissiparisler();
        if (key == 1) {
            goto baslangic;
        }
        break;
    }
}
