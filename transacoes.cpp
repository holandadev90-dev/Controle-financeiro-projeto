#include "transacoes.h"
#include "banco.h"
#include <iostream>

using namespace std;

void Valordeposito()
{
    double deposito;
    cout << "\n=========== DEPOSITO ==========\n";
    cout << "Digite o valor para deposito: ";
    cin >> deposito;

    if (deposito <= 0)
    {
        cout << "Digite um valor maior que zero!\n";
    }
    else
    {
        saldo += deposito;
        atualizarDadosUsuario();
        registrarTransacao("DEPOSITO", deposito, "Deposito");
        cout << "Seu saldo atual e: " << saldo << endl;
    }
}

void saque()
{
    double sacar;
    cout << "\n=========== SAQUE ===========\n";
    cout << "Seu saldo atual e R$: " << saldo << endl;
    cout << "Digite um valor para sacar: ";
    cin >> sacar;

    if (sacar <= 0)
    {
        cout << "\nDigite um valor maior que zero!\n";
    }
    else if (sacar > saldo)
    {
        cout << "\n======= VALOR INVALIDO ========\n";
        cout << "Saldo insuficiente!\n";
    }
    else
    {
        cin.ignore();
        string categoria;
        cout << "Digite a categoria/descricao do gasto (ex: Mercado, Lanche, Gasolina): ";
        getline(cin, categoria);

        if (categoria.empty())
        {
            categoria = "Geral";
        }

        saldo -= sacar;
        total += sacar;

        atualizarDadosUsuario();
        registrarTransacao("SAQUE", sacar, categoria);

        cout << "\n== SAQUE REALIZADO COM SUCESSO ==\n";
        cout << "Seu valor atualizado e R$: " << saldo << endl;
    }
}

void totalgastoo()
{
    cout << "\n============= TOTAL ============\n";
    cout << "\nSeu total gasto e: " << total << endl;
}

void totalextrato()
{
    cout << "\n=========== EXTRATO ============\n";

    string sql = "SELECT valor, data, categoria FROM transacoes WHERE usuario_id = " +
                 to_string(idUsuarioLogado) + " AND tipo = 'SAQUE' ORDER BY id DESC LIMIT 3;";

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    int contador = 1;
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        double valor = sqlite3_column_double(stmt, 0);

        const char *txtData = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        string data = txtData ? txtData : "N/A";

        const char *txtCat = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        string categoria = txtCat ? txtCat : "Outros";

        cout << "Saque " << contador << ": R$" << valor
             << " | " << data
             << " | Categoria: " << categoria << endl;

        contador++;
    }
    sqlite3_finalize(stmt);

    if (contador == 1)
    {
        cout << "Nenhum saque realizado ate o momento.\n";
    }

    cout << "\nSeu saldo atual e:   R$" << saldo << endl;
    cout << "Total gasto:         R$" << total << endl;
}