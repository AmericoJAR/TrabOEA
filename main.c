/******************************************************************
04/06/2016                   TrabOEA                    04/06/2016
-------------------------------------------------------------------
Programa..: TrabOEA
Autor.....: José Américo Rodrigues
Finalidade: Pesquisa de registros em um arquivo não ordenado de CEPs
            através de tabela hash
******************************************************************/
#include <cep.h>
#include <util.h>
#include <hash.h>

#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main() {
    int opcao;  // Guarda a opção do menu

    // Abertura dos arquivos
    abreCep();
    abreHash();
    // Loop para continuação da exibição do menu
    do {
        opcao = menu();
        switch(opcao){
            case 1: pesquisaHash();     break;
            case 2: estatisticasHash(); break;
            case 3: listaCep();         break;
            case 4: pesquisaListaCep("48010140");  break;
            case 5: listaHash();        break;
            case 0: sair();             break;
            default:
                printf("Opcao invalida!\n");
                pausa();
                break;
        }
    } while(opcao != 0);  //Condição de saída
	return 0;
}

/******************************************************************
Função....: sair
Finalidade: Finaliza as operações no arquivo de CEPs
******************************************************************/
int sair() {
	fechaCep();    // Fecha o arquivo de CEPs
	fechaHash();   // Fecha o arquivo de ordenação (hash)
    return 1;
}
