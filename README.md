# 🍝 Philosophers

> Philosophers es mi implementación del clásico problema de los **Dining Philosophers**, desarrollada como parte del **Common Core de 42**.  
> El objetivo de este proyecto es profundizar en la **programación concurrente**, trabajando con *threads*, *mutexes*, sincronización y control preciso del tiempo.

Este proyecto aborda uno de los problemas clásicos de concurrencia y permite comprender cómo gestionar correctamente recursos compartidos sin provocar **deadlocks**, **race conditions** o **starvation**.

---

## 📌 ¿Qué es Philosophers?

El problema de los filósofos comensales describe una situación en la que varios filósofos se sientan alrededor de una mesa circular. Entre cada filósofo hay un tenedor compartido.  
Cada filósofo alterna entre **pensar**, **comer** y **dormir**, pero para comer necesita tomar los dos tenedores adyacentes.

El reto consiste en permitir que todos los filósofos puedan comer respetando las reglas del problema y evitando bloqueos o comportamientos incorrectos derivados de una mala sincronización.

---

## 🎯 Objetivo del proyecto

El objetivo de este proyecto es crear una simulación que:

- Cree un thread independiente por cada filósofo  
- Gestione correctamente los recursos compartidos mediante mutexes  
- Evite deadlocks y starvation  
- Controle los tiempos con precisión en milisegundos  
- Termine correctamente cuando un filósofo muere o cuando todos han comido el número requerido de veces  
- Libere correctamente todos los recursos utilizados  

---

## ⚙️ Uso del programa

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

### Parámetros

- number_of_philosophers  
  Número de filósofos sentados alrededor de la mesa (y número de tenedores).

- time_to_die (ms)  
  Tiempo máximo que un filósofo puede pasar sin comer antes de morir.

- time_to_eat (ms)  
  Tiempo que tarda un filósofo en comer.

- time_to_sleep (ms)  
  Tiempo que el filósofo pasa durmiendo tras comer.

- number_of_times_each_philosopher_must_eat (opcional)  
  Si se especifica, la simulación termina cuando todos los filósofos han comido al menos ese número de veces.

---

## 🧠 Funcionamiento interno

Cada filósofo está representado por un thread independiente que ejecuta una rutina cíclica:

1. Pensar  
2. Tomar los tenedores necesarios  
3. Comer  
4. Soltar los tenedores  
5. Dormir  

Los tenedores se representan mediante mutexes, asegurando que solo un filósofo pueda utilizar un tenedor a la vez.

Existe además un sistema de monitorización que comprueba constantemente si algún filósofo ha superado el time_to_die o si todos han alcanzado el número de comidas requerido.

En caso de muerte de un filósofo, la simulación se detiene inmediatamente.

---

## 🚦 Señales y sincronización

El proyecto no depende de señales externas, pero implementa una sincronización estricta entre threads.

El acceso a los recursos compartidos como los tenedores, la escritura por pantalla y los estados globales está siempre protegido mediante mutexes.

Esto garantiza que las acciones se impriman de forma ordenada, que no se produzcan race conditions y que el estado de la simulación sea consistente.

La estrategia de sincronización está diseñada para evitar deadlocks y minimizar la posibilidad de starvation.

---

## 🛠️ Compilación

Para compilar el proyecto:

make

Comandos disponibles:

make clean  
make fclean  
make re  

---

## 🧪 Gestión de errores

El programa gestiona de forma controlada los errores que pueden producirse durante la ejecución:

- Argumentos inválidos o fuera de rango  
- Errores en la creación de threads  
- Errores en la inicialización de mutexes  
- Fallos durante la sincronización  

En todos los casos se muestra un mensaje de error claro, se liberan los recursos utilizados y el programa termina de forma segura sin dejar estados inconsistentes.

---

## 👤 Autor

Proyecto desarrollado por **ncheniou**  
Como parte del **Common Core de 42**.

Este proyecto me ha permitido profundizar en la programación concurrente, la sincronización de threads y la gestión correcta de recursos compartidos.

Este proyecto me ha permitido profundizar en la programación concurrente, entendiendo cómo sincronizar múltiples threads, proteger recursos compartidos y evitar problemas clásicos como *deadlocks* y *race conditions*.
