# PROJE ACIKLAMASI
### Özet:
Bu proje restoran ve müşterileri için yemek-takip uygulamaları içerir. Toplamda üç adet uygulama vardır bunlar: Restoran.exe Müşteri.exe Mutfak.exe'dir.
Toplamda 2 adet veritabanı vardır bunlar, [siparisler.txt](https://github.com/2memory333/programming2proje#2--siparislertxt) ve [yemeklistesi.txt](https://github.com/2memory333/programming2proje#1--yemeklistesitxt)'dir.
![uygulamalar](https://github.com/2memory333/programming2proje/assets/63019122/cde705af-3bac-4f87-b97d-67d93e558580)

# Uygulamalar ve yapabildikleri

## 1-) Müşteri.exe
Bu program restorandan sipariş vermek isteyen kullanıcılar içindir. Bu programda kullanıcılar restoranın menüsünü
görüntüleyip mevcut olan yemeklerden sipariş verebilmektedir. Vermiş olduğu siparişin durumunu (onaylandı)(reddedildi)(mutfakta) ve 
siparişinin hazırlanmasına ne kadar zaman kaldığını öğrenebilmektedir. Buna ek olarak kullanıcı, daha önce verdiği siparişleri de görüntüleyebilmektedir.

## 2-) Restoran.exe
Bu program; müşteriler tarafından verilmiş siparişleri yönetip, siparişler doğrultusunda analizler yapabilip, yemekler ve siparişler üzerinde güncelleme yapabilmektedir.<br><br>
Müşteri tarafından verilen siparişlerin hepsi ilk başta onay durumundadır. Restoran.exe bu siparişlere ret/onay verir. Yapılan bu işlemler (siparisler.txt) veritabanında gerçekleşir ve
müşteri.exe programı ile bağlantı sağlanır.<br>
Restoran gerektiğinde [yemeklistesi.txt](https://github.com/2memory333/programming2proje#1--yemeklistesitxt) veritabanı üzerinde değişikler yaparak yemeklerin: mevcutluk, ad, fiyat ve tahmini hazırlanma süresi üzerinde değişiklik yapabilir.<br>
Restoran, [siparisler.txt](https://github.com/2memory333/programming2proje#2--siparislertxt) veritabanı üzerinden aldığı bilgiler doğrultusunda bir takım analizler yapabilmektedir. Bunlar: Belirli tarihte kazanç bulma, belirli ay için kazanç bulma, tarihler arasında kazanç
bulma, en çok sipariş edilen yemeği bulma, en çok sipariş veren kullanıcıyı bulma, en çok sipariş edilen tarihi bulma olarak analiz yapılabilir.

## 3-) Mutfak.exe
Bu programda aşçılar, restoran tarafından onaylanmış siparişler için görevlendirilir. Bu görevlendirme siparişler <ins>en kısa sürede bitecek şekilde</ins> yapılır. Aşçılar görevlendirildikten sonra 
her yemek için bir bitiş süresi oluşur. Bu bitiş süresi [siparisler.txt](https://github.com/2memory333/programming2proje#2--siparislertxt) kısmında yer alan aktif yemeğin tahmini bitiş süresi ile değiştirilir. Bu şekilde müşteri yemeğinin tam olarak hazır olma süresini öğrenir.

# Kullanılan bazı fonksiyonlar;
## void listeyioku(int k)
Bu fonksiyonun temel amacı; veritabanları içerisindeki [siparisler.txt](https://github.com/2memory333/programming2proje#2--siparislertxt) , [yemeklistesi.txt](https://github.com/2memory333/programming2proje#1--yemeklistesitxt) özel karakterler arasında kalan metinleri sırası ile okur. Okuduğu bu
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

## void parcalayemeklistesi(char okunanparca[])
Fonksiyonun amacı yemeklistesi.txt içerisindeki tüm verileri ilgili dizilere yükleyerek bellek içine aktarmak. Ardından bu diziler kullanılarak örneğin ekrana yazdırılarak yemek listesi görüntülenmesi sağlanır.<br><br>
Bu fonksiyon, [listeyioku](https://github.com/2memory333/programming2proje#void-listeyiokuint-k) fonksiyonu tarafından parçalanmış anlamlı metni girdi olarak alır. <br><br>
Aldığı bu metni [parcala](https://github.com/2memory333/programming2proje#char-parcalachar-metin-int-parca) fonksiyonu ile parçalayıp elde ettiği parçaları düzen ve sıra içinde dizilere yükler.<br><br>
![code](https://github.com/2memory333/programming2proje/assets/63019122/02e8ea66-6d94-40c8-a450-ae16c7aba351)

[yemeklistesi.txt](https://github.com/2memory333/programming2proje#1--yemeklistesitxt) içerisindeki bir siparişin verisine göre ilk parça bize yemeğin mevcutluğunu belirlir. Bu yüzden hazır strcmp fonksiyonu kullanılarak yemek eğer mevcut ise yani ilk parça 1 ise devam ederiz.<br><br>
Ardından tüm parçaları ilgili dizilere yükleriz.<br><br>
**index** değişkeni; okunan parçaları, dizilerin hangi elemanına yükleyeceğimizi belirtir. 

## void parcalayemeklistesi(char okunanparca[])
Fonksiyondaki amaç müşteri tarafından verilmiş tüm siparişleri filtrelemeler yaparak ekrana yazdırmaktır. <br> <br>
![ekran](https://github.com/2memory333/programming2proje/assets/63019122/970104fb-520d-4e96-8c77-763234edec13)
<br>Öncelikle siparişlerini görüntüleyecek olan müşterinin kimliği ile verilen siparişteki kimlik uyuşuyor mu diye kontrol edilir. Eğer uyuşuyorsa devam edilir.<br>
Ardından müşteri geçmiş mi yoksa mevcut siparişini mi görüntülemek istediği "geçmiş" değişkeni ile kontrol edilir. <br>



# Veritabanları (txt dosyaları)
Programların birbirleri ile bağlantı sağlayacağı önemli dosyalardır. Örneğin müşteri.exe tarafından verilen yemek siparişi onay durumunda siparisler.txt'ye yazılır.
Restoran.exe siparisler.txt'yi okuyarak bu onay durumunda olan siparişe onay verir. Ardından müşteri.exe siparisler.txt üzerinde yapılan bu değişikliği görür ve o siparişi
aktif duruma geçirir.

## 1-) yemeklistesi.txt
![siparislertxtsema](https://github.com/2memory333/programming2proje/assets/63019122/cffe1f5c-d74a-40a0-8ebb-59db4847b2c7)<br>
Restoranın sahip olduğu yemeklerin mevcutluğunu, adını, fiyatını ve hazırlanma süresini içerir.<br>
İlk parçada okunan değer yemeğin mevcut olup olmadığı, ikinci parça yemek adı, üçüncü parça restoran.exe tarafından verilmiş tahmini hazırlanma süresi son parça ise fiyat bilgisini taşır.<br>
<br>Burada her parça ',' ile ayrılarak anlamlı metin oluşturur. Anlamlı metinler ise birbirlerinden '*' karakteri ile ayrılır. <br>
Her anlamlı metin [listeyioku](https://github.com/2memory333/programming2proje#void-listeyiokuint-k) fonksiyonu ile okunur sonrasında [parcala](https://github.com/2memory333/programming2proje#char-parcalachar-metin-int-parca) fonksiyonu kullanılarak parçalar okunur.
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
Altıncı parça, kullanıcının sipariş verdiği andaki saat bilgisi ile [yemeklistesi.txt](https://github.com/2memory333/programming2proje#1--yemeklistesitxt) veritabanından okunan yemeğin tahmini yapım süresinin toplanması ile oluşur. Yemeğin o andaki <ins>tahmini bitiş süresini</ins> belirtir.
Ancak bu süre <ins>tahmini</ins> olup [mutfak.exe](https://github.com/2memory333/programming2proje#3--mutfakexe) tarafından aşçılar görevlendirildikten sonra değişebilir.<br><br>
Yedinci parça: Sipariş verildiği andaki tarih bilgisini içerir.<br><br>
Sekizinci parça: Sipariş edilen yemeğin o zamandaki fiyat bilgisini içerir.























