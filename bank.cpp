#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int cap = 10000;
int inc = 1000;
int s1 = 5000, s2 = 3000,s3 = 4000;
mutex m;

void work(int sum)
{
    bool b = true;
    while(b)
    {
        m.lock();
        if(cap - sum >= 0)
        {
            cap -= sum;
            b = false;
            cout<<"thread "<<this_thread::get_id()<<" is credited and cap is "<<cap<<endl;
        }
        m.unlock();
    }
    this_thread::sleep_for(chrono::seconds(1));//1 month
    while(sum>0){
        m.lock();
        sum -= inc;
        cap += inc;
        cout<<"cap is "<<cap<<endl;
        m.unlock();
        this_thread::sleep_for(chrono::seconds(1));//1 month
    }
}

int main(){
    thread t1(&work,s1),t2(&work,s2),t3(&work,s3);
    char c='1';
    while(c!='0')
    {
        m.lock();
        cin>>c;
        cap += 3 * inc;
        cout<<"cap = "<<cap<<endl;
        m.unlock();
        this_thread::sleep_for(chrono::seconds(1));
    }
    t1.join();
    t2.join();
    t3.join();
}