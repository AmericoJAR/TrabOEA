# TrabOEA
--------------------------------------
Trabalho de OEA
--------------------------------------
Trabalho da disciplina Organiza��o e Estrutura de Arquivos ministrada pelo prof Renato Mauro no 
Centro Federal de Tecnologia do Rio de Janeiro na unidade Maracan� (CEFET-RJ).

A finalidade deste trabalho � o de aprendizado na manipula��o de estruturas de indexa��o arquivos atrav�s de tabelas de dispers�o (hash).

--------------------------------------
Comandos para compila��o e linkedi��o:
--------------------------------------
gcc.exe -c cep.c -o cep.o

gcc.exe -c hash.c -o hash.o

gcc.exe -c main.c -o main.o

gcc.exe -c util.c -o util.o

gcc.exe cep.o hash.o main.o util.o -o OEA.exe