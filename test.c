#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
  int numberOfProcess = info(1);
  int pages = info(3);
  int syscalls = info(2);

  printf(1,"Now we have %d processes in this system.\nThis process has made %d times system calls in main() function.\n",numberOfProcess, syscalls);
  printf(1, "The total number of the memory pages the current process is using: %d\n", pages);
  exit();
}
