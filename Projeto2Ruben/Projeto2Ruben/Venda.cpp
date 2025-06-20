#include "Venda.h"
#include "Common.h"
#pragma warning(disable : 4996) // Necessario pra não ocorrer erro de segurança com o CTIME

using namespace std;
int Venda::proximoId = 1;

LinhaVenda::LinhaVenda(int numeroLinha, const Produto& produto, int quantidade, double precoSemIVA, double iva, double totalComIVA)
{
	this->numeroLinha = numeroLinha;
	this->produto = produto;
	this->quantidade = quantidade;
	this->precoSemIVA = precoSemIVA;
	this->iva = iva;
	this->totalComIVA = totalComIVA;
}

int LinhaVenda::getNumeroLinha() const
{
	return this->numeroLinha;
}

Produto LinhaVenda::getProduto() const
{
	return this->produto;
}

int LinhaVenda::getQuantidade() const
{
	return this->quantidade;
}

double LinhaVenda::getPrecoSemIVA() const
{
	return this->precoSemIVA;
}

double LinhaVenda::getIVA() const
{
	return this->iva;
}

double LinhaVenda::getTotalComIVA() const
{
	return this->totalComIVA;
}
;

Venda::Venda()
{
	this->idVenda = this->proximoId++;
	this->valorEntregue = 0.0;
	this->troco = 0.0;
	this->dataVenda = time(0);
}

Venda::Venda(const Cliente& cliente)
{
	this->idVenda = this->proximoId++;
	this->cliente = cliente;
	this->valorEntregue = 0.0;
	this->troco = 0.0;
	this->dataVenda = time(0);
}

void Venda::adicionarProduto(const Produto& produto, int quantidade)
{
	double precoUnitario = produto.getPreco() * 1.3; // 30% acima do custo
	double precoSemIVA = precoUnitario * quantidade;
	double iva = precoSemIVA * 0.23; // IVA de 23%
	double totalComIVA = precoSemIVA + iva;
	int numeroLinha = static_cast<int>(this->linhas.size()) + 1;
	LinhaVenda linha(numeroLinha, produto, quantidade, precoSemIVA, iva, totalComIVA);
	this->linhas.push_back(linha);
}



void Venda::checkout(double valorEntregue)
{
	if (vendaSorteada)
	{
		this->valorEntregue = 0;
		this->troco = 0;
		cout << "Parabéns! Sua venda foi sorteada e você não precisa pagar nada!" << endl;
	}
	else
	{
		this->valorEntregue = valorEntregue;
		double total = getTotalVenda();
		this->troco = this->valorEntregue - total;
	}
	this->dataVenda = time(0); // Atualiza data da venda
}


void Venda::setVendaSorteada(bool sorteada)
{
	this->vendaSorteada = sorteada;
}

int Venda::getIdVenda() const
{
	return this->idVenda;
}

Cliente Venda::getCliente() const
{
	return this->cliente;
}

void Venda::setCliente(const Cliente& cliente) {
	this->cliente = cliente;
}

vector<LinhaVenda> Venda::getLinhas() const
{
	return this->linhas;
}

double Venda::getValorEntregue() const
{
	return this->valorEntregue;
}

double Venda::getTroco() const
{
	return this->troco;
}

time_t Venda::getDataVenda() const
{
	return this->dataVenda;
}

double Venda::getTotalVenda() const
{
	double total = 0.0;
	for (auto linha : this->linhas) {
		total += linha.getTotalComIVA();
	}
	return total;
}

void Venda::imprimirTalao() const
{
	std::cout << "\033[47m\033[30m"; // Fundo branco, texto preto

	cout << "------------------- TALAO DE COMPRA -------------------" << endl;
	cout << "Fatura N.: " << this->idVenda << " | Data: " << ctime(&this->dataVenda);
	cout << "Cliente N.: " << this->getCliente().getId() << " | Nome: " << this->getCliente().getNome() << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << left << setw(5) << "N." << setw(20) << "Produto" << setw(10) << "Qtd"
		<< setw(12) << "Preco s/IVA" << setw(10) << "IVA" << setw(12) << "Total c/IVA" << endl;
	for (const auto& linha : this->linhas) {
		cout << left << setw(5) << linha.getNumeroLinha()
			<< setw(20) << linha.getProduto().getNome()
			<< setw(10) << linha.getQuantidade()
			<< setw(12) << fixed << setprecision(2) << linha.getPrecoSemIVA()
			<< setw(10) << linha.getIVA()
			<< setw(12) << linha.getTotalComIVA() << endl;
	}
	cout << "-------------------------------------------------------" << endl;
	cout << "Total: " << this->getTotalVenda() << " EUR" << endl;

	if (vendaSorteada) {
		cout << "VENDA SORTEADA: GRATUITA!" << endl;
	}
	else {
		cout << "Valor entregue: " << this->valorEntregue << " EUR" << endl;
		cout << "Troco: " << this->troco << " EUR" << endl;
	}

	cout << "-------------------------------------------------------" << endl;

	std::cout << "\033[0m"; // Reset para as cores padrão
}

