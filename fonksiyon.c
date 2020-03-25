#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "oyun.h"
	
	
	int score;		//Kullan�c�n�n toplad��� puan say�s�.
	
	int can;

	int devamMi;
	
	int puan;			//Toplam puan say�s�.
	
	int DuvarDelmeHakki;
	
	typedef struct  {int x; int y;}koordinat;		//Oyuncunun genel koordinatlar� x ve y cinsinden tan�mlad�m x s�tun say�s� y ise sat�r say�s�d�r t�pk� koordinat d�zleminde oldu�u gibi.
	// k = Oyuncunun koordinatlar� i�in.
	koordinat k;									
	// m = m�krak��n�n koordinatar�.
	koordinat m1;		
	koordinat m2;		
	koordinat m3;	
	koordinat m4;		
	// g = gulyabanilerin koordinatlar�.
	koordinat g1;		
	koordinat g2;
	koordinat g3;
	
	int a;			//a ve b gulyabani_hareket fonksiyonunda kullan�lmak �zere tan�mlanm��t�r.
	int b;
	
	//A�a��daki integer de�erler m�zrakcilar_hareket fonksiyonunda kullan�lmak �zere tan�mlanm��lard�r.
	
	int yu1; int yu2; int yu3; int yu4; 	//YUKARI
	int a1;  int a2;  int a3;  int a4;		//A�A�I
	int sa1; int sa2; int sa3; int sa4;		//SA�A
	int so1; int so2; int so3; int so4;		//SOLA

void gotoxy(int y, int x) {
    printf("%c[%d;%df", 0x1B, y+4, x+33);
}

void renklendir(int renk) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), renk);
}

void baslangic_ekrani(){
	printf("\n\n\t\t\t 1) HAREKET ETMEK ICIN YON TUSLARINI KULLANIN. \n\n\t\t\t 2) %c = OYUNCUYU TEMSIL EDER.\n\n\t\t\t 3) AMAC OLMEDEN TUM PUANLARI TOPLAMAKTIR. (PUAN => %c)\n\n\t\t\t 4) %c = MIZRAKCILARI TEMSIL EDER. \n\n\t\t\t 5) %c = TUZAKLARI TEMSIL EDER.\n\n\t\t\t 6) %c = GULYABANILERI TEMSIL EDER.\n\n\t\t\t 7) 3 DEFA DUVAR PARCALAMA HAKKINIZ VARDIR\n\n\t\t\t(PARCALAMAK ISTEDIGINIZ DUVARA DOGRU YURUYUN, DUVAR PARCALANACAKTIR.) ",OYUNCU,PUAN,MIZRAKCI,TUZAK,GULYABANI);
	printf("\n\n\t\tOyuna baslamak icin herhangi bir tusa basin...\n");
	getch();
}

void olustur(char **A){
   int i,j;
    for(i=0;i<Y_BOYUT;i++){
        for(j=0;j<X_BOYUT;j++){
                A[i][j]=BOSLUK;
        }
        printf("\n");
    }
     
    for(i=0;i<Y_BOYUT;i++){
        A[i][0]=DIS_DUVAR;
        A[i][X_BOYUT-1]=DIS_DUVAR;
    }
    
    for(i=0;i<X_BOYUT;i++){
        A[0][i]=DIS_DUVAR;
		A[Y_BOYUT-1][i]=DIS_DUVAR;
    }
     
    rastgeleEngel(A);
     
}
 
void rastgeleEngel(char **A){
    int i,j,r;
    srand(time(NULL));
    for(i=1;i<Y_BOYUT-1;i++){
        for(j=1;j<X_BOYUT-1;j++){
                r=rand()%X_BOYUT;
                if(r<X_BOYUT/4)
                    A[i][j]=DUVAR;
        }
        printf("\n");
    }
     
    for(i=1;i<Y_BOYUT-1;i++){
        for(j=1;j<X_BOYUT-1;j++){
            if(
                A[i-1][j]==DUVAR 
                    && A[i+1][j]==DUVAR 
                        && A[i][j-1]==DUVAR 
                            &&  A[i][j+1]==DUVAR )
                    A[i][j]=BOSLUK;
        }
        printf("\n");
    }
     
}

void baslangic(char **A){			//Oyuncunun ba�lang�� kordinatlar�d�r.
	k.y=1;  k.x=1;				// k.x oyuncunun x eksenindeki (ka��nc� s�tun oldu�unu) koordinat�n� belirtir,
	A[k.y][k.x]=OYUNCU;			// k.y oyuncunun y eksenindeki (ka��nc� sat�r oldu�unu) koordinat�n� belirtir.
	gotoxy(k.y,k.x);
	renklendir(14);
	printf("%c",OYUNCU);
	renklendir(7);
	
	A[k.y+1][k.x]=BOSLUK;		// Ba�lang��ta duvarlar�n i�inde s�k���p kalmamas� i�in.
	A[k.y][k.x+1]=BOSLUK;
	
	baslangic_degerleri();
		
	}

void baslangic_degerleri(){
	score=0;  can=3;  devamMi=1; DuvarDelmeHakki=3; a=1; b=1;

	//A�a��daki integer de�erler m�zrakcilar_hareket fonksiyonunda kullan�lmak �zere tan�mlanm��lard�r.
	
	yu1=1; yu2=1; yu3=1; yu4=1; 	//YUKARI
	a1=1;  a2=1;  a3=1;  a4=1;		//A�A�I
	sa1=1; sa2=1; sa3=1; sa4=1;		//SA�A
	so1=1; so2=1; so3=1; so4=1;		//SOLA
}

