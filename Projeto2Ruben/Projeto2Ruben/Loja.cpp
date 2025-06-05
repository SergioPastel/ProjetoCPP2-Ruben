#include "Loja.h"
#include "Common.h"


Loja::Loja() {
    vector<Produto> Produtos;
}

//funcao mostrar estoque
void Loja::mostrarEstoque(){
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