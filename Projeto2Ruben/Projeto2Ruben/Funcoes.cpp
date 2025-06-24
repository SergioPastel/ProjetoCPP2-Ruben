#include "Common.h"
#include "Loja.h"

#define CYAN    "\033[36m" // Define a cor ciano.
#define RESET   "\033[0m" // Reseta a cor para o padrão.
void submenuRelatorios(Loja& l);

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
    {2, "Criar Novo / Atualizar Artigo"},
    {3, "Excluir Produto"},
    {4, "Exibir Stock"},
    {5, "Adicionar Clientes"},
    {6, "Alterar Clientes"},
    {7, "Remover Clientes"},
    {8, "Relatórios"},
    {9, "Sair"}
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
            l.efetuarVenda();
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
            {
                int id = validacaoInt("Insira o ID do cliente que desejas remover: ");
                Cliente* clientePtr = nullptr;
                l.checarCliente(id, clientePtr);
                if (clientePtr != nullptr) {
                    l.removerCliente(id);
                } else {
                    cout << "Cliente com o ID informado não encontrado." << endl;
                }
                cout << "Prima qualquer tecla...";
                _getch();
            }
            break;
        case 8:
            submenuRelatorios(l);
            break;
        case 9:
            cout << "Pressione qualquer tecla..." << endl;
            _getch();
            break;

        default:
            cout << "Opcao invalida! Tente novamente." << endl;
            _getch();
        }

        cout << endl;

    } while (opcao != 9);
}
void submenuRelatorios(Loja& l) {
    int opcao;
    string input;
    do {
        system("cls");
        l.logotipo();
        cout << "\n=========== SUBMENU DE RELATÓRIOS ===========\n";
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
