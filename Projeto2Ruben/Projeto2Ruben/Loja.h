#pragma once

#include "Produto.h"
#include "Cliente.h"
#include "Venda.h" // Certifique-se de incluir o cabeçalho correto
#include "Common.h"
class Venda;
using namespace std;

class Loja
{
private:
	vector<Produto> Produtos;
	vector<Cliente> Clientes; // Vetor de clientes.
	vector<Venda> Vendas; // Vetor de vendas.
	int vendaIndex = 0; // Para controlar a posição de escrita circular no vetor de vendas

public:
	// Construtores
	Loja();

	// Métodos		
	void mostrarEstoque();
	void checarProdutoEstoque(int, Produto*&);
	void removerProduto();
	void adicionarProduto();

	void efetuarVenda(); // Processo completo de venda
	void mostrarClientes(); // Para selecionar cliente na venda
	Cliente* selecionarCliente(); // Retorna ponteiro para cliente selecionado
	void adicionarVenda(const Venda& venda); // Adiciona venda ao vetor circular
};
