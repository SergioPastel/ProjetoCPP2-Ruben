#include "Cliente.h"
#include "Common.h"

Cliente::Cliente()
{// Construtor padrão, inicializa os atributos com valores padrão
	this->id = 0;
	this->nome = "";
	this->telefone = 0;
	this->morada = "";
}

Cliente::Cliente(int id, string nome, double telefone, string morada)
{
	this->id = id;
	this->nome = nome;
	this->telefone = telefone;
	this->morada = morada;
}

void Cliente::setId(int id)
{
	this->id = id;
}

int Cliente::getId() const
{
	return id;
}

void Cliente::setNome(string nome)
{
	this->nome = nome;
}

string Cliente::getNome() const
{
	return nome;
}

void Cliente::setTelefone(double telefone)
{
	this->telefone = telefone;
}

double Cliente::getTelefone() const
{
	return telefone;
}

void Cliente::setMorada(string morada)
{
	this->morada = morada;
}

string Cliente::getMorada() const
{
	return morada;
}

void Cliente::imprimirDados() const
{
	cout << "ID: " << id << endl;
	cout << "Nome: " << nome << endl;
	cout << "Telefone: " << telefone << endl;
	cout << "Morada: " << morada << endl;
}
