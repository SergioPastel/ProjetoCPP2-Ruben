#include "Produto.h"

Produto::Produto()
{
}

Produto::Produto(int id, string nome, int qtde, float preco)
{
	this->id = id;
	this->nome = nome;
	this->quantidade = qtde;
	this->precoCusto = preco;
}

void Produto::setId(int id)
{
	this->id = id;
}

int Produto::getId() const
{
	return this->id;
}

void Produto::setNome(string nome)
{
	this->nome = nome;
}

string Produto::getNome() const
{
	return this->nome;
}

void Produto::setQuantidade(int qtde)
{
	this->quantidade = qtde;
}

int Produto::getQuantidade() const
{
	return this->quantidade;
}

void Produto::setPreco(float preco)
{
	this->precoCusto = preco;
}

float Produto::getPreco() const
{
	return this->precoCusto;
}

string Produto::imprimirDados() {
	string pImpresso = "ID: " + to_string(this->getId()) + " | NOME: " + this->getNome() + " | Quantidade: " + to_string(this->getQuantidade()) + " | Preço: " + to_string(this->getPreco());
	return pImpresso;
}
