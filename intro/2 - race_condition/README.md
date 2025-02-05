# Race Condition

## What is a race condition?

A race condition occurs when a program depends on the timing of one or more events to function correctly.

A race condition typically occurs when multiple threads access a shared variable (or state) and they try to change it at the same time.

Race conditions are an intra-process thing, not inter-processes. It means there is no race condition between processes.


//  Visualization of the above program's execution.  When the two deposit 
//  functions run at the same time, the execution of statements over time
//  may interleave (and our simulated "network delay" further assures this),
//  causing a race condition to occur when they access the same shared state.
//  See how both threads access the balance, update the balance, and write 
//  the balance in such a way as to result in an incorrect balance!  
//
//
//  Thread #1             Thread #2              Bank Balance
//     
//  Read Balance  <----------------------------------- 0
//  balance = 0 
//                        Read Balance  <------------- 0
//                        balance = 0
//
//  Deposit +300
//  balance = 300
//                        Deposit +200 
//                        balance  = 200
//
//  Write Balance  ----------------------------------> 300
//  balance = 300
//                        Write Balance  ------------> 200
//                        balance = 200

