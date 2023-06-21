#ifndef __FIRST__COME__FIRST__SERVED__
#define __FIRST__COME__FIRST__SERVED__

// FCFS Algorithm


#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"

/**
 * [fcfs_print_gantt_chart ]
 * @param p  
 * @param len 
 */
void fcfs_print_gantt_chart(Process *p, int len)
{
	int i, j;
	

	printf("\t ");

	
	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].burst; j++)
			printf("--");

		printf(" ");
	}

	printf("\n\t|");

	
	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].burst - 1; j++)
			printf(" ");

		printf("%s", p[i].id);

		for (j = 0; j < p[i].burst - 1; j++)
			printf(" ");

		printf("|");
	}

	printf("\n\t ");


	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].burst; j++)
			printf("--");

		printf(" ");
	}

	printf("\n\t");

	
	printf("0");

	for (i = 0; i < len; i++)
	{
		for (j = 0; j < p[i].burst; j++)
			printf("  ");

		if (p[i].return_time > 9)
			printf("\b");

		printf("%d", p[i].return_time);

	}

	printf("\n");
}

/**
 * [FCFS FCFS ]
 * @param p   
 * @param len 
 */
void FCFS(Process *p, int len)
{
	int i;
	
	int total_waiting_time = 0;
	
	int total_turnaround_time = 0;
	
	int total_response_time = 0;
	
	int total_return_time = 0;
	

	process_init(p, len);
	// process_init 

	merge_sort_by_arrive_time(p, 0, len);
	// merge_sort_by_arrive_time 

	
	p[0].return_time = p[0].burst;
	p[0].turnaround_time = p[0].return_time - p[0].arrive_time;
	p[0].response_time = 0;
	p[0].waiting_time = 0;

	
	total_response_time += p[0].response_time;
	total_waiting_time += p[0].waiting_time;
	total_turnaround_time += p[0].turnaround_time;
	total_return_time += p[0].burst;

	
	for (i = 1; i < len; i++)
	{
		
		p[i].waiting_time = total_return_time - p[i].arrive_time;
		p[i].return_time = total_return_time + p[i].burst;
		p[i].turnaround_time = p[i].return_time - p[i].arrive_time;
		p[i].response_time = p[i].waiting_time;

		
		total_return_time += p[i].burst;
		total_waiting_time += p[i].waiting_time;
		total_turnaround_time += p[i].turnaround_time;
		total_response_time += p[i].response_time;
	}

	printf("\n\tFCFS Scheduling Algorithm\n\n");

	fcfs_print_gantt_chart(p, len);
	// fcfs_print_gantt_chart 

	
	printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
	printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)total_turnaround_time / (double)len);
	printf("\tAverage Response Time    : %-2.2lf\n\n", (double)total_response_time / (double)len);

	print_table(p, len);
	// print_table 
}

#endif
