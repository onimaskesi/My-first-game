#define X_BOYUT 40
#define Y_BOYUT 20
#define DUVAR 'O'
#define DIS_DUVAR '0'  //DI� DUVAR
#define BOSLUK ' '
#define OYUNCU 'E'
#define TUZAK '#'
#define PUAN '$'
#define X_MIZRAK '-'	//YATAYDAK� MIZRAKLAR
#define Y_MIZRAK '|'	//D�KEYDEK� MIZRAKLAR
#define MIZRAKCI 'M'
#define GULYABANI 'G'	//DOLA�AN YARATIKLAR
 
void olustur(char **A);
void rastgeleEngel(char **A);
void yaz(char **A);
void hareket(char **A);
void tuzak_olustur(char **A);
void puan_olustur(char **A);
void hareket(char **A);
void bitti_mi(char **A);
void mizrak_hareket(char **A);
void mzrakci_olustur(char **A);
void duvar_del(char **A, unsigned char x);
void baslangic_ekrani();
void gulyabani_hareket(char **A);
void baslangic_degerleri();
