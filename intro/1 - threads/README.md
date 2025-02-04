# Threads

## What is a Thread?

A thread is a single sequence stream within a process. Because threads have some of the properties of processes, they are sometimes called lightweight processes.


## What are the differences between process and thread?

Threads are not independent from each other unlike processes. A thread shares with other their code section, data section and OS resources like open files and signals. But, like processes, a thread has its own program counter, a register set, and a stack space.

## Why Multithreading?

Threads are the faster way to improve application through parallelism (to compare with processes) because threads creation, termination, context switching and communication between threads,... are much faster.

## POSIX Threads (pthreads)

`ptheads` is and execution model that exists independently from a programming language, as well as a parallel execution model. It allows a program to control multiple different flows of work that overlap in time. Each flow of work is referred to as a thread.