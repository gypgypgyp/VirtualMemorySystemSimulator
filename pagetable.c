#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "pagetable.h"
#include "swapfile.h"
#include "process.h"
#include "global.h"


/*******************************************************************************
 * GLOBALS (you will use this in the translate() function)
 */

/*
 * Current page table register, used by the processor to find the running
 * processes page table. The scheduler will update this when it dispatches
 * a new process, so you may assume it always points to the page table for
 * the /current/ process. A page table is an array of pte_t.
 */

pte_t* ptbr; /* Page Table Base Register on the CPU */



/*******************************************************************************
 * Get the page number from a virtual address.
 * @param addr The virtual address.
 * @return     The virtual page number (VPN) for this addres.
 */

vpn_t get_vpn(vaddr_t virt_addr) {
//write code to return the virtual page number for the virtual address passed in

    return virt_addr/page_size;
}



/*******************************************************************************
 * Get the offset for a particular address.
 * @param addr The virtual address.
 * @return     The offset into a page for the given virtual address.
 */

offset_t get_offset(vaddr_t virt_addr) {
	//write code to return the offset into a page for the given virtual address
   return virt_addr% page_size;
}


/*******************************************************************************
 * Create a physical address from a PFN and an offset.
 * @param The physical frame number (PFN).
 * @param The offset into the page.
 * @return The physical address.
 */

paddr_t create_paddr(pfn_t pfn, offset_t offset) {
	//write code to return the physical address given the two parameters
  return (pfn * page_size) + offset;;
}


/*******************************************************************************
 * Looks up an address in the current page table and returns the translated
 * physical address. If the entry for the given page is not valid, traps to
 * the OS (simulated by calling the pagefault_handler function).
 *
 * @param virt_addr The virtual address to translate.
 * @param write If the access is a write, this is 1. Otherwise, it is 0.
 * @return The physical address we are accessing.
 */

paddr_t translate(vaddr_t virt_addr, int write) {
  vpn_t vpn;
  offset_t offset;
  pfn_t pfn;
  paddr_t phys_addr;

  /* Sanity Check */
  assert(ptbr != NULL); /* do NOT modify */

  /* Break down the virtual address into VPN and Offset */
    vpn = get_vpn(virt_addr);
    offset = get_offset(virt_addr);
  
  printf("Virtual Address %5.5hu (VPN: %5.5hu OFFSET: %5.5hu)\n",
         virt_addr, vpn, offset); /* do NOT modify this output statement */

  /* If the page table entry is not valid, raise a page fault */
    pte_t *pte = &ptbr[vpn];
    if (!pte->valid){
        pagefault_handler(vpn);
    }

  /* Update used and dirty bits */
    pte->used = 1;
    if(write){
        pte->dirty=1;
    }

  /* Complete the translation */
    pfn = pte->pfn;
    phys_addr = create_paddr(pfn, offset);

  printf("Physical Address %5.5hu (PFN: %5.5hu OFFSET: %5.5hu)\n",
         phys_addr, pfn, offset); /* do NOT modify this output statement */
  return phys_addr;
}
