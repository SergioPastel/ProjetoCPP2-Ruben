#include "Venda.h"
#include "Common.h"
#pragma warning(disable : 4996) // Necessario pra não ocorrer erro de segurança com o CTIME

using namespace std;

int Venda::proximoId = 1; // Inicializa o ID da primeira venda em 1

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

Venda::Venda()
{
	this->idVenda = this->proximoId++; // Aumenta o ID da venda
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
		double trocoBruto = std::max(0.0, this->valorEntregue - total); // Calcula o troco bruto, garantindo que não seja negativo
		this->troco = round(trocoBruto * 100.0) / 100.0; // Arredonda o troco para duas casas decimais
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
    system("cls");
    const int largura = 80;

    std::cout << "\033[47m\033[30m"; // Fundo branco, texto preto

	auto linhaBranca = [](int largura) { // Função para imprimir uma linha em branco
        std::cout << std::setfill(' ') << std::setw(largura) << " " << std::endl;
        };

    linhaBranca(largura);    
    cout << left << setw(largura) << setfill(' ') << "------------------------------- TALAO DE COMPRA --------------------------------" << endl;    

    // Linha da fatura e data/hora
    {
		ostringstream oss; // Usando o std::ostringstream para formatar a string
        string dataStr = ctime(&this->dataVenda);
        if (!dataStr.empty() && dataStr.back() == '\n') dataStr.pop_back(); // Remove o \n do ctime
        oss << "Fatura N.: " << this->idVenda << " | Data: " << dataStr;
        string linha = oss.str();
        if (linha.length() > largura) linha = linha.substr(0, largura); // Trunca se passar
        cout << left << setw(largura) << setfill(' ') << linha << endl;
    }

    // Linha do cliente e nome
    {
        std::ostringstream oss;
        oss << "Cliente N.: " << this->getCliente().getId() << " | Nome: " << this->getCliente().getNome();
        std::string linha = oss.str();
        if (linha.length() > largura) linha = linha.substr(0, largura); // Trunca se passar
        cout << left << setw(largura) << setfill(' ') << linha << endl;
    }

    cout << left << setw(largura) << setfill(' ') << "--------------------------------------------------------------------------------" << endl;
    {
        std::ostringstream oss;
        oss << left << setw(5) << "N."
            << setw(22) << "Produto"
            << right << setw(7) << "Qtd"
            << right << setw(15) << "Preco s/IVA"
            << right << setw(12) << "IVA"
            << right << setw(15) << "Total c/IVA";
        cout << left << setw(largura) << setfill(' ') << oss.str() << endl;
    }
    cout << left << setw(largura) << setfill(' ') << "--------------------------------------------------------------------------------" << endl;

    for (const auto& linha : this->linhas) {
        std::ostringstream oss;
        oss << left << setw(5) << linha.getNumeroLinha()
            << setw(22) << linha.getProduto().getNome()
            << right << setw(7) << linha.getQuantidade()
            << right << setw(15) << fixed << setprecision(2) << linha.getPrecoSemIVA()
            << right << setw(12) << linha.getIVA()
            << right << setw(15) << linha.getTotalComIVA();
        cout << left << setw(largura) << setfill(' ') << oss.str() << endl;
    }
    cout << left << setw(largura) << setfill(' ') << "--------------------------------------------------------------------------------" << endl;

    {
        std::ostringstream oss;
        oss << right << setw(largura - 20) << "Total: " << setw(12) << fixed << setprecision(2) << this->getTotalVenda() << " EUR";
        cout << left << setw(largura) << setfill(' ') << oss.str() << endl;
    }

    if (vendaSorteada) {
        std::ostringstream oss;
        oss << right << setw(largura - 20) << "VENDA SORTEADA: GRATUITA!";
        cout << left << setw(largura) << setfill(' ') << oss.str() << endl;
    }
    else {
        {
            std::ostringstream oss;
            oss << right << setw(largura - 20) << "Valor entregue: " << setw(12) << this->valorEntregue << " EUR";
            cout << left << setw(largura) << setfill(' ') << oss.str() << endl;
        }
        {
            std::ostringstream oss;
            oss << right << setw(largura - 20) << "Troco: " << fixed << setprecision(2) << setw(12) << this->troco << " EUR";
            cout << left << setw(largura) << setfill(' ') << oss.str() << endl;
        }
    }

    cout << left << setw(largura) << setfill(' ') << "--------------------------------------------------------------------------------" << endl;
    linhaBranca(largura);

    std::cout << "\033[0m"; // Reset para as cores padrão
}