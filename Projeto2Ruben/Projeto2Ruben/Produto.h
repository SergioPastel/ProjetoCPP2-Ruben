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

		// Metodos
		void setId(int);
		int getId();
		void setNome(string);
		string getNome();
		void setQuantidade(int);
		int getQuantidade();
		void setPreco(float);
		float getPreco();
};

