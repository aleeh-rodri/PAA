#include "../algoritmos.h"
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

vector<vector<int>> reducaoBFS(int V, const vector<vector<int>>& adj){
    vector<vector<int>> reducaoAdj  = adj;
    cout << "[MODULO BFS] Analisando niveis e vizinhanca com fila..." << endl;

    for(int i = 0; i < V; i++){
        for(int vizinho : adj[i]){
            vector<bool> visitado(V, false);
            queue<int> q;
            q.push(vizinho);
            visitado[vizinho] = true;

            while(!q.empty()){
                int atual = q.front();
                q.pop();
                for(int prox : adj[atual]){
                    if(!visitado[prox]){
                        visitado[prox] = true;
                        q.push(prox);
                    }
                }
            }

            for(int w : adj[i]){
                if(vizinho != w && visitado[w]){
                    cout << "   -> [REMOVIDA] Aresta (" << i <<" -> " << w << ") - Encontrada atraves de BFS a partir de " << vizinho << "." << endl;
                    reducaoAdj[i].erase(remove(reducaoAdj[i].begin(), reducaoAdj[i].end(), w), reducaoAdj[i].end());
                }
            }
        }
    }
    return reducaoAdj;
}
