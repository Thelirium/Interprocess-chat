#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(){
	char buffer[64]; // Buffer para escrita de mensagens.

	// Criação do primeiro pipe nomeado/FIFO e avaliação do êxito da criação.
	// Os processos enxergam o pipe como um arquivo comum, a permissão 
	// 0664(-rw-rw-r--) define o que cada grupo pode fazer com esse arquivo
	int resultado = access("pipe_nom1", F_OK);
	if(resultado == -1){
		mkfifo("pipe_nom1", 0664);
	}

	// Acessando o segundo pipe, do segundo processo, para leitura.
	// A chamada de sistema access() é usada para checar a existência do
	// pipe nomeado com o parâmetro F_OK.
	resultado = access("pipe_nom2", F_OK);
	if (resultado == -1)
	{
		mkfifo("pipe_nom2", 0664);
	}

	// Acesso do pipe nomeado 1 para leitura somente.
	int pipe_leitura = open("pipe_nom1", O_RDONLY);
	if (pipe_leitura == -1)
	{
		printf("Erro durante o acesso ao pipe 1 pelo processo pessoa2\n");
		exit(0);
	}

	// Acesso ao pipe 2 para escrita
	int pipe_escrita = open("pipe_nom2", O_WRONLY);
	if (pipe_escrita == -1)
	{
		printf("Erro durante o acesso ao pipe 2 pelo processo pessoa2\n");
		exit(0);
	}

	// Laço para a escrita de mensagens
	while(1){
		// Acesso para leitura do que for escrito pelo primeiro processo
		memset(buffer, 0, 64);
		read(pipe_leitura, buffer, 64);
		printf("Ele: %s", buffer);

		// Escrita para leitura pelo primeiro processo
		memset(buffer, 0, 64); 
		printf("Eu: ");
		fgets(buffer, 64, stdin);
		write(pipe_escrita, buffer, strlen(buffer));
		printf("\n");
	}

	// Fechando os pipes criados com a chamada de sistema close().
	close(pipe_leitura);
	close(pipe_escrita);

	return 0;
}
