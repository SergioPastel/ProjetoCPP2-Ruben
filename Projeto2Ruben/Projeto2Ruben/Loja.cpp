#include "Loja.h"
#include "Common.h"
#include "Venda.h"
#include "Produto.h"
#include "Cliente.h"
#include "Validacoes.h"
#include "Funcoes.h"
#include <map>

#define RESET   "\033[0m" // Reseta a cor para o padrão.
#define RED     "\033[31m" // Define a cor vermelha.
#define GREEN   "\033[32m" // Define a cor verde.
#define CYAN    "\033[36m" // Define a cor ciano.

void Loja::logotipo() // O Logotipo está aqui pois poderiamos hipoteticamente ter mais de uma loja
{ cout << GREEN << R"(
                                                          
    ####    #####   #####     ####      ####    #####              ##     ##   ##   ####    ##   ##    ##     ####
   ##  ##  ##   ##   ## ##     ##      ##  ##  ##   ##            ####    ###  ##    ##     ### ###   ####     ##
  ##       ##   ##   ##  ##    ##     ##       ##   ##           ##  ##   #### ##    ##     #######  ##  ##    ##
  ##       ##   ##   ##  ##    ##     ##       ##   ##           ##  ##   ## ####    ##     #######  ##  ##    ##
  ##       ##   ##   ##  ##    ##     ##  ###  ##   ##           ######   ##  ###    ##     ## # ##  ######    ##   #
   ##  ##  ##   ##   ## ##     ##      ##  ##  ##   ##           ##  ##   ##   ##    ##     ##   ##  ##  ##    ##  ##
    ####    #####   #####     ####      #####   #####            ##  ##   ##   ##   ####    ##   ##  ##  ##   #######

)" << RESET << endl;

}

	
Loja::Loja() {
    this->Produtos.emplace_back(1, "Coleira", 20, 10.00);
    this->Produtos.emplace_back(2, "Racao Premium", 15, 20.90);
    this->Produtos.emplace_back(3, "Caminha king size", 30, 18.50);
    this->Produtos.emplace_back(4, "Areia Higienica", 25, 8.99);
    this->Produtos.emplace_back(5, "Shampoo Pet", 18, 9.75);
    this->Produtos.emplace_back(6, "Caminha Pequena", 10, 12.00);
    this->Produtos.emplace_back(7, "Comedouro Inox", 22, 6.80);
    this->Produtos.emplace_back(8, "Antipulgas", 12, 60.90);
    this->Produtos.emplace_back(9, "Arranhador para Gatos", 8, 50.90);
    this->Produtos.emplace_back(10, "Biscoito Canino", 40, 9.99);

    Clientes.push_back(Cliente(1, "João Silva", 912345678, "Rua A, 123"));
    Clientes.push_back(Cliente(2, "Maria Santos", 934567890, "Av. B, 456"));
    Clientes.push_back(Cliente(3, "Carlos Costa", 965432187, "Praça C, 789"));
}

//funcao mostrar estoque
void Loja::mostrarEstoque() {
	logotipo();
    cout << endl;
    cout << "------------------------------ ESTOQUE ATUAL ------------------------------" << endl;
    cout << left << setw(5) << "ID" << "| "
        << left << setw(30) << "Nome do Produto" << "| "
        << left << setw(6) << "Qtd." << "| "
        << right << setw(18) << "Preco Custo (EUR)" << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    bool estoqueVazioOuZerado = true;
    for (const Produto& p : Produtos) {
        if (p.getQuantidade() > 0) {
            cout << left << setw(5) << p.getId() << "| "
                << left << setw(30) << p.getNome() << "| "
                << left << setw(6) << p.getQuantidade() << "| "
                << right << setw(15) << fixed << setprecision(2) << p.getPreco() << " EUR" << endl;
            estoqueVazioOuZerado = false;
        }
    }
    if (estoqueVazioOuZerado) {
        cout << "O estoque está vazio ou todos os produtos têm quantidade 0." << endl;
    }
    cout << "---------------------------------------------------------------------------" << endl;
}

