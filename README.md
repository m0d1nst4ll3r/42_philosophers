# 42_philosophers
42 - common core - ring #3


Goals

- Each philosopher is its own thread
- Each fork is a mutex (malloced array of mutexes)
- There needs to be a separate thread looking at thread states to terminate program
- Writes must be mutexed


Problems

Because when you thread a function you can only send 1 argument, everything needed by the function needs to be in a structure

There needs to be a system to check when philosophers last ate
Solution:
gettimeofday at start of philo loop execution - timestamps will be relative to that
when a philo stops eating, he calls gettimeofday and writes the value somewhere
that value is checked every few milliseconds by the monitoring thread against its own gettimeofday (ideally every millisecond)
in the absence of that value, time from execution start must be used

We need to decide where we stop execution against times to eat max
Probably we send the data to each philosopher, which instead of a simple while(1) loop has a while(eaten less than max), or while 1 if max is not defined. When a philo is done, it returns. The threads are joined, when they all return, the program ends.
However, since we also have the monitoring thread, that one thread needs to be detached, meaning it can't be joined. It's not supposed to finish.
Or, we make each philo not return, but instead write to a value which is checked by the monitor. When all the values are 1, the monitor knows to exit peacefully.
A question arises: if the monitor has too much to do, can it really run every millisecond or is it going to overload the cpu? Should we try to optimize it?

Optimizing the monitor:
It checks two things: if philos have all stopped or if a philo is dead.
We check death with timestamps - since the monitor runs every millisecond, it should not calculate something over and over again if it can help it.
First of all the timestamp that philos write should already be the time that they die, as simple comparison can be made without any add or sub.
We can't just say "a philosopher died", we need to know which one, so we can't try to compress the data, there need to be as many memory slots as philosophers.
The monitor HAS to check against every slot. Slight optimizations like bitwise might be possible.
Philos having all stopped is the same: an array of values. However, it can be more simple: it can be a single value which is incremented from 0, when it reaches the amount of philos, we're good. A simple comparison is possible there.

Question: can we exit before threads return? Or do we have to make them return?


Ideas on how to do this

- A structure for philosophers containing
two mutex addresses - points to left fork and right fork
the write mutex as address (will be shared by all)
how long they should wait for eating, sleeping, how many times
the address of the "I've eaten" variable to increment when being done
the address of the timestamp of this specific philosopher
the start timestamp

- A structure for the monitor containing
the amount of philos to check against for eating (this is checked whether we've defined it or not, whatever, we have to check anyway unless we make two different functions)
the address of the "I've eaten" variable to check
the address of the timestamp array
the start timestamp
the write mutex

- The philosopher logic
this is yet to be decided, there needs to be some sort of tactic for eating so they don't die too easily
the naive approach is to just have them eat as soon as they can with mutexes, that will fail the evaluation though
regardless, when a philo eats, its locks both of its mutexes, writes, sleeps, unlocks
after eating, it writes, sleeps
after sleeping, it writes and just wait for the next time to eat

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

(idea: "I've eaten" variable decremented instead so that we know when it reaches 0 - this way we don't have to pass another int to the monitor)

the program is ready to start, the start timestamp is written to an int, copied to all the philo structures and the monitor structure
philo die timestamps are start timestamp + time to die
threads created with each structure, by index, monitor thread created
threads are all joined, program returns after this line - the threads will never return anyway
