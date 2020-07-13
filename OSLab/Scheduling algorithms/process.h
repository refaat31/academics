//
// Created by refaa on 7/12/2020.
//

#ifndef PROCESS_H
#define PROCESS_H


class process
{
    int pid;
    int btime;
    int priority;
    int atime;
    int ttime;
    int wtime;
    int rutime; //running state for first time
    int restime;
    int etime;
    int isTakeninQueue;
    bool isTakeninQueueFCFS;
    int durationInCurrentQueue;
    bool isTakenOnceInMLFQ;
public:
    process();
    void set_pid(int x);
    int get_pid();
    void set_btime(int x);
    int get_btime();
    void set_priority(int x);
    int get_priority();
    void set_atime(int x);
    int get_atime();

    void set_wtime();
    int get_wtime();
    void set_ttime();
    int get_ttime();
    void set_etime(int x);
    int get_etime();
    void set_rutime(int x);
    int get_rutime();
    void set_restime();
    int get_restime();
    void set_isTakeninQueue(int x);
    int get_isTakeninQueue();
    void set_isTakeninQueueFCFS(bool x);
    bool get_isTakeninQueueFCFS();
    void set_durationInCurrentQueue(int x);
    int get_durationInCurrentQueue();
    void set_isTakenOnceMLFQ(bool x);
    bool get_isTakenOnceMLFQ();
};

#endif 

