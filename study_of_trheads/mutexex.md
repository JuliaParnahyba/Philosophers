# MUTEXES
_Um mutex (mutual exclusion) é usado para prevenir condições de corrido (Race Conditions), garantindo que apenas um **thread** por vez tenha acesso a uma seção crítica._

## PRINCIPAIS FUNÇÕES
1. ***PTHREAD_MUTEX_INIT***
    * **Uso:** inicializar um mutex

    * **Protótipo:** 
        ```c
        int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
        ```
    
    * **Parâmetro:**
        - `mutex`: ponteiro para o mutex a ser inicializado
        - `attr`: atributo do mutex (use `NULL`para valores padrão)
    
    * **Exemplo:**
        ```c
        pthread_mutex_t fork_mutex;
        pthread_mutex_init(&fork_mutex, NULL);
        ```
2. ***PTHREAD_MUTEX_LOCK***
    * **Uso:** trava o mutex, ou seja, bloqueia o acesso por outras threads

    * **Protótipo:**
        ```c
        int pthread_mutex_lock(pthread_mutex_t *mutex);
        ```
    
    * **Parâmetro:**
        - `mutex`: mutex a ser travado
    
    * **Exemplo:**
        ```c
        pthread_mutex_lock(&fork_mutex);
        ```

3. ***PTHREAD_MUTEX_UNLOCK***
    * **Uso:** destrava o mutex, voltando a permitir o acesso por outras treads

    * **Protótipo:**
        ```c
        int pthread_mutex_unlock(pthread_mutex_t *mutex);
        ```
    
    * **Parâmetros:**
        - `mutex`: mutex a ser destarvado
    
    * **Exemplo:**
        ```c
        pthread_mutex_unlock(&fork_mutex);
        ```

4. ***PTHREAD_MUTEX_DESTROY***
    * **Uso:** destroi um mutex, liberando o recurso.

    * **Protótipo:**
        ```c
        pthread_mutex_destroy(pthread_mutex_t *mutex)
        ```
    
    * **Parâmetros:**
        - `mutex`: Mutex a ser destroído

    * **Exemplo:**
        ```c
        pthread_mutex_destroy(&fork_mutex);
        ```