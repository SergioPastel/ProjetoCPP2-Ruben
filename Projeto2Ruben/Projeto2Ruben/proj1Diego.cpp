#include <iostream> // Inclui a biblioteca padrão para entrada e saída (cin, cout).
#include <Windows.h> //Biblioteca para o Sleep
#include <iomanip> //Biblioteca para o setprecision para ter 2 casas decimais e para o setw
#include <ctime> // Para obter a data e hora
#include <limits> // Para obter os limites de tipos de dados como double, int, float e etc.
#include <string> // Para usar o getline
#include <cctype> // Para o tolower (converte o texto todo em letras minusculas)

using namespace std; // Permite usar elementos da biblioteca padrão sem o prefixo "std::"

// Códigos de cor ANSI para personalizar a saída no terminal.
#define RESET   "\033[0m" // Reseta a cor para o padrão.
#define RED     "\033[31m" // Define a cor vermelha.
#define GREEN   "\033[32m" // Define a cor verde.
#define CYAN    "\033[36m" // Define a cor ciano.


// Declaração das funções utilizadas no programa.
void logoTipo(); //Exibe o logotipo ASCII da loja.
void mainMenu(); //Exibe o menu principal.
void mostrarProdutos(bool); //Mostra os produtos disponíveis na loja.
void selecionarProduto(); //Permite ao cliente selecionar um produto para compra.
void novoProduto(); //Adiciona um novo produto à loja.
void menuContinuarComprarAdicionarProduto(int); //Menu para continuar comprando ou adicionar mais produtos.
void checkoutUser(); //Realiza o checkout do cliente.
void eliminarProduto(); //Elimina um produto da loja.
void imprimirTalao(); //Imprime o talão de compra.


//Estrutura usada para representar cada produto da loja
struct Produto {
    int id;
    string nome;
    double preco;
    int stock;
    bool ativo; //Indica se o produto está ativo (disponível para venda)
};

//Quantidade maxima de produtos que podem ser adicionados
const int maxProds = 100;
//Indice da quantidade de produtos
int quantidade = 3;

//Criação do vetor com 3 produtos adicionados, após o arranque do programa
Produto loja[maxProds]{
    {1, "Cafe", 1.20, 20, true},
    {2, "Leite", 0.80, 15, true},
    {3, "Pao", 0.50, 30, true},
};


//Estrutura usada para representar cada produto que user comprou
struct checkout {
    int idProd = 0;
    string nome;
    int quantidade = 0;
    double preco = 0.00;
};

double valorEntregueGlobal = 0.0; // Armazena o valor entregue pelo cliente

int userID = 0;
bool userIdIntroduzido = false; //Um booleano que indica se o ID do cliente já foi introduzido. Começa como falso, e quando o user introduz o ID, passa a verdadeiro

//Indice que é um contador de produtos no checkout. Começa com zero porque ainda não há produtos no checkout.
int quantidadeCheckout = 0;


//Criação do vetor para o checkout e fatura
checkout checkFatura[maxProds];


//========== MENU SECTION ==========
void logoTipo() {
    //Nota R(...) é uma raw string literal, que permite fazer artes ASCII e inserir texto livremente
    cout << CYAN << R"(
     _____                                        
    |  __ \                           _       _   
    | |__) |__  _   _ _ __   ___    _| |_   _| |_ 
    |  ___/ _ \| | | | '_ \ / _ \  |_   _| |_   _|
    | |  | (_) | |_| | |_) |  __/    |_|     |_|  
    |_|   \___/ \__,_| .__/ \___|                 
                     | |                          
                     |_|                          
    )" << RESET << endl << endl; //Reseta a cor para voltar ao normal.
}



