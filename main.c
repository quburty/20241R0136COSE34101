#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PROC_NUM 5
#define JOB_MAX_NUM 20
#define MAX_TIME 99

#define QUANTUM 2

typedef struct _Process {
    int pid;
    int cpu_burst_time;
    int io_burst_time;
    int arrival_time;
    int priority;
} Process;

typedef struct _Scheduling {
    int* start_time;
    int* end_time;
    int* p_idx;
    int p_ptr_len;

    int order_len;

    double avg_waiting_time;
    double avg_turnaround_time;
} Scheduling;

void Create_Process(Process** p_arr) {
    srand((unsigned)time(NULL));

    char method = 'n';
    printf("Randomly create process, ok? [y/n]: ");
    scanf("%c", &method);

    for (int i = 0; i < PROC_NUM; i++) {
        Process* p = (Process*)malloc(sizeof(Process));

        if (method == 'y' || method == 'Y')
        {
            p->pid = rand() % 1000 + 1;
            p->arrival_time = rand() % 10 + 1;
            p->cpu_burst_time = rand() % 5 + 1;
            p->priority = rand() % 5 + 1;
        }
        else
        {
            printf("write pid, arrival time, burst time, priority: ");
            scanf("%d %d %d %d", &p->pid, &p->arrival_time, &p->cpu_burst_time, &p->priority);
        }

        p_arr[i] = p;

        printf("Process Created! \npid: %d\narrival: %d\nburst: %d\npriority: %d\n\n", p->pid, p->arrival_time, p->cpu_burst_time, p->priority);
    }
}

void schedule_fcfs(Process** p_data, Scheduling* scheduling) {
    Process* p_arr[PROC_NUM];
    for (int i = 0; i < PROC_NUM; i++) { p_arr[i] = (Process*)malloc(sizeof(Process)); (*p_arr[i]) = (*p_data[i]); }

    scheduling->order_len = 0;
    scheduling->start_time = (int*)malloc(sizeof(int) * PROC_NUM);
    scheduling->end_time = (int*)malloc(sizeof(int) * PROC_NUM);
    scheduling->p_idx = (int*)malloc(sizeof(int) * PROC_NUM);

    int done[PROC_NUM] = { 0, };

    int available[PROC_NUM] = { -1, };
    int available_len = 0;

    int time = 0;
    int count = PROC_NUM;
    int current_left = 0;
    int current_idx = -1;
    while (count != 0)
    {
        if (current_left > 0) {
            current_left--;
            if (current_left != 0) {
                time++;
                continue;
            }

            scheduling->end_time[scheduling->order_len - 1] = time;
            done[current_idx] = 1;
            count--;
        }

        available_len = 0;
        for (int i = 0; i < PROC_NUM; i++) {
            if (done[i] == 0 && p_arr[i]->arrival_time <= time) {
                available[available_len] = i;
                available_len++;
            }
        }

        if (available_len != 0) {
            int min = 99;
            int idx = -1;
            for (int i = 0; i < available_len; i++) {
                if (p_arr[available[i]]->arrival_time < min)
                {
                    min = p_arr[available[i]]->arrival_time;
                    idx = available[i];
                }
            }

            current_idx = idx;
            current_left = p_arr[idx]->cpu_burst_time;

            scheduling->start_time[scheduling->order_len] = time;
            scheduling->p_idx[scheduling->order_len] = idx;
            scheduling->order_len++;
        }


        time++;
    }
}

void schedule_priority(Process** p_data, Scheduling* scheduling) {
    Process* p_arr[PROC_NUM];
    for (int i = 0; i < PROC_NUM; i++) { p_arr[i] = (Process*)malloc(sizeof(Process)); (*p_arr[i]) = (*p_data[i]); }

    scheduling->order_len = 0;
    scheduling->start_time = (int*)malloc(sizeof(int) * PROC_NUM);
    scheduling->end_time = (int*)malloc(sizeof(int) * PROC_NUM);
    scheduling->p_idx = (int*)malloc(sizeof(int) * PROC_NUM);

    int done[PROC_NUM] = { 0, };

    int available[PROC_NUM] = { -1, };
    int available_len = 0;

    int time = 0;
    int count = PROC_NUM;
    int current_left = 0;
    int current_idx = -1;
    while (count != 0)
    {
        if (current_left > 0) {
            current_left--;
            if (current_left != 0) {
                time++;
                continue;
            }

            scheduling->end_time[scheduling->order_len - 1] = time;
            done[current_idx] = 1;
            count--;
        }

        available_len = 0;
        for (int i = 0; i < PROC_NUM; i++) {
            if (done[i] == 0 && p_arr[i]->arrival_time <= time) {
                available[available_len] = i;
                available_len++;
            }
        }

        if (available_len != 0) {
            int min = 99;
            int idx = -1;
            for (int i = 0; i < available_len; i++) {
                if (p_arr[available[i]]->priority < min)
                {
                    min = p_arr[available[i]]->priority;
                    idx = available[i];
                }
            }

            current_idx = idx;
            current_left = p_arr[idx]->cpu_burst_time;

            scheduling->start_time[scheduling->order_len] = time;
            scheduling->p_idx[scheduling->order_len] = idx;
            scheduling->order_len++;
        }


        time++;
    }
}

