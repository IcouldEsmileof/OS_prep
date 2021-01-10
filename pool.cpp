#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
int cap = 0;
int mcap = 800;
int hcap = 700;
int lcap = 500;
int general_delay = 100;

mutex m;
void work(int delay,int change){
    while(1)
    {
        m.lock();
        if((cap <= lcap && change < 0) || (cap >= hcap && change > 0))
        {
            m.unlock();
            this_thread::sleep_for(chrono::seconds(5));
        }
        else
        {
            if(cap + change >= 0 && cap + change <= mcap)
            {
                cap += change;
                cout << "thread " << this_thread::get_id() << " made: " << cap << endl;
            }
            m.unlock();
            this_thread::sleep_for(chrono::milliseconds(delay));
        }
    }
}

int main()
{
    thread t1(&work,general_delay,100),t2(&work,general_delay,80),t3(&work,general_delay,-110);

    char c='1';
    while(c!='0'){
        cin>>c;
        m.lock();
        cout<<"curr cap = "<<cap<<endl;
        m.unlock();
    }
    t1.join();
    t2.join();
    t3.join();
    return 0;
}