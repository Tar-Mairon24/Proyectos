#include <utility>
#include <random>
#include <vector>
#include <iostream>
#include <iomanip>

bool esEstadoFinal(std::pair<int, int> jarra) {
    if (jarra.first == 2) {
        return true;
    }
    return false;

}

std::vector<int> generarReglas(std::pair<int, int> jarra) {
    std::vector<int> reglas;
    if(jarra.first < 4) {
            reglas.push_back(1);
        }
    if(jarra.second < 3) {
        reglas.push_back(2);
    }
    if(jarra.first > 0) {
        reglas.push_back(3);
    }
    if(jarra.second > 0) {
        reglas.push_back(4);
    }
    if(jarra.first > 0 && jarra.second < 3 && jarra.first + jarra.second >= 3) {
        reglas.push_back(5);
    }
    if(jarra.first < 4 && jarra.second > 0 && jarra.first + jarra.second >= 4) {
        reglas.push_back(6);
    }
    if(jarra.first > 0 && jarra.second < 3 && jarra.first + jarra.second <= 3) {
        reglas.push_back(7);
    }
    if(jarra.first < 4 && jarra.second > 0 && jarra.first + jarra.second <= 4) {
        reglas.push_back(8);
    }

    return reglas;
}

std::pair<int, int> aplicarRegla(std::pair<int, int> jarra, int regla) {
    switch(regla) {
        case 1:
            jarra.first = 4;
            break;
        case 2:
            jarra.second = 3;
            break;
        case 3:
            jarra.first = 0;
            break;
        case 4:
            jarra.second = 0;
            break;
        case 5:
            jarra.first = jarra.first - (3 - jarra.second);
            jarra.second = 3;
            break;
        case 6:
            jarra.second = jarra.second - (4 - jarra.first);
            jarra.first = 4;
            break;
        case 7:
            jarra.second = jarra.first + jarra.second;
            jarra.first = 0;
            break;
        case 8:
            jarra.first = jarra.first + jarra.second;
            jarra.second = 0;
            break;
    }
    return jarra;
}

int main() {
    std::pair<int, int> jarra = {0, 0};
    std::vector<int> reglas;
    int contador = 0;

    std::cout << std::left << std::setw(20) << "Estado Actual" 
              << std::setw(20) << "Reglas Posibles" 
              << std::setw(20) << "Regla utilizada" 
              << std::setw(12) << "Nuevo Estado" << std::endl;

    while(!esEstadoFinal(jarra)) {
        reglas = generarReglas(jarra);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, reglas.size() - 1);

        int regla = reglas[dis(gen)];

        std::cout << std::setw(20) << "(" + std::to_string(jarra.first) + ", " + std::to_string(jarra.second) + ")";

        std::string reglas_str;
        for(int i = 0; i < reglas.size(); i++) {
            reglas_str += std::to_string(reglas[i]) + " ";
        }
        std::cout << std::setw(20) << reglas_str << std::setw(20) << regla;;

        jarra = aplicarRegla(jarra, regla);

        std::cout << std::setw(20) << "(" + std::to_string(jarra.first) + ", " + std::to_string(jarra.second) + ")" << std::endl;

        if(contador % 30 == 0 && contador > 29) {
            std::cout << std::left << std::setw(20) << "Estado Actual" 
              << std::setw(20) << "Reglas Posibles" 
              << std::setw(20) << "Regla utilizada" 
              << std::setw(20) << "Nuevo Estado" << std::endl;
        }
        contador++;
    }

    std::cout << "\nSe ha llegado al estado final(" << std::to_string(jarra.first) << ", " << std::to_string(jarra.second) << ") en " << contador << " pasos" << std::endl;

    return 0;
}