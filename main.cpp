//
//  main.cpp
//  production_factory
//
//  Created by Ch Muhammad Wahab on 25/05/2021.
//  Copyright © 2021 Ch Muhammad Wahab. All rights reserved.
//

#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <mutex>
#include <unistd.h>
#include "HW7DynIntQueue.h"
using namespace std;
using namespace std::literals::chrono_literals;
auto givemetime = chrono::system_clock::to_time_t(chrono::system_clock::now());

HW7DynIntQueue fillobject;
HW7DynIntQueue packobject;

mutex m;

void put(int i,int l,int n){
    m.lock();
    fillobject.enqueue(i);
    cout<<"Producer has enqueued a new box "<<i<<" to filling queue (filling queue size is "<<fillobject.getCurrentSize()<<"):"<<ctime(&givemetime);
    m.unlock();
}
void filling(int i,int min, int max){
    m.lock();
    int k=i; fillobject.dequeue(i);
    cout<<"Filler "<< (rand()%2) + 1<<" started filling the box "<<k<<" (filling queue size "<<fillobject.getCurrentSize()<<"):"<<ctime(&givemetime);
    sleep(min);
    cout<<"Filler "<< (rand()%2) + 1<<" finished filling the box "<<k<<":"<<ctime(&givemetime);
    packobject.enqueue(k);
    cout<<"Filler "<< (rand()%2) + 1<<" put box 1 into packaging queue (packaging queue size is "<<packobject.getCurrentSize()<<":"<<ctime(&givemetime);
    m.unlock();
}
void packing(int i,int min,int max){
    m.lock();
    int k=i; packobject.dequeue(i);
    cout<<"Packager "<< (rand()%2) + 1<<" started packaging the box 1 (packaging queue size is " <<packobject.getCurrentSize()<<"):"<<ctime(&givemetime);
    sleep(min);
    cout<<"Packager "<< (rand()%2) + 1<<" finished packaging the box "<<k<<":"<<ctime(&givemetime);
    m.unlock();
}


int main(int argc, const char * argv[]) {

    int pr_min=1,pr_max=1,f_min=1,f_max=1,pk_min=1,pk_max=1;
    int items=2;
    
    cout<<"Please enter the total number of items:";
    cin>>items;
    cout<<"Please enter the min-max waiting time range of producer:";
    cout<<"Min:";cin>>pr_min;
    cout<<"Max:";cin>>pr_max;
    cout<<"Please enter the min-max waiting time range of filler workers:";
    cout<<"Min:";cin>>f_min;
    cout<<"Max:";cin>>f_max;
    cout<<"Please enter the min-max waiting time range of packager workers:";
    cout<<"Min:";cin>>pk_min;
    cout<<"Max:";cin>>pk_max;
    
    cout << "Simulation starts: "<<ctime(&givemetime);
    for(int i=1;i<=items;i++)
    {
        std::thread placing(put,i,pr_min,pk_max);
        thread fillings(filling,items,f_min,f_max);
        thread packk(packing,items,pk_min,pk_max);
        placing.join();
        fillings.join();
        packk.join();
    }
    cout <<"End of the simulation ends:"<< ctime(&givemetime) << endl;
}
