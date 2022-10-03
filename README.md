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

- [The Challenge](#the-challenge)
  - [Expected Input](#expected-input)
  - [Expected Output](#expected-output)
- [A Brief Guide to Threads and Mutexes](#a-brief-guide-to-threads-and-mutexes)
    - [pthread_create](#pthread_create)
    - [pthread_detach](#pthread_detach)
    - [pthread_join](#pthread_join)
    - [pthread_mutex_init](#pthread_mutex_init)
    - [pthread_mutex_destroy](#pthread_mutex_destroy)
    - [pthread_mutex_lock](#pthread_mutex_lock)
    - [pthread_mutex_unlock](#pthread_mutex_unlock)
- [Implementation](#implementation)
  - [Input and error handling](#input-and-error-handling)
  - [Bringing the Philosophers to Life](#bringing-the-philosophers-to-life)
  - [Monitoring](#monitoring)
  - [Avoiding Data Races](#avoiding-data-races)
- [Installation](#installation)


## The Challenge
This project is based on the well established [Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem).  It is set up as follows and demonstrated in the illustration above:
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
int pthread_detach(pthread_t thread);
```
*Indicates to the implementation that storage for the thread can be reclaimed when that thread terminates.*

- `pthread_t thread`: the target thread.

--- 
#### pthread_join
```C
int pthread_join(pthread_t thread, void **value_ptr);
```
*Waits for the thread to terminate, and optionally obtain its return value.*

- `pthread_t thread`: the target thread.
- `void **value_ptr`: if not `NULL`, where the value passed to `pthread_exit()` by the terminating thread is stored.

--- 
#### pthread_mutex_init
```C
int pthread_mutex_init(pthread_mutex_t *mutex,  const pthread_mutexattr_t *attr);
```

*Creates a new mutex.*

- `pthread_mutex_t *mutex`: the mutex object, contains the mutex ID.
-  `const pthread_mutexattr_t *attr`: attributes to assign to the mutex.  If `NULL`, the default attributes are used.

--- 
#### pthread_mutex_destroy
```C
int      pthread_mutex_destroy(pthread_mutex_t *mutex);
```

*Frees the resources allocated to the mutex.*

- `pthread_mutex_t *mutex`: The target mutex.

--- 
#### pthread_mutex_lock
```C
int pthread_mutex_lock(pthread_mutex_t *mutex);
```
*Locks the mutex.  If the mutex is already locked, the calling thread will block until the mutex becomes available.*

- `pthread_mutex_t *mutex`: The target mutex.

--- 
#### pthread_mutex_unlock
```C
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```
*If the current thread holds the lock on the mutex, this function will unlock it.*

- `pthread_mutex_t *mutex`: The target mutex.

---

**Return value:**
<br>
All of the above functions implement return values in the same way.

 If successful, the functions return zero, else an error number will be returned.

## Implementation
### Input and error handling
As always, the first thing the program does is parse the input and check for input errors.  

The errors include:
- The program only accepts four or five arguments.
- All of the arguments must be able to be converted to an `int`.
- There cannot be less than one philosopher.

If no errors are found, the input is then stored in a data struct `t_tools`.  An array of `t_philo`'s are created, each with its own `pthread_t` (thread) variable, and an array of `pthread_mutex_t` (mutexes) for each fork, both of which are the size of `n` , where `n` is the number of philosophers.  Both arrays are also stored in `t_tools`.  I choose to use an array of structs instead of a linked list as it allows for easy access to each philosopher without looping through a list, and as the number of philosophers is constant, it means the array can be malloc'ed at the beginning.  The `t_philo` struct also stores the time of its last meal, the amount of times it has eaten, and a pointer to the `t_tools` struct.  This means that each philosopher has access to the variables allocated by the input as well as the array of fork mutexes.

### Bringing the Philosophers to Life
When `pthread_create` is called, each thread it creates executes a function.  In my program that function is called `life`, which loops through each of the different phases; **eat**, **think**, and **sleep**. The most complicated of which is the **eating** phase.  The philosopher first has to determine which fork lies to their left and right, and then wait until each fork becomes available by attempting to unlock the forks respective mutex.  They **think** while they wait. Only when they have two forks they start eating. Once finished they simply unlock both mutexes.  They go to **sleep**, after which the cycle begins again. The cycle stops either if a philosopher has died or if the philosophers have eaten the set amount of times.

To avoid a **deadlock**, where all philosophers grab one fork each and none of them can eat, the program starts by staggering the philosophers. Philosophers with an even `id` grab a fork straight away, while philosophers with an uneven `id` wait for a short amount of time before they can start.

### Monitoring
While the parent thread waits for the rest of the threads to finish (I used `pthread_join()`), it monitors each philosopher.  The monitoring checks each philosopher for wether the last meal time exceeds the time to die.  If this is evaluated to true, the monitoring logs the death of the philosopher and ends the simulation.

### Avoiding Data Races
This was by far the most challenging part of creating this program.  There are two situations caused by the above implementation that could cause data races.  The first is that as monitoring is constantly checking the last meal time, each philosopher is also changing this variable, causing the possibility that both threads could be trying to access the variable at the same time.  The second occurs when a philosopher dies. The monitoring sets a boolean to true, which is check by each philosopher life cycle as well as the function that logs to the terminal.  When the boolean is true, both functions do not execute.  Again, this information is being accessed potentially simultaneously by multiple threads. To solve this problem, I implemented two more mutexes.  One for the last meal time, and the other for the end boolean.  Both have to helper functions to read and write, respectively.


## Installation
### Clone the repository:
``` 
git clone https://github.com/maiadegraaf/philo.git
cd philo
make
```

### Some commands to try:
The philosopher should not eat and should die:
```sh
./philo 1 800 200 200.
```
No philosopher should die and the program should continue indefinitely:

```sh
./philo 5 800 200 200
```
No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times:
```sh
./philo 5 800 200 200 7
```
No philosopher should die and the program should continue indefinitely:
```sh
./philo 4 410 200 200
```

One philosopher should die:
```sh
./philo 4 310 200 100
```

*Keep in mind that only slower computers this program might operate differently and a philosopher could die when they're not supposed.*
