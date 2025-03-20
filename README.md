# Understand the 42's project Philosophers
42's project on concurrent programming, multi-threading and multiprocessing, on solving [The Dining Philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem).



## I - Introduction


The Philosophers project at 42 is inspired by Edsger Dijkstra's "The Dining Philosophers problem" about concurrency and synchronization using threads, mutexes, and semaphores in programming. This classic computer science problem reinforces the capacity to manage shared resources in a multi-threaded environment while avoiding issues such as deadlocks and race conditions.


### 1 - Understanding the problem

In this simulation, multiple philosophers sit around a circular table with a large bowl of spaghetti at the center. Each philosopher alternates between three states: eating, thinking, and sleeping. However, eating requires two forks, one in each hand, and there are only as many forks as philosophers. Therefore, each philosopher must compete with their neighbors for access to the forks.

The simulation is governed by the following constraints:

- A philosopher can only eat if they have access to both the left and right forks.

- If a philosopher does not eat within a specified time, they die of starvation.

- Philosophers do not communicate with one another and are unaware of the state of their neighbors.

- The simulation stops when a philosopher dies or when all philosophers have eaten a predetermined number of times.

### 2 - Project Implementation

#### 2.1 - Mandatory Part: Threads and Mutexes

The mandatory implementation requires using threads and mutexes to synchronize access to shared resources (forks). Each philosopher is represented as a thread, and each fork is protected by a mutex to prevent simultaneous access by multiple philosophers. The key objectives of this implementation are:

- Ensuring that philosophers do not pick up forks simultaneously, causing deadlocks.

- Managing shared resources safely using mutex locks and unlocks.

- Logging each philosopher's state changes in a way that avoids data races.


#### 2.2 - Bonus Part: Processes and Semaphores

The bonus implementation increases the complexity by using processes and semaphores instead of threads and mutexes. The key differences are:

- Each philosopher is a separate process rather than a thread.

- Forks are represented by a semaphore, ensuring mutual exclusion for resource allocation.

- The main process oversees the simulation but does not participate as a philosopher.


### 3 - Technical Requirements

- **Global variables are forbidden.**

- **A precise logging system** is required to track state changes and detect starvation.

- **Thread safety** must be maintained to avoid race conditions and inconsistencies.

- **Concurrency management** is crucial, as improper synchronization could lead to deadlocks.

- Must-have arguments:
	- `number_of_philosophers`: The number of philos and also the number of forks.

	- `time_to_die` (in milliseconds): If a philo couldn't start eating `time_to_die` milliseconds since the beginning of his last meal (or the simulation), he dies.

	- `time_to_eat` (in milliseconds): The time it takes for each philo to eat. During this time, he holds two forks.

	- `time_to_sleep` (in milliseconds): The time a philo spends to sleep.
	
	- `number_of_time_each_philosopher_must_eat` (optional): If all philos have eaten at least `number_of_time_each_philosopher_must_eat` times, the simulation stops. If not specified, the simulation stops when there is one philo who dies.


## II - Functions

### 1 - Threads and Mutexes

These function are available in `pthread.h` library.

- `pthread_create()`: start a new thread in the calling process
	```c
	int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
	```
	Return `0` on success and an error number on error.

- `pthread_join()`: waits for the thread specified by `thread` to terminate. If that thread has already terminated, then `pthread_join()` returns immediately.

	```c
	int pthread_join(pthread_t thread, void **retval);
	```
	Return `0` on success and an error number on error.

- `pthread_detach()`: marks the thread identified by `thread` as detached. When a detached thread terminates, its resources are automatically released back to the system without the need for another thread to join with the terminated thread.
	```c
	int pthread_detach(pthrad_t thread);
	```
	Return `0` on success and an error number on error.
	
	`pthread_detach()` and `pthread_join()` are two sides of the same coin, both aiding in the proper management of thread resources but with distinct approaches. While `pthread_join()` involves **waiting** for the thread, **retrieving** its results, and then **cleaning up**, `pthread_detach()` sets the thread to **automatically clean up** after itself once it's done.

- `pthread_mutex_init()`: initializes the mutex referenced by `mutex` with attributes specified by `attr`.
	```c
	int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
	```
	Return `0` on success.

- `pthread_mutex_destroy()`: destroy the mutex object referenced by `mutex`. The mutex object becomes uninitialized and it can be reinitialized by using `pthread_mutex_init()`. It shall be safe to destroy an initialized mutex that is *unlocked*.
	```c
	int pthread_mutex_destroy(pthread_mutex_t *mutex);
	```
	Return `0` on success.

- `pthread_mutex_lock()`: the mutex object referenced by `mutex` shall be locked by a call to `thread_mutex_lock()` that return `0` or `[EOWNERDEAD]`. If the mutex is already locked by another thread, the calling thread shall block until the mutex becomes available. This operation shall return with the mutex object referenced by `mutex` in the locked state with the calling thread as its owners.
	```c
	int pthread_mutex_lock(pthread_mutex_t *mutex);
	```
	Return `0` on success.

- `pthread_mutex_unlock()`: releases the mutex object referenced by `mutex`.
	```c
	int pthread_mutex_unlock(pthread_mutex_t *mutex);
	```
	Return `0` on success.


### 2 - Processes and Semaphores



### 3 - Other functions

- `usleep()`: suspend execution of the calling thread for atleast *usec* microsecond. Return `0` on success and `-1` on error.

- `gettimeofday()`: get the time as well as the timezone. Return `0` on success and `-1` on failure (`<sys/time.h>`)

- `memset`, `printf`, `malloc`, `free`, `write`


## III - Pseudocode

### 1 - Mandatory part




### 2 - Bonus part









 ---

 #### E - Reference
 - [Unix Threads in C](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)

