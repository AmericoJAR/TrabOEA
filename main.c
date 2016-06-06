/******************************************************************
04/06/2016                   TrabOEA                    04/06/2016
-------------------------------------------------------------------
Programa..: TrabOEA
Autor.....: Jos� Am�rico Rodrigues
Finalidade: Pesquisa de registros em um arquivo n�o ordenado de CEPs
            atrav�s de tabela hash
******************************************************************/
#include <cep.h>
#include <util.h>
#include <hash.h>

#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main() {
    int opcao;  // Guarda a op��o do menu

    // Abertura dos arquivos
    abreCep();
    abreHash();
    // Loop para continua��o da exibi��o do menu
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
    } while(opcao != 0);  //Condi��o de sa�da
	return 0;
}

/******************************************************************
Fun��o....: sair
Finalidade: Finaliza as opera��es no arquivo de CEPs
******************************************************************/
int sair() {
	fechaCep();    // Fecha o arquivo de CEPs
	fechaHash();   // Fecha o arquivo de ordena��o (hash)
    return 1;
}
