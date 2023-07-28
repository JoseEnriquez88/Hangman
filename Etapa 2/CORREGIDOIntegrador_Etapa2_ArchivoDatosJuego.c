/*Etapa 2: Estructuras compuestas: listas 
(implementación estática mediante arrays)
1. Modificar el procedimiento de “ingresar datos” para que a medida 
que se ingresen los datos, se almacene la estructura que contiene los 
datos en una lista estática de datos.
2. Escribir las funciones necesarias para que el usuario pueda verificar 
los datos que posteriormente se grabaran en el archivo:
- Mostrar datos (recorrer la lista)
- Eliminar un dato (¿a partir de la selección del código de 
identificación del dato o del nombre?)
3. Modificar la función que graba los datos para que, en lugar de
grabar de un dato a la vez, los grabe a medida que recorra la lista 
de datos.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*DELCARACION DE CONSTANTES*/
#define MAX 4 /*Maximo de elementos de la lista de datos*/

/*TIPOS DE DATOS PERSONALIZADOS*/
typedef char t_string[25];/*Tipo de dato para palabras y oraciones cortas*/
typedef char t_string_2[500];/*Tipo de dato para oraciones largas*/

typedef struct{
	t_string categoria;
	t_string palabra;
	t_string_2 descripcion;
}t_regDatoJuego;/*Tipo de dato compuesto prara modelar los datos del juego*/

typedef t_regDatoJuego t_arrayDatosJuego[MAX];/*Tipo de dato para modelar un arreglo de datos del juego*/

typedef struct {
	t_arrayDatosJuego datoJuego;
	int maxElem;
}t_listaDatosJuego;/*Tipo de dato para modelar una lista de los datos del juego*/

/*PROTOTIPOS DE PROCEDIMIENTOS/FUNCIONES*/
/*Procedimientos para grabar o leer un archivo binario de datos*/
void abrirArchivo_ab();
void grabarDatos();

void abrirArchivo_rb();
void procesarDatos();

void finalizarProceso();

/*Procedimientos para manejar una lista*/
void inicializarLista();
bool listaVacia( t_listaDatosJuego );
bool listaLlena( t_listaDatosJuego );
void ingresarDatoLista( t_regDatoJuego, t_listaDatosJuego );
void vizualizarLista( t_listaDatosJuego );
void eliminarDeLaLista( int, t_listaDatosJuego );

/*Procedimientos complementarios*/
void ingresarDatosJuego();
void menu();
void continuar();
void iniciarPrograma();

/*DECLARACION DE VARIABLES GLOBALES*/
FILE * v_fileDatosJuego;/*Variable puntero a un archivo*/
t_listaDatosJuego v_listaDatosJuego;/*Variable de una lista de datos*/
t_regDatoJuego datoVacio;/*Variable para modelar un dato vacio*/

/*BLOQUE PRINCIPAL*/
int main() {
	iniciarPrograma();
	
	return 0;
}
/*DESARROLLO DE PROCEDIMIENTOS/FUNCIONES*/

/*Procedimiento que inicializa la lista*/
void inicializarLista() {
	v_listaDatosJuego.maxElem = -1;
}

/*Función que devuelve verdadero si la lista esta vacia*/
bool listaVacia( t_listaDatosJuego p_lista ) {
	return p_lista.maxElem == -1;
}

/*Funcion que devuelve verdadero si la lista esta llena*/
bool listaLlena( t_listaDatosJuego p_lista ) {
	return p_lista.maxElem == MAX-2; /*MAX-2 para que siempre quede libre un espacio en el vector*/
}

/*Procedimiento que permite ingresar un dato a una lista*/
void ingresarDatoLista( t_regDatoJuego p_dato, t_listaDatosJuego p_lista ) {
	if ( listaLlena(p_lista) ) {
		printf("\n\t\tLista llena\n");
	}else {
		v_listaDatosJuego.maxElem++;
		v_listaDatosJuego.datoJuego[v_listaDatosJuego.maxElem] = p_dato;
		
		printf("\n\n\t\tSe agrego el dato.\n");
	}
}

/*Procedimiento que permite ver los datos dentro de la lista*/
void vizualizarLista( t_listaDatosJuego p_lista ) {
	if ( listaVacia(p_lista) ) {
		printf("\n\t\tLista vacia\n");
	}else {
		int i;
		printf("\nDatos de la lista:\n");
		for( i=0; i<=p_lista.maxElem; i++ ) {
			printf("\n%d. Categoria: %s \nPalabra: %s \nDescripcion: %s\n", i+1
									, p_lista.datoJuego[i].categoria
									, p_lista.datoJuego[i].palabra
									, p_lista.datoJuego[i].descripcion );
		}
		
	}
}

/*Procedimiento que permite eliminar un dato en una posicion cualquiera (K), dentro de la lista*/
void eliminarDeLaLista( int k, t_listaDatosJuego p_lista ) {
	if( listaVacia(p_lista) ) {
		printf("\n\t\tLista vacia");
	}else {
		int i;
		
		v_listaDatosJuego.datoJuego[k-1] = datoVacio;
		
		for( i=k-1; i<=p_lista.maxElem; i++) { /*Permite reorganizar los elementos una vez eliminado el elemento k*/
			v_listaDatosJuego.datoJuego[i] = v_listaDatosJuego.datoJuego[i+1];
		}
		v_listaDatosJuego.datoJuego[v_listaDatosJuego.maxElem] = datoVacio;/*Se elimina el valor duplicado*/
		
		v_listaDatosJuego.maxElem--;
		
		printf("\n\t\tDato eliminado\n");
	}
}

