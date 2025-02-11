#include <iostream>
using namespace std;

class TicTacToe {
private:
    char tablero[3][3];    // Matriz para el tablero de juego
    char jugadorActual;    // 'X' o 'O'

public:
    // Constructor: inicializa el tablero vacío
    TicTacToe() {
        jugadorActual = 'X';
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                tablero[i][j] = ' ';
            }
        }
    }

    // Método para mostrar el tablero
    void mostrarTablero() {
        cout << "\n";
        for(int i = 0; i < 3; i++) {
            cout << " " << tablero[i][0] << " | " << tablero[i][1] << " | " << tablero[i][2] << endl;
            if(i != 2) cout << "---+---+---" << endl;
        }
        cout << "\n";
    }

    // Método para realizar un movimiento
    bool hacerMovimiento(int fila, int columna) {
        // Verifica si la posición está dentro del tablero y vacía
        if(fila >= 0 && fila < 3 && columna >= 0 && columna < 3 && tablero[fila][columna] == ' ') {
            tablero[fila][columna] = jugadorActual;
            jugadorActual = (jugadorActual == 'X') ? 'O' : 'X';  // Cambia el jugador
            return true;
        }
        return false;
    }

    // Verifica si hay un ganador
    bool hayGanador() {
        // Revisar filas
        for(int i = 0; i < 3; i++) {
            if(tablero[i][0] != ' ' && tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2]) {
                return true;
            }
        }
        
        // Revisar columnas
        for(int i = 0; i < 3; i++) {
            if(tablero[0][i] != ' ' && tablero[0][i] == tablero[1][i] && tablero[1][i] == tablero[2][i]) {
                return true;
            }
        }
        
        // Revisar diagonales
        if(tablero[0][0] != ' ' && tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2]) {
            return true;
        }
        if(tablero[0][2] != ' ' && tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0]) {
            return true;
        }
        
        return false;
    }

    // Verifica si el tablero está lleno (empate)
    bool tableroLleno() {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(tablero[i][j] == ' ') return false;
            }
        }
        return true;
    }

    // Obtiene el jugador actual
    char getJugadorActual() {
        return jugadorActual;
    }
};

int main() {
    TicTacToe juego;
    int fila, columna;

    cout << "=== TIC TAC TOE ===\n";
    cout << "Instrucciones: Ingresa fila (0-2) y columna (0-2) cuando sea tu turno\n";

    while(true) {
        juego.mostrarTablero();
        
        cout << "Turno del jugador " << juego.getJugadorActual() << endl;
        cout << "Ingresa fila (0-2): ";
        cin >> fila;
        cout << "Ingresa columna (0-2): ";
        cin >> columna;

        if(!juego.hacerMovimiento(fila, columna)) {
            cout << "Movimiento inválido. Intenta de nuevo.\n";
            continue;
        }

        if(juego.hayGanador()) {
            juego.mostrarTablero();
            // El ganador es el jugador anterior porque ya se cambió en hacerMovimiento
            char ganador = (juego.getJugadorActual() == 'X') ? 'O' : 'X';
            cout << "¡El jugador " << ganador << " ha ganado!\n";
            break;
        }

        if(juego.tableroLleno()) {
            juego.mostrarTablero();
            cout << "¡Empate!\n";
            break;
        }
    }

    return 0;
} 