#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;
//Estructuras
struct Coordenadas {
	int x;
	int y;
};

//Variables Globales
Coordenadas cursor;
//Funciones para decorar
void ocultarCursor();
void mostrarCursor();
void AltEnter();
void gotoxy(int x,int y);
void TamanoPantalla(int* ancho,int* alto);
Coordenadas obtenerPosicionCursor();
//FUNCIONES PARA EL FUNCIONAMIENTO
void menu(int* opcion);

int main() {
	int op;
	menu(&op);
	cout<<"Opcion elegida: "<<op;
	return 0;
}

void menu(int* opcion) {
	bool cambio;
	int anchopantalla=0,altopantalla=0;
	int iteracion=0;
	int tecla;
	char texto[100];
	ocultarCursor();
	strcpy(texto,"BIENVENIDO AL BANCO G & D");
	TamanoPantalla(&anchopantalla,&altopantalla);
	gotoxy((anchopantalla/2)-strlen(texto)/2,1);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
		Sleep(25);
	}
	strcpy(texto,"Trabajado por Guillermo Aponte y Daniel Ramirez");
	TamanoPantalla(&anchopantalla,&altopantalla);
	gotoxy((anchopantalla/2)-strlen(texto)/2,2);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
		Sleep(25);
	}
	gotoxy(0,altopantalla/4);
	cout<<"o <-- REGISTRAR CLIENTES";
	Sleep(200);
	gotoxy(anchopantalla-25,altopantalla/4);
	cout<<"CREACION DE CUENTAS --> o";
	Sleep(200);
	gotoxy(0,(altopantalla/4)*2);
	cout<<"o <--CONSULTA DE CUENTAS";
	Sleep(200);
	gotoxy(anchopantalla-29,(altopantalla/4)*2);
	cout<<"REGISTRO DE MOVIMIENTOS --> o";
	Sleep(200);
	gotoxy(0,(altopantalla/4)*3);
	cout<<"o <-- CONSULTA DE MOVIMIENTOS";
	Sleep(200);
	gotoxy(anchopantalla-33,(altopantalla/4)*3);
	cout<<"REPORTE GENERAL POR CLIENTE --> o";
	Sleep(200);
	gotoxy(anchopantalla-11,altopantalla-2);
	cout<<"SALIR --> o";
	gotoxy(0,altopantalla/4);
	while(tecla!=13) {
		cursor=obtenerPosicionCursor();
		iteracion++;
		if(iteracion%2500==0) {
			if(cambio) {
				cout<<char(254);
				gotoxy(cursor.x,cursor.y);
				cambio=false;
			} else {
				cout<<"o";
				gotoxy(cursor.x,cursor.y);
				cambio=true;
			}
		}
		if(kbhit()) {
			tecla=getch();
			switch(tecla) {
				case 80: { //Movimiento hacia abajo
					if(cursor.y<=(altopantalla/4*3)) {
						if(cursor.y==(altopantalla/4)*3) {
							cout<<"o";
							gotoxy(anchopantalla-1,altopantalla-2);
						}
						if(cursor.y==(altopantalla/4)*2) {
							cout<<"o";
							gotoxy(cursor.x,(altopantalla/4)*3);
						}
						if(cursor.y==altopantalla/4) {
							cout<<"o";
							gotoxy(cursor.x,(altopantalla/4)*2);
						}
					}
					break;
				}
				case 72: { //Movimiento hacia arriba
					if(cursor.y>altopantalla/4) {
						if(cursor.y==(altopantalla/4)*2) {
							cout<<"o";
							gotoxy(cursor.x,altopantalla/4);
						}
						if(cursor.y==(altopantalla/4)*3) {
							cout<<"o";
							gotoxy(cursor.x,(altopantalla/4)*2);
						}
						if(cursor.y==altopantalla-2) {
							cout<<"o";
							gotoxy(cursor.x,(altopantalla/4)*3);
						}
					}
					break;
				}
				case 75: { //Movimiento a la izquierda
					if(cursor.x==anchopantalla-1) {
						if(cursor.y==(altopantalla/4)*2) {
							cout<<"o";
							gotoxy(0,(altopantalla/4)*2);
						}
						if(cursor.y==(altopantalla/4)*3) {
							cout<<"o";
							gotoxy(0,(altopantalla/4)*3);
						}
						if(cursor.y==altopantalla-2) {
							cout<<"o";
							gotoxy(0,(altopantalla/4)*3);
						}
						if(cursor.y==altopantalla/4) {
							cout<<"o";
							gotoxy(0,altopantalla/4);
						}
					}
					break;
				}
				case 77: { //Movimiento a la derecha
					if(cursor.x==0) {
						if(cursor.y==(altopantalla/4)*2) {
							cout<<"o";
							gotoxy(anchopantalla-1,(altopantalla/4)*2);
						}
						if(cursor.y==(altopantalla/4)*3) {
							cout<<"o";
							gotoxy(anchopantalla-1,(altopantalla/4)*3);
						}
						if(cursor.y==altopantalla/4) {
							cout<<"o";
							gotoxy(anchopantalla-1,altopantalla/4);
						}
					}
					break;
				}
			}
		}
	}
	if(cursor.x==0){
		if(cursor.y==altopantalla/4){
			*opcion=1;
		}
		if(cursor.y==(altopantalla/4)*2){
			*opcion=2;
		}
		if(cursor.y==(altopantalla/4)*3){
			*opcion=3;
		}
	}
	else{
		if(cursor.y==altopantalla/4){
			*opcion=4;
		}
		if(cursor.y==(altopantalla/4)*2){
			*opcion=5;
		}
		if(cursor.y==(altopantalla/4)*3){
			*opcion=6;
		}
		if(cursor.y==altopantalla-2){
			system("cls");
			strcpy(texto,"HA DECIDIDO SALIR.");
			gotoxy((anchopantalla/2)-strlen(texto)/2,1);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
				Sleep(10);
			}
			strcpy(texto,"USTED HA USADO LOS SERVICIOS DEL BANCO G & D");
			gotoxy((anchopantalla/2)-strlen(texto)/2,3);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
				Sleep(10);
			}
			strcpy(texto,"HASTA PRONTO ;)");
			gotoxy((anchopantalla/2)-strlen(texto)/2,5);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
				Sleep(10);
			}
			Sleep(300);
			strcpy(texto,"   __   __   ");
			gotoxy((anchopantalla/2)-strlen(texto)/2,8);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			strcpy(texto,"  _/  \\ /  \\_ ");
			gotoxy((anchopantalla/2)-strlen(texto)/2,9);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			strcpy(texto,"/     |     \\");
			gotoxy((anchopantalla/2)-strlen(texto)/2,10);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			strcpy(texto,"|             |");
			gotoxy((anchopantalla/2)-strlen(texto)/2,11);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			strcpy(texto," \\           / ");
			gotoxy((anchopantalla/2)-strlen(texto)/2,12);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			strcpy(texto,"  \\         /  ");
			gotoxy((anchopantalla/2)-strlen(texto)/2,13);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			strcpy(texto,"    \\       /   ");
			gotoxy((anchopantalla/2)-strlen(texto)/2,14);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			strcpy(texto,"      \\     /     ");
			gotoxy((anchopantalla/2)-strlen(texto)/2,15);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			strcpy(texto,"       \\   /      ");
			gotoxy((anchopantalla/2)-strlen(texto)/2,16);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			strcpy(texto,"       \\ /      ");
			gotoxy((anchopantalla/2)-strlen(texto)/2,17);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			exit(1);
		}
	}
	system("cls");
	for(int j=0;j<3;j++){
		strcpy(texto,". . .");
		gotoxy((anchopantalla/2)-strlen(texto)/2,altopantalla/2);
		for(int i=0; i<strlen(texto); i++) {
			Sleep(100);
			cout<<*(texto+i);
		}
		Sleep(200);
		gotoxy((anchopantalla/2)-strlen(texto)/2,altopantalla/2);
		cout<<"     ";
	}
	gotoxy(0,0);
}

void ocultarCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(consoleHandle, &cursorInfo);

	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}
void mostrarCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(consoleHandle, &cursorInfo);

	cursorInfo.bVisible = true;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}
void AltEnter() {
	keybd_event(VK_MENU,
	            0x38,
	            0,
	            0);
	keybd_event(VK_RETURN,
	            0x1c,
	            0,
	            0);
	keybd_event(VK_RETURN,
	            0x1c,
	            KEYEVENTF_KEYUP,
	            0);
	keybd_event(VK_MENU,
	            0x38,
	            KEYEVENTF_KEYUP,
	            0);
	return;
}
void gotoxy(int x,int y) {
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y= y;
	SetConsoleCursorPosition(hcon,dwPos);
}
void TamanoPantalla(int* ancho,int* alto) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	*ancho = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	*alto = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
Coordenadas obtenerPosicionCursor() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	Coordenadas posicion;
	if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		posicion.x = csbi.dwCursorPosition.X;
		posicion.y = csbi.dwCursorPosition.Y;
	} else {
		posicion.x = -1;
		posicion.y = -1;
	}
	return posicion;
}