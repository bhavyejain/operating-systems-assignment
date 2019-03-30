#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex MUTEX;
int write_read = 1;
int readerNumber = 0;
int RUNFOR = 10;
int mut = 1;

void wait(string SEM)
{
    while (write_read == 0)
        ;
    write_read--;
}

void signal(string SEM)
{
    write_read++;
}
void writer()
{
    while (RUNFOR > 0)
    {
        wait("empty");
        cout << "Writing to file is going on\n";
        RUNFOR--;
        signal("full");
    }
}

void reader()
{
    while (RUNFOR > 0)
    {
        MUTEX.lock();
        readerNumber++;
        if (readerNumber == 1)
            wait("wrt");
        MUTEX.unlock();
        cout << "Reading from file is going on\n";
        MUTEX.lock();
        readerNumber--;
        if (readerNumber == 0)
            signal("full");
        MUTEX.unlock();
        RUNFOR--;
    }
}
void runThreads()
{
    thread writer_thread(writer);
    thread reader_thread(reader);
    writer_thread.join();
    reader_thread.join();
}

int main()
{
    cout << "Semaphores: Starve free reader writer solution \n";
    runThreads();
    return 0;
}