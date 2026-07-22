#include <iostream>
#include <iomanip>
using namespace std;


int main (){

    int opcao;
    double total = 0 , saldo = 0 , sacar , deposito;     // Dinheiro
    double saque1 = 0 , saque2 = 0 , saque3 = 0;        // Historico de saques 
    int quantidadeSaques = 0;

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
                 
                else if (opcao == 2)
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

                quantidadeSaques++;

                cout << "===============================\n";
                cout << "== SAQUE REALIZADO COM SUCESSO ==\n\n";
                cout << "Seu valor atualizado e: " << saldo << endl;
                cout << "===============================\n";
                cout << "Quantidade de saques realizados: "  << quantidadeSaques << endl;
                                        
                }
                }

                else if (opcao == 3)
                {
                    cout << "============= TOTAL ============\n\n";
                    cout << "Seu total gasto e: " << total << endl;
                    cout << "================================\n";
                }

                else if (opcao == 4)
                {
                    cout << "\n=========== EXTRATO ============\n";
                    cout << "Ultimo saque:        R$" << saque1 << endl;
                    cout << "Penultimo saque:     R$" << saque2 << endl;       
                    cout << "Antepenultimo saque: R$" << saque3 << endl;
                    cout << "\n===============================\n\n";

                    cout << "Seu saldo atual e: " << saldo << endl;
                    cout << "Total gasto: " << total << endl;
                    cout << "Quantidade de saques: " << quantidadeSaques << endl;
                    cout << " =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n";
                }
                else if (opcao == 5)
                {
                  //nao faz nada
                }
                else 
                {
                    cout << "\n\n======= OPCAO INVALIDA! =======\n\n";
                }
               
                } while (opcao != 5);
                    
                    cout << "====== ======= ====== ====== ======";
                    cout << "\n======== Programa encerrado! ======" << endl;
                    cout << "====== ======= ====== ====== ======";
                return 0;
                }
                