/*Procedimiento que permite crear un archivo binario de datos*/
void abrirArchivo_ab() {
	/*Se abre el archivo en modo escritura binaria*/
	v_fileDatosJuego = fopen("Datos_JuegoAhorcado.dat","ab");
	
	/*Se verifica que exista el el archivo*/
	if( v_fileDatosJuego == NULL ) {
		printf("\n\t\tNo se encontro el archivo");
		exit(EXIT_FAILURE);
	}
}

/*Procedimiento que nos permite grabar los datos a un archivo*/
void grabarDatos() {
	
	if( listaVacia(v_listaDatosJuego) ) {
		printf("\n\t\tNo hay datos en la lista para grabar.\n");
	}else {
		
		int i;
		for( i=0; i<= v_listaDatosJuego.maxElem; i++ ) {
			
			fwrite(&v_listaDatosJuego.datoJuego[i], sizeof(t_regDatoJuego), 1, v_fileDatosJuego);
			printf("\n\tRegistro insertado\n");
		}
	}
	
}

/*Procemiento que nos permite abrir el archivo en modo lectura*/
void abrirArchivo_rb() {
	v_fileDatosJuego = fopen("Datos_JuegoAhorcado.dat","rb");
	
	if( v_fileDatosJuego == NULL ) {
		printf("\n\t\tNo se encontro el archivo.");
		exit(EXIT_FAILURE);
	}
}

/*Procedimiento que permite mostrar por pantalla los datos dentro del archivo*/
void procesarDatos() {
	system("cls");
	
	t_regDatoJuego v_regDatosJuego;
	fread(&v_regDatosJuego, sizeof(t_regDatoJuego), 1, v_fileDatosJuego);
	while( !feof( v_fileDatosJuego ) ) {
		
		printf("\nCategoria: %s \nPalabra: %s \nDescripcion: %s\n", v_regDatosJuego.categoria, v_regDatosJuego.palabra, v_regDatosJuego.descripcion);
		
		fread(&v_regDatosJuego, sizeof(t_regDatoJuego), 1, v_fileDatosJuego);
	}
}

/*Procedimiento que cierra el flujo de datos de un archivo*/
void finalizarProceso() {
	fclose(v_fileDatosJuego);
}

/*Procedimiento que permite ingresar los datos por teclado*/
void ingresarDatosJuego() {
	char opcion = 's';
	t_regDatoJuego DatoJuego;
	
	
	printf("\nDesea ingresar un dato?(s-Si/n-No): ");
	fflush(stdin);
	scanf("%c", &opcion);
	while( opcion != 'n' && !listaLlena(v_listaDatosJuego) ){
		
		printf("\nIngrese los siguientes datos:\n");
	
		printf("\n\tCategoria: ");
		fflush(stdin);
		gets(DatoJuego.categoria);
	
		printf("\n\tPalabra: ");
		fflush(stdin);
		gets(DatoJuego.palabra);
	
		printf("\n\tDescripcion: ");
		fflush(stdin);
		gets(DatoJuego.descripcion);
		
		ingresarDatoLista( DatoJuego, v_listaDatosJuego );
		
		printf("\nDesea ingresar mas datos?(s-Si/n-No): ");
		fflush(stdin);
		scanf("%c", &opcion);
	}
	
	printf("\n\n%s", listaLlena(v_listaDatosJuego)? "La lista esta llena." : " ");
}

/*Procedimiento que permite crear un menu*/
void menu() {
	char opcion;
	int k;
	
	system("cls");
	
	printf("\n\t*** JUEGO DEL AHORCADO ***\n");
	printf("\n\t\t  +---+");
	printf("\n\t\t  |   |");
	printf("\n\t\t  O   |");
	printf("\n\t\t /|\   |");
	printf("\n\t\t / \   |");
	printf("\n\t\t      |");
	printf("\n\t\t =========\n");
	
	printf("\n\t\t***  MENU  ***\n");
	printf("\n\t1.Ingresar datos a la lista\n\t2.Vizualizar lista\n\t3.Eliminar dato de la lista");
	printf("\n\t4.Grabar datos\n\t5.Mostrar Datos\n\n\tx.Salir\n\n\n\tOpcion: ");
	fflush(stdin);
	scanf("%c", &opcion);	
	
	switch( opcion ) {
		case '1':
					ingresarDatosJuego();
					continuar();
					menu();			

			break;
		case '2':
					vizualizarLista( v_listaDatosJuego );
					continuar();
					menu();
			break;
		case '3':
					if( listaVacia(v_listaDatosJuego) ) {
						printf("\n\t\tLista vacia.");
					}else {
						vizualizarLista( v_listaDatosJuego );
						printf("\nDigite la posicion que desea eliminar:");
						scanf("%d", &k);
					
						eliminarDeLaLista( k, v_listaDatosJuego );
					}
					
					continuar();
					menu();
			break;
		case '4':
					abrirArchivo_ab();
					grabarDatos();
					
					continuar();
					finalizarProceso();
					menu();
			break;
		case '5':
					abrirArchivo_rb();
					procesarDatos();
					
					continuar();
					finalizarProceso();
					menu();
					
			break;
		case 'x':
			
			break;
		default:
					printf("\n\n\t\tOPCION INVALIDA. DIGITE SOLO LAS OPCIONES QUE SE MUESTRAN EN EL MENU");
					
					continuar();
					menu();
			break;
	}
	
}

/*Procedimiento que permite simular la funcion system("pause")*/
void continuar() {
	printf("\n\nPara continuar presione una tecla...\n");
	getch();
}

void iniciarPrograma(){
	strcpy(datoVacio.categoria," ");
	strcpy(datoVacio.palabra," ");/*Se inicializa el dato vacio*/
	strcpy(datoVacio.descripcion," ");
	
	inicializarLista();
	menu();
}
