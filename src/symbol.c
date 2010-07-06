#include "tort/core.h"


/********************************************************************/


tort_v tort_symbol_make(const char *string)
{
  if ( string ) {
  tort_map_entry *e = _tort_map_get_entry_cstr(0, _tort->symbols, string);
  if ( e ) {
    // fprintf(stderr, "\n old symbol = %s %p\n", tort_symbol_data(e->value), (void *) e->value);
    return e->value;
  } else {
    tort_v key, value;
    key = tort_string_new_cstr(string);
    value = tort_allocate(0, 0, sizeof(tort_symbol), _tort->_mt_symbol);
    tort_ref(tort_symbol, value)->name = key;
    _tort_map_add(0, _tort->symbols, key, value);
    // fprintf(stderr, "\n new symbol = %s %p\n", tort_symbol_data(value), (void *) value);
    return value;
  } 
  } else {
    tort_v value;
    value = tort_allocate(0, 0, sizeof(tort_symbol), _tort->_mt_symbol);
    tort_ref(tort_symbol, value)->name = tort_nil;
    return value;
  }
}