void Loja::mostrarEstoqueComPrecoVenda() {
    cout << endl;
    cout << "------------------------------ ESTOQUE ATUAL ------------------------------" << endl;
    cout << left << setw(5) << "ID" << "| "
        << left << setw(30) << "Nome do Produto" << "| "
        << left << setw(6) << "Qtd." << "| "
        << right << setw(18) << "Preco Venda (EUR)" << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    bool estoqueVazio = true;
    for (const Produto& p : this->Produtos) {
        double precoVenda = p.getPreco() * 1.3;
        cout << left << setw(5) << p.getId() << "| "
            << left << setw(30) << p.getNome() << "| "
            << left << setw(6) << p.getQuantidade() << "| "
            << right << setw(15) << fixed << setprecision(2) << precoVenda << " EUR" << endl;
        estoqueVazio = false;
    }
    if (estoqueVazio) {
        cout << "O estoque está vazio." << endl;
    }
    cout << "---------------------------------------------------------------------------" << endl;
}


//função para verificar se o produto escolhido tem no estoque.
void Loja::checarProdutoEstoque(int idProduto, Produto*& produtoSelecionado) {
    //percorre o estoque e se encontrar o produto no estoque, guarda o vetor no ponteiro.
    int tamanho = Produtos.size(); // Pra não dar erro no VS code
    produtoSelecionado = nullptr; // Inicia o ponteiro a nullo, para não haver lixo
    for (int i = 0; i < tamanho; i++) {
        if (Produtos[i].getId() == idProduto) {
            produtoSelecionado = &Produtos[i];
            break;
        }
    }
}

void Loja::removerProduto() {
    int idProduto;
    string input; // Necessario para receber a linha
    char continuar; // Necessario para receber a opção e não encher o buffer

    system("cls");
    this->mostrarEstoque();

    idProduto = Validacoes::validacaoInt("Insira o ID do produto: ");

    Produto* produtoSelecionado = nullptr; // Inicialmente não sabemos se o ID/Produto que o utilizador vai inserir existe, ent�o inicializamos um ponteiro nulo que é atualizado
    checarProdutoEstoque(idProduto, produtoSelecionado);

    // Verifica se o produto existe
    if (produtoSelecionado == nullptr) {
        cout << "Produto com ID " << idProduto << " não encontrado.\n";
    }
    else if (produtoSelecionado->getQuantidade() == 0) { // Se o produto existe, mas não está mais em estoque
        cout << "Este produto ja nao esta em estoque.";
    }
    else { // O produto existe e está em estoque
        do { // Garante que o usuario escreveu o nome certo e quer prosseguir
            system("cls");
            cout << "Produto selecionado - ID: " << produtoSelecionado->getId() << " | Nome: " << produtoSelecionado->getNome() << " | Quantidade: " << produtoSelecionado->getQuantidade() << " | Custo: " << produtoSelecionado->getPreco() << "\nDeseja remover do estoque? (Y/N): ";
            getline(cin, input);
            continuar = input[0];
        } while (continuar != 'y' && continuar != 'n' && continuar != 'Y' && continuar != 'N');

        if (continuar == 'n' || continuar == 'N') { // Se o usuario não quiser prosseguir, retorne a função anterior
            return;
        }

        produtoSelecionado->setQuantidade(0);
        cout << "Produto removido.\n";
    }

    _getch();
}

