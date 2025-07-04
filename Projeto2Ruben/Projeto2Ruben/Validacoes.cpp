#include "Validacoes.h"
#include "Common.h"

using namespace std;

// Função auxiliar para limpar o buffer de entrada e tratar erros
void Validacoes::limparBufferEntrada() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//função para tratar entrada inválida.
void Validacoes::tratarErroEntrada() {
	cout << RED << "Entrada inválida. Por favor, tente novamente.\n"; cout << RESET << endl;
    cin.clear(); // Limpa os flags de erro
    Validacoes::limparBufferEntrada(); // Descarta a entrada inválida
}

// Função para obter um float válido do usuário
float Validacoes::obterFloat(const string& prompt) {// Usado em cin's para validar ints e retornar os valores se forem validos. Se não forem repete até serem.
    float valor;
    while (true) {
        cout << prompt;
        if (cin >> valor && valor > 0) {
            Validacoes::limparBufferEntrada();
            return valor;
        }
        else {
            Validacoes::tratarErroEntrada();
        }
    }
}

int Validacoes::validacaoInt(const string& prompt) { // Usado em cin's para validar ints e retornar os valores se forem validos. Se não forem repete até serem.
    int n;

    while (true) {
        cout << prompt;
        if (cin >> n) {
            Validacoes::limparBufferEntrada();
            return n;
        }
        else {
            Validacoes::tratarErroEntrada();
        }
    }

    return n;
}