void schedule_sjf(Process** p_data, Scheduling* scheduling) {
    Process* p_arr[PROC_NUM];
    for (int i = 0; i < PROC_NUM; i++) { p_arr[i] = (Process*)malloc(sizeof(Process)); (*p_arr[i]) = (*p_data[i]); }

    scheduling->order_len = 0;
    scheduling->start_time = (int*)malloc(sizeof(int) * PROC_NUM);
    scheduling->end_time = (int*)malloc(sizeof(int) * PROC_NUM);
    scheduling->p_idx = (int*)malloc(sizeof(int) * PROC_NUM);

    int done[PROC_NUM] = { 0, };

    int available[PROC_NUM] = { -1, };
    int available_len = 0;

    int time = 0;
    int count = PROC_NUM;
    int current_left = 0;
    int current_idx = -1;
    while (count != 0)
    {
        if (current_left > 0) {
            current_left--;
            if (current_left != 0) {
                time++;
                continue;
            }

            scheduling->end_time[scheduling->order_len - 1] = time;
            done[current_idx] = 1;
            count--;
        }

        available_len = 0;
        for (int i = 0; i < PROC_NUM; i++) {
            if (done[i] == 0 && p_arr[i]->arrival_time <= time) {
                available[available_len] = i;
                available_len++;
            }
        }

        if (available_len != 0) {
            int min = 99;
            int idx = -1;
            for (int i = 0; i < available_len; i++) {
                if (p_arr[available[i]]->cpu_burst_time < min)
                {
                    min = p_arr[available[i]]->cpu_burst_time;
                    idx = available[i];
                }
            }

            current_idx = idx;
            current_left = p_arr[idx]->cpu_burst_time;

            scheduling->start_time[scheduling->order_len] = time;
            scheduling->p_idx[scheduling->order_len] = idx;
            scheduling->order_len++;
        }


        time++;
    }
}

void schedule_rr(Process** p_data, Scheduling* scheduling) {
    Process* p_arr[PROC_NUM];
    for (int i = 0; i < PROC_NUM; i++) { p_arr[i] = (Process*)malloc(sizeof(Process)); (*p_arr[i]) = (*p_data[i]); }

    scheduling->order_len = 0;
    scheduling->start_time = (int*)malloc(sizeof(int) * JOB_MAX_NUM); for (int i = 0; i < JOB_MAX_NUM; i++) { scheduling->start_time[i] = -1; }
    scheduling->end_time = (int*)malloc(sizeof(int) * JOB_MAX_NUM); for (int i = 0; i < JOB_MAX_NUM; i++) { scheduling->end_time[i] = -1; }
    scheduling->p_idx = (int*)malloc(sizeof(int) * JOB_MAX_NUM); for (int i = 0; i < JOB_MAX_NUM; i++) { scheduling->p_idx[i] = -1; }

    int done[PROC_NUM] = { 0, };

    int available[PROC_NUM] = { -1, };
    int available_len = 0;

    int time = 0;
    int count = PROC_NUM;
    int current_left = 0;
    int current_idx = -1;
    int current_quantum = 0;
    int prev_idx = -1;
    while (count != 0)
    {
        if (current_left > 0) {
            current_left--;
            current_quantum--;

            if (current_left != 0 && current_quantum != 0) {
                time++;
                continue;
            }

            if (current_left != 0)
            {
                prev_idx = current_idx;
                scheduling->end_time[scheduling->order_len - 1] = time;
                p_arr[prev_idx]->cpu_burst_time -= QUANTUM;
            }
            else
            {
                prev_idx = -1;
                scheduling->end_time[scheduling->order_len - 1] = time;
                done[current_idx] = 1;
                count--;
            }
        }

        available_len = 0;
        for (int i = 0; i < PROC_NUM; i++) {
            if (done[i] == 0 && p_arr[i]->arrival_time <= time) {
                available[available_len] = i;
                available_len++;
            }
        }

        if (available_len != 0) {

            int min = 99;
            int idx = -1;
            for (int i = 0; i < available_len; i++) {
                if (p_arr[available[i]]->arrival_time < min && (available_len == 1 || available[i] != prev_idx))
                {
                    min = p_arr[available[i]]->arrival_time;
                    idx = available[i];
                }
            }

            current_idx = idx;
            current_left = p_arr[idx]->cpu_burst_time;
            current_quantum = QUANTUM;

            scheduling->start_time[scheduling->order_len] = time;
            scheduling->p_idx[scheduling->order_len] = idx;
            scheduling->order_len++;
        }

        time++;
    }
}

