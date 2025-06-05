#pragma once

#include <string>

using namespace std;

class Produto
{
	private: // Atributos
		int id;
		string nome;
		int quantidade;
		float precoCusto;
	public: 
		// Construtores
		Produto();
		Produto(int, string, int, float);

		// Metodos
		void setId(int);
		int getId() const;
		void setNome(string);
		string getNome() const;
		void setQuantidade(int);
		int getQuantidade() const;
		void setPreco(float);
		float getPreco() const;

		string imprimirDados();
};

