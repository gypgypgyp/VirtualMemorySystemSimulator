#ifndef _SWAPFILE_H_
#define _SWAPFILE_H_

#include "types.h"

/*******************************************************************************
 * Save the given physical frame to disk with the given virtual page
 * information.
 *
 * @param pfn The physical frame to save.
 * @param vpn The virtual page number this frame holds.
 * @param pid The process identifier of the process that owns this frame.
 */
void save_page_to_disk(pfn_t pfn, vpn_t vpn, int pid);

/*******************************************************************************
 * Restores the given virtual page to the given physical frame.
 *
 * @param pfn The physical frame to restore the data to.
 * @param vpn The virtual page number of the page to restore.
 * @param pid The process identifer of the page's owner process.
 */
void load_page_from_disk(pfn_t pfn, vpn_t vpn, int pid);

/*******************************************************************************
 * Free the linked list maintained by the paging system.
 */
void swapfile_free(void);

#endif/*_SWAPFILE_H_*/
