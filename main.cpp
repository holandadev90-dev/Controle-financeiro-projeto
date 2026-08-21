#include <iostream>
#include <iomanip>
#include "banco.h"
#include "usuario.h"
#include "transacoes.h"

using namespace std;

static int opcao = 0;

void Menu()
{
    do
    {
        cout << fixed << setprecision(2);

        cout << "\n==================================================\n";
        cout << "              MENU DE OPCOES\n";
        cout << "==================================================\n";

        cout << "\nBem-vindo(a), " << usuarioCadastrado << "!";
        cout << "\nData e hora: " << ObterDataeHora();
        cout << "\nSaldo atual: R$ " << saldo << "\n";

        cout << "\n--------------------------------------------------\n";

        cout << "\n[1] Depositar\n";
        cout << "[2] Sacar\n";
        cout << "[3] Total gasto\n";
        cout << "[4] Extrato total\n";
        cout << "[5] Logout\n";
        cout << "[6] Sair\n";

        cout << "\n--------------------------------------------------\n";
        cout << "Opcao: ";

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
            return;
        }
        else if (opcao == 6)
        {
            cout << "\n==================================================\n";
            cout << "                 SAINDO DO SISTEMA\n";
            cout << "==================================================\n";

            cout << "\nObrigado por utilizar o Controle Financeiro!\n";
            cout << "Ate a proxima!\n";

            cout << "\n==================================================\n";
        }
        else
        {
            cout << "\n==================================================\n";
            cout << "                  OPCAO INVALIDA\n";
            cout << "==================================================\n";

            cout << "\nA opcao informada nao existe.\n";
            cout << "Escolha uma opcao valida no menu.\n";

            cout << "\n==================================================\n";
        }

    } while (opcao != 5 && opcao != 6);
}

int main()
{
    inicializarBanco();

    int opcaoInicial;

    while (true)
    {
        do
        {
            cout << "\n==================================================\n";
            cout << "           FINANCE CONTROL              \n";
            cout << "       Seu dinheiro, seu controle.      \n";
            cout << "==================================================\n";

            cout << "\n[1] Cadastro\n";
            cout << "[2] Login\n";
            cout << "[3] Sair\n";

            cout << "\n>> Escolha uma opcao: ";
            cin >> opcaoInicial;

            if (opcaoInicial == 1)
            {
                cadastro();
            }
            else if (opcaoInicial == 2)
            {
                if (login())
                {
                    break;
                }
            }
            else if (opcaoInicial == 3)
            {
                cout << "\n==================================================\n";
                cout << "       CONTROLE FINANCEIRO ENCERRADO\n";
                cout << "==================================================\n";
                cout << "       Obrigado por utilizar!\n";
                cout << "==================================================\n";

                sqlite3_close(db);
                return 0;
            }
            else
            {
                cout << "\n ======= OPCAO INVALIDA! ========\n";
            }

        } while (opcaoInicial != 3);

        if (saldo == 0)
        {
            cout << "\nDigite seu saldo inicial: ";
            cin >> saldo;
            atualizarDadosUsuario();
        }

        Menu();

        if (opcao == 6)
        {
            break;
        }
    }

    cout << "\n========================================\n";
    cout << "       CONTROLE FINANCEIRO ENCERRADO   \n";
    cout << "========================================\n";
    cout << "        Obrigado por utilizar!\n";
    cout << "========================================\n";

    sqlite3_close(db);
    return 0;
}