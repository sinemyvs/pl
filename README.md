## GİRİŞ
Bu projenin amacı, C dilinde kullanılan kodların zaman ve yer karmaşıklığının hesaplaması
amaçlanmaktadır.
      
## YÖNTEM
Projemizi Windows işletim sistemi üzerinde, CodeBlocks IDE üzerindegeliştirdik
Bu programdaki amaca ulaşmak için ilk olarak dosyadaki kodlar kelime ve karakterlere ayrılır.
İkinci olarak kelime karakter ve boşluk kombinasyonları çözülüp kod parçacıklarını bulup türleri belirtilir.
Ve son olarak da ayırtmalar kullanılarak time(n) , Space(n) ve O(n) bulur.
yer karmaşıklığı (space(n)) :
yer karmaşıklığı için tanımlayıcı elemanlara bakılır(int, char ,double gibi).mesela [ int i;  S(n) = 1'dir ] [ char x[n][n] ;  S(n) = n^2'dir].
Zaman karmaşıklığı(time(n)) :
zaman karmaşıklığını bulmak için de döngü elemanları(for ,while ,do) ve iç içe fonksiyonlara bakılır. İç içe ise [a^n ] gönderilir, döngü ise [ n^a ]gönderir.

## FONKSİYON KISITLARI
Bu kod switch case,struct yapıları için çalışmıyor. Ve for while if gibi elemanlarda süslü parantez kullanılmalı.

## SONUÇ
Alan karmaşıklığı yazdığınız algoritma bellekten ne kadar yer kullanıyor, zaman karmaşıklığı ise yazdığınız algoritmanın çalışma süresini ifade eder. Algoritma analizine neden ihtiyaç duyarız çünkü yazdığımız algoritmanın performansını bilmek isteriz, farklı algoritmalarla karşılaştırmak isteriz ve daha iyisi mümkün mü sorusuna ancak analiz yaparak cevap verebiliriz.
Bir algoritma çalışmasını bitirene kadar geçen süre yürütme zamanı olarak adlandırılır. Ve algoritmada genelde eleman sayısı n olarak gösterilir ve yürütme zamanı da T(n) ile ifade edilir. Algoritmadaki eleman sayısı çok fazla olduğunda yürütme zamanı, zaman karmaşıklığı olarak adlandırılır.
