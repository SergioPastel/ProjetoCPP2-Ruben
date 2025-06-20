#include "Cliente.h"
#include "Common.h"

Cliente::Cliente()
{// Construtor padr�o, inicializa os atributos com valores padr�o
	this->id = 0;
	this->nome = "";
	this->telefone = 0;
	this->morada = "";
}

Cliente::Cliente(int id, string nome, int telefone, string morada)
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

void Cliente::setTelefone(int telefone)
{
	this->telefone = telefone;
}

int Cliente::getTelefone() const
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
	cout << "ID: " << id << " | " << "Nome: " << nome << " | " << "Telefone: " << telefone << " | " << "Morada: " << morada << endl;
}
