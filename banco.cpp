#include "banco.h"
#include <iomanip>
#include <ctime>
#include <sstream>

// Definição real das variáveis globais
sqlite3 *db = nullptr;
int idUsuarioLogado = -1;
string usuarioCadastrado = "";
double saldo = 0.0;
double total = 0.0;

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

void inicializarBanco()
{
    int res = sqlite3_open("financeiro.db", &db);
    if (res != SQLITE_OK)
        return;

    string sqlUsuarios = "CREATE TABLE IF NOT EXISTS usuarios ("
                         "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                         "nome TEXT NOT NULL, "
                         "login TEXT UNIQUE NOT NULL, "
                         "senha TEXT NOT NULL, "
                         "saldo REAL DEFAULT 0.0, "
                         "total_gasto REAL DEFAULT 0.0);";

    string sqlTransacoes = "CREATE TABLE IF NOT EXISTS transacoes ("
                           "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                           "usuario_id INTEGER, "
                           "tipo TEXT, "
                           "valor REAL, "
                           "data TEXT, "
                           "categoria TEXT DEFAULT 'Outros', "
                           "FOREIGN KEY(usuario_id) REFERENCES usuarios(id));";

    char *mensagemErro = nullptr;
    sqlite3_exec(db, sqlUsuarios.c_str(), NULL, 0, &mensagemErro);
    sqlite3_exec(db, sqlTransacoes.c_str(), NULL, 0, &mensagemErro);

    string sqlAlter = "ALTER TABLE transacoes ADD COLUMN categoria TEXT DEFAULT 'Outros';";
    sqlite3_exec(db, sqlAlter.c_str(), NULL, 0, &mensagemErro);

    if (mensagemErro)
    {
        sqlite3_free(mensagemErro);
    }
}

void registrarTransacao(string tipo, double valor, string categoria)
{
    string dataHora = ObterDataeHora();

    if (categoria.empty())
    {
        categoria = "Outros";
    }

    string sql = "INSERT INTO transacoes (usuario_id, tipo, valor, data, categoria) VALUES (" +
                 to_string(idUsuarioLogado) + ", '" + tipo + "', " +
                 to_string(valor) + ", '" + dataHora + "', '" + categoria + "');";

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