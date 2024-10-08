/*
	INTEGRANTES: GUILLERMO APONTE, DANIEL RAMIREZ
	GRUPO: 4
	FECHA: 2024/09/15
	PROYECTO #1 "BANCO G & D ( SISTEMA DE MANEJO DE CLIENTES )"
*/
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
	char tipo;
	int apertura;
	int actual;
	int n_cuenta;
};
struct Movimientos {
	int identificacion;
	int consecutivo;
	int valor_movimiento;
	char tipo_movimiento;
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
void despedida();
Coordenadas obtenerPosicionCursor();
//FUNCIONES PARA EL FUNCIONAMIENTO
Cliente* cargar_archivos_cliente(Cliente *clientes);
Cuentas* cargar_archivos_cuentas(Cuentas *cuentas);
Movimientos* cargar_archivos_movimientos(Movimientos *movimientos);
void menu(int* opcion);
void registro_clientes();
void repetido(Cliente *cliente);
void crear_cuentas();
void consultar(Cliente* clientes, Cuentas *cuentas);
void transacciones(Cliente *clientes, Cuentas *cuenta);
int identificacionconsecutivo(int id);
void consultarMovimientos(Cliente *clientes, Cuentas *cuentas, Movimientos *movimientos);
void Mostrartodo(Cliente *clientes, Cuentas *cuentas, Movimientos *movimientos);
int main() {
	Cuentas *cuentas=new Cuentas[1];
	Cliente *clientes=new Cliente[1];
	Movimientos *movimientos=new Movimientos[1];
	int op;
	menu(&op);
	while(op != 7) {
		clientes=cargar_archivos_cliente(clientes);
		cuentas=cargar_archivos_cuentas(cuentas);
		movimientos=cargar_archivos_movimientos(movimientos);
		switch(op) {
			case 1: {
				registro_clientes();
				system("cls");
				menu(&op);
				break;
			}
			case 2: {
				consultar(clientes, cuentas);
				system("cls");
				menu(&op);
				break;
			}
			case 3: {
				consultarMovimientos(clientes,cuentas,movimientos);
				system("cls");
				menu(&op);
				break;
			}
			case 4: {

				crear_cuentas();
				system("cls");
				menu(&op);
				break;
			}
			case 5: {
				transacciones(clientes, cuentas);
				system("cls");
				menu(&op);
				break;
			}
			case 6: {
				Mostrartodo(clientes, cuentas, movimientos);
				system("cls");
				menu(&op);
				break;
			}
			default: {
				break;
			}
		}
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
			despedida();
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
Cliente* cargar_archivos_cliente(Cliente *clientes) {
	int tam;
	ifstream fileclientes("bases de datos de los clientes.dat",ios::binary|ios::in);
	if(fileclientes) {
		fileclientes.seekg(0, fileclientes.end);
		tam = fileclientes.tellg()/sizeof(Cliente);
		delete[] clientes;
		clientes = new Cliente[tam];
		fileclientes.seekg(0, fileclientes.beg);
		for(int i = 0; i < tam; i++) {
			fileclientes.read((char*)&clientes[i],sizeof(Cliente));
		}
		fileclientes.clear();
		fileclientes.close();
		return clientes;
	}
	return clientes;
}
Cuentas* cargar_archivos_cuentas(Cuentas *cuentas) {
	int tam;
	ifstream filecuentas("bases de datos de las cuentas.dat",ios::binary|ios::in);
	if(filecuentas) {
		filecuentas.seekg(0, filecuentas.end);
		tam = filecuentas.tellg()/sizeof(Cuentas);
		delete []cuentas;
		cuentas = new Cuentas[tam];
		filecuentas.seekg(0, filecuentas.beg);
		for(int i = 0; i < tam; i++) {
			filecuentas.read((char*)&cuentas[i], sizeof(Cuentas));
		}
		filecuentas.clear();
		filecuentas.close();
	}
	return cuentas;
}
Movimientos* cargar_archivos_movimientos(Movimientos *movimientos) {
	int tam;
	ifstream filemovimientos("bases de datos de los movimientos.dat",ios::binary|ios::in);
	if(filemovimientos) {
		filemovimientos.seekg(0, filemovimientos.end);
		tam = filemovimientos.tellg()/sizeof(Movimientos);
		delete[] movimientos;
		movimientos = new Movimientos[tam];
		filemovimientos.seekg(0, filemovimientos.beg);
		for(int i = 0; i < tam; i++) {
			filemovimientos.read((char*)&movimientos[i], sizeof(Movimientos));
		}
		filemovimientos.clear();
		filemovimientos.close();
	}
	return movimientos;
}
void registro_clientes() {
	Cliente cliente;
	bool guardable;
	bool cambio;
	int tecla=0;
	int iteracion=0;
	char texto[100];
	for(int i=0; i<anchopantalla; i++) {
		for(int j=0; j<altopantalla; j++) {
			if((i==0)||(i==anchopantalla-1)||(j==0)||(j==altopantalla-1)) {
				gotoxy(i,j);
				cout<<char(178);
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
			switch(tecla) {
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
	mostrarCursor();
	cin>>cliente.identificacion;
	ocultarCursor();
	ofstream file("bases de datos de los clientes.dat",ios::ate|ios::binary|ios::out|ios::app);
	if(!file) {
		cout << "Error al abrir el archivo";
		exit(1);
	}
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
	strcpy(texto,"Cliente Registrado correctamente!!");
	gotoxy((anchopantalla/2)-strlen(texto)/2,cursor.y+6);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	file.write((char*)&cliente, sizeof(Cliente));
	file.close();
	gotoxy((anchopantalla/2)-39/2,23);
	system("pause");
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
		cout << "No hay conexion con el archivo";
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
			mostrarCursor();
			cin >> cliente->identificacion;
			ocultarCursor();
			gotoxy((anchopantalla/2)-(strlen(texto)/2)-5,j);
			cout<<"                                                                 ";
			if(j>=22) {
				for(j=11; j<23; j++) {
					gotoxy((anchopantalla/2)-(strlen(texto)/2)-5,j);
					cout<<"                                                                 ";
				}
				j=11;
			}
		}
	}

}
void crear_cuentas() {
	srand(time(0));
	int identificacion;
	bool existente = false;
	int tipocuenta;
	bool suficiente = false;
	bool cambio;
	int correccion;
	int iteracion=0;
	int tecla=0;
	Cuentas cuenta;
	Cliente clientes;
	Cuentas auxiliar;
	char texto[100];
	ifstream inputfile("bases de datos de los clientes.dat", ios::binary|ios::in);
	if(inputfile.eof()) {
		existente = true;
	}
	if(!inputfile) {
		cout << "No hay conexion con el archivo de clientes, revise si ya hay almenos uno en el archivo"<<endl;
		system("pause");
		return;
	}
	for(int i=0; i<anchopantalla; i++) {
		for(int j=0; j<altopantalla; j++) {
			if((i==0)||(i==anchopantalla-1)||(j==0)||(j==altopantalla-1)) {
				gotoxy(i,j);
				cout<<char(178);
			}
		}
	}
	strcpy(texto,"Digite su numero de identificacion: ");
	gotoxy((anchopantalla/2)-strlen(texto)/2-5,3);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	mostrarCursor();
	cin >> cuenta.cliente.identificacion;
	ocultarCursor();
	inputfile.seekg(0, inputfile.beg);
	while(existente == false) {
		while(!inputfile.eof()) {
			inputfile.read((char*)&clientes, sizeof(Cliente));
			if(clientes.identificacion == cuenta.cliente.identificacion) {
				existente = true;
			}
		}
		if(existente==false) {
			strcpy(texto,"Este cliente no esta registrado, que desea hacer?");
			gotoxy((anchopantalla/2)-strlen(texto)/2,5);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			strcpy(texto,"Volver a digitar el numero");
			gotoxy((anchopantalla/4)-strlen(texto)/2,9);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			strcpy(texto,"Registrarse y volver");
			gotoxy((anchopantalla/4)*2-strlen(texto)/2,9);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			strcpy(texto,"Salir");
			gotoxy((anchopantalla/4)*3-strlen(texto)/2,9);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			strcpy(texto,"o");
			for(int k=1; k<4; k++) {
				gotoxy((anchopantalla/4)*k-strlen(texto)/2,10);
				for(int i=0; i<strlen(texto); i++) {
					cout<<*(texto+i);
				}
			}
			gotoxy((anchopantalla/4)-strlen(texto)/2,10);
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
						case 75: { //Movimiento a la izquierda
							if(cursor.x==(anchopantalla/4)-strlen(texto)/2) {
								cout<<"o";
								gotoxy((anchopantalla/4)*3-strlen(texto)/2,10);
							}
							if(cursor.x==(anchopantalla/4)*2-strlen(texto)/2) {
								cout<<"o";
								gotoxy((anchopantalla/4)-strlen(texto)/2,10);
							}
							if(cursor.x==(anchopantalla/4)*3-strlen(texto)/2) {
								cout<<"o";
								gotoxy((anchopantalla/4)*2-strlen(texto)/2,10);
							}
							break;
						}
						case 77: { //Movimiento a la derecha
							if(cursor.x==(anchopantalla/4)*3-strlen(texto)/2) {
								cout<<"o";
								gotoxy((anchopantalla/4)-strlen(texto)/2,10);
							}
							if(cursor.x==(anchopantalla/4)*2-strlen(texto)/2) {
								cout<<"o";
								gotoxy((anchopantalla/4)*3-strlen(texto)/2,10);
							}
							if(cursor.x==(anchopantalla/4)-strlen(texto)/2) {
								cout<<"o";
								gotoxy((anchopantalla/4)*2-strlen(texto)/2,10);
							}
							break;
						}
					}
				}
			}
			if(cursor.x==(anchopantalla/4)-strlen(texto)/2)
				correccion=1;
			if(cursor.x==(anchopantalla/4)*2-strlen(texto)/2)
				correccion=2;
			if(cursor.x==(anchopantalla/4)*3-strlen(texto)/2)
				correccion=3;
			switch(correccion) {
				case 1: {
					tecla=0;
					strcpy(texto,"                                 ");
					gotoxy((anchopantalla/2)-strlen(texto)/2-5,12);
					for(int i=0; i<strlen(texto); i++) {
						cout<<*(texto+i);
					}
					strcpy(texto,"Escriba su numero: ");
					gotoxy((anchopantalla/2)-strlen(texto)/2-5,12);
					for(int i=0; i<strlen(texto); i++) {
						cout<<*(texto+i);
					}
					inputfile.clear();
					inputfile.seekg(0,inputfile.beg);
					mostrarCursor();
					cin >> cuenta.cliente.identificacion;
					ocultarCursor();
					for(int i=0; i<anchopantalla; i++) {
						for(int j=0; j<altopantalla; j++) {
							if((i==0)||(i==anchopantalla-1)||(j==0)||(j==altopantalla-1)) {
								gotoxy(i,j);
								cout<<char(178);
							}
						}
					}
					break;
				}
				case 2: {
					system("cls");
					registro_clientes();
					system("cls");
					for(int i=0; i<anchopantalla; i++) {
						for(int j=0; j<altopantalla; j++) {
							if((i==0)||(i==anchopantalla-1)||(j==0)||(j==altopantalla-1)) {
								gotoxy(i,j);
								cout<<char(178);
							}
						}
					}
					strcpy(texto,"Digite el numero de identificacion del cliente recien registrado para la apertura de su cuenta: ");
					gotoxy((anchopantalla/2)-strlen(texto)/2-5,12);
					for(int i=0; i<strlen(texto); i++) {
						cout<<*(texto+i);
					}
					inputfile.clear();
					inputfile.seekg(0,inputfile.beg);
					mostrarCursor();
					cin >> cuenta.cliente.identificacion;
					ocultarCursor();
					tecla=0;
					break;
				}
				case 3: {
					despedida();
					break;
				}
			}
		}
	}
	existente = false;
	ifstream inputfile2("bases de datos de las cuentas.dat", ios::binary|ios::in);
	while(existente == false) {
		cuenta.n_cuenta = rand()%88889 + 11111;
		existente=true;
		while(!inputfile.eof()) {
			inputfile2.read((char*)&auxiliar, sizeof(Cuentas));
			if(cuenta.n_cuenta == auxiliar.n_cuenta) {
				existente = false;
			}
		}
		inputfile2.clear();
		inputfile2.seekg(0,inputfile2.beg);
	}
	inputfile2.close();
	system("cls");
	for(int i=0; i<anchopantalla; i++) {
		for(int j=0; j<altopantalla; j++) {
			if((i==0)||(i==anchopantalla-1)||(j==0)||(j==altopantalla-1)) {
				gotoxy(i,j);
				cout<<char(178);
			}
		}
	}
	strcpy(texto,"El numero aleatorio asignado a su cuenta es: ");
	gotoxy((anchopantalla/2)-strlen(texto)/2-5,3);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	cout<<cuenta.n_cuenta;
	strcpy(texto,"Que tipo de cuenta desea abrir?");
	gotoxy((anchopantalla/2)-strlen(texto)/2,5);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	strcpy(texto,"Ahorros");
	gotoxy((anchopantalla/3)-strlen(texto)/2,7);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	strcpy(texto,"Corriente");
	gotoxy((anchopantalla/3)*2-strlen(texto)/2,7);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	strcpy(texto,"o");
	for(int k=1; k<3; k++) {
		gotoxy((anchopantalla/3)*k-strlen(texto)/2,8);
		for(int i=0; i<strlen(texto); i++) {
			cout<<*(texto+i);
		}
	}
	gotoxy((anchopantalla/3)-strlen(texto)/2,8);
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
				case 75: { //Movimiento a la izquierda
					if(cursor.x==(anchopantalla/3)-strlen(texto)/2) {
						cout<<"o";
						gotoxy((anchopantalla/3)*2-strlen(texto)/2,8);
					}
					if(cursor.x==(anchopantalla/3)*2-strlen(texto)/2) {
						cout<<"o";
						gotoxy((anchopantalla/3)-strlen(texto)/2,8);
					}
					break;
				}
				case 77: { //Movimiento a la derecha
					if(cursor.x==(anchopantalla/3)*2-strlen(texto)/2) {
						cout<<"o";
						gotoxy((anchopantalla/3)-strlen(texto)/2,8);
					}
					if(cursor.x==(anchopantalla/3)-strlen(texto)/2) {
						cout<<"o";
						gotoxy((anchopantalla/3)*2-strlen(texto)/2,8);
					}
					break;
				}
			}
		}
	}
	if(cursor.x==(anchopantalla/3)-strlen(texto)/2)
		tipocuenta=1;
	if(cursor.x==(anchopantalla/3)*2-strlen(texto)/2/2)
		tipocuenta=2;
	switch(tipocuenta) {
		case 1: {
			cuenta.tipo = 'A';
			break;
		}
		case 2: {
			cuenta.tipo = 'C';
			break;
		}
	}
	while(suficiente == false) {
		cursor=obtenerPosicionCursor();
		if(cursor.y>=22) {
			for(int j=10; j<28; j++) {
				strcpy(texto,"                                                 ");
				gotoxy((anchopantalla/2)-strlen(texto)/2-6,j);
				for(int i=0; i<strlen(texto); i++) {
					cout<<*(texto+i);
				}
			}
			cursor.y=8;
		}
		strcpy(texto,"Saldo de apertura (minimo 50.000): ");
		gotoxy((anchopantalla/2)-strlen(texto)/2-4,cursor.y+2);
		for(int i=0; i<strlen(texto); i++) {
			cout<<*(texto+i);
		}
		mostrarCursor();
		cin >> cuenta.apertura;
		ocultarCursor();
		if(cuenta.apertura >= 50000) {
			strcpy(texto,"Cuenta creada correctamente!!");
			gotoxy((anchopantalla/2)-strlen(texto)/2,cursor.y+4);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			suficiente = true;
			cuenta.actual = cuenta.apertura;
			inputfile.seekg(0, inputfile.end);
		} else {
			strcpy(texto,"Saldo insuficiente, vuelva a intentarlo");
			gotoxy((anchopantalla/2)-strlen(texto)/2-4,cursor.y+4);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
		}
	}

	ofstream outputfile("bases de datos de las cuentas.dat", ios::binary|ios::out|ios::app|ios::ate);
	if(!outputfile) {
		cout << "Sin conexion con el archivo de cuentas";
		exit(1);
	}
	outputfile.write((char*)&cuenta, sizeof(Cuentas));
	outputfile.close();
	gotoxy((anchopantalla/2)-39/2,cursor.y+6);
	system("pause");
}

