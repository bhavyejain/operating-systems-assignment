#include <iostream>
#include <thread>
#include <mutex>
#include <random>

using namespace std;

mutex MUTEX;
int VAL = 0;
int MAXRUN = 20;
int RES = 0;
void waitAgent()
{
    while (VAL != 0)
        ;
}
void signalAgent(int x)
{
    VAL = x;
    //cout<<VAL<<endl;
}
void signalSmoker()
{
    VAL = 0;
}
void waitSmoker(int x)
{
    while (VAL != x && MAXRUN > 0)
        ;
    RES = x;
}
void agent()
{
    while (MAXRUN > 0)
    {
        waitAgent();
        MUTEX.lock();
        int random = rand();
        random = random % 3 + 1;
        if (random == 1)
        {
            cout << "agent-> 1\n";
            signalAgent(1);
        }
        else if (random == 2)
        {
            cout << "agent-> 2\n";
            signalAgent(2);
        }
        else if (random == 3)
        {
            cout << "agent-> 3\n";
            signalAgent(3);
        }
        MUTEX.unlock();
        MAXRUN--;
    }
}

void smoker(int s)
{
    while (MAXRUN > 0)
    {
        waitSmoker(s);
        if (MAXRUN <= 0)
            break;
        MUTEX.lock();
        cout << "Cigarette is being smoked by smoker " << s << "\n";
        signalSmoker();
        MUTEX.unlock();
        MAXRUN--;
    }
}
void runThreads()
{
    thread t1(agent);
    thread t2(smoker, 1);
    thread t3(smoker, 2);
    thread t4(smoker, 3);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}

int main()
{
    srand(clock());
    cout << "Semaphores: Cigarette Smoker Problem \n";
    runThreads();
    return 0;
}