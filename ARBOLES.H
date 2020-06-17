#ifndef ARBOLES_H_INCLUDED
#define ARBOLES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Jugadores.h"
#include "Listas2.h"
#include "ArregloDeLista.h"

typedef struct nodArbol
{
    Jugador jgador;
    struct nodArbol* izq;
    struct nodArbol* der;

}nodArbol;

nodArbol*inicArbol();
nodArbol*crearArbol(Jugador j);
nodArbol*buscarPorEdad(nodArbol*arbol, Jugador j);
nodArbol*insertar(nodArbol*arbol, Jugador j);
nodArbol*cargarArbol(nodArbol*arbol);
void inorder(nodArbol*arbol);
int SumarGolesArbol(nodArbol*arbol);
nodArbol*nodoMasIzq(nodArbol*arbol);
nodArbol*nodoMasDer(nodArbol*arbol);
nodArbol*borrarNodoArbolPorNumero(nodArbol*arbol, int numero);
nodArbol*pasarArchivoToArbol(char nombre[], nodArbol*arbol);
nodArbol*buscarPorNumero(nodArbol*arbol, int numero);
int pasarArbolADL(nodArbol*arbol, Convocatoria c[3]);
int comprobarJugador(nodArbol*arbol, int numero);
nodArbol*convocarJugador(nodArbol*arbol, int cantidad);
void resumenDelCampeonato(nodArbol*arbol, int puntos, int contador);
nodArbol*modificarJugador(nodArbol*arbol);

#endif // ARBOLES_H_INCLUDED
