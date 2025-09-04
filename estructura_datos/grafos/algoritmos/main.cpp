#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <unordered_map>
#include <limits>

using namespace std;

// DFS recorrido en profundidad
struct Nodo {
    int valor;
    // vector<Nodo*> hijos;
    Nodo* izquierda;
    Nodo* derecha;
    Nodo(int v) : valor(v), izquierda(nullptr), derecha(nullptr) {}
};
/*
*@param raiz: nodo raíz desde donde se inicia la búsqueda
*@param valor: valor a buscar en el grafo
*/
Nodo* dfs(Nodo* raiz, int value){
    if(raiz == nullptr) return nullptr; // Caso base: si el nodo es nulo, retornar nulo

    
    if(raiz->valor == value){
        cout << "Valor " << value << " encontrado." << endl;
        return raiz;
    }
    
    // SI ES BINARIO:
    
    Nodo* resultadoIzq = nullptr;
    Nodo* izquierda = resultadoIzq = dfs(raiz->izquierda, value);
    if(izquierda != nullptr) return resultadoIzq;

    Nodo* resultadoDer = nullptr;
    Nodo* derecha = resultadoDer = dfs(raiz->derecha, value);
    if(derecha != nullptr) return resultadoDer;

    return nullptr;
    
   // Con lista de nodos que son sus hijos
   
    // for(size_t i = 0; i < raiz->hijos.size(); ++i){
    //     Nodo* resultado = dfs(raiz->hijos[i], value);
    //     if(resultado != nullptr){
    //         cout << "Valor " << value << " encontrado en hijo " << raiz->hijos[i]->valor << endl;
    //         return resultado;
    //     } else {
    //         cout << "Valor " << value << " no encontrado en hijo " << raiz->hijos[i]->valor << endl;
    //     }
    // }
    return nullptr; // Si no se encuentra el valor
    
}

/*
* Suma los valores de todos los caminos desde la raíz hasta las hojas
*@param raiz: nodo raíz desde donde se inicia la suma
*@return: suma de los valores de todos los caminos
*/
int sumRootToLeaf(Nodo* raiz, int sumaActual){
    if(raiz == nullptr) return 0;
    sumaActual = sumaActual * 10 + raiz->valor; // convertir a número en base 10
    if(raiz->izquierda == nullptr && raiz->derecha == nullptr) return sumaActual;

    int sumaIzquierda = sumRootToLeaf(raiz->izquierda, sumaActual);
    int sumaDerecha = sumRootToLeaf(raiz->derecha, sumaActual);
    return sumaIzquierda + sumaDerecha;
}

void dfsIslas(vector<vector<int>>& grid, int i, int j){
    if(i < 0 || j < 0 || i >= static_cast<int>(grid.size()) || j >= static_cast<int>(grid[0].size()) || grid[i][j] == 0) return; // j >= grid[0].size() hace referencia a la columna, i a la fila
    // marcar visitada 
    grid[i][j] = 0;
    // explorar vecinos
    dfsIslas(grid, i + 1, j); // abajo
    dfsIslas(grid, i - 1, j); // arriba
    dfsIslas(grid, i, j + 1); // derecha
    dfsIslas(grid, i, j - 1); // izquierda
    dfsIslas(grid, i + 1, j + 1); // diagonal abajo derecha
    dfsIslas(grid, i - 1, j - 1); // diagonal arriba izquierda
    dfsIslas(grid, i + 1, j - 1); // diagonal abajo izquierda
    dfsIslas(grid, i - 1, j + 1); // diagonal arriba derecha
}
int numIslas(vector<vector<int>>& grid){
    if(grid.empty() || grid[0].empty()) return 0;
    int islas = 0;
    int filas = grid.size();
    int columnas = grid[0].size();
    for(int i = 0; i < filas; ++i){
        for(int j = 0; j < columnas; ++j){
            if(grid[i][j] == 1){
                islas++;
                dfsIslas(grid, i, j); 
            }
        }
    }
    return islas;
}

// Reemplazar color en sección de imagen
/**
 * @param imagen Matriz 2D que representa la imagen
 * @param sr Fila de inicio
 * @param sc Columna de inicio
 * @param newColor Nuevo color a aplicar
 * @param oldColor Color original a reemplazar
 * @return Matriz 2D con el área coloreada
 */
