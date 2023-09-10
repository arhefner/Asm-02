#include <stdio.h>
#include <stdlib.h>
#include "mmap.h"

#define MEMORY_SIZE         65536
#define BLOCK_SIZE          (MEMORY_SIZE / 16)
#define NUM_BLOCKS          (MEMORY_SIZE / BLOCK_SIZE)
#define PAGE_SIZE           256
#define PAGES_PER_BLOCK     (BLOCK_SIZE / PAGE_SIZE)
#define OCTETS_PER_PAGE     (PAGE_SIZE / 8)

static uint8_t *memoryMap;
static bool initialized = false;

bool mmapInit()
{
  memoryMap = (uint8_t *)calloc(MEMORY_SIZE / 8, sizeof(uint8_t));

  if (memoryMap == NULL)
  {
    return false;
  }

  initialized = true;
  return true;
}

bool mmapCheck(uint16_t address)
{
  unsigned index;
  uint8_t mask;

  index = address / 8;
  mask = 1 << (address % 8);

  if (memoryMap[index] & mask)
  {
    return false;
  }

  memoryMap[index] |= mask;
  return true;
}

void mmapPrint()
{
  bool clear;
  int index;

  if (!initialized) return;

  printf("Memory Map:\n");

  index = 0;

  for (int block = 0; block < NUM_BLOCKS; block++)
  {
    fprintf(stdout, "%04x | ", block * BLOCK_SIZE);
    for (int page = 0; page < PAGES_PER_BLOCK; page++)
    {
      clear = true;
      for (int octet = 0; octet < OCTETS_PER_PAGE; octet++)
      {
        if (memoryMap[index+octet])
        {
          clear = false;
          break;
        }
      }
      index += OCTETS_PER_PAGE;
      fputc(clear ? '.' : '*', stdout);
    }
    fputc('\n', stdout);
  }
}