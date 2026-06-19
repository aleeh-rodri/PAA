#include "../algoritmos.h"
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

static int tempo = 0;
static int numSCC = 0;

static void dfsTarjan(int u, const vector<vector<int>>& adj, vector<int>& ids, vector<int>& reduzido,
                      stack<int>& st, vector<bool>& naPilha, vector<int>& sccMap, vector<vector<int>>& sccNodes){

    ids[u] = reduzido[u] = tempo++;
    st.push(u);
    naPilha[u] = true;

    for(int v : adj[u]){
        if(ids[v] == -1){
            dfsTarjan(v, adj, ids, reduzido, st, naPilha, sccMap, sccNodes);
            reduzido[u] = min(reduzido[u], reduzido[v]);
        }else if(naPilha[v]){
            reduzido[u] = min(reduzido[u], ids[v]);
        }
    }

    if(reduzido[u] == ids[u]){
        vector<int> componenteAtual;
        while(true){
            int v = st.top();
            st.pop();
            naPilha[v] = false;
            sccMap[v] = numSCC;
            componenteAtual.push_back(v);
            if(v == u) break;
        }
        sccNodes.push_back(componenteAtual);
        numSCC++;
    }
}

static void dfsAlcanceCondensado(int atual, const vector<set<int>>& adjCondensada, vector<bool>& visitado){

    visitado[atual] = true;
    for(int vizinho : adjCondensada[atual]){
        if(!visitado[vizinho]){
            dfsAlcanceCondensado(vizinho, adjCondensada, visitado);
        }
    }
}

vector<vector<int>> reducaoTransitivaTarjan(int V, const vector<vector<int>>& adj){

    tempo = 0;
    numSCC = 0;
    vector<int> ids(V, -1), reduzido(V, -1), sccMap(V, -1);
    vector<bool> naPilha(V, false);
    stack<int> st;
    vector<vector<int>> sccNodes;

    cout << "\n[LOG TARJAN] Passo 1: Executando Algoritmo de Tarjan para encontrar SCCs..." << endl;

    for(int i = 0; i < V; i++){
        if(ids[i] == -1){
            dfsTarjan(i, adj, ids, reduzido, st,naPilha, sccMap, sccNodes);
        }
    }

    cout << "[LOG TARJAN] Passo 2: Condesando as " << numSCC << "SCCs encontradas em um DAG..." << endl;
    vector<set<int>> adjCondesada(numSCC);
    map<pair<int, int>, pair<int, int>> arestaRepresentante;

    for(int u = 0; u < V; u++){
        for(int v : adj[u]){
            int sccU = sccMap[u];
            int sccV = sccMap[v];
            if(sccU != sccV){
                adjCondesada[sccU].insert(sccV);
                arestaRepresentante[{
                    sccU, sccV
                }] = {u, v};
            }
        }
    }

    cout << "[LOG TARJAN] Passo 3: Realizando Reducao Transitiva no Grafo Condensado..." << endl;
    vector<set<int>> adjCondesadaReduzida = adjCondesada;

    for(int i = 0; i < numSCC; i++){
        for(int vizinho : adjCondesada[i]){
            vector<bool> alcancado(numSCC, false);
            dfsAlcanceCondensado(vizinho, adjCondesada, alcancado);

            for(int w : adjCondesada[i]){
                if(vizinho != w && alcancado[w]){
                    adjCondesadaReduzida[i].erase(w);
                }
            }
        }
    }

    cout << "[LOG TARJAN] Passo 4: Expandindo SCCs em Aneis e montando Sub-Grafo Final..." << endl;
    vector<vector<int>> subGrafo(V);

    for(const auto& componente: sccNodes){
        if(componente.size() > 1){
            for(size_t i = 0; i < componente.size(); i++){
                int u = componente[i];
                int prox = componente[(i +1) % componente.size()];
                subGrafo[u].push_back(prox);
                cout << "   -> [ANEL SCC] Adicionada aresta de ciclo vital: " << u << " -> " << prox << endl;
            }
        }
    }

    for(int i = 0; i < numSCC; i++){
        for(int j : adjCondesadaReduzida[i]){
            pair<int, int> arestaOriginal = arestaRepresentante[{i, j}];
            subGrafo[arestaOriginal.first].push_back(arestaOriginal.second);
            cout << "   -> [PONTE SCC] Restaurada aresta essencial entre grupos: " << arestaOriginal.first << " -> " << arestaOriginal.second << endl;
        }
    }

    cout << "[LOG TARJAN] Reducao concluida com sucesso gerando sub-grafo!" << endl;
    return subGrafo;
}
