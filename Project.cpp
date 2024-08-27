#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <ctime>
using namespace std;
//Estructuras
struct Coordenadas {
	int x;
	int y;
};
struct Cliente {
	char tipo[3];
	int identificacion;
	char nombres[20];
	char apellidos[20];
	char ciudad[20];
	char oficina[20];
};

struct Cuentas {
	Cliente cliente;
	char tipo[2];
	double apertura;
	double actual;
	int n_cuenta;
};
struct Movimientos {
	Cuentas cuenta;
	int consecutivo;
	char tipo_movimiento[2];

};

//Variables Globales
Coordenadas cursor;
int anchopantalla=0,altopantalla=0;
//Funciones para decorar
void ocultarCursor();
void mostrarCursor();
void AltEnter();
void gotoxy(int x,int y);
void TamanoPantalla(int* ancho,int* alto);
Coordenadas obtenerPosicionCursor();
//FUNCIONES PARA EL FUNCIONAMIENTO
void cargar_archivos(Cuentas *cuentas, Cliente *clientes, Movimientos *movimientos);
void menu(int* opcion);
void registro_clientes();
void repetido(Cliente *cliente);
void crear_cuentas();
int main() {
	Cuentas *cuentas=new Cuentas[100];
	Cliente *clientes=new Cliente[100];
	Movimientos *movimientos=new Movimientos[100];
	int op;
	menu(&op);
	switch(op) {
		case 1: {

			registro_clientes();
			break;
		}
		case 2: {
		
			break;
		}
		case 3: {

			break;
		}
		case 4: {
			crear_cuentas();
			break;
		}
		case 5: {

			break;
		}
		case 6: {
			break;
		}
		default: {
			break;
		}
	}
	while(1!=2){
		
	}
	return 0;
}

void menu(int* opcion) {
	bool cambio;
	int iteracion=0;
	int tecla;
	char texto[100];
	ocultarCursor();
	strcpy(texto,"BIENVENIDO AL BANCO G & D");
	TamanoPantalla(&anchopantalla,&altopantalla);
	gotoxy((anchopantalla/2)-strlen(texto)/2,1);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
		Sleep(15);
	}
	strcpy(texto,"Trabajado por Guillermo Aponte y Daniel Ramirez");
	TamanoPantalla(&anchopantalla,&altopantalla);
	gotoxy((anchopantalla/2)-strlen(texto)/2,2);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
		Sleep(15);
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
	if(cursor.x==0) {
		if(cursor.y==altopantalla/4) {
			*opcion=1;
		}
		if(cursor.y==(altopantalla/4)*2) {
			*opcion=2;
		}
		if(cursor.y==(altopantalla/4)*3) {
			*opcion=3;
		}
	} else {
		if(cursor.y==altopantalla/4) {
			*opcion=4;
		}
		if(cursor.y==(altopantalla/4)*2) {
			*opcion=5;
		}
		if(cursor.y==(altopantalla/4)*3) {
			*opcion=6;
		}
		if(cursor.y==altopantalla-2) {
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
	strcpy(texto," Cargando");
		gotoxy((anchopantalla/2)-strlen(texto)/2,altopantalla/2-1);
		for(int i=0; i<strlen(texto); i++) {
			Sleep(100);
			cout<<*(texto+i);
		}
	for(int j=0; j<3; j++) {
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
	gotoxy((anchopantalla/2)-strlen(texto)/2-1,altopantalla/2-1);
	cout<<"        ";
	gotoxy(0,0);
}


//funciones del sistema
void cargar_archivos(Cuentas *cuentas, Cliente *clientes, Movimientos *movimientos){
	int tam;
	ifstream fileclientes("bases de datos de los clientes.dat", ios::ate|ios::binary|ios::app|ios::in);
	ifstream filecuentas("bases de datos de las cuentas.dat", ios::ate|ios::binary|ios::app|ios::in);
	ifstream filemovimientos("bases de datos de los movimientos.dat",ios::ate|ios::binary|ios::app|ios::in);
	fileclientes.seekg(0, fileclientes.end);
	tam = fileclientes.tellg()/sizeof(Cliente);
	fileclientes.seekg(0, fileclientes.beg);
	for(int i = 0; i < tam; i++){
		fileclientes.read((char*)clientes+i, sizeof(Cliente));
	}
	filecuentas.seekg(0, filecuentas.end);
	tam = filecuentas.tellg()/sizeof(Cuentas);
	filecuentas.seekg(0, filecuentas.beg);
	for(int i = 0; i < tam; i++){
		filecuentas.read((char*)cuentas+i, sizeof(Cuentas));
	}
	filemovimientos.seekg(0, filemovimientos.end);
	tam = filemovimientos.tellg()/sizeof(Movimientos);
	filemovimientos.seekg(0, filemovimientos.beg);
	for(int i = 0; i < tam; i++){
		filemovimientos.read((char*)movimientos+i, sizeof(Movimientos));
	}
}
void registro_clientes() {
	Cliente cliente;
	bool guardable;
	bool cambio;
	int tecla=0;
	int iteracion=0;
	char texto[100];
	ofstream file("bases de datos de los clientes.dat",ios::ate|ios::binary|ios::out|ios::app);
	if(!file) {
		cout << "Error al abrir el archivo";
		exit(1);
	}
	for(int i=0;i<anchopantalla;i++){
		for(int j=0;j<altopantalla;j++){
			if((i==0)||(i==anchopantalla-1)||(j==0)||(j==altopantalla-1)){
				gotoxy(i,j);
				cout<<char(178);
				Sleep(1);
			}
		}
	}
	strcpy(texto,"Seleccione su tipo de identificacion");
	gotoxy((anchopantalla/2)-strlen(texto)/2,3);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	strcpy(texto,"C.C          T.I          C.E");
	gotoxy((anchopantalla/2)-strlen(texto)/2,5);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}	
	strcpy(texto,"o            o            o");
	gotoxy((anchopantalla/2)-strlen(texto)/2,6);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	gotoxy((anchopantalla/2)-strlen(texto)/2,6);
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
			switch(tecla){
				case 75: { //Movimiento a la izquierda
					if(cursor.x==(anchopantalla/2)-strlen(texto)/2) {
						cout<<"o";
						gotoxy((anchopantalla/2)+(strlen(texto)/2),6);
					}
					if(cursor.x==anchopantalla/2) {
						cout<<"o";
						gotoxy((anchopantalla/2)-(strlen(texto)/2),6);
					}
					if(cursor.x==(anchopantalla/2)+(strlen(texto)/2)) {
						cout<<"o";
						gotoxy(anchopantalla/2,6);
					}
					break;
				}
				case 77: { //Movimiento a la derecha
					if(cursor.x==(anchopantalla/2)+(strlen(texto)/2)) {
						cout<<"o";
						gotoxy((anchopantalla/2)-(strlen(texto)/2),6);
					}
					if(cursor.x==anchopantalla/2) {
						cout<<"o";
						gotoxy((anchopantalla/2)+(strlen(texto)/2),6);
					}
					if(cursor.x==(anchopantalla/2)-(strlen(texto)/2)) {
						cout<<"o";
						gotoxy(anchopantalla/2,6);
					}
					break;
				}
			}
		}
	}
	if(cursor.x==(anchopantalla/2)-(strlen(texto)/2))
		strcpy(cliente.tipo,"CC");
	if(cursor.x==anchopantalla/2)
		strcpy(cliente.tipo,"TI");
	if(cursor.x==(anchopantalla/2)+(strlen(texto)/2))
		strcpy(cliente.tipo,"CE");
	strcpy(texto,"Numero de documento: ");
	gotoxy((anchopantalla/2)-(strlen(texto)/2)-5,9);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	cin>>cliente.identificacion;
	repetido(&cliente);
	fflush(stdin);
	cursor=obtenerPosicionCursor();
	strcpy(texto,"Nombres: ");
	gotoxy((anchopantalla/2)-(strlen(texto)/2)-5,cursor.y+1);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	gets(cliente.nombres);
	cout << endl;
	strcpy(texto,"Apellidos: ");
	gotoxy((anchopantalla/2)-(strlen(texto)/2)-5,cursor.y+2);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	gets(cliente.apellidos);
	cout << endl;
	strcpy(texto,"Oficina: ");
	gotoxy((anchopantalla/2)-(strlen(texto)/2)-5,cursor.y+3);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	gets(cliente.oficina);
	strcpy(texto,"Ciudad: ");
	gotoxy((anchopantalla/2)-(strlen(texto)/2)-5,cursor.y+4);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	gets(cliente.ciudad);
	file.seekp(0, file.end);
	file.write((char*)&cliente, sizeof(Cliente));
	file.close();
}