void yaz(char **A){
    int i,j;
    
	system("@cls||clear");
     
	printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
    printf("\t\t\t\t");
    

    system("color 03");
    
	for(i=0;i<Y_BOYUT;i++){
        for(j=0;j<X_BOYUT;j++){
            printf("%c",A[i][j]);	
			}
			printf("\n\t\t\t\t");
        }
        
    }

void puan_olustur(char **A){	
	int i,x,y;
	srand(time(NULL));
	i=0;
	while(i<15){
		x=rand()%(X_BOYUT-2)+1;		// Puan�n d�� duvarda belirmesini engellemek i�in.
		y=rand()%(Y_BOYUT-2)+1;	
		if(A[y-1][x]!=DUVAR && A[y][x-1]!=DUVAR && A[y+1][x]!=DUVAR && A[y][x+1]!=DUVAR){ //E�er puan�n d�rt bir yan� duvar de�il ise olu�tur puan�.  
			A[y][x]=PUAN;
			printf("%c",PUAN);	
			i++;
		}
	}
}
    
void puan_sayisi(char **A){
	int i,j;
	
    puan=0;
    
	for(i=0;i<Y_BOYUT;i++){
        for(j=0;j<X_BOYUT;j++){
            if(A[i][j]==PUAN){
            	puan++;
			}
        }
    }
}

void puan_renklendir(char **A){
	int i,j;
    
	for(i=0;i<Y_BOYUT;i++){
        for(j=0;j<X_BOYUT;j++){
            if(A[i][j]==PUAN){
            	gotoxy(i,j);
            	renklendir(10);
            	printf("%c",PUAN);
            	renklendir(7);
			}
        }
    }
}
	
void hareket(char **A){
	unsigned char x;
	while(devamMi==1){
			x=getch();
			if(x==72 || x==119 || x==87){                      // (yukar� tu�u) || w || W
				
				if(A[k.y-1][k.x] != DIS_DUVAR ){
				
					if(A[k.y-1][k.x] != DUVAR || DuvarDelmeHakki>0){
						
						if(A[k.y-1][k.x] == DUVAR){
						DuvarDelmeHakki--;
						gotoxy(-4,-33);  		//Haritan�n en ba��na y�nlendirilir konsolda [0][0] kordinat�na denk gelir
						renklendir(14);
						printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki); //yaz fonksiyonundaki printf in ayn�s�d�r.
						renklendir(7);
						}
					
						mizrak_hareket(A);					
						gulyabani_hareket(A);
						
						renklendir(7);	
									
						if(A[k.y-1][k.x]==PUAN){			//E�er bir sonraki gidece�i yer puan ise scora 1 ekle.
							score++;
							gotoxy(-4,-33);
							renklendir(10);
							printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
							renklendir(7);
						}
					
						if(A[k.y-1][k.x]==TUZAK || A[k.y-1][k.x]==X_MIZRAK || A[k.y-1][k.x]==Y_MIZRAK || A[k.y-1][k.x]==GULYABANI){			//E�er bir sonraki gidece�i yer TUZAK ise can� 1 eksilt.
							can--;
							gotoxy(-4,-33);
							renklendir(12);
							printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
							renklendir(7);
						}
					
						A[k.y][k.x]=BOSLUK;
						
						gotoxy(k.y,k.x);
						printf("%c",BOSLUK);
						
						A[k.y-1][k.x]=OYUNCU;
						k.y = k.y-1;
						
						gotoxy(k.y,k.x);
						renklendir(14);
						printf("%c",OYUNCU);
						
						
					}
				
				}
				
			}else
			if(x==80 || x==115 || x==83){					// (a�a�� tu�u) || s || S
				
				if(A[k.y+1][k.x] != DIS_DUVAR ){
				
					if(A[k.y+1][k.x] != DUVAR || DuvarDelmeHakki>0){
					
						if(A[k.y+1][k.x] == DUVAR){
						DuvarDelmeHakki--;
						gotoxy(-4,-33);
						renklendir(14);
						printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
						renklendir(7);
						}
					
					renklendir(12);
					
					mizrak_hareket(A);					
					gulyabani_hareket(A);
					
					renklendir(7);
					
					if(A[k.y+1][k.x]==PUAN){
						score++;
						gotoxy(-4,-33);
						renklendir(10);
						printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
						renklendir(7);
					}
				
					if(A[k.y+1][k.x]==TUZAK || A[k.y+1][k.x]==X_MIZRAK || A[k.y+1][k.x]==Y_MIZRAK || A[k.y+1][k.x]==GULYABANI){
						can--;
						gotoxy(-4,-33);
						renklendir(12);
						printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
						renklendir(7);
					}
				
					A[k.y][k.x]=BOSLUK;
					
					gotoxy(k.y,k.x);
					printf("%c",BOSLUK);
					
					A[k.y+1][k.x]=OYUNCU;
					k.y = k.y+1;
					
					gotoxy(k.y,k.x);
					renklendir(14);
					printf("%c",OYUNCU);
					
					}
					}
					
						
			}else
			if(x==77 || x==100 || x==68 ){					// (sa� tu�u) || d || D
			
				if(A[k.y][k.x+1] != DIS_DUVAR ){
					
					if(A[k.y][k.x+1] != DUVAR || DuvarDelmeHakki>0){
						
						if(A[k.y][k.x+1] == DUVAR){
						DuvarDelmeHakki--;
						gotoxy(-4,-33);
						renklendir(14);
						printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
						renklendir(7);
						}
						renklendir(12);
						
						mizrak_hareket(A);					
						gulyabani_hareket(A);
						
						renklendir(7);
					
						if(A[k.y][k.x+1]==PUAN){
							score++;
							gotoxy(-4,-33);
							renklendir(10);
							printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
							renklendir(7);
						}
						if(A[k.y][k.x+1]==TUZAK || A[k.y][k.x+1]==X_MIZRAK || A[k.y][k.x+1]==Y_MIZRAK || A[k.y][k.x+1]==GULYABANI){
							can--;
							gotoxy(-4,-33);
							renklendir(12);
							printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
							renklendir(7);
						}
						A[k.y][k.x]=BOSLUK;
						
						gotoxy(k.y,k.x);
						printf("%c",BOSLUK);
						
						A[k.y][k.x+1]=OYUNCU;
						k.x = k.x+1;
						
						gotoxy(k.y,k.x);
						renklendir(14);
						printf("%c",OYUNCU);
	
					}
			}
			}else
			if(x==75 || x==97 || x==65 ){					// (sol tu�u) || a || A
			
				if(A[k.y][k.x-1] != DIS_DUVAR ){
				
					if(A[k.y][k.x-1] != DUVAR || DuvarDelmeHakki>0){
					
						if(A[k.y][k.x-1] == DUVAR){
						DuvarDelmeHakki--;
						gotoxy(-4,-33);
						renklendir(14);
						printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
						renklendir(7);
						}
					
					renklendir(12);
					
					mizrak_hareket(A);					
					gulyabani_hareket(A);
					
					renklendir(7);
				
					if(A[k.y][k.x-1]==PUAN){
						score++;
						gotoxy(-4,-33);
						renklendir(10);
						printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
						renklendir(7);
					}
					if(A[k.y][k.x-1]==TUZAK || A[k.y][k.x-1]==X_MIZRAK || A[k.y][k.x-1]==Y_MIZRAK || A[k.y][k.x-1]==GULYABANI){
						can--;
						gotoxy(-4,-33);
						renklendir(12);
						printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
						renklendir(7);
					}
					A[k.y][k.x]=BOSLUK;
					
					gotoxy(k.y,k.x);
					printf("%c",BOSLUK);
					
					A[k.y][k.x-1]=OYUNCU;
					k.x = k.x-1;
					
					gotoxy(k.y,k.x);
					renklendir(14);
					printf("%c",OYUNCU);
	

			}
		}
				}
	bitti_mi(A);				
	}
}

