# Philosophers@42 - Take forks, eat, sleep, think, repeat

In this project you will implement 3 solutions to the Dining Philosophers problem using 
(1) threads & mutexes, 
(2) threads & semaphores and 
(3) processes & semaphores

* [What's the Dining Philosophers problem?](#whats-the-dining-philosophers-problem)
* [How-to-solve-the-DPP](#how-to-solve-the-dpp)
* [How do I run this?](#how-do-i-run-this)
* [Project status](#project-status)
* [Resources](#resources)


## What's the Dining Philosophers problem?

The Dining Philosophers is a classical computer science problem about **shared resources** and **concurrency**.

If you are not familiar with it, you could start with [this article](https://medium.com/swlh/the-dining-philosophers-problem-bbdb92e6b788).


## How to solve the DPP?

In each of the solutions, the program will be given as arguments the _number of philosophers_, their _time to die_ (i.e time after which they die if they have not eaten), _time to eat_ (i.e how long they will eat), _time to sleep_ and optionally, the _number of meals_.

In the case where no number of meals is given, the program should be able to go on forever.

A few constrains are given regarding the library functions we are allowed to use. If you want to read the project instructions click [here](philosophers.en.subject.pdf)

### Solution 1

In the first solution, philosophers are represented as **threads and mutexes** are used to managed the shared resources. 


### Solution 2

In the second solution, philosophers are represented as **threads and semaphores** are used to managed the shared resources.


### Solution 3

Lastly, in the third solution, philosophers are represented as **processes and semaphores** are used to managed the shared resources.

## How do I run this?

```bash
git clone https://github.com/lmalki-h/philosophers
cd philosophers/philo_one 
make
./philo_one 5 410 200 200
```

## Project status

This project is in progress...

## Resources

https://sites.uclouvain.be/SystInfo/notes/Theorie/Threads/coordination.html
