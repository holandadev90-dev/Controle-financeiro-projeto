# 💰 Controle Financeiro em C++ com SQLite

Sistema de gerenciamento financeiro de terminal com persistência de dados em SQLite, suporte a múltiplos usuários, extrato de transações e controle de saldo.

---

## 🚀 Funcionalidades
* **Cadastro e Login:** Validação de credenciais e garantia de login único.
* **Persistência no SQLite:** Saldo, total gasto e histórico gravados no banco de dados.
* **Gestão Financera:** Operações de Depósito, Saque e Exibição de Extrato.
* **Histórico do Banco:** Extrato dos últimos saques ordenados do mais recente para o antigo.
* **Sessão:** Opção de Logout para trocar de usuário sem fechar o programa.

---

## 🛠️ Pré-requisitos
* Compilador GCC/G++ instalado (MinGW no Windows).
* Arquivo do SQLite (`sqlite3.h`, `sqlite3.c` ou `sqlite3.o`) na mesma pasta.

---

## 💻 Como Compilar e Executar

1. **Abra o terminal** na pasta do projeto.

2. **Compile o código** unindo o C++ com a biblioteca do SQLite:
   ```powershell
   g++ etapaV6BD_3.cpp sqlite3.o -o etapaV6BD.exe
   ```

3. **Execute o programa**:
   ```powershell
   .\etapaV6BD.exe
   ```

---

## 📋 Como Usar

### 1️⃣ Tela Inicial
Ao iniciar, escolha uma das opções:
* `1`: Cadastrar nome, login e senha.
* `2`: Fazer login com sua conta.
* `3`: Encerrar a aplicação.

### 2️⃣ Primeiro Acesso
* Se for seu primeiro login, o sistema solicitará o **Saldo Inicial** para configurar a conta no banco de dados.

### 3️⃣ Menu do Usuário
Após logar, navegue pelas opções:
* `1 - DEPOSITAR`: Adiciona saldo e registra no histórico do banco.
* `2 - SACAR`: Realiza saque (valida saldo suficiente) e atualiza o extrato.
* `3 - Total gasto`: Exibe o valor acumulado em saques.
* `4 - Extrato total`: Consulta o histórico das últimas movimentações no banco.
* `5 - Logout`: Desloga e permite entrar com outra conta.
* `6 - Sair`: Encerra o programa.

---

## 🗄️ Estrutura do Banco de Dados (`financeiro.db`)
O sistema cria automaticamente as tabelas:
* `usuarios`: Guarda `id`, `nome`, `login`, `senha`, `saldo` e `total_gasto`.
* `transacoes`: Relaciona movimentações via `usuario_id` (Chave Estrangeira).