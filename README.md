# 🍝 Understand the 42's project Philosophers 🍴

42's project on concurrent programming, multi-threading and multiprocessing, on solving [The Dining Philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem).


## I - Introduction 👓


The Philosophers project at 42 is inspired by Edsger Dijkstra's "The Dining Philosophers problem" about concurrency and synchronization using threads, mutexes, and semaphores in programming. This classic computer science problem reinforces the capacity to manage shared resources in a multi-threaded environment while avoiding issues such as deadlocks and race conditions.


### 1 - Understanding the problem 🍽️

In this simulation, multiple philosophers sit around a circular table with a large bowl of spaghetti at the center. Each philosopher alternates between three states: eating, thinking, and sleeping. However, eating requires two forks, one in each hand, and there are only as many forks as philosophers. Therefore, each philosopher must compete with their neighbors for access to the forks.

The simulation is governed by the following constraints:

- A philosopher can only eat if they have access to both the left and right forks.

- If a philosopher does not eat within a specified time, they die of starvation.

- Philosophers do not communicate with one another and are unaware of the state of their neighbors.

- The simulation stops when a philosopher dies or when all philosophers have eaten a predetermined number of times.

### 2 - Project Implementation 🍽️

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


### 3 - Technical Requirements 🍽️

- **Global variables are forbidden.**

- **A precise logging system** is required to track state changes and detect starvation.

- **Thread safety** must be maintained to avoid race conditions and inconsistencies.

- **Concurrency management** is crucial, as improper synchronization could lead to deadlocks.
	A **deadlock** is a situation in which each thread waits for a resource held by another thread or a locked mutex.

- Must-have arguments:
	- `number_of_philosophers`: The number of philos and also the number of forks.

	- `time_to_die` (in milliseconds): If a philo couldn't start eating `time_to_die` milliseconds since the beginning of his last meal (or the simulation), he dies.

	- `time_to_eat` (in milliseconds): The time it takes for each philo to eat. During this time, he holds two forks.

	- `time_to_sleep` (in milliseconds): The time a philo spends to sleep.
	
	- `number_of_time_each_philosopher_must_eat` (optional): If all philos have eaten at least `number_of_time_each_philosopher_must_eat` times, the simulation stops. If not specified, the simulation stops when there is one philo who dies.

---

## II - Functions 🧰

### 1 - Threads and Mutexes 🔏

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


### 2 - Processes and Semaphores 🔒

 A **semaphore** is a mechanism used in multithreaded programs for managing the access to shared resources, such as memory or files, by the threads when multiple tasks or threads are running at the same time. Semaphores are very useful in process synchronization and multithreading.

 When the value of the semaphore is zero, any process that performs a wait operation will be blocked until another process performs a signal operation.

 The basic difference between semaphore and mutex is semaphore can lock/unlock multiple times between multiple threads, while mutex cannot lock/unlock difference threads at once.

These function are available in `semaphore.h` library:

- `sem_open()`: create a new or open an existing semaphore `name` with the initial `value` of semaphore.
	```c
	sem_t	*sem_open(char *name, O_CREAT | O_EXCL, 0644, int value);
	```
	It returns the address of new semaphore on success, otherwise it returns `SEM_FAILED`.

- `sem_close()`: close the semaphore `sem`
	```c
	int	sem_close(sem_t *sem);
	```
	It return `0` on success and `-1` if error.

- `sem_wait()`: lock a semaphore: check value of semaphore `sem`, if that value is greater than `0`, decrement it and start executing the next lines. Else, that value is `0`, it blocks the process/threads until either it rises above `0` or there's signal interrupts.
	```c
	int	sem_wait(sem_t *sem);
	```
	It return `0` on success. On error, the value of `sem` is unchanged and `-1` is returned.

- `sem_post()`: unlock the semaphore `sem` by incrementing the semaphore `sem` value.
	```c
	int	sem_post(sem_t *sem);
	```
	It return `0` on success. On error, the value of `sem` is unchanged and `-1` is returned.

- `sem_unlink()`: remove the semaphore referred to by `name`
	```c
	int	sem_unlink(char *name);
	```
	It return `0` on success and `-1` if error.


### 3 - Other functions ⏲️

- `usleep()`: suspend execution of the calling thread for atleast `usec` microsecond. 
	```c
	int usleep(useconds_t usec);
	```
	Return `0` on success and `-1` on error.

- `gettimeofday()`: get the time as well as the timezone. Return `0` on success and `-1` on failure (`<sys/time.h>`)
	The `timeval` structure gives the time exact in second and microsecond after the epoch time Jan 1, 1970
	```c
	struct timeval
	{
		time_t		tv_sec; // in seconds
		suseconds_t tv_usec; // in microseconds
	}
	```
	To calculate the given time in milliseconds we use the formula:
	```c
	tv_sec * 1000 + tv_usec / 1000
	```

- `memset`, `printf`, `malloc`, `free`, `write`

---

## III - Testing the programme 🧪

### 1 - Mandatory part 📕

#### 1. Compile programme

 In the folder `philo`, run one of the command in the Terminal:

```bash
make
make re
make all
```

#### 2. Run programme 
	
 Then run the command `./philo` with 4 or 5 arguments.
	
```bash
./philo num_philos time_to_die time_to_eat time_to_sleep max_meals
```

#### 3. Testing the thread error or race condition

 Using `valgrind` - `helgrind`

```bash
valgrind --tool=helgrind ./philo [...]
```

### 2 - Bonus part 🔖

#### 1. Compile programme

 In the folder `philo_bonus`, run one of the command in the Terminal:

```bash
make
make re
make all
make bonus
```

#### 2. Run programme 
	
 Then run the command `./philo_bonus` with 4 or 5 arguments.
	
```bash
./philo_bonus num_philos time_to_die time_to_eat time_to_sleep max_meals
```

#### 3. Testing the thread error or race condition

 Using `valgrind` - `helgrind`

```bash
valgrind --tool=helgrind ./philo_bonus [...]
```

---

## IV - Issues and Bugs 🐛

 Please feel free to create a new issue with the title and description on the issues page of this `42cursus-Philosophers` repository.
 
 If you have already found the solution to the problem, we would love to review your `pull request`!

 Thank you in advance and Happy coding!

---

### Reference
 - [Unix Threads in C](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)
 - [Concurrent programming, with examples](https://begriffs.com/posts/2020-03-23-concurrent-programming.html)
 - [Helgrind](https://valgrind.org/docs/manual/hg-manual.html)
