#include <stdio.h>
#include <stdlib.h>
#include "mem.h"
#include "cpu_estado.h"
#include "es.h"


#ifndef PROCESSO_H
#define PROCESSO_H

typedef struct processo_t processo_t;
typedef enum { pronto, em_execucao, bloqueado } processo_estado_t;

processo_t* processo_cria(int num, processo_estado_t estado);

//inicia a memória do processo quando criado
err_t processo_init_mem(processo_t *self);

// transfere o .maq para a memória do progrma 
err_t transf_mem(processo_t *self, int* progr, int tam_progr);

void processo_destroi(processo_t* self);

//muda o estado do processo para em_execução
void processo_executa(processo_t* self);

//muda o estado do processo para bloqueado
//salva junto ao processo:
//- estados da cpu e memoria no momento do bloqueio;
//- dispositivo que causou o bloqueio;
//- tipo de chamada que causou o bloqueio (e/s).
void processo_bloqueia(processo_t* self, mem_t* memoria, 
                      cpu_estado_t* cpu_estado, int disp, acesso_t chamada);

//muda o estado do processo para pronto
void processo_desbloqueia(processo_t* self);

// retorna o estado da memória do processo
mem_t* processo_mem(processo_t* self);

// retorna a última chamada de sistema feita pelo processo que causou bloqueio
acesso_t processo_chamada(processo_t* processo);

// retorna o estado da cpu do processo
cpu_estado_t* processo_cpu(processo_t* self) ;

// retorna o estado do processo (pronto, em_execucao, bloqueado)
processo_estado_t processo_estado(processo_t* self);

//retorna o numero do processo
int processo_num(processo_t* self) ;

//retorna o dispositivo que causou o último bloqueio do processo
int processo_disp(processo_t* processo);


#endif
