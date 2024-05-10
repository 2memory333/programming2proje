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
Bu fonksiyonda temel amaç verilen anlamlı metin içerisindeki özel karakter (,) ile ayrılmış parçaları bulmaktır. Fonksiyonun ilk parametresi ile anlamlı metin girdi olarak verilir, ikinci parametresinde ise kaçıncı parça bulunmak istenildiği girilir.<br> **Örneğin:** <br> char anlamli_metin[100] ="merhaba,dunya,hello,world"; <br> 
Yukarıdaki diziyi, parcala(anlamli_metin,1) olarak çağırdığımızda bize <ins>merhaba</ins> kelimesini döndürür. <br> parcala(anlamli_metin,3) olarak çağırırsak <ins>hello</ins> kelimesini döndürür. 

# Veritabanları (txt dosyaları)
## 1-) yemeklistesi.txt
![siparislertxtsema](https://github.com/2memory333/programming2proje/assets/63019122/cffe1f5c-d74a-40a0-8ebb-59db4847b2c7)<br>
Restoranın sahip olduğu yemeklerin mevcutluğunu, adını, fiyatını ve hazırlanma süresini içerir.<br>
İlk parçada okunan değer yemeğin mevcut olup olmadığı, ikinci parça yemek adı, üçüncü parça restoran.exe tarafından verilmiş tahmini hazırlanma süresi son parça ise fiyat bilgisini taşır.<br>
<br>Burada her parça ',' ile ayrılarak anlamlı metin oluşturur. Anlamlı metinler ise birbirlerinden '*' karakteri ile ayrılır. <br>
Her anlamlı metin [listeyioku](https://github.com/2memory333/programming2proje?tab=readme-ov-file#void-listeyiokuint-k) fonksiyonu ile okunur sonrasında [parcala](https://github.com/2memory333/programming2proje?tab=readme-ov-file#char-parcalachar-metin-int-parca) fonksiyonu kullanılarak parçalar okunur.
## 2-) siparisler.txt
![siparislertxtsema](https://github.com/2memory333/programming2proje/assets/63019122/c9c4d22d-cf99-427a-9d16-928764c2d29e) Müşteriler tarafından verilmiş tüm siparişlerin kayıtlarının tutulduğu veritabanıdır. <br>
İlk parça, her kullanıcının verdiği her bir sipariş için benzersiz rastgele bir şekilde oluşan kimlik numarasıdır. <br><br>
İkinci parça sipariş kayıdının türünü olduğunu gösterir. Eğer bu parça <br>
0 ise: Siparişin geçmiş zamanda yapılmış ve bitmiş olduğunu gösterir. <br>
1 ise: Siparişin restoran tarafından onaylanmış, o andaki aktif sipariş olduğunu belirtir. <br>
2 ise: Siparişin müşteri tarafından verildiği ancak henüz restoran tarafından onaylanmadığını belirtir. <br>
3 ise: Siparişin restoran tarafından reddedildiğini belirtir. <br><br>
Üçüncü parça, siparişi yapan kullanıcının kimlik numarasını belirtir.<br><br>
Döndüncü parça, sipariş edilen yemeği belirtir.<br><br>
Beşinci parça, kullanıcının sipariş verdiği andaki saati belirtir.<br><br>
Altıncı parça, kullanıcının sipariş verdiği andaki saat bilgisi ile ([yemeklistesi.txt](https://github.com/2memory333/programming2proje?tab=readme-ov-file#yemeklistesi-txt)) veritabanından okunan yemeğin tahmini yapım süresinin toplanması ile oluşur. Yemeğin o andaki <ins>tahmini bitiş süresini</ins> belirtir.
Ancak bu süre <ins>tahmini</ins> olup (mutfak.exe) tarafından aşçılar görevlendirildikten sonra değişebilir.<br><br>
Yedinci parça: Sipariş verildiği andaki tarih bilgisini içerir.<br><br>
Sekizinci parça: Sipariş edilen yemeğin o zamandaki fiyat bilgisini içerir.























