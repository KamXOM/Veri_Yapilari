#include <iostream>
#include <string>

using namespace std;

// Ürün yapısı
struct Urun {
    int barkod;
    string isim;
};

// Bağlı liste düğümü
struct Dugum {
    Urun urun;
    Dugum* sonraki;
};

// Bağlı liste sınıfı
class LinkedList {
private:
    Dugum* bas;

public:
    LinkedList() : bas(nullptr){}

    // Ürün ekleme
    void ekleUrun(const string& isim,int kategori) {
        int enBuyukBarkod = 0;
        Dugum* gecici = bas;
        while (gecici) {
            if ((gecici->urun.barkod / 100) == kategori) {
                if (gecici->urun.barkod > enBuyukBarkod) {
                    enBuyukBarkod = gecici->urun.barkod;
                }
            }
            gecici = gecici->sonraki;
        }
        int yeniBarkod = (kategori * 100) + ((enBuyukBarkod % 100) + 1);
        Dugum* yeniDugum = new Dugum;
        yeniDugum->urun.barkod = yeniBarkod;
        yeniDugum->urun.isim = isim;
        Dugum* onceki = nullptr;
        gecici = bas;
        while (gecici && gecici->urun.barkod < yeniBarkod) {
            onceki = gecici;
            gecici = gecici->sonraki;
        }
        if (onceki == nullptr) {
            // Yeni ürün en başa ekleniyo
            bas = yeniDugum;
            yeniDugum->sonraki = gecici;
        } else {
            // Yeni ürün, önceki ve gecici düğümler arasına ekleniyo
            onceki->sonraki = yeniDugum;
            yeniDugum->sonraki = gecici;
        }
    }

    // Ürün silme
    void urunKaldir(int barkod) {
        if (!bas)
            return;
        if (bas->urun.barkod == barkod) {
            Dugum* oylesine = bas;
            bas = bas->sonraki;
            delete oylesine;
            return;
        }
        Dugum* once = nullptr;
        Dugum* anlik = bas;
        while (anlik && anlik->urun.barkod != barkod) {
            once = anlik;
            anlik = anlik->sonraki;
        }
        if (!anlik)
            return;
        once->sonraki = anlik->sonraki;
        delete anlik;
    }

    // Ürünleri listeleme
    void urunListele() {
        Dugum* oylesine = bas;
        while (oylesine) {
            cout << oylesine->urun.barkod << "\t" << oylesine->urun.isim << endl;
            oylesine = oylesine->sonraki;
        }
    }

    // Bağlı listede ürünü barkod numarasına göre bulma
    Urun* urunBul(int barkod) {
        Dugum* oylesine = bas;
        while (oylesine) {
            if (oylesine->urun.barkod == barkod) {
                return &(oylesine->urun); // Ürünü bulunduğu düğümün adresiyle döndür
            }
        oylesine = oylesine->sonraki;
        }
    return nullptr; // Ürünü bulamadıysa nullptr döndür
    }
};

// Kuyruk sınıfı
class Kuyruk {
private:
    struct kuyrukDugum {
        int musteriNo; // Müşteri kimliği veya sıra numarası
        kuyrukDugum* sonraki;
    };

    kuyrukDugum* onu;
    kuyrukDugum* arka;
    int siradakiMusteriNo;

public:
    Kuyruk() : onu(nullptr), arka(nullptr), siradakiMusteriNo(1)  {}

    // Müşteri eklemek
    void ekleKuyruk() {
        kuyrukDugum* yeniDugum = new kuyrukDugum;
        yeniDugum->musteriNo = siradakiMusteriNo++;
        yeniDugum->sonraki = nullptr;

        if (!onu) {
            onu = yeniDugum;
            arka = yeniDugum;
        } else {
            arka->sonraki = yeniDugum;
            arka = yeniDugum;
        }
    }

    // Müşteri çıkarmak
    void cikarKuyruk() {
        if (!onu)
            return;

        kuyrukDugum* oylesine = onu;
        onu = onu->sonraki;
        delete oylesine;

        if (!onu)
            arka = nullptr;
    }

    // Kuyruğu listeleme
    void bakKuyruk() {
        kuyrukDugum* oylesine = onu;
        while (oylesine) {
            cout << oylesine->musteriNo << " ";
            oylesine = oylesine->sonraki;
        }
        cout << endl;
    }
};

// Yığın sınıfı
class Yigin {
private:
    struct YiginDugum {
        Urun urun;
        YiginDugum* sonraki;
    };

    YiginDugum* ust;

public:
    Yigin() : ust(nullptr) {}

    // Ürün ekleme
    void urunEkle(int barkod, const string& isim) {
        Urun yeniUrun{barkod, isim};
        YiginDugum* yeniDugum = new YiginDugum{yeniUrun, ust};
        ust = yeniDugum;
    }

