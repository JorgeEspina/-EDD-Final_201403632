#include<stdio.h>
#include<stdlib.h>

struct NodoSpl{
    int Id;
    struct NodoSpl *Izquierda;
    struct NodoSpl *Derecha;
};

struct NodoSpl* CrearNodo(int Id){
    struct NodoSpl* Nuevo = (struct NodoSpl*)malloc(sizeof(struct NodoSpl));
    Nuevo->Id = Id;
    Nuevo->Izquierda = NULL;
    Nuevo->Derecha = NULL;
    return Nuevo;
}
struct NodoSpl *RotacionIzquierda(struct NodoSpl *Actual){
    struct NodoSpl *tmp = Actual->Derecha;
    Actual->Derecha = tmp->Izquierda;
    tmp->Izquierda = Actual;
    return tmp;
}

struct NodoSpl *RotacionDerecha(struct NodoSpl *Actual){
    struct NodoSpl *tmp = Actual->Izquierda;
    Actual->Izquierda = tmp->Derecha;
    tmp->Derecha = Actual;
    return tmp;
}


struct NodoSpl *BalanceoArbol(struct NodoSpl *Raiz, int Id){
    if (Raiz == NULL || Raiz->Id == Id){
        return Raiz;
    }
    if (Raiz->Id > Id){
        if (Raiz->Izquierda == NULL){
            return Raiz;
        }
        if (Raiz->Izquierda->Id > Id){// rotacion zig zig
            Raiz->Izquierda->Izquierda = BalanceoArbol(Raiz->Izquierda->Izquierda, Id);
            Raiz = RotacionDerecha(Raiz);
        }else if (Raiz->Izquierda->Id < Id){ // Zig-Zag
            Raiz->Izquierda->Derecha = BalanceoArbol(Raiz->Izquierda->Derecha, Id);
            if (Raiz->Izquierda->Derecha != NULL)
                Raiz->Izquierda = RotacionIzquierda(Raiz->Izquierda);
        }
        return (Raiz->Izquierda == NULL)? Raiz: RotacionDerecha(Raiz);
    }else{
        if (Raiz->Derecha == NULL){
            return Raiz;
        }
        if (Raiz->Derecha->Id > Id){ // rotacion zig-zag
            Raiz->Derecha->Izquierda = BalanceoArbol(Raiz->Derecha->Izquierda, Id);
            if (Raiz->Derecha->Izquierda != NULL)
                Raiz->Derecha = RotacionDerecha(Raiz->Derecha);
        }else if (Raiz->Derecha->Id < Id){// rotacion zag-zag
            Raiz->Derecha->Derecha = BalanceoArbol(Raiz->Derecha->Derecha, Id);
            Raiz = RotacionIzquierda(Raiz);
        }
        return (Raiz->Derecha == NULL)? Raiz: RotacionIzquierda(Raiz);
    }
}

struct NodoSpl *IngresarNodo(struct NodoSpl *Raiz, int Id){
    if (Raiz == NULL){
        return CrearNodo(Id);
    }
    Raiz = BalanceoArbol(Raiz,Id);
    if (Raiz->Id == Id){
        return Raiz;
    }

    struct NodoSpl *Nuevo  = CrearNodo(Id);
    if (Raiz->Id > Id){
        Nuevo->Derecha = Raiz;
        Nuevo->Izquierda = Raiz->Izquierda;
        Raiz->Izquierda = NULL;
    }else{
        Nuevo->Izquierda = Raiz;
        Nuevo->Derecha = Raiz->Derecha;
        Raiz->Derecha = NULL;
    }
    return Nuevo;
}

