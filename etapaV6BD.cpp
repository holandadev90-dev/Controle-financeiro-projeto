#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <string>
#include "sqlite3.h"

using namespace std;

// PONTEIRO DO BANCO DE DADOS //
sqlite3 *db;

/// PROTOTIPOS ///
void inicializarBanco();
void Menu();
void Valordeposito();
void saque();
void totalgastoo();
void totalextrato();
void cadastro();
bool login();
void atualizarDadosUsuario();
void registrarTransacao(string tipo, double valor);
void deslogar();

// VARIAVEIS GLOBAIS //
int idUsuarioLogado = -1; // Guarda o ID do usuario logado para salvar as alteracoes
string senhaConfirmacao = "";
string usuarioCadastrado = "";
string senhaCadastrada = "";
string LoginDigitado = "";

string ObterDataeHora()
{
    time_t agora = time(0);
    tm *dataHora = localtime(&agora);

    stringstream ss;

    ss << setw(2) << setfill('0') << dataHora->tm_mday << "/";
    ss << setw(2) << setfill('0') << dataHora->tm_mon + 1 << "/";
    ss << dataHora->tm_year + 1900 << " ";

    ss << setw(2) << setfill('0') << dataHora->tm_hour << ":";
    ss << setw(2) << setfill('0') << dataHora->tm_min << ":";
    ss << setw(2) << setfill('0') << dataHora->tm_sec;

    return ss.str();
}

// VARIAVEIS NUMERICAS //
int opcao;
double total = 0, saldo = 0, sacar, deposito;

void inicializarBanco()
{
    int res = sqlite3_open("financeiro.db", &db);
    if (res != SQLITE_OK)
        return;

    // Tabela de Usuarios
    string sqlUsuarios = "CREATE TABLE IF NOT EXISTS usuarios ("
                         "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                         "nome TEXT NOT NULL, "
                         "login TEXT UNIQUE NOT NULL, "
                         "senha TEXT NOT NULL, "
                         "saldo REAL DEFAULT 0.0, "
                         "total_gasto REAL DEFAULT 0.0);";

    // Nova Tabela de Transações
    string sqlTransacoes = "CREATE TABLE IF NOT EXISTS transacoes ("
                           "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                           "usuario_id INTEGER, "
                           "tipo TEXT, "
                           "valor REAL, "
                           "data TEXT, "
                           "FOREIGN KEY(usuario_id) REFERENCES usuarios(id));";

    char *mensagemErro = nullptr;
    sqlite3_exec(db, sqlUsuarios.c_str(), NULL, 0, &mensagemErro);
    sqlite3_exec(db, sqlTransacoes.c_str(), NULL, 0, &mensagemErro);
}

// Atualiza saldo e total gasto no banco ao depositar ou sacar

void registrarTransacao(string tipo, double valor)
{
    string dataHora = ObterDataeHora();
    string sql = "INSERT INTO transacoes (usuario_id, tipo, valor, data) VALUES (" +
                 to_string(idUsuarioLogado) + ", '" + tipo + "', " +
                 to_string(valor) + ", '" + dataHora + "');";

    char *mensagemErro = nullptr;
    sqlite3_exec(db, sql.c_str(), NULL, 0, &mensagemErro);
    if (mensagemErro)
        sqlite3_free(mensagemErro);
}

void atualizarDadosUsuario()
{
    string sql = "UPDATE usuarios SET saldo = " + to_string(saldo) +
                 ", total_gasto = " + to_string(total) +
                 " WHERE id = " + to_string(idUsuarioLogado) + ";";

    char *mensagemErro = nullptr;
    sqlite3_exec(db, sql.c_str(), NULL, 0, &mensagemErro);
    if (mensagemErro)
        sqlite3_free(mensagemErro);
}

