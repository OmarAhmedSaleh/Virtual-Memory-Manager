#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <alloca.h>

#define FRAME_SIZE 256        // size of the frame
#define TOTAL_NUMBER_OF_FRAMES 256  // total number of frames in physical memory
#define ADDRESS_MASK  0xFFFF  //mask all but the address
#define OFFSET_MASK  0xFF //mask all but the offset
#define TLB_SIZE 16       // size of the TLB
#define PAGE_TABLE_SIZE 256  // size of the page table

int pageTableNumbers[PAGE_TABLE_SIZE];  // array to hold the page numbers in the page table
int pageTableFrames[PAGE_TABLE_SIZE];   // array to hold the frame numbers in the page table

int TLBPageNumber[TLB_SIZE];  // array to hold the page numbers in the TLB
int TLBFrameNumber[TLB_SIZE]; // array to hold the frame numbers in the TLB

int physicalMemory[TOTAL_NUMBER_OF_FRAMES][FRAME_SIZE]; // physical memory 2D array

int pageFaults = 0;   // counter to track page faults
int TLBHits = 0;      // counter to track TLB hits
int firstAvailableFrame = 0;  // counter to track the first available frame
int firstAvailablePageTableNumber = 0;  // counter to track the first available page table entry
int numberOfTLBEntries = 0;             // counter to track the number of entries in the TLB

// number of characters to read for each line from input file
#define BUFFER_SIZE 10

// number of bytes to read
#define CHUNK  256

// input file and backing store
FILE    *address_file;
FILE    *backing_store;

// how we store reads from input file
char address[BUFFER_SIZE];
int logical_address;

// the buffer containing reads from backing store
signed char buffer[CHUNK];

// the value of the byte (signed char) in memory
signed char  value;

// headers for the functions used below
void getPage(int address);
void readFromStore(int pageNumber);
void insertIntoTLB(int pageNumber, int frameNumber);