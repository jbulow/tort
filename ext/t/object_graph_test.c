#include "tort/tort.h"
#include "tort/block.h"

#include <stdio.h>


int main(int argc, char **argv, char **environ)
{
  tort_v io;
 
  tort_runtime_create();
  // { extern int _tort_dl_debug; _tort_dl_debug = 1; }
  tort_send(tort_s(_dlopen), tort_string_new_cstr("libtortext"));

  io = tort_stdout;

  {
    extern void tog(tort_v);
    tog(_tort->_mt_object);
  }
  tort_printf(io, "\n\nDONE\n");

  return 0;
}

