#include "Common.h"
#include "Validacoes.h"
#include "Funcoes.h"
#include "Loja.h"

using namespace std;

// Função para converter uma string para minúsculas. Usado para comparações
string Funcoes::toMinuscula(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Todos os menus são definidos aqui, funcionam de forma semelhante, mas com opções diferentes

//função menu
void Funcoes::exibirMenu() { // Menu inicial da aplicação
	
	int opcao; // Variável para armazenar a opção escolhida pelo usuário	
	Loja l; // Loja que vai ser usada pelas funões do menu
	
    vector<pair<int, string>> menuOpcoes = { // Menu de opções, usado para impressão das opções na tela
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

	string linhaSeparadora(larguraTotal, '-'); // Imprime uma linha separadora com base na largura total

	do {  // Loop para exibir o menu até que o usuário escolha sair
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
        opcao = Validacoes::validacaoInt("Escolha uma opcao: ");
        switch (opcao) {
		case 1: 
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
			_getch(); // Getchs são usados para esperar o usuário pressionar uma tecla antes de prosseguir
            break;
        default:
            cout << RED << "Opcao invalida! Tente novamente." << RESET << endl;
            _getch();
        }
        cout << endl;

    } while (opcao != 0);
}

void Funcoes::submenuEstoque(Loja& l) {
    int opcao;
    do {
        system("cls");
        l.logotipo();
        cout << "\n=========== GESTAO DE ESTOQUE ===========\n";
        cout << "1 - Criar Novo / Atualizar Artigo\n";
        cout << "2 - Excluir Artigo\n";
        cout << "3 - Exibir Produtos\n";
        cout << "0 - Voltar ao menu principal\n";
        cout << "=============================================\n";
        opcao = Validacoes::validacaoInt("Escolha uma opção: ");
        switch (opcao) {
        case 1:
            l.adicionarProduto();
            break;
        case 2:
            l.removerProduto();
            break;
        case 3:
            system("cls"); // As outras funções limpam a tela por si, mas o mostrar estoque não faz isso por default
            l.mostrarEstoque();
            cout << "Prima qualquer tecla...";
            _getch();
            break;
		case 0: // Quando o usuário escolhe 0, o loop é encerrado e o menu principal é exibido novamente
            break;
        default:
            cout << RED << "Opção inválida! Tente novamente." << RESET << endl;
            _getch();
        }
    } while (opcao != 0);
}

void Funcoes::submenuClientes(Loja& l) {
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
        opcao = Validacoes::validacaoInt("Escolha uma opção: ");
        switch (opcao) {
        case 1:
            l.adicionarCliente();
            break;
        case 2:
            l.mostrarClientes();
            l.alterarCliente(Validacoes::validacaoInt("Insira o ID do cliente que desejas alterar: "));
            break;
        case 3:
            l.mostrarClientes();
            {
                int id = Validacoes::validacaoInt("Insira o ID do cliente que desejas remover: ");
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
            cout << RED << "Opção inválida! Tente novamente." << RESET << endl;
            _getch();
        }
    } while (opcao != 0);
}

void Funcoes::submenuRelatorios(Loja& l) {
    int opcao;
	string input; // Variável para armazenar o nome do produto que o usuário deseja ver no relatório de vendas por produto
    do {
        system("cls");
        l.logotipo();
        cout << "\n=========== RELATÓRIOS ===========\n";
        cout << "1 - Relatório de estoque total\n";
        cout << "2 - Relatório de vendas por produto\n";
        cout << "3 - Relatório total de vendas\n";
        cout << "0 - Voltar ao menu principal\n";
        cout << "=============================================\n";
        opcao = Validacoes::validacaoInt("Escolha uma opção: ");
        switch (opcao) {
        case 1:
            system("cls");
            l.relatorioEstoqueTotal();
            cout << "Prima qualquer tecla...";
            _getch();
            break;
        case 2:
            system("cls");
            l.logotipo();
            l.mostrarEstoqueComPrecoVenda();
            cout << "Insira o nome do produto que deseja ver: ";
			getline(cin, input); // Getline é usado para ler uma linha inteira, incluindo espaços
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
            cout << RED << "Opção inválida! Tente novamente." << RESET << endl;
            _getch();
        }
    } while (opcao != 0);
}