void consultar(Cliente *clientes, Cuentas *cuentas) {
	bool cambio=true;
	int iteracion=0;
	int tecla=0;
	int identificacion;
	int cuenta;
	int opcion;
	bool encontrado = false;
	int tam;
	int tam2;
	char texto[100];
	char textoaux[100];
	ifstream fileclientes("bases de datos de los clientes.dat",ios::binary|ios::in);
	if(!fileclientes) {
		cout<<"Archivo no encontrado, revise si almenos se ha registrado un cliente"<<endl;
		system("pause");
		return;
	}
	ifstream filecuentas("bases de datos de las cuentas.dat",ios::binary|ios::in);
	if(!filecuentas) {
		cout<<"Archivo no encontrado, revise si almenos se ha creado una cuenta"<<endl;
		system("pause");
		return;
	}
	fileclientes.seekg(0,fileclientes.end);
	filecuentas.seekg(0,filecuentas.end);
	tam=(filecuentas.tellg()/sizeof(Cuentas));
	tam2=(fileclientes.tellg()/sizeof(Cliente));
	fileclientes.close();
	filecuentas.close();
	strcpy(texto,"Por que metodo desea buscar una cuenta?");
	gotoxy(anchopantalla/2-strlen(texto)/2,4);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	for(int i=0; i<anchopantalla; i++) {
		for(int j=0; j<altopantalla; j++) {
			if((i==0)||(i==anchopantalla-1)||(j==0)||(j==altopantalla-1)) {
				gotoxy(i,j);
				cout<<char(178);
			}
		}
	}
	strcpy(texto,"Por # de identificacion");
	gotoxy(anchopantalla/3-strlen(texto)/2,7);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	strcpy(texto,"Por # de Cuenta");
	gotoxy((anchopantalla/3)*2-strlen(texto)/2,7);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	strcpy(texto,"o");
	gotoxy(anchopantalla/3-strlen(texto)/2,8);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	strcpy(texto,"o");
	gotoxy((anchopantalla/3)*2-strlen(texto)/2,8);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	gotoxy((anchopantalla/3)-strlen(texto)/2,8);
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
				case 75: { //Movimiento a la izquierda
					if(cursor.x==(anchopantalla/3)-strlen(texto)/2) {
						cout<<"o";
						gotoxy((anchopantalla/3)*2-strlen(texto)/2,8);
					}
					if(cursor.x==(anchopantalla/3)*2-strlen(texto)/2) {
						cout<<"o";
						gotoxy((anchopantalla/3)-strlen(texto)/2,8);
					}
					break;
				}
				case 77: { //Movimiento a la derecha
					if(cursor.x==(anchopantalla/3)*2-strlen(texto)/2) {
						cout<<"o";
						gotoxy((anchopantalla/3)-strlen(texto)/2,8);
					}
					if(cursor.x==(anchopantalla/3)-strlen(texto)/2) {
						cout<<"o";
						gotoxy((anchopantalla/3)*2-strlen(texto)/2,8);
					}
					break;
				}
			}
		}
	}
	if(cursor.x==(anchopantalla/3)-strlen(texto)/2)
		opcion=1;
	if(cursor.x==(anchopantalla/3)*2-strlen(texto)/2)
		opcion=2;
	switch(opcion) {
		case 1: {
			strcpy(texto,"Digite el # de identificacion: ");
			gotoxy((anchopantalla/3)-strlen(texto)/2,10);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			mostrarCursor();
			cin>>identificacion;
			ocultarCursor();
			for(int i = 0; i < tam; i++) {
				if(identificacion == (cuentas+i)->cliente.identificacion) {
					strcpy(texto,"Datos de cuenta ");
					gotoxy((anchopantalla/3)-strlen(texto)/2,15);
					for(int i=0; i<strlen(texto); i++) {
						cout<<*(texto+i);
					}
					for(int j = 0; j < tam2; j++) {
						if(identificacion == (clientes+j)->identificacion) {
							encontrado=true;
							strcpy(texto,"       Cliente: ");
							gotoxy((anchopantalla/3)-strlen(texto)/2,17);
							for(int i=0; i<strlen(texto); i++) {
								cout<<*(texto+i);
							}
							cout<<(clientes+j)->nombres<<" "<<(clientes+j)->apellidos;
							strcpy(texto,"      # Cuenta: ");
							gotoxy((anchopantalla/3)-strlen(texto)/2,19);
							for(int i=0; i<strlen(texto); i++) {
								cout<<*(texto+i);
							}
							cout<<(cuentas+i)->n_cuenta;
							strcpy(texto,"Cuenta de tipo: ");
							gotoxy((anchopantalla/3)-strlen(texto)/2,21);
							for(int i=0; i<strlen(texto); i++) {
								cout<<*(texto+i);
							}
							if((cuentas+i)->tipo == 'A') {
								cout<<"Ahorros";
							} else {
								cout<<"Corriente";
							}
							strcpy(texto,"         Saldo: ");
							gotoxy((anchopantalla/3)-strlen(texto)/2,23);
							for(int i=0; i<strlen(texto); i++) {
								cout<<*(texto+i);
							}
							cout<<(cuentas+i)->actual;
						}
					}
				}
			}
			break;
		}
		case 2: {
			strcpy(texto,"Digite el # de cuenta ");
			gotoxy((anchopantalla/3)*2-strlen(texto)/2,10);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			mostrarCursor();
			cin >> cuenta;
			ocultarCursor();
			for(int i = 0; i < tam; i++) {
				if(cuenta == (cuentas+i)->n_cuenta) {
					strcpy(texto,"Datos de cuenta ");
					gotoxy((anchopantalla/3)*2-strlen(texto)/2,15);
					for(int i=0; i<strlen(texto); i++) {
						cout<<*(texto+i);
					}
					for(int k = 0; k < tam2; k++) {
						if((cuentas+i)->cliente.identificacion == (clientes+k)->identificacion) {
							encontrado=true;
							strcpy(texto,"       Cliente: ");
							gotoxy((anchopantalla/3)*2-strlen(texto)/2,17);
							for(int i=0; i<strlen(texto); i++) {
								cout<<*(texto+i);
							}
							cout << (clientes+k)->nombres << " " << (clientes+k)->apellidos << endl;
							strcpy(texto,"      # Cuenta: ");
							gotoxy((anchopantalla/3)*2-strlen(texto)/2,19);
							for(int i=0; i<strlen(texto); i++) {
								cout<<*(texto+i);
							}
							cout << (cuentas+i)->n_cuenta << endl;
							strcpy(texto,"Cuenta de tipo: ");
							gotoxy((anchopantalla/3)*2-strlen(texto)/2,21);
							for(int i=0; i<strlen(texto); i++) {
								cout<<*(texto+i);
							}
							if((cuentas+i)->tipo == 'A') {
								cout << "Ahorros" << endl;
							} else {
								cout << "Corriente" << endl;
							}
							strcpy(texto,"         Saldo: ");
							gotoxy((anchopantalla/3)*2-strlen(texto)/2,23);
							for(int i=0; i<strlen(texto); i++) {
								cout<<*(texto+i);
							}
							cout << (cuentas+i)->actual << endl;
						}
					}
				}
			}
			break;
		}
		default: {
			break;
		}
	}
	strcpy(texto,"Cuenta no encontrada");
	gotoxy((anchopantalla/2)-strlen(texto)/2,15);
	if(encontrado==false) {
		for(int i=0; i<strlen(texto); i++) {
			cout<<*(texto+i);
		}
	}
	gotoxy((anchopantalla/2)-39/2,25);
	system("pause");
}
void transacciones(Cliente *clientes, Cuentas *cuentas) {
	srand(time(0));
	bool encontrado=false;
	int numerocuenta;
	int tam;
	int tam2;
	int opcion;
	int retiro;
	int consigna;
	int poscuenta;
	int tecla=0;
	int iteracion;
	char texto[100];
	bool cambio=true;
	Movimientos movimientoaux;
	ifstream filecuentas("bases de datos de las cuentas.dat",ios::binary|ios::in);
	if(!filecuentas) {
		cout<<"Error, revise si existe almenos una cuenta creada"<<endl;
		system("pause");
		return;
	}
	ifstream fileclientes("bases de datos de los clientes.dat",ios::binary|ios::in);
	if(!fileclientes) {
		cout<<"Error, revise si existe almenos un cliente registrado"<<endl;
		system("pause");
		return;
	}
	for(int i=0; i<anchopantalla; i++) {
		for(int j=0; j<altopantalla; j++) {
			if((i==0)||(i==anchopantalla-1)||(j==0)||(j==altopantalla-1)) {
				gotoxy(i,j);
				cout<<char(178);
			}
		}
	}
	strcpy(texto,"Digite el numero de cuenta: ");
	gotoxy(anchopantalla/2-strlen(texto)/2-5,3);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	mostrarCursor();
	cin >> numerocuenta;
	ocultarCursor();
	filecuentas.seekg(0,filecuentas.end);
	tam=(filecuentas.tellg()/sizeof(Cuentas));
	fileclientes.seekg(0, fileclientes.end);
	tam2=(fileclientes.tellg())/sizeof(Cliente);
	fileclientes.close();
	filecuentas.close();
	for(int i = 0; i < tam; i++) {
		if(numerocuenta == (cuentas+i)->n_cuenta) {
			poscuenta = i;
			encontrado=true;
			strcpy(texto,"Que tipo de movimiento desea realizar?");
			gotoxy(anchopantalla/2-strlen(texto)/2,5);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			for(int i=0; i<anchopantalla; i++) {
				for(int j=0; j<altopantalla; j++) {
					if((i==0)||(i==anchopantalla-1)||(j==0)||(j==altopantalla-1)) {
						gotoxy(i,j);
						cout<<char(178);
					}
				}
			}
			strcpy(texto,"Retiro");
			gotoxy(anchopantalla/3-strlen(texto)/2,7);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			strcpy(texto,"Consignacion");
			gotoxy((anchopantalla/3)*2-strlen(texto)/2,7);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			strcpy(texto,"o");
			gotoxy(anchopantalla/3-strlen(texto)/2,8);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			strcpy(texto,"o");
			gotoxy((anchopantalla/3)*2-strlen(texto)/2,8);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			gotoxy((anchopantalla/3)-strlen(texto)/2,8);
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
						case 75: { //Movimiento a la izquierda
							if(cursor.x==(anchopantalla/3)-strlen(texto)/2) {
								cout<<"o";
								gotoxy((anchopantalla/3)*2-strlen(texto)/2,8);
							}
							if(cursor.x==(anchopantalla/3)*2-strlen(texto)/2) {
								cout<<"o";
								gotoxy((anchopantalla/3)-strlen(texto)/2,8);
							}
							break;
						}
						case 77: { //Movimiento a la derecha
							if(cursor.x==(anchopantalla/3)*2-strlen(texto)/2) {
								cout<<"o";
								gotoxy((anchopantalla/3)-strlen(texto)/2,8);
							}
							if(cursor.x==(anchopantalla/3)-strlen(texto)/2) {
								cout<<"o";
								gotoxy((anchopantalla/3)*2-strlen(texto)/2,8);
							}
							break;
						}
					}
				}
			}
			if(cursor.x==(anchopantalla/3)-strlen(texto)/2)
				opcion=1;
			if(cursor.x==(anchopantalla/3)*2-strlen(texto)/2)
				opcion=2;
			switch(opcion) {
				case 1: {
					movimientoaux.tipo_movimiento = 'R';
					strcpy(texto,"Cuanto quiere retirar?: ");
					gotoxy(anchopantalla/2-strlen(texto)/2-5,10);
					for(int i=0; i<strlen(texto); i++) {
						cout<<*(texto+i);
					}
					mostrarCursor();
					cin >> retiro;
					ocultarCursor();
					if((cuentas+i)->actual-retiro<0) {
						strcpy(texto,"Esta cuenta no cuenta con fondos suficientes para realizar este movimiento");
						gotoxy(anchopantalla/2-strlen(texto)/2,10);
						for(int i=0; i<strlen(texto); i++) {
							cout<<*(texto+i);
						}
						gotoxy(anchopantalla/2-39/2,12);
						system("pause");
						return;
					}
					movimientoaux.valor_movimiento=retiro;
					break;
				}
				case 2: {
					movimientoaux.tipo_movimiento = 'C';
					strcpy(texto,"Cuanto quiere consignar?: ");
					gotoxy(anchopantalla/2-strlen(texto)/2-5,10);
					for(int i=0; i<strlen(texto); i++) {
						cout<<*(texto+i);
					}
					mostrarCursor();
					cin >> consigna;
					ocultarCursor();
					movimientoaux.valor_movimiento=consigna;
					break;
				}
				default: {
					break;
				}
			}
		}
	}
	if(movimientoaux.tipo_movimiento == 'R') {
		(cuentas+poscuenta)->actual -= retiro;
	} else {
		(cuentas+poscuenta)->actual += consigna;
	}
	if(encontrado==true) {
		system("cls");
		for(int i=0; i<anchopantalla; i++) {
			for(int j=0; j<altopantalla; j++) {
				if((i==0)||(i==anchopantalla-1)||(j==0)||(j==altopantalla-1)) {
					gotoxy(i,j);
					cout<<char(178);
				}
			}
		}
		for(int i=0; i<tam; i++) {
			if(numerocuenta==(cuentas+i)->n_cuenta) {
				for(int j=0; j<tam2; j++) {
					if((cuentas+i)->cliente.identificacion==(clientes+j)->identificacion) {
						movimientoaux.identificacion=(clientes+j)->identificacion;
						movimientoaux.consecutivo=identificacionconsecutivo(movimientoaux.identificacion);
						strcpy(texto,"Resumen de la operacion: ");
						gotoxy(anchopantalla/2-strlen(texto)/2,3);
						for(int i=0; i<strlen(texto); i++) {
							cout<<*(texto+i);
						}
						strcpy(texto,"Cliente: ");
						strcat(texto,(clientes+j)->nombres);
						strcat(texto," ");
						strcat(texto,(clientes+j)->apellidos);
						gotoxy(anchopantalla/3,6);
						for(int i=0; i<strlen(texto); i++) {
							cout<<*(texto+i);
						}
						strcpy(texto,"# Cuenta: ");
						gotoxy(anchopantalla/3,8);
						for(int i=0; i<strlen(texto); i++) {
							cout<<*(texto+i);
						}
						cout<<(cuentas+i)->n_cuenta;
						if(movimientoaux.tipo_movimiento=='R') {
							strcpy(texto,"Tipo de movimiento: Retiro ");
							gotoxy(anchopantalla/3,10);
							for(int i=0; i<strlen(texto); i++) {
								cout<<*(texto+i);
							}
							strcpy(texto,"Valor del movimiento ");
							gotoxy(anchopantalla/3,12);
							for(int i=0; i<strlen(texto); i++) {
								cout<<*(texto+i);
							}
							cout << retiro ;
						} else {
							strcpy(texto,"Tipo de movimiento: Consignacion ");
							gotoxy(anchopantalla/3,10);
							for(int i=0; i<strlen(texto); i++) {
								cout<<*(texto+i);
							}
							strcpy(texto,"Valor del movimiento ");
							gotoxy(anchopantalla/3,12);
							for(int i=0; i<strlen(texto); i++) {
								cout<<*(texto+i);
							}
							cout << consigna;
						}
						strcpy(texto,"Saldo actual de la cuenta: ");
						gotoxy(anchopantalla/3,14);
						for(int i=0; i<strlen(texto); i++) {
							cout<<*(texto+i);
						}
						cout<< (cuentas+i)->actual;
					}
				}
			}
		}
		gotoxy(anchopantalla/2-39/2,18);
		system("pause");
		ofstream outputmov("bases de datos de los movimientos.dat", ios::binary|ios::out|ios::app|ios::ate);
		if(!outputmov) {
			cout << "Sin conexion con el archivo de movimientos";
			exit(1);
		}
		outputmov.write((char*)&movimientoaux, sizeof(Movimientos));
		outputmov.close();


		ofstream outputclient("bases de datos de los clientes.dat", ios::binary|ios::out);
		if(!outputclient) {
			cout << "Sin conexion con el archivo de clientes";
			exit(1);
		}
		for(int i = 0; i < tam2; i++) {
			outputclient.write((char*)(clientes+i), sizeof(Cliente));
		}
		outputclient.close();


		ofstream outputcuent("bases de datos de las cuentas.dat", ios::binary|ios::out);
		if(!outputcuent) {
			cout << "Sin conexion con el archivo de cuentas";
			exit(1);
		}
		for(int i = 0; i < tam2; i++) {
			outputcuent.write((char*)(cuentas+i), sizeof(Cuentas));
		}
		outputcuent.close();
	} else {
		strcpy(texto,"Cuenta no encontrada en la base de datos");
		gotoxy(anchopantalla/2-strlen(texto)/2,10);
		for(int i=0; i<strlen(texto); i++) {
			cout<<*(texto+i);
		}
		gotoxy(anchopantalla/2-39/2,12);
		system("pause");
	}
}
int identificacionconsecutivo(int id) {
	int consecutivo = 1;
	int tam;
	Movimientos idarchivo;
	ifstream inputmov("bases de datos de los movimientos.dat",ios::binary|ios::in);
	if(!inputmov) {
		return 1;
	}
	inputmov.seekg(0,inputmov.end);
	tam=inputmov.tellg()/sizeof(Movimientos);
	inputmov.seekg(0);
	for(int i=0; i<tam; i++) {
		inputmov.read((char*)&idarchivo,sizeof(Movimientos));
		if(id==idarchivo.identificacion) {
			consecutivo=idarchivo.consecutivo+1;
		}
	}
	return consecutivo;
}

