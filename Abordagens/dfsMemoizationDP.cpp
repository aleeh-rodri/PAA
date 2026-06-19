#include "../algoritmos.h"
#include <iostream>
#include <algorithm>

using namespace std;

void dfsMemoization(int u, const vector<vector<int>>& adj, vector<vector<bool>>& alcancado, vector<bool>& calculado, int V){
    if(calculado[u]) {
        return;
    }

    calculado[u] = true;

    for(int v : adj[u]){
        dfsMemoization(v, adj, alcancado, calculado, V);
        alcancado[u][v] = true;

        for(int w = 0; w < V; w++){
            if(alcancado[v][w]){
                alcancado[u][w] = true;
            }
        }
    }
}

vector<vector<int>> reducaoTransitivaMemoization(int V, const vector<vector<int>>& adj){
    vector<vector<bool>> alcancado(V, vector<bool>(V, false));
    vector<bool> calculado(V, false);

    cout << "[LOG MEMOIZATION] Construindo a tabela de atingibilidade com Programacao Dinamica..." << endl;

    for(int i = 0; i < V; i++){
        if(!calculado[i]) dfsMemoization(i, adj, alcancado, calculado, V);
    }

    vector<vector<int>> reducaoAdj = adj;

    for(int i = 0; i < V; i++){
        for(int w : adj[i]){
            bool trasitivo = false;
            for(int vizinho : adj[i]){
                if(vizinho != w && alcancado[vizinho][w]){
                    trasitivo = true;
                    cout << "   -> [REMOVIDA] (" << i << " -> " << w << "). Memoization mostra que " << vizinho << " chega em " << w << "." << endl;
                    break;
                }
            }
            if(trasitivo){
                reducaoAdj[i].erase(remove(reducaoAdj[i].begin(), reducaoAdj[i].end(), w), reducaoAdj[i].end());
            }
        }
    }
    return reducaoAdj;
}