void reemplazarColor(vector<vector<int>>& imagen, int sr, int sc, int newColor, int oldColor){
    if(sr < 0 || sc < 0 || sr >= static_cast<int>(imagen.size()) || sc >= static_cast<int>(imagen[0].size()))return; // fuera de los límites

    if(imagen[sr][sc] != oldColor) return;

    imagen[sr][sc] = newColor; // cambiar color

    reemplazarColor(imagen, sr + 1, sc, newColor, oldColor); // abajo
    reemplazarColor(imagen, sr - 1, sc, newColor, oldColor); // arriba
    reemplazarColor(imagen, sr, sc + 1, newColor, oldColor); // derecha
    reemplazarColor(imagen, sr, sc - 1, newColor, oldColor); // izquierda
}
vector<vector<int>> floodFill(vector<vector<int>>& imagen, int sr, int sc, int newColor){
    int oldColor = imagen[sr][sc];
    if(oldColor == newColor) return imagen;
    reemplazarColor(imagen, sr, sc, newColor, oldColor);
    return imagen;
}
void mostrarImagen(){
    vector<vector<int>> image = {
        {1, 1, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };

    int sr = 1, sc = 1, newColor = 2;

    vector<vector<int>> result = floodFill(image, sr, sc, newColor);

    cout << "Imagen resultante:\n";
    for (auto& fila : result) {
        for (auto& pixel : fila) {
            cout << pixel << " ";
        }
        cout << endl;
    }
}

// arbol a string
string cadenaArbol(Nodo* raiz){
    if(!raiz) return "";
    string res = to_string(raiz->valor);
    if(raiz->izquierda){
        res += "(" + cadenaArbol(raiz->izquierda) + ")";
    }
    if(raiz->derecha){
        res += "(" + cadenaArbol(raiz->derecha) + ")";
    }

    return res;
}

// batalla naval - contar barcos
int contarBarcos(vector<vector<char>>& tablero){
    if(tablero.empty() || tablero[0].empty()) return 0;
    int filas = tablero.size();
    int columnas = tablero[0].size();
    int barcos = 0;
    for(int i = 0; i < filas; ++i){
        for(int j = 0; j < columnas; ++j){
            if(tablero[i][j] == 'X'){
                if(i > 0 && tablero[i - 1][j] == 'X') continue; // parte inferior de un barco vertical
                if(j > 0 && tablero[i][j - 1] == 'X') continue; // parte derecha de un barco horizontal
                barcos++;
            }
        }
    }
    return barcos;
}

// islas cerradas - rodeadas de 1
void recorrerIslas(vector<vector<int>>& grid, int i, int j, bool& cerrada){
    int filas = grid.size();
    int columnas = grid[0].size();
    // si está por fuera de límites
    if(i < 0 || j < 0 || i >= filas || j >= columnas) return;
    if(grid[i][j] == 1) return;
    // si toca el borde, no es cerrada
    if(i == 0 || j == 0 || i == filas - 1 || j == columnas -1) cerrada = false;
    
    grid[i][j] = 1; // marcar como visitado

    recorrerIslas(grid, i + 1, j, cerrada); // abajo
    recorrerIslas(grid, i - 1, j, cerrada); // arriba
    recorrerIslas(grid, i, j + 1, cerrada); // derecha
    recorrerIslas(grid, i, j - 1, cerrada); // izquierda
}
int islasCerradas(vector<vector<int>>& grid){
    if(grid.empty() || grid[0].empty()) return 0;
    int filas = grid.size();
    int columnas = grid[0].size();
    int islas = 0;
    for(int i = 0; i < filas; ++i){
        for(int j = 0; j < columnas; ++j){
            if(grid[i][j] == 0){
                bool cerrada = true;
                recorrerIslas(grid, i, j, cerrada);
                if(cerrada) islas++;
            }
        }
    }
    return islas;
}



// ================ BFS ===================

void bfs(Nodo* raiz){
    if(raiz == nullptr) return;
    queue<Nodo*> q;
    q.push(raiz);
    int nivel = 0;

    while(!q.empty()){
        int nodosEnNivel = q.size();
        cout << "Nivel: " << nivel << ": ";
        for(int i = 0; i < nodosEnNivel; ++i){
            Nodo* actual = q.front();
            q.pop();
            
            cout << actual->valor << " ";

            // agregar hijos a la cola
            if(actual->izquierda != nullptr){
                q.push(actual->izquierda);
            }
            if(actual->derecha != nullptr){
                q.push(actual->derecha);
            }
        }
        
        cout << endl;
        nivel++;
    }
}

// movimientos de caballo en ajedrez
int minKnightMoves(int origenX, int origenY, int destinoX, int destinoY){
    if(origenX == destinoX && origenY == destinoY) return 0; // ya está en el destino
    // movimientos posible
    vector<pair<int, int>> movimientos = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };

    queue<pair<int, int>> q;
    q.push({origenX, origenY});

    vector<vector<bool>> visitado(8, vector<bool>(8, false));
    visitado[origenX][origenY] = true;

    int saltos = 0;

    while(!q.empty()){
        int nodosEnNivel = q.size();

        for(int i = 0; i < nodosEnNivel; ++i){
            auto [x, y] = q.front();
            q.pop();

            // ver si estamos en el destino
            if(x == destinoX && y == destinoY){
                cout << "Mínimos movimientos de caballo: " << saltos << endl;
                return saltos;
            }
            for(auto [dx, dy] : movimientos){
            int nuevoX = x + dx;
            int nuevoY = y + dy;
            // verificar límites del tablero
            if(nuevoX >= 0 && nuevoX < 8 && nuevoY >= 0 && nuevoY < 8 && !visitado[nuevoX][nuevoY]){
                visitado[nuevoX][nuevoY] = true;
                q.push({nuevoX, nuevoY});
            }
        }
        }        
        saltos++;
    }
    return -1;
}

