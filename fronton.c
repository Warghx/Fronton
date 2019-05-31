#include<stdio.h>
#include<conio.h>
#include"Graphics_Console.h"


#define DX 41
#define DY 31
#define DespX 4
#define DespY 6
#define NX 33
#define NY 21
#define BRICK 219
#define PALAOFFSET 2
#define MAX_MILLORSJUGADORS 5

typedef struct
{
	int punt;
	int nom;
}TipusJugador;


void InfoPuntsPartida (HANDLE hScreen, int puntuacio);
void InfoVidesPartida(HANDLE hScreen, int vides);
void GameOver(HANDLE hScreen);
void Pausa(HANDLE hScreen);
void InitTauler(HANDLE hScreen);
void PintarPala(int PalaX, int PalaY, HANDLE hScreen);
void BorrarPala(int PalaX, int PalaY, HANDLE hScreen);
void PintarPilota(int PilotaX, int PilotaY, HANDLE hScreen);
void BorrarPilota(int PilotaX, int PilotaY, HANDLE hScreen);


int Joc(int nivell)
{
    int vides=7,puntuacio=0;
    int tecla;
	int NCops=0;
    int PalaX=(NX/2 + DespX);
    int PalaY=(NY+DespY);
    int PilotaX=(DespX+16);
    int PilotaY=(DespY+1);
	int DirPilotaY=1;
	int DirPilotaX=1;
	int Velocitat, xocpala;
	int toca=0;
    
	
    HANDLE hScreen;
    hScreen=GetStdHandle(STD_OUTPUT_HANDLE);
    InitScreen(hScreen);
    InitTauler(hScreen);
    PintarPala(PalaX, PalaY, hScreen);
    PintarPilota(PilotaX, PilotaY, hScreen);
	if (nivell==1)
		Velocitat=2000;
	if(nivell==2)
		Velocitat=1000;
	if(nivell==3)
		Velocitat=100;

	//mayor o igual q pilotax-->palax-po
    
   while(vides>0)
    {
        InfoPuntsPartida(hScreen, puntuacio);
        InfoVidesPartida(hScreen, vides);
        if(_kbhit()>0)
        {
            tecla= _getch();
        
            if (tecla==224)
            {
                tecla = _getch();
                switch(tecla)
                {
                    case 75://izquierda
                    if (PalaX>=DespX+4)
                    {
                        BorrarPala(PalaX, PalaY, hScreen);
                        PalaX--;
                        PintarPala(PalaX, PalaY, hScreen);
						if ((PalaX==8 || PalaX==33)) //para cuando llegue a los extremos no deje una parte borrada
                        {
                         InitTauler(hScreen);
                        }
                        
                    }                
                        break;

                    case 77://derecha
                    if (PalaX<=NX)
                    {
                        BorrarPala(PalaX, PalaY, hScreen);
                        PalaX++;
                        PintarPala(PalaX, PalaY, hScreen);
						if ((PalaX==8 || PalaX==33))//para cuando llegue a los extremos no deje una parte borrada
                        {
                         InitTauler(hScreen);
                        }
                        
                    }
                
                        break;   
	            }
            }
        
              else
               {
                   switch(tecla)
                    {
                        case 113://q para salir del juego
                        vides=0;
						InfoVidesPartida(hScreen,vides);
						break;

						case 81://Q para salir del juego
						vides=0;
						InfoVidesPartida(hScreen,vides);
						break;


                         case 32://barra pausa
                            Pausa(hScreen);
                        break;
  
                    }                                     
               }
	   }
		NCops++;
		if(NCops==Velocitat)
		{
			BorrarPilota(PilotaX,PilotaY,hScreen);
			xocpala = DeterminarDireccioPilota(PilotaX, PilotaY,  PalaX, PalaY, &DirPilotaX, &DirPilotaY);

			switch(toca)
		   {
				case 0:
					 PilotaX=PilotaX+DirPilotaX;
					 PilotaY=PilotaY+DirPilotaY;
					 PintarPilota(PilotaX,PilotaY,hScreen);
					 break;
				case 1:
					 PilotaX=PilotaX+DirPilotaX;
					 PilotaY=PilotaY+DirPilotaY;
				     PintarPilota(PilotaX,PilotaY,hScreen);//llamor inforvidespartida
					 puntuacio++;
						// Sumar puntuacion
					 break;
				// case -1 restar vida y pintar la pelota de nuevo y reiniciar//
				case -1:
					vides=vides-1;
					InfoVidesPartida(hScreen,vides);
					PintarPilota(PilotaX, PilotaY, hScreen);
					break;



		   }


			NCops=0;
		}
		
   }
   
   GameOver(hScreen);
        
   return (puntuacio); 
    

}
      

