#include "Produto.h"

Produto::Produto()
{
}

void Produto::setId(int)
{
}

int Produto::getId() const
{
	return 0;
}

void Produto::setNome(string)
{
}

string Produto::getNome() const
{
	return string();
}

void Produto::setQuantidade(int)
{
}

int Produto::getQuantidade() const
{
	return 0;
}

void Produto::setPreco(float)
{
}

float Produto::getPreco() const
{
	return 0.0f;
}

string Produto::imprimirDados() {
	string pImpresso = "ID: " + to_string(this->getId()) + " | NOME: " + this->getNome() + " | Quantidade: " + to_string(this->getQuantidade()) + " | Pre�o: " + to_string(this->getPreco());
	return pImpresso;
}
