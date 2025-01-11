# THREADS
_Uma **thread** é uma unidade de execução em um processo. Várias **threads** podem ser executadas pralelamente em um programa, compartilhando a mesma memória._

_No projeto em questão, cada **personagem** é representado por uma **thread**_


## PRINCIPAIS FUNÇÕES
1. ***PTHREAD_CREATE***
    * **Uso:** cria uma nova tread

    * **Protótipo:** 
        ```c
        int pthread_creat(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
        ```

    * **Parâmetros:**
        - `thread`: ponteiro para armazenas o indentificador da thread criada;
        - `attr`: atributos da thread (usar `NULL` para valores padrão);
        - `start_routine`: função que será executada pela thread;
        - `arg`: argumento para a função da thread;
    
    * **Retorno:** em caso de sucesso retorna 0 (zero), em caso de erro outro valor.

    * **Exemplo:**
        ```c
        void    *philosopher(void *arg)
        {
            printf("Filósofo %d está pensando.\n", *(int *)args);
            return ;
        }

        pthread_t thread;
        int id = 1;
        pthread_creat(&thread, NULL, philosopher, &id);
        pthread_join(thread, NULL);
        ```
  
2. ***PTHREAD_JOIN***
    * **Uso:** aguarda uma thread terminar

    * **Protótipo:**
        ```c
        int pthread_join(pthread_t thread, void **retvall);
        ```
    
    * **Parâmetros:**
        - `thread`: thread que quer aguardar
        - `retval`: retorno da thread (pode ser `NULL`)
    
    * **Exemplo:**
        ```c
        pthread_join(thread, NULL);
        ```