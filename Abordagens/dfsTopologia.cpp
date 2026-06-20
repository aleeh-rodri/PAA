#include "../algoritmos.h"
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// DFS auxiliar para gerar a ordenacao topologica.
// O vertice so entra na pilha depois que todos os seus vizinhos foram visitados.
static void topologicalSortDFS(int u, const vector<vector<int>>& adj, vector<bool>& visitado, stack<int>& pilha) {
    visitado[u] = true;

    for (int vizinho : adj[u]) {
        if (!visitado[vizinho]) {
            topologicalSortDFS(vizinho, adj, visitado, pilha);
        }
    }

    pilha.push(u);
}

// Funcao que executa a ordenacao topologica usando std::stack.
static vector<int> topologicalSort(int V, const vector<vector<int>>& adj) {
    vector<bool> visitado(V, false);
    stack<int> pilha;

    for (int i = 0; i < V; i++) {
        if (!visitado[i]) {
            topologicalSortDFS(i, adj, visitado, pilha);
        }
    }

    vector<int> ordem;

    while (!pilha.empty()) {
        ordem.push_back(pilha.top());
        pilha.pop();
    }

    return ordem;
}

// Reducao transitiva baseada em DFS Topologica.
// Considera que o grafo de entrada e um DAG.
vector<vector<int>> reducaoDFSTopologica(int V, const vector<vector<int>>& adj) {
    cout << "[MODULO DFS TOPOLOGICA] Calculando ordenacao topologica..." << endl;

    vector<int> ordemTopologica = topologicalSort(V, adj);

    cout << "[MODULO DFS TOPOLOGICA] Ordem topologica encontrada: ";
    for (int vertice : ordemTopologica) {
        cout << vertice << " ";
    }
    cout << endl;

    // alcance[u][v] indica se u consegue alcancar v.
    vector<vector<bool>> alcance(V, vector<bool>(V, false));

    cout << "[MODULO DFS TOPOLOGICA] Processando vertices em ordem topologica inversa..." << endl;

    // Processa de tras para frente.
    // Assim, quando analisamos u, os alcances dos seus filhos ja foram calculados.
    for (int idx = (int)ordemTopologica.size() - 1; idx >= 0; idx--) {
        int u = ordemTopologica[idx];

        for (int v : adj[u]) {
            // u alcanca diretamente v.
            alcance[u][v] = true;

            // u tambem herda todos os vertices que v alcanca.
            for (int w = 0; w < V; w++) {
                if (alcance[v][w]) {
                    alcance[u][w] = true;
                }
            }
        }
    }

    vector<vector<int>> reducaoAdj = adj;

    cout << "[MODULO DFS TOPOLOGICA] Verificando arestas transitivas..." << endl;

    // Para cada aresta direta u -> v, verifica se existe outro vizinho x de u
    // que tambem consegue alcancar v. Se existir, u -> v e transitiva.
    for (int u = 0; u < V; u++) {
        for (int v : adj[u]) {
            bool transitiva = false;

            for (int x : adj[u]) {
                if (x != v && alcance[x][v]) {
                    transitiva = true;

                    cout << "   -> [REMOVIDA] Aresta (" << u << " -> " << v
                         << ") - DFS Topologica encontrou caminho alternativo via "
                         << x << "." << endl;

                    break;
                }
            }

            if (transitiva) {
                reducaoAdj[u].erase(
                    remove(reducaoAdj[u].begin(), reducaoAdj[u].end(), v),
                    reducaoAdj[u].end()
                );
            }
        }
    }

    cout << "[MODULO DFS TOPOLOGICA] Reducao concluida." << endl;

    return reducaoAdj;
}