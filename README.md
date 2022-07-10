# 42_philosophers
42 - common core - ring #3

State

Almost done, philo func needs writing
Probably bugs here and there, need to test each func to make sure it works correctly
Might need to optimize or fix other problems - will see once we have a functional prog


Goals

- Each philosopher is its own thread
- Each fork is a mutex (malloced array of mutexes)
- There needs to be a separate thread looking at thread states to terminate program
- Writes must be mutexed


Brainstorm

The program is mostly coded, what remains is only the philo func

Philo func is the hard part. They need to have a logic so they don't die when they can not spend too much time to eat but there's a lot of them. In other words, they have to stop eating to let others eat. If it's a first come first serve, we can't know what'll happen.
Another detail is important: forks are shared. Two philos can eat at the same time, but they need to not be adjacent to each other.
The best way seems to be simple enough: each even numbered philo eats first, then odd, then even, etc...
However, how do we force them to do that through code logic.
They are allowed to know their own numbers, but they can't know if anyone else is eating. They can know for how long though. So a simple way would be, if you're even, eat instantly, if not, wait for the time taken to eat, and then eat. Seems simple enough.


Ideas on how to do this

- A structure for philosophers containing
two mutex addresses - points to left fork and right fork
the write mutex as address (will be shared by all)
how long they should wait for eating, sleeping, how many times
the address of the "I've eaten" variable to increment when being done
the address of the timestamp of this specific philosopher
the start timestamp

- A structure for the monitor containing
the address of the "I've eaten" variable to check
the address of the timestamp array
the start timestamp
the write mutex

- The monitor logic
checks if "I've eaten" variable is 0, if so, exit without saying anything
checks if the current timestamp is equal or superior to any of the timestamps from each of the philosopher
this could start taking a lot of time with a lot of philo threads, but hey. I can optimize later. plus it's not mandatory.
if so, print a "dead" message with the index of the dead philo, exits

- Execution order
interpret args, write them, error out if bad
create as many mutexes as philosophers
create as many structures as philosophers
create as many timestamps as philosophers (they're all arrays ofc)
create a struct for the monitor
create an int as "I've eaten" variable
create a write mutex
each philo structure is initialized:
	- its fork mutexes are assigned based on its index (pointers)
	- its time data is written to (sleep, eat, times to eat)
	- its timestamp points to its specific timestamp based on its index
	- the address to the incremented "I've eaten" variable
	- a single int that is its ID (index)
	- write mutex is assigned
the monitoring structure is initialized
	- address of the "I've eaten" variable
	- write mutex
	- start timestamp
	- address of philo die timestamps
the threads can now be launched:
all of the threads will not start executing before a "start" mutex is unlocked
this allows for threads to be created in any timeframe you want and not fuck up the timestamps
start mutex is locked
philo threads are created
monitor thread is created
start timestamp is written
death timers are all initialized to start timestamp + time to die
start mutex is unlocked

at this point the program goes into parallel execution, philo threads will do their thing, monitor thread will do its thing

all threads are joined, the program shouldn't ever go beyond this.
