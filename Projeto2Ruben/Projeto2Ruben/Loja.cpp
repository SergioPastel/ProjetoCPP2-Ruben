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



void Loja::mostrarClientes()
{
    cout << "------------------- CLIENTES -------------------" << endl;
    for (const auto& c : Clientes) {
        cout << "ID: " << c.getId() << " | Nome: " << c.getNome() << endl;
    }
    cout << "------------------------------------------------" << endl;
}

Cliente* Loja::selecionarCliente()
{
    {
        mostrarClientes();
        int idCliente = validacaoInt("Insira o ID do cliente: ");
        for (auto& c : Clientes) {
            if (c.getId() == idCliente) {
                return &c;
            }
        }
        cout << "Cliente não encontrado!" << endl;
        return nullptr;
    }
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
    {
        system("cls");
        cout << "************ EFETUAR VENDA ************" << endl;

        // Selecionar cliente
        Cliente* cliente = selecionarCliente();
        if (!cliente) {
            cout << "Operação cancelada." << endl;
            _getch();
            return;
        }

        Venda venda(*cliente);

        // Seleção de produtos
        char adicionarMais;
        do {
            mostrarEstoque();
            int idProduto = validacaoInt("Insira o ID do produto: ");
            Produto* produtoSelecionado = nullptr;
            checarProdutoEstoque(idProduto, produtoSelecionado);

            if (!produtoSelecionado || produtoSelecionado->getQuantidade() == 0) {
                cout << "Produto inválido ou sem estoque." << endl;
            }
            else {
                int quantidade = validacaoInt("Quantidade a comprar: ");
                if (quantidade > 0 && quantidade <= produtoSelecionado->getQuantidade()) {
                    venda.adicionarProduto(*produtoSelecionado, quantidade);
                    produtoSelecionado->setQuantidade(produtoSelecionado->getQuantidade() - quantidade);
                    cout << "Produto adicionado a venda." << endl;
                }
                else {
                    cout << "Quantidade invalida." << endl;
                }
            }
            cout << "Adicionar mais produtos? (Y/N): ";
            string input;
            getline(cin, input);
            adicionarMais = input.empty() ? 'n' : input[0];
        } while (adicionarMais == 'y' || adicionarMais == 'Y');

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
        venda.imprimirTalao();

        // Armazenar venda
        adicionarVenda(venda);

        cout << "Venda concluída! Pressione qualquer tecla para voltar ao menu." << endl;
        _getch();
    }
}