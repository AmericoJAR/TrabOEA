/******************************************************************
04/06/2016                      Util                     04/06/2016
-------------------------------------------------------------------
Arquivo...: util.c
Autor.....: Jos� Am�rico Rodrigues
Finalidade: Arquivo de c�digos utilit�rios do sistema
******************************************************************/
#include <util.h>
#include <windows.h>

/******************************************************************
Fun��o....: menu
Finalidade: Apresentar menu principal do aplicativo
******************************************************************/
int menu() {
	// Guarda a op��o do menu a ser passada para a fun��o principal
    int num;

    limpaTela();  // Limpa a tela
    // Exibe o menu de op��es
	printf("Consulta de CEPs\n\n");
	printf("Menu:\n\n");
	printf("1. Consultar CEP\n");
	printf("2. Verificar estatisticas\n");
	printf("3. Listar CEPs\n");
	printf("4. Listar CEPs ap�s consulta\n");
	printf("5. Listar Tabela Hash\n");
	printf("0. Sair\n\n");
	printf("Escolha uma opcao: ");
	scanf("%d", &num);

	return num;
}

/******************************************************************
Fun��o....: limpaTela
Finalidade: Limpa a tela
******************************************************************/
int limpaTela() {
// Pesquisa realizada na internet com uso da API do windows
#ifdef _WIN32
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hStdOut, &csbi);
    FillConsoleOutputCharacter(hStdOut, ' ', csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
    SetConsoleCursorPosition(hStdOut, coord);
#else
    printf("\e[H\e[2J");
#endif

    return 0;
}

/******************************************************************
Fun��o....: pausa
Finalidade: pausa o processo mostrando mensagem (parecido com o DOS)
******************************************************************/
int pausa() {
    printf("\n\nPressione qualquer tecla para continuar... \n");
    getchar(); getchar();

    return 0;
}
