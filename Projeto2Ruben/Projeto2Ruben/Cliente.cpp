#include "Cliente.h"
#include "Common.h"

Cliente::Cliente()
{// Construtor padrão, inicializa os atributos com valores padrão
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
	cout << left<<setw(4)  << "ID: " << this->getId() << " | "
		<< "Nome: " << setw(20) << this->getNome() << " | "
		<< setw(9) << "Telefone: " << setw(9) << this->getTelefone() << " | "
		<< "Morada: " << this->getMorada() << endl;
}
