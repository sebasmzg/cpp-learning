// Algoritmos Greedy

#include <iostream>
#include <climits>

using namespace std;

/*
*@param coinSet: conjunto de monedas disponibles
*@param n: número de monedas en el conjunto
*@param N: cantidad a cambiar
*/
int greedyChange(int* coinSet, int n, int N){
    if(N == 0) return 0; // Caso base: si no queda cantidad, no se necesitan monedas
    if(N < 0) return INT_MAX; // Caso base: si la cantidad es negativa, no es posible cambiar
    int coins = INT_MAX; // Variable para almacenar el número mínimo de monedas
    // Recorrer set de monedas / opciones
    for(int i = 0; i < n; ++i){
        int result = greedyChange(coinSet, n, N - coinSet[i]);
        if(result != INT_MAX){
            coins = min(coins, result + 1); // result se le suma +1 porque se está usando una moneda más
        }
    }
    return coins;
}

int main(){
    int coinSet[] = {1, 3, 4};
    int N = 8;
    int n = sizeof(coinSet) / sizeof(coinSet[0]);
    int result = greedyChange(coinSet, n, N);
    if(result != INT_MAX){
        cout << "Número mínimo de monedas para cambiar " << N << " es: " << result << endl;
    }else{
        cout << "No es posible cambiar " << N << " con las monedas disponibles." << endl;
    }
    return 0;
}