//Função para mostrar os produtos da loja
void mostrarProdutos(bool trinta) {
    cout << left; // Alinha o texto à esquerda
    cout << setw(5) << "ID" << setw(20) << "Nome" << setw(10) << "Preco" << setw(10) << "Stock" << endl; // Cabeçalho das colunas. Cada coluna tem um tamanho fixo definido por setw.
    cout << string(45, '-') << endl; // Linha separadora

    for (int i = 0; i < quantidade; i++) { // Percorre o vetor dos produtos da loja
        if (loja[i].ativo == true) { // Verifica se o produto está ativo
            if (trinta == false)
            {
                cout << setw(5) << loja[i].id // Exibe o ID do produto com o tamanho definido por setw.
                    << setw(20) << loja[i].nome // Exibe o nome do produto com o tamanho definido por setw.
                    << setw(10) << fixed << setprecision(2) << loja[i].preco // Exibe o preço do produto com 2 casas decimais e o tamnho definido por setw.
                    << setw(10) << loja[i].stock // Exibe o estoque do produto com o tamanho definido por setw.
                    << endl;
            }
            else
            {
                cout << setw(5) << loja[i].id // Exibe o ID do produto com o tamanho definido por setw.
                    << setw(20) << loja[i].nome // Exibe o nome do produto com o tamanho definido por setw.
                    << setw(10) << fixed << setprecision(2) << loja[i].preco * 1.30 // Exibe o preço do produto com 2 casas decimais e o tamnho definido por setw.
                    << setw(10) << loja[i].stock // Exibe o estoque do produto com o tamanho definido por setw.
                    << endl;
            }
        }
    }
}



void selecionarProduto() { // Função para selecionar um produto para compra.

    int prod, qtd; // Variáveis para armazenar o ID do produto e a quantidade desejada

    system("CLS"); // Limpa o ecrã

    if (userIdIntroduzido == false) // Se o ID do cliente ainda não foi introduzido, pede para o usuário inserir o ID
    {
        logoTipo();

        cout << "Insira o numero do cliente: ";
        cin >> userID;

        if (cin.fail()) {
            cin.clear(); // Limpa o estado de erro
            cin.ignore(1000, '\n'); // Descarta a entrada inválida

            system("CLS");
            cout << RED << "Insira um valor valido." << RESET;
            Sleep(3000);

            selecionarProduto();
        } else if (userID <= 0) {
            system("CLS");

            cout << RED << "ID tem de ser maior que zero.\n\n" << RESET;

            system("pause");
            selecionarProduto();
        }
        else
        {
            userIdIntroduzido = true; // Marca que o ID foi introduzido.
        }
    }

    system("CLS"); // Limpa o ecrã

    logoTipo();

    mostrarProdutos(true); // Mostra os produtos com 30%

    cout << "\n\n";

    cout << "Que produto deseja comprar: ";
    cin >> prod; // Lê o ID do produto desejado.

    if (cin.fail()) {
        cin.clear(); // Limpa o estado de erro
        cin.ignore(1000, '\n'); // Descarta a entrada inválida

        system("CLS");
        cout << RED << "Insira um valor valido." << RESET;
        Sleep(3000);

        selecionarProduto();
    }

    bool prodEncontrado = false; // Inicia em falso o produto encontrado

    for (int i = 0; i < quantidade; i++) {
        if (loja[i].id == prod) { // Verifica se o produto (id) está no vetor
            prodEncontrado = true; // Produto encontrado, passa a true.

            cout << "\nQual a quantidade que quer comprar: ";
            cin >> qtd; // Lê a quantidade desejada 


            if (cin.fail()) {
                cin.clear(); // Limpa o estado de erro
                cin.ignore(1000, '\n'); // Descarta a entrada inválida

                system("CLS");
                cout << RED << "Insira um valor valido." << RESET;
                Sleep(3000);

                selecionarProduto();
            }
            if (qtd <= 0)
            {
                cout << RED << "Quantidade tem de ser maior que zero.\n" << RESET;

                system("pause");

                selecionarProduto();
            }


            if (qtd > loja[i].stock) { // Verifica se tem quantidade suficiente para efetuar a compra
                cout << RED << "Stock insuficiente, so existe " << loja[i].stock << " em stock." << RESET;

                Sleep(3000); // A tela fica congelada por 3 segundos

                menuContinuarComprarAdicionarProduto(2); // Redireciona para o menu de vendas

                return; // Sai da função para evitar criar uma venda inválida
            }

            // Verifica se o produto já está no checkout
            for (int j = 0; j < quantidadeCheckout; j++) { // Ciclo para percorrer o vetor dos produtos que o user escolheu comprar
                if (checkFatura[j].idProd == prod) { // Verifica se o produto já está no checkout
                    if (checkFatura[j].quantidade + qtd > loja[i].stock) { // Verifica se o user não ultrapassa o Stock
                        cout << RED << "Stock insuficiente! Apenas " << loja[i].stock << " unidades disponiveis, e tem " << checkFatura[j].quantidade << " unidades no carrinho." << RESET;

                        Sleep(4000); // A tela fica congelada por 4 segundos

                        menuContinuarComprarAdicionarProduto(2); // Redireciona para o menu de vendas

                        return; // Sai da função para evitar criar uma venda inválida
                    }

                    // Atualiza a quantidade no carrinho
                    checkFatura[j].quantidade += qtd; // Atualiza a quantidade do produto no checkout

                    cout << GREEN << "Compra atualizada com sucesso!" << RESET;

                    Sleep(3000); // A tela fica congelada por 3 segundos

                    menuContinuarComprarAdicionarProduto(2); // Chama um menu a perguntar se quer continuar a comprar ou voltar

                    return; // Sai da função após atualizar o carrinho
                }

            }

            // Adiciona o produto à estrutura do checkout/fatura
            checkFatura[quantidadeCheckout].idProd = prod;
            checkFatura[quantidadeCheckout].nome = loja[i].nome;
            checkFatura[quantidadeCheckout].preco = loja[i].preco;
            checkFatura[quantidadeCheckout].quantidade = qtd;

            quantidadeCheckout++; // Aumenta o índice de produtos no vetor checkout

            cout << GREEN << "Compra registada com sucesso!" << RESET;

            Sleep(3000); // A tela fica congelada por 3 segundos

            menuContinuarComprarAdicionarProduto(2); // Chama um menu a perguntar se quer continuar a comprar ou voltar

            return; // Sai da função após registrar a compra
        }

    }

    if (prodEncontrado == false) { // Caso o produto não tenha sido encontrado no vetor, retorna uma mensagem de erro
        cout << RED << "Produto nao encontrado!" << RESET;

        Sleep(3000); // A tela fica congelada por 3 segundos

        menuContinuarComprarAdicionarProduto(2); // Redireciona para o menu de vendas
    }

}

