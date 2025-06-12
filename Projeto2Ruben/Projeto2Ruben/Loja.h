// O erro ocorre porque a classe Cliente n�o foi inclu�da neste arquivo de cabe�alho.
// Para corrigir, adicione #include "Cliente.h" no in�cio do arquivo Loja.h.

#pragma once

#include "Produto.h"
#include "Cliente.h" 
#include "Venda.h"
#include "Common.h"

using namespace std;

class Loja
{
	private: 
		vector<Produto> Produtos;	
		vector<Cliente> Clientes; // Vetor de clientes.
		vector<Venda> Vendas;
		int vendaIndex = 0; // Para controlar a posi��o de escrita circular no vetor de vendas

	public:
		// Construtores
		Loja();

		// Metodos		
		void mostrarEstoque();
		void checarProdutoEstoque(int, Produto*&);
		void removerProduto();
		void adicionarProduto();

		void efetuarVenda(); // Processo completo de venda
		void mostrarClientes(); // Para selecionar cliente na venda
		Cliente* selecionarCliente(); // Retorna ponteiro para cliente selecionado
		void adicionarVenda(const Venda& venda); // Adiciona venda ao vetor circular
};