void tuzak_olustur(char **A){	
	int x,y,i=1;
	srand(time(NULL));
	while(i<10){
		x=rand()%(X_BOYUT-2)+1;		// TUZAK�n d�� duvarda belirmesini engellemek i�in.
		y=rand()%(Y_BOYUT-2)+1;	
			A[y][x]=TUZAK;
			i++;	
	}
}

void tuzak_renklendir(char **A){
	int i,j;
    
	for(i=0;i<Y_BOYUT;i++){
        for(j=0;j<X_BOYUT;j++){
            if(A[i][j]==TUZAK){
            	gotoxy(i,j);
            	renklendir(12);
            	printf("%c",TUZAK);
            	renklendir(7);
			}
        }
    }
}

void mizrakci_olustur(char **A){
	
	int X,Y;
	
	X = X_BOYUT-2;  Y = Y_BOYUT-2;
	
	srand(time(NULL));
	
	m1.x=rand()%X+1;
	m1.y=rand()%Y+1;
	
	m2.x=rand()%X+1;
	m2.y=rand()%Y+1;
	
	m3.x=rand()%X+1;
	m3.y=rand()%Y+1;
	
	m4.x=rand()%X+1;
	m4.y=rand()%Y+1;
	

	
	A[m1.y][m1.x]=MIZRAKCI; A[m2.y][m2.x]=MIZRAKCI; A[m3.y][m3.x]=MIZRAKCI; A[m4.y][m4.x]=MIZRAKCI;

	
	
}

void mirakci_renklendir(char **A){
	int i,j;
    
	for(i=0;i<Y_BOYUT;i++){
        for(j=0;j<X_BOYUT;j++){
            if(A[i][j]==MIZRAKCI){
            	gotoxy(i,j);
            	renklendir(12);
            	printf("%c",MIZRAKCI);
            	renklendir(7);
			}
        }
    }
}

