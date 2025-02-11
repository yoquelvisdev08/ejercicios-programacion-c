// Inclusión de bibliotecas necesarias
#include <iostream>  // Para entrada/salida
#include <fstream>  // Para manejo de archivos
#include <string>   // Para manejo de cadenas
#include <vector>   // Para el contenedor vector

using namespace std;

// Clase que maneja la lista de tareas
class TodoList {
private:
    vector<string> tareas;      // Vector para almacenar las tareas
    string nombreArchivo;       // Nombre del archivo donde se guardarán las tareas

public:
    // Constructor: inicializa la lista cargando tareas desde el archivo
    TodoList(string archivo) : nombreArchivo(archivo) {
        cargarTareas();
    }

    // Método para agregar una nueva tarea a la lista
    void agregarTarea(string tarea) {
        tareas.push_back(tarea);
        guardarTareas();        // Guarda inmediatamente en el archivo
    }

    // Método para mostrar todas las tareas en pantalla
    void mostrarTareas() {
        if (tareas.empty()) {
            cout << "No hay tareas pendientes.\n";
            return;
        }

        cout << "\nLista de tareas:\n";
        for (int i = 0; i < tareas.size(); i++) {
            cout << i + 1 << ". " << tareas[i] << endl;
        }
    }

private:
    // Método para guardar las tareas en el archivo
    void guardarTareas() {
        ofstream archivo(nombreArchivo);    // Abre el archivo en modo escritura
        for (const string& tarea : tareas) {
            archivo << tarea << endl;       // Escribe cada tarea en una nueva línea
        }
        archivo.close();                    // Cierra el archivo
    }

    // Método para cargar las tareas desde el archivo
    void cargarTareas() {
        ifstream archivo(nombreArchivo);    // Abre el archivo en modo lectura
        string linea;
        
        while (getline(archivo, linea)) {   // Lee el archivo línea por línea
            tareas.push_back(linea);        // Agrega cada línea como una tarea
        }
        archivo.close();                    // Cierra el archivo
    }
};

// Función principal del programa
int main() {
    TodoList lista("tareas.txt");  // Crea una instancia de TodoList
    int opcion;
    string tarea;

    // Bucle principal del programa
    while (true) {
        // Muestra el menú de opciones
        cout << "\n=== TODO List ===\n";
        cout << "1. Agregar tarea\n";
        cout << "2. Ver tareas\n";
        cout << "3. Salir\n";
        cout << "Elige una opción: ";
        cin >> opcion;
        cin.ignore();  // Limpia el buffer del teclado

        // Procesa la opción seleccionada
        switch (opcion) {
            case 1:
                cout << "Ingresa la nueva tarea: ";
                getline(cin, tarea);
                lista.agregarTarea(tarea);
                cout << "Tarea agregada correctamente.\n";
                break;
            case 2:
                lista.mostrarTareas();
                break;
            case 3:
                cout << "¡Hasta luego!\n";
                return 0;
            default:
                cout << "Opción no válida.\n";
        }
    }

    return 0;
} 