struct NodoSpl* EliminarNodo(struct NodoSpl *Raiz, int Id){
    struct NodoSpl *Actual;
    if (!Raiz){
        return NULL;
    }
    Raiz = BalanceoArbol(Raiz, Id);
    if (Id != Raiz->Id){
        return Raiz;
    }
    if (!Raiz->Izquierda){
        Actual = Raiz;
        Raiz = Raiz->Derecha;
    }else{
        Actual = Raiz;
        Raiz = BalanceoArbol(Raiz->Izquierda, Id);
        Raiz->Derecha = Actual->Derecha;
    }
    free(Actual);
    return Raiz;
}
struct NodoSpl *BusquedaNodo(struct NodoSpl *Raiz, int Id){
    return BalanceoArbol(Raiz, Id);
}
struct NodoSpl * Modificar(struct NodoSpl *Raiz,int Id,int Mod){
    if (Raiz != NULL){
        if(Raiz->Id == Id){
            Raiz->Id = Mod;
            BalanceoArbol(Raiz,Raiz->Id);
        }
        Modificar(Raiz->Izquierda,Id,Mod);
        Modificar(Raiz->Derecha,Id,Mod);
    }
    return Raiz;
}
FILE* archivo;

void Graficar(struct NodoSpl *Raiz){

    archivo =  fopen("Arbol_Spl.dot","w");

    fprintf(archivo,"digraph ARBOL_SPL{\n\tnode[shape = circle,width=0.5,height=0.5,fillcolor=""\"Orange\"""style=""\"filled\"""];\n\tedge[style = \"bold\"];");
    if(Raiz != NULL){
        Inicio(Raiz);
        RecursivoIzquierda(Raiz->Izquierda);
        RecursivoDerecha(Raiz->Derecha);
        LazosNodos(Raiz);
    }
    else{
        fprintf(archivo,"\n\tstruct[label = \"No Hay datos\"];");
    }
    fprintf(archivo,"\n}");
    fclose(archivo);

    /*CREACION DE DOT*/
    /*cadena.clear();
    cadena = "dot -Tpng ";
    cadena.append(ArbolABB->name.toStdString());
    cadena.append(".dot -o ");
    cadena.append(ArbolABB->name.toStdString());
    cadena.append(".png");
    system(cadena.c_str());*/
    system("dot -Tpng Arbol_Spl.dot -o Arbol_Spl.png");

}
void Inicio(struct NodoSpl *Nodo){
    if(Nodo == NULL){
    }else{

    fprintf(archivo,"\n\tstruct%i[label = \"Id = %i\"];",Nodo->Id,Nodo->Id);
    }
}


void RecursivoIzquierda(struct NodoSpl *Nodo){
    if(Nodo == NULL){
    }else{

        fprintf(archivo,"\n\tstruct%i[label = \"Id = %i\"];",Nodo->Id,Nodo->Id);

        RecursivoIzquierda(Nodo->Izquierda);
        RecursivoDerecha(Nodo->Derecha);
    }
}

void RecursivoDerecha(struct NodoSpl *Nodo){
    if(Nodo == NULL){
        //return "";
    }else{

        fprintf(archivo,"\n\tstruct%i[label = \"Id = %i\"];",Nodo->Id,Nodo->Id);

        RecursivoIzquierda(Nodo->Izquierda);
        RecursivoDerecha(Nodo->Derecha);
    }

}

void LazosNodos(struct NodoSpl *Nodo){
    if(Nodo != NULL){
        LazosNodosIzquierda(Nodo);
        LazosNodosDerecha(Nodo);
        LazosNodos(Nodo->Izquierda);
        LazosNodos(Nodo->Derecha);
    }
}

void LazosNodosIzquierda(struct NodoSpl *Nodo){
    if(Nodo != NULL){
        if(Nodo->Izquierda != NULL){
      fprintf(archivo,"\n\tstruct%i->struct%i[label=\"Izq\"];",Nodo->Id,Nodo->Izquierda->Id);
        }else{
        }
    }else{
    }
}

