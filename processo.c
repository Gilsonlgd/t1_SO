#include <stdlib.h>
#include <stdbool.h>
#include "processo.h"
#include "mem.h"
#include "cpu_estado.h"
#include "es.h"
#include "contr.h"

struct processo_t {
  int num;
  int disp;
  acesso_t chamada_bloqueio;
  processo_estado_t estado;
  mem_t* memoria;
  cpu_estado_t* cpu_estado;
};

processo_t *processo_cria(int num, processo_estado_t estado)
{
    processo_t *self;
    self = malloc(sizeof(processo_t));
    self->num = num;
    self->estado = estado;
    self->cpu_estado = cpue_cria();
    self->disp = 0;
    self->chamada_bloqueio = 0;
    self->memoria = mem_cria(MEM_TAM);
    return self;
}

void processo_init_mem(processo_t *self)
{
    int num = self->num;

    switch (num)
    {
    case 1:
        int progr[] = {
            #include "p1.maq"
        };
        transf_mem(self, progr);
    case 2:
        int progr[] = {
            #include "p2.maq"
        };
        transf_mem(self, progr);
    case 3:
        int progr[] = {
            #include "p3.maq"
        };
        transf_mem(self, progr);
    default:
        int* progr = NULL;
        transf_mem(self, progr);
    }
}

void transf_mem(processo_t *self, int* progr)
{
  // programa para executar na nossa CPU
  int tam_progr = sizeof(progr)/sizeof(progr[0]);

  if(progr != NULL) {
    mem_t *mem = self->memoria;
    for (int i = 0; i < tam_progr; i++) {
        if (mem_escreve(mem, i, progr[i]) != ERR_OK) {
        t_printf("so.init_mem: erro de memória, endereco %d\n", i);
        panico(self);
        }
    }
  }
}

void processo_destroi(processo_t* self)
{
    free(self);
}

void processo_executa(processo_t* self) {
    self->estado = em_execucao;
}

void processo_bloqueia(processo_t* self, mem_t* memoria, cpu_estado_t* cpu_estado, 
                      int disp, acesso_t chamada)
{
    self->estado = bloqueado;
    self->disp = disp;
    self->chamada_bloqueio = chamada;
    cpue_copia(cpu_estado, self->cpu_estado);
    mem_copia(self->memoria, memoria);
}

void processo_desbloqueia(processo_t* self)
{
    self->estado = pronto;
}

mem_t* processo_mem(processo_t* self) {
    return self->memoria;
}

acesso_t processo_chamada(processo_t* processo)
{
    return processo->chamada_bloqueio;
}

cpu_estado_t* processo_cpu(processo_t* self) {
    return self->cpu_estado;
}

processo_estado_t processo_estado(processo_t* self){
    return self->estado;
}

int processo_num(processo_t* self) {
    return self->num;
}

int processo_disp(processo_t* processo)
{
    return processo->disp;
}



