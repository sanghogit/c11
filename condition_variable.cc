// clang++ -g condition_variable.cc -lpthread
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <future>
#include <condition_variable>
#include <unistd.h>
using namespace std;

queue<int> iqueue;
condition_variable icond;
mutex imutex;

/*
notify_one() doesn't queue anything. If one thread calls notify_one 
  and there are no other threads wait(), notify_one() will not do anything.
Therefore, if you want producer-consumer work synchronousely, 
  the prducer should give time (e.g. sleep) to consumer to process data & wait
*/
void producer()
{
	int i = 0;

	while( i < 5 ) {
		// LOCK
		{
		lock_guard<mutex> lg {imutex};  // wait() temporily unlock mutex
					cout << "locked" << endl;
		iqueue.push( i++ );
					cout << "unlocked" << endl;
		}
		icond.notify_one();
		this_thread::sleep_for( chrono::milliseconds(10)); // give time to consumer
	}
}

/*
wait() unlock while waiting, relock on return.
wait() immediately unlock the mutex so as to allow the other thread 
  to acquire the mutex and make changes to program state. 
  When the other thread notifies, the wait() will attempt 
  to acquire the mutex again before returning
*/
void consumer()
{
	while( true ) {
		int i;
		{
		unique_lock<mutex> ul {imutex};
					cout << "\t\tbefore wait" << endl;
		icond.wait( ul, [] { return !iqueue.empty(); } );
					cout << "\t\tafter wait" << endl;

		while ( !iqueue.empty()) { 
			cout << "\t\tconsumed " << (i = iqueue.front()) << endl;
			iqueue.pop();
		}
		}
		if( i == 4 ) break;
	}
}

int main()
{
	auto f2 = async( launch::async, consumer );
	auto f1 = async( launch::async, producer );

/* same as above
	thread t1 { producer };
	thread t2 { consumer };

	t1.join();
	t2.join();
*/
}