void checkoutUser() {
    system("CLS"); // Limpa o ecrã

    double precoPagar;

    if (quantidadeCheckout == 0) { // Verifica se o user já efetuou alguma compra
        system("CLS"); // Limpa o ecrã

        logoTipo();

        cout << RED << "Ainda nao efetuou nenhuma compra!" << RESET;
        Sleep(3000);

        menuContinuarComprarAdicionarProduto(2);
    }
    else {
        logoTipo();

        cout << "<=======> Checkout - Resumo da compra <=======>\n\n";

        cout << "Nome dos artigos: ";

        for (int i = 0; i < quantidadeCheckout; i++) {
            cout << checkFatura[i].nome; // Mostra os nomes dos produtos que o user tem no carrinho

            if (quantidadeCheckout > 1 && i != quantidadeCheckout - 1) { // Adiciona uma "," no meio dos produtos selecionados, menos no último
                cout << ", ";
            }
            else {
                cout << " ";
            }
        }

        cout << "\nQuantidade: ";

        for (int i = 0; i < quantidadeCheckout; i++) {
            cout << checkFatura[i].quantidade; // Mostra a quantidade que o user tem no carrinho de X produto

            if (quantidadeCheckout > 1 && i != quantidadeCheckout - 1) { // Adiciona uma "," no meio dos produtos selecionados, menos no último
                cout << ", ";
            }
            else {
                cout << " ";
            }
        }

        double somaSemIVA = 0.0;
        double somaComIVA = 0.0;

        for (int i = 0; i < quantidadeCheckout; i++) {
            somaSemIVA = somaSemIVA + (checkFatura[i].quantidade * checkFatura[i].preco) * 1.30; // Faz a soma para o preço total sem IVA
        }

        somaComIVA = somaSemIVA * 1.23; // Adiciona 23% de IVA

        cout << fixed << setprecision(2);
        cout << "\nPreco total s/IVA: " << somaSemIVA; // Mostra o preço total sem IVA
        cout << "\nPreco total c/IVA: " << somaComIVA; // Mostra o preço total com IVA

        // Sorteio para determinar se a venda será gratuita
        srand(time(0)); // Inicializa o gerador de números aleatórios
        int sorteio = rand() % 100; // Gera um número entre 0 e 99 (1% de chance)

        if (sorteio == 0) { // Se o número sorteado for 0, a venda é gratuita
            cout << GREEN << "\nParabens! Sua compra foi sorteada e sera totalmente gratuita!" << RESET << endl;
            Sleep(3000);

            // Atualiza o estoque sem cobrar do cliente
            for (int i = 0; i < quantidade; i++) { // Ciclo para percorrer o vetor dos produtos
                for (int j = 0; j < quantidadeCheckout; j++) { // Ciclo para percorrer o vetor dos produtos que o user escolheu comprar
                    if (loja[i].id == checkFatura[j].idProd) {
                        loja[i].stock = loja[i].stock - checkFatura[j].quantidade; // Atualiza o stock depois da compra bem-sucedida
                    }
                }
            }

            valorEntregueGlobal = 0.0; // Redefine o valor entregue para evitar cálculos incorretos no valor do troco.     
            imprimirTalao(); // Imprime o talão normalmente
            return; // Finaliza a função
        }

        cout << "\n\nInsira o valor que vai entregar: ";
        cin >> precoPagar;

        if (cin.fail()) {
            cin.clear(); // Limpa o estado de erro
            cin.ignore(1000, '\n'); // Descarta a entrada inválida

            system("CLS");
            cout << RED << "Insira um valor valido." << RESET;
            Sleep(3000);

            checkoutUser();
        }
        if (precoPagar <= 0)
        {
            cout << RED << "Preco a pagar tem de ser maior que zero.\n";

            system("pause");

            checkoutUser();
        }

        if (precoPagar >= somaComIVA) { // Verifica se o dinheiro que o user entregou é maior ou igual ao valor a pagar
            for (int i = 0; i < quantidade; i++) { // Ciclo para percorrer o vetor dos produtos
                for (int j = 0; j < quantidadeCheckout; j++) { // Ciclo para percorrer o vetor dos produtos que o user escolheu comprar
                    if (loja[i].id == checkFatura[j].idProd) {
                        loja[i].stock = loja[i].stock - checkFatura[j].quantidade; // Atualiza o stock depois da compra bem-sucedida
                    }
                }
            }

            valorEntregueGlobal = precoPagar; // Armazena o valor entregue globalmente

            cout << GREEN << "Compra realizada com sucesso!" << RESET;
            Sleep(3000); // A tela fica congelada por 3 segundos

            imprimirTalao();
        }
        else {
            cout << RED << "Valor insuficiente, tente novamente." << RESET;
            Sleep(3000); // A tela fica congelada por 3 segundos

            checkoutUser();
        }
    }
}


