#include "Estoque.h"
#include "Common.h"


Estoque::Estoque() {
    vector<Produto> Produtos;
}

//funcao mostrar estoque
void Estoque::mostrarEstoque(){
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
void Estoque::checarProdutoEstoque(int idProduto, Produto*& produtoSelecionado) {
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