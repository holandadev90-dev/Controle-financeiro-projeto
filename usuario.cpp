#include "usuario.h"
#include "banco.h"
#include <iostream>

using namespace std;

void cadastro()
{
    string LoginDigitado, senhaCadastrada, senhaConfirmacao;

    cout << "\n==================================================\n";
    cout << "                 NOVO CADASTRO\n";
    cout << "==================================================\n";

    cout << "\nCrie sua conta para acessar o Controle Financeiro.\n";

    cout << "\n--------------------------------------------------\n";
    cout << "Nome de usuario: ";
    getline(cin >> ws, usuarioCadastrado);

    cout << "Login: ";
    cin >> LoginDigitado;

    cout << "Senha: ";
    cin >> senhaCadastrada;

    cout << "Confirmar senha: ";
    cin >> senhaConfirmacao;

    while (senhaCadastrada != senhaConfirmacao)
    {
        cout << "\n--------------------------------------------------\n";
        cout << "ERRO: As senhas nao conferem!\n";
        cout << "--------------------------------------------------\n";

        cout << "\nDigite novamente a senha: ";
        cin >> senhaCadastrada;

        cout << "Confirme a senha: ";
        cin >> senhaConfirmacao;
    }

    string sql = "INSERT INTO usuarios (nome, login, senha, saldo, total_gasto) VALUES ('" +
                 usuarioCadastrado + "', '" + LoginDigitado + "', '" + senhaCadastrada + "', 0.0, 0.0);";

    char *mensagemErro = nullptr;
    int res = sqlite3_exec(db, sql.c_str(), NULL, 0, &mensagemErro);

    if (res == SQLITE_OK)
    {
        cout << "\n==================================================\n";
        cout << "             CADASTRO REALIZADO!\n";
        cout << "==================================================\n";

        cout << "\nBem-vindo(a), " << usuarioCadastrado << "!\n";
        cout << "Sua conta foi criada com sucesso.\n";
        cout << "Agora voce ja pode acessar o sistema.\n";

        cout << "\n==================================================\n";
    }
    else
    {
        cout << "\n==================================================\n";
        cout << "                 ERRO NO CADASTRO\n";
        cout << "==================================================\n";

        cout << "\nO login '" << LoginDigitado
             << "' ja existe no sistema ,tente novamente.\n";

        cout << "\nEscolha outro login e tente novamente.\n";

        cout << "\n==================================================\n";

        if (mensagemErro)
            sqlite3_free(mensagemErro);
    }
}

bool login()
{
    string LoginEntrada, SenhaEntrada;

    cout << "\n==================================================\n";
    cout << "                  LOGIN DE ACESSO\n";
    cout << "==================================================\n";

    cout << "\nDigite seus dados para acessar sua conta.\n";

    cout << "\n--------------------------------------------------\n";
    cout << "Login: ";
    cin >> LoginEntrada;

    cout << "Senha: ";
    cin >> SenhaEntrada;

    cout << "\n--------------------------------------------------\n";

    string sql = "SELECT id, nome, saldo, total_gasto FROM usuarios WHERE login = '" + LoginEntrada + "' AND senha = '" + SenhaEntrada + "';";

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        idUsuarioLogado = sqlite3_column_int(stmt, 0);
        usuarioCadastrado = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        saldo = sqlite3_column_double(stmt, 2);
        total = sqlite3_column_double(stmt, 3);

        cout << "\n==================================================\n";
        cout << "             LOGIN REALIZADO COM SUCESSO!\n";
        cout << "==================================================\n";

        cout << "\nBem-vindo(a), " << usuarioCadastrado << "!\n";
        cout << "Acesso autorizado ao Controle Financeiro.\n";

        cout << "\n==================================================\n";

        sqlite3_finalize(stmt);
        return true;
    }
    else
    {
        cout << "\n==================================================\n";
        cout << "                 ACESSO NEGADO\n";
        cout << "==================================================\n";

        cout << "\nLogin ou senha incorretos.\n";
        cout << "Verifique seus dados e tente novamente.\n";

        cout << "\n==================================================\n";

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

    cout << "\n==================================================\n";
    cout << "                  SESSAO ENCERRADA\n";
    cout << "==================================================\n";

    cout << "\nLogout realizado com sucesso!\n";
    cout << "Ate a proxima visita.\n";

    cout << "\n==================================================\n";
}