    // Ürün çıkarma
    void urunCikar() {
        if (!ust) {
            cout << "Sepet bos. Urun cikarilamaz.\n";
            return;
        }
        YiginDugum* silinecek = ust;
        ust = ust->sonraki;
        delete silinecek;
    }

    // Ürün listeleme
    void urunListele() {
        YiginDugum* iter = ust;
        while (iter) {
            cout << iter->urun.barkod << "\t" << iter->urun.isim << endl;
            iter = iter->sonraki;
        }
    }
};

int main() {
    // Market ürünleri ve kuyruk oluşturma
    LinkedList urunListe;
    Kuyruk musteriKuyruk;
    Yigin musteriSepeti;

    // Ürünleri eklemece
    urunListe.ekleUrun("Ekmek",1);
    urunListe.ekleUrun("Su",1);
    urunListe.ekleUrun("Pirinc",1);
    urunListe.ekleUrun("Domates",1);
    urunListe.ekleUrun("Sabun",2);
    urunListe.ekleUrun("Sampuan",2);
    urunListe.ekleUrun("Camasir Suyu",2);
    urunListe.ekleUrun("Pil",3);
    urunListe.ekleUrun("Ampul",3);
    urunListe.ekleUrun("Usb",3);

    // Müşteri kuyruğuna müşterileri eklemece
    for(int i=0;i<5;i++){
        musteriKuyruk.ekleKuyruk();
    }

    int secim;
    do {
        cout << "\n1. Yeni urun ekle\n";
        cout << "2. Yeni musteri ekle\n";
        cout << "3. Musteri sepetine urun ekle\n";
        cout << "4. Urun cikar\n";
        cout << "5. Kuyruktan musteri cikar\n";
        cout << "6. Musteri sepetinden urun cikar\n";
        cout << "7. Urunleri listele\n";
        cout << "8. Kuyrugu listele\n";
        cout << "9. Musteri sepetini listele\n";
        cout << "0. Cikis\n";
        cout << "Seciminizi yapin: ";
        cin >> secim;

        switch (secim) {
            case 1: {
                int kategori;
                string isim;
                cout << "Yeni urunun kategorisini girin. (1-Yiyecek\t2-Temizlik\t3-Ev Araclari):";
                cin >> kategori;
                cout << "Yeni urunun ismini girin: ";
                cin.ignore();
                getline(cin, isim);
                switch (kategori) {
                    case 1: // Yiyecek kategorisi
                        urunListe.ekleUrun(isim,1);
                        break;
                    case 2: // Temizlik kategorisi
                        urunListe.ekleUrun(isim,2);
                        break;
                    case 3: // Ev araçları kategorisi
                        urunListe.ekleUrun(isim,3);
                        break;
                    default:
                        cout << "Gecersiz kategori!\n";
                        break;
                }
                break;
            }
            case 2: {
                cout << "Musteri eklendi.\n";
                musteriKuyruk.ekleKuyruk();
                break;
            }
            case 3: {
                int barkod;
                string isim;
                cout << "Sepete eklemek istediginiz urunun barkodunu girin: ";
                cin >> barkod;
                Urun* urun = urunListe.urunBul(barkod); // Urun, urunListe'deki aranan ürünün adresini tutar
                if (urun) {
                    musteriSepeti.urunEkle(barkod, urun->isim);
                    cout << "Urun sepete eklendi.\n";
                } else {
                    cout << "Boyle bir urun bulunmamaktadir.\n";
                }
                break;
            }
            case 4: {
                int barkod;
                cout << "Hangi barkod no'lu urun kaldirilsin?\n";
                cin >> barkod;
                urunListe.urunKaldir(barkod);
                cout << "Urun cikarildi.\n";
                break;
            }
            case 5: {
                cout << "Musteri cikartildi.\n";
                musteriKuyruk.cikarKuyruk();
                break;
            }
            case 6: {
                cout << "Sepetten urun cikartildi.\n";
                musteriSepeti.urunCikar();
                break;
            }
            case 7: {
                cout << "Market Urunleri:" << endl;
                urunListe.urunListele();
                cout << endl;
                break;
            }
            case 8: {
                cout << "Kasa Onundeki Sira:" << endl;
                musteriKuyruk.bakKuyruk();
                cout << endl;
                break;
            }
            case 9: {
                cout << "Musteri Sepeti:" << endl;
                musteriSepeti.urunListele();
                cout << endl;
                break;
            }
            case 0:
                cout << "Programdan cikiliyor.\n";
                break;
            default:
                cout << "Gecersiz secim!\n";
                break;
        }
    } while (secim != 0);

    return 0;
}

                        // Ahmet Onur MALAY 222803031 
                        // 2.Sınıf Yazılım Mühendisliği 2.Öğretim