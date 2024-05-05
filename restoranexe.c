#include <stdio.h>
#include <string.h>
#include <cstdlib>

int yemeksayisi = 0;
char yemekmevcutluk[30][2];
char yemekadlari[30][50];
char yemekfiyatlari[30][4];
char yemeksureleri[30][4];
char aranansiparisid[30] = "";
int onay;
int index = 0;

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

void degistir(char metin[], int position) {
    char siparisid[30];
    position = position - strlen(metin);
    strcpy(siparisid, parcala(metin,1));
    if (!strcmp(siparisid, aranansiparisid))
    {
        FILE* dosya;
        dosya = fopen("C:\\Users\\Efe\\Desktop\\proje\\bin\\Debug\\siparisler.txt", "r+");
        if (dosya != NULL) {
            fseek(dosya, position + strlen(siparisid), SEEK_SET);
            fprintf(dosya, "%d",onay);
            fclose(dosya);
        }
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
                if (k == 2)
                    degistir(buffer, position);
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

int mainsoru() {
    int key;
    printf("Islemler\n\n");
    printf("[1] yemek listesini guncelle\n[2] siparisleri yonet\n[3] diger\n");
    scanf("%d", &key);
    return key;
}

int main()
{
    char giris[100];
    char* key; 
    int devam;
    int sirakodu;
    listeyioku(0);   
bas:
    system("cls");
    printf("[1] Yemek Listesini Duzenle\n[2] Onay Bekleyen Siparisleri Goruntule\n[3] Diger\n\n");
    int islemkodu;
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

            if (!strcmp(key,"o")) { //siparis onaylanirsa
                key = strtok(NULL, "-");
                strcpy(aranansiparisid, key);
                onay = 1;
                listeyioku(2);
                system("cls");
                printf("%s kodlu siparis onaylandi.\n\n", aranansiparisid);
            }
            if (!strcmp(key, "r")) { //siparis reddedilirse
                key = strtok(NULL, "-");
                strcpy(aranansiparisid, key);
                onay = 3;
                listeyioku(2);
                system("cls");
                printf("%s kodlu siparis reddedildi.\n\n", aranansiparisid);
            }
        }
    }
    if (islemkodu == 3){
        system("cls");
        printf("Secebileceginiz islemler:\n");
        printf("Beliri ay icin kazanilan para [1]\n");
        printf("Beliri tarih icin kazanilan para [2]\n");
        printf("Tarihler arasi para kazanmayi goruntule [3]\n");
        printf("En kazancli gun [4]\n");
        printf("En cok siparis veren kullanici [5]\n");
        printf("En cok tercih edilen yemek [6]\n");
        printf("Calisan asci sayisini belirle [7]\n");
        printf("Yemek yapim suresini belirle [8]\n");
    }
}
