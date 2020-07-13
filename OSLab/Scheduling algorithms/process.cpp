
#include<iostream>
#include "process.h"
using namespace std;
process::process()
{

    priority=0;
    btime=0;
    atime=0;
    rutime=-1;
    isTakeninQueueFCFS=false;
    durationInCurrentQueue = 0;
    isTakenOnceInMLFQ = false;
}

void process::set_pid(int x)
{
    pid=x;
}
int process:: get_pid()
{
    return pid;
}
void process::set_btime(int x)
{
    btime=x;
}

int process::get_btime()
{
    return btime;
}
void process::set_priority(int x)
{
    priority=x;
}

int process::get_priority()
{
    return priority;
}
void process::set_atime(int x)
{
    atime=x;
}

int process::get_atime()
{
    return atime;
}

void process::set_ttime()
{
    ttime=etime-atime;
}

int process::get_ttime()
{
    return ttime;
}
void process::set_etime(int x)
{
    etime=x;
}

int process::get_etime()
{
    return etime;
}
void process::set_wtime()
{
    wtime=ttime-btime;
}

int process::get_wtime()
{
    return wtime;
}
void process::set_rutime(int x)
{
    rutime=x;
}

int process::get_rutime()
{
    return rutime;
}

void process::set_restime()
{
    restime=rutime-atime;
}

int process::get_restime()
{
    return restime;
}

void process::set_isTakeninQueue(int x)
{
    isTakeninQueue=x;
}

int process::get_isTakeninQueue()
{
    return isTakeninQueue;
}

void process::set_isTakeninQueueFCFS(bool x) {
    isTakeninQueueFCFS=x;
}

bool process::get_isTakeninQueueFCFS() {
    return isTakeninQueueFCFS;
}

void process::set_durationInCurrentQueue(int x){
    durationInCurrentQueue = x;
}

int process::get_durationInCurrentQueue(){
    return durationInCurrentQueue;
}

void process::set_isTakenOnceMLFQ(bool x){
    isTakenOnceInMLFQ = x;
}

bool process::get_isTakenOnceMLFQ(){
    return isTakenOnceInMLFQ;
}