#include <iostream>

int main(){
    int number = 88;
    int *pNumber = &number;
    std::cout << "number: " << number << std::endl;
    std::cout << "pNumber: " << pNumber << std::endl;
    std::cout << "*pNumber: " << *pNumber << std::endl;

    return 0;
}