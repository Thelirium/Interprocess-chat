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
		// printf("Erro durante a criação do pipe nomeado 1\n");
		int resultado = mkfifo("pipe_nom1", 0664);
		//exit(0);
	}

	// Acessando o segundo pipe, do segundo processo, para leitura.
	// A chamada de sistema access() é usada para checar a existência do
	// pipe nomeado com o parâmetro F_OK.
	resultado = access("pipe_nom2", F_OK);
	if (resultado == -1)
	{
		printf("Erro durante o acesso ao pipe nomeado 2 pelo processo pessoa1\n");
		printf("Pipe nomeado 2 será criado\n");
		resultado = mkfifo("pipe_nom2", 0664);
		if (resultado == -1)
		{
			printf("Erro durante a criação do pipe 2 pelo processo pessoa1\n");
			exit(0);
		}
	}

	// Como pipes só podem ser usados para leitura ou escrita, o primeiro
	// deles será usado pelo processo pessoa1 para escrita das mensagens.
	// A chamada de sistema open() é usada para abrir o pipe somente com a
	// possibilidade de escrita ativa, através do parâmetro O_WRONLY.
	int pipe_escrita = open("pipe_nom1", O_WRONLY);

	// Acesso do pipe nomeado 2 para leitura somente.
	int pipe_leitura = open("pipe_nom2", O_RDONLY);
	
	// Laço para a escrita de mensagens
	while(1){
		// Capturando a mensagem inserida pelo usuário com fgets().
		// Escrita da mensagem no pipe com chamada de sistema write(), como 
		// se escrevesse em um arquivo comum.
		memset(buffer, 0, sizeof(buffer)); 
		printf("Eu: ");
		fgets(buffer, 64, stdin);
		write(pipe_escrita, buffer, strlen(buffer));

		// Parte do laço para leitura do que for escrito no segundo pipe
		memset(buffer, 0, 64);
		read(pipe_leitura, buffer, 64);
		printf("Ele: %s\n", buffer);
	}

	// Fechando os pipes criados com a chamada de sistema close().
	close(pipe_leitura);
	close(pipe_escrita);

	return 0;
}