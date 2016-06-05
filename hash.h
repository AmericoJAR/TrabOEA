/******************************************************************
04/06/2016                     hash.h                    04/06/2016
-------------------------------------------------------------------
Arquivo...: hash.h
Autor.....: José Américo Rodrigues
Finalidade: Header para operações na tabela hash em arquivo
******************************************************************/
#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include <stdio.h>

#define HASHFILE "cep_h.idx"
#define MAXHASH 900001

// Estrutura para a leitura dos registros da tabela hash
typedef struct {
    long CEP;
    long PosArq;
    long Proximo;
} HashTab;

int criaHash();
int pesquisaHash();
int estatisticasHash();
int listaHash();
int abreHash();
HashTab leHash(long pos);
int escreveHash(HashTab reg, long pos, int rel);
int fechaHash();

FILE *arqhash;  // Ponteiro para o arquivo da tabela hash
HashTab ht;     // Estrutura para o registro da tabela

#endif // HASH_H_INCLUDED
