# Interprocess-chat
Chat entre dois processos com uso de pipes nomeados.

Pipes nomeados são acessados pelos processos como feito com arquivos comuns, portanto a escrita e leitura destes elementos é possível com uso das chamadas de sistema write() e read(). A lógica aqui aplicada é a seguinte: cada pipe somente é acessado pelo processo para leitura ou escrita, não ocorrendo essas duas operações simultaneamente. Partindo disso, o primeiro processo, "pessoa1", usa o pipe nomeado 1 para escrever suas mensagens, fazendo uso do pipe nomeado 2 para ler as mensagens escritas pelo segundo processo. O processo "pessoa2", por sua vez, usa o pipe 2 para escrever suas mensagens e lê as que foram deixadas no pipe 1. 



Passo a passo para utilização:
1 - Abrir duas janelas de terminal;
2 - Em cada uma das janelas realizar a compilação de ambos os arquivos, pessoa1.c e pessoa2.c;
3 - Em uma janela executar pessoa1 e em outra o pessoa2;
4 - A marcação "Eu:" indica o momento de escrever uma mensagem.
