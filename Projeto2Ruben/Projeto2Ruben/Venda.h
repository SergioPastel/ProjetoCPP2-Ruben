#pragma once
#include "Common.h"
#include "Produto.h"
#include "Cliente.h"
#include <vector>
#include <ctime>

using namespace std;

// class LinhaVenda � respons�vel por representar uma linha de venda no tal�o, contendo informa��es sobre o produto vendido, quantidade, pre�o e IVA.
class LinhaVenda {
private:
    int numeroLinha;         // N�mero incremental da linha no tal�o
    Produto produto;         // Produto vendido
    int quantidade;          // Quantidade vendida
    double precoSemIVA;      // Pre�o unit�rio sem IVA
    double iva;              // Valor do IVA
    double totalComIVA;      // Total da linha com IVA

public:
    LinhaVenda(int numeroLinha, const Produto& produto, int quantidade, double precoSemIVA, double iva, double totalComIVA);

    int getNumeroLinha() const;
    Produto getProduto() const;
    int getQuantidade() const;
    double getPrecoSemIVA() const;
    double getIVA() const;
    double getTotalComIVA() const;
};

class Venda {
private:
    int idVenda;                         // N�mero da fatura
    Cliente cliente;                     // Cliente associado � venda
    vector<LinhaVenda> linhas;           // Linhas da venda (produtos)
    double valorEntregue;                // Valor entregue pelo cliente
    double troco;                        // Troco a devolver
    time_t dataVenda;                    // Data da venda
    static int proximoId;                // Para gerar IDs autom�ticos

public:
    // Construtores
    Venda();
    Venda(const Cliente& cliente);

    // M�todos para adicionar produtos � venda
    void adicionarProduto(const Produto& produto, int quantidade);

    // M�todos de checkout e pagamento
    void checkout(double valorEntregue);

    // Getters
    int getIdVenda() const;
    Cliente getCliente() const;
    void setCliente(const Cliente& cliente);
    vector<LinhaVenda> getLinhas() const;
    double getValorEntregue() const;
    double getTroco() const;
    time_t getDataVenda() const;
    double getTotalVenda() const;

    // Impress�o do tal�o
    void imprimirTalao() const;
};