int numeroFatura = 1; // Número inicial da fatura

void imprimirTalao() {
    system("CLS"); // Limpa o ecrã

    logoTipo();

    // Obter a data atual
    time_t now = time(0);
    tm ltm; // Estrutura para armazenar a data
    localtime_s(&ltm, &now); // Usa localtime_s para preencher a estrutura

    double somaSemIVA = 0.0, somaComIVA = 0.0, valorIVA = 0.0;

    cout << CYAN << "==================== TALAO ====================" << RESET << endl;
    cout << "Numero da Fatura: " << numeroFatura << endl;
    cout << "Numero do Cliente: " << userID << endl;
    cout << "Data: " << 1900 + ltm.tm_year << "-" << 1 + ltm.tm_mon << "-" << ltm.tm_mday << endl;
    cout << "----------------------------------------------" << endl;

    cout << "Produto\tQtd\tPreco s/IVA\tPreco c/IVA" << endl;

    for (int i = 0; i < quantidadeCheckout; i++) {
        double precoSemIVA = (checkFatura[i].preco * checkFatura[i].quantidade) * 1.30;
        double precoComIVA = precoSemIVA * 1.23; // Adiciona 23% de IVA
        double iva = precoComIVA - precoSemIVA;

        somaSemIVA = somaSemIVA + precoSemIVA; //Calcula valor sem IVA
        somaComIVA = somaComIVA + precoComIVA; //Calcula valor com IVA
        valorIVA = valorIVA + iva; //Calcula o valor do IVA

        cout << checkFatura[i].nome << "\t"
            << checkFatura[i].quantidade << "\t"
            << fixed << setprecision(2) << precoSemIVA << "\t\t"
            << precoComIVA << endl; //Imprime cada produto
    }

    cout << "----------------------------------------------" << endl;
    cout << "Total s/IVA: " << fixed << setprecision(2) << somaSemIVA << endl;
    cout << "Valor do IVA (23%): " << valorIVA << endl;
    cout << "Total c/IVA: " << somaComIVA << endl;

    // Verifica se a venda foi gratuita
    double troco;
    if (valorEntregueGlobal == 0.0) {
        troco = 0.0; // Troco é zero para vendas gratuitas
    }
    else {
        troco = valorEntregueGlobal - somaComIVA; // Calcula o troco normalmente
    }

    cout << "Valor Entregue: " << valorEntregueGlobal << endl;
    cout << "Troco: " << troco << endl;
    cout << CYAN << "==============================================" << RESET << endl;

    // Incrementar os números da fatura e do cliente
    numeroFatura++;

    // Limpar o vetor de checkout após imprimir o talão
    quantidadeCheckout = 0;
    userID = 0; //Id do user passa a ser 0
    userIdIntroduzido = false; //Verificacao se o user introduziu o ID volta a falso

    cout << endl;
    system("pause");
    mainMenu();
}


