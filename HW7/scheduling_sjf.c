#include <stdio.h>

struct myStr {
    int pid, arrival_time, burst_time;
    int waiting_time, turnaround_time, response_time;
};

int main() {
    int n, completed = 0, current = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct myStr s[n];
    int done[n];
    for (int i = 0; i < n; i++) {
        s[i].pid = i + 1;
        printf("\nEnter Arrival Time and Burst Time for each process (AT BT):\n");
        scanf("%d %d", &s[i].arrival_time, &s[i].burst_time);
        done[i] = 0;
    }

    printf("\nSJF Scheduling!!!!\n");
    printf("Gantt Chart: ");


    while (completed < n) {
        int idx = -1, min_bt = 9999;
        for (int i = 0; i < n; i++) {
            if (!done[i] && s[i].arrival_time <= current) {
               if (s[i].burst_time < min_bt || 
                  (s[i].burst_time == min_bt && s[i].arrival_time < s[idx].arrival_time) ||
                  (s[i].burst_time == min_bt && s[i].arrival_time == s[idx].arrival_time && s[i].pid < s[idx].pid)) {
                  min_bt = s[i].burst_time;
                 idx = i;
               }
           }
        }

        if (idx != -1) {
            printf("| P%d ", s[idx].pid);
            s[idx].response_time = current - s[idx].arrival_time;
            s[idx].waiting_time = s[idx].response_time;
            current += s[idx].burst_time;
            s[idx].turnaround_time = current - s[idx].arrival_time;
            done[idx] = 1;
            completed++;
        } else current++;
    }

    printf("|\n\nPID\tAT\tBT\tWT\tTAT\tRT\n");
    float twt = 0, ttat = 0;
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               s[i].pid, s[i].arrival_time, s[i].burst_time,
               s[i].waiting_time, s[i].turnaround_time, s[i].response_time);
        twt += s[i].waiting_time;
        ttat += s[i].turnaround_time;
    }

    printf("\nAvg WT=%.2f  Avg TAT=%.2f\n", twt / n, ttat / n);
    return 0;
}


