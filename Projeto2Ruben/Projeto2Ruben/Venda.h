#pragma once
#include "Common.h"
#include "Produto.h"
#include "Cliente.h"
#include <vector>
#include <ctime>

using namespace std;

// class LinhaVenda é responsável por representar uma linha de venda no talão, contendo informações sobre o produto vendido, quantidade, preço e IVA.
class LinhaVenda {
private:
    int numeroLinha;         // Número incremental da linha no talão
    Produto produto;         // Produto vendido
    int quantidade;          // Quantidade vendida
    double precoSemIVA;      // Preço unitário sem IVA
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
    int idVenda;                         // Número da fatura
    Cliente cliente;                     // Cliente associado à venda
    vector<LinhaVenda> linhas;           // Linhas da venda (produtos)
    double valorEntregue;                // Valor entregue pelo cliente
    double troco;                        // Troco a devolver
    time_t dataVenda;                    // Data da venda
    static int proximoId;                // Para gerar IDs automáticos

public:
    // Construtores
    Venda();
    Venda(const Cliente& cliente);

    // Métodos para adicionar produtos à venda
    void adicionarProduto(const Produto& produto, int quantidade);

    // Métodos de checkout e pagamento
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

    // Impressão do talão
    void imprimirTalao() const;
};
