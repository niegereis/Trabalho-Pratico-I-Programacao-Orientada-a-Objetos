// Membros do grupo
//  Eduardo Silva
//  Guilherme Souza
//  Niege Reis

#include <stdio.h>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "apartamento.h"
#include "casa.h"
#include "chacara.h"
#include "funcoesAuxiliares.h"
#include "imovel.h"

using namespace std;
using namespace FuncoesAuxiliares;

int main() {
  cout << fixed << setprecision(2);
  string arquivoImoveis = "dataBaseImoveis.txt", linha;
  ifstream arquivo(arquivoImoveis);
  vector<Imovel*> listaDeImoveis;

  if (!arquivo.is_open()) {
    cout << "Erro ao abrir arquivo de imóveis!" << endl;
    return 1;
  }

  int id = 1;
  while (getline(arquivo, linha)) {
    Imovel* imovel = criarImovelPelaLinha(linha, id);
    listaDeImoveis.push_back(imovel);
    id++;
  }
  arquivo.close();

  int opcao;
  do {
    cout << "------------------------------------------------------------------"
            "-----------------------"
         << endl;
    cout << "0 - Sair do programa." << endl;
    cout << "1 - Verifica se propietário possui algum imóvel." << endl;
    cout << "2 - Obtêm os imóveis abaixo ou igual a um valor." << endl;
    cout << "3 - Obtêm os imóveis que possuem um número maior ou igual a "
            "quantidade de quartos."
         << endl;
    cout << "4 - Obtêm um lista de imóveis pelo tipo ordenados pelo valor "
            "crescente."
         << endl;
    cout << "5 - Obtêm um lista de imóveis pela cidade e ordena pelo valor "
            "decrescente."
         << endl;
    cout << "6 - Obtêm lista de imóveis pelo proprierário." << endl;
    cout << "7 - Imprime na tela ou salva em um arquivo." << endl;
    cout << "------------------------------------------------------------------"
            "-----------------------"
         << endl;
    cout << "Digite a opção desejada: ";
    cin >> opcao;

    limpaBuffer();

    string proprietario, tipoImovel, cidade, proprietarioBuscado,
        escolhaDoUsuario;
    float valorBuscado;
    int qtQuartosBuscado;

    switch (opcao) {
      case 1: {
        cout << "Digite o nome do proprietário que você deseja buscar: ";
        getline(cin, proprietario);

        if (ehProprietario(listaDeImoveis, proprietario)) {
          cout << "É proprietário!" << endl;
        } else {
          cout << "Não é proprietário!" << endl;
        }
        break;
      }

      case 2: {
        cout << "Digite pelo valor do imóvel que você deseja buscar: ";
        cin >> valorBuscado;
        vector<Imovel*> listaDeImoveisValorBuscado =
            obterListaDeImoveisPeloValor(listaDeImoveis, valorBuscado);
        if (!listaDeImoveisValorBuscado.empty())
          imprimeListaOuSalvaEmArquivo(listaDeImoveisValorBuscado, "imprime");
        else
          cout << "Não existe imovel no intervalo de valor buscado!" << endl;
        limpaBuffer();
        break;
      }

      case 3: {
        cout << "Digite pela quantidade de quartos do imóvel que você deseja "
                "buscar: ";
        cin >> qtQuartosBuscado;
        vector<Imovel*> listaDeImoveisQuartosBuscado =
            obterListaDeImoveisPelaQuantidadeQuartos(listaDeImoveis,
                                                     qtQuartosBuscado);
        cout << "\n\n" << qtQuartosBuscado << endl;
        if (!listaDeImoveisQuartosBuscado.empty())
          imprimeListaOuSalvaEmArquivo(listaDeImoveisQuartosBuscado, "imprime");
        else
          cout << "Não existe imovel no intervalo de quartos buscado!" << endl;
        limpaBuffer();
        break;
      }

      case 4: {
        cout << "Digite pelo tipo do imóvel que você deseja buscar: ";
        getline(cin, tipoImovel);
        vector<Imovel*> listaDeImoveisTipoDoImovelBuscado =
            obterListaDeImoveisPeloTipoDoImovel(listaDeImoveis, tipoImovel);
        if (!listaDeImoveisTipoDoImovelBuscado.empty())
          imprimeListaOuSalvaEmArquivo(listaDeImoveisTipoDoImovelBuscado,
                                       "imprime");
        else
          cout << "Não existe imovel do tipo buscado!" << endl;
        break;
      }

      case 5: {
        cout << "Digite pela cidade em que está o imóvel que você deseja "
                "buscar: ";
        getline(cin, cidade);
        vector<Imovel*> listaDeImoveisCidadeDoImovelBuscado =
            obterListaDeImoveisPelaCidadeDoImovel(listaDeImoveis, cidade);
        if (!listaDeImoveisCidadeDoImovelBuscado.empty())
          imprimeListaOuSalvaEmArquivo(listaDeImoveisCidadeDoImovelBuscado,
                                       "imprime");
        else
          cout << "Não existe imovel da cidade buscada!" << endl;
        break;
      }

      case 6: {
        cout << "Digite pelo proprietário que é dono do imóvel que você deseja "
                "buscar : ";
        getline(cin, proprietarioBuscado);
        vector<vector<Imovel*>::iterator>
            listaDeImoveisProprietarioDoImovelBuscado =
                obterListaDeImoveisPeloProprietarioDoImovel(
                    listaDeImoveis, proprietarioBuscado);
        if (!listaDeImoveisProprietarioDoImovelBuscado.empty())
          imprimeListaDeImoveisIt(listaDeImoveisProprietarioDoImovelBuscado,
                                  &cout);
        else
          cout << "Não existe imovel do proprietário buscado!" << endl;
        break;
      }

      case 7: {
        cout << "Digite 'imprime' para imprimir no terminal ou 'arquivo' para "
                "salvar os dados dos imóveis em um arquivo saida.txt:";
        getline(cin, escolhaDoUsuario);
        imprimeListaOuSalvaEmArquivo(listaDeImoveis, escolhaDoUsuario);
        break;
      }
    }

    if (opcao != 0) {
      cout << "Digite enter para continuar...";
      getchar();
      system("clear");
    }
  } while (opcao != 0);

  for (Imovel* imovel : listaDeImoveis) {
    delete imovel;
  }

  return 0;
}