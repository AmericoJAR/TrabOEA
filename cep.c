/******************************************************************
04/06/2016                      cep                      04/06/2016
-------------------------------------------------------------------
Arquivo...: cep.c
Autor.....: Jos� Am�rico Rodrigues
Finalidade: Opera��es no arquivo nao ordenado de CEPs
******************************************************************/
#include <cep.h>
#include <stdbool.h>

/******************************************************************
Fun��o....: listaCep
Finalidade: Lista os registros do arquivo de CEPs
******************************************************************/
int listaCep() {
    long registro = -1;

    limpaTela();
	printf("Listando o arquivo de CEPs...\n\n");

    registro++;
    e = leCep(registro);
    while(!feof(arqcep)) {
        printf("\nRegistro: %ld - ", registro);
        imprimeCep(e);
        registro++;
        e = leCep(registro);
    }
	pausa();
	return 1;
}

/******************************************************************
Fun��o....: pesquisaListaCep
Finalidade: Lista os registros do arquivo de CEPs ap�s pesquisa de
            um dado registro
******************************************************************/
int pesquisaListaCep(char cep[9]) {
    long registro = -1;
    bool naoencontrado = true;

    limpaTela();
	printf("Listando o arquivo de CEPs a partir do CEP %s...\n\n", cep);

    registro++;
    e = leCep(registro);
    while(!feof(arqcep)) {
        if (e.cep == cep) naoencontrado = false;
        if (!naoencontrado) {
            printf("\nRegistro: %ld - ", registro);
            imprimeCep(e);
        }
        registro++;
        e = leCep(registro);
    }
	pausa();
	return 1;
}

/******************************************************************
Fun��o....: abreCep
Finalidade: Abre o arquivo de CEPs
******************************************************************/
int abreCep() {

    // Verifica a exist�ncia do arquivo de CEPs e abre-o
	arqcep = fopen(CEPFILE,"r");
	if(!arqcep) {
		fprintf(stderr,"Arquivo %s nao pode ser aberto para leitura\n", CEPFILE);
		return 1;
	}
}

/******************************************************************
Fun��o....: leCep
Finalidade: Le um registro do arquivo de CEPs
Par�metros: pos - Deslocamento do registro em rela��o ao in�cio do
                  arquivo de CEPs
******************************************************************/
Endereco leCep(long pos) {
    Endereco reg;

    fseek(arqcep, (pos * 300), SEEK_SET);
    memset(&reg, 0, sizeof(Endereco));    // Zera a vari�vel para guardar o endere�o
    fread(&reg.endereco, 1, 72, arqcep);
    fread(&reg.bairro, 1, 72, arqcep);
    fread(&reg.cidade, 1, 72 , arqcep);
    fread(&reg.nomeEstado, 1, 72, arqcep);
    fread(&reg.siglaEstado, 1, 2, arqcep);
    fread(&reg.cep, 1, 8, arqcep);
	fseek(arqcep, 2, SEEK_CUR);
    return reg;
}

/******************************************************************
Fun��o....: imprimeCep
Finalidade: imprime um registro do arquivo de CEPs
Par�metros: reg - registro a ser impresso
******************************************************************/
int imprimeCep(Endereco reg) {
    printf("\n\nEndereco: %72s", reg.endereco);
    printf("\nBairro..: %72s", reg.bairro);
    printf("\nCidade..: %72s", reg.cidade);
    printf("\nEstado..: %72s", reg.nomeEstado);
    printf("\nUF......: %2s", reg.siglaEstado);
    printf("\nCEP.....: %8s", reg.cep);
}

/******************************************************************
Fun��o....: fechaCep
Finalidade: Fecha o arquivo de CEPs
******************************************************************/
int fechaCep() {

	fclose(arqcep); // Fecha o arquivo de CEPs
    return 0;
}
