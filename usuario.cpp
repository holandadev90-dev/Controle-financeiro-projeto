#include "usuario.h"
#include "banco.h"
#include <iostream>

using namespace std;

void cadastro()
{
    string LoginDigitado, senhaCadastrada, senhaConfirmacao;

    cout << "\n=========== CADASTRO ===========\n";
    cout << "Digite um Nome de usuario: ";
    getline(cin >> ws, usuarioCadastrado);

    cout << "Escolha um Login para acessar o sistema: ";
    cin >> LoginDigitado;

    cout << "Digite uma senha: ";
    cin >> senhaCadastrada;

    cout << "Confirme a Senha: ";
    cin >> senhaConfirmacao;

    while (senhaCadastrada != senhaConfirmacao)
    {
        cout << "\nAs senhas nao conferem. Digite novamente a senha: ";
        cin >> senhaCadastrada;
        cout << "Confirme a Senha: ";
        cin >> senhaConfirmacao;
    }

    string sql = "INSERT INTO usuarios (nome, login, senha, saldo, total_gasto) VALUES ('" +
                 usuarioCadastrado + "', '" + LoginDigitado + "', '" + senhaCadastrada + "', 0.0, 0.0);";

    char *mensagemErro = nullptr;
    int res = sqlite3_exec(db, sql.c_str(), NULL, 0, &mensagemErro);

    if (res == SQLITE_OK)
    {
        cout << "\n ====== CADASTRO REALIZADO COM SUCESSO! ======\n";
        cout << "Bem Vindo(a) Ao nosso Controle Financeiro " << usuarioCadastrado << "!\n";
    }
    else
    {
        cout << "\n[ERRO AO CADASTRAR]: O Login '" << LoginDigitado << "' ja existe no banco.\n";
        if (mensagemErro)
            sqlite3_free(mensagemErro);
    }
}

bool login()
{
    string LoginEntrada, SenhaEntrada;

    cout << "\n============ LOGIN DE ACESSO ============\n";
    cout << "Digite seu Login: ";
    cin >> LoginEntrada;
    cout << "Digite sua Senha: ";
    cin >> SenhaEntrada;

    string sql = "SELECT id, nome, saldo, total_gasto FROM usuarios WHERE login = '" + LoginEntrada + "' AND senha = '" + SenhaEntrada + "';";

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        idUsuarioLogado = sqlite3_column_int(stmt, 0);
        usuarioCadastrado = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        saldo = sqlite3_column_double(stmt, 2);
        total = sqlite3_column_double(stmt, 3);

        cout << "\n======= LOGIN REALIZADO COM SUCESSO! =======\n";
        sqlite3_finalize(stmt);
        return true;
    }
    else
    {
        cout << "\n======== LOGIN OU SENHA INCORRETOS! ========\n";
        sqlite3_finalize(stmt);
        return false;
    }
}

void deslogar()
{
    idUsuarioLogado = -1;
    usuarioCadastrado = "";
    saldo = 0.0;
    total = 0.0;
    cout << "\n======= LOGOUT REALIZADO COM SUCESSO! =======\n";
}