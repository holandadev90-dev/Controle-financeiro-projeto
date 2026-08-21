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
            return;
        }
        else if (opcao == 6)
        {
            cout << "\n======= SAINDO DO SISTEMA =======\n";
        }
        else
            cout << "\n======= OPCAO INVALIDA! =======\n";

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
                    break;
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

    cout << "\n====== ======= ====== ====== ======";
    cout << "\n======= Controle encerrado! =======" << endl;
    cout << "====== ======= ====== ====== ======\n";

    sqlite3_close(db);
    return 0;
}