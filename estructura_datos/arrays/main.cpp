#include <iostream>
#include <vector>
#include <algorithm>

class DynamicArray {
    private:
        int* data;
        int capacity;
        int size;
    public:
        DynamicArray(int cap) {
            capacity = cap;
            size = 0;
            data = new int[capacity];
        }

        void push_back(int value){ // Añadir un elemento al final
            if(size == capacity) {
                // 1. Guardar puntero actual
                // 2. Crear nuevo array dinamico con nueva capacidad
                // 3. copiar elementos antiguos al nuevo array
                // 4. liberar memoria array viejo delete[]
                // 5. apuntar data al nuevo array
                capacity *= 2; // 1
                int* newData = new int[capacity]; // 2
                for(int i = 0; i < size; ++i){
                    newData[i] = data[i]; // 3
                }
                delete[] data; // 4
                data = newData; // 5
            }
            data[size] = value;
            size++;
        }

        void print() {
            for(int i = 0; i < size; ++i){
                std::cout << data[i] << " ";
            }
            std::cout << "\n"; 
        }
};

class Solution {
public:
    void moveZeroes(std::vector<int>& nums) {
        std::cout << "move zeros:\n";
        int left = 0; // Puntero para la posición de inserción de números no cero
        for(size_t right = 0; right < nums.size(); ++right){ // Iterar sobre el vector
            if(nums[right] != 0){ // Si el número no es cero
                nums[left] = nums[right]; // Moverlo a la posición de inserción
                left++; // Avanzar el puntero de inserción
            }
        }
        for(size_t i = left; i < nums.size(); ++i){ // Rellenar el resto del vector con ceros
            nums[i] = 0;
        }
        // Imprimir el vector resultante
        for(size_t i = 0; i < nums.size(); ++i){
            std::cout << nums[i] << " ";
        }
    }

    void optimized(std::vector<int>& nums){
        std::cout << "\nOptimized approach:\n";
        int pos = 0;
        for(int i = 0; i < nums.size(); ++i){
            if(nums[i] != 0){
                std::swap(nums[pos], nums[i]);
                pos++;
            }
        }
        for(int i = 0; i < nums.size(); ++i){
            std::cout << nums[i] << " ";
        }
    }
};

int main(){
    Solution sol;
    std::vector<int> nums = {0,1,0,3,12};
    sol.moveZeroes(nums);
    sol.optimized(nums);
//     DynamicArray arr(2); // capacidad inicial 2
//     arr.push_back(10);
//     arr.push_back(20);
//     arr.print(); // 10 20
//     arr.push_back(30); // redimensiona
//     arr.print(); // 10 20 30
//     arr.push_back(40);
//     arr.print(); // 10 20 30 40
}