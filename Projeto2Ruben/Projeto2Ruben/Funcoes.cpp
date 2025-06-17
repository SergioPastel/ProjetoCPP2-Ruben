#include "Common.h"
#include "Loja.h"

using namespace std;

// Função para converter uma string para minúsculas
string toMinuscula(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

//função menu
void exibirMenu() {
    int opcao;
    Loja l;

    vector<pair<int, string>> menuOpcoes = {
        {1, "Efetuar Venda"},
        {2, "Criar Novo / Atualizar Artigo"},
        {3, "Excluir Produto"},
        {4, "Exibir Stock"},
		{5, "Adicionar Clientes"},
		{6, "Alterar Clientes"},
        {7, "Remover Clientes"},
        {8, "Sair"}
    };

    // Definir as larguras das colunas
    const int larguraID = 7;
    const int larguraOpcao = 40;

    // Calcular a largura total da linha
    const int larguraTotal = larguraID + 2 + larguraOpcao + 2; // ID + " | " + Opção + " |"

    string linhaSeparadora(larguraTotal, '-');

    do {
        system("cls");

        cout << "------------------ MENU PRINCIPAL -----------------" << endl;
        cout << left << setw(larguraID) << "Opção" << " | " << left << setw(larguraOpcao) << "Descrição" << endl;
        cout << linhaSeparadora << endl;

        for (const auto& item : menuOpcoes) {
            cout << left << setw(larguraID) << item.first << " | " << left << setw(larguraOpcao) << item.second << endl;
        }

        cout << linhaSeparadora << endl;
        opcao = validacaoInt("Escolha uma opcao: ");
        switch (opcao) {
        case 1: l.efetuarVenda();
            // chamar funcao de venda aqui
            // venda();
            break;
        case 2: 
            // chamar funcao de criacao
            l.adicionarProduto();
            break;
        case 3:
            // chamar funcao de eliminacao
            l.removerProduto();
            break;
        case 4:
            // chamar funcao mostrar estoque
            l.mostrarEstoque();
            cout << "Prima qualquer tecla...";
            _getch();
            break;
        case 5:
            // chamar funcao adicionar cliente
            l.adicionarCliente();
            break;
		case 6:
            // chamar funcao mostrar clientes
            l.mostrarClientes();
            l.alterarCliente(validacaoInt("Insira o ID do cliente que desejas alterar: "));
            break;
        case 7:
            // chamar funcao mostrar clientes
            l.mostrarClientes();
            l.removerCliente(validacaoInt("Insira o ID do cliente que desejas remover: "));
            break;
        case 8:
            cout << "Pressione qualquer tecla..." << endl;
            _getch();
            exit(0); 
            break;
        default:
            cout << "Opcao invalida! Tente novamente." << endl;
            _getch();
        }

        cout << endl;

    } while (opcao != 7);
}