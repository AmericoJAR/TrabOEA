/******************************************************************
04/06/2016                   TrabOEA                    04/06/2016
-------------------------------------------------------------------
Programa..: TrabOEA
Autor.....: José Américo Rodrigues
Finalidade: Pesquisa de registros em um arquivo não ordenado de CEPs
            através de tabela hash
******************************************************************/
#include "cep.h"
#include "util.h"
#include "hash.h"

#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>

int main() {
    int opcao;  // Guarda a opção do menu

	setlocale(LC_ALL, "Portuguese");	//habilita a acentuação para o português
    // Abertura dos arquivos
    abreCep();    						// Abre o arquivo de CEPs
    abreHash();   						// Abre o arquivo de ordenação (hash)
    // Loop para continuação da exibição do menu
    do {
        opcao = menu();
        switch(opcao){
            case 1: pesquisaHash();     break;
            case 2: estatisticasHash(); break;
            case 3: listaCep();			break;
//            case 4: pesquisaListaCep("48010140");
//					break;
            case 4: listaHash();		break;
            case 0: break;
            default:
                printf("Opção inválida!\n");
                pausa();
                break;
        }
    } while(opcao != 0);  				//Condição de saída
    // Fechamento dos arquivos
    abreCep();    						// Fecha o arquivo de CEPs
    abreHash();   						// Fecha o arquivo de ordenação (hash)
	return 0;
}
