#include "grafo.h"
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <string>
#include <utility>
using namespace std;

Grafo::Grafo(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo. Verifique o nome ou o local." << endl;
        return;
    }

    arquivo >> n >> m;

    map<string, int> nomeParaIndice;
    indiceParaNome.resize(n);

    for (int i = 0; i < n; ++i) {
        string nome;
        arquivo >> nome;
        nomeParaIndice[nome] = i;
        indiceParaNome[i] = nome;
    }

    matrizAdj.resize(n, vector<int>(n, 0));

    for (int i = 0; i < m; ++i) {
        string nome1, nome2;
        arquivo >> nome1 >> nome2;

        if (nomeParaIndice.find(nome1) == nomeParaIndice.end() ||
            nomeParaIndice.find(nome2) == nomeParaIndice.end()) {
            cout << "Atencao: vertice nao reconhecido na aresta " << nome1 << " - " << nome2 << endl;
            continue;
        }

        int idx1 = nomeParaIndice[nome1];
        int idx2 = nomeParaIndice[nome2];

        matrizAdj[idx1][idx2]++;
        matrizAdj[idx2][idx1]++;
    }

    arquivo.close();
}

void Grafo::imprimirMatriz() const {
    cout << "\nMatriz de Adjacencia:\n";
    for (const auto& linha : matrizAdj) {
        for (int val : linha) {
            cout << val << " ";
        }
        cout << endl;
    }
}

void Grafo::imprimirArestas() const {
    cout << "\nLista de Arestas:\n";
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = 0; k < matrizAdj[i][j]; k++) {
                cout << indiceParaNome[i] << " - " << indiceParaNome[j] << endl;
            }
        }
    }
}

void Grafo::calcularGraus() const {
    cout << "\nGrau de cada vertice:\n";
    for (int i = 0; i < n; i++) {
        int grau = 0;
        for (int j = 0; j < n; j++) {
            grau += matrizAdj[i][j];
        }
        cout << "Vertice " << indiceParaNome[i] << ": grau " << grau << endl;
    }
}

bool Grafo::ehSimples() const {
    for (int i = 0; i < n; i++) {
        if (matrizAdj[i][i] != 0) return false;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && matrizAdj[i][j] > 1) return false;
        }
    }
    return true;
}

bool Grafo::ehPseudografo() const {
    for (int i = 0; i < n; i++) {
        if (matrizAdj[i][i] != 0) return true;
    }
    return false;
}

bool Grafo::ehMultigrafo() const {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && matrizAdj[i][j] > 1) return true;
        }
    }
    return false;
}

bool Grafo::ehCompleto() const {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && matrizAdj[i][j] == 0) return false;
        }
    }
    return true;
}

bool Grafo::ehConexo() const {
    vector<bool> visitado(n, false);
    queue<int> fila;

    fila.push(0);
    visitado[0] = true;

    while (!fila.empty()) {
        int v = fila.front();
        fila.pop();

        for (int i = 0; i < n; i++) {
            if (matrizAdj[v][i] > 0 && !visitado[i]) {
                visitado[i] = true;
                fila.push(i);
            }
        }
    }

    for (bool v : visitado) {
        if (!v) return false;
    }
    return true;
}

void Grafo::densoOuEsparso() const {
    int maxArestas = n * (n - 1) / 2;
    double densidade = (double)m / maxArestas;

    cout << "\nAnalise de Densidade:\n";
    cout << "Densidade: " << (densidade * 100) << "%\n";
    if (densidade > 0.5) {
        cout << "O grafo eh DENSO.\n";
    } else {
        cout << "O grafo eh ESPARSO.\n";
    }
}

void Grafo::propriedades() const {
    cout << "\nPropriedades do Grafo:\n";

    if (ehSimples()) {
        cout << "- Eh um grafo simples\n";
    } else if (ehPseudografo()) {
        cout << "- Eh um pseudografo\n";
    } else if (ehMultigrafo()) {
        cout << "- Eh um multigrafo\n";
    }

    if (ehCompleto()) {
        cout << "- Eh um grafo completo\n";
    } else {
        cout << "- Nao eh um grafo completo\n";
    }

    if (ehConexo()) {
        cout << "- Eh um grafo conexo\n";
    } else {
        cout << "- Eh um grafo desconexo\n";
    }

    densoOuEsparso();
}