void LazosNodosDerecha(struct NodoSpl *Nodo){
    if(Nodo != NULL){
        if(Nodo->Derecha != NULL){
            fprintf(archivo,"\n\tstruct%i->struct%i[label=\"Der\"];",Nodo->Id,Nodo->Derecha->Id);
        }else{
        }
    }else{
    }
}
int main(){
     struct NodoSpl *Raiz = NULL;
     /*Raiz = IngresarNodo(Raiz,20);
     Raiz = IngresarNodo(Raiz,30);
     Raiz = IngresarNodo(Raiz,40);
     Raiz = IngresarNodo(Raiz,50);
     Raiz = IngresarNodo(Raiz,100);
     Raiz = IngresarNodo(Raiz,200);
     Raiz = IngresarNodo(Raiz,25);
     Raiz = IngresarNodo(Raiz,75);
     Raiz = IngresarNodo(Raiz,90);
     Raiz = IngresarNodo(Raiz,80);
     Raiz = IngresarNodo(Raiz,125);
     Raiz = IngresarNodo(Raiz,35);
     Raiz = IngresarNodo(Raiz,60);
     Raiz = IngresarNodo(Raiz,130);
     Raiz = IngresarNodo(Raiz,65);

     Graficar(Raiz);
     Raiz = Modificar(Raiz,80,5);
     Graficar(Raiz);
     Raiz = EliminarNodo(Raiz, 50);
     Graficar(Raiz);
      Raiz = EliminarNodo(Raiz, 125);
     Graficar(Raiz);
      Raiz = EliminarNodo(Raiz, 60);
     Graficar(Raiz);
      Raiz = EliminarNodo(Raiz, 20);
     Graficar(Raiz);
      Raiz = EliminarNodo(Raiz, 200);
     Graficar(Raiz);
     Raiz = BusquedaNodo(Raiz, 30);
     Graficar(Raiz);
     Raiz = BusquedaNodo(Raiz, 100);
     Graficar(Raiz);
     Raiz = BusquedaNodo(Raiz, 90);
     Graficar(Raiz);
     Raiz = BusquedaNodo(Raiz, 35);
     Graficar(Raiz);
     Raiz = BusquedaNodo(Raiz, 65);
     Graficar(Raiz);
     Raiz = BusquedaNodo(Raiz, 130);
     Graficar(Raiz);
     Raiz = BusquedaNodo(Raiz, 80);
     Graficar(Raiz);
     Raiz = BusquedaNodo(Raiz, 25);
     Graficar(Raiz);*/
     int Opcion;
     int Numero;
     int Numero1;
      printf("\n| Universidad de San Carlos de Guatemala |");
      printf("\n|        Facultad de Ingenieria          |");
      printf("\n|         Estructuras de Datos           |");
      printf("\n|             Seccion: B                 |");
      printf("\n|       Jorge David Espina Molina        |");
      printf("\n|              201403632                 |");
      printf("\n|              Final                     |");
      printf("\n\n");
      do{
              printf("|******************Menu******************|\n");
              printf("|     1.- Agregar                        |\n");
              printf("|     2.- Modificar                      |\n");
              printf("|     3.- Eliminar                       |\n");
              printf("|     4.- Buscar                         |\n");
              printf("|     5.- Salir                          |\n");
              printf("|                                        |\n");
              printf("|     Introduzca su Opcion (1-3)         |\n");
              printf("******************************************\n\n");
              scanf("%d",&Opcion);
               switch(Opcion){
                  case 1: // ingresar
                       printf("Ingrese numero: \n");
                       scanf("%d", &Numero);
                       Raiz = IngresarNodo(Raiz,Numero);
                       Graficar(Raiz);
                       break;
                  case 2:// modificar
                       printf("Ingrese numero que desea modificar: \n");
                       scanf("%d", &Numero);
                       printf("Ingrese numero que desea modificar: \n");
                       scanf("%d", &Numero1);
                       Raiz = Modificar(Raiz,Numero,Numero1);
                       Graficar(Raiz);
                       break;
                  case 3: // eliminar
                       printf("Ingrese numero a Eliminar: \n");
                       scanf("%d", &Numero);
                       Raiz = EliminarNodo(Raiz, Numero);
                       Graficar(Raiz);
                    break;
                  case 4: // buscar
                       printf("Ingrese numero a Buscar: \n");
                       scanf("%d", &Numero);
                       Raiz = BusquedaNodo(Raiz, Numero);
                       Graficar(Raiz);
                    break;
                }
     }while(Opcion  < 5);
    return 0;
}
