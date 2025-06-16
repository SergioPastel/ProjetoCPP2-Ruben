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

	Cliente* selecionarCliente(); // Retorna ponteiro para cliente selecionado
	void checarCliente(int, Cliente*&);
	void mostrarClientes(); 
	void alterarCliente(int);
	void adicionarCliente();
	void removerCliente(int);

	void efetuarVenda(); // Processo completo de venda
	void adicionarVenda(const Venda& venda); // Adiciona venda ao vetor circular
};
