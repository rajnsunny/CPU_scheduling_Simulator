#ifndef __HIGHEST__RESPONSE__RATIO__NEXT__
#define __HIGHEST__RESPONSE__RATIO__NEXT__

// HRN Algorithm


#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"

/**
 * [hrn_print_gantt_chart ]
 * @param p  
 * @param len 
 */
void hrn_print_gantt_chart(Process *p, int len)
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
 * [HRN HRN ]
 * @param p   
 * @param len 
 */
void HRN(Process *p, int len)
{
	int i, j;
	
	int time, loc;
	
	int total_burst_time = 0;
	
	int total_waiting_time = 0;
	
	int total_turnaround_time = 0;
	
	int total_response_time = 0;
	

	float hrr, temp;
	

	process_init(p, len);
	// process_init 

	
	for (i = 0; i < len; i++)
	{
		total_burst_time += p[i].burst;
		
	}

	merge_sort_by_arrive_time(p, 0, len);
	// merge_sort_by_arrive_time 

	
	for (time = p[0].arrive_time; time < total_burst_time;)
	{
		hrr = -9999;
		

		
		for (i = 0; i < len; i++)
		{
			
			if ((p[i].arrive_time <= time)
					&& (p[i].completed != TRUE))
			{
				temp = (p[i].burst + (time - p[i].arrive_time)) / p[i].burst;
				
				if (hrr < temp)
				{
					hrr = temp;
				
					loc = i;
					
				}
			}
		}

		time += p[loc].burst;
		
		p[loc].waiting_time = time - p[loc].arrive_time - p[loc].burst;
		p[loc].turnaround_time = time - p[loc].arrive_time;
		p[loc].return_time = p[loc].turnaround_time + p[loc].arrive_time;
		p[loc].response_time = p[loc].waiting_time;
		p[loc].completed = TRUE;

		total_waiting_time += p[loc].waiting_time;
	
		total_turnaround_time += p[loc].turnaround_time;
		
		total_response_time += p[loc].response_time;
	}

	quick_sort_by_return_time(p, len);
	// quick_sort_by_return_time 

	printf("\tHighest Response Ratio Next Scheduling Algorithm\n\n");

	hrn_print_gantt_chart(p, len);
	// hrn_print_gantt_chart 

	
	printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)total_waiting_time / (double)len);
	printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)total_turnaround_time / (double)len);
	printf("\tAverage Response Time    : %-2.2lf\n\n", (double)total_response_time / (double)len);

	print_table(p, len);
	// print_table 
}

#endif
