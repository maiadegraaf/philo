# philo

<p align="center">
  <a href="https://github.com/maiadegraaf">
    <picture>
    <img alt="philosophers" src="https://user-images.githubusercontent.com/68693691/193335768-6f2799a9-6904-497b-b49a-707ac551e21d.png" width=350>
    </picture>
  </a>
</p>

*This project introduces the concepts of multi-threading and mutexes.*

## Table of Contents
- [philo](#philo)
  - [Table of Contents](#table-of-contents)
  - [The Challenge](#the-challenge)
    - [Expected Input](#expected-input)
    - [Expected Output](#expected-output)
  - [A Brief Guide to Threads and Mutexes](#a-brief-guide-to-threads-and-mutexes)
      - [pthread_create](#pthread_create)
  - [- `void *arg`: the argument to pass to the above function.](#--void-arg-the-argument-to-pass-to-the-above-function)
      - [pthread_detach](#pthread_detach)
      - [pthread_join](#pthread_join)
      - [pthread_mutex_init](#pthread_mutex_init)
      - [pthread_mutex_destroy](#pthread_mutex_destroy)
      - [pthread_mutex_lock](#pthread_mutex_lock)
      - [pthread_mutex_unlock](#pthread_mutex_unlock)


## The Challenge
This project is based on the well established [Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem).  It is set up as follows:
- One or more philosopher sit at a round table, at the center of which is a bowl of spaghetti.
- There are as many forks as philosophers, one between each philosopher.  A fork can only be used by the philosophers sitting directly next to it.
- The philosophers can only eat when they are holding a fork in each hand.  Once they have finished eating they put down the forks.
- The philosophers alternate between **eating**, **sleeping**, and of course **thinking**.  They cannot do two things at once.
- If a philosopher goes without eating for too long they will starve.
- The philosophers cannot communicate.

The goal is ultimately to prevent the philosophers from dying, or in other words, prevent the program from deadlocking, in which progress is no longer possible.

Furthermore each philosopher will be its own process or thread, and each fork has its own mutex.

### Expected Input
The program runs with the following arguments:<br>
```sh
./philo num_of_philo time_to_die time_to_eat time_to_sleep [num_eat]
```

| Argument                | Explanation                                                                                                                                                    |
| ----------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `num_of_philo`          | The number of philosophers (and forks).                                                                                                                        |
| `time_to_die`\*         | How long it takes for the philosopher to die without eating.  Measured by the time since the beginning of their last meal, or the beginning of the simulation. |
| `time_to_eat`\*         | The length of time a philosopher spends eating.                                                                                                                |
| `time_to_sleep`\*       | The length of time a philosopher spends sleeping.                                                                                                              |
| [optional]<br>`num_eat` | The amount of a times each philosopher must eat before the simulation ends.  If not specified, the simulation only stops when a philosopher dies.              |
*\*measured in milliseconds*
### Expected Output
The program logs the philosophers actions to the terminal, where `[time_stamp]` is the time since the start of the simulation, and `[x]` is the philosophers number.:

```
[time_stamp] Philosopher [x] is thinking 🤔
[time_stamp] Philosopher [x] has picked up a 🤛fork
[time_stamp] Philosopher [x] has picked up a 🤛fork🤜
[time_stamp] Philosopher [x] is eating 🍝
[time_stamp] Philosopher [x] is sleeping 💤
[time_stamp] Philosopher [x] is thinking 🤔
```

When a philosopher dies, the program will display the following message and end the simulation.
```
[time_stamp] Philosopher [x] has died 💀
```

## A Brief Guide to Threads and Mutexes
The core of this project boils down to tackling parallel execution, which is essentially creating multiple simultaneous work flows or processes. A single work flow is referred to as a **thread**.

A **mutex** (mutual exclusion), also referred to as a lock, is a mechanism used when there are multiple threads to limit access to a resource. It assures that multiple threads cannot write or read from a resource at the same time, therefore guaranteeing that one thread isn't reading a resource while another is modifying it.

Both are controlled through functions from the `pthread.h` library. The following are the functions we are allowed to use for this project:

---

#### pthread_create

```C
int pthread_create(pthread_t *thread, pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
```
*Creates a new thread.*
- `pthread_t *thread`: the thread object, contains the thread ID.
- `pthread_attr_t *attr`: attributes to assign to the thread.  If `NULL`, the default attributes are used.
- `void *(*start_routine)(void *)`: the function the thread executes.
- `void *arg`: the argument to pass to the above function.
---
#### pthread_detach
```C
```
--- 
#### pthread_join
```C
int pthread_join(pthread_t thread, void **value_ptr);
```
*Suspends execution of the calling thread until the target thread terminates unless the target thread has already terminated.*

- `pthread_t thread`: the target thread.
- `void **value_ptr`: if not `NULL`, where the value passed to `pthread_exit()` by the terminating thread is stored.

--- 
#### pthread_mutex_init
```C
```
--- 
#### pthread_mutex_destroy
```C
```
--- 
#### pthread_mutex_lock
```C
```
--- 
#### pthread_mutex_unlock
```C
```