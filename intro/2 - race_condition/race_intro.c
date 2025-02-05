#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

int balance = 0;

int read_balance()
{
	usleep(250000);
	return balance;
}

void write_balance(int new_balance)
{
	usleep(250000);
	balance = new_balance;
}

void *deposit(void *amount)
{
	int account_balance = read_balance();
	account_balance += *((int *)amount);
	write_balance(account_balance);
	return NULL;
}

int main()
{
	int before = read_balance();
	printf("Before: %d\n", before);

	pthread_t thread1;
	pthread_t thread2;
	
	int deposit1 = 300;
	int deposit2 = 200;

	pthread_create(&thread1, NULL, deposit, (void *)&deposit1);
	pthread_create(&thread2, NULL, deposit, (void *)&deposit2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	int after = read_balance();
	printf("After: %d\n", after);
}
//
//	Shared state when both Thread 1 and 2 can get assess and change the Bank Balance
//		=> This is Race condition
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
//
//