void Loja::adicionarProduto() {

    string nome;
    int valorAdd;
    bool existe = false; // Flag inspeciona se o artigo ja existe

    system("cls");
    mostrarEstoque();

    cout << "Insira o nome do novo artigo: ";
    // cin.ignore();
    getline(cin, nome); // Le a linha inteira, permitindo espacos nos nomes 

    int tamanho = Loja::Produtos.size(); // Pra não dar erro no VS code

    for (int i = 0; i < tamanho; i++) {
        if (Funcoes::toMinuscula(Produtos[i].getNome()) == Funcoes::toMinuscula(nome)) {  // Compara o nome do produto com cada item do estoque. Se encontrar um igual, deixa de adicionar e comea a alterar o produto existente
            string input; // Necessario para receber a linha
            char opt; // Necessario para receber a opção sem encher o buffer

            cout << "PRODUTO - " << Produtos[i].imprimirDados();
            while (true) {
                cout << endl; // Adiciona uma quebra de linha antes da mensagem
                valorAdd = Validacoes::validacaoInt("Adicione ao stock (valor >= 0): "); // Altera a mensagem para o usuário
                if (valorAdd >= 0) {
                    break;
                }
                else {
                    cout << "Quantidade inválida. Por favor, insira um valor maior ou igual a zero.\n";
                }
            }
            Produtos[i].setQuantidade(Produtos[i].getQuantidade() + valorAdd);
            do { // Pergunta se o user quer atualizar o preço
                cout << "Deseja atualizar o preço?(Y/N) ";
                getline(cin, input);
                opt = input[0];
            } while (opt != 'y' && opt != 'n' && opt != 'Y' && opt != 'N');

            if (opt == 'y' || opt == 'Y') {
                Produtos[i].setPreco(Validacoes::obterFloat("Insira o novo preço: "));
            }

            cout << "Artigo atualizado.";
            existe = true;
            break;
        }
    }
    if (existe == false) {
        string input; // Necessario para receber a linha
        char continuar; // Necessario para receber a opção e não encher o buffer

        do { // Garante que o usuario escreveu o nome certo e quer prosseguir
            cout << "Nome inserido: " << nome << ". Deseja continuar? (Y/N): ";
            getline(cin, input);
            continuar = input[0];
        } while (continuar != 'y' && continuar != 'n' && continuar != 'Y' && continuar != 'N');

        if (continuar == 'n' || continuar == 'N') // Se o usuario não quiser prosseguir, retorne a função anterior
            return;

        Produto p; // Novo produto que iremos adicionar ao array no final

        p.setNome(nome); // O nome do produto e o nome que inserimos acima
        p.setId(Produtos.size() + 1); // Id atribuido e um a mais do que o tamanho do estoque, que seria o ultimo id por default

        cout << "Nome do Produto: " << nome << endl;
        p.setPreco(Validacoes::obterFloat("Insira o custo: "));
        while (p.getPreco() <= 0) // Enquanto o user tentar dar valor 0 ou negativo, fica pedindo por novo valor
            p.setPreco(Validacoes::obterFloat("Custo invalido. Insira um valor maior que 0: "));

        p.setQuantidade(Validacoes::validacaoInt("Insira a quantidade: "));
        while (p.getQuantidade() <= 0) // Enquanto o user tentar dar valor 0 ou negativo, fica pedindo por novo valor
            p.setQuantidade(Validacoes::validacaoInt("Quantidade invalida. Insira um valor maior que 0: "));

        // Adiciona ao vetor e aumenta o tamanho do estoque para que mais adicoes sejam possiveis
        Produtos.push_back(p);

        cout << "Artigo adicionado.";
    }
    _getch();
}

Cliente* Loja::selecionarCliente()
{
    mostrarClientes();
    Cliente* cliente = nullptr;
    int idCliente = Validacoes::validacaoInt("Insira o ID do cliente: ");

    checarCliente(idCliente, cliente);

    if (cliente != nullptr) {
        return cliente;
    }
    else {
        std::cout << "Cliente não encontrado!" << std::endl;
        return nullptr;
    }
}

void Loja::checarCliente(int idCliente, Cliente*& clienteSelecionado) {
    // Percorre a lista de clientes e, se encontrar o cliente com o ID, guarda o ponteiro.
    int tamanho = Clientes.size(); // Para evitar problemas de compilador
    clienteSelecionado = nullptr; // Inicializa como nulo
    for (int i = 0; i < tamanho; i++) {
        if (Clientes[i].getId() == idCliente) {
            clienteSelecionado = &Clientes[i];
            break;
        }
    }
}


