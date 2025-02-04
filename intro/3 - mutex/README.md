# Mutex

## What is a mutex?

Mutex (mutual exclusion) is a synchronization primitive that enforces limits on access to a shared resource when we have multiple threads of execution.

We can use a mutex to lock a critical section of code that accesses a shared resource so that way only one thread of execution can enter the critical section of code at a time.

//
//  Mutex Version Execution Visualization
//
//
//
//  Thread #1             Thread #2              Bank Balance
//
//                        **  LOCK  **
//       
//  WAIT @ LOCK           Read Balance  <------------- 0
//       |                balance = 0
//       |
//       |                Deposit +200 
//       |                balance  = 200
//       |
//       |                Write Balance  ------------> 200
//       |                balance = 200
//       |
//   LOCK FREE            ** UNLOCK **
// 
//  **  LOCK  ** 
//
//  Read Balance  <----------------------------------- 200
//  balance = 200 
//
//  Deposit +300
//  balance = 500
//
//  Write Balance  ----------------------------------> 500
//  balance = 500
//
//  ** UNLOCK **
//