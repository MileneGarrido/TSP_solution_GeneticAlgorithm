#include <cmath>
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>

const int NUM_CIUDADES = 7;

// Definición de la estructura Punto para representar coordenadas (x, y)
struct Punto {
    int x;
    int y;
    Punto(int px, int py); // Constructor de la estructura Punto
};

// Declaración de la clase Individuo
class Individuo {
public:
    int genotipo[NUM_CIUDADES]; // Arreglo para almacenar la secuencia de ciudades visitadas
    float fitness; // Valor que representa la distancia de ruta del individuo
    Individuo();
    void CalcularFitness(Punto ciudades[NUM_CIUDADES]);// Método para calcular el fitness del individuo
    void MostrarRuta();// Método para mostrar la ruta del individuo
private:
    float CalcularDistancia(Punto& a, Punto& b); // Método privado para calcular la distancia entre dos puntos
};

// Declaración de la clase Poblacion
class Poblacion {
public:
    Individuo individuos[10]; // Arreglo de 10 individuos que forman la población
    int generacion_actual; // Variable que guarda el número de generación actual

    Poblacion(); // Constructor de la clase Poblacion
    void Inicializar(Punto ciudades[NUM_CIUDADES]); // Método para inicializar la población de individuos
    void Evaluar(Punto ciudades[NUM_CIUDADES]);
    void Seleccionar();
    void Cruzar();
    void Mutar();
    void NuevaGeneracion(Punto ciudades[NUM_CIUDADES]);
    void Mostrar();
    Individuo MejorIndividuo(); // Funcion para obtener el mejor individuo de la poblacion
    void MostrarMejorRuta(); // Funcion para mostrar la mejor ruta encontrada

};