void visualizarMovimientoCaballo(int origenX, int origenY, int destinoX, int destinoY) {
    // Mostrar tablero inicial
    cout << "\n📊 Tablero de ajedrez (8x8):" << endl;
    cout << "  0 1 2 3 4 5 6 7" << endl;
    for (int i = 0; i < 8; i++) {
        cout << i << " ";
        for (int j = 0; j < 8; j++) {
            if (i == origenX && j == origenY) {
                cout << " ♞ ";  // Caballo en posición inicial
            } else if (i == destinoX && j == destinoY) {
                cout << "🎯 ";  // Destino
            } else {
                cout << (((i + j) % 2 == 0) ? "⬜" : "⬛") << " ";  // Tablero de ajedrez
            }
        }
        cout << endl;
    }
    
    // Calcular y mostrar el resultado
    int movimientos = minKnightMoves(origenX, origenY, destinoX, destinoY);
    cout << "Número mínimo de movimientos: " << movimientos << endl;

}
void testCaballoAjedrez() {
    visualizarMovimientoCaballo(0, 0, 1, 2);
    visualizarMovimientoCaballo(0, 0, 7, 7);
    visualizarMovimientoCaballo(3, 3, 3, 3);
}

// Rotting oranges

int orangesRotting(vector<vector<int>>& grid){
    // dimensiones
    int m = grid.size();
    if(m == 0) return 0;
    int n = grid[0].size();
    // inicializar cola
    queue<pair<int, int>> q;
    // contar frescas
    int frescas = 0;
    // inicializar cola con podridas iniciales y contar frecas
        // 1 son naranjas, 2 podridas, 0 espacios
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j){
            if(grid[i][j] == 2){
                q.push({i, j});
            } else if(grid[i][j] == 1){
                frescas++;
            }
        }
    }
    // caso base 1, no hay frescas, finaliza
    if(frescas == 0) return 0;
    // caso bsae 2, no hay podridas, finaliza
    if(q.empty()) return -1;
    // direcciones propagacion
    vector<pair<int, int>> dirs = {{-1,0},{0,1},{1,0},{0,-1}};
    // tiempo
    int dias = 0;

    // BFS propagar
    while(!q.empty() && frescas > 0){
        // incrementar días por cada nivel recorrudi
        dias++;
        // procesar las naranjas podridas del nivel actual
        int size = q.size();
        for(int i = 0; i < size; ++i){
            auto [x,y] = q.front();
            q.pop();

            // verificar direcciones
            for(auto& [dx,dy] : dirs){
                int nx = x + dx;
                int ny = y + dy;
                // verificar si en limites hay naranja fresa
                if(nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1){
                    // si hay, pudrir
                    grid[nx][ny] = 2;
                    // agregarla a la cola para proximo  día
                    q.push({nx,ny});
                    // decrementar naranjas frescas
                    frescas--;
                }
            }
        }
    }
    // caso base 3, si aun quedan naranjas frescas, no es posible pudrid todas
    return frescas > 0 ? -1 : dias;
}

void probarNaranjasPodridas(){
    // Caso 1: Todas las naranjas se pudren eventualmente
    vector<vector<int>> grid1 = {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1}
    };
    int resultado1 = orangesRotting(grid1); 
    cout << "días necesarios: " << resultado1 << endl;
    
    // Caso 2: Imposible pudrir todas las naranjas (aisladas)
    vector<vector<int>> grid2 = {
        {2, 1, 1},
        {0, 1, 1},
        {1, 0, 1}
    };
    int resultado2 = orangesRotting(grid2);
    cout << "días necesarios: " << resultado2 << " (imposible)" << endl;
    
    // Caso 3: No hay naranjas frescas inicialmente
    vector<vector<int>> grid3 = {
        {0, 2, 2},
        {0, 0, 2},
        {0, 0, 0}
    };
    int resultado3 = orangesRotting(grid3);
    cout << "días necesarios: " << resultado3 << " (ya terminado)" << endl;
}


// Shortest Bridge Between Islands

void marcarIslas(vector<vector<int>>& grid, int i, int j, int mark){
    int n = grid.size();
    int m = grid[0].size();

    if(i < 0 || j < 0 || i>= n || j >= m || grid[i][j] != 1) return;

    grid[i][j] = mark;

    marcarIslas(grid, i + 1, j, mark); 
    marcarIslas(grid, i - 1, j, mark);
    marcarIslas(grid,i, j - 1, mark);
    marcarIslas(grid, i, j + 1, mark);
}

// encontrar puente mas corto
int shortestBridge(vector<vector<int>>& grid){
    int n = grid.size();

    // cola bfs
    queue<pair<int, int>> q;
    
    // encontrar primera isla y marcarla
    bool found = false;
    for(int i = 0; i < n && !found; ++i){
        for(int j = 0; j < n && !found; ++j){
            if(grid[i][j] == 1){
                marcarIslas(grid, i, j, 2);
                found = true;
                break;
            }
        }
    }
    // añadir celdas de primera isla a la cola
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; ++j){
            if(grid[i][j] == 2){
                q.push({i, j});
            }
        }
    }

    // direcciones
    vector<pair<int, int>> dirs = {{-1,0},{0,1},{1,0},{0,-1}};

    // bfs camino más corto
    int distance = 0;
    while(!q.empty()){
        int size = q.size();
        for(int i = 0; i < size; ++i){
            auto [ x,y] = q.front();
            q.pop();
            // verificar direcciones
            for(auto [dx,dy] : dirs){
                int nx = x + dx;
                int ny = y + dy;
                // verificar limires
                if(nx >= 0 && nx < n && ny >= 0 && ny < n){
                    if(grid[nx][ny] == 1){
                        // encontramos segunda isla
                        return distance;
                    }else if(grid[nx][ny] == 0){
                    // marcar como visitada, parte del puente
                    grid[nx][ny] = 3; // visualizar puente
                    q.push({nx,ny});
                    }
                }
            }
        }
        distance++;

    }
    return -1;
}

