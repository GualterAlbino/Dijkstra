#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <stack>
#define INFINITO 10000000

using namespace std;

class Grafo {
private:
    int numVertices;
    list<pair<int, int>> *adjacencias;

public:
    Grafo(int numVertices) {
        this->numVertices = numVertices;
        adjacencias = new list<pair<int, int>>[numVertices];
    }

    //Fun��o que trasnforma meu mapeamento em uma matriz
    void adicionarAresta(int v1, int v2, int custo) {
        adjacencias[v1].push_back(make_pair(v2, custo));
    }

    int dijkstra(int origem, int destino, vector<int>& verticesPercorridos) {
        int distancias[numVertices]; // Dist�ncias m�nimas para cada v�rtice
        int visitados[numVertices]; // Vetor para marcar os v�rtices visitados
        int antecessor[numVertices]; // Rastreamento de v�rtices antecessores

        //A priority permite que seja determinada a ordem dos elementos por armazenar o valor do segundo elemento
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> filaPrioridade;

        for (int i = 0; i < numVertices; i++) {
            distancias[i] = INFINITO;  // Inicializa todas as dist�ncias como infinito
            visitados[i] = false; // Inicializa todos os v�rtices como n�o visitados
            antecessor[i] = -1; // Inicializa o vetor de antecessores
        }

        distancias[origem] = 0; // A dist�ncia do v�rtice de origem para ele mesmo � 0
        filaPrioridade.push(make_pair(distancias[origem], origem)); // Insere o v�rtice de origem na fila de prioridade

        while (!filaPrioridade.empty()) {
            pair<int, int> par = filaPrioridade.top();
            int vertice = par.second;
            filaPrioridade.pop();

            if (visitados[vertice] == false) {
                visitados[vertice] = true;// Marca o v�rtice como visitado

                list<pair<int, int>>::iterator it;

                for (it = adjacencias[vertice].begin(); it != adjacencias[vertice].end(); it++) {
                    int verticeAdjacente = it->first;
                    int custoAresta = it->second;

                    if (distancias[verticeAdjacente] > (distancias[vertice] + custoAresta)) {
                        distancias[verticeAdjacente] = distancias[vertice] + custoAresta;
                        antecessor[verticeAdjacente] = vertice; // Atualiza o antecessor do v�rtice

                        // Insere na fila se uma dist�ncia menor for encontrada
                        filaPrioridade.push(make_pair(distancias[verticeAdjacente], verticeAdjacente));
                    }
                }
            }
        }

         // Rastrear os v�rtices percorridos
        int vertice = destino;
        while (vertice != -1) {
            verticesPercorridos.push_back(vertice);
            vertice = antecessor[vertice];
        }

        //reverse(verticesPercorridos.begin(), verticesPercorridos.end());

        return distancias[destino];
    }
};

int main() {
    Grafo grafo(15);

    // Primeiro fluxo
    grafo.adicionarAresta(0, 1, 200); // A -> B
    grafo.adicionarAresta(1, 2, 300); // B -> C
    grafo.adicionarAresta(2, 3, 500); // C -> D
    grafo.adicionarAresta(3, 4, 400); // D -> E
    grafo.adicionarAresta(4, 5, 900); // E -> F
    grafo.adicionarAresta(5, 6, 800); // F -> G
    grafo.adicionarAresta(6, 7, 900); // G -> H
    grafo.adicionarAresta(7, 8, 1200); // H -> I (5,2KM)

    // Segundo fluxo
    grafo.adicionarAresta(2, 9, 200); // C -> J
    grafo.adicionarAresta(9, 10, 700); // J -> K
    grafo.adicionarAresta(10, 11, 450); // K -> L
    grafo.adicionarAresta(11, 12, 600); // L -> M
    grafo.adicionarAresta(12, 13, 650); // M -> N
    grafo.adicionarAresta(13, 14, 1200); // N -> O
    grafo.adicionarAresta(14, 8, 2000); // O -> I (6,3KM)

    int origem = 0;  // V�rtice de origem (A)
    int destino = 8; // V�rtice de destino (I)

    vector<int> verticesPercorridos;

    int distancia = grafo.dijkstra(origem, destino, verticesPercorridos);

    cout << "Melhor caminho de " << char('A' + origem) << " para " << char('A' + destino) << ": ";
    for (int i = 0; i < verticesPercorridos.size(); i++) {
        cout << char('A' + verticesPercorridos[i]);
        if (i != verticesPercorridos.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;

    cout << "Dist�ncia total percorrida: " << distancia << " metros" << endl;

    int quantidadeVerticesPercorridos = verticesPercorridos.size();
    cout << "Quantidade de v�rtices percorridos: " << quantidadeVerticesPercorridos << endl;

    return 0;
}
