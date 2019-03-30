#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex MUTEX;
int BUFFER_SIZE = 200;
int number = 0;
int maximum = 20;
int turn = 0;
int mut = 1;

void wait(string SEMA)
{
    if (SEMA == "empty")
    {
        while (number == BUFFER_SIZE)
            ;
        mut--;
    }
    else
    {
        while (number == 0)
            ;
        mut--;
    }
}
void signal(string SEMA)
{
    if (SEMA == "empty")
    {
        mut++;
    }
    else
    {
        mut++;
    }
}
void producer()
{
    while (maximum > 0)
    {
        wait("empty");
        MUTEX.lock();
        number += 1;
        cout << "The Producer has produced " << number << "\n";
        maximum -= 1;
        MUTEX.unlock();
        signal("full");
    }
}
void consumer()
{
    while (maximum > 0)
    {
        wait("full");
        MUTEX.lock();
        cout << "The Consumer has consumed " << number << "\n";
        number -= 1;
        maximum -= 1;
        MUTEX.unlock();
        signal("empty");
    }
}
void runThreads()
{
    thread t1(producer);
    thread t2(consumer);
    t1.join();
    t2.join();
}
int main()
{
    cout << "Semophore: Producer Consumer \n";
    runThreads();
    return 0;
}