void testShortestBridge(){
    vector<vector<int>> grid = {
        {1,1,1,1,1},
        {1,0,0,0,1},
        {1,0,1,0,1},
        {1,0,0,0,1},
        {1,1,1,1,1},
    };
    int resultado = shortestBridge(grid);
    cout << "Puente más corto entre islas: " << resultado << endl;
}

// Buscaminas
vector<vector<char>> buscaminas(vector<vector<char>>&board, vector<int>& click){
    int m = board.size();
    if(m == 0) return board;
    int n = board[0].size();
    int row = click[0];
    int col = click[1];

    cout << "Click en posición: [" << row << "," << col << "]" << endl;

    // Verificar si está dentro de los límites
    if (row < 0 || row >= m || col < 0 || col >= n) {
        cout << "Click fuera de límites!" << endl;
        return board;
    }

    // si da click en mina, terminalo
    if(board[row][col] == 'M'){
        cout << "boom, mina. juego terminado." << endl;
        board[row][col] = 'X';
        return board;
    }
    // si ya fue revelada
    if(board[row][col] != 'E'){
        cout << "La casilla ya fue revelada." << endl;
        return board;
    }

    // direcciones
    vector<pair<int, int>> dirs = {
        {-1,-1}, {-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}
    };

    // mina vacía, contar minas adyacentes
    int count = 0;
    for(auto [dx,dy] : dirs){
        int newRow = row + dx;
        int newCol = col + dy;
        // verificar limites
        if(newRow >= 0 && newRow < m && newCol >= 0 && newCol < n && board[newRow][newCol] == 'E'){
            // contar minas
            if(board[newRow][newCol] == 'M' || board[newRow][newCol] == 'X'){
                count++;
            }
        }
    }

    // mostar minas adyacentes
    if(count > 0){
        cout << "casilla con " << count << " minas adyacentes." << endl;
        board[row][col] = '0' + count; // convertir número a char
    } 
    // si no hay minas adyacentes expandir DFS
    else {
        board[row][col] = 'B';
        // expandir en todas las direcctiones
        for(auto [dx,dy] : dirs){
            int newRow = row + dx;
            int newCol = col + dy;

            if(newRow >= 0 && newRow < m && newCol >= 0 && newCol < m && board[newRow][newCol] == 'E'){
                vector<int> newClick = {newRow, newCol};
                buscaminas(board, newClick);
            }
        }
    }
    return board;
}
void mostrarTablero(const vector<vector<char>>& board) {
    int m = board.size();
    if (m == 0) return;
    int n = board[0].size();
    
    // Imprimir encabezado de columnas
    cout << "  ";
    for (int j = 0; j < n; ++j) {
        cout << j << " ";
    }
    cout << endl;
    
    // Imprimir filas con números
    for (int i = 0; i < m; ++i) {
        cout << i << " ";
        for (int j = 0; j < n; ++j) {
            char cell = board[i][j];
            
            // Representación visual
            if (cell == 'M') cout << "□ "; // Casilla no revelada (podría ser mina)
            else if (cell == 'E') cout << "□ "; // Casilla no revelada
            else if (cell == 'B') cout << "  "; // Casilla vacía revelada
            else if (cell == 'X') cout << "💣"; // Mina explotada
            else cout << cell << " "; // Números 1-8
        }
        cout << endl;
    }
}

// Función para probar el Buscaminas
void probarBuscaminas() {
// Ejemplo 1: Click en casilla sin minas adyacentes (expansión)
    vector<vector<char>> board1 = {
        {'E', 'E', 'E', 'E', 'E'},
        {'E', 'E', 'M', 'E', 'E'},
        {'E', 'E', 'E', 'E', 'E'},
        {'E', 'E', 'E', 'E', 'E'}
    };
    
    cout << "\n🎲 EJEMPLO 1: Click en casilla sin minas adyacentes" << endl;
    cout << "Tablero inicial:" << endl;
    mostrarTablero(board1);
    
    vector<int> click1 = {3, 0}; // Click en esquina inferior izquierda
    vector<vector<char>> result1 = buscaminas(board1, click1);
    
    cout << "\nTablero después del click:" << endl;
    mostrarTablero(result1);
    
    // Ejemplo 2: Click en casilla con minas adyacentes
    vector<vector<char>> board2 = {
        {'E', 'E', 'E', 'E', 'E'},
        {'E', 'E', 'M', 'E', 'E'},
        {'E', 'E', 'E', 'E', 'E'},
        {'E', 'E', 'E', 'E', 'E'}
    };
    
    cout << "\n" << string(50, '=') << endl;
    cout << "🎲 EJEMPLO 2: Click en casilla con mina adyacente" << endl;
    cout << "Tablero inicial:" << endl;
    mostrarTablero(board2);
    
    vector<int> click2 = {1, 1}; // Click adyacente a una mina
    vector<vector<char>> result2 = buscaminas(board2, click2);
    
    cout << "\nTablero después del click:" << endl;
    mostrarTablero(result2);
    
    // Ejemplo 3: Click en una mina
    vector<vector<char>> board3 = {
        {'E', 'E', 'E', 'E', 'E'},
        {'E', 'E', 'M', 'E', 'E'},
        {'E', 'E', 'E', 'E', 'E'},
        {'E', 'E', 'E', 'E', 'E'}
    };
    
    cout << "\n" << string(50, '=') << endl;
    cout << "🎲 EJEMPLO 3: Click directo en una mina" << endl;
    cout << "Tablero inicial:" << endl;
    mostrarTablero(board3);
    
    vector<int> click3 = {1, 2}; // Click en una mina
    vector<vector<char>> result3 = buscaminas(board3, click3);
    
    cout << "\nTablero después del click:" << endl;
    mostrarTablero(result3);
}


