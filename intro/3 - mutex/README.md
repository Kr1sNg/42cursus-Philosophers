# Mutex

## What is a race condition?

A race condition occurs when a program depends on the timing of one or more events to function correctly.

A race condition typically occurs when multiple threads access a shared variable (or state) at the same time.

## What is a mutex?

Mutex (mutual exclusion) is a synchronization primitive that enforces limits on access to a shared resource when we have multiple threads of execution.

We can use a mutex to lock a critical section of code that accesses a shared resource so that way only one thread of execution can enter the critical section of code at a time.

