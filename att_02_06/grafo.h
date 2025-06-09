#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <vector>

class Grafo {
private:
    int n; // número de vértices
    int m; // número de arestas
    std::vector<std::vector<int>> matrizAdj;
    std::vector<std::string> indiceParaNome;

public:
    Grafo(const std::string& nomeArquivo);

    void imprimirMatriz() const;
    void imprimirArestas() const;
    void calcularGraus() const;

    bool ehSimples() const;
    bool ehPseudografo() const;
    bool ehMultigrafo() const;
    bool ehCompleto() const;
    bool ehConexo() const;

    void densoOuEsparso() const;
    void propriedades() const;
};

#endif
