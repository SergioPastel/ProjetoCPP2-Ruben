#include "Loja.h"
#include "Common.h"
#include "Venda.h"
#include "Produto.h"
#include "Cliente.h"


Loja::Loja() {
    this->Produtos.emplace_back(1, "Placa Mãe Asus B550", 20, 85.00);
    this->Produtos.emplace_back(2, "Processador Ryzen 5 5600X", 20, 140.00);
    this->Produtos.emplace_back(3, "Memoria RAM 16GB DDR4", 20, 35.00);
    this->Produtos.emplace_back(4, "Disco SSD 1TB NVMe", 20, 55.00);
    this->Produtos.emplace_back(5, "Fonte 650W 80+ Bronze", 20, 45.00);
    this->Produtos.emplace_back(6, "Placa Grafica RTX 3060", 20, 260.00);
    this->Produtos.emplace_back(7, "Caixa Mid Tower", 20, 40.00);
    this->Produtos.emplace_back(8, "Cooler CPU ARGB", 20, 25.00);
    this->Produtos.emplace_back(9, "Monitor 24'' Full HD", 20, 90.00);
    this->Produtos.emplace_back(10, "Suporte Monitor", 20, 8.00);

    Clientes.push_back(Cliente(1, "João Silva", 912345678, "Rua A, 123"));
    Clientes.push_back(Cliente(2, "Maria Santos", 934567890, "Av. B, 456"));
    Clientes.push_back(Cliente(3, "Carlos Costa", 965432187, "Praça C, 789"));
}

