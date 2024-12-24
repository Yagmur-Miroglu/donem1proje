#include <stdio.h>//standart işlemler için gerekli kütüphane
#include <string.h>  //strcpy işlevi için gerekli kütüphane

// Fonksiyon saat farkını dakika cinsinden döndürür
int hesapla_dakika_farki(int saat1, int dakika1, int saat2, int dakika2) {
    return (saat2 * 60 + dakika2) - (saat1 * 60 + dakika1);
}

int main() {
    // Dosya işaretçileri
    FILE *gunlukDosya, *gecDosya, *erkenDosya;
    char sicil[10], saat[10],girisCikis;

    // Dosyalar istenilen formatta açılır
    gunlukDosya = fopen("gunluk.dat", "r");  // Dosya içindeki değerleri okumak için "okuma" formatında açılır
    gecDosya = fopen("gec.dat", "w");       // En geç kalanı yazmak için "yazma "formatında açılır
    erkenDosya = fopen("erken.dat", "w");   // En erken çıkanı yazmak için "yazma "formatında açılır

    // Dosyaların başarıyla açılıp açılmadığını kontrol edilir
    if (gunlukDosya == NULL || gecDosya == NULL || erkenDosya == NULL) {
        printf("Dosya acilamadi");
        return 1;
    }

    // Örneğimizdeki standart giriş ve çıkış saatleri
    int baslangicSaat = 9, baslangicDakika = 0; // İşe başlama saati: 09:00
    int bitisSaat = 17, bitisDakika = 0;       // İşten çıkış saati: 17:00

    // En geç kalanı ve en erken çıkanı tutan değişkenler
    char enGecSicil[10], enErkenSicil[10];
    int enGecSure = -1, enErkenSure = -1;

    // dosya sonuna gelinmediği sürece dosyadaki her satır sırayla okunur
    while (fscanf(gunlukDosya, "%s %s %c", sicil, saat, &girisCikis) != EOF) {
        int saatInt, dakikaInt;
        // Saat bilgisi SS:DD formatında ayrıştır, saat ve dakika değerlerine atanır
        sscanf(saat, "%d:%d", &saatInt, &dakikaInt);

        if (girisCikis == '<') { // Giriş kontrolü
            // Çalışanın işe geç kalma durumunu hesaplar
            int gecikme = hesapla_dakika_farki(baslangicSaat, baslangicDakika, saatInt, dakikaInt);
            if (gecikme > 0 && gecikme > enGecSure) { // Daha fazla geç kalan bulunursa
                enGecSure = gecikme;
                strcpy(enGecSicil, sicil); // Sicil numarası enGecSicil dizisine kopyalanır
            }
        } else if (girisCikis == '>') { // Çıkış kontrolü
            // Çalışanın erken çıkma durumunu hesaplar
            int erkenCikis = hesapla_dakika_farki(saatInt, dakikaInt, bitisSaat, bitisDakika);
            if (erkenCikis > 0 && (erkenCikis > enErkenSure)) { // Daha erken çıkan bulunursa
                enErkenSure = erkenCikis;
                strcpy(enErkenSicil, sicil); // Sicil numarası enGecSicil dizisine kopyalanır
            }
        }
    }

    // En geç kalanı ve en erken çıkanı dosyalara yazdır
    if (enGecSure > 0) {
        fprintf(gecDosya, "%s %d\n", enGecSicil, enGecSure);
    }
    else {
        printf("kimse gec kalmadi");
    }
    if (enErkenSure > 0) {
        fprintf(erkenDosya, "%s %d\n", enErkenSicil, enErkenSure);
    }
    else {
        printf("kimse erken cikmadi");
    }

    // Dosyaları kapat ve işlemi tamamla
    fclose(gunlukDosya);
    fclose(gecDosya);
    fclose(erkenDosya);

    printf("Islem tamamlandi.\n");
    return 0;
}
