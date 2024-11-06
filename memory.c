#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "pagetable.h"
#include "useful.h"

#include "memory.h"

/*******************************************************************************
 * Main memory.
 */
uint8_t *memory;

/*******************************************************************************
 * Loads the data given by the virtual address, using the virutal -> physical
 * translation system of the CPU.
 *
 * @param va The virtual address to read.
 * @return The data at the given address.
 */
word_t mem_load(vaddr_t va) {

   word_t data = memory[translate(va, 0)];
   count_reads++;

   printf("LOADED %3.3hu as data from virtual address %5.5hu.\n", data, va);
   return data;
}

/**
 * Stores the data given by the virtual address, using the virutal -> physical
 * translation system of the CPU.
 *
 * @param va The virtual address to write.
 * @param data The data to write to the address.
 */
void mem_store(vaddr_t va, word_t data) {

   memory[translate(va, 1)] = data;
   count_writes++;

   printf("STORED %3.3u as data in virtual address %5.5u.\n", data, va);
}

/*******************************************************************************
 * Initializes all memory controlled by the processory -- that is, the physical
 * memory and the TLB.
 */
void mem_init(void) {
   if ((memory = (uint8_t*) calloc(mem_size, sizeof(unsigned char))) == NULL) {
      PERROR("calloc");
      exit(EXIT_FAILURE);
   }
}

/*******************************************************************************
 * Frees all the memory used to represent physical memory
 */
void mem_free(void) {
   free(memory);
}
