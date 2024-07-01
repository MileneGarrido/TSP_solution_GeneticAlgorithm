#include "funciones.h"


std::string ConvertirABinario(int numero) {
    std::string binario = "";
    for (int i = 2; i >= 0; --i) {
        if ((numero >> i) & 1) {
            binario += '1';
        } else {
            binario += '0';
        }
    }
    return binario;
}

Punto::Punto(int px, int py) {
    x = px;
    y = py;
}

Individuo::Individuo() {
    fitness = 0;
    // Generar genotipo aleatorio binario
    
     // Inicialización del genotipo con una permutación aleatoria de las ciudades
    int ciudades_disponibles[NUM_CIUDADES];
    for (int i = 0; i < NUM_CIUDADES; ++i) {
        ciudades_disponibles[i] = i;
    }

    // Barajar aleatoriamente las ciudades disponibles
   for (int i = NUM_CIUDADES - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        // Intercambiar ciudades_disponibles[i] con ciudades_disponibles[j]
        int temp = ciudades_disponibles[i];
        ciudades_disponibles[i] = ciudades_disponibles[j];
        ciudades_disponibles[j] = temp;
    }

    // Asignar el genotipo basado en la permutación aleatoria
    for (int i = 0; i < NUM_CIUDADES; ++i) {
        genotipo[i] = ciudades_disponibles[i];
    }
}

float Individuo::CalcularDistancia(Punto& a, Punto& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void Individuo::CalcularFitness(Punto ciudades[NUM_CIUDADES]) {
    fitness = 0;
    for (int i = 0; i < NUM_CIUDADES - 1; i++) {
        int idx1 = genotipo[i];
        int idx2 = genotipo[i + 1];
        fitness += CalcularDistancia(ciudades[idx1], ciudades[idx2]);
    }
    // Volver al punto de inicio
    int idx_inicio = genotipo[0];
    int idx_fin = genotipo[NUM_CIUDADES - 1];
}

void Individuo::MostrarRuta() {
    std::cout << "Ruta: ";
    for (int i = 0; i < NUM_CIUDADES; i++) {
        std::cout << genotipo[i] << " ";
    }

    std::cout << "- Binario: ";
    for (int i = 0; i < NUM_CIUDADES; i++) {
        std::cout << ConvertirABinario(genotipo[i]) << " ";
    }
    std::cout << std::endl;
}

Poblacion::Poblacion() {
    generacion_actual = 1;
    for (int i = 0; i < 10; i++) {
        individuos[i] = Individuo();
    }
}

void Poblacion::Inicializar(Punto ciudades[NUM_CIUDADES]) {
    for (int i = 0; i < 10; i++) {
        individuos[i].CalcularFitness(ciudades);
    }
}

void Poblacion::Evaluar(Punto ciudades[NUM_CIUDADES]) {
    for (int i = 0; i < 10; i++) {
        individuos[i].CalcularFitness(ciudades);
    }
}

void Poblacion::Seleccionar() {
    // Ordenar los individuos por fitness de menor a mayor
    std::sort(individuos, individuos + 10, [](Individuo a, Individuo b) {
        return a.fitness < b.fitness;
    });

    // Los 2 mejores individuos de la generación anterior pasan directamente a la nueva generación
    Individuo padres[2];
    padres[0] = individuos[0];
    padres[1] = individuos[1];
    // Generar el resto de la población mediante cruce de los 2 mejores individuos
    for (int i = 2; i < 10; i++) {
        int puntoCruce = rand() % (NUM_CIUDADES - 1) + 1; // Punto de cruce aleatorio

        Individuo parent1 = padres[0];
        Individuo parent2 = padres[1];
        Individuo child;

        // Marcadores para controlar las ciudades añadidas
        bool added[NUM_CIUDADES] = {false};

        // Generar hijo
        int idx = 0;
        // Copiar segmento hasta el punto de cruce de parent1
        for (int j = 0; j < puntoCruce; j++) {
            int city = parent1.genotipo[j];
            child.genotipo[idx++] = city;
            added[city] = true;
        }
        // Completar con las ciudades de parent2 que no están ya en el hijo
        for (int j = 0; j < NUM_CIUDADES; j++) {
            int city = parent2.genotipo[j];
            if (!added[city]) {
                child.genotipo[idx++] = city;
                added[city] = true;
            }
        }
        individuos[i] = child; // Asignar hijo a los individuos de la nueva generación
    }
}

void Poblacion::Mutar() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < NUM_CIUDADES; j++) {
            if ((rand() % 100) < 10) { // 10% de probabilidad de mutación
                int city1 = rand() % NUM_CIUDADES;
                int city2 = rand() % NUM_CIUDADES;
                while (city2 == city1) {
                    city2 = rand() % NUM_CIUDADES; // Asegurar que city2 sea diferente de city1
                }
                // Intercambiar ciudades en la mutación
                int temp = individuos[i].genotipo[city1];
                individuos[i].genotipo[city1] = individuos[i].genotipo[city2];
                individuos[i].genotipo[city2] = temp;
            }
        }
    }
}

void Poblacion::NuevaGeneracion(Punto ciudades[NUM_CIUDADES]) {
    Seleccionar();
    Mutar();
    Evaluar(ciudades);
    generacion_actual++;
}

void Poblacion::Mostrar() {
    for (int i = 0; i < 10; i++) {
        std::cout << "Individuo " << i + 1 << " - Fitness: " << individuos[i].fitness << " - ";
        individuos[i].MostrarRuta();
    }
}

Individuo Poblacion::MejorIndividuo() {
    Individuo mejor = individuos[0];
    for (int i = 1; i < 10; i++) {
        if (individuos[i].fitness < mejor.fitness) {
            mejor = individuos[i];
        }
    }
    return mejor;
}

void Poblacion::MostrarMejorRuta() {
    Individuo mejor = MejorIndividuo();
    std::cout << "Generacion: " << generacion_actual -1 << " - Fitness: " << mejor.fitness << " - ";
    mejor.MostrarRuta();
}
