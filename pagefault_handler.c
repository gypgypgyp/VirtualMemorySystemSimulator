#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "swapfile.h"
#include "process.h"
#include "global.h"

pfn_t get_free_frame(void);


/*******************************************************************************
 * Page fault handler. When the CPU encounters an invalid address mapping in a
 * process' page table, it invokes the CPU via this handler. The OS then
 * allocates a physical frame for the requested page (either by using a free
 * frame or evicting one), changes the process' page table to reflect the
 * mapping and then restarts the interrupted process.
 *
 * @param vpn The virtual page number requested.
 */

void pagefault_handler(vpn_t request_vpn) {
  pfn_t frame_pfn;
  vpn_t victim_vpn;
  pcb_t *victim_pcb;

  /* Sanity Check */
  assert(ptbr != NULL); /* do NOT modify */

  /* Add 1 to the Page Fault count */
  count_pagefaults++; /* do NOT modify */

  /* Find a free or victim frame */
  frame_pfn = get_free_frame();
  assert(frame_pfn < CPU_NUM_FRAMES); /* make sure the frame no. is valid */


  /* Use the Frame Table (reverse lookup table) to find the victim. Also check, initialize victim_pcb to know if victim is a free frame or not.*/
  fte_t *frame = &frametable[frame_pfn];
  victim_pcb = frame->pcb;
  victim_vpn = frame->vpn;

  printf("****PAGE FAULT has occurred at VPN %u. Evicting (PFN %u VPN %u) as victim.\n",
         request_vpn, frame_pfn, victim_vpn); /* do NOT modify this output statement */

  /* If there is a victim (i.e., wasn't a free frame) then evict it */
  if (victim_pcb) {
    printf("**** evicting victim page VPN %hu from frame PFN %hu\n", victim_vpn, frame_pfn);

    /* mark victim page as invalid */
      pte_t *victim_pte = &victim_pcb->pagetable[victim_vpn];
      victim_pte->valid = 0;


    /* if victim page is dirty, save it to the disk */
      if (victim_pte->dirty) {
          save_page_to_disk(frame_pfn, victim_vpn, victim_pcb->pid);
      }
  } else {
    printf("**** using free frame PFN %hu\n", frame_pfn);
  }

  /* Retreive the page from disk (or create a new page if it doesn't exist). */

    load_page_from_disk(frame_pfn, request_vpn, current->pid);

  /* update the faulting process page table; set the pfn, valid bit, dirty bit, used bit; initially used bit will be 0  */

    pte_t *new_pte = &ptbr[request_vpn];
    new_pte->pfn = frame_pfn;
    new_pte->valid = 1;
    new_pte->used = 0;
    new_pte->dirty = 0;


  /* update the frame table */
    frame->pcb = current;
    frame->vpn = request_vpn;

}


/*******************************************************************************
 * Finds a free physical frame. If none are available, uses a clock sweep
 * algorithm to find a used frame for eviction.
 *
 * @return The physical frame number of a free (or evictable) frame.
 */

pfn_t get_free_frame(void) {
   static pfn_t next_frame = 0;
   pfn_t victim_frame, i;
   pte_t* pt;

   /* See if there are any free frames */
   /* do NOT modify this for loop */
   for (i = 0; i < CPU_NUM_FRAMES; i++)
      if (frametable[i].pcb == NULL) {
         return i;
      }

   /* Implement the Clock Sweep Algorithm */
   assert(frametable[next_frame].pcb != NULL); /* should be NO free frames */
    while (frametable[next_frame].pcb != NULL){
        pt = &(frametable[next_frame].pcb->pagetable[frametable[next_frame].vpn]);
        if (pt->used==0){
            break;
        }else{
            pt->used = 0;
        }
        next_frame = (next_frame + 1) % CPU_NUM_FRAMES;
    }

   /* AT this point, next_frame now points to the chosen victim (which has used bit == 0) */

   victim_frame = next_frame;                      /* assign the chosen victim to frame (temp variable) */
   next_frame = (next_frame + 1) % CPU_NUM_FRAMES; /* increment next_frame to point to next one to look at */
   /* victim_frame now points to the chose victim, and
    * next_frame points to where to resume for the next eviction */

   return victim_frame;
}
