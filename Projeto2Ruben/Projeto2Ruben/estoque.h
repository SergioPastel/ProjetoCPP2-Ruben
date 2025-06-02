#pragma once

#include "Produto.h"
#include <vector> // Usaremos essa biblioteca para fazer o nosso vetor dinamico

using namespace std;

class estoque // Essa classe vai ser responsavel pelo nosso vetor de produtos. Vai se encarregar de fazer alterações ao estoque
{
	private: 
		vector<Produto> Produtos;
		int qtdeStock = Produtos.size(); // Usaremos isso para fazer IDs automaticos
	public:
		//
};

