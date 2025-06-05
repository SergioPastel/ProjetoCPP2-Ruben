// O erro ocorre porque a classe Cliente não foi incluída neste arquivo de cabeçalho.
// Para corrigir, adicione #include "Cliente.h" no início do arquivo Loja.h.

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
		int vendaIndex = 0; // Para controlar a posição de escrita circular no vetor de vendas

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
