/******************************************************************
04/06/2016                      hash                     04/06/2016
-------------------------------------------------------------------
Arquivo...: hash.c
Autor.....: José Américo Rodrigues
Finalidade: Operações no arquivo da tabela hash
******************************************************************/
#include <stdlib.h>
#include <hash.h>
#include <cep.h>
#include <util.h>

/******************************************************************
Função....: criaHash
Finalidade: Cria o arquivo da tabela hash (índices)
******************************************************************/
int criaHash() {
    int i;                      // Variável auxiliar para os índices
    long h;                     // Posição na tabela hash
    long registro = -1;         // Posição atual do registro de CEPs
    long posicaofinal;          // Final do arquivo de índices (hash)
    long posicaoarqanterior;    // Posição anterior no arquivo (hash)
    long posicaoanterior;       // Posiçao anterior no arquivo
    HashTab htaux, htant;       // Auxiliares para adicionar registros na tabela

    arqhash = fopen(HASHFILE, "w");
    fechaHash();
    arqhash = fopen(HASHFILE, "r+");  //Reabre-o
    abreCep();
    limpaTela();   // Limpa a tela
	printf("Criando o arquivo de indices (hash)...   ");
	printf("0%% "); // Inicia a barra de progresso
    // Loop para inclusão das linhas da tabela
    for (i = 0; i <= MAXHASH; i++) {
        ht.CEP = 0; ht.PosArq = -1; ht.Proximo = -1; // Inicializa os dados da tabela
        escreveHash(ht, 0, SEEK_END);                // Adiciona o registro no final do arquivo
        if (i % 45000 == 0) printf("\x219");         // Exibe o andamento do processo
    }
    printf(" 100%%\n\n");   // Finaliza a barra de progresso
	printf("Indexando o arquivo de CEPs (hash)...    ");
	printf("0%% ");
 	registro++;
    e = leCep(registro);   //Lê o primeiro registro do arquivo de CEps
    // Loop para circular pelos registros de CEPs
	while (strlen(e.cep) > 0) {
        h = strtol(e.cep, NULL, 10) % MAXHASH;  // Calcula a posição para pesquisar
        // Vai até a linha calculada da tabela e guarda as informações contidas
        ht = leHash(h);
        // Guarda as informações na variável auxiliar
        htaux.CEP = strtol(e.cep, NULL, 10);    // Novo CEP
        htaux.PosArq = registro;                // Posição da linha no arquivo de CEPs
        htaux.Proximo = -1;                     // Não há ainda colisão
        // Se não houver um CEP na linha...
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
        // Há colisão...
        else {
            // 1ª colisão
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
                // Guarda a posição da nova linha para sobrescrever o campo
                // Proximo da linha onde houve a colisão
                posicaofinal = (ftell(arqhash) / sizeof(HashTab));
                // Guarda-se a nova informação do arquivo de CEPs
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
            // Há várias colisões
            else {
//                htant = ht;
                //posicaoarqanterior = ht.PosArq;
//                posicaoanterior = ht.Proximo;
                // Loop para circular por todas as colisões encontradas
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
                // Guarda-se a posição da nova linha para sobrescrever o campo
                // Proximo da linha onde houve a colisão
                posicaofinal = (ftell(arqhash) / sizeof(HashTab));
                // Grava a nova informação do arquivo de CEPs
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
        e = leCep(registro);    // Lê o próximo CEP
    }
    printf(" 100%%\n\n");
	return 0;
}

/******************************************************************
Função....: pesquisaHash
Finalidade: Consultar um elemento através da tabela de hash
******************************************************************/
int pesquisaHash() {
	char cep[9];  // Guarda o nome a ser pesquisado
	long h;  // Guarda o número do registro

    // Leitura via teclado do CEP a ser pesuisado
    printf("CEP a ser pesquisado: "); scanf("%s", cep);
 	printf("Procurando o CEP [%s]\n", cep);

    // Calcula a posição para pesquisar
    h = strtol(cep, NULL, 10) % MAXHASH;
    // Vai até a linha calculada da tabela e guarda as informações contidas
    ht = leHash(h);
    if (strtol(cep, NULL, 10) == ht.CEP) {
        // CEP encontrado de primeira... Pegando informações do arquivo de CEPs
        e = leCep(ht.PosArq);
        printf("CEP %s encontrado! - ", cep);
        imprimeCep(ht.PosArq, e);
    }
    // CEP houve colisão ou não foi encontrado
    else {



    }
	pausa();
	return 0;
}

/******************************************************************
Função....: estatisticasHash
Finalidade: Estatísticas gerais do arquivo de Hash
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
 	// Exibe informações do arquivo de CEPs
	printf("Total de CEPs no arquivo: %ld\n", tamanho/sizeof(Endereco));
	printf("Tamanho dos Registros...: %d bytes\n", sizeof(Endereco));
	printf("Tamanho do Arquivo......: %ld bytes\n", tamanho);

    free(colisoes);
    pausa();
	return 0;
}

/******************************************************************
Função....: listaHash
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
Função....: abreHash
Finalidade: Abre o arquivo da tabela hash
******************************************************************/
int abreHash() {
    // Verifica a existência do arquivo de hash e abre-o.
    // Caso não exista, cria-o
	arqhash = fopen(HASHFILE,"r");
	if(!arqhash) {
        fclose(arqhash);
		criaHash();
	}
    return 0;
}

/******************************************************************
Função....: leHash
Finalidade: Le um registro da tabela de Hash
******************************************************************/
HashTab leHash(long pos) {
    HashTab reg;

    fseek(arqhash, pos * sizeof(HashTab), SEEK_SET);
    fread(&reg, sizeof(HashTab), 1, arqhash);
    return reg;
}

/******************************************************************
Função....: escreveHash
Finalidade: Grava um registro no arquivo da tabela de Hash
Parâmetros: reg - Registro a ser gravado
            pos - Deslocamento do registro em relação ao início do
                  arquivo de CEPs
            rel - a pesquisa é relativa ao início do arquivo, à po-
                  sição corrente ou ao fim do arquivo?
******************************************************************/
int escreveHash(HashTab reg, long pos, int rel) {
    // Pesquisa no deslocamento o registro selecionado
    fseek(arqhash, pos * sizeof(HashTab), rel); // Pesquisa
    // Grava o registro no arquivo
    fwrite(&reg, sizeof(HashTab), 1, arqhash);
    return 1;
}

/******************************************************************
Função....: fechaHash
Finalidade: Fecha o arquivo da tabela hash
******************************************************************/
int fechaHash() {
	fclose(arqhash);     // Fecha o arquivo de ordenação (hash)
    return 1;
}
