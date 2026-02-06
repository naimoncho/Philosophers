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

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

## 🧠 Funcionamiento interno

Cada filósofo está representado por un **thread independiente** que ejecuta una rutina cíclica compuesta por las siguientes acciones:

1. Pensar  
2. Tomar los tenedores necesarios  
3. Comer  
4. Soltar los tenedores  
5. Dormir  

Los tenedores se representan mediante **mutexes**, asegurando que solo un filósofo pueda utilizar un tenedor a la vez.  
Esto evita condiciones de carrera y accesos simultáneos a recursos compartidos.

Además, existe un sistema de monitorización que comprueba continuamente:

- Si algún filósofo ha superado el `time_to_die` sin comer
- Si todos los filósofos han alcanzado el número de comidas requerido (cuando se especifica)

En caso de que un filósofo muera, la simulación se detiene inmediatamente de forma controlada.

---

## 🚦 Señales y sincronización

Aunque el proyecto no depende de señales del sistema como `SIGINT`, se implementa una **sincronización estricta** para garantizar un comportamiento correcto y determinista.

El acceso a los siguientes recursos compartidos está siempre protegido mediante **mutexes**:

- Tenedores
- Escritura por pantalla
- Estados globales del programa

Esto asegura que:
- Las acciones se impriman sin solaparse
- El estado de la simulación sea consistente
- No se produzcan condiciones de carrera

La sincronización está diseñada para evitar **deadlocks** y minimizar la posibilidad de **starvation**.

---

## 🛠️ Compilación

Para compilar el proyecto:
make
Para limpiar los archivos objeto:
make clean
Para realizar una limpieza completa:
make fclean
Para recompilar el proyecto desde cero:
make re

## 🧪 Gestión de errores

El programa gestiona de forma controlada los errores que pueden producirse durante la inicialización y ejecución de la simulación, manteniendo siempre un estado consistente.

Se comprueban, entre otros, los siguientes casos:

- Número de argumentos incorrecto
- Argumentos no numéricos o fuera de rango
- Errores en la creación de threads (`pthread_create`)
- Errores en la inicialización o destrucción de mutexes
- Fallos durante la sincronización de recursos compartidos

En todos los casos:
- Se muestra un mensaje de error claro y descriptivo
- Se liberan correctamente los recursos reservados
- El programa termina de forma segura sin producir comportamientos indefinidos

## 👤 Autor

Proyecto desarrollado por **ncheniou**  
Como parte del **Common Core de 42**.

Este proyecto me ha permitido profundizar en la programación concurrente, entendiendo cómo sincronizar múltiples threads, proteger recursos compartidos y evitar problemas clásicos como *deadlocks* y *race conditions*.