void Loja::mostrarClientes()
{
    system("cls");
	logotipo();
	cout << endl;
    cout << "------------------- CLIENTES -------------------" << endl;
    for (const auto& c : Clientes) {
        c.imprimirDados();
    }
    cout << "------------------------------------------------" << endl;
}

void Loja::alterarCliente(int id) {
    Cliente* cliente = nullptr;
    bool alterado = false;
    string input;
    char opt;

    checarCliente(id, cliente);

    if (cliente != nullptr) {
        // Alteração de nome
        do {
            cout << "Deseja alterar o nome?(Y/N): ";
            getline(cin, input);
            opt = input[0];
        } while (opt != 'y' && opt != 'n' && opt != 'Y' && opt != 'N');
        
        if (opt == 'y' || opt == 'Y') {
            string novoNome;
            cout << "Digite o novo nome do cliente: ";
            getline(cin, novoNome);
            cliente->setNome(novoNome);
            alterado = true;
        }

        // Alteração de telefone
        do {
            cout << "Deseja alterar o numero de telefone?(Y/N): ";
            getline(cin, input);
            opt = input[0];
        } while (opt != 'y' && opt != 'n' && opt != 'Y' && opt != 'N');

        if (opt == 'y' || opt == 'Y') {
            int novoTel;  
            novoTel = Validacoes::validacaoInt("Digite o novo numero do cliente: ");
            cliente->setTelefone(novoTel);
            alterado = true;
        }

        // Alteração de morada
        do {
            cout << "Deseja alterar a morada?(Y/N): ";
            getline(cin, input);
            opt = input[0];
        } while (opt != 'y' && opt != 'n' && opt != 'Y' && opt != 'N');

        if (opt == 'y' || opt == 'Y') {
            string novaMorada;
            cout << "Digite a nova morada do cliente: ";
            getline(cin, novaMorada);
            cliente->setMorada(novaMorada);
            alterado = true;
        }

        if (alterado == true)
            cout << "Cliente atualizado com sucesso!\n";
        else
            cout << "O cliente não foi alterado.\n";
        _getch();
    }
    else {
        cout << "Cliente com ID " << id << " não existe.\n";
        _getch();
    }
}

void Loja::removerCliente(int id) {
    Cliente* cliente = nullptr;
    string input;
    char opt;

    checarCliente(id, cliente);

    if (id == 0) {
        return;
    }
    else if (cliente == nullptr) {
        cout << "Cliente com ID " << id << " não encontrado.\n";
        return;
    }
    else {
        // Confirmação de remoção
        do {
            cout << "Tem certeza que deseja remover o cliente '" << cliente->getNome() << "'? (Y/N): ";
            getline(cin, input);
            opt = input[0];
        } while (opt != 'y' && opt != 'n' && opt != 'Y' && opt != 'N');

        if (opt == 'n' || opt == 'N') {
            cout << "Remoção cancelada.\n";            
            return;
        }

        // Remove o cliente do vetor
        for (auto it = Clientes.begin(); it != Clientes.end(); ++it) {
            if (it->getId() == id) {
                Clientes.erase(it);
                cout << "Cliente removido com sucesso.\n";
                _getch();
                return;
            }
        }
        // Caso não encontre (deveria ter encontrado)
        cout << "Erro ao remover cliente.\n";
        _getch();
    }
}

void Loja::adicionarCliente() {
    int id = Clientes.back().getId() + 1;
    string nome;
    int telefone;
    string morada;

    system("cls");
    mostrarClientes();

    cout << "Insira o nome do novo cliente: ";
    getline(cin, nome); // Le a linha inteira, permitindo espacos nos nomes
    telefone = Validacoes::validacaoInt("Insira o numero de telefone: ");
    cout << "Insira a morada: ";
    getline(cin, morada);

    this->Clientes.emplace_back(id ,nome, telefone, morada);
}

