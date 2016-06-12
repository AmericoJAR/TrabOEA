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
    long posicaoarqanterior;    // Posi��o anterior no arquivo (hash)
    long posicaoanterior;       // Posi�ao anterior no arquivo
    HashTab htaux, htant;       // Auxiliares para adicionar registros na tabela

    arqhash = fopen(HASHFILE, "w");
    fechaHash();
    arqhash = fopen(HASHFILE, "r+");  //Reabre-o
    abreCep();
    limpaTela();   // Limpa a tela
	printf("Criando o arquivo de indices (hash)...   ");
	printf("0%% "); // Inicia a barra de progresso
    // Loop para inclus�o das linhas da tabela
    for (i = 0; i <= MAXHASH; i++) {
        ht.CEP = 0; ht.PosArq = -1; ht.Proximo = -1; // Inicializa os dados da tabela
        escreveHash(ht, 0, SEEK_END);                // Adiciona o registro no final do arquivo
        if (i % 45000 == 0) printf("\x219");         // Exibe o andamento do processo
    }
    printf(" 100%%\n\n");   // Finaliza a barra de progresso
	printf("Indexando o arquivo de CEPs (hash)...    ");
	printf("0%% ");
 	registro++;
    e = leCep(registro);   //L� o primeiro registro do arquivo de CEps
    // Loop para circular pelos registros de CEPs
	while (strlen(e.cep) > 0) {
        h = strtol(e.cep, NULL, 10) % MAXHASH;  // Calcula a posi��o para pesquisar
        // Vai at� a linha calculada da tabela e guarda as informa��es contidas
        ht = leHash(h);
        // Guarda as informa��es na vari�vel auxiliar
        htaux.CEP = strtol(e.cep, NULL, 10);    // Novo CEP
        htaux.PosArq = registro;                // Posi��o da linha no arquivo de CEPs
        htaux.Proximo = -1;                     // N�o h� ainda colis�o
        // Se n�o houver um CEP na linha...
        if (ht.CEP == 0) {
            escreveHash(htaux, h, SEEK_SET);    // Guarda o CEP no arquivo hash
printf("\nCEP: %s - ", e.cep);
printf("CEP: %ld - ", ht.CEP);
printf("PosArq: %ld - ", ht.PosArq);
printf("Prox: %ld - ", ht.Proximo);
printf("\nCEP: %ld - ", htaux.CEP);
printf("PosArq: %ld - ", htaux.PosArq);
printf("Prox: %ld - ", htaux.Proximo);
printf("Pos: %ld - ", h);
printf("SEEK_SET1\n");
        }
        // H� colis�o...
        else {
            // 1� colis�o
            if (ht.Proximo == -1) {
                escreveHash(htaux, 0, SEEK_END);    // Adiciona o CEP no final do arquivo
printf("\nCEP: %s - ", e.cep);
printf("CEP: %ld - ", ht.CEP);
printf("PosArq: %ld - ", ht.PosArq);
printf("Prox: %ld - ", ht.Proximo);
printf("\nCEP: %ld - ", htaux.CEP);
printf("PosArq: %ld - ", htaux.PosArq);
printf("Prox: %ld - ", htaux.Proximo);
printf("Pos: %ld - ", 0);
printf("SEEK_END1\n");
                // Guarda a posi��o da nova linha para sobrescrever o campo
                // Proximo da linha onde houve a colis�o
                posicaofinal = (ftell(arqhash) / sizeof(HashTab));
                // Guarda-se a nova informa��o do arquivo de CEPs
                htaux.CEP = ht.CEP;
                htaux.PosArq = ht.PosArq;
                htaux.Proximo = posicaofinal;
                escreveHash(htaux, h, SEEK_SET);
printf("\nCEP: %s - ", e.cep);
printf("CEP: %ld - ", ht.CEP);
printf("PosArq: %ld - ", ht.PosArq);
printf("Prox: %ld - ", ht.Proximo);
printf("\nCEP: %ld - ", htaux.CEP);
printf("PosArq: %ld - ", htaux.PosArq);
printf("Prox: %ld - ", htaux.Proximo);
printf("Pos: %ld - ", h);
printf("SEEK_SET2\n");
            }
            // H� v�rias colis�es
            else {
//                htant = ht;
                //posicaoarqanterior = ht.PosArq;
//                posicaoanterior = ht.Proximo;
                // Loop para circular por todas as colis�es encontradas
                while (ht.Proximo != -1) {
                    ht = leHash(ht.Proximo);
printf("\nCEP: %s - ", e.cep);
printf("CEP: %ld - ", ht.CEP);
printf("PosArq: %ld - ", ht.PosArq);
printf("Prox: %ld - ", ht.Proximo);
printf("*******************\n");
                   if (ht.Proximo != -1) {
                        //posicaoarqanterior = ht.PosArq;
//                        posicaoanterior = ht.Proximo;
//                        htant = ht;
                    }
                }
                escreveHash(htaux, 0, SEEK_END);    // Adiciona o novo CEP no final do arquivo
printf("CEP: %s - ", e.cep);
printf("CEP: %ld - ", ht.CEP);
printf("PosArq: %ld - ", ht.PosArq);
printf("Prox: %ld - ", ht.Proximo);
printf("\nCEP: %ld - ", htaux.CEP);
printf("PosArq: %ld - ", htaux.PosArq);
printf("Prox: %ld - ", htaux.Proximo);
printf("Pos: %ld - ", 0);
printf("SEEK_END2\n");
                // Guarda-se a posi��o da nova linha para sobrescrever o campo
                // Proximo da linha onde houve a colis�o
                posicaofinal = (ftell(arqhash) / sizeof(HashTab));
                // Grava a nova informa��o do arquivo de CEPs
                htaux.CEP = strtol(e.cep, NULL, 10);
                htaux.PosArq = registro;    //htant.PosArq; //posicaoarqanterior;
                htaux.Proximo = posicaofinal;
                escreveHash(htaux, h, SEEK_SET);
printf("\nCEP: %s - ", e.cep);
printf("CEP: %ld - ", htaux.CEP);
printf("PosArq: %ld - ", ht.PosArq);
printf("Prox: %ld - ", ht.Proximo);
printf("\nCEP: %ld - ", htaux.CEP);
printf("PosArq: %ld - ", htaux.PosArq);
printf("Prox: %ld - ", posicaofinal);
printf("Pos: %ld - ", h);
printf("SEEK_SET3\n");
pausa();
            }
        }
        if (registro % 45000 == 0) printf("\x219"); // Exibe o andamento do processo
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
        imprimeCep(ht.PosArq, e);
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
    // Pesquisa no deslocamento o registro selecionado
    fseek(arqhash, pos * sizeof(HashTab), rel); // Pesquisa
    // Grava o registro no arquivo
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
