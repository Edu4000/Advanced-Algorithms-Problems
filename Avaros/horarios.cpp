/*
EJERCICIO

Escriba un codigo de un algoritmo avaro para tener una aplicacion de consola que:

Ayude a un estudiante a crear su horariode clase,hay n clases que
consumen cierta cantidad de tiempo, solo se puede asistir a una clase a la 
vez, maximice la cantidad de clasesa las que se puede asistir segun las
siguientes opciones de horarios.
*/

#include <iostream>
#include <vector>
using namespace std;


struct materia {
    string nombre;
    // Lun - Vie <==> 0 - 4
    vector<int> dias;
    double horaInicio;
    double horaFinal;
};

bool factibilidad_de_horario(vector<vector<bool>> &calendario, materia clase) {

    int inicio = clase.horaInicio / 0.5;
    int final = clase.horaFinal / 0.5;

    // Checa los dias de la clase
    for (int dia : clase.dias) {
        // Checa las horas en cada dia
        for (int hora = inicio; hora < final; hora++) {
            // El horario esta ocupado <=> No es factible
            if (calendario[dia][hora]) return false;
        }
    }

    // Tomar la materia es factible
    return true;
}

void agregar_materia(vector<vector<bool>> &calendario, materia clase) {

    int inicio = clase.horaInicio / 0.5;
    int final = clase.horaFinal / 0.5;

    // Checa los dias de la clase
    for (int dia : clase.dias) {
        // Checa las horas en cada dia
        for (int hora = inicio; hora < final; hora++) {
            calendario[dia][hora] = true;
        }
    }

}

void quitar_materia(vector<vector<bool>> &calendario, materia clase) {

    int inicio = clase.horaInicio / 0.5;
    int final = clase.horaFinal / 0.5;

    // Checa los dias de la clase
    for (int dia : clase.dias) {
        // Checa las horas en cada dia
        for (int hora = inicio; hora < final; hora++) {
            calendario[dia][hora] = false;
        }
    }

}

void greedy_recursivo (vector<materia> &clases, vector<vector<bool>> &calendario, vector<materia> curr_horario, vector<materia> &horario_resultante) {

    // Busqueda de candidatos
    for (int i = 0; i < clases.size(); i++) {

        if (factibilidad_de_horario(calendario, clases[i])) {

            // Agregando materia a calendario, lista de materias y quitando de opciones
            agregar_materia(calendario, clases[i]);     curr_horario.push_back(clases[i]);    clases.erase(clases.begin() + i);

            // Llamando a recursion
            greedy_recursivo(clases, calendario, curr_horario, horario_resultante);

            // Quitando materia de calendario, lista de materias y regresando a opciones
            clases.insert(clases.begin() + i, curr_horario.back());    curr_horario.pop_back();   quitar_materia(calendario, clases[i]);

        }

    }

    //Seleccion
    if (curr_horario.size() > horario_resultante.size()) {
        horario_resultante = curr_horario;
    }

}

void solucion (vector<materia> &clases, vector<vector<bool>> &calendario) {
    // Variable resultado
    vector<materia> horario_resultante, curr_horario;

    greedy_recursivo(clases, calendario, curr_horario, horario_resultante);

    // Imprimiendo el nombre de las clases resultantes
    for (materia clase : horario_resultante) {
        cout << clase.nombre << "\n";
    }

}


int main(int argc, char const *argv[])
{
    // Lista de clases
    vector<materia> clases;
    clases.push_back(materia{"1", vector<int> {0,2}, 9, 11});
    clases.push_back(materia{"2", vector<int> {1,3}, 10, 12});
    clases.push_back(materia{"3", vector<int> {2,4}, 11, 13});
    clases.push_back(materia{"4", vector<int> {0,1}, 9.5, 11.5});
    clases.push_back(materia{"5", vector<int> {1,3}, 11.5, 13.5});
    clases.push_back(materia{"6", vector<int> {4}, 13, 16});
    clases.push_back(materia{"7", vector<int> {0,2}, 9, 11});

    // Calendario Semanal
    vector<vector<bool>> calendario = vector<vector<bool>> (5, vector<bool> (24*2, false));

    solucion(clases, calendario);

    return 0;
}
