#ifndef _PAGETABLE_H_
#define _PAGETABLE_H_

#include "types.h"

/*******************************************************************************
 * Page table entry.
 */

typedef struct {
  pfn_t pfn;            /* Physical frame number */
  unsigned char valid;  /* Valid 'bit' - may be 1 or 0 */
  unsigned char dirty;  /* Dirty 'bit' - may be 1 or 0 */
  unsigned char used;   /* Used (i.e., accessed recently) 'bit' - may be 1 or 0 */
} pte_t;


/*******************************************************************************
 * Current page table register, used by the processor to find the running
 * processes page table. The scheduler will update this when it dispatches
 * a new process, so you may assume it always points to the page table for
 * the /current/ process. A page table is an array of pte_t.
 */
extern pte_t* ptbr; /* Page Table Base Register on the CPU */

/*******************************************************************************
 * Number of entries in a page table
 */
extern uint16_t CPU_NUM_PTE;

/*******************************************************************************
 * Number of frames in memory 
 */
extern uint16_t CPU_NUM_FRAMES;


/*******************************************************************************
 * Looks up an address in the current page table and returns the translated
 * physical address. If the entry for the given page is not valid, traps to
 * the OS (simulated by calling the pagefault_handler function).
 *
 * @param virt_addr The virtual address to translate.
 * @param write If the access is a write, this is 1. Otherwise, it is 0.
 * @return The physical address we are accessing.
 */

paddr_t translate(vaddr_t virt_addr, int write);


/*******************************************************************************
 * Page fault handler. When the CPU encounters an invalid address mapping in a
 * process' page table, it invokes the CPU via this handler. The OS then
 * allocates a physical frame for the requested page (either by using a free
 * frame or evicting one), changes the process' page table to reflect the
 * mapping and then restarts the interrupted process.
 *
 * @param vpn The virtual page number requested.
 */

void pagefault_handler(vpn_t request_vpn);


#endif/*_PAGETABLE_H_*/