void mizrak_hareket(char **A){
	
	renklendir(12);
	
	///////////1.MIZRAK�I ���N/////////////////////

	
	if(A[(m1.y)-yu1][m1.x]==DUVAR || A[(m1.y)-yu1][m1.x]==DIS_DUVAR || A[(m1.y)-yu1][m1.x]==PUAN || A[(m1.y)-yu1][m1.x]==GULYABANI || A[(m1.y)-yu1][m1.x]==TUZAK || A[(m1.y)-yu1][m1.x]==MIZRAKCI || A[(m1.y)-yu1][m1.x]==X_MIZRAK || A[(m1.y)-yu1][m1.x]==Y_MIZRAK){		//bir duvarla veya puanla kar��la�t���nda d�ng�y� ba�a almas� i�in 
		
		A[(m1.y)-(yu1-1)][m1.x]=BOSLUK;  //d�ng� ba�a d�nd���nde en son olu�an m�zra��n silinmesi i�in.
		
		gotoxy((m1.y)-(yu1-1),m1.x);
		printf("%c",BOSLUK);
		
		yu1=1;
	}else{
		if(A[(m1.y)-yu1][m1.x]==OYUNCU){
			can--;
			gotoxy(-4,-33);
			printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
		}
		A[(m1.y)-yu1][m1.x]=Y_MIZRAK;		//yukar�
		
		gotoxy((m1.y)-yu1,m1.x);
		printf("%c",Y_MIZRAK);
		
		A[(m1.y)-(yu1-1)][m1.x]=BOSLUK;
		
		gotoxy((m1.y)-(yu1-1),m1.x);
		printf("%c",BOSLUK);
		
		yu1++;
	}
	
	if(A[(m1.y)+a1][m1.x]==DUVAR || A[(m1.y)+a1][m1.x]==DIS_DUVAR || A[(m1.y)+a1][m1.x]==PUAN|| A[(m1.y)+a1][m1.x]==GULYABANI || A[(m1.y)+a1][m1.x]==TUZAK || A[(m1.y)+a1][m1.x]==X_MIZRAK || A[(m1.y)+a1][m1.x]==Y_MIZRAK || A[(m1.y)+a1][m1.x]==MIZRAKCI){		//s�rekli ate�leme olsun diye.
		A[(m1.y)+(a1-1)][m1.x]=BOSLUK;
		
		gotoxy((m1.y)+(a1-1),m1.x);
		printf("%c",BOSLUK);
		
		a1=1;
	}else{
		if(A[(m1.y)+a1][m1.x]==OYUNCU){
			can--;
			gotoxy(-4,-33);
			printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
		}
		A[(m1.y)+a1][m1.x]=Y_MIZRAK;		//a�a�� 
		
		gotoxy((m1.y)+a1,m1.x);
		printf("%c",Y_MIZRAK);
		
		A[(m1.y)+(a1-1)][m1.x]=BOSLUK;	
		
		gotoxy((m1.y)+(a1-1),m1.x);
		printf("%c",BOSLUK);
		
		a1++;
	}


	if(A[m1.y][(m1.x)+sa1]==DUVAR || A[m1.y][(m1.x)+sa1]==DIS_DUVAR || A[m1.y][(m1.x)+sa1]==PUAN || A[m1.y][(m1.x)+sa1]==GULYABANI || A[m1.y][(m1.x)+sa1]==TUZAK || A[m1.y][(m1.x)+sa1]==X_MIZRAK || A[m1.y][(m1.x)+sa1]==Y_MIZRAK || A[m1.y][(m1.x)+sa1]==MIZRAKCI){		//s�rekli ate�leme olsun diye.
	
		A[m1.y][(m1.x)+(sa1-1)]=BOSLUK;
		
		gotoxy(m1.y,(m1.x)+(sa1-1));
		printf("%c",BOSLUK);
		
		sa1=1;
		
	}else{
		if(A[m1.y][(m1.x)+sa1]==OYUNCU){
			can--;
			gotoxy(-4,-33);
			printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
		}
		A[m1.y][(m1.x)+sa1]=X_MIZRAK;		//sa�a
		
		gotoxy(m1.y,(m1.x)+sa1);
		printf("%c",X_MIZRAK);
		
		A[m1.y][(m1.x)+(sa1-1)]=BOSLUK;
		
		gotoxy(m1.y,(m1.x)+(sa1-1));
		printf("%c",BOSLUK);
		
		sa1++;
	}


	if(A[m1.y][(m1.x)-so1]==DUVAR || A[m1.y][(m1.x)-so1]==DIS_DUVAR || A[m1.y][(m1.x)-so1]==PUAN || A[m1.y][(m1.x)-so1]==GULYABANI || A[m1.y][(m1.x)-so1]==TUZAK || A[m1.y][(m1.x)-so1]==X_MIZRAK || A[m1.y][(m1.x)-so1]==Y_MIZRAK || A[m1.y][(m1.x)-so1]==MIZRAKCI){		//s�rekli ate�leme olsun diye.
		A[m1.y][(m1.x)-(so1-1)]=BOSLUK;
		
		gotoxy(m1.y,(m1.x)-(so1-1));
		printf("%c",BOSLUK);
		
		so1=1;
	}else{
		if(A[m1.y][(m1.x)-so1]==OYUNCU){
			can--;
			gotoxy(-4,-33);
			printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
		}
		A[m1.y][(m1.x)-so1]=X_MIZRAK;		//sola
		
		gotoxy(m1.y,(m1.x)-so1);
		printf("%c",X_MIZRAK);
		
		A[m1.y][(m1.x)-(so1-1)]=BOSLUK;
		
		gotoxy(m1.y,(m1.x)-(so1-1));
		printf("%c",BOSLUK);
		
		so1++;
	}
	A[m1.y][m1.x]=MIZRAKCI;
	
	gotoxy(m1.y,m1.x);
	printf("%c",MIZRAKCI);
	

	

	///////////2/////////////////////
	
		if(A[(m2.y)-yu2][m2.x]==DUVAR || A[(m2.y)-yu2][m2.x]==DIS_DUVAR || A[(m2.y)-yu2][m2.x]==PUAN || A[(m2.y)-yu2][m2.x]==GULYABANI || A[(m2.y)-yu2][m2.x]==TUZAK || A[(m2.y)-yu2][m2.x]==MIZRAKCI || A[(m2.y)-yu2][m2.x]==X_MIZRAK || A[(m2.y)-yu2][m2.x]==Y_MIZRAK){		//bir duvarla veya puanla kar��la�t���nda d�ng�y� ba�a almas� i�in 
		A[(m2.y)-(yu2-1)][m2.x]=BOSLUK;  //d�ng� ba�a d�nd���nde en son olu�an m�zra��n silinmesi i�in.
		
		gotoxy((m2.y)-(yu2-1),m2.x);
		printf("%c",BOSLUK);
		
		yu2=1;
	}else{
		if(A[(m2.y)-yu2][m2.x]==OYUNCU){
			can--;
			gotoxy(-4,-33);
			printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
		}
		A[(m2.y)-yu2][m2.x]=Y_MIZRAK;		//yukar�
		
		gotoxy((m2.y)-yu2,m2.x);
		printf("%c",Y_MIZRAK);
		
		A[(m2.y)-(yu2-1)][m2.x]=BOSLUK;
		
		gotoxy((m2.y)-(yu2-1),m2.x);
		printf("%c",BOSLUK);
		
		yu2++;
	}
	
	if(A[(m2.y)+a2][m2.x]==DUVAR || A[(m2.y)+a2][m2.x]==DIS_DUVAR || A[(m2.y)+a2][m2.x]==PUAN|| A[(m2.y)+a2][m2.x]==GULYABANI || A[(m2.y)+a2][m2.x]==TUZAK || A[(m2.y)+a2][m2.x]==X_MIZRAK || A[(m2.y)+a2][m2.x]==Y_MIZRAK || A[(m2.y)+a2][m2.x]==MIZRAKCI){		//s�rekli ate�leme olsun diye.
		A[(m2.y)+(a2-1)][m2.x]=BOSLUK;
		
		gotoxy((m2.y)+(a2-1),m2.x);
		printf("%c",BOSLUK);
		
		a2=1;
	}else{
		if(A[(m2.y)+a2][m2.x]==OYUNCU){
			can--;
			gotoxy(-4,-33);
			printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
		}
		A[(m2.y)+a2][m2.x]=Y_MIZRAK;		//a�a�� 
		
		gotoxy((m2.y)+a2,m2.x);
		printf("%c",Y_MIZRAK);
		
		A[(m2.y)+(a2-1)][m2.x]=BOSLUK;	
		
		gotoxy((m2.y)+(a2-1),m2.x);
		printf("%c",BOSLUK);
		
		a2++;
	}


	if(A[m2.y][(m2.x)+sa2]==DUVAR || A[m2.y][(m2.x)+sa2]==DIS_DUVAR || A[m2.y][(m2.x)+sa2]==PUAN || A[m2.y][(m2.x)+sa2]==GULYABANI || A[m2.y][(m2.x)+sa2]==TUZAK || A[m2.y][(m2.x)+sa2]==X_MIZRAK || A[m2.y][(m2.x)+sa2]==Y_MIZRAK || A[m2.y][(m2.x)+sa2]==MIZRAKCI){		//s�rekli ate�leme olsun diye.
		A[m2.y][(m2.x)+(sa2-1)]=BOSLUK;
		
		gotoxy(m2.y,(m2.x)+(sa2-1));
		printf("%c",BOSLUK);
		
		sa2=1;
	}else{
		if(A[m2.y][(m2.x)+sa2]==OYUNCU){
			can--;
			gotoxy(-4,-33);
			printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
		}
		A[m2.y][(m2.x)+sa2]=X_MIZRAK;		//sa�a
		
		gotoxy(m2.y,(m2.x)+sa2);
		printf("%c",X_MIZRAK);
		
		A[m2.y][(m2.x)+(sa2-1)]=BOSLUK;
		
		gotoxy(m2.y,(m2.x)+(sa2-1));
		printf("%c",BOSLUK);
		
		sa2++;
	}


	if(A[m2.y][(m2.x)-so2]==DUVAR || A[m2.y][(m2.x)-so2]==DIS_DUVAR || A[m2.y][(m2.x)-so2]==PUAN || A[m2.y][(m2.x)-so2]==GULYABANI || A[m2.y][(m2.x)-so2]==TUZAK || A[m2.y][(m2.x)-so2]==X_MIZRAK || A[m2.y][(m2.x)-so2]==Y_MIZRAK || A[m2.y][(m2.x)-so2]==MIZRAKCI){		//s�rekli ate�leme olsun diye.
		A[m2.y][(m2.x)-(so2-1)]=BOSLUK;
		
		gotoxy(m2.y,(m2.x)-(so2-1));
		printf("%c",BOSLUK);
		
		so2=1;
	}else{
		if(A[m2.y][(m2.x)-so2]==OYUNCU){
			can--;
			gotoxy(-4,-33);
			printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
		}
		A[m2.y][(m2.x)-so2]=X_MIZRAK;		//sola
		
		gotoxy(m2.y,(m2.x)-so2);
		printf("%c",X_MIZRAK);
		
		A[m2.y][(m2.x)-(so2-1)]=BOSLUK;
		
		gotoxy(m2.y,(m2.x)-(so2-1));
		printf("%c",BOSLUK);
		
		so2++;
	}
	A[m2.y][m2.x]=MIZRAKCI;
	
	gotoxy(m2.y,m2.x);
	printf("%c",MIZRAKCI);




	
	///////////3/////////////////////
	
		if(A[(m3.y)-yu3][m3.x]==DUVAR || A[(m3.y)-yu3][m3.x]==DIS_DUVAR || A[(m3.y)-yu3][m3.x]==PUAN || A[(m3.y)-yu3][m3.x]==GULYABANI || A[(m3.y)-yu3][m3.x]==TUZAK || A[(m3.y)-yu3][m3.x]==MIZRAKCI || A[(m3.y)-yu3][m3.x]==X_MIZRAK || A[(m3.y)-yu3][m3.x]==Y_MIZRAK){		//bir duvarla veya puanla kar��la�t���nda d�ng�y� ba�a almas� i�in 
		A[(m3.y)-(yu3-1)][m3.x]=BOSLUK;  //d�ng� ba�a d�nd���nde en son olu�an m�zra��n silinmesi i�in.
		
		gotoxy((m3.y)-(yu3-1),m3.x);
		printf("%c",BOSLUK);
		
		yu3=1;
	}else{
		if(A[(m3.y)-yu3][m3.x]==OYUNCU){
			can--;
			gotoxy(-4,-33);
			printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
		}
		A[(m3.y)-yu3][m3.x]=Y_MIZRAK;		//yukar�
		
		gotoxy((m3.y)-yu3,m3.x);
		printf("%c",Y_MIZRAK);
		
		A[(m3.y)-(yu3-1)][m3.x]=BOSLUK;
		
		gotoxy((m3.y)-(yu3-1),m3.x);
		printf("%c",BOSLUK);
		
		yu3++;
	}
	
	if(A[(m3.y)+a3][m3.x]==DUVAR || A[(m3.y)+a3][m3.x]==DIS_DUVAR || A[(m3.y)+a3][m3.x]==PUAN|| A[(m3.y)+a3][m3.x]==GULYABANI || A[(m3.y)+a3][m3.x]==TUZAK || A[(m3.y)+a3][m3.x]==X_MIZRAK || A[(m3.y)+a3][m3.x]==Y_MIZRAK || A[(m3.y)+a3][m3.x]==MIZRAKCI){		//s�rekli ate�leme olsun diye.
		A[(m3.y)+(a3-1)][m3.x]=BOSLUK;
		
		gotoxy((m3.y)+(a3-1),m3.x);
		printf("%c",BOSLUK);
		
		a3=1;
	}else{
		if(A[(m3.y)+a3][m3.x]==OYUNCU){
			can--;
			gotoxy(-4,-33);
			printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
		}
		A[(m3.y)+a3][m3.x]=Y_MIZRAK;		//a�a�� 
		
		gotoxy((m3.y)+a3,m3.x);
		printf("%c",Y_MIZRAK);
		
		A[(m3.y)+(a3-1)][m3.x]=BOSLUK;	
		
		gotoxy((m3.y)+(a3-1),m3.x);
		printf("%c",BOSLUK);
		
		a3++;
	}


	if(A[m3.y][(m3.x)+sa3]==DUVAR || A[m3.y][(m3.x)+sa3]==DIS_DUVAR || A[m3.y][(m3.x)+sa3]==PUAN || A[m3.y][(m3.x)+sa3]==GULYABANI || A[m3.y][(m3.x)+sa3]==TUZAK || A[m3.y][(m3.x)+sa3]==X_MIZRAK || A[m3.y][(m3.x)+sa3]==Y_MIZRAK || A[m3.y][(m3.x)+sa3]==MIZRAKCI){		//s�rekli ate�leme olsun diye.
		A[m3.y][(m3.x)+(sa3-1)]=BOSLUK;
		
		gotoxy(m3.y , (m3.x)+(sa3-1));
		printf("%c",BOSLUK);
		
		sa3=1;
	}else{
		if(A[m3.y][(m3.x)+sa3]==OYUNCU){
			can--;
			gotoxy(-4,-33);
			printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
		}
		A[m3.y][(m3.x)+sa3]=X_MIZRAK;		//sa�a
		
		gotoxy(m3.y , (m3.x)+sa3);
		printf("%c",X_MIZRAK);
		
		A[m3.y][(m3.x)+(sa3-1)]=BOSLUK;
		
		gotoxy(m3.y , (m3.x)+(sa3-1));
		printf("%c",BOSLUK);
		
		sa3++;
	}


	if(A[m3.y][(m3.x)-so3]==DUVAR || A[m3.y][(m3.x)-so3]==DIS_DUVAR || A[m3.y][(m3.x)-so3]==PUAN || A[m3.y][(m3.x)-so3]==GULYABANI || A[m3.y][(m3.x)-so3]==TUZAK || A[m3.y][(m3.x)-so3]==X_MIZRAK || A[m3.y][(m3.x)-so3]==Y_MIZRAK || A[m3.y][(m3.x)-so3]==MIZRAKCI){		//s�rekli ate�leme olsun diye.
		A[m3.y][(m3.x)-(so3-1)]=BOSLUK;
		
		gotoxy(m3.y , (m3.x)-(so3-1));
		printf("%c",BOSLUK);
		
		so3=1;
	}else{
		if(A[m3.y][(m3.x)-so3]==OYUNCU){
			can--;
			gotoxy(-4,-33);
			printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
		}
		A[m3.y][(m3.x)-so3]=X_MIZRAK;		//sola
		
		gotoxy(m3.y , (m3.x)-so3);
		printf("%c",X_MIZRAK);
		
		A[m3.y][(m3.x)-(so3-1)]=BOSLUK;
		
		gotoxy(m3.y , (m3.x)-(so3-1));
		printf("%c",BOSLUK);
		
		so3++;
	}
	A[m3.y][m3.x]=MIZRAKCI;
	
	gotoxy(m3.y,m3.x);
	printf("%c",MIZRAKCI);
	

	



	
	///////////4/////////////////////
	
		if(A[(m4.y)-yu4][m4.x]==DUVAR || A[(m4.y)-yu4][m4.x]==DIS_DUVAR || A[(m4.y)-yu4][m4.x]==PUAN || A[(m4.y)-yu4][m4.x]==GULYABANI || A[(m4.y)-yu4][m4.x]==TUZAK || A[(m4.y)-yu4][m4.x]==MIZRAKCI || A[(m4.y)-yu4][m4.x]==X_MIZRAK || A[(m4.y)-yu4][m4.x]==Y_MIZRAK){		//bir duvarla veya puanla kar��la�t���nda d�ng�y� ba�a almas� i�in 
		A[(m4.y)-(yu4-1)][m4.x]=BOSLUK;  //d�ng� ba�a d�nd���nde en son olu�an m�zra��n silinmesi i�in.
		
		gotoxy((m4.y)-(yu4-1) , m4.x);
		printf("%c",BOSLUK);
		
		yu4=1;
	}else{
		if(A[(m4.y)-yu4][m4.x]==OYUNCU){
			can--;
			gotoxy(-4,-33);
			printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
		}
		A[(m4.y)-yu4][m4.x]=Y_MIZRAK;		//yukar�
		
		gotoxy((m4.y)-yu4 , m4.x);
		printf("%c",Y_MIZRAK);
		
		A[(m4.y)-(yu4-1)][m4.x]=BOSLUK;
		
		gotoxy((m4.y)-(yu4-1) , m4.x);
		printf("%c",BOSLUK);
		
		yu4++;
	}
	
	if(A[(m4.y)+a4][m4.x]==DUVAR || A[(m4.y)+a4][m4.x]==DIS_DUVAR || A[(m4.y)+a4][m4.x]==PUAN|| A[(m4.y)+a4][m4.x]==GULYABANI || A[(m4.y)+a4][m4.x]==TUZAK || A[(m4.y)+a4][m4.x]==X_MIZRAK || A[(m4.y)+a4][m4.x]==Y_MIZRAK || A[(m4.y)+a4][m4.x]==MIZRAKCI){		//s�rekli ate�leme olsun diye.
		A[(m4.y)+(a4-1)][m4.x]=BOSLUK;
		
		gotoxy((m4.y)+(a4-1) , m4.x);
		printf("%c",BOSLUK);
		
		a4=1;
	}else{
		if(A[(m4.y)+a4][m4.x]==OYUNCU){
			can--;
			gotoxy(-4,-33);
			printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
		}
		A[(m4.y)+a4][m4.x]=Y_MIZRAK;		//a�a�� 
		
		gotoxy((m4.y)+a4 , m4.x);
		printf("%c",Y_MIZRAK);
		
		A[(m4.y)+(a4-1)][m4.x]=BOSLUK;	
		
		gotoxy((m4.y)+(a4-1) , m4.x);
		printf("%c",BOSLUK);
		
		a4++;
	}


	if(A[m4.y][(m4.x)+sa4]==DUVAR || A[m4.y][(m4.x)+sa4]==DIS_DUVAR || A[m4.y][(m4.x)+sa4]==PUAN || A[m4.y][(m4.x)+sa4]==GULYABANI || A[m4.y][(m4.x)+sa4]==TUZAK || A[m4.y][(m4.x)+sa4]==X_MIZRAK || A[m4.y][(m4.x)+sa4]==Y_MIZRAK || A[m4.y][(m4.x)+sa4]==MIZRAKCI){		//s�rekli ate�leme olsun diye.
		A[m4.y][(m4.x)+(sa4-1)]=BOSLUK;
		
		gotoxy(m4.y , (m4.x)+(sa4-1));
		printf("%c",BOSLUK);
		
		sa4=1;
	}else{
		if(A[m4.y][(m4.x)+sa4]==OYUNCU){
			can--;
			gotoxy(-4,-33);
			printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
		}
		A[m4.y][(m4.x)+sa4]=X_MIZRAK;		//sa�a
		
		gotoxy(m4.y , (m4.x)+sa4);
		printf("%c",X_MIZRAK);
		
		A[m4.y][(m4.x)+(sa4-1)]=BOSLUK;
		
		gotoxy(m4.y , (m4.x)+(sa4-1));
		printf("%c",BOSLUK);
		
		sa4++;
	}


	if(A[m4.y][(m4.x)-so4]==DUVAR  || A[m4.y][(m4.x)-so4]==DIS_DUVAR|| A[m4.y][(m4.x)-so4]==PUAN || A[m4.y][(m4.x)-so4]==GULYABANI || A[m4.y][(m4.x)-so4]==TUZAK || A[m4.y][(m4.x)-so4]==X_MIZRAK || A[m4.y][(m4.x)-so4]==Y_MIZRAK || A[m4.y][(m4.x)-so4]==MIZRAKCI){		//s�rekli ate�leme olsun diye.
		A[m4.y][(m4.x)-(so4-1)]=BOSLUK;
		
		gotoxy(m4.y , (m4.x)-(so4-1));
		printf("%c",BOSLUK);
		
		so4=1;
	}else{
		if(A[m4.y][(m4.x)-so4]==OYUNCU){
			can--;
			gotoxy(-4,-33);
			printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
		}
		A[m4.y][(m4.x)-so4]=X_MIZRAK;		//sola
		
		gotoxy(m4.y , (m4.x)-so4);
		printf("%c",X_MIZRAK);
		
		A[m4.y][(m4.x)-(so4-1)]=BOSLUK;
		
		gotoxy(m4.y , (m4.x)-(so4-1));
		printf("%c",BOSLUK);
		
		so4++;
	}
	A[m4.y][m4.x]=MIZRAKCI;
	
	gotoxy(m4.y,m4.x);
	printf("%c",MIZRAKCI);
	
}

