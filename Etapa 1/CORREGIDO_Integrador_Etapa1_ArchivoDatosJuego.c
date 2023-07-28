/*Crear un programa en lenguaje “C” que permita generar un archivo
binario de datos en elcontexto del software que desarrollaran. Para 
ello será necesario que se permita ingresar por teclado los datos 
que fuesen necesarios. El programa deberá construirse 
con “estructuras” y contener las funciones necesarias*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


/*DECLARACION DE CONSTANTES*/

/*TIPOS DE DATOS PERSONALIZADOS*/
typedef char t_string[25]; /*Tipo de dato para palabras y oraciones cortas*/
typedef char t_string_2[100]; /*Tipo de dato para oraciones largas*/

typedef struct{
	t_string categoria;
	t_string palabra;
	t_string_2 descripcion;
}t_regDatoJuego; /*Tipo de dato compuesto para modelar los datos del juego*/

/*PROTOTIPOS DE PROCEDIMIENTOS/FUNCIONES*/
/*Procedimientos para grabar o leer un archivo binario de datos*/
void abrirArchivo_ab();
void grabarDatos();

void abrirArchivo_rb();
void procesarDatos();

void finalizarProceso();

/*Procedimientos complementarios*/
void ingresarDatosJuego();
void menu();
void continuar();
void informacionDelJuego();

/*DECLARACION DE VARIABLES GLOBALES*/
t_regDatoJuego v_regDatosJuego;/*Variable que contendra los datos de un registro*/
FILE * v_fileDatosJuego;/*Variable puntero a un archivo*/

/*BLOQUE PRINCIPAL*/
int main() {
	menu();
	return 0;
}

/*DESARROLLO DE PROCEDIMIENTOS/FUNCIONES*/
/*Procedimiento que permite crear un archivo binario de datos*/
void abrirArchivo_ab() {
	v_fileDatosJuego = fopen("Datos_JuegoAhorcado.dat","wb");
	
	if( v_fileDatosJuego == NULL ) {
		printf("No se encontro el archivo...");
		exit(EXIT_FAILURE);
	}
}

/*Procedimiento que nos permite grabar los datos a un archivo*/
void grabarDatos() {
	char opcion;
	 
	printf("\nDesea ingresar datos de la palabra a adivinar? \n(s-Si/n-No): ");
	fflush(stdin);
	scanf("%c", &opcion);
	
	while( tolower(opcion) != 'n' ) {
		
		ingresarDatosJuego();
		
		fwrite(&v_regDatosJuego, sizeof(v_regDatosJuego), 1, v_fileDatosJuego);
		printf("\tRegistro insertado\n");
		
		printf("\nDesea ingresar datos de una nueva palabra? \n(s-Si/n-No): ");
		fflush(stdin);
		scanf("%c", &opcion);
		system("cls");
	}
}

/*Procedimiento que permite abrir el archivo en modo lectura*/
void abrirArchivo_rb() {
	v_fileDatosJuego = fopen("Datos_JuegoAhorcado.dat","rb");
	
	if( v_fileDatosJuego == NULL ) {
		printf("No se encontro el archivo...");
		exit(EXIT_FAILURE);
	}
}

/*Procedimiento que permite mostrar por pantalla los datos dentro del archivo*/
void procesarDatos() {
	system("cls");
	
	fread(&v_regDatosJuego, sizeof(v_regDatosJuego), 1, v_fileDatosJuego);
	while( !feof( v_fileDatosJuego ) ) {
		
		printf("\nCategoria: %s \nPalabra: %s \nDescripcion: %s\n", v_regDatosJuego.categoria, v_regDatosJuego.palabra, v_regDatosJuego.descripcion);
		
		fread(&v_regDatosJuego, sizeof(v_regDatosJuego), 1, v_fileDatosJuego);
	}
}

/*Procedimiento que cierra el flujo de datos de un archivo*/
void finalizarProceso() {
	fclose(v_fileDatosJuego);
	printf("\n\nArchivo cerrado");
}

/*Procedimiento que permite ingresar los datos por teclado*/
void ingresarDatosJuego() {
	informacionDelJuego();
	printf("\nIngrese los siguientes datos:\n");
	
	printf("\n\tCategoria: ");
	fflush(stdin);
	gets(v_regDatosJuego.categoria);
	
	printf("\n\tPalabra: ");
	fflush(stdin);
	gets(v_regDatosJuego.palabra);
	
	printf("\n\tDescripcion: ");
	fflush(stdin);
	gets(v_regDatosJuego.descripcion);
	
	printf("\n");
}
/*Procedimiento que permite crear un menu*/
void menu() {
	char opcion;
	
	system("cls");
	printf("\n\t*** JUEGO DEL AHORCADO ***\n");
	printf("\n\t\t  +---+");
	printf("\n\t\t  |   |");
	printf("\n\t\t  O   |");
	printf("\n\t\t /|\   |");
	printf("\n\t\t / \   |");
	printf("\n\t\t      |");
	printf("\n\t\t =========\n");
	
	printf("\n\t\tMENU \n");
	printf("\n\t1_Grabar datos\n\t2_Mostrar Datos\n\n\tx_Salir\n\n\n\tOpcion: ");
	fflush(stdin);
	scanf("%c", &opcion);	
	
	switch( opcion ) {
		case '1':
					abrirArchivo_ab();
					grabarDatos();
					
					continuar();
					finalizarProceso();
					menu();
					
			break;
		case '2':
					abrirArchivo_rb();
					procesarDatos();
					
					continuar();
					finalizarProceso();
					menu();
					
			break;
		case 'x':
			
			break;
		default:
					printf("\n\nOPCION INVALIDA!!!");
					
					continuar();
					menu();
			break;
	}
	
}

/*Procedimiento que permite simular la funcion system("pause")*/
void continuar() {
	printf("\n\nPara continuar presionar una tecla...\n");
	getch();
}

void informacionDelJuego(){
	printf("\n\t\tACLARACION\nLa informacion ingresada servira para distribuir la misma al momento de la ejecucion del juego.");
	printf("\n1-La CATEGORIA resulta de una clasificacion de cosas.\n\tPor ejemplo: ANIMALES - COLORES.");
	printf("\n2-PALABRA: debera ingresar la palabra a adivinar.");
	printf("\n3-DESCRIPCION: servira para guiar al jugador acerca de la palabra a adivinar.\n");
}
