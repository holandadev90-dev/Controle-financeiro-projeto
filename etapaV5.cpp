#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <string>
using namespace std;

/// PROTOTIPOS ///
void Menu();
void Valordeposito();
void saque();
void totalgastoo();
void totalextrato();
void cadastro();
bool login();

// VARIAVEIS DO TIPO STRING//

string senhaConfirmacao = "";
string usuarioCadastrado = "";
string senhaCadastrada = "";
string LoginDigitado = "";
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
//==========================//

// VARIAVEIS DO TIPO INT E DOUBLE "NUMEROS"//
int opcao;
double total = 0, saldo = 0, sacar, deposito; // Dinheiro
double saque1 = 0, saque2 = 0, saque3 = 0;    // Historico de saques
int quantidadeSaques = 0;
//=======================================//

bool login()
{
    // Apenas as variaveis que serao digitadas AGORA sao declaradas aqui
    string LoginDigitado, SenhaDigitada;

    cout << "\n============ LOGIN DE ACESSO ============\n";
    cout << "Digite seu Login: ";
    cin >> LoginDigitado;
    cout << "Digite sua Senha: ";
    cin >> SenhaDigitada;

    // Agora sim ele compara com as variaveis GLOBAIS salvas no cadastro!
    if (LoginDigitado == usuarioCadastrado && SenhaDigitada == senhaCadastrada)
    {
        cout << "\n======= LOGIN REALIZADO COM SUCESSO! =======\n";
        return true;
    }
    else
    {
        cout << "\n======== LOGIN OU SENHA INCORRETOS! ========\n";
        return false;
    }
}
void cadastro()
{
    cout << "\n=========== CADASTRO ===========\n";
    cout << "\nDigite um Nome de usuario: \n";
    getline(cin >> ws, usuarioCadastrado); // Permite espaços no nome do usuário
    cout << "\nEscolha um Login para acessar o sistema: \n";
    getline(cin >> ws, LoginDigitado);
    cout << "\nDigite uma senha: \n";
    cin >> senhaCadastrada;
    cout << "\nConfirme a Senha: \n";
    cin >> senhaConfirmacao;

    // Verificar se a senha e a confirmação são iguais
    while (senhaCadastrada != senhaConfirmacao)
    {
        cout << "As senhas nao conferem. Digite novamente a senha: ";
        cin >> senhaCadastrada;
        cout << "Confirme a Senha: ";
        cin >> senhaConfirmacao;
    }

    cout << "\n ====== CADASTRO REALIZADO COM SUCESSO! ======\n";
    cout << "Bem Vindo(a) Ao nosso Controle Financeiro " << usuarioCadastrado << "!\n";
}

void Menu()
{
    do
    {
        cout << fixed << setprecision(2);

        cout << "======== MENU DE OPCOES =========";
        cout << "\n\nSeu saldo e  R$: " << saldo << endl;
        cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-";
        cout << "\n1 - (DEPOSITAR)\n";
        cout << "2 - (SACAR)\n";
        cout << "3 - (Total gasto)\n";
        cout << "4 - (Extrato total)\n";
        cout << "5 - (Sair)\n";

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
}
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

    cout << dataHora->tm_mday << "/";
    cout << setw(2) << dataHora->tm_mon + 1 << "/";
    cout << dataHora->tm_year + 1900 << " ";

    cout << setw(2) << dataHora->tm_hour << ":";
    cout << setw(2) << dataHora->tm_min << ":";
    cout << setw(2) << dataHora->tm_sec << "" << endl;
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

    int opcaoInicial;

    cout << "===== CONTROLE FINANCEIRO =====";
    cout << "\n -------- BEM VINDO ----------\n";
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
        if (!login())
        {
            cout << "\n ======= LOGIN OU SENHA INCORRETOS! ========\n";
            return 0; // Encerra o programa se o login falhar
        }
    }
    else if (opcaoInicial == 3)
    {
        cout << "\n ======= PROGRAMA ENCERRADO! ========\n";
        return 0; // Encerra o programa se a opção inicial for sair
    }

    else
    {
        cout << "\n ======= OPCAO INVALIDA! ========\n";
        return 0; // Encerra o programa se a opção inicial for inválida
    }

    cout << "===== CONTROLE FINANCEIRO =====";
    cout << "\n---------- BEM VINDO  ---------\n";
    cout << "\nDigite seu saldo atual: ";
    cin >> saldo;

    Menu();

    cout << "====== ======= ====== ====== ======";
    cout << "\n======= Controle encerrado! =======" << endl;
    cout << "====== ======= ====== ====== ======";
    return 0;
}
