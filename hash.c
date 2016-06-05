/******************************************************************
04/06/2016                      hash                     04/06/2016
-------------------------------------------------------------------
Arquivo...: hash.c
Autor.....: Jos� Am�rico Rodrigues
Finalidade: Opera��es no arquivo da tabela hash
******************************************************************/
#include <stdlib.h>
#include <hash.h>
#include <cep.h>
#include <util.h>

/******************************************************************
Fun��o....: criaHash
Finalidade: Cria o arquivo da tabela hash (�ndices)
******************************************************************/
int criaHash() {
    int i;                      // Vari�vel auxiliar para os �ndices
    long h;                     // Posi��o na tabela hash
    long registro = -1;         // Posi��o atual do registro de CEPs
    long posicaofinal;          // Final do arquivo de �ndices (hash)
    long posicaoanterior;       // Final do arquivo de �ndices (hash)
    HashTab htaux;              // Auxiliar para adicionar registros na tabela

    arqhash = fopen(HASHFILE, "w");
    fechaHash();
    arqhash = fopen(HASHFILE, "r+");  //Reabre-o
    abreCep();

    limpaTela();   // Limpa a tela
	printf("Criando o arquivo de indices...   ");
	printf("0%% ");
    // Loop para inclus�o das linhas da tabela
    for (i = 0; i <= MAXHASH; i++) {
         // Inicializando os dados da tabela
        ht.CEP = 0; ht.PosArq = -1; ht.Proximo = -1;
        // Adiciona o registro no final do arquivo
        escreveHash(ht, 0, SEEK_END);    //
        if (i % 45000 == 0) {
            printf("\x219");    // Exibe o andamento do processo
        }
    }
    printf(" 100%%\n\n");

	printf("Indexando o arquivo de CEPs...    ");
	printf("0%% ");
 	registro++;
    e = leCep(registro);   //Le o primeiro registro do arquivo de CEps
    // Loop para circular nos registro de CEPs
	while (strlen(e.cep) > 0) {
        // Calcula a posi��o para pesquisar
        h = strtol(e.cep, NULL, 10) % MAXHASH;
        // Vai at� a linha calculada da tabela e guarda as informa��es contidas
        ht = leHash(h);
        // Se n�o houver um CEP na linha...
        if (ht.CEP == 0) {
            // Guarda-se a nova informa��o do arquivo de CEPs
            htaux.CEP = strtol(e.cep, NULL, 10);    // Novo CEP
            htaux.PosArq = registro;                // Posi��o da linha do arquivo de CEPs
            htaux.Proximo = -1;                     // N�o h� ainda colis�o
            escreveHash(htaux, h, SEEK_SET);
         }

        // H� colis�o...
        else {

            // 1� colis�o
            if (ht.Proximo == -1) {
                // Adiciona o novo CEP no final do arquivo
                htaux.CEP = strtol(e.cep, NULL, 10);    // Novo CEP
                htaux.PosArq = registro;                // Posi��o da linha do arquivo de CEPs
                htaux.Proximo = -1;                     // N�o h� mais colis�es
                escreveHash(htaux, 0, SEEK_END);
                // Guarda-se a posi��o da nova linha para sobrescrever o campo
                // Proximo da linha onde houve a colis�o
                posicaofinal = (ftell(arqhash) / sizeof(HashTab));
                // Guarda-se a nova informa��o do arquivo de CEPs
                htaux.CEP = ht.CEP;
                htaux.PosArq = ht.PosArq;
                htaux.Proximo = posicaofinal;
                escreveHash(htaux, h, SEEK_SET);
            }

            // H� v�rias colis�es
            else {
                posicaoanterior = 0;
                // Loop para circular por todas as colis�es encontradas
                while (ht.Proximo != -1) {
                    ht = leHash(ht.Proximo);
                    if (ht.Proximo != -1) {
                        posicaoanterior = ht.Proximo;
                    }
                    printf("Proximo: %ld", ht.Proximo);
                    printf("Posicao anterior: %ld", posicaoanterior);
                }

                // Adiciona o novo CEP no final do arquivo
                htaux.CEP = strtol(e.cep, NULL, 10);    // Novo CEP
                htaux.PosArq = registro;                // Posi��o da linha do arquivo de CEPs
                htaux.Proximo = -1;                     // N�o h� mais colis�es
                escreveHash(htaux, 0, SEEK_END);
                // Guarda-se a posi��o da nova linha para sobrescrever o campo
                // Proximo da linha onde houve a colis�o
                posicaofinal = (ftell(arqhash) / sizeof(HashTab));

                    printf("Entrei aqui!");
                    printf("Proximo: %ld", ht.Proximo);
                    printf("Posicao anterior: %ld", posicaoanterior);
                    printf("Posicao final: %ld", posicaofinal);

                // Guarda-se a nova informa��o do arquivo de CEPs
                htaux.CEP = ht.CEP;
                htaux.PosArq = ht.PosArq;
                htaux.Proximo = posicaofinal;
                escreveHash(htaux, posicaoanterior, SEEK_SET);
            }
        }
        if (registro % 45000 == 0) {
            printf("\x219");    // Exibe o andamento do processo
        }

        registro++;
        e = leCep(registro);    // L� o pr�ximo CEP
    }
    printf(" 100%%\n\n");

	return 0;
}

