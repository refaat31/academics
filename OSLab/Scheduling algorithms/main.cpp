#include <iostream>
#include <algorithm>
#include <queue>
#include<utility>
#include<iterator>
#include<cstdio>
#include<cstdlib>

#include "process.h"
using namespace std;

//PREEMPTIVE SJF
bool comparator(process a, process b);
//NON-PREEMPTIVE SJF
bool comparator2(process a, process b);
bool comparator3(process a, process b);
bool sortByProcessId(process a, process b);

int main()
{

    process p[6];
    process temp_p[6];

    p[1].set_pid(1);
    p[1].set_btime(13);
    p[1].set_priority(3);
    p[1].set_atime(2);

    p[2].set_pid(2);
    p[2].set_btime(1);
    p[2].set_priority(1);
    p[2].set_atime(0);

    p[3].set_pid(3);
    p[3].set_btime(2);
    p[3].set_priority(3);
    p[3].set_atime(1);

    p[4].set_pid(4);
    p[4].set_btime(16);
    p[4].set_priority(4);
    p[4].set_atime(3);

    p[5].set_pid(5);
    p[5].set_btime(7);
    p[5].set_priority(2);
    p[5].set_atime(5);

    for(int i=1;i<6;i++){
        temp_p[i].set_pid(p[i].get_pid());
        temp_p[i].set_btime(p[i].get_btime());
        temp_p[i].set_priority(p[i].get_priority());
        temp_p[i].set_atime(p[i].get_atime());
    }
//*
 //* Used for checking input
 //* delete before sumbmission
//    cout<<"P & TEMP_P\n\n\n";
//    for(int i=1;i<6;i++){
//        printf("%d %d %d %d\n",p[i].get_pid(),p[i].get_btime(),p[i].get_priority(),p[i].get_atime());
//        printf("%d %d %d %d\n\n",temp_p[i].get_pid(),temp_p[i].get_btime(),temp_p[i].get_priority(),temp_p[i].get_atime());
//
//    }
//
//
//
//    cout<<"ending...."<<endl;
//    return 0;
//
//*/
    int l,total_btime=0;
    for(l=1; l<6; l++)
        total_btime+=p[l].get_btime();
    //sort(p,p+6,sortByProcessId);

    //FCFS
    printf("**********FCFS**********\n\n");
    int t=0;
    int temp,i,temp2;
    deque <int> fcfs1;
    for(t=0;t<=total_btime;t++){
        for(i=1;i<=5;i++){
            if(p[i].get_atime()<=t && p[i].get_isTakeninQueueFCFS()==false){
                fcfs1.push_back(i);
                p[i].set_isTakeninQueueFCFS(true);
                printf("P%d     ",i);
            }


        }
//    used for checking the queue , delete before submission
//        for(auto k:fcfs1)
//            printf("%d ",k);
//        printf("\n\n");
        temp = fcfs1.front();

        if(p[temp].get_rutime()==-1){
            p[temp].set_rutime(t);
            
        }

        p[temp].set_btime(p[temp].get_btime()-1);
        if(p[temp].get_btime()==0){
            fcfs1.pop_front();
            p[temp].set_etime(t+1);
        }

    }
    
    printf("\n\n");
     int xx,yy,xx2;
      //Retrieving the original burst time
    for(i=1; i<=5; i++)
    {
        xx=temp_p[i].get_pid();
        for(int k=1; k<=5; k++)
        {

            yy=p[k].get_pid();
            if(xx==yy)
            {
                xx2=temp_p[i].get_btime();
                p[k].set_btime(xx2);
            }
        }
    }
    for(i=1; i<=5; i++)
    {
        p[i].set_ttime();

        p[i].set_wtime();
        p[i].set_restime();

    }
        //AVG WAITING TIME
    int wt_sum=0,rest_sum=0;
    for(i=1; i<=5; i++)
    {
        wt_sum+=p[i].get_wtime();
        rest_sum+=p[i].get_restime();

    }


    double avg_wt=((wt_sum)*1.0)/5;
    double avg_rest=((rest_sum)*1.0)/5;

    cout<<endl;
    cout<<endl;
    cout<<"Avg Response Time    -   "<<avg_rest<<endl;
    cout<<"Avg Waiting Time     -   "<<avg_wt<<endl;

    //sort the "p" object of class process
    //according to their process id

    sort(p+1,p+6,sortByProcessId);
    cout<<endl;
    for(i=1; i<=5; i++)
    {
        cout<<endl;
        cout<<"P"<<p[i].get_pid()<<":"<<endl;
        cout<<"Start Time       :   "<<p[i].get_rutime()<<endl;
        cout<<"Finish Time      :   "<<p[i].get_etime()<<endl;
        cout<<"Response Time    :   "<<p[i].get_restime()<<endl;
        cout<<"Waiting Time     :   "<<p[i].get_wtime()<<endl;
    }
    cout<<endl;
    cout<<endl;
//return 0;
// //retrieving the original values of processes
//     for(int rec=1;rec<=5;rec++){
//         p[rec].set_pid(temp_p[rec].get_pid());
//         p[rec].set_btime(temp_p[rec].get_btime());
//         p[rec].set_priority(temp_p[rec].get_priority());
//         p[rec].set_atime(temp_p[rec].get_atime());
//         p[rec].set_rutime(-1);
//     }



   

    // for(l=1; l<6; l++)
    //     total_btime+=p[l].get_btime();
    sort(p,p+6,comparator);

    //PREEMPTIVE SJF
    t=0;
    int cur_pid,prev_cur_pid=-1;//****
    cout<<"**********Preemptive SJF**********"<<endl<<endl;
    for(t=0; t<=total_btime; t++)
    {
        for(i=1; i<=5; i++)
        {
            temp2=p[i].get_atime();
            if(temp2<=t)
            {

                cur_pid=p[i].get_pid();

                temp=p[i].get_btime();

                if(temp==0)
                    continue;

                temp--;
                if(prev_cur_pid==-1)
                    cout<<"P"<<cur_pid<<"    ";

                else if(prev_cur_pid!=cur_pid)
                    cout<<"P"<<cur_pid<<"    ";


                prev_cur_pid=cur_pid;

                if(temp==0)
                    p[i].set_etime(t+1);
                p[i].set_btime(temp);
                if(p[i].get_rutime() == -1)
                    p[i].set_rutime(t);

                sort(p,p+6,comparator);
                break;
            }
        }
    }


    //Retrieving the original burst time
    for(i=1; i<=5; i++)
    {
        xx=temp_p[i].get_pid();
        for(int k=1; k<=5; k++)
        {

            yy=p[k].get_pid();
            if(xx==yy)
            {
                xx2=temp_p[i].get_btime();
                p[k].set_btime(xx2);
            }
        }
    }
    for(i=1; i<=5; i++)
    {
        p[i].set_ttime();

        p[i].set_wtime();
        p[i].set_restime();

    }
//AVG WAITING TIME
    wt_sum=0,rest_sum=0;
    for(i=1; i<=5; i++)
    {
        wt_sum+=p[i].get_wtime();
        rest_sum+=p[i].get_restime();

    }


    avg_wt=((wt_sum)*1.0)/5;
    avg_rest=((rest_sum)*1.0)/5;

    cout<<endl;
    cout<<endl;
    cout<<"Avg Response Time    -   "<<avg_rest<<endl;
    cout<<"Avg Waiting Time     -   "<<avg_wt<<endl;

    //sort the "p" object of class process
    //according to their process id

    sort(p+1,p+6,sortByProcessId);
    cout<<endl;
    for(i=1; i<=5; i++)
    {
        cout<<endl;
        cout<<"P"<<p[i].get_pid()<<":"<<endl;
        cout<<"Start Time       :   "<<p[i].get_rutime()<<endl;
        cout<<"Finish Time      :   "<<p[i].get_etime()<<endl;
        cout<<"Response Time    :   "<<p[i].get_restime()<<endl;
        cout<<"Waiting Time     :   "<<p[i].get_wtime()<<endl;
    }
    cout<<endl;
    cout<<endl;

//NON-PREEMPTIVE SJF
    cout<<"**********Non Preemptive SJF**********"<<endl<<endl;
    t=0;
    for(i=1; i<=5; i++)
        p[i].set_rutime(-1);

    prev_cur_pid=-1;
    for(t=0; t<total_btime;)
    {

        for(i=1; i<=5; i++)
        {
            temp2=p[i].get_atime();

            if(temp2<=t)
            {

                cur_pid=p[i].get_pid();

                temp=p[i].get_btime();

                if(temp==0)
                    continue;

                int temp3=0;
                if(prev_cur_pid==-1)
                    cout<<"P"<<cur_pid<<"    ";

                else if(prev_cur_pid!=cur_pid)
                    cout<<"P"<<cur_pid<<"    ";


                prev_cur_pid=cur_pid;

                while(temp!=0)
                {
                    temp--;
                    temp3++;
                }


                p[i].set_etime(t+temp3);
                p[i].set_btime(temp);
                if(p[i].get_rutime() == -1)
                    p[i].set_rutime(t);


                sort(p,p+6,comparator);
                t+=temp3;
                break;
            }



        }


    }


    for(i=1; i<=5; i++)
    {
        xx=temp_p[i].get_pid();
        for(int k=1; k<=5; k++)
        {

            yy=p[k].get_pid();
            if(xx==yy)
            {
                xx2=temp_p[i].get_btime();
                p[k].set_btime(xx2);
            }
        }
    }
    cout<<endl;
    for(i=1; i<=5; i++)
    {
        p[i].set_ttime();

        p[i].set_wtime();
        p[i].set_restime();

    }
//AVG WAITING TIME
    wt_sum=0,rest_sum=0;
    for(i=1; i<=5; i++)
    {
        wt_sum+=p[i].get_wtime();
        rest_sum+=p[i].get_restime();

    }

    avg_wt=((wt_sum)*1.0)/5;
    avg_rest=((rest_sum)*1.0)/5;
    cout<<endl; //****

    cout<<"Avg Response Time    -   "<<avg_rest<<endl;
    cout<<"Avg Waiting Time     -   "<<avg_wt<<endl;

    //sort the "p" object of class process
    //according to their process id

    sort(p+1,p+6,sortByProcessId);
    cout<<endl;
    for(i=1; i<=5; i++)
    {
        cout<<endl;
        cout<<"P"<<p[i].get_pid()<<":"<<endl;
        cout<<"Start Time       :   "<<p[i].get_rutime()<<endl;
        cout<<"Finish Time      :   "<<p[i].get_etime()<<endl;
        cout<<"Response Time    :   "<<p[i].get_restime()<<endl;
        cout<<"Waiting Time     :   "<<p[i].get_wtime()<<endl;
    }
    cout<<endl;




    cout<<endl;



    //preemptive priority scheduling
    cout<<"**********Preemptive Priority Scheduling**********"<<endl<<endl;
    sort(p,p+6,comparator2);
    for(i=1; i<=5; i++)
        p[i].set_rutime(-1);
    prev_cur_pid=-1;

    t=0;

    for(t=0; t<=total_btime; t++)
    {
        for(i=1; i<=5; i++)
        {
            temp2=p[i].get_atime();
            if(temp2<=t)
            {

                cur_pid=p[i].get_pid();
                //cout<<cur_pid<<endl;
                temp=p[i].get_btime();

                if(temp==0)
                    continue;
                //cout<<cur_pid<<"        "<<temp<<endl;
                temp--;
                if(prev_cur_pid==-1)            //****
                    cout<<"P"<<cur_pid<<"    ";

                else if(prev_cur_pid!=cur_pid)
                    cout<<"P"<<cur_pid<<"    ";


                prev_cur_pid=cur_pid;

                if(temp==0)
                    p[i].set_etime(t+1);
                p[i].set_btime(temp);
                if(p[i].get_rutime() == -1)
                    p[i].set_rutime(t);

                sort(p,p+6,comparator2);
                break;
            }
        }
    }


    for(i=1; i<=5; i++)
    {
        xx=temp_p[i].get_pid();
        for(int k=1; k<=5; k++)
        {

            yy=p[k].get_pid();
            if(xx==yy)
            {
                xx2=temp_p[i].get_btime();
                p[k].set_btime(xx2);
            }
        }
    }
    for(i=1; i<=5; i++)
    {
        p[i].set_ttime();

        p[i].set_wtime();
        p[i].set_restime();

    }
//AVG WAITING TIME
    wt_sum=0,rest_sum=0;
    for(i=1; i<=5; i++)
    {
        wt_sum+=p[i].get_wtime();
        rest_sum+=p[i].get_restime();
        // cout<<wt_sum<<endl;
    }

    avg_wt=((wt_sum)*1.0)/5;
    avg_rest=((rest_sum)*1.0)/5;
    cout<<endl;
    cout<<endl;
    cout<<"Avg Response Time    -   "<<avg_rest<<endl;
    cout<<"Avg Waiting Time     -   "<<avg_wt<<endl;

    //sort the "p" object of class process
    //according to their process id

    sort(p+1,p+6,sortByProcessId);
    cout<<endl;
    for(i=1; i<=5; i++)
    {
        cout<<endl;
        cout<<"P"<<p[i].get_pid()<<":"<<endl;
        cout<<"Start Time       :   "<<p[i].get_rutime()<<endl;
        cout<<"Finish Time      :   "<<p[i].get_etime()<<endl;
        cout<<"Response Time    :   "<<p[i].get_restime()<<endl;
        cout<<"Waiting Time     :   "<<p[i].get_wtime()<<endl;
    }
    cout<<endl;
    cout<<endl;


    //Non preemptive priority scheduling
    cout<<"**********Non preemptive Priority scheduling**********"<<endl<<endl;
    t=0;
    for(i=1; i<=5; i++)
        p[i].set_rutime(-1);

    prev_cur_pid=-1;
    for(t=0; t<total_btime;)
    {

        for(i=1; i<=5; i++)
        {
            temp2=p[i].get_atime();

            if(temp2<=t)
            {

                cur_pid=p[i].get_pid();

                temp=p[i].get_btime();

                if(temp==0)
                    continue;

                if(prev_cur_pid==-1)
                    cout<<"P"<<cur_pid<<"    ";

                else if(prev_cur_pid!=cur_pid)
                    cout<<"P"<<cur_pid<<"    ";


                prev_cur_pid=cur_pid;

                int temp3=0;
                while(temp!=0)
                {
                    temp--;
                    temp3++;
                }


                p[i].set_etime(t+temp3);
                p[i].set_btime(temp);
                if(p[i].get_rutime() == -1)
                    p[i].set_rutime(t);


                sort(p,p+6,comparator2);
                t+=temp3;
                break;
            }



        }


    }


    for(i=1; i<=5; i++)
    {
        xx=temp_p[i].get_pid();
        for(int k=1; k<=5; k++)
        {

            yy=p[k].get_pid();
            if(xx==yy)
            {
                xx2=temp_p[i].get_btime();
                p[k].set_btime(xx2);
            }
        }
    }
    cout<<endl;
    for(i=1; i<=5; i++)
    {
        p[i].set_ttime();

        p[i].set_wtime();
        p[i].set_restime();

    }
//AVG WAITING TIME
    wt_sum=0,rest_sum=0;
    for(i=1; i<=5; i++)
    {
        wt_sum+=p[i].get_wtime();
        rest_sum+=p[i].get_restime();

    }

    avg_wt=((wt_sum)*1.0)/5;
    avg_rest=((rest_sum)*1.0)/5;
    cout<<endl;

    cout<<"Avg Response Time    -   "<<avg_rest<<endl;
    cout<<"Avg Waiting Time     -   "<<avg_wt<<endl;

    //sort the "p" object of class process
    //according to their process id

    sort(p+1,p+6,sortByProcessId);
    cout<<endl;
    for(i=1; i<=5; i++)
    {
        cout<<endl;
        cout<<"P"<<p[i].get_pid()<<":"<<endl;
        cout<<"Start Time       :   "<<p[i].get_rutime()<<endl;
        cout<<"Finish Time      :   "<<p[i].get_etime()<<endl;
        cout<<"Response Time    :   "<<p[i].get_restime()<<endl;
        cout<<"Waiting Time     :   "<<p[i].get_wtime()<<endl;
    }
    cout<<endl;
    cout<<endl;


    //round robin
    cout<<"**********Round Robin**********"<<endl<<endl;
    sort(p,p+6,comparator3); //sort according to arrival time

    queue <int> process_queue;

    for(i=1; i<=5; i++)
    {
        p[i].set_rutime(-1);
        p[i].set_isTakeninQueue(0);
    }









    int cur_btime,zz,quantum=1;
    prev_cur_pid=-1;
    for(t=0; t<=total_btime; t++)
    {
        //this loop is for determining if there are any new arrivals of processes. if there are, they are included in the queue
        for(i=1; i<=5; i++)
        {
            temp2=p[i].get_atime();
            if(temp2<=t && p[i].get_isTakeninQueue()==0)
            {

                process_queue.push(p[i].get_pid());
                p[i].set_isTakeninQueue(1);
            }

        }
        int temp4;


        if(t==0)
            cur_pid=process_queue.front();
        else
            cur_pid = p[cur_pid].get_pid();

        if(prev_cur_pid==-1)
            cout<<"P"<<cur_pid<<"    ";

        else if(prev_cur_pid!=cur_pid)
            cout<<"P"<<cur_pid<<"    ";


        prev_cur_pid=cur_pid;



        for(i=1; i<=5; i++)
        {
            zz=p[i].get_pid();
            if(zz==cur_pid)
            {
                cur_pid=i;
                break;
            }

        }



        cur_btime=p[cur_pid].get_btime();

        if(cur_btime==0)
        {
            process_queue.pop();
            p[cur_pid].set_btime(0);
            quantum=1;
            p[cur_pid].set_etime(t);

            cur_pid=process_queue.front();

            for(i=1; i<=5; i++)
            {
                zz=p[i].get_pid();
                if(zz==cur_pid)
                {
                    cur_pid=i;
                    break;
                }

            }
            cur_btime=p[cur_pid].get_btime();


        }

        if(quantum>4)
        {
            temp4=process_queue.front();
            process_queue.push(temp4);
            process_queue.pop();
            cur_pid=process_queue.front();
            quantum=1;

            for(i=1; i<=5; i++)
            {
                zz=p[i].get_pid();
                if(zz==cur_pid)
                {
                    cur_pid=i;
                    break;
                }

            }
            cur_btime=p[cur_pid].get_btime();

        }


        if(p[cur_pid].get_rutime() == -1)
            p[cur_pid].set_rutime(t);



        cur_btime--;
        p[cur_pid].set_btime(cur_btime);
        quantum++;




    }






    for(i=1; i<=5; i++)
    {
        xx=temp_p[i].get_pid();
        for(int k=1; k<=5; k++)
        {

            yy=p[k].get_pid();
            if(xx==yy)
            {
                xx2=temp_p[i].get_btime();
                p[k].set_btime(xx2);
            }
        }
    }
    for(i=1; i<=5; i++)
    {
        p[i].set_ttime();

        p[i].set_wtime();
        p[i].set_restime();

    }
//AVG WAITING TIME
    wt_sum=0,rest_sum=0;
    for(i=1; i<=5; i++)
    {
        wt_sum+=p[i].get_wtime();
        rest_sum+=p[i].get_restime();

    }

    avg_wt=((wt_sum)*1.0)/5;
    avg_rest=((rest_sum)*1.0)/5;
    cout<<endl;
    cout<<endl;
    cout<<"Avg Response Time    -   "<<avg_rest<<endl;
    cout<<"Avg Waiting Time     -   "<<avg_wt<<endl;

    //sort the "p" object of class process
    //according to their process id

    sort(p+1,p+6,sortByProcessId);
    cout<<endl;
    for(i=1; i<=5; i++)
    {
        cout<<endl;
        cout<<"P"<<p[i].get_pid()<<":"<<endl;
        cout<<"Start Time       :   "<<p[i].get_rutime()<<endl;
        cout<<"Finish Time      :   "<<p[i].get_etime()<<endl;
        cout<<"Response Time    :   "<<p[i].get_restime()<<endl;
        cout<<"Waiting Time     :   "<<p[i].get_wtime()<<endl;
    }
    cout<<endl;
    cout<<endl;
    cout<<"\n";


    for(i=1; i<=5; i++)
        p[i].set_rutime(-1);
    //MLFQ Scheduling
    printf("**********MLFQ Scheduling**********\n\n");
    deque <int> q4,q8,q_fcfs;
    //Three queues
    //One with quantum = 4, another with quantum = 8
    //and lastly fcfs
    
    // for testing 
    //printf("%d",total_btime);
    // return 0;
    prev_cur_pid=0;
    for(t=0;t<=total_btime;t++){
        for(i=1;i<=5;i++){
            if(p[i].get_atime()<=t  && p[i].get_isTakenOnceMLFQ()==false){
                q4.push_back(i);
                p[i].set_isTakenOnceMLFQ(true);
            }
                
        }
        //remove thiws
        // printf("At time %d , Queue 4 : ",t);
        // for(auto tempv_new:q4){
        //     cout<<tempv_new <<" ";

        // }

        //printf("\n");
            
        if(!q4.empty()){

//            if(!q4.empty()){
                cur_pid = q4.front();
                if(cur_pid!=prev_cur_pid){
                    printf("P%d     ",cur_pid);
                    prev_cur_pid=q4.front();
                }

                p[cur_pid].set_btime (p[cur_pid].get_btime()-1);
                p[cur_pid].set_durationInCurrentQueue(p[cur_pid].get_durationInCurrentQueue()+1);
                if(p[cur_pid].get_rutime()==-1)
                    p[cur_pid].set_rutime(t);
                if(p[cur_pid].get_btime()==0){
                    p[cur_pid].set_etime(t+1);
                    q4.pop_front();
                }
         
 //           }
             if(p[q4.front()].get_durationInCurrentQueue()==4){
                p[q4.front()].set_durationInCurrentQueue(0);
                q8.push_back(q4.front());
                q4.pop_front();
            }
       

                
            
        }
        else if(!q8.empty()){


 //           if(!q8.empty()){
                cur_pid = q8.front();
                if(cur_pid!=prev_cur_pid){
                    printf("P%d     ",cur_pid);
                    prev_cur_pid = q8.front();
                }
                
                p[cur_pid].set_btime(p[cur_pid].get_btime()-1);
                p[cur_pid].set_durationInCurrentQueue(p[cur_pid].get_durationInCurrentQueue()+1);
                if(p[cur_pid].get_rutime()==-1)
                    p[cur_pid].set_rutime(t);
                if(p[cur_pid].get_btime()==0){
                    p[cur_pid].set_etime(t+1);
                    q8.pop_front();
                }
 //           }
             if(p[q8.front()].get_durationInCurrentQueue()==8){
                p[q8.front()].set_durationInCurrentQueue(0);
                q_fcfs.push_back(q8.front());
                q8.pop_front();
            }
        }
        else if(!q_fcfs.empty()){
            cur_pid = q_fcfs.front();
            if(cur_pid!=prev_cur_pid){
                printf("P%d     ",cur_pid);
                prev_cur_pid = q_fcfs.front();
            }
            p[cur_pid].set_btime(p[cur_pid].get_btime()-1);
            p[cur_pid].set_durationInCurrentQueue(p[cur_pid].get_durationInCurrentQueue()+1);
            if(p[cur_pid].get_rutime()==-1)
                p[cur_pid].set_rutime(t);
            if(p[cur_pid].get_btime()==0){
                p[cur_pid].set_etime(t+1);
                q_fcfs.pop_front();
            }
        }
    }

     for(i=1; i<=5; i++)
    {
        xx=temp_p[i].get_pid();
        for(int k=1; k<=5; k++)
        {

            yy=p[k].get_pid();
            if(xx==yy)
            {
                xx2=temp_p[i].get_btime();
                p[k].set_btime(xx2);
            }
        }
    }
    for(i=1; i<=5; i++)
    {
        p[i].set_ttime();

        p[i].set_wtime();
        p[i].set_restime();

    }
//AVG WAITING TIME
    wt_sum=0,rest_sum=0;
    for(i=1; i<=5; i++)
    {
        wt_sum+=p[i].get_wtime();
        rest_sum+=p[i].get_restime();

    }

    avg_wt=((wt_sum)*1.0)/5;
    avg_rest=((rest_sum)*1.0)/5;
    cout<<endl;
    cout<<endl;
    cout<<"Avg Response Time    -   "<<avg_rest<<endl;
    cout<<"Avg Waiting Time     -   "<<avg_wt<<endl;

    //sort the "p" object of class process
    //according to their process id

    sort(p+1,p+6,sortByProcessId);
    cout<<endl;
    for(i=1; i<=5; i++)
    {
        cout<<endl;
        cout<<"P"<<p[i].get_pid()<<":"<<endl;
        cout<<"Start Time       :   "<<p[i].get_rutime()<<endl;
        cout<<"Finish Time      :   "<<p[i].get_etime()<<endl;
        cout<<"Response Time    :   "<<p[i].get_restime()<<endl;
        cout<<"Waiting Time     :   "<<p[i].get_wtime()<<endl;
    }
    cout<<endl;
    cout<<endl;
    cout<<"\n";



}


bool comparator(process a, process b)
{
    return (a.get_btime()<b.get_btime());
}

bool comparator2(process a, process b)
{
    return (a.get_priority()<b.get_priority());
}

bool comparator3(process a, process b)
{
    return (a.get_atime()<b.get_atime());
}

bool sortByProcessId(process a, process b)
{
    return (a.get_pid()<b.get_pid());
}

