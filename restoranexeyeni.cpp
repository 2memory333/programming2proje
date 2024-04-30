#include <stdio.h>
#include <string.h>
#include <cstdlib>


char giris[100];
int yemeksayisi = 0;
char yemekmevcutluk[30][2];
char yemekadlari[30][50];
char yemekfiyatlari[30][4];
char yemeksureleri[30][4];
int dizilericinindeks = 0;

//yemeklistesi.txt'nin parcasi okunup bu fonksiyona verildiginde o parcayi ayristirip ilgili degiskende kaydeder.
void parcalayemeklistesi(char okunanparca[]) {
    int i = 0;
    char* key;
    key = strtok(okunanparca, ","); //strtok fonksiyonunu kullanip okunan parcayi tanitiriz.

    while (key != NULL) {
        switch (i)
        {
        case 0: //mevcutluk
            strcpy(yemekmevcutluk[dizilericinindeks], key);
            yemeksayisi++;
            break;
        case 1: //yemek adi
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

//siparisler.txt parcalar
void parcalasiparisler(char okunanparca[]) {
    char kisiid[16];
    char siparisid[16];
    int i = 0;
    char* key;
    key = strtok(okunanparca, ","); //strtok fonksiyonunu kullanip okunan parcayi tanitiriz, ilk parcadan siparisid
    strcpy(siparisid, key);
    key = strtok(NULL, ","); //kisi id tanitilir
    strcpy(kisiid, key);
    key = strtok(NULL, ",");//key'e durum atandi
            if (!strcmp(key, "2")) //siparis onay durumunda ise
            {
                while (key != NULL) {
                    switch (i)
                    {
                    case 0: //durum
                        printf("[SIP_%s] [ONAY BEKLIYOR] ",siparisid);
                        printf("KULLANICI:%s ", kisiid);
                        break;
                    case 1: //yemek adi
                        printf("YEMEK:%s ", key);
                        break;
                    case 2: //saat
                        printf("SAAT:%s ", key);
                        break;
                    case 3: //teslim saati
                        printf("TAHMINI TESLIM SAATI:%s ", key);
                        break;
                    case 4:
                        printf("SIPARIS TARIHI:%s ", key); //tarih
                        break;
                    case 5:
                        printf("ODENMIS TUTAR:%s\n", key); //yemek fiyati
                        break;
                    }
                    key = strtok(NULL, ","); //null ile strtok'a daha once parcaladigi dizinin kalan kismini kullanir
                    i++;
                }
            }
        }

void siparisonay() {

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
    printf("Islemler\n\n");
    printf("[1] yemek listesini guncelle\n[2] siparisleri yonet\n[3] diger\n");
    scanf("%d", &key);
    return key;
}

int main()
{
    char sipariskodu[12];
    int devam;
    int sirakodu;
    listeyioku(0);   
bas:
    system("cls");
    printf("[1] Yemek Listesini Duzenle\n[2] Siparisleri Goruntule\n[3] Diger\n\n");
    int islemkodu;
    scanf("%d", &islemkodu);
    while (getchar() != '\n'); //ustteki scanf cagrisindan kalan karakterleri temizlemek icin
    if (islemkodu == 1) {
        devam = 1;
        while (devam) {
            system("cls");;
            for (int i = 0; i < yemeksayisi; i++) {
                printf("[SIRA]:%d [MEVCUTLUK]:%s [YEMEK ADI]:%s [FIYATI]:%s [HAZIRLANMA SURESI]:%s\n", i, yemekmevcutluk[i], yemekadlari[i], yemekfiyatlari[i], yemeksureleri[i]);
            }
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
            char* key; //? neden * kullandik
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
        listeyioku(1);
        printf("\nOnaylamak istediginiz siparis kodunu giriniz: ");
        scanf("%s", sipariskodu);
        printf("\n%s kodlu siparis onaylandi.",sipariskodu);
    }
    if (islemkodu == 3){
    }
}
