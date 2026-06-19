#include <iostream>
#include "algoritmos.h"

using namespace std;

void printGrafo(const string& titulo, const vector<vector<int>>& adj) {
    cout << "\n=== " << titulo << " ===" << endl;
    for (size_t i = 0; i < adj.size(); ++i) {
        cout << "Vertice " << i << " aponta para: ";
        if (adj[i].empty()) {
            cout << "(ninguem)";
        } else {
            for (int vizinho : adj[i]) cout << vizinho << " ";
        }
        cout << endl;
    }
    cout << "=========================\n" << endl;
}

int main() {
    //Grafo Sem Ciclo
    int V = 8;
    vector<vector<int>> listaAdj(V);
    listaAdj[0] = {1, 2, 3, 4, 7};
    listaAdj[1] = {2, 3, 5};
    listaAdj[2] = {3, 4, 6};
    listaAdj[3] = {4, 5, 7};
    listaAdj[4] = {5, 6};
    listaAdj[5] = {6, 7};
    listaAdj[6] = {7};
    listaAdj[7] = {};

    //Grafo Com Ciclo
    int V2 = 6;
    vector<vector<int>> listaAdjCiclo(V2);
    listaAdjCiclo[0] = {1, 5};
    listaAdjCiclo[1] = {2};
    listaAdjCiclo[2] = {0, 3, 4}; //Liga o ciclo 1 ao ciclo 2
    listaAdjCiclo[3] = {4, 5};
    listaAdjCiclo[4] = {3,5};
    listaAdjCiclo[5] = {};

    int opcao = -1;
    while (opcao != 0) {
        cout << "\n=== PAINEL DE METODOS MODULARES ===" << endl;
        cout << "1. Executar Modulo DFS" << endl;
        cout << "2. Executar Modulo BFS" << endl;
        cout << "3. Executar DFS com Memoization (DP)" << endl;
        cout << "4. Executar Tratamento de Ciclos SCC (Tarjan)" << endl;
        cout << "5. Executar Warshall com Matriz de Adjacencia" << endl;
        cout << "8. Exibir Grafo Original" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        vector<vector<int>> resultado;

        switch (opcao) {
            case 1:
                printGrafo("Grafo Original", listaAdj);
                resultado = reducaoDFS(V, listaAdj);
                printGrafo("Resultado: Modulo DFS", resultado);
                break;

            case 2:
                printGrafo("Grafo Original", listaAdj);
                resultado = reducaoBFS(V, listaAdj);
                printGrafo("Resultado: Modulo BFS", resultado);
                break;

            case 3:
                printGrafo("Grafo Original", listaAdj);
                resultado = reducaoTransitivaMemoization(V, listaAdj);
                printGrafo("Resultado: DFS com Memoization (DP)", resultado);
                break;

            case 4:
                printGrafo("Grafo Original", listaAdjCiclo);
                resultado = reducaoTransitivaTarjan(V2, listaAdjCiclo);
                printGrafo("Resultado: Tratamento de Ciclos SCC (Tarjan)", resultado);
                break;

            case 5:
                printGrafo("Grafo Original", listaAdj);
                resultado = reducaoWarshall(V, listaAdj);
                printGrafo("Resultado: Warshall com Matriz de Adjacencia", resultado);
                break;

            case 8:
                printGrafo("Grafo Original", listaAdj);
                break;

            case 0:
                cout << "Saindo do programa..." << endl;
                break;

            default:
                cout << "Opcao invalida!" << endl;
        }
    }
    return 0;
}