void Loja::adicionarVenda(const Venda& venda)
{
    static int pos = 0; // Mantém a posição da próxima escrita (circular)
    if (Vendas.size() < 100) {
        Vendas.push_back(venda);
    }
    else {
        Vendas[pos] = venda;
    }
    pos = (pos + 1) % 100; // Avança circularmente
}

void Loja::relatorioEstoqueTotal() {
    int total = 0;
	system("cls");
	logotipo();
	cout << endl;
    cout << "---------------- RELATÓRIO DE ESTOQUE ----------------" << endl;
    for (const Produto& p : Produtos) {
        cout << "ID: " << p.getId() << " | Nome: " << p.getNome() << " | Quantidade: " << p.getQuantidade() << endl;
        total += p.getQuantidade();
    }
    cout << "------------------------------------------------------" << endl;
    cout << "Total de itens em estoque: " << total << endl;
}

void Loja::relatorioVendasPorProduto(const string& nomeProduto) {
    // Verifica se o produto existe na lista da loja
    bool produtoExiste = false;
    for (const Produto& p : Produtos) {
        if (Funcoes::toMinuscula(p.getNome()) == Funcoes::toMinuscula(nomeProduto)) {
            produtoExiste = true;
            break;
        }
    }

    if (!produtoExiste) {
        cout << "Erro: O produto " << nomeProduto << " não existe no sistema." << endl;
        return;
    }

    // Se o produto existe, prossegue com o relatório
    int quantidadeVendida = 0;
    double valorTotal = 0.0;
    bool encontrou = false;

    cout << "Relatório de vendas para o produto: " << nomeProduto << endl;

    for (size_t i = 0; i < Vendas.size(); ++i) {
        const Venda& venda = Vendas[i];

        for (const LinhaVenda& linha : venda.getLinhas()) {
            if (Funcoes::toMinuscula(linha.getProduto().getNome()) == Funcoes::toMinuscula(nomeProduto)) {
                int qtd = linha.getQuantidade();
                double totalLinha = linha.getTotalComIVA();

                cout << "\nVenda " << (i + 1)
                    << " - Cliente: " << venda.getCliente().getNome()
                    << " (ID: " << venda.getCliente().getId() << ")" << endl;

                cout << "  Quantidade: " << qtd
                    << ", Total com IVA: " << fixed << setprecision(2)
                    << totalLinha << " EUR" << endl;

                quantidadeVendida += qtd;
                valorTotal += totalLinha;
                encontrou = true;
                break;
            }
        }
    }

    if (!encontrou) {
        cout << "Nenhuma venda encontrada para esse produto." << endl;
        return;
    }

    cout << "\nResumo:" << endl;
    cout << "Quantidade total vendida: " << quantidadeVendida << endl;
    cout << "Valor total vendido (com IVA): " << fixed << setprecision(2) << valorTotal << " EUR" << endl;
}


