/* -*- c -*- */
#include "tort/core.h"

tort_GETTER(symbol,tort_v,name);
tort_GETTER(symbol,tort_v,version);
#if TORT_ANON_SYMBOL_MTABLE
tort_GETTER(symbol,tort_v,mtable_method_map);
#endif

const char *_tort_symbol_name(tort_v sym) 
{ 
  return tort_string_data(tort_ref(tort_symbol, sym)->name);
}

tort_symbol* _tort_M_symbol___create(tort_tp tort_mtable *mtable, tort_v name)
{
  tort_symbol *value = tort_allocate(mtable, sizeof(tort_symbol));
  value->name = name;
  value->version = tort_i(0);
#if TORT_ANON_SYMBOL_MTABLE
  value->mtable_method_map = ( name == tort_nil || name == 0 ) ? tort_map_create() : tort_nil;
#endif
  return value;
}

tort_symbol* _tort_M_symbol__new(tort_tp tort_mtable *mtable, tort_v name)
{
  return tort_symbol_new(name != tort_nil ? tort_string_data(name) : 0);
}

tort_symbol* tort_symbol_new(const char *string)
{
  if ( string ) {
    tort_pair *e = _tort_m_map__get_entry_cstr(tort_ta tort_(symbols), string);
    if ( e ) {
      // fprintf(stderr, "\n old symbol = %s %p\n", tort_symbol_data(e->second), (void *) e->second);
      return e->second;
    } else {
      tort_string *name = tort_string_new_cstr(string);
      tort_symbol *sym = _tort_M_symbol___create(tort_ta tort__mt(symbol), name);
      _tort_m_map__add(tort_ta tort_(symbols), name, sym);
      // fprintf(stderr, "\n new symbol = %s %p\n", tort_symbol_data(value), (void *) value);
      return sym;
    }
  } else {
    return _tort_M_symbol___create(tort_ta tort__mt(symbol), tort_nil);
  }
}

tort_v tort_runtime_initialize_symbol()
{
#define tort_d_s(N) tort__s(N) = tort_symbol_new(tort_symbol_encode(#N));
#include "tort/d_s.h"

  /* Prepare special symbol table get method. */
  tort_h(tort_(symbols))->mtable = tort_mtable_create(tort_h_mtable(tort_(symbols)));
  tort_add_method(tort_h_mtable(tort_(symbols)), "get", _tort_m_map__get_string);
  tort_add_method(tort_h_mtable(tort_(symbols)), "set", _tort_m_object__identity);
  tort_add_method(tort_h_mtable(tort_(symbols)), "delete", _tort_m_object__identity);

  return tort_(symbols);
}