//MAIN MENU
void mainMenu() {
    int num = 0;

    do {
        system("CLS"); // Limpa o ecrã

        logoTipo();

        cout << "1 - Efetuar venda" << endl;
        cout << "2 - Adicionar produto" << endl;
        cout << "3 - Eliminar produto" << endl;

        cout << endl << endl;

        cout << "9 - Sair" << endl << endl;

        cout << "Escolha uma opcao: ";
        cin >> num;

        // Verifica se o usuário inseriu uma entrada válida
        if (cin.fail() || (num != 1 && num != 2 && num != 3 && num != 9)) {
            cin.clear(); // Limpa o estado de erro
            cin.ignore(1000, '\n'); // Descarta a entrada inválida

            system("CLS");
            cout << RED << "Insira um valor valido presente no menu." << RESET;
            Sleep(3000);
        }
    } while (num != 1 && num != 2 && num != 3 && num != 9);

    // Verifica a escolha do usuário
    switch (num) {
        case 1:
            selecionarProduto();
            break;
        case 2:
            novoProduto(); // Chama a funcionalidade de adicionar produto
            break;
        case 3:
            eliminarProduto(); // Chama a funcionalidade de eliminar produto
            break;
        case 9:

            system("CLS"); // Limpa o ecrã
            cout << "Obrigado, e volte sempre!" << endl << endl;
            exit(0); // Finaliza o programa
    }
}

void novoProduto() {
    int opcao = 0, stock = 0, idProd = 0;
    double preco = 0.00;
    string nomeProd;

    system("CLS"); //Limpa o ecrã

    logoTipo();

    if (quantidade >= maxProds)
    {
        cout << RED << "Atingiu o limite de produtos!" << RESET;

        return;
    }

    cin.ignore(); // Limpa o buffer de entrada para evitar problemas com o getline
    cout << "Insira o nome do novo produto: ";
    getline(cin, nomeProd); // Usa getline para capturar o nome completo, incluindo espaços

    if (cin.fail()) {
        cin.clear(); // Limpa o estado de erro
        cin.ignore(1000, '\n'); // Descarta a entrada inválida

        system("CLS");
        cout << RED << "Insira um valor valido." << RESET;
        Sleep(3000);

        novoProduto();
    }

    bool prodIgual = false;

    for (int i = 0; i < quantidade; i++)
    {
        string string1 = nomeProd, string2 = loja[i].nome; //Passa ambos os textos para outras variaveis

        for (int j = 0; j < string1.length(); j++) {
            string1[j] = tolower(string1[j]);
        }

        for (int k = 0; k < string2.length(); k++) {
            string2[k] = tolower(string2[k]);
        }

        //Se ambas as strings forem iguais, produto igual foi encontrado e guarda o ID do produto
        if (string1 == string2 && loja[i].ativo == true)
        {
            prodIgual = true;
            idProd = i;

            break;
        }
    }

    //Se o produto for igual lê na mesma os outros valores e no fim atualiza o stock e mostra uma mensagem a dizer que o produto foi encontrado e que o stock do mesmo foi atualizado
    if (prodIgual == true)
    {
        cout << "Insira o stock do novo produto: ";
        cin >> stock;

        if (cin.fail()) {
            cin.clear(); // Limpa o estado de erro
            cin.ignore(1000, '\n'); // Descarta a entrada inválida

            system("CLS");
            cout << RED << "Insira um valor valido." << RESET;
            Sleep(3000);

            novoProduto();
        }
        if (stock <= 0)
        {
            cout << RED << "Stock tem de ser maior que zero.\n" << RESET;

            system("pause");

            novoProduto();
        }

        loja[idProd].stock += stock;

        cout << GREEN << "Ja existe um artigo com o nome '" << nomeProd << "', a atualizar o stock do produto ja existente" << RESET;
    }
    else //Se não existir nenhum produto igual faz o processo normal da criação do produto
    {
        loja[quantidade].id = quantidade + 1;

        loja[quantidade].nome = nomeProd;

        cout << "Insira o preco do novo produto: ";
        cin >> preco;

        if (cin.fail()) {
            cin.clear(); // Limpa o estado de erro
            cin.ignore(1000, '\n'); // Descarta a entrada inválida

            system("CLS");
            cout << RED << "Insira um valor valido." << RESET;
            Sleep(3000);

            novoProduto();
        }
        if (preco <= 0)
        {
            cout << RED << "Preco tem de ser maior que zero.\n" << RESET;

            system("pause");

            novoProduto();
        }

        cout << "Insira o stock do novo produto: ";
        cin >> stock;

        if (cin.fail()) {
            cin.clear(); // Limpa o estado de erro
            cin.ignore(1000, '\n'); // Descarta a entrada inválida

            system("CLS");
            cout << RED << "Insira um valor valido." << RESET;
            Sleep(3000);

            novoProduto();
        }
        if (stock <= 0)
        {
            cout << RED << "Stock tem de ser maior que zero.\n" << RESET;

            system("pause");

            novoProduto();
        }

        loja[quantidade].preco = preco;

        loja[quantidade].stock = stock;

        loja[quantidade].ativo = true;

        quantidade++;


        cout << endl << GREEN << "Produto adicionado com sucesso!" << RESET;
    }

    Sleep(3000);

    //Chama menu para continuar a adicionar produtos ou voltar ao menu anterior
    menuContinuarComprarAdicionarProduto(1);
}



