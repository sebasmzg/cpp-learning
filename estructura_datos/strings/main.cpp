#include <iostream>
#include <string>
#include <vector>

// operaciones comunes de strings
// s.length() - longitud
// s.empty() - si está vacío
// s.append("texto") - concatenar
// s.insert(pos, "texto") - insertar en posición
// s.erase(pos, n) - eliminar n caracteres desde pos
// s.replace(pos, n, "texto") - reemplazar n caracteres desde pos por "texto"
// s.compare("texto") - comparar con otro string, devuelve 0 si son iguales
// s.reverse() - invertir el string
// s.clear() - limpiar el string
// s == "texto" - comparación directa
// s != "texto" - comparación directa
// s[i] - acceder al carácter en la posición i
// s[0] = 'A' - modificar carácter en la posición 0
// s.substr(pos, len) - obtener subcadena desde pos de longitud len
// s.find("texto") - buscar texto, devuelve posición o npos si no se encuentra
// s.rfind("texto") - buscar desde el final, devuelve posición o npos si no se encuentra
// s.find_first_of("abc") - primer carácter que coincida con "abc", devuelve posición o npos
// s.find_last_of("abc") - último carácter que coincida con "abc", devuelve posición o npos
// s.find_first_not_of("abc") - primer carácter que no coincida con "abc", devuelve posición o npos
// s.find_last_not_of("abc") - último carácter que no coincida con "abc", devuelve posición

bool isAnagram(std::string s, std::string t){
    if(s.length() != t.length()) return false;
    std::vector<int> count(26, 0); // Asumiendo solo letras minúsculas a-z

    for(size_t i = 0; i < s.length(); ++i){
        count[s[i] - 'a']++; // Incrementar el conteo para el carácter en s
        // count cuenta la cantidad de veces que aparece cada letra
        // 'a' es el offset para convertir char a índice 0-25
        count[t[i] - 'a']--; // Decrementar el conteo para el carácter en t
    }

    for (int c : count) { // Verificar que todos los conteos sean cero
        // Si algún conteo no es cero, significa que las letras no coinciden
        // y por lo tanto no son anagramas
        // Si todos son cero, entonces son anagramas
        // porque tienen la misma cantidad de cada letra
        // Si count[i] es positivo, significa que hay más letras en s que en t
        // Si count[i] es negativo, significa que hay más letras en t que en s
        if (c != 0) return false;
    }
    return true;
}

int main() {
    std::cout << isAnagram("listen", "silent") << "\n"; // 1 (true)
    std::cout << isAnagram("rat", "car") << "\n";       // 0 (false)
}