void InitTauler(HANDLE hScreen) //pintar tablero
 {
    int i;
    TextColor(CYAN, CYAN, hScreen);
    for(i=0;i<NX;i++)
    {
        GotoXY(DespX+i,DespY,hScreen);
        printf("%c",BRICK);
    }

    for(i=0;i<NY;i++)
    {
        GotoXY(DespX,DespY+i,hScreen);
        printf("%c",BRICK);
    }

    for(i=0;i<NY;i++)
    {
        GotoXY(NX+4,DespY+i,hScreen);
        printf("%c",BRICK);
    }
 }

void InfoPuntsPartida(HANDLE hScreen, int puntuacio) //pintar puntuacón
{
  
    TextColor(LIGHTGREY,BLACK,hScreen);
    GotoXY(DespX+2,DespY-4,hScreen);
    printf("Puntuacio: %d",puntuacio);
}

void Pausa(HANDLE hScreen) 
{
    TextColor(LIGHTGREY,BLACK,hScreen);
    GotoXY((NX+4)/2,NY/2,hScreen);
    printf("Pausa");
    _getch();
    TextColor(BLACK,BLACK,hScreen);
    GotoXY((NX+4)/2,NY/2,hScreen);
    printf("Pausa");
        
    
}

void GameOver(HANDLE hScreen)//para cuando se acaban las vidas o sales del juego on q Q
{
    TextColor(LIGHTGREY,BLACK,hScreen);
    GotoXY(NX/2,NY/2,hScreen);
    printf("GAME OVER");
    _getch();
    TextColor(BLACK,BLACK,hScreen);
    GotoXY(NX/2,NY/2,hScreen);
    printf("GAME OVER");
}
void InfoVidesPartida(HANDLE hScreen, int vides) //mostrar vidas restantes
{
  
    TextColor(LIGHTGREY,BLACK,hScreen);
    GotoXY(DespX+2,DespY-3,hScreen);
    printf("Vides: %d",vides);
}

void PintarPala(int PalaX, int PalaY, HANDLE hScreen) //moverpala
{
    int i;
    TextColor(LIGHTGREY,LIGHTGREY,hScreen);
    for(i=(PalaX-PALAOFFSET); i<=(PalaX+PALAOFFSET); i++)
	{
        GotoXY(i, 26, hScreen);
        printf("%c",BRICK);
    }
}
void BorrarPala(int PalaX, int PalaY, HANDLE hScreen)//moverpala
{
    int i;
    TextColor(BLACK,BLACK,hScreen);
    for(i=(PalaX-PALAOFFSET); i<=(PalaX+PALAOFFSET); i++)
    {
        GotoXY(i, 26, hScreen);
        printf("%c",BRICK);
    }
}    
void PintarPilota(int PilotaX, int PilotaY, HANDLE hScreen)
{
    TextColor(LIGHTGREY,LIGHTGREY,hScreen);
    GotoXY(PilotaX, PilotaY, hScreen);
    printf("%c",BRICK);
}
void BorrarPilota(int PilotaX, int PilotaY, HANDLE hScreen)
{
    TextColor(BLACK,BLACK,hScreen);
    GotoXY(PilotaX, PilotaY, hScreen);
    printf("%c",BRICK);
}

