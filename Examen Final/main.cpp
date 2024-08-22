#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<ctype.h>
#include<ctime>
#include<string>
#include<sstream>
#include <algorithm>

using namespace std;

//constantes necesarias para el almacenamiento de los registros
//Valores de prueba, a nivel real, se deberán utilizar registros más grandes
const int MAX_VIAJEROS = 30;
const int MAX_REGISTROS = 60;
 
 //Atributo para color de letra
HANDLE hConsoleHandle = GetStdHandle (STD_OUTPUT_HANDLE);
 
//Estructuras de datos necesarias para el funcionamiento del programa
struct Documento { //registra el tipo de documento y número del mismo. 
	string tipo;
	string numero;
};

struct InformacionPersonal { //registra la información importante de una persona
	string nombre;
	string apellido;
	string nacionalidad;
	string fechaNacimiento;
};

struct Viajero { //registra la información del viajero 
	int id;
	InformacionPersonal infoPersonal;
	Documento documento;
};

struct Registro { //registra la información del los viajes
	int id;
	int idViajero;
	string lugarSalida;
	string lugarLlegada;
	string fecha;
	string hora;
	string numeroTicket;
};

struct Lugar { //registra la información del los lugares
	string ciudad;
	string pais;
};

 
 //Variables Globales
Viajero viajeros[MAX_VIAJEROS];
Registro registros[MAX_REGISTROS];
Lugar lugares[MAX_REGISTROS];
int cantidadViajeros = 0;
int cantidadRegistros = 0;
 
 
//prototipos de funciones y procedimientos
void gotoxy(int x ,int y);
void cuadro(int x1, int y1, int x2, int y2);
void registrarViajero();
void registrarEntradaSalida();
void eliminarViajero();
void ordenarViajerosPorNombreBurbuja();
void consultarViajeros();
void consultarRegistros();
void menu();
 
 
 /***********************************************************************************************/
