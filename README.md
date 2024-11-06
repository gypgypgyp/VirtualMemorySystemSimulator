# VirtualMemorySystemSimulator

This is a virtual memory system simulator. It is able to 

1. Split the Address
2. Translate the Address
3. Handle Page Faults
4. Improve the Page Replacement Algorithm


1/ To compile the program, use the following command:

g++ -g -Wall -pedantic -std=c++11 *.c -o vm-sim

2/ The program file generated will be named vm-sim. It takes the name of a memory trace file as an argument, and a few such files are provided for you in the workloads/ directory. For example, to run the simulator with the basic trace file, run:

./vm-sim workloads/basic

3/ There are also several optional command line options that you can play around with, such as changing the memory size and the page size. The defaults are memory size = 16 and page size = 2. To view these options, type:

./vm-sim -h

Here are the contents of the “Basic” trace file:
@ 0 init
@ 1 mozilla s014 s028 s039
s 0 4 10 l028 s116 s129
s 1 3 42
s 1 4 11 l129 l116 l039 l028
Example lines:
“s 0 1 4”→Proceed id 0 (init) STORED 4 as data in virtual address 00001. “l 0 2 8”→Process id 0 (init) LOADED 8 as data from virtual address 00002