void Loja::relatorioTotalVendas() {
    logotipo();
    cout << endl;
    if (Vendas.empty()) {
        cout << "---------------- RELATÓRIO DE VENDAS ----------------" << endl;
        cout << "Nenhuma venda foi realizada ainda." << endl;
        cout << "-----------------------------------------------------" << endl;
        return;
    }

    map<string, int> vendasPorProduto;
    map<string, double> lucroPorProduto;
    map<int, double> valorPorCliente;
    double totalVendas = 0.0;

    // Garantir que todos os produtos estejam registrados mesmo com 0 vendas
    for (const Produto& p : Produtos)
        vendasPorProduto[p.getNome()] = 0;

    for (const Venda& venda : Vendas) {
        totalVendas += venda.getTotalVenda();
        int idCliente = venda.getCliente().getId();
        valorPorCliente[idCliente] += venda.getTotalVenda();

        for (const LinhaVenda& linha : venda.getLinhas()) {
            string nome = linha.getProduto().getNome();
            vendasPorProduto[nome] += linha.getQuantidade();
            double precoCusto = linha.getProduto().getPreco();
            double precoVenda = precoCusto * 1.3;
            double lucro = (precoVenda - precoCusto) * linha.getQuantidade();
            lucroPorProduto[nome] += lucro;
        }
    }

    vector<string> maisVendidos, menosVendidos;
    int maxQtd = -1, minQtd = INT_MAX;

    for (const auto& par : vendasPorProduto) {
        if (par.second > maxQtd) {
            maxQtd = par.second;
            maisVendidos = { par.first };
        }
        else if (par.second == maxQtd) {
            maisVendidos.push_back(par.first);
        }

        if (par.second < minQtd) {
            minQtd = par.second;
            menosVendidos = { par.first };
        }
        else if (par.second == minQtd) {
            menosVendidos.push_back(par.first);
        }
    }

    int idClienteTop = -1;
    double maiorValor = 0.0;
    for (const auto& par : valorPorCliente) {
        if (par.second > maiorValor) {
            maiorValor = par.second;
            idClienteTop = par.first;
        }
    }

    cout << "---------------- RELATÓRIO DE VENDAS ----------------" << endl;
    cout << "Total de vendas (com IVA): " << fixed << setprecision(2) << totalVendas << " EUR" << endl;

    cout << "Produto(s) mais vendido(s): ";
    for (const string& nome : maisVendidos) cout << nome << " | ";
    cout << "(" << maxQtd << " unidades)" << endl;

    cout << "Produto(s) menos vendido(s): ";
    for (const string& nome : menosVendidos) cout << nome << " | ";
    cout << "(" << minQtd << " unidades)" << endl;

    cout << "Lucro dos produtos mais vendidos:" << endl;
    for (const string& nome : maisVendidos) {
        cout << "  " << nome << ": " << fixed << setprecision(2) << lucroPorProduto[nome] << " EUR" << endl;
    }


    if (idClienteTop != -1) {
        for (const Cliente& c : Clientes) {
            if (c.getId() == idClienteTop) {
                cout << "Cliente que mais comprou: " << c.getNome()
                    << " (ID: " << c.getId() << ") - " << maiorValor << " EUR" << endl;
                break;
            }
        }
    }
    else {
        cout << "Nenhum cliente realizou compras." << endl;
    }

    cout << "-----------------------------------------------------" << endl;
}


