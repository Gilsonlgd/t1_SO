#  T1 - Trabalho 1
- Utiliza-se o código disponibilizado pelo professor para implementar um S.O;
- Neste trabalho, a ideia é implementar multiprogramação no S.O;
- A partir deste embrião serão desenvolvidos os T1 e T2.

## Programas Utilizados para testes:
- São utilizados dois programas: o p2 e p3;
- p2 é uma implementação do professor, le um número do terminar 1 e imprime todos os numeros de 1 até ele;
- p3 é uma implementação minha. Utiliza um dispositivo virtual que gera números aleatórios. Nesse caso está imprimindo 10 números aleatório no terminal 0;

## Um geral:
O SO mantém toda a informação referente a cada processo em uma tabela de processos. Essa tabela contém o estado da CPU para esse processo, o estado do processo (em execução, pronto, bloqueado), informação que permite saber porque o processo está bloqueado e como/quando desbloqueá-lo. Para facilitar a implementação, mantém inclusive uma cópia de toda a memória principal. A troca de um processo para outro inclui o salvamento e recuperação de toda a memória do sistema. Mais tarde, quando falarmos sobre gerenciamento de memória, isso é otimizado.

O SO mantém um conjunto de programas que podem ser executados. Um programa é o conteúdo de um arquivo ".maq". Cada programa é designado por um número, e esse número é usado pela chamada de criação de um processo para identificar o programa a executar. Quando um processo for criado, o conteúdo da memória do processo é inicializado a partir do programa.

Na inicialização, o SO cria um processo para executar um programa inicial. Os demais processos são criados por chamadas "SO_CRIA" realizadas pelos processos em execução.

A única forma de bloqueio de um processo é por E/S. 

O escalonador é o mais simples possível, escolhe o primeiro dos processos prontos.

O funcionamento do SO no atendimento de uma interrupção é ser algo como:
- identifica o processo que foi interrompido
- salva o contexto (estado do processador, conteúdo da memória) na entrada correspondente ao processo interrompido na tabela de processos (ou não, porque pode ser que nenhum processo estivesse em execução)
- atende à interrupção
- verifica se deve desbloquear algum processo bloqueado
- chama o escalonador (escolhe o processo a executar)
- faz o despacho — recupera o contexto, correspondente ao processo escolhido

Caso o escalonador não tenha conseguido escolher nenhum processo (não tem nenhum processo pronto), o despacho simplesmente coloca a CPU em modo zumbi.

