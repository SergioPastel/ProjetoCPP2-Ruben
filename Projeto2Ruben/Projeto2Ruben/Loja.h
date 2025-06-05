#pragma once

#include "Produto.h"
#include "Common.h"

using namespace std;

class Loja // Essa classe vai ser responsavel pelo nosso vetor de produtos. Vai se encarregar de fazer alterações ao estoque
{
	private: 
		vector<Produto> Produtos;		
	public:
		// Construtores
		Loja();
		// Metodos		
		void mostrarEstoque();
		void checarProdutoEstoque(int, Produto*&);
		void removerProduto();
		void adicionarProduto();
};

