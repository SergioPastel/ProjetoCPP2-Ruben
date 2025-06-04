#pragma once

#include "Produto.h"
#include <vector> // Usaremos essa biblioteca para fazer o nosso vetor dinamico

using namespace std;

class Estoque // Essa classe vai ser responsavel pelo nosso vetor de produtos. Vai se encarregar de fazer alterações ao estoque
{
	private: 
		vector<Produto> Produtos;		
	public:
		// Metodos		
		void mostrarEstoque();
		void checarProdutoEstoque(int, Produto*&);
		void removerProduto();
		void adicionarProduto();
};

