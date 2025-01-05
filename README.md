# Philosophers - 42 Rio

> "I never thought philosophy would be so deadly"


## Descrição do Projeto
O projeto **Philosophers** explora os conceitos básicos de threading em C, simulando o clássico problema dos filósofos comensais. A proposta é desenvolver um programa que gerencie múltiplos threads e mutexes, garantindo a sincronização adequada para evitar condições de corrida e impasses.

A implementação visa reproduzir uma mesa com filósofos que alternam entre comer, pensar e dormir, respeitando as regras do problema:

- Cada filósofo precisa de dois garfos para comer.
- Os filósofos não se comunicam entre si.
- Um filósofo morre se ficar tempo demais sem comer.

A simulação termina quando um filósofo morre ou todos comem um número específico de vezes (se configurado).


## Recursos Utilizados
- **Linguagem**: C
- **Threading**: `pthread_create`, `pthread_detach`, `pthread_join`
- **Sincronização**: `pthread_mutex_init`, `pthread_mutex_lock`, `pthread_mutex_unlock`, `pthread_mutex_destroy`
- **Temporização**: `usleep`, `gettimeofday`
- **Memória**: `malloc`, `free`
- **Utilitários**: `printf`, `write`, `memset`


## Regras Globais
- **Sem variáveis globais.** 
- **O uso de mutex é obrigatório** para controlar o acesso aos garfos.
- **Não pode haver vazamento de memória.** Toda memória alocada deve ser liberada ao final do programa.
- **Logs precisos e sincronizados:** qualquer mudança de estado de um filósofo deve ser registrada imediatamente.
- **Formato do log:**
    [timestamp_in_ms] X has taken a fork
    [timestamp_in_ms] X is eating
    [timestamp_in_ms] X is sleeping
    [timestamp_in_ms] X is thinking
    [timestamp_in_ms] X died


## Estrutura do Projeto
- **`philo/`** – Contém todos os arquivos do projeto.
- **`Makefile`** – Automação da compilação com as regras: `all`, `clean`, `fclean` e `re`.
- **Arquivos Fonte (`.c` e `.h`)** – Código organizado seguindo a [Norm da 42](https://github.com/42School/norminette).


## Aprendizados Adquiridos
- **Gerenciamento de threads e mutexes.**
- **Controle de concorrência e prevenção de race conditions.**
- **Resolução de deadlocks e starvation.**
- **Sincronização de tempo e operações.**
- **Implementação prática de algoritmos clássicos de sincronização.**


## Regras de Avaliação
- O projeto segue a [Norm da 42](https://github.com/42School/norminette).
- A avaliação envolve:
  - **Apresentação (defense)**
  - **Peer-evaluation**


##
© 2025 Parnahyba - 42 Rio





