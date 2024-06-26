#include <iostream> // Para las entradas y salidas
#include <vector> // para crear y manipular vectores
#include <stack> // para crear y manipular elementos de pila
#include <cstdlib> // para utilizar propiedades de c
#include <ctime> // para utilizar la función srand y rand

using namespace std;

// Definimos la estructura de una celda
struct Cell {
    bool visited;
    bool topWall;
    bool bottomWall;
    bool leftWall;
    bool rightWall;
};

// Variables globales para el tamaño del laberinto
int WIDTH;
int HEIGHT;

// Definimos el laberinto como una matriz de celdas usando un vector de vectores
vector<vector<Cell>> maze;

// Función para inicializar el laberinto
void initializeMaze() {
    maze.resize(HEIGHT, vector<Cell>(WIDTH));

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            maze[i][j].visited = false;
            maze[i][j].topWall = true;
            maze[i][j].bottomWall = true;
            maze[i][j].leftWall = true;
            maze[i][j].rightWall = true;
        }
    }
}

// Estructura para representar las coordenadas de una celda
struct Position {
    int x, y;
};

// Función para obtener vecinos no visitados
vector<Position> getUnvisitedNeighbors(Position& cell) {
    vector<Position> neighbors;

    if (cell.y > 0 && !maze[cell.y - 1][cell.x].visited) // Arriba
        neighbors.push_back({cell.x, cell.y - 1});
    if (cell.y < HEIGHT - 1 && !maze[cell.y + 1][cell.x].visited) // Abajo
        neighbors.push_back({cell.x, cell.y + 1});
    if (cell.x > 0 && !maze[cell.y][cell.x - 1].visited) // Izquierda
        neighbors.push_back({cell.x - 1, cell.y});
    if (cell.x < WIDTH - 1 && !maze[cell.y][cell.x + 1].visited) // Derecha
        neighbors.push_back({cell.x + 1, cell.y});

    return neighbors;
}

// Función para eliminar la pared entre dos celdas
void removeWall(Position& current, Position& next) {
    if (current.x == next.x) {
        if (current.y > next.y) {
            maze[current.y][current.x].topWall = false;
            maze[next.y][next.x].bottomWall = false;
        } else {
            maze[current.y][current.x].bottomWall = false;
            maze[next.y][next.x].topWall = false;
        }
    } else {
        if (current.x > next.x) {
            maze[current.y][current.x].leftWall = false;
            maze[next.y][next.x].rightWall = false;
        } else {
            maze[current.y][current.x].rightWall = false;
            maze[next.y][next.x].leftWall = false;
        }
    }
}

// Función para generar el laberinto usando DFS
void generateMaze(int startX, int startY) {
    stack<Position> cellStack;
    Position current = {startX, startY};
    maze[startY][startX].visited = true;

    do {
        vector<Position> neighbors = getUnvisitedNeighbors(current);

        if (!neighbors.empty()) {
            Position next = neighbors[rand() % neighbors.size()];
            removeWall(current, next);
            cellStack.push(current);
            current = next;
            maze[current.y][current.x].visited = true;
        } else if (!cellStack.empty()) {
            current = cellStack.top();
            cellStack.pop();
        }
    } while (!cellStack.empty());
}

void printMaze() {
    for (int i = 0; i < WIDTH * 2 + 1; i++) cout << "_";
    cout << endl;

    for (int i = 0; i < HEIGHT; i++) {
        cout << "|";
        for (int j = 0; j < WIDTH; j++) {
            if (maze[i][j].bottomWall)
                cout << "_";
            else
                cout << " ";

            if (maze[i][j].rightWall)
                cout << "|";
            else
                cout << " ";
        }
        cout << endl;
    }
}

int main() {
    srand(time(0)); // Inicializamos la semilla para la generación de números aleatorios

    // Pedimos al usuario que ingrese el tamaño del laberinto
    cout << "Ingrese el ancho del laberinto: ";
    cin >> WIDTH;
    cout << "Ingrese el alto del laberinto: ";
    cin >> HEIGHT;

    // Inicializamos el laberinto con las dimensiones dadas por el usuario
    initializeMaze();
    generateMaze(0, 0);

    // Configuramos la entrada y la salida
    maze[0][0].leftWall = false;
    maze[HEIGHT-1][WIDTH-1].rightWall = false;

    printMaze();

    return 0;
}