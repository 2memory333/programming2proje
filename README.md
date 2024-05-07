# PROJE ACIKLAMASI
### Özet:
Bu proje restoran ve müşterileri için yemek-takip uygulamaları içerir. Toplamda üç adet uygulama vardır bunlar:
Restoran.exe
Müşteri.exe
Mutfak.exe

# Uygulamalar ve yapabildikleri

## 1-) Müşteri.exe
Bu program restorandan sipariş vermek isteyen kullanıcılar içindir. Bu programda kullanıcılar restoranın menüsünü
görüntüleyip mevcut olan yemeklerden sipariş verebilmektedir. Vermiş olduğu siparişin durumunu (onaylandı)(reddedildi)(mutfakta) ve 
siparişinin hazırlanmasına ne kadar zaman kaldığını öğrenebilmektedir. Buna ek olarak kullanıcı, daha önce verdiği siparişleri de görüntüleyebilmektedir

# Kullanılan fonksiyonlar;
## void listeyioku(int k)
Bu fonksiyonun temel amacı; veritabanları içerisindeki (siparişler.txt)(yemeklistesi.txt) özel karakterler arasında kalan metinleri sırası ile okur. Okuduğu bu
metinleri işlemek için ilgili fonksiyonlara dağıtır.

![11111](https://github.com/2memory333/programming2proje/assets/63019122/fc70f76e-b434-43fa-8194-7e13f2b76075)

buffer[100]; anlamlı metni yerleştirmek için bir dizidir.<br>
int indeks = 0; buffer dizisinin indeksini belirtir.

**1)** İlk olarak fopen fonksiyonu ile okunacak veri tabanı açılır. <br>
**2)** Sonrasında (karakter = fgetc(fileptr) ile txt'den bir karakter okunur.  while ((karakter = fgetc(fileptr)) != EOF) ile txt bitene kadar okuma yapacağımız belirtilir. <br>
**3)** Okudugumuz karakter * mı değil mi diye kontrol edilir.

**Eğer * değil ise**:<br>
okuduğumuz karakter buffer adlı dizinin indeks değişkeni ile belirtilen elemanına yazılır. Ardından indeks değişkeni
bir arttırılır. Bunun sebebi bir sonraki okunan karakterin buffer dizisinde en son eklediğimiz karakterin hemen yanına eklenmesini sağlamaktır.

**Eğer * karakterini okursak**:<br>
aradığımız anlamlı metin kısmını bulmuşuzdur demektir. Buffer dizisinin indeks elemanı '\0' olarak ayarlanır bunun sebebi artık buffer dizisinin bittiğini göstermektir.
Ardından okuduğumuz bu anlamlı metin işlenmek üzere ilgili fonksiyonlara "parcalayemeklistesi(),parcalasiparisler()" dağıtılır. Burada daha txt bitmediğinden okunacak başka anlamlı metinler de vardır. 
Bu sebeple buffer dizisinin içi boşaltılıp diğer anlamlı metinleri almak için müsait olmalıdır. Bunu hazır fonksiyon olan memset(buffer,0,100) ile yaparız. Ardından indeks değişkenini tekrardan 0 yaparız. 

## char* parcala(char metin[], int parca)
Bu fonksiyonda temel amaç verilen anlamlı metin içerisindeki özel karakter (,) ile ayrılmış parçaları bulmaktır. Fonksiyonun ilk parametresi ile anlamlı metin girdi olarak verilir, ikinci parametresinde ise kaçıncı parça bulunmak istenildiği girilir. Örneğin; <br> char anlamli_metin[100] ="merhaba,dunya,hello,world"; <br> 
Yukarıdaki diziyi, parcala(anlamli_metin,1) olarak çağırdığımızda bize merhaba kelimesini döndürür. parcala(anlamli_metin,3) olarak çağırırsak hello kelimesini döndürür. 