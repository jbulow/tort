#ifndef _tort_INIT_H
#define _tort_INIT_H

tort_v tort_runtime_initialize_malloc();
tort_v tort_runtime_initialize_error();
tort_v tort_runtime_initialize_mtable();
tort_v tort_runtime_initialize_symbol();
tort_v tort_runtime_initialize_gc();
tort_v tort_runtime_initialize_io();
tort_v tort_runtime_initialize_printf();
tort_v tort_runtime_initialize_write();
tort_v tort_runtime_initialize_debug();
tort_v tort_runtime_initialize_method();
tort_v tort_runtime_initialize_lookup();
tort_v tort_runtime_initialize_tort();
tort_v tort_runtime_initialize_dynlib();

#endif
