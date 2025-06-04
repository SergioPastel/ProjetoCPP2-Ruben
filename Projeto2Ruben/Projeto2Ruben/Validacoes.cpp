#include "Validacoes.h"
#include "Common.h"

using namespace std;

// Função auxiliar para limpar o buffer de entrada e tratar erros
void limparBufferEntrada() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//função para tratar entrada inválida.
void tratarErroEntrada() {
    cout << "Entrada inválida. Por favor, tente novamente.\n";
    cin.clear(); // Limpa os flags de erro
    limparBufferEntrada(); // Descarta a entrada inválida
}

// Função para obter um float válido do usuário
float obterFloat(const string& prompt) {// Usado em cin's para validar ints e retornar os valores se forem validos. Se não forem repete até serem.
    float valor;
    while (true) {
        cout << prompt;
        if (cin >> valor && valor > 0) {
            limparBufferEntrada();
            return valor;
        }
        else {
            tratarErroEntrada();
        }
    }
}

int validacaoInt(const string& prompt) { // Usado em cin's para validar ints e retornar os valores se forem validos. Se não forem repete até serem.
    int n;

    while (true) {
        cout << prompt;
        if (cin >> n) {
            limparBufferEntrada();
            return n;
        }
        else {
            tratarErroEntrada();
        }
    }

    return n;
}