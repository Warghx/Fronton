#include "Graphics_Console.h"

void GotoXY(int x,int y,HANDLE screen)
{
 COORD position = { x, y };
 SetConsoleCursorPosition(screen,position);
}

//===================================================================================
// NOM: TextColor
//===================================================================================
// DESCRIPCIÓ: Funcio per canviar els colors de texte i fons de la consola DOS
//===================================================================================
void TextColor(int frontcolor,int backgroundcolor,HANDLE screen)
{
   unsigned short color_attribute;
   color_attribute = backgroundcolor;
   color_attribute = _rotl(color_attribute,4) | frontcolor;
   SetConsoleTextAttribute(screen,color_attribute);
}

//===================================================================================
// NOM: SetScreenSize
//===================================================================================
// DESCRIPCIÓ: Fixem les dimensions de la finestra consola
//===================================================================================

void SetScreenSize(HANDLE hConsole)
{
    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT myWindow;
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInformation;
    int err=1;
	COORD c;
	
	GetConsoleScreenBufferInfo(hConsole,&screenBufferInformation);

	myWindow.Left = 0;
	myWindow.Top = 0;
	//myWindow.Right=((screenBufferInformation.dwMaximumWindowSize.X)/2)-1;
	//myWindow.Bottom=((screenBufferInformation.dwMaximumWindowSize.Y)/2)-1;
	myWindow.Right=DX-1;
	myWindow.Bottom=DY-1;
	
    err=SetConsoleWindowInfo(hConsole,TRUE,&myWindow);

	c.X=DX;
	c.Y=DY;
//	c.X=((screenBufferInformation.dwMaximumWindowSize.X)/2);
//	c.Y=((screenBufferInformation.dwMaximumWindowSize.Y)/2);
	
	err=SetConsoleScreenBufferSize(hConsole,c);


}

void InitScreen(HANDLE hConsole)
{
	CONSOLE_CURSOR_INFO ConCurInf;

	SetScreenSize(hConsole);

	// ------------------------------------------------------------------------------
	// Amaguem el cursor:	         
	ConCurInf.dwSize = 10; 
    ConCurInf.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole,&ConCurInf);
}
