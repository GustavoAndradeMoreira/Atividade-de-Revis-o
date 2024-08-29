#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Ativo {
    string ticket;
    int quantidade;
    double precoMedio;
};

int buscaBinaria(const vector<Ativo>& ativos, const string& ticket, int inicio, int fim) {
    if (inicio > fim)
        return -1;

    int meio = (inicio + fim) / 2;

    if (ativos[meio].ticket == ticket)
        return meio;
    else if (ativos[meio].ticket > ticket)
        return buscaBinaria(ativos, ticket, inicio, meio - 1);
    else
        return buscaBinaria(ativos, ticket, meio + 1, fim);
}

void registrarCompra(vector<Ativo>& ativos) {
    string ticket;
    int quantidade;
    double valor;

    cout << "Digite o ticket do ativo: ";
    cin >> ticket;
    cout << "Digite a quantidade comprada: ";
    cin >> quantidade;
    cout << "Digite o valor do ativo no momento da compra: ";
    cin >> valor;

    int index = buscaBinaria(ativos, ticket, 0, ativos.size() - 1);

    if (index != -1) {
        Ativo& ativo = ativos[index];
        ativo.precoMedio = ((ativo.precoMedio * ativo.quantidade) + (valor * quantidade)) / (ativo.quantidade + quantidade);
        ativo.quantidade += quantidade;
    } else {
        Ativo novoAtivo;
        novoAtivo.ticket = ticket;
        novoAtivo.quantidade = quantidade;
        novoAtivo.precoMedio = valor;
        ativos.push_back(novoAtivo);
        sort(ativos.begin(), ativos.end(), [](const Ativo& a, const Ativo& b) { return a.ticket < b.ticket; });
    }

    cout << "Compra registrada com sucesso!" << endl;
}

void registrarVenda(vector<Ativo>& ativos) {
    string ticket;
    int quantidade;
    double valor;

    cout << "Digite o ticket do ativo: ";
    cin >> ticket;
    cout << "Digite a quantidade vendida: ";
    cin >> quantidade;
    cout << "Digite o valor do ativo no momento da venda: ";
    cin >> valor;

    int index = buscaBinaria(ativos, ticket, 0, ativos.size() - 1);

    if (index != -1) {
        Ativo& ativo = ativos[index];
        if (ativo.quantidade >= quantidade) {
            ativo.quantidade -= quantidade;
            cout << "Venda registrada com sucesso!" << endl;
        } else {
            cout << "Erro: Quantidade insuficiente para realizar a venda." << endl;
        }
    } else {
        cout << "Erro: Ativo nao encontrado." << endl;
    }
}

void verSaldo(const vector<Ativo>& ativos) {
    string ticket;
    cout << "Digite o ticket do ativo: ";
    cin >> ticket;

    int index = buscaBinaria(ativos, ticket, 0, ativos.size() - 1);

    if (index != -1) {
        const Ativo& ativo = ativos[index];
        cout << "Ticket: " << ativo.ticket << ", Quantidade: " << ativo.quantidade << ", Preco Medio: " << ativo.precoMedio << endl;
    } else {
        cout << "Erro: Ativo nao encontrado." << endl;
    }
}

void listarPatrimonio(const vector<Ativo>& ativos) {
    if (ativos.empty()) {
        cout << "Nenhum ativo registrado." << endl;
        return;
    }

    cout << "Patrimonio do Investidor:" << endl;
    for (const auto& ativo : ativos) {
        cout << "Ticket: " << ativo.ticket << ", Quantidade: " << ativo.quantidade << ", Preco Medio: " << ativo.precoMedio << endl;
    }
}

int main() {
    vector<Ativo> ativos;
    int opcao;

    do {
        cout << "\nMenu:" << endl;
        cout << "1. Registrar Compra" << endl;
        cout << "2. Registrar Venda" << endl;
        cout << "3. Ver Saldo de um Ativo" << endl;
        cout << "4. Listar Patrimonio" << endl;
        cout << "5. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                registrarCompra(ativos);
                break;
            case 2:
                registrarVenda(ativos);
                break;
            case 3:
                verSaldo(ativos);
                break;
            case 4:
                listarPatrimonio(ativos);
                break;
            case 5:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
        }
    } while (opcao != 5);

    return 0;
}
