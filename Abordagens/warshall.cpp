#include "../algoritmos.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> reducaoWarshall(int V, const vector<vector<int>>& adj) {
    cout << "[MODULO WARSHALL] Construindo matriz de adjacencia e calculando fecho transitivo..." << endl;

    // Matriz de alcance: alcance[i][j] indica se existe caminho de i ate j
    vector<vector<bool>> alcance(V, vector<bool>(V, false));

    // 1. Converte lista de adjacencia para matriz de adjacencia
    for (int i = 0; i < V; i++) {
        for (int vizinho : adj[i]) {
            alcance[i][vizinho] = true;
        }
    }

    // 2. Algoritmo de Warshall para calcular o fecho transitivo
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (alcance[i][k] && alcance[k][j]) {
                    alcance[i][j] = true;
                }
            }
        }
    }

    // 3. Copia o grafo original para remover apenas as arestas transitivas
    vector<vector<int>> reducaoAdj = adj;

    cout << "[MODULO WARSHALL] Verificando arestas transitivas..." << endl;

    // 4. Para cada aresta direta i -> j, verifica se existe caminho alternativo i -> k -> j
    for (int i = 0; i < V; i++) {
        for (int j : adj[i]) {
            bool transitiva = false;

            for (int k = 0; k < V; k++) {
                if (k != i && k != j && alcance[i][k] && alcance[k][j]) {
                    transitiva = true;

                    cout << "   -> [REMOVIDA] Aresta (" << i << " -> " << j
                         << ") - Warshall encontrou caminho alternativo passando por "
                         << k << "." << endl;

                    break;
                }
            }

            if (transitiva) {
                reducaoAdj[i].erase(
                    remove(reducaoAdj[i].begin(), reducaoAdj[i].end(), j),
                    reducaoAdj[i].end()
                );
            }
        }
    }

    cout << "[MODULO WARSHALL] Reducao concluida." << endl;

    return reducaoAdj;
}