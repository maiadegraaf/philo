# philo

<p align="center">
  <a href="https://github.com/maiadegraaf">
    <picture>
    <img alt="philosophers" src="https://user-images.githubusercontent.com/68693691/193335768-6f2799a9-6904-497b-b49a-707ac551e21d.png" width=350>
    </picture>
  </a>
</p>

*This project introduces the concepts of multi-threading and mutexes.*

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
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat
```

|   |   |
|---|---|
|`number_of_philosophers`|The number of philosophers (and forks).|
|`time_to_die`\*|How long it takes for the philosopher to die without eating.  Measured by the time since the beginning of their last meal, or the beginning of the simulation.|
|`time_to_eat`\*| The length of time a philosopher spends eating.|
|`time_to_sleep`\*| The length of time a philosopher spends sleeping. |
|[optional]`number_of_times_a_philosopher_must_eat`| The amount of a times each philosopher must eat before the simulation ends.  If not specified, the simulation only stops when a philosopher dies.|
*\*measured in milliseconds*