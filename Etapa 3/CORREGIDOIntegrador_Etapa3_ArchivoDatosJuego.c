/*Etapa 3: Estructuras compuestas enlazadas (implementación dinámica 
mediante listas enlazadas)
1. Modificar la función de “IngresarDatos ()” para que a medida que se 
ingresen los datos, se almacene la estructura que contiene los datos en 
una lista enlazada de datos en lugar de la lista estática programada en 
la etapa anterior.
2. Modificar las funciones necesarias para que el usuario pueda verificar
los datos que posteriormente se grabaran en el archivo (Mostrar lista de
datos, eliminar un dato, etc.) para que apliquen a las funciones 
correspondientes a las listas.
3. Modificar la función que graba los datos para que recorra la lista 
enlazada de datos, en lugar de recorrer la lista estática y a medida que 
acceda a un nodo con contenido correspondiente a un dato lo grabe en el 
archivo de datos.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*DECLARACION DE CONSTANTES*/
#define MAX 4 /*Maximo de elementos de la lista de datos*/

/*TIPOS DE DATOS PERSONALIZADOS*/
typedef char t_string[25];/*Tipo de dato para palabras y oraciones cortas*/
typedef char t_string_2[500]; /*Tipo de dato para oraciones largas*/

typedef struct{
	t_string categoria;
	t_string palabra;
	t_string_2 descripcion;
}t_regDatoJuego;/*Tipo de dato compuesto para modelar los datos del juego*/

typedef struct nodo {
	t_regDatoJuego datoJuego;
	struct nodo * siguiente;
}t_listaDatosJuego; /*Tipo de dato para modelar una lista de los datos del juego*/

/*PROTOTIPOS DE PROCEDIMIENTOS/FUNCIONES*/
/*Procedimientos para grabar o leer un archivo binario de datos*/
void abrirArchivo_ab();
void grabarDatos();

void abrirArchivo_rb();
void procesarDatos();

void finalizarProceso();

/*Procedimientos para manejar una lista*/
void inicializarLista();
bool listaVacia( t_listaDatosJuego * );
void ingresarDatoLista( t_regDatoJuego );
void vizualizarLista( t_listaDatosJuego * );
void eliminarDeLaLista( int );

/*Procedimientos complementarios*/
void ingresarDatosJuego();
void menu();
void continuar();
void iniciarPrograma();

/*DECLARACION DE VARIABLES GLOBALES*/
FILE * v_fileDatosJuego; /*Variable puntero a un archivo*/
t_listaDatosJuego * v_listaDatosJuego; /*Variable de una lista de datos*/
t_regDatoJuego datoVacio; /*Variable para modelar un dato vacio*/

/*BLOQUE PRINCIPAL*/
int main() {
	iniciarPrograma();
	return 0;
}
/*DESARROLLO DE PROCEDIMIENTOS/FUNCIONES*/

/*Procedimiento que inicializa la lista*/
void inicializarLista() {
	v_listaDatosJuego = NULL;
}

/*Función que devuelve verdadero si la lista esta vacia*/
bool listaVacia( t_listaDatosJuego * p_lista ) {
	return v_listaDatosJuego == NULL;
}

/*Procedimiento que permite ingresar un dato a una lista*/
void ingresarDatoLista( t_regDatoJuego p_dato ) {
	t_listaDatosJuego * nuevoNodo;
	nuevoNodo = (t_listaDatosJuego*) malloc( sizeof(t_listaDatosJuego) );
	nuevoNodo->datoJuego = p_dato;
	nuevoNodo->siguiente = v_listaDatosJuego;
	v_listaDatosJuego = nuevoNodo;
	printf("\n\tDato insertado.\n");
}

/*Procedimiento que permite ver los datos dentro de la lista*/
void vizualizarLista( t_listaDatosJuego * p_lista ) {
	if ( listaVacia(p_lista) ) {
		printf("\nLista vacia...\n");
	}else {
		t_listaDatosJuego * aux; 
		int i = 1;
		aux = p_lista;
		
		printf("\nDatos de la lista\n");
		while( aux != NULL ) {
			printf("\n%d.Categoria: %s\nPalabra: %s\nDescripcion: %s\n", i++
									, aux->datoJuego.categoria
									, aux->datoJuego.palabra
									, aux->datoJuego.descripcion );
			
			aux = aux->siguiente;
		}
	}
}

/*Procedimiento que permite eliminar el primer dato de la lista*/
void eliminarPrimero() {
	if ( listaVacia( v_listaDatosJuego ) ) {
		printf("\nLa lista esta vacia...\n");
	} else {
		t_listaDatosJuego * nodoSuprimir = v_listaDatosJuego;
		v_listaDatosJuego = v_listaDatosJuego->siguiente;
		printf("\n\tDato eliminado.");	
		free(nodoSuprimir);
		nodoSuprimir = NULL;
	}
}