//funcao mostrar estoque
void Loja::mostrarEstoque() {
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

    idProduto = validacaoInt("Insira o ID do produto: ");

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

    system("cls");

    int tamanho = Loja::Produtos.size(); // Pra não dar erro no VS code

    for (int i = 0; i < tamanho; i++) {
        if (toMinuscula(Produtos[i].getNome()) == toMinuscula(nome)) {  // Compara o nome do produto com cada item do estoque. Se encontrar um igual, deixa de adicionar e comea a alterar o produto existente
            string input; // Necessario para receber a linha
            char opt; // Necessario para receber a opção sem encher o buffer

            cout << "PRODUTO - " << Produtos[i].imprimirDados();
            while (true) {
                valorAdd = validacaoInt("Adicione ao stock (valor >= 0): "); // Altera a mensagem para o usuário
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
                Produtos[i].setPreco(obterFloat("Insira o novo preço: "));
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
            system("cls");
        } while (continuar != 'y' && continuar != 'n' && continuar != 'Y' && continuar != 'N');

        if (continuar == 'n' || continuar == 'N') // Se o usuario não quiser prosseguir, retorne a função anterior
            return;

        Produto p; // Novo produto que iremos adicionar ao array no final

        p.setNome(nome); // O nome do produto e o nome que inserimos acima
        p.setId(Produtos.size() + 1); // Id atribuido e um a mais do que o tamanho do estoque, que seria o ultimo id por default

        cout << "Nome do Produto: " << nome << endl;
        p.setPreco(obterFloat("Insira o custo: "));
        while (p.getPreco() <= 0) // Enquanto o user tentar dar valor 0 ou negativo, fica pedindo por novo valor
            p.setPreco(obterFloat("Custo invalido. Insira um valor maior que 0: "));

        p.setQuantidade(validacaoInt("Insira a quantidade: "));
        while (p.getQuantidade() <= 0) // Enquanto o user tentar dar valor 0 ou negativo, fica pedindo por novo valor
            p.setQuantidade(validacaoInt("Quantidade invalida. Insira um valor maior que 0: "));

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
    int idCliente = validacaoInt("Insira o ID do cliente: ");

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
    cout << "------------------- CLIENTES -------------------" << endl;
    for (const auto& c : Clientes) {
        cout << "ID: " << c.getId() << " | Nome: " << c.getNome()  << " | Telefone: " << c.getTelefone() << " | Morada: " <<
            c.getMorada() << endl;
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
            cout << "Deseja alterar o nome?(Y/N)";
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
            cout << "Deseja alterar o numero de telefone?(Y/N)";
            getline(cin, input);
            opt = input[0];
        } while (opt != 'y' && opt != 'n' && opt != 'Y' && opt != 'N');

        if (opt == 'y' || opt == 'Y') {
            int novoTel;  
            novoTel = validacaoInt("Digite o novo numero do cliente: ");
            cliente->setTelefone(novoTel);
            alterado = true;
        }

        // Alteração de morada
        do {
            cout << "Deseja alterar a morada?(Y/N)";
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


void Loja::adicionarCliente() {
    int id = Clientes.size() + 1;
    string nome;
    int telefone;
    string morada;

    system("cls");
    mostrarClientes();

    cout << "Insira o nome do novo cliente: ";
    getline(cin, nome); // Le a linha inteira, permitindo espacos nos nomes
    validacaoInt("Insira o numero de telefone: ");
    cout << "Insira a morada: ";
    getline(cin, morada);

    this->Clientes.emplace_back(id ,nome, telefone, morada);
}

void Loja::adicionarVenda(const Venda& venda)
{
    {
        // Limite de 100 vendas, sobrescreve as mais antigas
        if (Vendas.size() < 100) {
            Vendas.push_back(venda);
        }
        else {
            static int pos = 0;
            Vendas[pos] = venda;
            pos = (pos + 1) % 100;
        }
    }
}

void Loja::efetuarVenda()
{
    string input;
    char opt;
    Cliente* cliente;

    system("cls");
    cout << "************ EFETUAR VENDA ************" << endl;

    Venda venda;

    // Seleção de produtos
    char adicionarMais;
	bool produtoAdicionado = false;

    mostrarEstoque();
    do {        
        int idProduto = validacaoInt("Insira o ID do produto: ");
        Produto* produtoSelecionado = nullptr;
        checarProdutoEstoque(idProduto, produtoSelecionado);

        if (!produtoSelecionado || produtoSelecionado->getQuantidade() == 0) {
            cout << "Produto inválido ou sem estoque." << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer de entrada

        }
        else {
            int quantidade = validacaoInt("Quantidade a comprar: ");
            if (quantidade > 0 && quantidade <= produtoSelecionado->getQuantidade()) {
                venda.adicionarProduto(*produtoSelecionado, quantidade);                
                cout << "Produto adicionado a venda." << endl;
				produtoAdicionado = true; // Marca que pelo menos um produto foi adicionado
            }
            else {
                cout << "Quantidade invalida." << endl;
            }
        }
        cout << "Adicionar mais produtos? (Y/N): ";
        getline(cin, input);
        adicionarMais = input.empty() ? 'n' : input[0];
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
        opt = input.empty() ? 'n' : input[0];
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
				char tentarNovamente = input.empty() ? 'n' : input[0];
                if (tentarNovamente == 'n' || tentarNovamente == 'N')
                {
                    cout << "Venda cancelada. " << endl;
					_getch();
					return; // Cancela a venda se o cliente não for selecionado
                }
            }
        } while (!cliente);
    }

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

    // Checkout
    double total = venda.getTotalVenda();
    cout << "Total a pagar (com IVA): " << fixed << setprecision(2) << total << " EUR" << endl;
    double valorEntregue = obterFloat("Valor entregue pelo cliente: ");
    while (valorEntregue < total) {
        cout << "Valor insuficiente. Tente novamente." << endl;
        valorEntregue = obterFloat("Valor entregue pelo cliente: ");
    }
    venda.checkout(valorEntregue);

    // Imprimir talão
    system("cls");
    venda.imprimirTalao();

    // Armazenar venda
    adicionarVenda(venda);

    cout << "Venda concluída! Pressione qualquer tecla para voltar ao menu." << endl;
    _getch();
}