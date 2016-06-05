/******************************************************************
04/06/2016                      cep                      04/06/2016
-------------------------------------------------------------------
Arquivo...: cep.c
Autor.....: José Américo Rodrigues
Finalidade: Operações no arquivo nao ordenado de CEPs
******************************************************************/
#include <cep.h>

/******************************************************************
Função....: listaCep
Finalidade: Lista os registros do arquivo de CEPs
******************************************************************/
int listaCep() {
    long registro = -1;

    limpaTela();
	printf("Listando o arquivo de CEPs...\n\n");

    registro++;
    e = leCep(registro);
    while(!feof(arqcep)) {
        imprimeCep(registro, e);
        registro++;
        e = leCep(registro);
    }
	pausa();
	return 1;
}

/******************************************************************
Função....: pesquisaListaCep
Finalidade: Lista os registros do arquivo de CEPs após pesquisa de
            um dado registro
******************************************************************/
int pesquisaListaCep(char cep[9]) {
    long registro = -1;
    int naoencontrado = 1;

    limpaTela();
	printf("Listando o arquivo de CEPs a partir do CEP %s...\n\n", cep);

    registro++;
    e = leCep(registro);
    while(!feof(arqcep)) {
        if (strcmp(e.cep, cep)) naoencontrado = 0;
        if (naoencontrado == 0) {
            imprimeCep(registro, e);
        }
        registro++;
        e = leCep(registro);
    }
	pausa();
	return 1;
}

/******************************************************************
Função....: abreCep
Finalidade: Abre o arquivo de CEPs
******************************************************************/
int abreCep() {

    // Verifica a existência do arquivo de CEPs e abre-o
	arqcep = fopen(CEPFILE,"r");
	if(!arqcep) {
		fprintf(stderr,"Arquivo %s nao pode ser aberto para leitura\n", CEPFILE);
		return 1;
	}
}

/******************************************************************
Função....: leCep
Finalidade: Le um registro do arquivo de CEPs
Parâmetros: pos - Deslocamento do registro em relação ao início do
                  arquivo de CEPs
******************************************************************/
Endereco leCep(long pos) {
    Endereco reg;

    fseek(arqcep, (pos * 300), SEEK_SET);
    memset(&reg, 0, sizeof(Endereco));    // Zera a variável para guardar o endereço
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
Função....: imprimeCep
Finalidade: imprime um registro do arquivo de CEPs
Parâmetros: pos - Deslocamento do registro em relação ao início do
                  arquivo de CEPs
            reg - registro a ser impresso
******************************************************************/
int imprimeCep(long pos, Endereco reg) {
    printf("\nReg...: %ld", pos);
    printf("\nEnder.: %72s", reg.endereco);
    printf("Bairro: %72s", reg.bairro);
    printf("Cidade: %72s", reg.cidade);
    printf("Estado: %72s", reg.nomeEstado);
    printf("UF....: %2s", reg.siglaEstado);
    printf("\nCEP...: %8s\n", reg.cep);
    return 0;
}

/******************************************************************
Função....: fechaCep
Finalidade: Fecha o arquivo de CEPs
******************************************************************/
int fechaCep() {

	fclose(arqcep); // Fecha o arquivo de CEPs
    return 0;
}