// Vuelo más barato con k paradas

/**
 * @param flights Array de vuelos, que continene array con from, to, price.
 * @param src Origen del vuelo
 * @param dst Destino
 * @param k paradas
 */
int encontrarVueloBarato(int n,vector<vector<int>>& flights, int src, int dst, int k){
    // grafo adyacencia: ciudad ->[(destino, precio)]
    vector<vector<pair<int, int>>> graph(n);
    for(auto& flight : flights){
        int from = flight[0];
        int to = flight[1];
        int price = flight[2];
        graph[from].push_back({to, price});
    }

    // cola
    queue<pair<int, int>> q;
    q.push({src, 0});
    // array costo minimo
    vector<int> minCost(n, INT_MAX);

    int paradas = 0;
    // bfs por niveles, cada nivel, una parada
    while(!q.empty() && paradas <= k){
        int size = q.size();
        // vuelos en el nivel actual
        for(int i = 0; i < size; ++i){
            auto [ciudad_actual, costo_actual] = q.front();
            q.pop();
            // vuelos desde ciudad actual
            for(auto [destino, precio] : graph[ciudad_actual]){
                int nuevo_costo = costo_actual + precio;
                // Solo considerar si es mejor
                if(nuevo_costo < minCost[destino]){
                   minCost[destino] = nuevo_costo;
                   q.push({destino, nuevo_costo}); 
                }
            }
        }
        paradas++;
    }
    cout << "Costo mínimo desde " << src << " hasta " << dst << " con " << k << " paradas: " << (minCost[dst] == INT_MAX ? -1 : minCost[dst]) << endl;
    return minCost[dst] == INT_MAX ? -1 : minCost[dst];
}

// Escalera y serpientes

pair<int,int> coordenadas(int casilla, int n){
    casilla --;
    int fila = casilla / n; // ejemplo: 5 / 4 = 1, 6 / 4 = 1
    int columna = casilla % n; // ejemplo: 5 % 4 = 1, 6 % 4 = 2
    // si la fila es impar, invertir columna
    if(fila % 2 == 1){
        columna = n -1 - columna;
    }
    // las filas se cuentan desde abajo hacia arriba
    fila = n - 1 - fila;

    return {fila, columna};
}

int serpientesYEscaleras(vector<vector<int>>& board){
    int n = board.size();
    int destino = n * n; // última casilla
    // bfs
    queue<pair<int, int>> q; // (casilla, movimientos)
    vector<bool> visitado(n * n + 1, false); // n * n + 1 = tamaño del tablero

    q.push({1, 0}); // empezar en casilla 1 con 0 movimientos
    visitado[1] = true; // marcar casilla 1 como visitada

    while(!q.empty()){
        int size = q.size();
        for(int i = 0; i < size; ++i){
            auto[casilla_actual, movimientos] = q.front();
            q.pop(); 
            // si llegamos a destino
            if(casilla_actual == destino){
                return movimientos;
            }
            // probar movimientos del dado 1 a 6
            for(int dado = 1; dado <= 6; ++dado){
                int proxima_casilla = casilla_actual + dado;
                // verificar limites
                if(proxima_casilla > destino) break;
                // verificar si ya llegamos
                if(proxima_casilla == destino) return movimientos + 1;
                // obtener coordenadas
                auto [fila, columna] = coordenadas(proxima_casilla, n);
                // verificar si hay escalera o serpiente
                if(board[fila][columna] != -1){
                    proxima_casilla = board[fila][columna];
                }
                // si no ha sido visitada
                if(!visitado[proxima_casilla]){
                    visitado[proxima_casilla] = true;
                    q.push({proxima_casilla, movimientos + 1});
                }
            }
        }
    }
    return -1;
}

// Visualizar el tablero
void mostrarTablero(const vector<vector<int>>& board) {
    int n = board.size();
    cout << "\n🎮 TABLERO DE JUEGO:" << endl;
    
    for (int i = 0; i < n; ++i) {
        cout << "Fila " << i << ": ";
        for (int j = 0; j < n; ++j) {
            if (board[i][j] == -1) {
                cout << "__ ";
            } else {
                cout << board[i][j] << " ";
                if (board[i][j] < 10) cout << " ";
            }
        }
        cout << endl;
    }
    
    cout << "\n📋 NUMERACIÓN DE CASILLAS (Boustrophedon):" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Fila " << i << ": ";
        for (int j = 0; j < n; ++j) {
            // Calcular número de casilla para esta posición
            int fila_desde_abajo = n - 1 - i;
            int casilla;
            
            if (fila_desde_abajo % 2 == 0) {
                // Fila par: de izquierda a derecha
                casilla = fila_desde_abajo * n + j + 1;
            } else {
                // Fila impar: de derecha a izquierda
                casilla = fila_desde_abajo * n + (n - 1 - j) + 1;
            }
            
            cout << casilla;
            if (casilla < 10) cout << " ";
            cout << " ";
        }
        cout << endl;
    }
}