void repetido(Cliente *cliente) {
	bool guardable = false;
	char texto[100];
	int j=12;
	Cliente cliente2;
	ifstream inputfile("bases de datos de los clientes.dat", ios::binary|ios::in);
	if(inputfile.eof()) {
		guardable = true;
	}
	if(!inputfile) {
		cout << "No hay coneccion con el archivo";
		exit(1);
	}
	inputfile.seekg(0, inputfile.beg);
	while(guardable == false) {
		guardable=true;
		while(!inputfile.eof()) {
			inputfile.read((char*)&cliente2, sizeof(Cliente));
			if(cliente2.identificacion == cliente->identificacion) {
				guardable = false;
			}
		}
		if(guardable==false) {
			strcpy(texto,"Este numero ya existe, intente de nuevo: ");
			gotoxy((anchopantalla/2)-(strlen(texto)/2)-5,j);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			j++;
			inputfile.clear();
			inputfile.seekg(0,inputfile.beg);
			cin >> cliente->identificacion;
			gotoxy((anchopantalla/2)-(strlen(texto)/2)-5,j);
			cout<<"                                                                 ";
			if(j>=22){
				for(j=11;j<23;j++){
					gotoxy((anchopantalla/2)-(strlen(texto)/2)-5,j);
					cout<<"                                                                 ";
				}
				j=11;
			}
		}
	}

}
void crear_cuentas(){
	srand(time(0));
	int identificacion;
	bool existente = false;
	Cuentas cuenta;
	Cliente clientes;
	ifstream inputfile("bases de datos de los clientes.dat", ios::binary|ios::in);
	if(inputfile.eof()) {
		existente = true;
	}
	if(!inputfile) {
		cout << "No hay conexion con el archivo de clientes";
		exit(1);
	}
	cout << "Digite su numero de identificacion: ";
	cin >> cuenta.cliente.identificacion;
	inputfile.seekg(0, inputfile.beg);
	while(existente == false) {
		while(!inputfile.eof()) {
			existente=true;
			inputfile.read((char*)&clientes, sizeof(Cliente));
			if(clientes.identificacion != cuenta.cliente.identificacion) {
				existente = false;
			}
		}
		if(existente==false) {
			cout << "Este numero no existe, vuelva a intentar";
			inputfile.clear();
			inputfile.seekg(0,inputfile.beg);
			cin >> cuenta.cliente.identificacion;
		}
	}
	cuenta.n_cuenta = rand()%88889+11111;
	cout << cuenta.n_cuenta << endl;
	
	ofstream outputfile("bases de datos de las cuentas.dat", ios::binary|ios::out|ios::app|ios::ate);
	if(!outputfile){
		cout << "Sin conexion con el archivo de cuentas";
		exit(1);
	}
	
}






















//funciones de decoración
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