void consultarMovimientos(Cliente *clientes, Cuentas *cuentas, Movimientos *movimientos) {
	char texto[100];
	int iteracion=0;
	int tecla;
	bool cambio=true;
	int cuenta;
	int identificacion;
	int eleccion;
	int tam1;
	int tam2;
	int tam3;
	int posmov;
	int poscuent;
	int posclient;
	int linea=5;
	bool primero = true;
	bool encontrado = false;
	ifstream inputmov("bases de datos de los movimientos.dat", ios::binary|ios::in);
	if(!inputmov) {
		cout<<"Error, revise si existe almenos un movimiento registrado"<<endl;
		system("pause");
		return;
	}
	ifstream inputclient("bases de datos de los clientes.dat", ios::binary|ios::in);
	ifstream inputcuent("bases de datos de las cuentas.dat", ios::binary|ios::in);
	inputclient.seekg(0, inputclient.end);
	tam1 = inputclient.tellg()/sizeof(Cliente);
	inputclient.close();
	inputcuent.seekg(0, inputcuent.end);
	tam2= inputcuent.tellg()/sizeof(Cuentas);
	inputcuent.close();
	inputmov.seekg(0, inputmov.end);
	tam3 = (inputmov.tellg()/sizeof(Movimientos));
	inputmov.close();
	strcpy(texto,"Como quiere consultar los movimientos de la cuenta");
	gotoxy(anchopantalla/2-strlen(texto)/2,5);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	for(int i=0; i<anchopantalla; i++) {
		for(int j=0; j<altopantalla; j++) {
			if((i==0)||(i==anchopantalla-1)||(j==0)||(j==altopantalla-1)) {
				gotoxy(i,j);
				cout<<char(178);
			}
		}
	}
	strcpy(texto,"Por # de identificacion");
	gotoxy(anchopantalla/3-strlen(texto)/2,7);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	strcpy(texto,"Por # de cuenta");
	gotoxy((anchopantalla/3)*2-strlen(texto)/2,7);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	strcpy(texto,"o");
	gotoxy(anchopantalla/3-strlen(texto)/2,8);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	strcpy(texto,"o");
	gotoxy((anchopantalla/3)*2-strlen(texto)/2,8);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	gotoxy((anchopantalla/3)-strlen(texto)/2,8);
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
				case 75: { //Movimiento a la izquierda
					if(cursor.x==(anchopantalla/3)-strlen(texto)/2) {
						cout<<"o";
						gotoxy((anchopantalla/3)*2-strlen(texto)/2,8);
					}
					if(cursor.x==(anchopantalla/3)*2-strlen(texto)/2) {
						cout<<"o";
						gotoxy((anchopantalla/3)-strlen(texto)/2,8);
					}
					break;
				}
				case 77: { //Movimiento a la derecha
					if(cursor.x==(anchopantalla/3)*2-strlen(texto)/2) {
						cout<<"o";
						gotoxy((anchopantalla/3)-strlen(texto)/2,8);
					}
					if(cursor.x==(anchopantalla/3)-strlen(texto)/2) {
						cout<<"o";
						gotoxy((anchopantalla/3)*2-strlen(texto)/2,8);
					}
					break;
				}
			}
		}
	}
	if(cursor.x==(anchopantalla/3)-strlen(texto)/2)
		eleccion=1;
	if(cursor.x==(anchopantalla/3)*2-strlen(texto)/2)
		eleccion=2;
	switch(eleccion) {
		case 1: {
			strcpy(texto,"Digite el # de identificacion ");
			gotoxy(anchopantalla/3-strlen(texto)/2,12);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			mostrarCursor();
			cin >> identificacion;
			ocultarCursor();
			for(int i = 0; i < tam1; i++) {
				for(int j = 0; j < tam3; j++) {
					if(identificacion == (clientes+i)->identificacion && (clientes+i)->identificacion == (movimientos+j)->identificacion) {
						for(int k = 0; k < tam2; k++) {
							if((clientes+i)->identificacion == (cuentas+k)->cliente.identificacion) {
								poscuent = k;
							}
						}
						encontrado = true;
						if(primero == true) {
							posmov = j;
							posclient = i;
							primero = false;
						}

					}
				}
			}
			break;
		}
		case 2: {
			strcpy(texto,"Digite el # de cuenta ");
			gotoxy(anchopantalla/3*2-strlen(texto)/2,12);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			mostrarCursor();
			cin >> cuenta;
			ocultarCursor();
			for(int i = 0; i <tam2; i++) {
				for(int j = 0; j < tam3; j++) {
					for(int k = 0; k < tam1; k++) {
						if(cuenta == (cuentas+i)->n_cuenta && (cuentas+i)->cliente.identificacion == (clientes+k)->identificacion && (clientes+k)->identificacion == (movimientos+j)->identificacion) {
							encontrado = true;
							if(primero == true) {
								posmov = j;
								poscuent = i;
								posclient = k;
								primero = false;
							}
						}
					}
				}
			}
			break;
		}
		default: {
			break;
		}
	}
	if(encontrado == true) {
		system("cls");
		for(int i=0; i<anchopantalla; i++) {
			for(int j=0; j<altopantalla; j++) {
				if((i==0)||(i==anchopantalla-1)||(j==0)||(j==altopantalla-1)) {
					gotoxy(i,j);
					cout<<char(178);
				}
			}
		}
		strcpy(texto,"Consecutivo");
		gotoxy((anchopantalla/8),3);
		for(int i=0; i<strlen(texto); i++) {
			cout<<*(texto+i);
		}
		strcpy(texto,"Cliente");
		gotoxy((anchopantalla/8)*2,3);
		for(int i=0; i<strlen(texto); i++) {
			cout<<*(texto+i);
		}
		strcpy(texto,"Cuenta");
		gotoxy((anchopantalla/7)*3,3);
		for(int i=0; i<strlen(texto); i++) {
			cout<<*(texto+i);
		}
		strcpy(texto,"Tipo");
		gotoxy((anchopantalla/7)*4,3);
		for(int i=0; i<strlen(texto); i++) {
			cout<<*(texto+i);
		}
		strcpy(texto,"Valor del movimiento");
		gotoxy((anchopantalla/7)*5,3);
		for(int i=0; i<strlen(texto); i++) {
			cout<<*(texto+i);
		}
		for(int i = posmov; i < tam3; i++) {
			if((movimientos+i)->identificacion == identificacion || (movimientos+i)->identificacion == (cuentas+poscuent)->cliente.identificacion) {
				gotoxy((anchopantalla/8),linea);
				cout<<(movimientos+i)->consecutivo;
				gotoxy((anchopantalla/8)*2,linea);
				cout<<(clientes+posclient)->nombres<<" "<<(clientes+posclient)->apellidos;
				gotoxy((anchopantalla/7)*3,linea);
				cout<<(cuentas+poscuent)->n_cuenta;
				if((movimientos+i)->tipo_movimiento == 'R') {
					gotoxy((anchopantalla/7)*4,linea);
					cout << "Retiro" << endl;
				} else {
					gotoxy((anchopantalla/7)*4,linea);
					cout << "Consigna" << endl;
				}
				gotoxy((anchopantalla/7)*5,linea);
				cout<<(movimientos+i)->valor_movimiento;
				linea++;
			}
		}
	} else {
		strcpy(texto,"Cuenta no encontrada");
		gotoxy(anchopantalla/2-strlen(texto)/2,14);
		for(int i=0; i<strlen(texto); i++) {
			cout<<*(texto+i);
		}
	}
	gotoxy(anchopantalla/2-39/2,altopantalla-3);
	system("pause");
}