/******************************************************************
Fun��o....: pesquisaHash
Finalidade: Consultar um elemento atrav�s da tabela de hash
******************************************************************/
int pesquisaHash() {
	char cep[9];  // Guarda o nome a ser pesquisado
	long h;  // Guarda o n�mero do registro

    // Leitura via teclado do CEP a ser pesuisado
    printf("CEP a ser pesquisado: "); scanf("%s", cep);
 	printf("Procurando o CEP [%s]\n", cep);

    // Calcula a posi��o para pesquisar
    h = strtol(cep, NULL, 10) % MAXHASH;
    // Vai at� a linha calculada da tabela e guarda as informa��es contidas
    ht = leHash(h);
    if (strtol(cep, NULL, 10) == ht.CEP) {
        // CEP encontrado de primeira... Pegando informa��es do arquivo de CEPs
        e = leCep(ht.PosArq);
        printf("CEP %s encontrado! - ", cep);
        printf("posicao: %ld", ht.PosArq);
        imprimeCep(e);
    }
    // CEP houve colis�o ou n�o foi encontrado
    else {



    }
	pausa();

	return 0;
}

/******************************************************************
Fun��o....: estatisticasHash
Finalidade: Estat�sticas gerais do arquivo de Hash
******************************************************************/
int estatisticasHash() {
	int *colisoes;
	long h;
    long registro = -1;
    long tamanho;   // Guarda o tamanho do arquivo

    colisoes = malloc (MAXHASH * sizeof (int));
    if (colisoes == NULL) {
        printf ("Erro! Nao foi possivel alocar memoria para o vetor.\n");
        exit (EXIT_FAILURE);
    }
	int resultado[20];
	long int i;

    for (i = 0; i <= MAXHASH; i++) {
        if (i < 20) resultado[i] = 0;
        colisoes[i] = 0;
    }

    registro++;
    e = leCep(registro);
	while(strlen(e.cep) > 0) {
        h = strtol(e.cep, NULL, 10) % MAXHASH;
        colisoes[h]++;
        registro++;
        e = leCep(registro);
    }

    for (i = 0; i <= MAXHASH; i++) {
        resultado[colisoes[i]]++;
    }

    for (i = 0; i < 20 ; i++){
        printf("Quantidade de elementos %ld: %d\n", i, resultado[i]);
    }

    fseek(arqcep, 0, SEEK_END);
	tamanho = ftell(arqcep);
 	// Exibe informa��es do arquivo de CEPs
	printf("Total de CEPs no arquivo: %ld\n", tamanho/sizeof(Endereco));
	printf("Tamanho dos Registros...: %d bytes\n", sizeof(Endereco));
	printf("Tamanho do Arquivo......: %ld bytes\n", tamanho);

    free(colisoes);
    pausa();

	return 0;
}

/******************************************************************
Fun��o....: listaHash
Finalidade: Lista a tabela Hash
******************************************************************/
int listaHash() {
    long registro = -1;

    limpaTela();
	printf("Listando o arquivo de indices...\n\n");

    registro++;
    ht = leHash(registro);
    while(!feof(arqhash)) {
        printf("\nRegistro: %ld - ", registro);
        printf("CEP...: %ld - ", ht.CEP);
        printf("Posicao: %ld - ", ht.PosArq);
        printf("Proximo: %ld", ht.Proximo);

        registro++;
        ht = leHash(registro);
    }
	pausa();
	return 1;
}

/******************************************************************
Fun��o....: abreHash
Finalidade: Abre o arquivo da tabela hash
******************************************************************/
int abreHash() {

    // Verifica a exist�ncia do arquivo de hash e abre-o.
    // Caso n�o exista, cria-o
	arqhash = fopen(HASHFILE,"r");
	if(!arqhash) {
        fclose(arqhash);
		criaHash();
	}
    return 0;
}

/******************************************************************
Fun��o....: leHash
Finalidade: Le um registro da tabela de Hash
******************************************************************/
HashTab leHash(long pos) {
    HashTab reg;

    fseek(arqhash, pos * sizeof(HashTab), SEEK_SET);
    fread(&reg, sizeof(HashTab), 1, arqhash);
    return reg;
}

/******************************************************************
Fun��o....: escreveHash
Finalidade: Grava um registro no arquivo da tabela de Hash
Par�metros: reg - Registro a ser gravado
            pos - Deslocamento do registro em rela��o ao in�cio do
                  arquivo de CEPs
            rel - a pesquisa � relativa ao in�cio do arquivo, � po-
                  si��o corrente ou ao fim do arquivo?
******************************************************************/
int escreveHash(HashTab reg, long pos, int rel) {
        fseek(arqhash, pos * sizeof(HashTab), rel);
        // Guarda o registro no arquivo
        fwrite(&reg, sizeof(HashTab), 1, arqhash);
        return 1;
}

/******************************************************************
Fun��o....: fechaHash
Finalidade: Fecha o arquivo da tabela hash
******************************************************************/
int fechaHash() {

	fclose(arqhash);     // Fecha o arquivo de ordena��o (hash)
    return 1;
}
