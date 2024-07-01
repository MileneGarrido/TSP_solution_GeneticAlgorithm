#include "funciones.h"
#include <iostream>
#include <ctime> 


int main() {
    
    Punto ciudades[NUM_CIUDADES] = {
        Punto(-80, 80),
        Punto(150, -150),
        Punto(-170, 70),
        Punto(40, 10),
        Punto(-70, 130),
        Punto(-90, 135),
        Punto(170, 80)
    };
    unsigned  t0,t1;
    t0=clock();

    Poblacion poblacion;
    poblacion.Inicializar(ciudades);
    std::cout << "Poblacion inicial:\n";
    poblacion.Mostrar();

   for (int generacion = 1; generacion <= 100; generacion++) {
        std::cout << "\nGeneracion " << generacion << ":\n";
        poblacion.NuevaGeneracion(ciudades);
        poblacion.Mostrar();

       // poblacion.MostrarMejorRuta(); // Mostrar el mejor individuo de cada generacion
        //td::cout << std::endl;
    }


    /* Ejecutar múltiples generaciones
    const int numGeneraciones = 100;
    for (int i = 0; i < numGeneraciones; ++i)
    {
         poblacion.NuevaGeneracion(ciudades);
    }*/

    std::cout << "Mejor ruta encontrada:\n";
    poblacion.MostrarMejorRuta();

    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    std::cout << "Execution Time: " << time << std::endl;
    return 0;

}