int DeterminarDireccioPilota(int PilotaX,int PilotaY,int PalaX, int PalaY,int*DirPilotaX,int*DirPilotaY)
{	
	int toca = 0;
	if(PilotaY==(DespY+1) && (*DirPilotaY == -1))//cuando toca la parte de arriba
	{
		*DirPilotaY=-*DirPilotaY;
		 toca = 0;
	}
	if(PilotaX==DespX+1)//cuando toca el lado izquierdo
	{
		*DirPilotaX=-*DirPilotaX;
	   	 toca = 0;
	}
	if(PilotaX==NX+3)//cuando toca el lado izquierdo
	{
		*DirPilotaX=-*DirPilotaX;
	   	 toca = 0;
	}

	  if(((PilotaX<PalaX-PALAOFFSET) && (PilotaX > (DespX + 2)) || (PilotaY==PalaY+PALAOFFSET)) && (PilotaY>=PalaY))//cuando toca pala
    {
        *DirPilotaY=-*DirPilotaY;
         toca= 1;
    }
    return toca;
	/*if((PilotaX==PalaX)||(PilotaX==PalaX+1)||(PilotaX==PalaX+2)||(PilotaX==PalaX-1)||(PilotaX=PalaX-2) && (PilotaY==PalaY))//cuando toca pala
	{
		*DirPilotaY=-*DirPilotaY;
		 toca= 1;
    }
	
	*/
	

}
void MenuNivellDificultat()
{	printf("------Menu Dificultat------\n");
	printf("1.-Principiant\n");
	printf("2.-Mitja\n");
	printf("3.-Expert\n");
	printf("-------------------------------\n");
}
void Menu()
{
	printf("------Menu Principal------\n");
	printf("1.-Millors Puntuacions\n");
	printf("2.-Escollir Nivell del Joc\n");
	printf("3.-Jugar al Fronton\n");
	printf("4.-Sortir\n");
	printf("----------------------\n");
}

void InicialitzarTaulaMillorJugadors(TipusJugador *T)
{
	int i;
	for (i=0;i<MAX_MILLORSJUGADORS;i++)
	{
		T[i].punt = 0;
		T[i].nom ='A';
	}
}
/*void EmplenarPosicioTaula(TMillorsJugadors[posicio],punts)
{	
int posicio;
	//

	if (posicio!=0)
	    InicialitzarTaulaMillorJugadors(TipusJugador *T)
		EmplenarPosicioTaula()

}*/
/*
void EmplenarPosicioTaula()
{
	int i;
	int posicio=-1;
	for (i=0;i<MAX_MILLORSJUGADORS;i++)
		if(T[i].punt < punt)
		{ posicio=i;
		  return(posicio);
	    }
}*/

void main()
{	
	TipusJugador TMillorsJugadors[MAX_MILLORSJUGADORS];
	char opcio; 
	int nivell=2;
	int punts=0;
	int posicio=-1;
	HANDLE hScreen;

	hScreen=GetStdHandle(STD_OUTPUT_HANDLE);//Declaremlapantalla//
	InitScreen(hScreen);//Inizialitzarllavorperalafunciórand()//
	srand((unsigned)time(NULL));
	InicialitzarTaulaMillorJugadors(TMillorsJugadors);
	do
	{
		system("cls");
		MenuPrincipal();
		opcio=_getch();
		switch (opcio){
		 case 49:
				system("cls");
				EscriureRanking(TMillorsJugadors);
				printf("Prem una tecla per tornar al menu principal");
				_getch();
				break;
		 case 50:
				do
				{
				system("cls");
				MenuNivellDificultat();
				scanf("%d",&nivell);
				}
				while((nivell!=1)&&(nivell!=2)&&(nivell!=3));
				break;
	     case 51:
			system("cls");
			punts=Joc(nivell);
			system("cls");
					//FemlacridadelFrontolipassemelniveliretornapunts
					//ComprovemsiesunTop5retornalaposicióonenelranking
					//Esinohoes
			posicio=ComprovarSiEsTop5(TMillorsJugadors, punts);
		if (posicio>=0) 
		{
				DesplacarArray(TMillorsJugadors,posicio);
				EmplenarPosicioTaula(&TMillorsJugadors[posicio],punts);
		}
		break;
	}
	}while (opcio!=52);
}