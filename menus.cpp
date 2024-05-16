#include <stdio.h>
#include "menus.h"

/*  Nombre de la función: menuIniciarSesion
 *  Tipo de función: void
 *  Parámetros: ListaCliente &lista
 *  Descripción de la función: Esta función muestra al usuario un menu
 *                             donde se le pide iniciar sesion o crear
 *                             cuenta segun decida.
 */
void menuIniciarSesion(ListaCliente &lista){
    int opcion;
    char cliente_ingresado[30];
    int id_ingresado;
    int posicion;
    printf("\nBienvenido a su plataforma de streaming\n");
    do{
        printf("1. Iniciar sesion\n2. Crear usuario\nSeleccionar una opcion: ");
        scanf("%d", &opcion);
        getchar();
        if(opcion == 1){
            do{
                printf("\n========INICIAR SESION========\n");
                printf("Ingrese su nombre de usuario: ");
                scanf("%s", cliente_ingresado);
                if(verificarClienteNombre(cliente_ingresado, lista)){
                    posicion = localizaClienteNombre(cliente_ingresado, lista);
                    id_ingresado = recuperaid(posicion, lista);
                    printf("\n========USUARIO '%s' INGRESADO========\n", cliente_ingresado);
                    return;
                } else{
                    printf("\nEl usuario '%s' no existe\n", cliente_ingresado);
                    printf("Por favor intentelo de nuevo\n");
                }
            } while(verificarClienteNombre(cliente_ingresado, lista) == 0);
        } else if(opcion == 2){
            do{
                printf("\n========CREAR USUARIO========\n");
                printf("Ingrese su nombre de usuario: ");
                scanf("%s", cliente_ingresado);
                if(verificarClienteNombre(cliente_ingresado, lista) == 0){
                    id_ingresado = finCliente(lista);
                    posicion = finCliente(lista);
                    insertaCliente(id_ingresado, cliente_ingresado, posicion, lista);
                    printf("\nUsuario '%s' creado exitosamente!\n", cliente_ingresado);
                    printf("Dirigiendose a menu...\n");
                    return;
                } else {
                    printf("\nEl nombre de usuario '%s' ya existe\n", cliente_ingresado);
                    printf("Por favor intentelo de nuevo\n");
                }
            } while(verificarClienteNombre(cliente_ingresado, lista) != 0);
        } else{
            printf("\nOpcion invalida!\n");
            printf("Por favor intentelo de nuevo\n");
        }
    } while (opcion != 1 && opcion != 2);
}

/*  Nombre de la función: menu
 *  Tipo de función: void
 *  Parámetros: ListaPelicula &lista_p, ListaSerie &lista_s
 *  Descripción de la función: Esta función muestra al usuario el menu
 *                             de la plataforma de streaming con todas
 *                             sus funciones.
 */
