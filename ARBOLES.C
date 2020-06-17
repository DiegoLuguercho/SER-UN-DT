#include "Arboles.h"

nodArbol*inicArbol()
{
    return NULL;
}
nodArbol*crearArbol(Jugador j)
{
    nodArbol*aux=(nodArbol*) malloc(sizeof(nodArbol));
    aux->jgador=j;
    aux->izq=NULL;
    aux->der=NULL;
    return aux;
}
nodArbol*buscarPorEdad(nodArbol*arbol, Jugador j)
{
    nodArbol*rta=NULL;
    if(arbol!=NULL)
    {
        if(j.edad == arbol->jgador.edad)
        {
            rta=arbol;
        }
        else
        {
            if(j.edad > arbol->jgador.edad)
            {
                rta=buscarPorEdad(arbol->der, j);
            }
            else
            {
                rta=buscarPorEdad(arbol->izq, j);
            }
        }
    }
    return rta;
}
nodArbol*insertar(nodArbol*arbol, Jugador j)
{

    if(arbol==NULL)
    {
        arbol=crearArbol(j);
    }
    else
    {
        if(j.numero < arbol->jgador.numero)
        {
            arbol->izq=insertar(arbol->izq, j);
        }
        else
        {
            arbol->der=insertar(arbol->der, j);
        }
    }
    return arbol;
}
nodArbol*cargarArbol(nodArbol*arbol)
{
    Jugador j;
    char letra='s';
    char rol[20]={"nada"};
    nodArbol* numero=NULL;
    printf("\n\tCARGARNDO ARBOL ");
    while(letra=='s')
    {
        printf("\nIngrese Nombre: ");
        fflush(stdin);
        gets(&j.nombreYapellido);
        fflush(stdin);
        printf("\nIngrese Edad: ");
        scanf("%d", &j.edad);
        printf("\nIngrese Posicion: ");
        scanf("%s", &j.posicion);
        printf("\nIngrese Numero de camiseta: ");
        scanf("%d", &j.numero);
        while(numero=buscarPorNumero(arbol, j.numero)!=NULL)
        {
            printf("\n              EL NUMERO YA ESTA UTILIZADO");
            printf("\n              Por favor ingrese otro numero");
            printf("\n\nIngrese nuevamente numero de camiseta: ");
            scanf("%d", &j.numero);
        }
        printf("\nIngrese condicion(Apto, Lesionado): ");
        scanf("%s", &j.condicion);
        j.cantGoles=0;
        j.amonestaciones=0;
        strcpy(&j.rolEnEquipo, rol);
        arbol=insertar(arbol, j);
        printf("\nDesea continuar? s/n: ");
        fflush(stdin);
        scanf("%c", &letra);
    }
    return arbol;
}
void inorder(nodArbol*arbol)
{
    if(arbol!=NULL)
    {
        inorder(arbol->izq);
        printf("\nNombre y Apellido: %s", arbol->jgador.nombreYapellido);
        printf("\nEdad: %d", arbol->jgador.edad);
        printf("\nPosicion: %s", arbol->jgador.posicion);
        printf("\nNumero de camiseta: %d", arbol->jgador.numero);
        printf("\nCantidad de goles: %d", arbol->jgador.cantGoles);
        printf("\nAmonestaciones(Mas de 3, no apto para ser convocado): %d", arbol->jgador.amonestaciones);
        printf("\nCondicion: %s", arbol->jgador.condicion);
        printf("\nConvocatoria: %s", arbol->jgador.rolEnEquipo);
        printf("\n");
        inorder(arbol->der);
    }
}
int SumarGolesArbol(nodArbol*arbol)
{
    int rta=0;
    nodArbol*aux=arbol;
    if(aux!=NULL)
    {

        rta=aux->jgador.cantGoles+SumarGolesArbol(aux->izq)+SumarGolesArbol(aux->der);

    }
    return rta;
}
nodo2*pasarArbolaLista(nodArbol*arbol, nodo2*lista)
{
    nodo2*aux=NULL;
    if(arbol!=NULL)
    {
        lista=pasarArbolaLista(arbol->izq, lista);
        aux=crearnodo(arbol->jgador);
        lista=agregarOrdenado(lista, aux);
        lista=pasarArbolaLista(arbol->der, lista);
    }
    return lista;
}
nodArbol*nodoMasIzq(nodArbol*arbol)
{
    nodArbol*aux=arbol;
    if(arbol!=NULL)
    {
        if(arbol->izq==NULL)
        {
            aux=arbol;
        }
        else
        {
            aux=nodoMasIzq(arbol->izq);
        }
    }
    return aux;
}
nodArbol*nodoMasDer(nodArbol*arbol)
{
    nodArbol*aux=arbol;
    if(arbol!=NULL)
    {
        if(arbol->der==NULL)
        {
            aux=arbol;
        }
        else
        {
            aux=nodoMasDer(arbol->der);
        }
    }
    return aux;
}
nodArbol*borrarNodoArbolPorNumero(nodArbol*arbol, int numero)
{
    if(arbol!=NULL)
    {
        if(arbol->jgador.numero == numero)
        {
            if(arbol->izq!=NULL)
            {
                nodArbol*masDer=nodoMasDer(arbol->izq);
                arbol->jgador=masDer->jgador;
                arbol->izq=borrarNodoArbolPorNumero(arbol->izq, masDer->jgador.numero);
            }
            else if(arbol->der!=NULL)
            {
                nodArbol*masIzq=nodoMasIzq(arbol->der);
                arbol->jgador=masIzq->jgador;
                arbol->izq=borrarNodoArbolPorNumero(arbol->der, masIzq->jgador.numero);
            }
            else
            {
                free(arbol);
                arbol=NULL;
            }
        }
        else
        {
            if(arbol->jgador.numero < numero)
            {
                arbol->der=borrarNodoArbolPorNumero(arbol->der, numero);
            }
            else
            {
                arbol->izq=borrarNodoArbolPorNumero(arbol->izq, numero);
            }
        }
    }
    return arbol;
}

