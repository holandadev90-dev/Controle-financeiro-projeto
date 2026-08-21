#include "transacoes.h"
#include "banco.h"
#include <iostream>

using namespace std;

void Valordeposito()
{
    double deposito;

    cout << "\n==================================================\n";
    cout << "                    DEPOSITO\n";
    cout << "==================================================\n";

    cout << "\nDigite o valor para deposito: R$ ";
    cin >> deposito;

    if (deposito <= 0)
    {
        cout << "\n--------------------------------------------------\n";
        cout << "ERRO: Digite um valor maior que zero!\n";
        cout << "--------------------------------------------------\n";
    }
    else
    {
        saldo += deposito;

        atualizarDadosUsuario();
        registrarTransacao("DEPOSITO", deposito, "Deposito");

        cout << "\n==================================================\n";
        cout << "             DEPOSITO REALIZADO!\n";
        cout << "==================================================\n";

        cout << "\nValor depositado: R$ " << deposito << endl;
        cout << "Saldo atual: R$ " << saldo << endl;

        cout << "\n==================================================\n";
    }
}

void saque()
{
    double sacar;

    cout << "\n==================================================\n";
    cout << "                     SAQUE\n";
    cout << "==================================================\n";

    cout << "\nSaldo atual: R$ " << saldo << endl;
    cout << "Digite o valor para sacar: R$ ";
    cin >> sacar;

    if (sacar <= 0)
    {
        cout << "\n--------------------------------------------------\n";
        cout << "ERRO: Digite um valor maior que zero!\n";
        cout << "--------------------------------------------------\n";
    }
    else if (sacar > saldo)
    {
        cout << "\n==================================================\n";
        cout << "                 SALDO INSUFICIENTE\n";
        cout << "==================================================\n";

        cout << "\nO valor informado e maior que seu saldo atual.\n";
        cout << "Saldo disponivel: R$ " << saldo << endl;

        cout << "\n==================================================\n";
    }
    else
    {
        cin.ignore();

        string categoria;

        cout << "\nCategoria/descricao do gasto:\n";
        cout << "(Ex: Mercado, Lanche, Gasolina)\n";
        cout << "Digite: ";
        getline(cin, categoria);

        if (categoria.empty())
        {
            categoria = "Geral";
        }

        saldo -= sacar;
        total += sacar;

        atualizarDadosUsuario();
        registrarTransacao("SAQUE", sacar, categoria);

        cout << "\n==================================================\n";
        cout << "              SAQUE REALIZADO!\n";
        cout << "==================================================\n";

        cout << "\nValor sacado: R$ " << sacar << endl;
        cout << "Categoria: " << categoria << endl;
        cout << "Saldo atual: R$ " << saldo << endl;

        cout << "\n==================================================\n";
    }
}

void totalgastoo()
{
    cout << "\n==================================================\n";
    cout << "                  RESUMO FINANCEIRO\n";
    cout << "==================================================\n";

    cout << "\nTotal gasto:  R$ " << total << endl;
    cout << "Saldo atual:  R$ " << saldo << endl;

    cout << "\n--------------------------------------------------\n";
    cout << "             CONTINUE NO SISTEMA!\n";
    cout << "--------------------------------------------------\n";
}

void totalextrato()
{
    cout << "\n==================================================\n";
    cout << "                  EXTRATO FINANCEIRO\n";
    cout << "==================================================\n";

    cout << "\nUltimas movimentacoes:\n";
    cout << "--------------------------------------------------\n";

    string sql = "SELECT valor, data, categoria FROM transacoes WHERE usuario_id = " +
                 to_string(idUsuarioLogado) + " AND tipo = 'SAQUE' ORDER BY id DESC LIMIT 3;";

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    int contador = 1;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        double valor = sqlite3_column_double(stmt, 0);

        const char *txtData =
            reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));

        string data = txtData ? txtData : "N/A";

        const char *txtCat =
            reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));

        string categoria = txtCat ? txtCat : "Outros";

        cout << "\n[" << contador << "] SAQUE\n";
        cout << "    Valor:      R$ " << valor << endl;
        cout << "    Data:       " << data << endl;
        cout << "    Categoria:  " << categoria << endl;

        cout << "--------------------------------------------------\n";

        contador++;
    }

    sqlite3_finalize(stmt);

    if (contador == 1)
    {
        cout << "\nNenhum saque realizado ate o momento.\n";
        cout << "--------------------------------------------------\n";
    }

    cout << "\n                 RESUMO FINANCEIRO\n";
    cout << "--------------------------------------------------\n";
    cout << "Saldo atual:    R$ " << saldo << endl;
    cout << "Total gasto:    R$ " << total << endl;

    cout << "\n==================================================\n";
}