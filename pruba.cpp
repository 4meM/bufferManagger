#include <iostream>
#include <ctime>

// Función para obtener la diferencia en segundos entre dos tiempos
long obtenerDiferenciaEnSegundos(time_t tiempo1, time_t tiempo2) {
    return difftime(tiempo1, tiempo2);
}

int main() {
    // Obtener dos tiempos
    time_t tiempo1 = time(0); // Obtener tiempo actual
    time_t tiempo2 = tiempo1 - 3600; // Restar una hora (3600 segundos)

    // Calcular la diferencia en segundos
    long diferencia = obtenerDiferenciaEnSegundos(tiempo1, tiempo2);

    // Imprimir la diferencia
    std::cout << "La diferencia en segundos entre los dos tiempos es: " << tiempo1 << std::endl;
    std :: cout << tiempo2 << "\n";

    return 0;
}