/*Procedimiento que permite eliminar un dato en una posicion k, dentro de la lista*/
void eliminarDeLaLista( int k) {
	int i;
	
	t_listaDatosJuego * aux, * nodoSuprimir;
	aux = v_listaDatosJuego;
	
	for( i=1; i<k; i++ ) {
		aux = aux->siguiente;
	}
	
	nodoSuprimir = aux->siguiente;
	aux->siguiente = nodoSuprimir->siguiente;
	printf("\n\tDato eliminado.");
	free(nodoSuprimir);
	nodoSuprimir = NULL;
}

/*Procedimiento que permite crear un archivo binario de datos*/
void abrirArchivo_ab() {
	/*Se abre el archivo en modo escritura binaria*/
	v_fileDatosJuego = fopen("Datos_JuegoAhorcado.dat","wb");
	
	/* Se verifica que exista el archivo*/
	if( v_fileDatosJuego == NULL ) {
		printf("NO se encontro el archivo...");
		exit(EXIT_FAILURE);
	}
}

/*Procedimiento que nos permite grabar los datos a un archivo*/
void grabarDatos() {
	
	if( listaVacia(v_listaDatosJuego) ) {
		printf("\nNo hay datos en la lista para grabar...\n");
	}else {
		
		t_listaDatosJuego * aux;
		aux = v_listaDatosJuego;
		
		while( aux != NULL) {
			fwrite(&aux->datoJuego, sizeof(t_regDatoJuego), 1, v_fileDatosJuego);
			printf("\n\tRegistro insertado\n");
			
			aux = aux->siguiente;
		}
	}
	
}

/*Procemiento que nos permite abrir el archivo en modo lectura*/
void abrirArchivo_rb() {
	v_fileDatosJuego = fopen("Datos_JuegoAhorcado.dat","rb");
	
	if( v_fileDatosJuego == NULL ) {
		printf("NO se encontro el archivo...");
		exit(EXIT_FAILURE);
	}
}

/*Procedimiento que permite mostrar por pantalla los datos dentro del archivo*/
void procesarDatos() {
	system("cls");
	
	t_regDatoJuego v_regDatosJuego;
	fread(&v_regDatosJuego, sizeof(t_regDatoJuego), 1, v_fileDatosJuego);
	while( !feof( v_fileDatosJuego ) ) {
		
		printf("\nCategoria: %s\nPalabra: %s\nDescripcion: %s\n", v_regDatosJuego.categoria, v_regDatosJuego.palabra, v_regDatosJuego.descripcion);
		
		fread(&v_regDatosJuego, sizeof(t_regDatoJuego), 1, v_fileDatosJuego);
	}
}


/*Procedimiento que cierra el flujo de datos de un archivo*/
void finalizarProceso() {
	fclose(v_fileDatosJuego);
}

/*Procedimiento que permite ingresar los datos por teclado*/
void ingresarDatosJuego() {
	int opcion;
	t_regDatoJuego DatoJuego;
	
	do{
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
		
		ingresarDatoLista( DatoJuego );
		
		printf("\n\tPresione cualquier tecla para continuar... \n\t(0 para finalizar): ");
		fflush(stdin);
		scanf("%d", &opcion);
		system("cls");
	}while(opcion != 0);
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
	printf("\n\t\t /|\\  |");
	printf("\n\t\t / \\  |");
	printf("\n\t\t      |");
	printf("\n\t\t =========\n");
	
	printf("\n\t***  MENU  ***\n");
	printf("\n\t1.Ingresar datos\n\t2.Eliminar datos de la lista\n\t3.Vizualizar lista\n\t4.Grabar datos\n\t5.Mostrar Datos\n\n\tx.Salir\n\n\n\tOpcion: ");
	fflush(stdin);
	scanf("%c", &opcion);	
	
	switch( opcion ) {
		case '1':
					ingresarDatosJuego();
					continuar();
					menu();
					break;
		case '2':
					if( listaVacia(v_listaDatosJuego) ) {
						printf("\n\t\tLista vacia.");
					}else {
						vizualizarLista( v_listaDatosJuego );
						printf("\nQue posicion desea eliminar?");
						scanf("%d", &k);
						if( k == 1 ) {
							eliminarPrimero();
						}else {
							eliminarDeLaLista( k );
						}
					}
					
					continuar();
					menu();
					break;
		case '3':
					vizualizarLista( v_listaDatosJuego );
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
					finalizarProceso();
					break;
		default:
					printf("\n\n\t\tOPCION INCORRECTA. DIGITE SOLO LAS OPCIONES DADAS EN EL MENU.");
					
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

void iniciarPrograma(){
	strcpy(datoVacio.categoria," ");
	strcpy(datoVacio.palabra," "); /*Se inicializa el dato vacio*/
	strcpy(datoVacio.descripcion," ");
	
	inicializarLista();
	menu();

}
