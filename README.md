# Controle Financeiro em C++

Sistema de controle financeiro pessoal desenvolvido em C++ modularizado com banco de dados SQLite.

## 🚀 Funcionalidades
- Cadastro e login de usuários
- Depósitos e saques com categorização de gastos
- Consulta de saldo, total gasto e extrato recente
- Persistência de dados em SQLite

## 📁 Estrutura do Projeto
- `main.cpp`: Fluxo do menu principal.
- `usuario.cpp` / `usuario.h`: Gerenciamento de login, cadastro e sessão.
- `transacoes.cpp` / `transacoes.h`: Operações de depósito, saque e extrato.
- `banco.cpp` / `banco.h`: Conexão e rotinas com o banco SQLite.
- `sqlite3.c` / `sqlite3.h`: Biblioteca SQLite.

## 🛠️ Como Compilar e Executar

### Pré-requisitos
- Compilador GCC/G++ instâncias no sistema.

### Passo a Passo no Terminal

1. Compilar o arquivo C do SQLite:
   ```bash
   gcc -c sqlite3.c -o sqlite3.o