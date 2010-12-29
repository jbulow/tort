#include "tort/tort.h"
#include <stdio.h>

int main(int argc, char **argv, char **environ)
{
  tort_v io;
  tort_v v;

  tort_runtime_create();

  io = tort_stdout;

  tort_printf(io, "  123 => obj %lld\n", (long long) (v = tort_i(123)));
  tort_printf(io, "  123 => int %lld\n", (long long) tort_I(v));

  printf("\nDONE\n");

  return 0;
}