void schedule_sjf_preemptive(Process** p_data, Scheduling* scheduling) {
    Process* p_arr[PROC_NUM];
    for (int i = 0; i < PROC_NUM; i++) { p_arr[i] = (Process*)malloc(sizeof(Process)); (*p_arr[i]) = (*p_data[i]); }

    scheduling->order_len = 0;
    scheduling->start_time = (int*)malloc(sizeof(int) * JOB_MAX_NUM); for (int i = 0; i < JOB_MAX_NUM; i++) { scheduling->start_time[i] = -1; }
    scheduling->end_time = (int*)malloc(sizeof(int) * JOB_MAX_NUM); for (int i = 0; i < JOB_MAX_NUM; i++) { scheduling->end_time[i] = -1; }
    scheduling->p_idx = (int*)malloc(sizeof(int) * JOB_MAX_NUM); for (int i = 0; i < JOB_MAX_NUM; i++) { scheduling->p_idx[i] = -1; }

    int done[PROC_NUM] = { 0, };

    int time = 0;
    int count = PROC_NUM;
    int current_left = -1;
    int current_idx = -1;

    while (count != 0)
    {
        int min = 99;
        int idx = -1;
        for (int i = 0; i < PROC_NUM; i++) {
            if (done[i] == 0 && p_arr[i]->arrival_time <= time && current_idx != i && p_arr[i]->cpu_burst_time < min) {
                min = p_arr[i]->cpu_burst_time;
                idx = i;
            }
        }
        if (idx != -1 && current_idx != -1 && current_left > p_arr[idx]->cpu_burst_time)
        {
            p_arr[current_idx]->cpu_burst_time = current_left;
            scheduling->end_time[scheduling->order_len - 1] = time;
            current_idx = idx;
            current_left = p_arr[idx]->cpu_burst_time;
            scheduling->start_time[scheduling->order_len] = time;
            scheduling->p_idx[scheduling->order_len] = idx;
            scheduling->order_len++;
        }
        else {
            if (current_left == 0) {
                done[current_idx] = 1;
                scheduling->end_time[scheduling->order_len - 1] = time;
                current_left = -1;
                current_idx = -1;
                count--;
                if (count == 0) break;
            }

            if (idx != -1 && current_idx == -1) {
                current_idx = idx;
                current_left = p_arr[idx]->cpu_burst_time;
                scheduling->start_time[scheduling->order_len] = time;
                scheduling->p_idx[scheduling->order_len] = idx;
                scheduling->order_len++;
            }
        }

        if (current_left > 0) current_left--;
        time++;
    }
}

void schedule_priority_preemptive(Process** p_data, Scheduling* scheduling) {
    Process* p_arr[PROC_NUM];
    for (int i = 0; i < PROC_NUM; i++) { p_arr[i] = (Process*)malloc(sizeof(Process)); (*p_arr[i]) = (*p_data[i]); }

    scheduling->order_len = 0;
    scheduling->start_time = (int*)malloc(sizeof(int) * JOB_MAX_NUM); for (int i = 0; i < JOB_MAX_NUM; i++) { scheduling->start_time[i] = -1; }
    scheduling->end_time = (int*)malloc(sizeof(int) * JOB_MAX_NUM); for (int i = 0; i < JOB_MAX_NUM; i++) { scheduling->end_time[i] = -1; }
    scheduling->p_idx = (int*)malloc(sizeof(int) * JOB_MAX_NUM); for (int i = 0; i < JOB_MAX_NUM; i++) { scheduling->p_idx[i] = -1; }

    int done[PROC_NUM] = { 0, };

    int time = 0;
    int count = PROC_NUM;
    int current_left = -1;
    int current_idx = -1;

    while (count != 0)
    {
        int min = 99;
        int idx = -1;
        for (int i = 0; i < PROC_NUM; i++) {
            if (done[i] == 0 && p_arr[i]->arrival_time <= time && current_idx != i && p_arr[i]->priority < min) {
                min = p_arr[i]->priority;
                idx = i;
            }
        }
        if (idx != -1 && current_idx != -1 && p_arr[current_idx]->priority > p_arr[idx]->priority && current_left > 0)
        {
            p_arr[current_idx]->cpu_burst_time = current_left;
            scheduling->end_time[scheduling->order_len - 1] = time;
            current_idx = idx;
            current_left = p_arr[idx]->cpu_burst_time;
            scheduling->start_time[scheduling->order_len] = time;
            scheduling->p_idx[scheduling->order_len] = idx;
            scheduling->order_len++;
        }
        else {
            if (current_left == 0) {
                done[current_idx] = 1;
                scheduling->end_time[scheduling->order_len - 1] = time;
                current_left = -1;
                current_idx = -1;
                count--;
                if (count == 0) break;
            }

            if (idx != -1 && current_idx == -1) {
                current_idx = idx;
                current_left = p_arr[idx]->cpu_burst_time;
                scheduling->start_time[scheduling->order_len] = time;
                scheduling->p_idx[scheduling->order_len] = idx;
                scheduling->order_len++;
            }
        }

        if (current_left > 0) current_left--;
        time++;
    }
}