void menu(ListaPelicula &lista_p, ListaSerie &lista_s) {
    int opcion;
    int opcion_2;
    int opcion_3;
    char titulo_ingresado[30];
    char titulo[30];
    int posicion;
    int reproducciones;
    int capitulo;
    int temporada;
    int capitulo_ingresado;
    int temporada_ingresado;

    do {
        printf("\n========== MENU ==========\n");
        printf("1. Ingreso de titulo\n");
        printf("2. Reproduccion de titulo\n");
        printf("3. Eliminacion de titulo\n");
        printf("4. Busqueda de titulo\n");
        printf("5. Salir\n");
        printf("==========================\n");
        printf("Ingrese la opcion deseada: ");
        scanf("%d", &opcion);
        getchar(); 
        switch (opcion) {
            case 1:
                do{
                    printf("\nDesea ingresar una serie o una pelicula?\n1. Pelicula\n2. Serie\nSeleccione una opcion: ");
                    scanf("%d", &opcion_2);
                    getchar();
                        if(opcion_2 == 1){
                            printf("\nIngrese el titulo de la pelicula: ");
                            scanf(" %[^\n]", titulo_ingresado);
                            if(verificarPeliculaTitulo(titulo_ingresado, lista_p)){
                                printf("\nEl titulo '%s' ya se encuentra en Peliculas\n", titulo_ingresado);
                                printf("Redigirigiendo a menu...\n");
                            } else{
                                insertaPelicula(titulo_ingresado, 0, finPelicula(lista_p), lista_p);
                                printf("\n === %s ingresada exitosamente ===\n", titulo_ingresado);
                                ordenarTitulosPelicula(lista_p);
                                imprimeListaPelicula(lista_p);
                            }
                        }else if(opcion_2 == 2){
                            printf("\nIngrese el titulo de la serie: ");
                            scanf(" %[^\n]", titulo_ingresado);
                            if(verificarSerieTitulo(titulo_ingresado, lista_s)){
                                printf("\nEl titulo '%s' ya se encuentra en Series\n", titulo_ingresado);
                                printf("Redigirigiendo a menu...\n");
                            } else{
                                printf("\nIngrese numero de temporadas de '%s': ", titulo_ingresado);
                                scanf("%i", &temporada);
                                printf("\nIngrese numero de capitulos de '%s': ", titulo_ingresado);
                                scanf("%i", &capitulo);
                                insertaSerie(titulo_ingresado, temporada, capitulo, 0, finSerie(lista_s), lista_s);
                                printf("\n === %s ingresada exitosamente ===\n", titulo_ingresado);
                                ordenarTitulosSerie(lista_s);
                                imprimeListaSerie(lista_s);
                            }
                        } else{
                            printf("\nPor favor ingrese una opcion valida\n");
                        }
                } while(opcion_2 != 1 && opcion_2 != 2);
                break;
            case 2:
                do {
                    printf("\nDesea ver una serie o una pelicula?\n1. Pelicula\n2. Serie\nSeleccione una opcion: ");
                    scanf("%d", &opcion_2);
                    getchar();
                    if (opcion_2 == 1){
                        carteleraPelicula(lista_p);
                        printf("Ingrese titulo de la pelicula que desea ver: ");
                        scanf(" %[^\n]", titulo_ingresado);
                        if(verificarPeliculaTitulo(titulo_ingresado, lista_p)){
                            reproducirPelicula(titulo_ingresado, lista_p);
                        } else{
                            printf("\nTitulo '%s' no encontrado en Peliculas\n", titulo_ingresado);
                            printf("Redirigiendo a menu...\n");
                        }
                    } else if (opcion_2 == 2){
                        carteleraSerie(lista_s);
                        printf("Ingrese titulo de la serie que desea ver: ");
                        scanf(" %[^\n]", titulo_ingresado);
                        if(verificarSerieTitulo(titulo_ingresado, lista_s)){
                            posicion = localizaSerieTitulo(titulo_ingresado, lista_s);
                            temporada = recuperaTemporadasSerie(posicion, lista_s);
                            capitulo = recuperaCapitulosSerie(posicion, lista_s);
                            printf("Ingrese temporada: ");
                            scanf("%d", &temporada_ingresado);
                            if (temporada >= temporada_ingresado){
                                printf("Ingrese capitulo: ");
                                scanf("%d", &capitulo_ingresado);
                                if(capitulo >= capitulo_ingresado){
                                    reproducirSerie(titulo_ingresado, temporada_ingresado, capitulo_ingresado, lista_s);
                                } else{
                                    printf("\nCapitulo ingresado no existe en la serie '%s'\n", titulo_ingresado);
                                }
                            } else{
                                printf("\nTemporada ingresada no existe en la serie '%s'\n", titulo_ingresado);
                            }
                        }  else{
                            printf("\nTitulo '%s' no encontrado en Series\n", titulo_ingresado);
                        }
                    } else{
                        printf("\nPor favor ingrese una opcion valida.\n");
                    }
                } while (opcion_2 != 1 && opcion_2 != 2);
                break;
            case 3:
                do {
                    printf("\nDesea eliminar una serie o una pelicula?\n1. Pelicula\n2. Serie\nSeleccione una opcion: ");
                    scanf("%d", &opcion_2);
                    getchar();
                    if (opcion_2 == 1) {
                        carteleraPelicula(lista_p);
                        printf("Ingrese titulo de la pelicula que desea eliminar: ");
                        scanf(" %[^\n]", titulo_ingresado);
                        if(verificarPeliculaTitulo(titulo_ingresado, lista_p)){
                            posicion = localizaPeliculaTitulo(titulo_ingresado, lista_p);
                            reproducciones = recuperarReproduccionesPelicula(posicion, lista_p);
                            if (reproducciones <= 5) {
                                suprimePelicula(posicion, lista_p); 
                                printf("\nPelicula '%s' eliminada con exito!\n", titulo_ingresado);
                                printf("Redirigiendo a menu...\n");
                            } else {
                                printf("\nNo se puede eliminar la pelicula porque supera las 5 reproducciones\n");
                                printf("Redirigiendo a menu...\n");
                            } 
                        } else{
                            printf("\nTitulo '%s' no encontrado en Peliculas\n", titulo_ingresado);
                            printf("Redirigiendo a menu...\n");
                        }
                    } else if (opcion_2 == 2) {
                        carteleraSerie(lista_s);
                        printf("Ingrese titulo de la serie que desea eliminar: ");
                        scanf(" %[^\n]", titulo_ingresado);
                        if(verificarSerieTitulo(titulo_ingresado, lista_s)){
                            posicion = localizaSerieTitulo(titulo_ingresado, lista_s);
                            reproducciones = recuperaReproduccionesSerie(posicion, lista_s);
                            if (reproducciones <= 5) {
                                suprimeSerie(posicion, lista_s);
                                printf("\nSerie '%s' eliminada con exito!\n", titulo_ingresado);
                                printf("Redirigiendo a menu...\n");
                            } else {
                                printf("\nNo se puede eliminar la serie '%s' porque supera las 5 reproducciones\n", titulo_ingresado);
                                printf("Redirigiendo a menu...\n");
                            }
                        } else {
                            printf("\nTitulo '%s' no encontrado en Series\n", titulo_ingresado);
                            printf("Redirigiendo a menu...\n");
                        }
                    } else {
                        printf("\nPor favor ingrese una opcion valida\n");
                    }
                } while (opcion_2 != 1 && opcion_2 != 2);
                break;
            case 4:
                do{
                    printf("\nDesea buscar una pelicula o una serie?\n1. Pelicula\n2. Serie\nSeleccione una opcion: ");
                    scanf("%d", &opcion_2);
                    getchar();
                    if (opcion_2 == 1){
                        printf("Ingrese titulo de la pelicula que desea buscar: ");
                        scanf(" %[^\n]", titulo_ingresado);
                        if (verificarPeliculaTitulo(titulo_ingresado, lista_p)) {
                            posicion = localizaPeliculaTitulo(titulo_ingresado, lista_p);
                            reproducciones = recuperarReproduccionesPelicula(posicion, lista_p);
                        do{
                            printf("\n=======PELICULA ENCONTRADA=======\n");
                            printf("Titulo: %s --- Reproducciones: %d\n", titulo_ingresado, reproducciones);
                            printf("================================\n");
                            printf("\nPor favor escoja una opcion\n1. Reproducir pelicula\n2. Eliminar pelicula\n3. Volver al menu\n");
                            printf("Ingrese opcion: ");
                            scanf("%d", &opcion_3);
                            getchar();
                            switch(opcion_3){
                                case 1:
                                    reproducirPelicula(titulo_ingresado, lista_p);
                                    break; 
                                case 2:
                                    if (reproducciones <= 5) {
                                        suprimePelicula(posicion, lista_p); 
                                        printf("\nPelicula '%s' eliminada con exito!\n", titulo_ingresado);
                                        printf("Redirigiendo a menu...\n");
                                    } else {
                                        printf("\nNo se puede eliminar la pelicula porque supera las 5 reproducciones\n");
                                        printf("Redirigiendo a menu...\n");
                                    }
                                    break;
                                case 3:
                                    printf("\nRedigirigiendo a menu...\n");
                                    break;
                                default:
                                    printf("\nOpcion invalida. Por favor ingrese una opcion valida\n");
                                    break;
                            }
                        } while (opcion_3 != 1 && opcion_3 != 2);
                        } else {
                            printf("\nLa pelicula no se encuentra en la lista.\n");
                            printf("Redirigiendo a menu...\n");
                        }
                    } else if(opcion_2 == 2){
                        printf("Ingrese titulo de la serie que desea buscar: ");
                        scanf(" %[^\n]", titulo_ingresado);
                        if (verificarSerieTitulo(titulo_ingresado, lista_s)) {
                            posicion = localizaSerieTitulo(titulo_ingresado, lista_s);
                            reproducciones = recuperaReproduccionesSerie(posicion, lista_s);
                            capitulo = recuperaCapitulosSerie(posicion, lista_s);
                            temporada = recuperaTemporadasSerie(posicion, lista_s);
                            do{
                                printf("\n=======SERIE ENCONTRADA========\n");
                                printf("Titulo: %s --- Temporadas: %i --- Capitulos: %i --- Reproducciones: %i\n", titulo_ingresado, temporada, capitulo, reproducciones);
                                printf("================================\n");
                                printf("\nPor favor escoja una opcion\n1. Reproducir serie\n2. Eliminar serie\n3. Volver al menu\n");
                                printf("Ingrese opcion: ");
                                scanf("%d", &opcion_3);
                                getchar();
                                switch(opcion_3){
                                    case 1:
                                        printf("Ingrese temporada: ");
                                        scanf("%d", &temporada_ingresado);
                                        if (temporada >= temporada_ingresado){
                                            printf("Ingrese capitulo: ");
                                            scanf("%d", &capitulo_ingresado);
                                            if(capitulo >= capitulo_ingresado){
                                                reproducirSerie(titulo_ingresado, temporada_ingresado, capitulo_ingresado, lista_s);
                                            } else{
                                                printf("\nCapitulo ingresado no existe en la serie '%s'\n", titulo_ingresado);
                                            }
                                        } else{
                                            printf("\nTemporada ingresada no existe en la serie '%s'\n", titulo_ingresado);
                                        }
                                        break; 
                                    case 2:
                                        if(reproducciones <= 5){
                                            suprimeSerie(posicion, lista_s);
                                            printf("\nPelicula '%s' eliminada con exito!\n", titulo_ingresado);
                                        } else{
                                            printf("\nNo se puede eliminar la pelicula porque supera las 5 reproducciones\n");
                                        }
                                        break;
                                    case 3:
                                        break;
                                    default:
                                        printf("Por favor ingrese una opcion valida");
                                        break;
                                }
                            } while (opcion_3 != 1 && opcion_3 != 2);
                        } else {
                            printf("\nLa serie no se encuentra en la lista.\n");
                            printf("Redirigiendo a menu...\n");
                        }
                    } else{
                        printf("\nPor favor ingrese una opcion valida\n\n");
                    }
                } while(opcion_2 != 1 && opcion_2 != 2);
                break;
            case 5:
                printf("\nSaliendo del programa...\n");
                return; // Termina la funcion y el programa
            default:
                printf("\nOpcion invalida. Por favor ingrese una opcion valida.\n");
                break;
        }
    } while (opcion != 5);
}