// horarios del curso

bool tieneCiclo(int curso, vector<vector<int>>& graph, vector<int>& estado){
    if(estado[curso] == 1) return true; // ciclo detectado
    if(estado[curso] == 2) return false; // ya visitado

    estado[curso] = 1; // marcar como en proceso
    for(int vecino : graph[curso]){
        if(tieneCiclo(vecino, graph, estado)) return true;
    }
    estado[curso] = 2; // marcar como visitado
    return false;
}

bool puedeTerminar(int numCursos, vector<vector<int>>& prerequisitos){
    // construir grafo
    vector<vector<int>> graph(numCursos);
    for(auto& pre : prerequisitos){
        graph[pre[1]].push_back(pre[0]); // prerrequisito -> curso
    }
    // estado: 0 no visitado, 1 en proceso, 2 completado
    vector<int> estado(numCursos, 0);

    for(int i = 0; i < numCursos; ++i){
        if(estado[i] == 0 && tieneCiclo(i, graph, estado)){
            return false; // ciclo detectado
        }
    }
    return true; // no hay ciclos
}

// BACKTRACKING

// Generar combinaciones de letras a partir de un número de teléfono

void generarCombinaciones(int pos, string& digits, string palabra, vector<string>& solution, unordered_map<char, string>& teclado){
    if(pos == static_cast<int>(digits.size())){
        if(!palabra.empty()){
            solution.push_back(palabra);
        }
        return;
    }
    for(auto& letra : teclado[digits[pos]]){
        generarCombinaciones(pos + 1, digits, palabra + letra, solution, teclado);
    }
    
}

vector<string> letterCombinations(string digits){
    vector<string> solution;
    if(digits.empty()) return solution;

    unordered_map<char, string> teclado = {
        {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"},
        {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}
    };

    generarCombinaciones(0, digits, "", solution, teclado);
    return solution;
}

void probarCombinacionesLetras(){
    vector<string> resultado = letterCombinations("23");
    for(auto& combinacion : resultado){
        cout << combinacion << endl;
    }
}

// posibles direcciones ip válidas a partir de string

bool esValido(string numero){
    if(numero.empty() || numero.size() > 3) return false;
    if(numero.length() > 1 && numero[0] == '0') return false; // no permitir 0XX
    int valor = stoi(numero);
    return valor >= 0 && valor <= 255;
}

void crearCombinaciones(string ip,vector<string>& IPSvalidas, int index, int cantidadNums, const string& IPvalida){
    if(cantidadNums > 4) return;
    if(cantidadNums == 4 && index == static_cast<int>(ip.size())){
        IPSvalidas.push_back(IPvalida.substr(0, IPvalida.size() - 1)); // eliminar el último punto
        return; 
    }
    for(int i = 1; i < 4; ++i){
        if(index + i > static_cast<int>(ip.size())) break; // evitar desbordamiento
        string numero = ip.substr(index, i);
        if(!esValido(numero)) continue;

        crearCombinaciones(ip, IPSvalidas, index + i, cantidadNums + 1, IPvalida + numero + ".");
    }
}

vector<string> restoreIpsAddress(string s){
    vector<string> IPSvalidas;
    crearCombinaciones(s, IPSvalidas, 0, 0, {});
    return IPSvalidas;
}

void probarIpsRestauradas(){
    vector<string> resultado = restoreIpsAddress("19216801");
    for(auto& ip : resultado){
        cout << ip << endl;
    }
}


// buscar palabras en una matriz

bool dfsWords(vector<vector<char>>& board, int i, int j, int pos, string& word, vector<vector<bool>>& visitado){
    if(pos == static_cast<int>(word.length())) return true;

    int filas = board.size();
    int columnas = board[0].size();

    if(i < 0 || i >= filas || j < 0 || j >= columnas || board[i][j] != word[pos] || visitado[i][j]) return false;

    visitado[i][j] = true;

    bool encontrado = dfsWords(board, i + 1, j, pos + 1, word, visitado) ||
                      dfsWords(board, i - 1, j, pos + 1, word, visitado) ||
                      dfsWords(board, i, j + 1, pos + 1, word, visitado) ||
                      dfsWords(board, i, j - 1, pos + 1, word, visitado);

    visitado[i][j] = false;
    return encontrado;
}

bool wordSearch(vector<vector<char>>& board, string& word){
    if(word.empty()) return true;
    if(board.empty() || board[0].empty()) return false;
    
    int filas = board.size();
    int columnas = board[0].size();

    vector<vector<bool>> visitado(filas, vector<bool>(columnas, false));

    for(int i = 0; i < filas; ++i){
        for(int j = 0; j < columnas; ++j){
            if(dfsWords(board, i, j, 0, word, visitado)){
                return true;
            }
        }
    }
    return false;
}

// combinaciones de sumas posibles
void dfsCombinationSum(vector<int>& candidates, int target, int start, vector<int>& current, vector<vector<int>>& result){
    if(target == 0){
        result.push_back(current);
        return;
    }
    if(target < 0) return;

    for(int i = start; i < static_cast<int>(candidates.size()); ++i){
        // añadir candidato actual a combinación
        current.push_back(candidates[i]);
        // para poder usar el mismo candidato, varias veces, usar i y no i+1
        dfsCombinationSum(candidates, target - candidates[i], i, current, result);
        // remover candidato para probar otra opción
        current.pop_back();
    }

}
vector<vector<int>> combinationSum(vector<int>& candidates, int target){
    vector<vector<int>> result;
    vector<int> current;
    dfsCombinationSum(candidates, target, 0, current, result);
    return result;
}

// dado un array devolver todas las permutaciones distintas
void dfsPermutations(vector<int>& nums, vector<bool> used, vector<int>& current, vector<vector<int>>& result){
    // si la permutación está completa
    if(current.size() == nums.size()){
        result.push_back(current);
        return;
    }
    // probar numeros no usados
    for(size_t i = 0; i < nums.size(); ++i){
        // si está en uso, saltar
        if(used[i]) continue;
        // usar actual
        used[i] = true;
        current.push_back(nums[i]);
        // continuar permutación
        dfsPermutations(nums, used, current, result);
        // remover numero y marcarlo como no usado
        current.pop_back();
        used[i] = false;
    }
}
vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> current;
    vector<bool> used(nums.size(), false);
    
    dfsPermutations(nums, used, current, result);
    return result;
}

