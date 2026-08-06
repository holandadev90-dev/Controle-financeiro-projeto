#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
using namespace std;
string dataSaque1;
string dataSaque2;
string dataSaque3;
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


    int opcao;
    double total = 0, saldo = 0, sacar, deposito; // Dinheiro
    double saque1 = 0, saque2 = 0, saque3 = 0;    // Historico de saques
    int quantidadeSaques = 0;

void Valordeposito()
{
    double deposito;
    
        {

            cout << "\n=========== DEPOSITO ==========\n";
            cout << "Digite o valor para deposito: ";
            cin >> deposito;

            if (deposito <= 0)
            {
                cout << "Digite um valor maior que zero!\n\n";
            }

            else
            {
                saldo += deposito;
                cout << "Seu saldo atual e: " << saldo << endl;
            }
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
                cout << "Seu saldo atual e " << saldo << endl;
                cout << "===============================\n";
            }
            else
            {
                saldo -= sacar;
                total += sacar;

                saque3 = saque2;
                saque2 = saque1;
                saque1 = sacar;


                dataSaque3 = dataSaque2;
                dataSaque2 = dataSaque1;
                dataSaque1 = ObterDataeHora();

                quantidadeSaques++;

                cout << "===============================\n";
                cout << "== SAQUE REALIZADO COM SUCESSO ==\n\n";
                cout << "Seu valor atualizado e: " << saldo << endl;               
                cout << "===============================\n";
                cout << "Quantidade de saques realizados: " << quantidadeSaques << endl;
            }
        }
void totalgastoo()


{
    cout << "============= TOTAL ============\n\n";
    cout << "Seu total gasto e: " << total << endl;
    cout << "================================\n";
}
void mostrardataehora()
{
 time_t agora = time(0);
    tm *dataHora = localtime(&agora);

    cout <<dataHora->tm_mday<<"/";
    cout <<setw(2)<<dataHora->tm_mon+1<<"/";
    cout <<dataHora->tm_year+1900<<" ";

    cout << setw(2) << dataHora->tm_hour <<":";
    cout << setw(2) << dataHora->tm_min <<":";
    cout << setw(2) << dataHora->tm_sec<<""<<endl;
}
void totalextrato()
{
                              
            cout << "\n=========== EXTRATO ============\n";
            cout << "Ultimo saque:        R$" << saque1 << endl;
            cout << "Data e Hora: " << dataSaque1 << endl;
            cout << "\n\n";
            cout << "Penultimo saque:     R$" << saque2 << endl;
            cout << "Data e Hora: " << dataSaque2 << endl;
            cout << "\n\n";
            cout << "Antepenultimo saque: R$" << saque3 << endl;
            cout << "Data e Hora: " << dataSaque3 << endl;
            cout << "\n===============================\n\n";

            cout << "Seu saldo atual e: " << saldo << endl;
            cout << "Total gasto: " << total << endl;
            cout << "Quantidade de saques: " << quantidadeSaques << endl;
            cout << " =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n";
}

int main()
{

    cout << "===== CONTROLE FINANCEIRO =====";
    cout << "\n---------- BEM VINDO  ---------\n";
    cout << "\nDigite seu saldo atual: ";
    cin >> saldo;

    do
    {
        cout << fixed << setprecision(2);

        cout << "======== MENU DE OPCOES =========";
        cout << "\n\nSeu saldo e    R$: " << saldo << endl;
        cout << "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
        cout << "1 - (depositar)\n";
        cout << "2 - (sacar)\n";
        cout << "3 - (Total gasto)\n";
        cout << "4 - (Extrato total)\n";
        cout << "5 - (Sair)\n";
        cout << "---------------------------------\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        if (opcao == 1)
        {
            Valordeposito();            
        }

        else if (opcao == 2)
        {
            saque();
        }

        else if (opcao == 3)
        {
            totalgastoo();
        }

        else if (opcao == 4)
        {
            totalextrato();
        }
        else if (opcao == 5)
        {
            // nao faz nada
        }
        else
        {
            cout << "\n\n======= OPCAO INVALIDA! =======\n\n";
        }

    } while (opcao != 5);

    cout << "====== ======= ====== ====== ======";
    cout << "\n======== Controle encerrado! ======" << endl;
    cout << "====== ======= ====== ====== ======";
    return 0;
}