void Loja::efetuarVenda()
{
    string input;
    char opt;
    Cliente* cliente;

    system("cls");    

    Venda venda;

    // Seleção de produtos
    char adicionarMais;
    bool produtoAdicionado = false;

    logotipo();
    cout << "************ EFETUAR VENDA ************" << endl;
    mostrarEstoqueComPrecoVenda();
    do {
        // Escolhe um produto
        int idProduto = Validacoes::validacaoInt("Insira o ID do produto: ");
        Produto* produtoSelecionado = nullptr;
        checarProdutoEstoque(idProduto, produtoSelecionado);

        // Assegura-se de que o produto existe
        if (!produtoSelecionado || produtoSelecionado->getQuantidade() == 0) {
            cout << "Produto inválido ou sem estoque.\n";
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            // Checa se o produto já foi inserido na venda
            bool produtoJaExiste = false;
            for (auto const& linha : venda.getLinhas()) {
                if (linha.getProduto().getId() == produtoSelecionado->getId()) {
                    produtoJaExiste = true;
                    break;
                }
            }

            if (produtoJaExiste) {
                cout << "Este produto já foi inserido na venda!\n";
            }
            else {
                // Recebe a quantidade e adiciona o produto
                int quantidade = Validacoes::validacaoInt("Quantidade a comprar: ");
                if (quantidade > 0 && quantidade <= produtoSelecionado->getQuantidade()) {
                    venda.adicionarProduto(*produtoSelecionado, quantidade);
                    cout << "Produto adicionado à venda.\n";
                    produtoAdicionado = true;
                }
                else {
                    cout << "Quantidade inválida.\n";
                }
            }
        }

        do {
            cout << "Adicionar mais produtos? (Y/N): ";
            getline(cin, input);
            if (!input.empty()) {
                adicionarMais = toupper(input[0]);
            }
            else {
                adicionarMais = ' ';
            }
            if (adicionarMais != 'Y' && adicionarMais != 'N') {
                cout << "Opção inválida! Digite apenas Y ou N." << endl;
            }
        } while (adicionarMais != 'Y' && adicionarMais != 'N');

    } while (adicionarMais == 'y' || adicionarMais == 'Y');

    if (!produtoAdicionado)
    {
        cout << "Nenhum produto válido foi adicionado. Venda cancelada!" << endl;
        _getch();
        return;
    }

    // Selecionar cliente
    do {
        mostrarClientes();
        cout << "Deseja adicionar um novo cliente? (Y/N): ";
        getline(cin, input);
        opt = input[0];
    } while (opt != 'y' && opt != 'n' && opt != 'Y' && opt != 'N');

    if (opt == 'Y' || opt == 'y') {
        adicionarCliente();
        cliente = &Clientes.back();
    }
    else {
        do
        {
            cliente = selecionarCliente();
            if (!cliente)
            {
                cout << "ID de cliente inválido. Tente novamente ou adicione um novo cliente." << endl;
                cout << "Deseja tentar novamente? (Y/N): ";
                getline(cin, input);
                char tentarNovamente = input[0];
                if (tentarNovamente == 'n' || tentarNovamente == 'N')
                {
                    cout << "Venda cancelada. " << endl;
                    _getch();
                    return; // Cancela a venda se o cliente não for selecionado
                }
            }
        } while (!cliente);
    }

    venda.setCliente(*cliente);    

    // Checkout
    double total = venda.getTotalVenda();
    Produto p; // Produto usado para fazer o checkout
    cout << endl;
    for (LinhaVenda l : venda.getLinhas()) {       
        p = l.getProduto();
        cout << p.getNome() << "(" << l.getQuantidade() << ") | " << l.getTotalComIVA() << " EUR" << endl;
    }
    cout << "Total a pagar (com IVA): " << fixed << setprecision(2) << total << " EUR" << endl;

    do {
        cout << endl << "Deseja prosseguir com a compra?(Y/N) ";
        getline(cin, input);
        opt = input[0];

        if (opt == 'n' || opt == 'n') {
            cout << "\nVenda cancelada";
            _getch();
            return;
        }

    } while (opt != 'y' && opt != 'Y' && opt != 'n' && opt != 'N');

    // Confirmar venda e atualizar estoque
    const auto& itensVendidos = venda.getLinhas();

    for (const auto& item : itensVendidos) {
        int idComprado = item.getProduto().getId(); // ID do produto comprado
        int quantidadeVendida = item.getQuantidade();

        // Procurar no estoque o produto com o mesmo ID
        for (auto& produtoEstoque : this->Produtos) {
            if (produtoEstoque.getId() == idComprado) {
                // Atualizar a quantidade no estoque real
                produtoEstoque.setQuantidade(produtoEstoque.getQuantidade() - quantidadeVendida);
                break; // Encontrou e atualizou, pode sair do loop interno
            }
        }
    }

    // Sorteio ANTES de pedir o valor ao cliente
    srand((unsigned)time(0));
    bool sorteada = (rand() % 50 == 0);
    venda.setVendaSorteada(sorteada);

    if (sorteada) {
        cout << "Parabéns! Sua venda foi sorteada e será gratuita!" << endl;
        venda.checkout(0);
    }
    else {
        double valorEntregue = Validacoes::obterFloat("Valor entregue pelo cliente: ");
		const double EPSILON = 0.01; // Tolerância para comparação de floats
        while (valorEntregue + EPSILON < total) {
            cout << "Valor insuficiente. Tente novamente." << endl;
            valorEntregue = Validacoes::obterFloat("Valor entregue pelo cliente: ");
        }
        venda.checkout(valorEntregue);
    }



    // Imprimir talão
    system("cls");
    venda.imprimirTalao();

    // Armazenar venda
    adicionarVenda(venda);

    cout << "Venda concluída! Pressione qualquer tecla para voltar ao menu." << endl;
    _getch();
}