bool login()
{
    string LoginEntrada, SenhaEntrada;

    cout << "\n============ LOGIN DE ACESSO ============\n";
    cout << "Digite seu Login: ";
    cin >> LoginEntrada;
    cout << "Digite sua Senha: ";
    cin >> SenhaEntrada;

    // Busca ID, Nome, Saldo e Total Gasto salvos no banco
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

void cadastro()
{
    cout << "\n=========== CADASTRO ===========\n";
    cout << "Digite um Nome de usuario: ";
    getline(cin >> ws, usuarioCadastrado); // Permite nomes com espaço

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

void Menu()
{
    do
    {
        cout << fixed << setprecision(2);

        cout << "\n======== MENU DE OPCOES =========";
        cout << "\nBem-Vindo(a), " << usuarioCadastrado << "!\n";
        cout << "\nData e Hora: " << ObterDataeHora() << endl;
        cout << "\nSeu saldo e  R$: " << saldo << endl;
        cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-";
        cout << "\n1 - (DEPOSITAR)\n";
        cout << "\n2 - (SACAR)\n";
        cout << "\n3 - (Total gasto)\n";
        cout << "\n4 - (Extrato total)\n";
        cout << "\n5 - (Logout)\n";
        cout << "\n6 - (Sair)\n";
        cout << "\nOpcao: ";

        cin >> opcao;

        if (opcao == 1)
            Valordeposito();
        else if (opcao == 2)
            saque();
        else if (opcao == 3)
            totalgastoo();
        else if (opcao == 4)
            totalextrato();
        else if (opcao == 5)
        {
            deslogar();
            return; // Retorna ao menu inicial
        }
        else if (opcao == 6)
        {
            cout << "\n======= SAINDO DO SISTEMA =======\n";
        }
        else
            cout << "\n======= OPCAO INVALIDA! =======\n";

    } while (opcao != 5 && opcao != 6);
}

void Valordeposito()
{
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
        atualizarDadosUsuario();                  // Grava o novo saldo no banco
        registrarTransacao("DEPOSITO", deposito); // Grava o historico no banco
        cout << "Seu saldo atual e: " << saldo << endl;
    }
}

void saque()
{
    cout << "\n=========== SAQUE ===========\n";
    cout << "Seu saldo atual e " << saldo << endl;
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
        saldo -= sacar;
        total += sacar;

        // Grava o novo saldo/total no usuario
        atualizarDadosUsuario();

        // Registra a movimentacao no historico do banco
        registrarTransacao("SAQUE", sacar);

        cout << "\n== SAQUE REALIZADO COM SUCESSO ==\n";
        cout << "Seu valor atualizado e: " << saldo << endl;
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

    // Busca os ultimos 3 saques ordenados do mais recente para o mais antigo
    string sql = "SELECT valor, data FROM transacoes WHERE usuario_id = " +
                 to_string(idUsuarioLogado) + " AND tipo = 'SAQUE' ORDER BY id DESC LIMIT 3;";

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);

    int contador = 1;
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        double valor = sqlite3_column_double(stmt, 0);
        string data = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));

        cout << "Saque " << contador << ": R$" << valor << " | " << data << endl;
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

void deslogar()
{
    idUsuarioLogado = -1;
    usuarioCadastrado = "";
    saldo = 0.0;
    total = 0.0;
    cout << "\n======= LOGOUT REALIZADO COM SUCESSO! =======\n";
}

int main()
{
    inicializarBanco();

    int opcaoInicial;

    // Loop principal da aplicacao (permite deslogar e voltar ao menu)
    while (true)
    {
        do
        {
            cout << "\n===== CONTROLE FINANCEIRO =====\n";
            cout << "\n1 - (CADASTRO)\n";
            cout << "\n2 - (LOGIN)\n";
            cout << "\n3 - (SAIR)\n";
            cout << "\nEscolha uma opcao: ";
            cin >> opcaoInicial;

            if (opcaoInicial == 1)
            {
                cadastro();
            }
            else if (opcaoInicial == 2)
            {
                if (login())
                {
                    break; // Sai do do/while inicial para ir para o Menu principal
                }
            }
            else if (opcaoInicial == 3)
            {
                cout << "\n ======= PROGRAMA ENCERRADO! ========\n";
                sqlite3_close(db);
                return 0;
            }
            else
            {
                cout << "\n ======= OPCAO INVALIDA! ========\n";
            }

        } while (opcaoInicial != 3);

        // Se o saldo do usuario for 0 (novo cadastro), solicita o saldo inicial
        if (saldo == 0)
        {
            cout << "\nDigite seu saldo inicial: ";
            cin >> saldo;
            atualizarDadosUsuario();
        }

        // Abre o menu principal do usuario
        Menu();

        // Se a opcao escolhida no Menu() foi 6 (Sair do Programa), quebra o loop principal
        if (opcao == 6)
        {
            break; // break esta dentro do loop "while (true)"
        }
    }

    cout << "\n====== ======= ====== ====== ======";
    cout << "\n======= Controle encerrado! =======" << endl;
    cout << "====== ======= ====== ====== ======\n";

    sqlite3_close(db);
    return 0;
}