nodArbol*pasarArchivoToArbol(char nombre[], nodArbol*arbol)
{
    FILE*archi;
    archi=fopen(nombre, "rb");
    Jugador aux;
    if(archi!=NULL)
    {
        while(fread(&aux, sizeof(Jugador), 1, archi)>0)
        {
            arbol=insertar(arbol, aux);
        }
        fclose(archi);
    }

    return arbol;
}
nodArbol*buscarPorNumero(nodArbol*arbol, int numero)
{
    nodArbol*rta=NULL;
    if(arbol!=NULL)
    {
        if(numero == arbol->jgador.numero)
        {
            rta=arbol;
        }
        else
        {
            if(numero > arbol->jgador.numero)
            {
                rta=buscarPorNumero(arbol->der, numero);
            }
            else
            {
                rta=buscarPorNumero(arbol->izq, numero);
            }
        }
    }
    return rta;
}

int comprobarJugador(nodArbol*arbol, int numero)
{
    int rta=0;
    if(arbol!=NULL)
    {
        if(numero == arbol->jgador.numero)
        {
            rta=1;
        }
        else
        {
            if(numero > arbol->jgador.numero)
            {
                rta=comprobarJugador(arbol->der, numero);
            }
            else
            {
                rta=comprobarJugador(arbol->izq, numero);
            }
        }
    }
    return rta;
}

nodArbol*insertarArbol(nodArbol*arbol, nodArbol*aux)
{

    if(arbol==NULL)
    {
        arbol=aux;
    }
    else
    {
        if(aux->jgador.numero < arbol->jgador.numero)
        {
            arbol->izq=insertarArbol(arbol->izq, aux);
        }
        else
        {
            arbol->der=insertarArbol(arbol->der, aux);
        }
    }
    return arbol;
}