void gulyabani_olustur(char **A){
	
	int X,Y;
	
	X = X_BOYUT-2;  Y = Y_BOYUT-2;

	srand(time(NULL));
	
	while(1){
	g1.x=rand()%X+1;
	g1.y=rand()%Y+1;
	
	g2.x=rand()%X+1;
	g2.y=rand()%Y+1;
	
	if(A[g1.y][g1.x]!=MIZRAKCI && A[g2.y][g2.x]!=MIZRAKCI){
		A[g1.y][g1.x]=GULYABANI; A[g2.y][g2.x]=GULYABANI;
		break;
	}
	}
}

void gulyabaniler_renklendir(char **A){
	int i,j;
    
	for(i=0;i<Y_BOYUT;i++){
        for(j=0;j<X_BOYUT;j++){
            if(A[i][j]==GULYABANI){
            	gotoxy(i,j);
            	renklendir(12);
            	printf("%c",GULYABANI);
            	renklendir(7);
			}
        }
    }
}

void gulyabani_hareket(char **A){
	
	renklendir(12);
	
	///////////////1.GULYABAN�/////////////////

if(A[g1.y+a][g1.x]!=DUVAR && A[g1.y+a][g1.x]!=DIS_DUVAR && A[g1.y+a][g1.x]!=PUAN && A[g1.y+a][g1.x]!=TUZAK && A[g1.y+a][g1.x]!=MIZRAKCI && A[g1.y+a][g1.x]!=GULYABANI){	//engelle kar��la�ana kadar sa�a git.
		if(A[g1.y+a][g1.x]==OYUNCU){
			can--;
			gotoxy(-4,-33);
			printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
		}
		A[g1.y+a][g1.x]=GULYABANI;
		
		gotoxy(g1.y+a,g1.x);
		printf("%c",GULYABANI);
		
		A[g1.y][g1.x]=BOSLUK;
		
		gotoxy(g1.y,g1.x);
		printf("%c",BOSLUK);
		
		g1.y=g1.y+a;
	}
	if(A[g1.y+a][g1.x]==DUVAR || A[g1.y+a][g1.x]==DIS_DUVAR || A[g1.y+a][g1.x]==PUAN || A[g1.y+a][g1.x]==TUZAK || A[g1.y+a][g1.x]==MIZRAKCI || A[g1.y+a][g1.x]==GULYABANI || A[g1.y+a][g1.x]==X_MIZRAK || A[g1.y+a][g1.x]==Y_MIZRAK){
		a=a*(-1); //engelle kar��la�t�ktan sonra z�tt� y�ne gitmesi i�in.
	}
	
	
	///////////////2.GULYABAN�/////////////////

	if(A[g2.y+b][g2.x]!=DUVAR && A[g2.y+b][g2.x]!=DIS_DUVAR && A[g2.y+b][g2.x]!=PUAN && A[g2.y+b][g2.x]!=TUZAK && A[g2.y+b][g2.x]!=MIZRAKCI && A[g2.y+b][g2.x]!=GULYABANI && A[g2.y+b][g2.x]!=X_MIZRAK && A[g2.y+b][g2.x]!=Y_MIZRAK){	//engelle kar��la�ana kadar sa�a git.
		if(A[g2.y+b][g2.x]==OYUNCU){
			can--;
			gotoxy(-4,-33);
			printf("\n\t\t\t\tScore=%d/%d  Can=%d  Parcala=%d\n\n",score,puan,can,DuvarDelmeHakki);
		}
		A[g2.y+b][g2.x]=GULYABANI;
		
		gotoxy(g2.y+b,g2.x);
		printf("%c",GULYABANI);
		
		A[g2.y][g2.x]=BOSLUK;
		
		gotoxy(g2.y,g2.x);
		printf("%c",BOSLUK);
		
		g2.y=g2.y+b;
	}
	if(A[g2.y+b][g2.x]==DUVAR || A[g2.y+b][g2.x]==DIS_DUVAR || A[g2.y+b][g2.x]==PUAN || A[g2.y+b][g2.x]==TUZAK || A[g2.y+b][g2.x]==MIZRAKCI || A[g2.y+b][g2.x]==GULYABANI || A[g2.y+b][g2.x]==X_MIZRAK || A[g2.y+b][g2.x]==Y_MIZRAK){
		b=b*(-1); //engelle kar��la�t�ktan sonra z�tt� y�ne gitmesi i�in.
	}	
}

void renk_ver(char **A){
	puan_renklendir(A);
	tuzak_renklendir(A);
	mirakci_renklendir(A);
	gulyabaniler_renklendir(A);
	baslangic(A);
}

void bitti_mi(char **A){
	unsigned char x;
	while(can==0){
		system("cls");
		renklendir(12);
		printf("\n\n\n\n\t\t\t\tGAME OVER\n\n\t\t\t\tSCORE=%d\n\n\tTekrar oynamak icin T tusuna basiniz",score);
		x=getch();
		renklendir(7);
		if(x==116 || x==84){
			devamMi=0;
			can=3;
			system("cls");
		}
	}
	while(score==puan){	
		system("cls");
		renklendir(10);
		printf("\n\n\n\n\t\t\t\t$  $  $  $  $  $  $  $  $  $  $\n\n\n\n\t\t\t\t     TEBRIKLER KAZANDINIZ     \n\n\n\n\t\t\t\t$  $  $  $  $  $  $  $  $  $  $\n\n\n\tTekrar oynamak icin T tusuna basiniz");
		x=getch();
		renklendir(7);
		if(x==116 || x==84){
			devamMi=0;
			score=0;
			system("cls");
		}
	}
}

