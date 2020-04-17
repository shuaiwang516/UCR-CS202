#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
  int numberOfProcess = info(1);
  info(1);
  int syscalls = info(2);
  printf(1,"Now we have %d processes in this system, and this process has made %d times system calls\n",numberOfProcess, syscalls); 

  int pages = info(3);
  printf(1, "The total number of the memory pages the current process is using: %d\n", pages);

  exit();
}
