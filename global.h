#ifndef _GLOBAL_H_
#define _GLOBAL_H_

/*******************************************************************************
 * Make the page_size variable globally accessible.
 */
extern unsigned page_size;

/*******************************************************************************
 * Make the mem_size variable globally accessible.
 */
extern unsigned mem_size;

/*******************************************************************************
 * Display the stastics gathered from executing the simulator.
 */
/* void display_statistics(); */

/*******************************************************************************
 * Compute the Average Mean Access Time.
 */
/* double compute_emat(); */

/*******************************************************************************
 * Number of pagefaults generated during execution.
 */
extern unsigned long int count_pagefaults;

/*******************************************************************************
 * Number of TLB hits generated during execution.
 */
extern unsigned long int count_tlbhits;

/*******************************************************************************
 * Raw number of stores executed.
 */
extern unsigned long int count_writes;

/*******************************************************************************
 * Raw number of loads executed.
 */
extern unsigned long int count_reads;

/*******************************************************************************
 * Raw number of loads executed.
 */
extern unsigned long int count_diskaccesses;

#endif/*_GLOBAL_H_*/
