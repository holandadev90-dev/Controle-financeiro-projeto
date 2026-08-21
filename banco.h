#ifndef BANCO_H
#define BANCO_H

#include <iostream>
#include <string>
#include "sqlite3.h"

using namespace std;

// Ponteiro do Banco e Variáveis Globais compartilhadas
extern sqlite3 *db;
extern int idUsuarioLogado;
extern string usuarioCadastrado;
extern double saldo;
extern double total;

// Funções de Inicialização e Auxiliares
void inicializarBanco();
string ObterDataeHora();
void atualizarDadosUsuario();
void registrarTransacao(string tipo, double valor, string categoria = "Outros");

#endif