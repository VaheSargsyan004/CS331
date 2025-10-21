#include <stdio.h>

struct myStr{
  int pid;
  int arrival_time;
  int burst_time;
  int turnaround_time;
  int waiting_time;
  int response_time;
};

void sortByArrival(struct myStr s[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (s[i].arrival_time > s[j].arrival_time ||
               (s[i].arrival_time == s[j].arrival_time && s[i].pid > s[j].pid)) {
                struct myStr temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }
}


void fcfs(struct myStr s[], int n) {
    sortByArrival(s, n);   

    int current_time = 0;
    float total_wt = 0;
    float total_tat = 0;

    printf("\nFCFS Scheduling!!!!\n");
    printf("Gantt Chart: ");

    for (int i = 0; i < n; i++) {
        if (current_time < s[i].arrival_time)
            current_time = s[i].arrival_time;

        printf("| P%d ", s[i].pid);

        s[i].response_time = current_time - s[i].arrival_time;
        s[i].waiting_time = s[i].response_time;
        current_time += s[i].burst_time;
        s[i].turnaround_time = current_time - s[i].arrival_time;

        total_wt += s[i].waiting_time;
        total_tat += s[i].turnaround_time;
    }

    printf("|\n\nPID\tAT\tBT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               s[i].pid,
               s[i].arrival_time,
               s[i].burst_time,
               s[i].waiting_time,
               s[i].turnaround_time,
               s[i].response_time);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}


int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct myStr s[n];

    printf("\nEnter Arrival Time and Burst Time for each process (AT BT):\n");
    for (int i = 0; i < n; i++) {
        s[i].pid = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d %d", &s[i].arrival_time, &s[i].burst_time);
    }


    fcfs(s, n);

    return 0;
}