void evaluation(Process** p_arr, Scheduling* scheduling) {
    scheduling->avg_turnaround_time = 0.0;
    scheduling->avg_waiting_time = 0.0;
    for (int i = 0; i < PROC_NUM; i++) {
        int end_time = 0;

        for (int j = scheduling->order_len - 1; j >= 0; j--) {
            if (scheduling->p_idx[j] == i) {
                end_time = scheduling->end_time[j];
                break;
            }
        }

        int turnaround_time = end_time - p_arr[i]->arrival_time;
        int wait_time = turnaround_time - p_arr[i]->cpu_burst_time;

        scheduling->avg_waiting_time += (double)wait_time / (double)PROC_NUM;
        scheduling->avg_turnaround_time += (double)turnaround_time / (double)PROC_NUM;
    }

    printf("Average Waiting Time compare: \n");
    printf("Scheduling %d: %f\n", 0, scheduling->avg_waiting_time);

    printf("\nAverage Turnaround Time compare: \n");
    printf("Scheduling %d: %f\n", 0, scheduling->avg_turnaround_time);
}

void display_gantt(Process** p_arr, Scheduling* scheduling) {
    int last_end_time = 0;
    for (int i = 0; i < scheduling->order_len; i++) {
        if (scheduling->start_time[i] != last_end_time)
            printf("|Wait(%d)", scheduling->start_time[i] - last_end_time);

        int idx = scheduling->p_idx[i];
        printf("│ P%d(%d) ", p_arr[idx]->pid, scheduling->end_time[i] - scheduling->start_time[i]);
        last_end_time = scheduling->end_time[i];
    }
    printf("│\n\n");
}

int main()
{
    Process** p_arr = (Process**)malloc(sizeof(Process*) * PROC_NUM);
    Create_Process(p_arr);

    Scheduling* scheduling_fcfs = (Scheduling*)malloc(sizeof(Scheduling));
    Scheduling* scheduling_sjf = (Scheduling*)malloc(sizeof(Scheduling));
    Scheduling* scheduling_sjf_preemption = (Scheduling*)malloc(sizeof(Scheduling));
    Scheduling* scheduling_priority = (Scheduling*)malloc(sizeof(Scheduling));
    Scheduling* scheduling_priority_preemption = (Scheduling*)malloc(sizeof(Scheduling));
    Scheduling* scheduling_rr = (Scheduling*)malloc(sizeof(Scheduling));

    int num = 0;

    while (1)
    {
        printf("----choose algorithm----");
        printf("1.fcfs\t2.sjf\t3.sjf_preempt\n");
        printf("4.priority\t5.priority_preempt\t6.Round Robin\n");
        scanf("%d", &num);

        switch (num)
        {
        case 1:
            schedule_fcfs(p_arr, scheduling_fcfs);
            evaluation(p_arr, scheduling_fcfs);
            display_gantt(p_arr, scheduling_fcfs);
            break;
        case 2:
            schedule_sjf(p_arr, scheduling_sjf);
            evaluation(p_arr, scheduling_sjf);
            display_gantt(p_arr, scheduling_sjf);
            break;
        case 3:
            schedule_sjf_preemptive(p_arr, scheduling_sjf_preemption);
            evaluation(p_arr, scheduling_sjf_preemption);
            display_gantt(p_arr, scheduling_sjf_preemption);
            break;
        case 4:
            schedule_priority(p_arr, scheduling_priority);
            evaluation(p_arr, scheduling_priority);
            display_gantt(p_arr, scheduling_priority);
            break;
        case 5:
            schedule_priority_preemptive(p_arr, scheduling_priority_preemption);
            evaluation(p_arr, scheduling_priority_preemption);
            display_gantt(p_arr, scheduling_priority_preemption);
            break;
        case 6:
            schedule_rr(p_arr, scheduling_rr);
            evaluation(p_arr, scheduling_rr);
            display_gantt(p_arr, scheduling_rr);
            break;
        case 0:
            return 0;
        default:
            break;
        }
    }

    return 0;
}