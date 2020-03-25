#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "fonksiyon.c"

int main(){

	char **A;
	int i;
   
    tekrarla :
    	
		
	    A = (char**) malloc(Y_BOYUT * sizeof(char*));
	    for(i=0;i<Y_BOYUT;i++){
	    	A[i] = malloc(X_BOYUT * sizeof(char));
		}
	    
	
	    
	    baslangic_ekrani();
	    
	    olustur(A);
	     
		baslangic(A);
		
		puan_olustur(A);
		
		tuzak_olustur(A);
		
		mizrakci_olustur(A);
		
		gulyabani_olustur(A);
		
		puan_sayisi(A);
	    
		yaz(A);
		
		baslangic(A);
		
		renk_ver(A);
		
		hareket(A);
		
		//printf("ne demek kakakakakakaakkaka");
		//getch();
		free(A);
		
	goto tekrarla;
		
	return 0;
}
