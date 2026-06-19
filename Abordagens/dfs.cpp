#include "../algoritmos.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Função interna auxiliar (static indica que ela só pertence a este arquivo)
static void dfsAcessivel(int atual, const vector<vector<int>>& adj, vector<bool>& visitado) {
    visitado[atual] = true;
    for (int vizinho : adj[atual]) {
        if (!visitado[vizinho]) dfsAcessivel(vizinho, adj, visitado);
    }
}

// Implementação oficial do método declarado no header
vector<vector<int>> reducaoDFS(int V, const vector<vector<int>>& adj) {
    vector<vector<int>> reducaoAdj = adj;
    cout << "[MODULO DFS] Executando analise de caminhos..." << endl;

    for (int i = 0; i < V; ++i) {
        for (int vizinho : adj[i]) {
            vector<bool> alcancavel(V, false);
            dfsAcessivel(vizinho, adj, alcancavel);

            for(int w : adj[i]) {
                if(vizinho != w && alcancavel[w]) {
                    cout << "   -> [REMOVIDA] Aresta (" << i << " -> " << w << ") por transitividade." << endl;
                    reducaoAdj[i].erase(remove(reducaoAdj[i].begin(), reducaoAdj[i].end(), w), reducaoAdj[i].end());
                }
            }
        }
    }
    return reducaoAdj;
}