void Mostrartodo(Cliente *clientes, Cuentas *cuentas, Movimientos *movimientos) {
	int tecla=0;
	int iteracion=0;
	int cuenta;
	int identificacion;
	int eleccion;
	int tam1;
	int tam2;
	int tam3;
	int posmov;
	int poscuent;
	int posclient;
	int linea=13;
	bool cambio=true;
	bool primero = true;
	bool encontradocuenta = false;
	bool encontradomovimiento = false;
	char texto[100];
	ifstream inputmov("bases de datos de los movimientos.dat", ios::binary|ios::in);
	if(!inputmov) {
		cout<<"Error, Verifique si existe almenos un movimiento para consultar"<<endl;
		system("pause");
		return;
	}
	ifstream inputclient("bases de datos de los clientes.dat", ios::binary|ios::in);
	ifstream inputcuent("bases de datos de las cuentas.dat", ios::binary|ios::in);
	inputclient.seekg(0, inputclient.end);
	tam1 = inputclient.tellg()/sizeof(Cliente);
	inputclient.close();
	inputcuent.seekg(0, inputcuent.end);
	tam2= inputcuent.tellg()/sizeof(Cuentas);
	inputcuent.close();
	inputmov.seekg(0, inputmov.end);
	tam3 = (inputmov.tellg()/sizeof(Movimientos));
	inputmov.close();
	strcpy(texto,"Como quiere consultar el reporte general?");
	gotoxy(anchopantalla/2-strlen(texto)/2,3);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	for(int i=0; i<anchopantalla; i++) {
		for(int j=0; j<altopantalla; j++) {
			if((i==0)||(i==anchopantalla-1)||(j==0)||(j==altopantalla-1)) {
				gotoxy(i,j);
				cout<<char(178);
			}
		}
	}
	strcpy(texto,"Por # de identificacion");
	gotoxy(anchopantalla/3-strlen(texto)/2,7);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	strcpy(texto,"Por # de cuenta");
	gotoxy((anchopantalla/3)*2-strlen(texto)/2,7);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	strcpy(texto,"o");
	gotoxy(anchopantalla/3-strlen(texto)/2,8);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	strcpy(texto,"o");
	gotoxy((anchopantalla/3)*2-strlen(texto)/2,8);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	gotoxy((anchopantalla/3)-strlen(texto)/2,8);
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
				case 75: { //Movimiento a la izquierda
					if(cursor.x==(anchopantalla/3)-strlen(texto)/2) {
						cout<<"o";
						gotoxy((anchopantalla/3)*2-strlen(texto)/2,8);
					}
					if(cursor.x==(anchopantalla/3)*2-strlen(texto)/2) {
						cout<<"o";
						gotoxy((anchopantalla/3)-strlen(texto)/2,8);
					}
					break;
				}
				case 77: { //Movimiento a la derecha
					if(cursor.x==(anchopantalla/3)*2-strlen(texto)/2) {
						cout<<"o";
						gotoxy((anchopantalla/3)-strlen(texto)/2,8);
					}
					if(cursor.x==(anchopantalla/3)-strlen(texto)/2) {
						cout<<"o";
						gotoxy((anchopantalla/3)*2-strlen(texto)/2,8);
					}
					break;
				}
			}
		}
	}
	if(cursor.x==(anchopantalla/3)-strlen(texto)/2)
		eleccion=1;
	if(cursor.x==(anchopantalla/3)*2-strlen(texto)/2)
		eleccion=2;
	switch(eleccion) {
		case 1: {
			strcpy(texto,"Digite el # de identificacion ");
			gotoxy(anchopantalla/3-strlen(texto)/2,12);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			mostrarCursor();
			cin >> identificacion;
			ocultarCursor();
			system("cls");
			for(int i=0; i<anchopantalla; i++) {
				for(int j=0; j<altopantalla; j++) {
					if((i==0)||(i==anchopantalla-1)||(j==0)||(j==altopantalla-1)) {
						gotoxy(i,j);
						cout<<char(178);
					}
				}
			}
			for(int i = 0; i < tam2; i++) {
				if(identificacion == (cuentas+i)->cliente.identificacion) {
					strcpy(texto,"REPORTE GENERAL");
					gotoxy(anchopantalla/2-strlen(texto)/2,2);
					for(int i=0; i<strlen(texto); i++) {
						cout<<*(texto+i);
					}
					strcpy(texto,"Datos de cuenta");
					gotoxy(anchopantalla/2-strlen(texto)/2,3);
					for(int i=0; i<strlen(texto); i++) {
						cout<<*(texto+i);
					}
					strcpy(texto,"Cliente");
					gotoxy((anchopantalla/5)-strlen(texto)/2,5);
					for(int i=0; i<strlen(texto); i++) {
						cout<<*(texto+i);
					}
					strcpy(texto,"Cuenta #");
					gotoxy((anchopantalla/5)*2-strlen(texto)/2,5);
					for(int i=0; i<strlen(texto); i++) {
						cout<<*(texto+i);
					}
					strcpy(texto,"Tipo de cuenta");
					gotoxy((anchopantalla/5)*3-strlen(texto)/2,5);
					for(int i=0; i<strlen(texto); i++) {
						cout<<*(texto+i);
					}
					strcpy(texto,"Saldo actual");
					gotoxy((anchopantalla/5)*4-strlen(texto)/2,5);
					for(int i=0; i<strlen(texto); i++) {
						cout<<*(texto+i);
					}
					for(int j = 0; j < tam1; j++) {
						if(identificacion == (clientes+j)->identificacion) {
							encontradocuenta=true;
							gotoxy((anchopantalla/5),7);
							strcpy(texto,(clientes+j)->nombres);
							strcat(texto," ");
							strcat(texto,(clientes+j)->apellidos);
							gotoxy((anchopantalla/5)-strlen(texto)/2,7);
							for(int i=0; i<strlen(texto); i++) {
								cout<<*(texto+i);
							}
							gotoxy((anchopantalla/5)*2-3,7);
							cout << (cuentas+i)->n_cuenta;
							if((cuentas)->tipo == 'A') {
								gotoxy((anchopantalla/5)*3-4,7);
								cout << "Ahorros" << endl;
							} else {
								gotoxy((anchopantalla/5)*3-5,7);
								cout << "Corriente" << endl;
							}
							gotoxy((anchopantalla/5)*4-4,7);
							cout << (cuentas+i)->actual << endl;
						}
					}
				}
			}
			if(encontradocuenta == true) {
				for(int i = 0; i < tam1; i++) {
					for(int j = 0; j < tam3; j++) {
						if(identificacion == (clientes+i)->identificacion && (clientes+i)->identificacion == (movimientos+j)->identificacion) {
							for(int k = 0; k < tam2; k++) {
								if((clientes+i)->identificacion == (cuentas+k)->cliente.identificacion) {
									poscuent = k;
								}
							}
							encontradomovimiento = true;
							if(primero == true) {
								posmov = j;
								posclient = i;
								primero = false;
							}

						}
					}
				}
			}
			if(encontradomovimiento == true) {
				strcpy(texto,"MOVIMIENTOS");
				gotoxy((anchopantalla/2)-strlen(texto)/2,9);
				for(int i=0; i<strlen(texto); i++) {
					cout<<*(texto+i);
				}
				strcpy(texto,"Consecutivos");
				gotoxy((anchopantalla/4)-strlen(texto)/2,11);
				for(int i=0; i<strlen(texto); i++) {
					cout<<*(texto+i);
				}
				strcpy(texto,"Tipo");
				gotoxy((anchopantalla/4)*2-strlen(texto)/2,11);
				for(int i=0; i<strlen(texto); i++) {
					cout<<*(texto+i);
				}
				strcpy(texto,"Valor");
				gotoxy((anchopantalla/4)*3,11);
				for(int i=0; i<strlen(texto); i++) {
					cout<<*(texto+i);
				}
				for(int i = posmov; i < tam3; i++) {
					if((movimientos+i)->identificacion == identificacion || (movimientos+i)->identificacion == (cuentas+poscuent)->cliente.identificacion) {
						gotoxy((anchopantalla/4),linea);
						cout << (movimientos+i)->consecutivo;
						if((movimientos+i)->tipo_movimiento == 'R') {
							gotoxy((anchopantalla/4)*2-3,linea);
							cout << "Retiro" << endl;
						} else {
							gotoxy((anchopantalla/4)*2-4,linea);
							cout << "Consigna" << endl;
						}
						gotoxy((anchopantalla/4)*3,linea);
						cout << (movimientos+i)->valor_movimiento;
						linea++;
					}
				}
			}
			if(encontradocuenta == true && encontradomovimiento == false) {
				strcpy(texto,"Movimientos no encontrados");
				gotoxy((anchopantalla/2)-strlen(texto)/2,10);
				for(int i=0; i<strlen(texto); i++) {
					cout<<*(texto+i);
				}
			} else if(encontradocuenta == false) {
				strcpy(texto,"Cuenta no encontrada");
				gotoxy((anchopantalla/2)-strlen(texto)/2,8);
				for(int i=0; i<strlen(texto); i++) {
					cout<<*(texto+i);
				}
			}
			break;
		}
		case 2: {
			strcpy(texto,"Digite su numero de cuenta ");
			gotoxy(anchopantalla/3*2-strlen(texto)/2,12);
			for(int i=0; i<strlen(texto); i++) {
				cout<<*(texto+i);
			}
			mostrarCursor();
			cin >> cuenta;
			ocultarCursor();
			system("cls");
			for(int i=0; i<anchopantalla; i++) {
				for(int j=0; j<altopantalla; j++) {
					if((i==0)||(i==anchopantalla-1)||(j==0)||(j==altopantalla-1)) {
						gotoxy(i,j);
						cout<<char(178);
					}
				}
			}
			for(int i = 0; i < tam2; i++) {
				if(cuenta == (cuentas+i)->n_cuenta) {
					strcpy(texto,"REPORTE GENERAL");
					gotoxy(anchopantalla/2-strlen(texto)/2,2);
					for(int i=0; i<strlen(texto); i++) {
						cout<<*(texto+i);
					}
					strcpy(texto,"Datos de cuenta");
					gotoxy(anchopantalla/2-strlen(texto)/2,3);
					for(int i=0; i<strlen(texto); i++) {
						cout<<*(texto+i);
					}
					strcpy(texto,"Cliente");
					gotoxy((anchopantalla/5)-strlen(texto)/2,5);
					for(int i=0; i<strlen(texto); i++) {
						cout<<*(texto+i);
					}
					strcpy(texto,"Cuenta #");
					gotoxy((anchopantalla/5)*2-strlen(texto)/2,5);
					for(int i=0; i<strlen(texto); i++) {
						cout<<*(texto+i);
					}
					strcpy(texto,"Tipo de cuenta");
					gotoxy((anchopantalla/5)*3-strlen(texto)/2,5);
					for(int i=0; i<strlen(texto); i++) {
						cout<<*(texto+i);
					}
					strcpy(texto,"Saldo actual");
					gotoxy((anchopantalla/5)*4-strlen(texto)/2,5);
					for(int i=0; i<strlen(texto); i++) {
						cout<<*(texto+i);
					}
					for(int k = 0; k < tam1; k++) {
						if((cuentas+i)->cliente.identificacion == (clientes+k)->identificacion) {
							encontradocuenta=true;
							gotoxy((anchopantalla/5),7);
							strcpy(texto,(clientes+k)->nombres);
							strcat(texto," ");
							strcat(texto,(clientes+k)->apellidos);
							gotoxy((anchopantalla/5)-strlen(texto)/2,7);
							for(int i=0; i<strlen(texto); i++) {
								cout<<*(texto+i);
							}
							gotoxy((anchopantalla/5)*2-3,7);
							cout << (cuentas+i)->n_cuenta;
							if((cuentas+i)->tipo == 'A') {
								gotoxy((anchopantalla/5)*3-4,7);
								cout << "Ahorros" << endl;
							} else {
								gotoxy((anchopantalla/5)*3-5,7);
								cout << "Corriente" << endl;
							}
							gotoxy((anchopantalla/5)*4-4,7);
							cout << (cuentas+i)->actual << endl;
						}
					}
				}
			}
			for(int i = 0; i <tam2; i++) {
				for(int j = 0; j < tam3; j++) {
					for(int k = 0; k < tam1; k++) {
						if(cuenta == (cuentas+i)->n_cuenta && (cuentas+i)->cliente.identificacion == (clientes+k)->identificacion && (clientes+k)->identificacion == (movimientos+j)->identificacion) {
							encontradomovimiento = true;
							if(primero == true) {
								posmov = j;
								poscuent = i;
								posclient = k;
								primero = false;
							}
						}
					}
				}
			}
			if(encontradomovimiento == true) {
				strcpy(texto,"MOVIMIENTOS");
				gotoxy((anchopantalla/2)-strlen(texto)/2,9);
				for(int i=0; i<strlen(texto); i++) {
					cout<<*(texto+i);
				}
				strcpy(texto,"Consecutivos");
				gotoxy((anchopantalla/4)-strlen(texto)/2,11);
				for(int i=0; i<strlen(texto); i++) {
					cout<<*(texto+i);
				}
				strcpy(texto,"Tipo");
				gotoxy((anchopantalla/4)*2-strlen(texto)/2,11);
				for(int i=0; i<strlen(texto); i++) {
					cout<<*(texto+i);
				}
				strcpy(texto,"Valor");
				gotoxy((anchopantalla/4)*3,11);
				for(int i=0; i<strlen(texto); i++) {
					cout<<*(texto+i);
				}
				for(int i = posmov; i < tam3; i++) {
					if((movimientos+i)->identificacion == identificacion || (movimientos+i)->identificacion == (cuentas+poscuent)->cliente.identificacion) {
						gotoxy((anchopantalla/4),linea);
						cout << (movimientos+i)->consecutivo;
						if((movimientos+i)->tipo_movimiento == 'R') {
							gotoxy((anchopantalla/4)*2-3,linea);
							cout << "Retiro" << endl;
						} else {
							gotoxy((anchopantalla/4)*2-4,linea);
							cout << "Consigna" << endl;
						}
						gotoxy((anchopantalla/4)*3,linea);
						cout << (movimientos+i)->valor_movimiento;
						linea++;
					}
				}
			}
			if(encontradocuenta == true && encontradomovimiento == false) {
				strcpy(texto,"Movimientos no encontrados");
				gotoxy((anchopantalla/2)-strlen(texto)/2,10);
				for(int i=0; i<strlen(texto); i++) {
					cout<<*(texto+i);
				}
			} else if(encontradocuenta == false) {
				strcpy(texto,"Cuenta no encontrada");
				gotoxy((anchopantalla/2)-strlen(texto)/2,8);
				for(int i=0; i<strlen(texto); i++) {
					cout<<*(texto+i);
				}
			}
			break;
		}
	}
	gotoxy((anchopantalla/2)-39/2,altopantalla-3);
	system("pause");
}

//funciones de decoracion
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
void despedida() {
	char texto[100];
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
	strcpy(texto,"        V       ");
	gotoxy((anchopantalla/2)-strlen(texto)/2,18);
	for(int i=0; i<strlen(texto); i++) {
		cout<<*(texto+i);
	}
	cursor=obtenerPosicionCursor();
	gotoxy(0,cursor.y+2);
	system("pause");
	exit(1);
}