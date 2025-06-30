#include "Common.h"
#include "Validacoes.h"
#include "Funcoes.h"
#include "Loja.h"

#define CYAN    "\033[36m" // Define a cor ciano.
#define RESET   "\033[0m" // Reseta a cor para o padrão.

using namespace std;

// Função para converter uma string para minúsculas
string toMinuscula(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

//função menu
void exibirMenu() {
	
    int opcao;
    string input;
    Loja l;
	
    vector<pair<int, string>> menuOpcoes = {
    {1, "Efetuar Venda"},
    {2, "Gestao de Estoque"},
    {3, "Gestao de Clientes"},
    {4, "Relatórios"},
    {0, "Sair"}
    };


    // Definir as larguras das colunas
    const int larguraID = 7;
    const int larguraOpcao = 40;

    // Calcular a largura total da linha
    const int larguraTotal = larguraID + 2 + larguraOpcao + 2; // ID + " | " + Opção + " |"

    string linhaSeparadora(larguraTotal, '-');

    do {
        system("cls");
        l.logotipo();
		cout << endl;
        cout << CYAN << "Desenvolvido por Diego Mayrinck e Sergio Sant'Anna" << RESET << endl;
        cout << endl;
        cout << "------------------ MENU PRINCIPAL -----------------" << endl;
        cout << left << setw(larguraID) << "Opção" << " | " << left << setw(larguraOpcao) << "Descrição" << endl;
        cout << linhaSeparadora << endl;

        for (const auto& item : menuOpcoes) {
            cout << left << setw(larguraID) << item.first << " | " << left << setw(larguraOpcao) << item.second << endl;
        }

        cout << linhaSeparadora << endl;
        opcao = validacaoInt("Escolha uma opcao: ");
        switch (opcao) {
		case 1: 
            // chamar funcao de venda aqui 
            l.efetuarVenda();                    
            break;
        case 2: 
            submenuEstoque(l);
            break;
        case 3:
            submenuClientes(l);
            break;
        case 4:
            submenuRelatorios(l);
            break;
        case 0:
            cout << "Pressione qualquer tecla..." << endl;
            _getch();
            break;
        default:
            cout << "Opcao invalida! Tente novamente." << endl;
            _getch();
        }
        cout << endl;

    } while (opcao != 0);
}

void submenuEstoque(Loja& l) {
    int opcao;
    string input;
    do {
        system("cls");
        l.logotipo();
        cout << "\n=========== GESTAO DE ESTOQUE ===========\n";
        cout << "1 - Criar Novo / Atualizar Artigo\n";
        cout << "2 - Excluir Artigo\n";
        cout << "3 - Exibir Produtos\n";
        cout << "0 - Voltar ao menu principal\n";
        cout << "=============================================\n";
        opcao = validacaoInt("Escolha uma opção: ");
        switch (opcao) {
        case 1:
            // chamar funcao de criacao
            l.adicionarProduto();
            break;
        case 2:
            // chamar funcao de eliminacao
            l.removerProduto();
            break;
        case 3:
            // chamar funcao mostrar estoque
            system("cls");
            l.mostrarEstoque();
            cout << "Prima qualquer tecla...";
            _getch();
            break;
        case 0:
            break;
        default:
            cout << "Opção inválida! Tente novamente." << endl;
            _getch();
        }
    } while (opcao != 0);
}

void submenuClientes(Loja& l) {
    int opcao;
    string input;
    do {
        system("cls");
        l.logotipo();
        cout << "\n=========== GESTAO DE CLIENTES ===========\n";
        cout << "1 - Adicionar clientes\n";
        cout << "2 - Alterar clientes\n";
        cout << "3 - Remover clientes\n";
        cout << "0 - Voltar ao menu principal\n";
        cout << "=============================================\n";
        opcao = validacaoInt("Escolha uma opção: ");
        switch (opcao) {
        case 1:
            // chamar funcao adicionar cliente
            l.adicionarCliente();
            break;
        case 2:
            // chamar funcao mostrar clientes
            l.mostrarClientes();
            l.alterarCliente(validacaoInt("Insira o ID do cliente que desejas alterar: "));
            break;
        case 3:
            // chamar funcao mostrar clientes
            l.mostrarClientes();
            {
                int id = validacaoInt("Insira o ID do cliente que desejas remover: ");
                Cliente* clientePtr = nullptr;
                l.checarCliente(id, clientePtr);
                if (clientePtr != nullptr) {
                    l.removerCliente(id);
                }
                else {
                    cout << "Cliente com o ID informado não encontrado." << endl;
                }
                cout << "Prima qualquer tecla...";
                _getch();
            }
            break;
        case 0:
            break;
        default:
            cout << "Opção inválida! Tente novamente." << endl;
            _getch();
        }
    } while (opcao != 0);
}

void submenuRelatorios(Loja& l) {
    int opcao;
    string input;
    do {
        system("cls");
        l.logotipo();
        cout << "\n=========== RELATÓRIOS ===========\n";
        cout << "1 - Relatório de estoque total\n";
        cout << "2 - Relatório de vendas por produto\n";
        cout << "3 - Relatório total de vendas\n";
        cout << "0 - Voltar ao menu principal\n";
        cout << "=============================================\n";
        opcao = validacaoInt("Escolha uma opção: ");
        switch (opcao) {
        case 1:
            system("cls");
            l.relatorioEstoqueTotal();
            cout << "Prima qualquer tecla...";
            _getch();
            break;
        case 2:
            system("cls");
            l.mostrarEstoqueComPrecoVenda();
            cout << "Insira o nome do produto que deseja ver: ";
            getline(cin, input);
            l.relatorioVendasPorProduto(input);
            cout << "Prima qualquer tecla...";
            _getch();
            break;
        case 3:
            system("cls");
            l.relatorioTotalVendas();
            cout << "Prima qualquer tecla...";
            _getch();
            break;
        case 0:
            break;
        default:
            cout << "Opção inválida! Tente novamente." << endl;
            _getch();
        }
    } while (opcao != 0);
}
