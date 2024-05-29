#include <iostream>
#include <vector>
#include <algorithm>

// Definición de la clase Nodo
class Node {
public:
    std::vector<std::vector<char>> data; // Datos del nodo
    int level; // Nivel del nodo
    int fval; // Valor de la función de evaluación f

    // Constructor del nodo
    Node(std::vector<std::vector<char>> data, int level, int fval) {
        this->data = data;
        this->level = level;
        this->fval = fval;
    }

    // Función para encontrar la posición de un caracter en los datos del nodo
    std::pair<int, int> find(char x) {
        for (int i = 0; i < data.size(); i++) {
            for (int j = 0; j < data[i].size(); j++) {
                if (data[i][j] == x) {
                    return {i, j}; // Retorna la posición del caracter
                }
            }
        }
        return {-1, -1}; // Retorna -1, -1 si el caracter no se encuentra
    }

    // Función para copiar los datos de un nodo
    std::vector<std::vector<char>> copy(std::vector<std::vector<char>> root) {
        std::vector<std::vector<char>> temp;
        for (auto &i : root) {
            std::vector<char> t;
            for (auto &j : i) {
                t.push_back(j);
            }
            temp.push_back(t);
        }
        return temp; // Retorna la copia de los datos
    }

    // Función para intercambiar dos posiciones en los datos del nodo
    std::vector<std::vector<char>> shuffle(std::vector<std::vector<char>> puz, int x1, int y1, int x2, int y2) {
        if (x2 >= 0 && x2 < data.size() && y2 >= 0 && y2 < data.size()) {
            std::vector<std::vector<char>> temp_puz = copy(puz);
            char temp = temp_puz[x2][y2];
            temp_puz[x2][y2] = temp_puz[x1][y1];
            temp_puz[x1][y1] = temp;
            return temp_puz; // Retorna los datos con las posiciones intercambiadas
        } else {
            return {}; // Retorna un vector vacío si las posiciones son inválidas
        }
    }

    // Función para generar los hijos de un nodo
    std::vector<Node*> generate_child() {
        auto [x, y] = find('_'); // Encuentra la posición del caracter '_'
        std::vector<std::pair<int, int>> val_list = {{x, y - 1}, {x, y + 1}, {x - 1, y}, {x + 1, y}}; // Lista de posiciones a intercambiar
        std::vector<Node*> children; // Vector para almacenar los hijos
        for (auto &i : val_list) {
            auto child = shuffle(data, x, y, i.first, i.second); // Intercambia las posiciones
            if (!child.empty()) {
                Node* child_node = new Node(child, level + 1, 0); // Crea un nuevo nodo hijo
                children.push_back(child_node); // Agrega el hijo a la lista de hijos
            }
        }
        return children; // Retorna la lista de hijos
    }
};

// Definición de la clase Puzzle
class Puzzle {
public:
    int n, moves; // Tamaño del puzzle
    std::vector<Node*> open; // Lista de nodos abiertos
    std::vector<Node*> closed; // Lista de nodos cerrados

    // Constructor del puzzle
    Puzzle(int size) {
        n = size;
    }

    // Función para aceptar los datos del puzzle desde la entrada estándar
    std::vector<std::vector<char>> accept() {
        std::vector<std::vector<char>> puz;
        for (int i = 0; i < n; i++) {
            std::vector<char> temp(n);
            for (int j = 0; j < n; j++) {
                std::cin >> temp[j];
            }
            puz.push_back(temp);
        }
        return puz; // Retorna los datos del puzzle
    }

    // Función heurística para calcular la distancia entre el estado actual y el objetivo
    int h(std::vector<std::vector<char>> start, std::vector<std::vector<char>> goal) {
        int temp = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (start[i][j] != goal[i][j] && start[i][j] != '_') {
                    temp += 1;
                }
            }
        }
        return temp; // Retorna la distancia
    }

    // Función para calcular el valor de la función de evaluación f
    int f(Node* start, std::vector<std::vector<char>> goal) {
        return h(start->data, goal) + start->level; // Retorna el valor de f
    }

    // Función para procesar el puzzle
    void process() {
        std::cout << "Ingresa el estado inicial " << std::endl;
        auto start = accept(); // Acepta el estado inicial
        std::cout << "Ingresa el estado meta " << std::endl;        
        auto goal = accept(); // Acepta el estado objetivo

        Node* startNode = new Node(start, 0, 0); // Crea el nodo inicial
        startNode->fval = f(startNode, goal); // Calcula el valor de f para el nodo inicial
        open.push_back(startNode); // Agrega el nodo inicial a la lista abierta

        while (true) {
            Node* cur = open[0]; // Toma el primer nodo de la lista abierta
            std::cout << "\n";
            std::cout << "  | \n";
            std::cout << "  | \n";
            std::cout << " \\\'/ \n\n";
            if(h(cur->data, goal) != 0)
                std::cout << "Explorando nivel: " << cur->level + 1 << std::endl;
            else {
                std::cout << "Estado final encontrado" << std::endl;
                std::cout << "f' final = " << f(cur, goal) << std::endl;
                std::cout << "Numero de pasos: " << cur->level + 1 << std::endl;
            }
            for (auto &i : cur->data) {
                for (auto &j : i) {
                    std::cout << "\033[1;31m" << j << " ";
                }
                std::cout << "\033[0m" << std::endl;
            }
            if (h(cur->data, goal) == 0) {
                break; // Si la distancia al objetivo es 0, termina el bucle
            }
            for (auto &i : cur->generate_child()) {
                i->fval = f(i, goal); // Calcula el valor de f para cada hijo
                std::cout << "\n";
                std::cout << "\033[34m"<< "f' = " << f(i, goal) << "\033[0m" << std::endl;
                for (auto &row : i->data) {
                    for (auto &col : row) {
                        std::cout << col << " ";
                    }
                    std::cout << "\n";
                }
                open.push_back(i); // Agrega el hijo a la lista abierta
            }
            closed.push_back(cur); // Agrega el nodo actual a la lista cerrada
            open.erase(open.begin()); // Elimina el nodo actual de la lista abierta

            // Ordena la lista abierta en base al valor de f
            std::sort(open.begin(), open.end(), [](Node* a, Node* b) {
                return a->fval < b->fval;
            });
        }

        // Elimina los nodos de la lista abierta
        for (auto &i : open) {
            delete i;
        }
        // Elimina los nodos de la lista cerrada
        for (auto &i : closed) {
            delete i;
        }
    }
};

// Función principal
int main() {
    Puzzle puz(3); // Crea un nuevo puzzle de tamaño 3
    puz.process(); // Procesa el puzzle
    return 0; // Retorna 0
}