const int INF = numeric_limits<int>::max();

/*
1. inicializar arreglo de distancias y arreglo de visitados. init dist con infnito para todos excepto para el nodo de inicio que es 0
2. iterar para todos los nodos
3. seleccionar en cada iteracion el nodo no visitado con la distancia mínima
4. actualizar los vecinos del nodo seleccionado, si la ditancia actual al vecino es mayor que la distancia al nodo seleccionado + peso de la arista, actualizar la distancia al vecino
5. finalizar marcando el nodo seleccionado como visitado para no volver a seleccionarlo
*/
void dijkstra(const vector<vector<pair<int, int>>>& grafo, int inicio){
    int num_nodos = grafo.size();
    vector<int> dist(num_nodos, INF);
    vector<int> predecesor(num_nodos, -1);

    // inicializar distancia del nodo inicio
    dist[inicio] = 0;

    // cola de prioridad para obtener el nodo con la distancia mínima
    // pair {distancia, nodo}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, inicio});
    // recorrer el grafo
    while(!pq.empty()){
        // acceder al primer elemento y tomar la distancia y el nodo
        int d = pq.top().first; // distancia
        int nodo = pq.top().second; // nodo
        pq.pop();
        // si ya encontramos un camino más corto, saltar
        if(d > dist[nodo]) continue;
        // explorar vecinos
        for(auto& arista : grafo[nodo]){
            int vecino = arista.first;
            int peso = arista.second;
            // si encontramos un camino más corto
            if(dist[nodo] + peso < dist[vecino]){
                dist[vecino] = dist[nodo] + peso;
                predecesor[vecino] = nodo;
                pq.push({dist[vecino], vecino});
            }
        }
    }

    cout << "--- algoritmo de Dijkstra ---" << endl;
    for(int i = 0; i < num_nodos; ++i){
        if(dist[i] == INF){
            cout << "Nodo " << i << " está inalcanzable desde el nodo "<< inicio << endl;
        } else {
            cout << "Distancia desde " << inicio << " al nodo " << i << " es " << dist[i] << endl;
        }
    }
}


// bellman-ford: camino más corto en un grafo con pesos negativos
// no funciona si el grafo tiene un ciclo negativo (ciclo donde la suma de los pesos es negativa)
/*
1. inicializar un arreglo de distancias con infinito para todos los nodos excepto el nodo de inicio que es 0
2. relajación: repetir num_nodos -1 vececs el siguiente paso: para cada arista(u -> v), si dist[u] + peso(u,v) < dist[v], actualizar dist[v] = dist[u] + peso(u,v). este proceso de "relajacion" reduce las distancias estimadas
3. verificar ciclos negativos: para cada arista(u -> v), si dist[u] + peso(u,v) < dist[v], entonces hay un ciclo negativo en el grafo
*/
struct Arista{
    // u: nodo origen
    // v: nodo destino
    // peso: peso de la arista
    int u, v, peso;
};
void bellmanFord(const vector<Arista>& aristas, int num_nodos, int inicio){
    vector<int> dist(num_nodos, INF);
    vector<int> predecesor(num_nodos, -1);

    dist[inicio] = 0;
    // relajación. (num_nodos - 1) veces
    for(int i = 0; i < num_nodos -1; ++i){
        for(const auto& arista : aristas){
            if(dist[arista.u] != INF && dist[arista.u] + arista.peso < dist[arista.v]){
                dist[arista.v] = dist[arista.u] + arista.peso;
                predecesor[arista.v] = arista.u;
            }
        }
    }
    // detectar ciclos negativos
    for(const auto& arista : aristas){
        if(dist[arista.u] != INF && dist[arista.u] + arista.peso < dist[arista.v]){
            cout << "El grafo contiene un ciclo negativo" << endl;
            return;
        }
    }

    cout << "--- algoritmo de Bellman-Ford ---" << endl;
    for(int i = 0; i < num_nodos; ++i){
        if(dist[i] == INF){
            cout << "Nodo " << i << " está inalcanzable desde el nodo "<< inicio << endl;
        } else {
            cout << "Distancia desde " << inicio << " al nodo " << i << " es " << dist[i] << endl;
        }
    }
}

