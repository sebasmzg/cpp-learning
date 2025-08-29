#include <iostream> 

int busquedaBinIterativa(int a[], int n, int clave){
    int central, bajo, alto;
    int valorCentral;
    bajo = 0;
    alto = n - 1;
    while(bajo <= alto){
        central = (bajo + alto) / 2;
        valorCentral = a[central];
        if(valorCentral == clave){
            return central;
        } else if(valorCentral < clave){
            bajo = central + 1;
        } else {
            alto = central - 1;
        }
    }
    return -1; // No encontrado
}


int main(){
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int clave = 3;
    int resultado = busquedaBinIterativa(arr, n, clave);
    if(resultado != -1){
        std::cout << "Elemento encontrado en el índice: " << resultado << std::endl;
    } else {
        std::cout << "Elemento no encontrado." << std::endl;
    }
    return 0;
}