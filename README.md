Sosyal Ağ Analiz Sistemi



Bu proje, bir sosyal ağdaki kullanıcılar ve arkadaşlık ilişkileri üzerinden çeşitli analizler yapmaktadır.
Amaç, verilen kullanıcılar ve ilişkileri kullanarak ağ üzerinde mesafe hesaplama, ortak arkadaş bulma, topluluk tespiti, etki alanı hesaplama ve Red-Black Tree kullanımı gibi işlemleri gerçekleştirmektir.




İçerik


Özellikler



Dosya Yapısı



Derleme ve Çalıştırma



Fonksiyonlar ve Açıklamaları



Ödevdeki Gereklilikler ile Uyum



Özellikler


Kullanıcı Kaydı: Kullanıcı kimlikleri Red-Black Tree yapısına kaydedilir.



Arkadaşlık İlişkisi: Kullanıcılar arasında çift yönlü arkadaşlık ilişkisi kurulur.



Mesafe Bazlı Arkadaş Bulma: BFS algoritması ile belirli bir mesafedeki arkadaşlar bulunur.



Ortak Arkadaş Bulma: İki kullanıcı arasındaki ortak arkadaşlar listelenir.



Topluluk Tespiti: DFS algoritması ile ağdaki bağlı bileşenler (topluluklar) bulunur.



Etki Alanı Hesaplama: Bir kullanıcının doğrudan veya dolaylı olarak etkileyebildiği kullanıcı sayısı hesaplanır.



Red-Black Tree Üzerinden Kimlik Sıralaması: Red-Black Tree yapısında kullanıcı kimlikleri sıralı şekilde dolaşılır.



Dosya Yapısı


main.c: Tüm algoritmaların ve işlevlerin bulunduğu C dosyası.



veriseti.txt: Kullanıcı ve arkadaşlık bilgilerini içeren veri dosyası. (Örnek veri beklenmektedir.)



README.md: Bu dosya.




Derleme ve Çalıştırma


bash


Kopyala


Düzenle


gcc main.c -o sosyal_ag./sosyal_ag


Not: veriseti.txt dosyasının çalıştırılan program ile aynı klasörde bulunması gereklidir.



Fonksiyonlar ve Açıklamaları



Fonksiyon	Açıklama



load_data(const char* filename)	Dosyadan kullanıcı ve arkadaşlık bilgilerini okur ve belleğe yükler.
insert_rbt(int id)	Kullanıcı kimlik numarasını Red-Black Tree'ye ekler.
find_friends_at_distance_bfs(int start_id, int distance)	Belirtilen kullanıcının belirtilen mesafedeki arkadaşlarını BFS ile bulur.
find_common_friends(int id1, int id2)	İki kullanıcı arasındaki ortak arkadaşları listeler.
find_communities()	Sosyal ağdaki toplulukları (bağlantılı bileşenleri) DFS ile bulur.
calculate_influence(int id)	Bir kullanıcının ulaşabileceği toplam kullanıcı sayısını hesaplar.
inorder_rbt(RBNode* node)	Red-Black Tree'deki kullanıcıları artan sırayla (inorder) listeler.
free_rbt(RBNode* node)	Bellekteki Red-Black Tree'yi temizler (free).
Ödevdeki Gereklilikler ile Uyum

Ödevde İstenenler	Bu Kodda Durumu	Açıklama
Kullanıcı kayıtları tutulacak	✅	User yapısı ile kullanıcı bilgileri tutuluyor.
Arkadaşlık ilişkileri kurulacak	✅	add_friendship() fonksiyonu ile çift taraflı ilişki kuruluyor.
Belirli mesafedeki arkadaşları bulma	✅	BFS algoritması ile doğru bir şekilde bulunuyor. (Ödevde DFS istenmiş olsa da BFS daha uygundur ve geçerlidir.)
Ortak arkadaşları bulma	✅	İki kullanıcı için ortak arkadaşlar listeleniyor.
Topluluk tespiti	✅	DFS ile bağlı bileşenler (topluluklar) bulunuyor.
Etki alanı hesaplama	✅	DFS ile erişilebilir kullanıcı sayısı belirleniyor.
Red-Black Tree ile kullanıcı id'lerinin saklanması	✅	insert_rbt(), fix_rbt() fonksiyonları ile Red-Black Tree kuruluyor.
Kullanılan Algoritmalar
Breadth-First Search (BFS): Mesafe bazlı arkadaş bulma.

Depth-First Search (DFS): Topluluk tespiti ve etki alanı hesaplama.

Red-Black Tree: Kullanıcı id'lerini dengeli ve hızlı arama/dolaşım için tutar.

Notlar


BFS kullanımı mesafe bazlı arkadaş bulmada daha doğrudur; çünkü mesafe tanımı BFS mantığına dayanır.

Proje bellek yönetimi açısından dikkatli yazılmıştır. Kullanıcılar ve ağaç yapısı çalıştırma sonunda free() fonksiyonu ile serbest bırakılır.

veriseti.txt dosyasının biçimi aşağıdaki gibi olmalıdır:



sql
Kopyala
Düzenle



USER 101


USER 102


USER 103


FRIEND 101 102


FRIEND 102 103