// grafo bipartito: particionar un grafo en dos conjutnos
/*
1. inicializar un arreglo de colores y un arreglo de visitados
2. recorrer desde un nodo, asignar un color (0 o 1) y marcar como visitado
3. colorear los vecinos del nodo actual con el color opuesto, si ya tiene un color, verificar que sea el color opuesto
4. si se encuentra un vecino con el mismo color, el grafo no es bipartito
5. repetir para todos los nodos no visitados
*/
bool es_bipartito(const vector<vector<int>>& grafo, int num_nodos){
    // array almacenar color de cada nodo, -1 sin color, 0 y 1 son los dos colores
    vector<int> color(num_nodos, -1);
    // iterar sobre los nodos para manejar grafos desconectados
    for(int inicio = 0; inicio < num_nodos; ++inicio){
        if(color[inicio] == -1){
            // iniciar BFS desde este nodo
            queue<int> q;
            q.push(inicio);
            color[inicio] = 0; // asignar primer color

            while(!q.empty()){
                int nodo = q.front();
                q.pop();
                // verificar vecinos
                for(int vecino : grafo[nodo]){
                    if(color[vecino] == -1){
                        // asignar color opuesto
                        color[vecino] = 1 - color[nodo];
                        q.push(vecino);
                    } else if(color[vecino] == color[nodo]){
                        // vecino tiene el mismo color, no es bipartito
                        return false;
                    }
                }
            }
        }
    }
    return true; // es bipartito
}
const int NUM_WORKERS = 3;
const int NUM_MACHINES = 3;


void workingMachineAsignment(const vector<vector<int>>& grafo, int num_trabajadores){
    vector<int> asignacion(num_trabajadores, -1); // -1 significa no asignado
}
int main(){
    // grafo binario 
    // Nodo* raizBinaria = new Nodo(1);
    // raizBinaria->izquierda = new Nodo(2);
    // raizBinaria->derecha = new Nodo(3);
    // raizBinaria->izquierda->izquierda = new Nodo(4);
    // raizBinaria->izquierda->derecha = new Nodo(5);
    // raizBinaria->derecha->izquierda = new Nodo(6);
    // raizBinaria->derecha->derecha = new Nodo(7);
    // grafo binario
    /*
            1
           / \
          2   3
         / \ / \
        4  5 6  7
    */
    // grafo con hijos
    // Nodo* raiz = new Nodo(1);
    // raiz->hijos.push_back(new Nodo(2));
    // raiz->hijos.push_back(new Nodo(3));
    // raiz->hijos[0]->hijos.push_back(new Nodo(4));
    // raiz->hijos[0]->hijos.push_back(new Nodo(5));
    // raiz->hijos[1]->hijos.push_back(new Nodo(6));
    // raiz->hijos[1]->hijos.push_back(new Nodo(7));
    // Realizar búsqueda DFS

    int num_nodos = 5;
    // Grafo representado como una lista de adyacencia:
    // {nodo_destino, peso}
    vector<vector<pair<int, int>>> grafo(num_nodos);
    grafo[0].push_back({1, 10});
    grafo[0].push_back({2, 5});
    grafo[1].push_back({2, 2});
    grafo[1].push_back({3, 1});
    grafo[2].push_back({1, 3});
    grafo[2].push_back({3, 9});
    grafo[2].push_back({4, 2});
    grafo[3].push_back({4, 4});
    grafo[4].push_back({0, 7});
    grafo[4].push_back({3, 6});

    dijkstra(grafo, 0);

    // Grafo con aristas con pesos negativos
    vector<Arista> aristas;
    aristas.push_back({0, 1, -1});
    aristas.push_back({0, 2, 4});
    aristas.push_back({1, 2, 3});
    aristas.push_back({1, 3, 2});
    aristas.push_back({1, 4, 2});
    aristas.push_back({3, 2, 5});
    aristas.push_back({3, 1, 1});
    aristas.push_back({4, 3, -3});
    
    bellmanFord(aristas, num_nodos, 0);

    num_nodos = 6;
    vector<vector<int>> grafo1(num_nodos);
    // Grafo bipartito
    grafo1[0].push_back(1);
    grafo1[0].push_back(3);
    grafo1[1].push_back(0);
    grafo1[1].push_back(2);
    grafo1[2].push_back(1);
    grafo1[2].push_back(3);
    grafo1[3].push_back(0);
    grafo1[3].push_back(2);
    grafo1[4].push_back(5);
    grafo1[5].push_back(4);
    
    cout << "--- Verificacion de Grafo Bipartito ---" << endl;
    if (es_bipartito(grafo1, num_nodos)) {
        cout << "El grafo es bipartito." << endl;
    } else {
        cout << "El grafo NO es bipartito." << endl;
    }
    
    // Grafo no bipartito (contiene un ciclo de longitud impar)
    vector<vector<int>> grafo2(3);
    grafo2[0].push_back(1);
    grafo2[1].push_back(0);
    grafo2[1].push_back(2);
    grafo2[2].push_back(1);
    grafo2[2].push_back(0);
    
    if (es_bipartito(grafo2, 3)) {
        cout << "El segundo grafo es bipartito." << endl;
    } else {
        cout << "El segundo grafo NO es bipartito." << endl;
    }

    return 0;
}