//MENU para o adicionar novo produto e/ou continuar a comprar
void menuContinuarComprarAdicionarProduto(int val) {
    int opcao;

    do
    {
        system("CLS"); //Limpa o ecrã

        logoTipo();

        //Mostra o COUT para a respetiva chamada do menu
        if (val == 1)
        {
            cout << "1 - Continuar a adicionar\n";
        }
        else
        {
            cout << "1 - Continuar a comprar\n";
        }

        if (val == 1)
        {
            cout << "2 - Voltar\n";
        }
        else
        {
            cout << "2 - Checkout\n";
        }

        cout << "Selecione uma opcao: ";
        cin >> opcao;

        //Verifica se o user introduziu texto e apaga o valor que o user inseriu anteriormente
        if (cin.fail() || (opcao != 1 && opcao != 2))
        {
            cin.clear(); //Limpa o estado do erro
            cin.ignore(1000, '\n'); //Descarta 1000 char's do input do user

            system("CLS"); //Limpa o ecrã
            cout << RED << "Insira um valor valido presente no menu." << RESET;
            Sleep(3000);
        }
    } while (opcao != 1 && opcao != 2);

    switch (opcao)
    {
        case 1:
            //Redireciona o user para a respetiva funcao
            if (val == 1)
            {
                novoProduto();
            }
            else
            {
                selecionarProduto();
            }
            break;
        case 2:
            //Redireciona o user para a respetiva funcao
            if (val == 1)
            {
                mainMenu();
            }
            else
            {
                checkoutUser();
            }
            break;
        default:
            break;
    }

}

void eliminarProduto() {

    int idProduto;

    system("CLS"); // Limpa o ecrã

    logoTipo();

    mostrarProdutos(false); // Mostra os produtos disponíveis sem 30%

    cout << "\n\nDigite o ID do produto que deseja eliminar: ";
    cin >> idProduto;

    if (cin.fail()) {
        cin.clear(); // Limpa o estado de erro
        cin.ignore(1000, '\n'); // Descarta a entrada inválida

        system("CLS");
        cout << RED << "Insira um valor valido." << RESET;
        Sleep(3000);

        eliminarProduto();
    }

    // Verifica se o ID do produto é válido
    bool produtoEncontrado = false;

    for (int i = 0; i < quantidade; i++) {
        if (loja[i].id == idProduto && loja[i].ativo == true) {
            produtoEncontrado = true;

            // Marca o produto como inativo
            loja[i].ativo = false;

            cout << GREEN << "Produto '" << loja[i].nome << "' eliminado com sucesso!" << RESET << endl;
            Sleep(3000); // Pausa para exibir a mensagem

            mainMenu(); // Retorna ao menu de estoque

            return;
        }
    }

    if (produtoEncontrado == false) {
        cout << RED << "Produto nao encontrado! Verifique o ID e tente novamente." << RESET << endl;
        Sleep(3000); // Pausa para exibir a mensagem
        eliminarProduto(); // Retorna ao menu de estoque
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    mainMenu();
}