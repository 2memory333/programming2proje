#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int saat = 1938;
int tarih = 24142024;
int tahminiteslim = 2016;
char kisiid[16] = "434330";

char yemekadlari[20][30];
char yemekfiyatlari[20][4];
char yemeksureleri[20][4];
int dizilericinindeks = 0;
int gecmis; //gecmis veya mevcut siparislerin goruntulenmesi icin bool
int yemeksayisi = 0; //kaç tane yemek oldugunu gosterir.

//siparisler.txt parcalar
void parcalasiparisler(char okunanparca[]) {

    int i = 0;
    char* key;
    key = strtok(okunanparca, ","); //strtok fonksiyonunu kullanip okunan parcayi tanitiriz.

    if (!strcmp(key, kisiid)) { //eger okunan parcadaki id, kisiid'e esitse
        key = strtok(NULL, ",");//key'e durum atandi

        if (gecmis) { //eğer gecmis siparis goruntuleme isteniyorsa
            if (!strcmp(key, "0"))
            {
                while (key != NULL) {
                    switch (i)
                    {
                    case 0: //durum
                        printf("[GECMIS]");
                        break;
                    case 1: //yemek adi
                        printf("SIPARIS EDILMIS YEMEK:%s ", key);
                        break;
                    case 2: //saat
                        printf("SIPARIS SAATI:%s ", key);
                        break;
                    case 3: //teslim saati
                        printf("TESLIM SAATI:%s ", key);
                        break;
                    case 4:
                        printf("SIPARIS TARIHI:%s ", key); //tarih
                        break;
                    case 5:
                        printf("ODENMIS TUTAR:%s\n", key); //yemek fiyati
                        break;
                    case 6:
                        //siparis id
                        break;
                    }
                    key = strtok(NULL, ","); //null ile strtok'a daha once parcaladigi dizinin kalan kismini kullanir
                    i++;
                }
            }
        }

        if (!gecmis) { //eğer mevcut sipariş görüntüleme istenirse
            if (!strcmp(key, "1") || !strcmp(key, "2")) {
                while (key != NULL) {
                    switch (i)
                    {
                    case 0: //durum
                        if (!strcmp(key, "2"))
                            printf("[ONAY BEKLIYOR]");
                        if (!strcmp(key, "1"))
                            printf("[AKTIF SIPARIS]");
                        break;
                    case 1: //yemek adi
                        printf(" [%s]", key);
                        break;
                    case 2: //saat
                        printf(" Saat:%s", key);
                        break;
                    case 3: //tahmini teslim
                        printf(" Tahmini teslim:%s", key);
                        break;
                    case 4:
                        printf(" Tarih:%s", key); //tarih
                        break;
                    case 5:
                        printf(" Tutar:%s\n", key); //yemek fiyati
                        break;
                    case 6:
                        //siparis id
                        break;
                    }
                    key = strtok(NULL, ","); //null ile strtok'a daha once parcaladigi dizinin kalan kismini kullanir
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
    char* key;
    key = strtok(okunanparca, ","); //strtok fonksiyonunu kullanip okunan parcayi tanitiriz.

    if (strcmp(key, "0")) { //eger key 1'e eşitse yani yemek mevcutsa, parcayi okumaya baslar
        while (key != NULL) {
            switch (i)
            {
            case 0: //mevcutluk
                break;
            case 1: //yemek adi
                yemeksayisi++;
                strcpy(yemekadlari[dizilericinindeks], key);
                break;
            case 2: //fiyati
                strcpy(yemekfiyatlari[dizilericinindeks], key);
                break;
            case 3: //hazirlanma suresi
                strcpy(yemeksureleri[dizilericinindeks], key);
                break;
            }
            key = strtok(NULL, ","); //null ile strtok'a daha once parcaladigi dizinin kalan kismini kullanir
            i++;
        }
        dizilericinindeks++;
    }
}

//ilgili txt'yi okur. * * arasindaki metinleri bulup ilgili fonksiyona ayristirma icin gonderir
void listeyioku(int k) {

    FILE* fileptr;
    if (!k)
        fileptr = fopen("C:\\Users\\Efe\\Desktop\\proje\\bin\\Debug\\yemeklistesi.txt", "r");
    else
        fileptr = fopen("C:\\Users\\Efe\\Desktop\\proje\\bin\\Debug\\siparisler.txt", "r");


    if (fileptr == NULL) {
        printf("error");
    }
    char buffer[100];
    int karakter;
    int indeks = 0;
    dizilericinindeks = 0;
    while ((karakter = fgetc(fileptr)) != EOF) { //tek tek karakter oku
        if (karakter == '*') //ilgili metin okundugunda
        {
            buffer[indeks] = '\0';
            if (!k)
                parcalayemeklistesi(buffer);
            else
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

int mainsoru() {
    int key;
    printf("Ne yapmak istiyorsunuz?\n\n");
    printf("[1] yemek listesini goruntule\n[2] siparis durumunu gor\n[3] onceki siparislerine bak\n");
    scanf("%d", &key);
    return key;
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
            fprintf(dosya, "%s,2,%s,%d,%d,%d,%s*", kisiid, yemekadlari[kod], saat, tahminiteslim, tarih, yemekfiyatlari[kod]);
            fclose(dosya);
            printf("%s siparisi basariyla alindi. geri donmek icin: [1]\n", yemekadlari[kod]);
            scanf("%d", &key);
            if (key == 1)
                goto baslangic;
        }
        if (key == 2)
            goto baslangic; //geri donmek icin
        break;

    case 2: //siparis durumu
        system("cls");
        gecmis = 0;
        listeyioku(1);
        printf("\n[1] geri don\n");
        scanf("%d", &key);
        if (key == 1)
            goto baslangic;
        break;

    case 3: //geçmiş siparislerim
        system("cls");
        gecmis = 1;
        listeyioku(1);
        printf("\n[1] geri don\n");
        scanf("%d", &key);
        if (key == 1)
            goto baslangic;
        break;
    }
}
