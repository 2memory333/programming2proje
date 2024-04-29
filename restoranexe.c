#include <stdio.h>
#include <string.h>

char giris[100];
int ind = 0;
char yemekmevcutluk[30][2];
char yemekadlari[30][50];
char yemekfiyatlari[30][4];
char yemeksureleri[30][4];
int dizilericinindeks = 0;

//yemeklistesi.txt'nin parcasi okunup bu fonksiyona verildiginde o parcayi ayristirip ilgili degiskende kaydeder.
void parcalayemeklistesi(char okunanparca[]){

int i = 0;
char *key;
key = strtok(okunanparca, ","); //strtok fonksiyonunu kullanip okunan parcayi tanitiriz.

while (key != NULL){
    switch(i)
    {
    case 0: //mevcutluk
        strcpy(yemekmevcutluk[dizilericinindeks],key);
        ind++;
       break;
    case 1: //yemek adi
        strcpy(yemekadlari[dizilericinindeks],key);
        break;
    case 2: //fiyati
           strcpy(yemekfiyatlari[dizilericinindeks],key);
        break;
    case 3: //hazirlanma suresi
           strcpy(yemeksureleri[dizilericinindeks],key);
        break;
    }
    key = strtok(NULL, ","); //null ile strtok'a daha once parcaladigi dizinin kalan kismini kullanir
    i++;
    }
        dizilericinindeks++;
}

int main()
{
FILE *fileptr;
fileptr = fopen("C:\\Users\\Efe\\Desktop\\proje\\bin\\Debug\\yemeklistesi.txt","r");

if (fileptr == NULL){
    printf("error");
}
   char buffer[100];
   int karakter;
   int indeks = 0;
   while ((karakter = fgetc(fileptr)) != EOF) { //tek tek karakter oku
        if(karakter == '*') //ilgili metin kýsmý okundugunda
        {
            buffer[indeks] = '\0'; //dizinin bittiðini ifade eden karakter eklenir.
            parcalayemeklistesi(buffer);
            memset(buffer, 0, sizeof(buffer)); //bufferi resetlemek icin fonk
            indeks = 0; //buffere yazarken en basindan baslamak icin
        }
        else{
        buffer[indeks] = karakter; //okunan chari bufferin belirli indeksine yaz
        indeks++; //indeksi arttir
        }
    }
fclose(fileptr);

/*
printf("\nmevcutluk degismek icin: m-(sira kodu)-(birim)\n");
printf("yemek adi degismek icin: a-(sira kodu)-(ad)\n");
printf("yemek fiyati degismek icin: f-(sira kodu)-(birim)\n");
printf("hazirlanma suresi degismek icin: s-(sira kodu)-(birim)\n\n");

printf("yemek eklemek icin: e-(mevcutluk)-(yemek adi)-(fiyati)-(hazirlanma suresi)\n\n");
*/
int sirakodu;
while(1){

for(int i = 0; i<ind; i++){
    printf("[SIRA]:%d [MEVCUTLUK]:%s [YEMEK ADI]:%s [FIYATI]:%s [HAZIRLANMA SURESI]:%s\n",i,yemekmevcutluk[i],yemekadlari[i],yemekfiyatlari[i],yemeksureleri[i]);
}

int i = 0;
char c;
while (scanf("%c", &c) == 1 && c != '\n') {
    giris[i++] = c;
}
giris[i] = '\0';

char *key; //? neden * kullandik
key = strtok(giris, "-");

if(*key == 'm'){ //0 veya 1 olmali degilse hata verdirt
    sirakodu = atoi(strtok(NULL, "-"));
    key = strtok(NULL, "-");
    strcpy(yemekmevcutluk[sirakodu],key);
}
if(*key == 'a'){ //ad uzunsa hata ver
    sirakodu = atoi(strtok(NULL, "-"));
    key = strtok(NULL, "-");
    strcpy(yemekadlari[sirakodu],key);
}
if(*key == 'f'){ //eger fiyat harfse hata ver
    sirakodu = atoi(strtok(NULL, "-"));
    key = strtok(NULL, "-");
    strcpy(yemekfiyatlari[sirakodu],key);
}
if(*key == 's'){ //sure harfse hata ver
    sirakodu = atoi(strtok(NULL, "-"));
    key = strtok(NULL, "-");
    strcpy(yemeksureleri[sirakodu],key);
}
if(*key == 'e'){ //sure harfse hata ver
strcpy(yemekmevcutluk[ind],strtok(NULL,"-"));
strcpy(yemekadlari[ind],strtok(NULL,"-"));
strcpy(yemekfiyatlari[ind],strtok(NULL,"-"));
strcpy(yemeksureleri[ind],strtok(NULL,"-"));
ind++;
}
if(*key == 'k'){ //yemek listesini kaydeder.
    FILE *dosya;
    dosya = fopen("C:\\Users\\Efe\\Desktop\\proje\\bin\\Debug\\yemeklistesi.txt", "w");
    for(int i = 0; i<ind; i++){
    fprintf(dosya, "%s,%s,%s,%s*",yemekmevcutluk[i],yemekadlari[i],yemekfiyatlari[i],yemeksureleri[i]);
}
    fclose(dosya);
}

system("cls");
}
}