nodArbol* convocarJugador(nodArbol*arbol, int cantidad)
{
    int numero=0;
    char concentrado[20]={"Concentrado"};
    char condicion[4]={"Apto"};
    nodArbol*rta=NULL;
    if(arbol!=NULL)
    {
        printf("\nIngrese el dorsal del jugador a convocar: ");
        scanf("%d", &numero);
        rta=buscarPorNumero(arbol, numero);
        if(rta==NULL)
        {
            printf("\n No se encuentra el dorsal del jugador, ingrese uno nuevo \n");
            arbol=convocarJugador(arbol, cantidad);
        }
        else if(cantidad<23)
        {
            if((rta->jgador.amonestaciones>=3)&&(strcmp(rta->jgador.condicion, &condicion)!=0))
            {
                printf("\n Este jugador no puede ser convocado porque esta lesionado, expulsado o llego al limite de amarillas \n");
                arbol=convocarJugador(arbol, cantidad);

            }
            else
            {
                strcpy(rta->jgador.rolEnEquipo, &concentrado);
                cantidad++;
                arbol=convocarJugador(arbol, cantidad);
            }
        }
        else
        {
            printf("\n Ya se han convocado los 23 jugadores \n");
        }
    }
    return arbol;
}

nodArbol*reserva(nodArbol*arbol)
{
    char rol[5]={"nada"};
    char convocatoria[10]={"Reserva"};
    if(arbol!=NULL)
    {
        if((arbol->jgador.edad<=22)&&(strcmp(arbol->jgador.rolEnEquipo, rol)==0))
        {
            strcpy(arbol->jgador.rolEnEquipo, convocatoria);
        }
        reserva(arbol->izq);
        reserva(arbol->der);
    }
}
nodArbol*noconcentrado(nodArbol*arbol)
{
    char rol[5]={"nada"};
    char convocatoria[20]={"No concentrado"};
    if(arbol!=NULL)
    {
        if((strcmp(arbol->jgador.rolEnEquipo, rol)==0))
        {
            strcpy(arbol->jgador.rolEnEquipo, convocatoria);
        }
        noconcentrado(arbol->izq);
        noconcentrado(arbol->der);
    }
}

nodArbol*buscarMayorGoles(nodArbol*arbol)
{

}

void resumenDelCampeonato(nodArbol*arbol, int puntos, int contador)
{
    int TotalGoles=SumarGolesArbol(arbol);
    nodArbol*goleador=buscarMayorGoles(arbol);
    printf("\n RESUMEN DEL CAMPEONATO");
    printf("\n Cantidad de fechas jugadas: %d", contador);
    printf("\n Cantidad de puntos conseguidos: %d", puntos);
    printf("\n Cantidad de goles marcados: %d", TotalGoles);
    printf("\n Goleador del equipo:");
    printf("\n                     Nombre: %s", goleador->jgador.nombreYapellido);
    printf("\n                     Cantidad de goles: %d \n", goleador->jgador.cantGoles);
}

nodArbol*modificarJugador(nodArbol*arbol)
{
    Jugador j;
    char control='s';
    nodArbol* numero=NULL;
    int controlador=0;
    char control2;
    int numero2;
    char condicion[20]={"Lesionado"};
    printf("\n\tModificando jugadores despues del partido\n");
    while(control=='s')
    {
        printf("\n Escriba el numero del jugador que quiere modificar: ");
        scanf("%d", &j.numero);
        numero=buscarPorNumero(arbol, j.numero);
        printf("\n Que desea modificar(escribe el numero indicado): ");
        printf("\n                    1- Goles ");
        printf("\n                    2- Lesion ");
        printf("\n                    3- Amonestacion");
        printf("\n                    Ingrese numero: ");
        scanf("%d", &controlador);
        if(controlador==1)
        {
            printf("\nIngrese cantidad de goles: ");
            scanf("%d", numero->jgador.cantGoles);
        }
        else if(controlador==2)
        {
            printf("\nEl jugador se ha lesionado?(s/n): ");
            scanf("%c", &control2);
            if(control2=='s')
            {
                strcpy(numero->jgador.condicion, condicion);
            }
        }
        else if(controlador==3)
        {
            printf("\nSi el jugador fue amonestado ingrese 1, si el jugador fue expulsado ingrese 2: ");
            scanf("%d", &numero2);
            if(numero2==1)
            {
                numero->jgador.amonestaciones=+1;
            }
            else
            {
                numero->jgador.amonestaciones=+3;
            }
        }
        printf("\n\nDesea seguir? (s/n): ");
        scanf("%c", &control);
    }
    return arbol;
}