//procedimientos y funciones
void gotoxy(int x ,int y){
	
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);

}
void cuadro(int x1, int y1, int x2, int y2){
	int i;
	
	for (i=x1; i<=x2;i++){
		gotoxy(i,y1); printf("%c",205);   
		gotoxy(i,y2); printf("%c",205);   
	}

	for (i=y1; i<=y2;i++){
		gotoxy(x1,i); printf("%c",186);  
		gotoxy(x2,i); printf("%c",186);   
	}

	
	gotoxy(x1,y1); printf("%c",201);   
	gotoxy(x1,y2); printf("%c",200);  
	gotoxy(x2,y1); printf("%c",187);  
	gotoxy(x2,y2); printf("%c",188);  

}
void registrarViajero() { //Método que sirve para registrar un viajero
	
	char sigue;

	do{
		system("cls");
	
		cuadro(10,7,95,24);
		cuadro(18,3,40,5); 
		SetConsoleTextAttribute (hConsoleHandle, 10);
		gotoxy(22,04); printf("INGRESANDO DATOS");
	
		if (cantidadViajeros >= MAX_VIAJEROS) {
			cout << "No se pueden registrar más viajeros.\n";
			return;
		}
	
		Viajero v;
		v.id = cantidadViajeros + 1;
	
		gotoxy(16,8);cout << "Ingrese el nombre del viajero: ";
		cin >> v.infoPersonal.nombre;
		gotoxy(16,10);cout << "Ingrese el apellido del viajero: ";
		cin >> v.infoPersonal.apellido;
		gotoxy(16,12);cout << "Ingrese la nacionalidad: ";
		cin >> v.infoPersonal.nacionalidad;
		gotoxy(16,14);cout << "Ingrese la fecha de nacimiento (DD/MM/AAAA): ";
		cin >> v.infoPersonal.fechaNacimiento;
	
		gotoxy(16,16);cout << "Ingrese el tipo de documento (Pasaporte, DNI, etc.): ";
		cin >> v.documento.tipo;
		gotoxy(16,18);cout << "Ingrese el numero de documento: ";
		cin >> v.documento.numero;
	
		viajeros[cantidadViajeros] = v;
		cantidadViajeros++;
		gotoxy(16,20);cout << "Viajero registrado con éxito \n";
		
		do{
			SetConsoleTextAttribute (hConsoleHandle, 2);
			gotoxy(75,23);cout << "Desea Continuar S/N";
			sigue=getch();

		}while (toupper(sigue)!='S' && toupper(sigue)!='N');
	
	}while (tolower(sigue)=='s');	
}
void registrarEntradaSalida() { //Método que sirve para registrar la entrada o salida del viajero
	
	char sigue;

	do{
		system("cls");
	
		cuadro(10,7,95,24);
		cuadro(18,3,40,5); 
		SetConsoleTextAttribute (hConsoleHandle, 10);
		gotoxy(22,04); printf("REGISTROS");
	
	
		if (cantidadRegistros >= MAX_REGISTROS) {
			cout << "No se pueden registrar más entradas/salidas." << endl;
			return;
		}
	
		Registro r;
		r.id = cantidadRegistros + 1;
	
		gotoxy(16,8);cout << "Ingrese el ID del viajero: ";
		cin >> r.idViajero;
		cin.ignore(); //Permite ignorar lo ingresado anteriormente y no saltarse una línea
		gotoxy(16,10);cout << "Ingrese el lugar de salida (ciudad, pais): ";
		getline(cin, r.lugarSalida);  //línea que funciona para incluir espacios   
		gotoxy(16,12);cout << "Ingrese el lugar de llegada (ciudad, pais): ";
		getline(cin, r.lugarLlegada); //línea que funciona para incluir espacios  
		gotoxy(16,14);cout << "Ingrese la fecha (DD/MM/AAAA): ";
		cin >> r.fecha;
		gotoxy(16,16);cout << "Ingrese la hora (HH:MM): ";
		cin >> r.hora;
		gotoxy(16,18);cout << "Ingrese el numero de ticket: ";
		cin >> r.numeroTicket;
	
		registros[cantidadRegistros] = r;
		cantidadRegistros++;
		gotoxy(16,22);cout << "Registro de entrada/salida realizado con exito." << endl;
	
		do{
			SetConsoleTextAttribute (hConsoleHandle, 2);
			gotoxy(75,23);cout << "Desea Continuar S/N";
			sigue=getch();

		}while (toupper(sigue)!='S' && toupper(sigue)!='N');
	
	}while (tolower(sigue)=='s');
	
	
}
void eliminarViajero() { ////Método que sirve para eliminar a un viajero
	char sigue;
	int id;
	
	do{
		system("cls");
	
		cuadro(10,7,95,24);
		cuadro(18,3,40,5); 
		SetConsoleTextAttribute (hConsoleHandle, 10);
		gotoxy(22,04); printf("ELIMINAR VIAJERO");
	
		gotoxy(16,8);cout << "Ingrese el ID del viajero a eliminar: ";
		cin >> id;
	
		for (int i = 0; i < cantidadViajeros; i++) { //Se recorre todo el vector de viajeros
			if (viajeros[i].id == id) { //si se encuentra el viajero, se realiza la eliminación y se corre una posición hacia atrás
				for (int j = i; j < cantidadViajeros - 1; j++) {
					viajeros[j+1].id = viajeros[j].id; //El último viajero toma el ID del viajero eliminado, para que quede en secuencia
					viajeros[j] = viajeros[j + 1]; //El último viajero toma el la posición viajero eliminado, para que quede en secuencia
					
				}
				cantidadViajeros--;
				
				gotoxy(16,10);cout << "Viajero eliminado con éxito." << endl;
			}else{
				gotoxy(16,10);cout << "Viajero no encontrado." << endl;
			}
		}
		
		
		do{
			SetConsoleTextAttribute (hConsoleHandle, 2);
			gotoxy(75,23);cout << "Desea Continuar S/N";
			sigue=getch();

		}while (toupper(sigue)!='S' && toupper(sigue)!='N');
	
	}while (tolower(sigue)=='s');
		
}
void ordenarViajerosPorNombreBurbuja() { //Método que ayuda a ordenar a los viajeros alfabéticamente de la A -Z mediante el algoritmo burbuja
	
	char sigue;
	int id;
	
	do{
		system("cls");
	
		cuadro(10,7,95,24);
		cuadro(18,3,45,5); 
		SetConsoleTextAttribute (hConsoleHandle, 10);
		gotoxy(22,04); printf("ORDENAMIENTO");
	
		for (int i = 0; i < cantidadViajeros - 1; i++) {
			for (int j = 0; j < cantidadViajeros - i - 1; j++) {
				if (viajeros[j].infoPersonal.nombre > viajeros[j + 1].infoPersonal.nombre) {
					swap(viajeros[j], viajeros[j + 1]);
				}
			}
		}
		
		//El algoritmo va posición por posición y si encuentra que el siguiente de n (n+1) es alfabétocamente
		//superior a él, se intercambian posiciones. 
		
		gotoxy(22,10);cout << "Viajeros ordenados por nombre (Burbuja)." << endl;
		do{
			SetConsoleTextAttribute (hConsoleHandle, 2);
			gotoxy(75,23);cout << "Desea Continuar S/N";
			sigue=getch();

		}while (toupper(sigue)!='S' && toupper(sigue)!='N');
	
	}while (tolower(sigue)=='s');
		
}
void consultarViajeros() {//método para ver todos los viajeros ingresados
	char sigue;
	int id;
	
	do{
		system("cls");
	
	
		for (int i = 0; i < cantidadViajeros; i++) {
			cout << "ID: " << viajeros[i].id 
				<< ", Nombre: " << viajeros[i].infoPersonal.nombre
				<< ", Apellido: " << viajeros[i].infoPersonal.apellido
				<< ", Nacionalidad: " << viajeros[i].infoPersonal.nacionalidad
				<< ", Fecha de Nacimiento: " << viajeros[i].infoPersonal.fechaNacimiento
				<< ", Tipo Documento: " << viajeros[i].documento.tipo
				<< ", Numero Documento: " << viajeros[i].documento.numero << endl;
		}
	
		do{
			SetConsoleTextAttribute (hConsoleHandle, 2);
			gotoxy(75,23);cout << "Desea Continuar S/N";
			sigue=getch();

		}while (toupper(sigue)!='S' && toupper(sigue)!='N');
	
	}while (tolower(sigue)=='s');
}
void consultarRegistros() {//método para ver todos registros de ingresos y salidas ingresados
	
	char sigue;
	int id;
	
	do{
		system("cls");
	
	
		for (int i = 0; i < cantidadRegistros; i++) {
			cout << "ID Registro: " << registros[i].id 
				<< ", ID Viajero: " << registros[i].idViajero
				<< ", Lugar de Salida: " << registros[i].lugarSalida
				<< ", Lugar de Llegada: " << registros[i].lugarLlegada
				<< ", Fecha: " << registros[i].fecha
				<< ", Hora: " << registros[i].hora
				<< ", Numero de Ticket: " << registros[i].numeroTicket << endl;
		}
		
		do{
			SetConsoleTextAttribute (hConsoleHandle, 2);
			gotoxy(75,23);cout << "Desea Continuar S/N";
			sigue=getch();

		}while (toupper(sigue)!='S' && toupper(sigue)!='N');
	
	}while (tolower(sigue)=='s');
		
}
void menu(){ //método del menú
	char opc,conti;
	
	do{
		
		system("cls");
		cuadro(16,1,65,3); //primer cuadro de arriba hacia abajo
		cuadro(8,4,72,22);//grande
		cuadro(8,23,72,25); //cuadro de abajo opcion es
		cuadro(59,19,71,21); //cuadro pequeño salir

		SetConsoleTextAttribute (hConsoleHandle, 10);
	    gotoxy(22,2);printf("***** MIGRACION DE COSTA RICA *****");
        SetConsoleTextAttribute (hConsoleHandle, 15);
	    gotoxy(15,5);printf("[1]  REGISTRAR VIAJERO");
		gotoxy(15,7);printf("[2]  REGISTRAR ENTRADA/SALIDA");
		gotoxy(15,9);printf("[3]  ELIMINAR VIAJERO");
		gotoxy(15,11);printf("[4]  ORDENAR VIAJEROS POR NOMBRE");
		gotoxy(15,13);printf("[5]  CONSULTAR VIAJEROS");
		gotoxy(15,15);printf("[6]  CONSULTAR REGISTROS DE ENTRADA Y SALIDA");

		
		gotoxy(60,20);printf("<[7] SALIR>");
		
		SetConsoleTextAttribute(hConsoleHandle,14);
		gotoxy(15,24);printf("Su opcion es: ");
		opc=getch();

		switch(opc){
		case '1':
			registrarViajero();
			break;
		case '2':
			registrarEntradaSalida();
			break;
		case '3':
			eliminarViajero();
			break;
		case '4':
			ordenarViajerosPorNombreBurbuja();
			break;
		case '5':
			consultarViajeros();
			break;
		case '6':
			consultarRegistros();
			break;
		case '7': 
				
			system("cls");
			gotoxy(20,10);printf("Estas seguro Que Deseas Salir del Sistema");
			SetConsoleTextAttribute (hConsoleHandle, 2);
			gotoxy(20,15);printf("Desea Continuar S/N");
			conti=getch();

			if (conti=='N' || conti=='n')
				menu();
			else if (conti=='S' || conti=='s')

				break; 
		
		}
			

		}while(opc!='7');
}
 
int main(int argc, char** argv) {
	
	menu();
	
	return 0;
}
