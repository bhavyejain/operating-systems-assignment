#include <iostream>
#include <thread>
#include <mutex>
#include <random>

using namespace std;

int RUNFOR = 20;
int n = 5;
int st[5] = {};
mutex MUTEX;
void waitPhilosopher(int x)
{
    while (st[(x + 1) % 5] == 1 || st[(x) % 5] == 1)
        ;
}
void signalEat(int x)
{
    st[(x + 1) % 5] = 1;
    st[x] = 1;
}
void signalRelease(int x)
{
    st[(x + 1) % 5] = 0;
    st[x] = 0;
}
void philosopher(int x)
{
    while (RUNFOR > 0)
    {
        MUTEX.lock();
        cout << "Philosopher number " << x + 1 << " wants to eat\n";
        MUTEX.unlock();
        waitPhilosopher(x);
        MUTEX.lock();
        signalEat(x);
        cout << "Philosopher number " << x + 1 << " is eating \n";
        MUTEX.unlock();
        MUTEX.lock();
        signalRelease(x);
        cout << "Philosopher number" << x + 1 << " is now thinking\n";
        MUTEX.unlock();
        RUNFOR--;
    }
}
void runThreads()
{
    thread t1(philosopher, 0);
    thread t2(philosopher, 1);
    thread t3(philosopher, 2);
    thread t4(philosopher, 3);
    thread t5(philosopher, 4);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
}

int main()
{
    cout << "Semaphores: Dining Philosophers \n";
    runThreads();
    return 0;
}