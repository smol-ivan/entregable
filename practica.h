#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define ETHSIZE 400
#define PRECIO 50

struct Servidor
{
    bool taxis[5];
    int ganancias;
    int viajes;
};

void inicializarServidor(struct Servidor *servidor)
{
    for (int i = 0; i < 5; i++)
    {
        if (i == 0)
        {
            servidor->taxis[i] = true;
        }
        else
        {
            servidor->taxis[i] = false;
        }
    }
    servidor->ganancias = 0;
    servidor->viajes = 0;
}

// Funcion para decodificar usando sscanf
// sintaxis usada: "{texto}|{numero}"

void s_decodificar(char *buffer, char *texto, int *numero)
{
    sscanf(buffer, "%[^|]|%d", texto, numero);
}

void s_codificar(char *buffer, char *texto, int numero)
{
    sprintf(buffer, "%s|%d", texto, numero);
}

int buscar_taxi(struct Servidor *servidor)
{
    // Inicializar la semilla para la generación de números aleatorios
    srand(time(NULL));

    int taxis_libres[5];
    int count = 0;

    // Recopilar todos los taxis libres
    for (int i = 0; i < 5; i++)
    {
        if (!servidor->taxis[i])
        {
            taxis_libres[count] = i;
            count++;
        }
    }

    // Si no hay taxis libres, regresar -1
    if (count == 0)
    {
        return -1;
    }

    // Seleccionar un taxi libre de manera aleatoria
    int indice_aleatorio = rand() % count;

    servidor->taxis[indice_aleatorio] = true;
    servidor->viajes++;
    servidor->ganancias += PRECIO;

    return taxis_libres[indice_aleatorio];
}

void terminar_viaje(struct Servidor *servidor, int placa)
{
    // La placa es el indice del taxi
    servidor->taxis[placa] = false;
}

void estado(struct Servidor *servidor, int *ganancia, int *viajes)
{
    *ganancia = servidor->ganancias;
    *viajes = servidor->viajes;

    printf("Ganancia total: %d\n", *ganancia);
    printf("# de viajes realizados: %d\n", *viajes);

    // Imprimir la disponibilidad de los taxis
    for (int i = 0; i < 5; i++)
    {
        printf("Taxi %d: %s\n", i, servidor->taxis[i] ? "Ocupado" : "Libre");
    }
}
