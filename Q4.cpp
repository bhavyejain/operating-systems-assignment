#include <iostream>
#include <thread>
#include <mutex>
#include <random>

using namespace std;

mutex MUTEX;
int MAXRUN = 20;
int FREESEATS = 10;
int customerNumber = 0;
int barberNumber = 1;
void waitBarber()
{
    while (customerNumber <= 0)
        ;
}
void signalBarber()
{
    customerNumber--;
    if (customerNumber == 0)
        cout << "Barber is sleeping\n";
}
void signalCustomer()
{
    customerNumber++;
    if (customerNumber == 1)
        cout << "Barber wakes up\n";
}
void barber()
{
    while (MAXRUN > 0)
    {
        waitBarber();
        MUTEX.lock();
        FREESEATS++;
        cout << "Barber is cutting hair\n";
        signalBarber();
        MUTEX.unlock();
        MAXRUN--;
    }
}
void customer()
{
    while (MAXRUN > 0)
    {
        MUTEX.lock();
        if (FREESEATS > 0)
        {
            FREESEATS--;
            cout << "Customer enters : " << customerNumber + 1 << "\n";
            signalCustomer();
            MUTEX.unlock();
        }
        else
        {
            cout << "No seat is empty for new customer"
                 << "\n";
            MUTEX.unlock();
        }
        MAXRUN--;
    }
}

void runThreads()
{
    thread customer_thread(customer);
    thread barber_thread(barber);
    customer_thread.join();
    barber_thread.join();
}

int main()
{
    cout << "Semaphores: Sleeping Barber Problem\n";
    runThreads();
    return 0;
}