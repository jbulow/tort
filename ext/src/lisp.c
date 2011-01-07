#include "tort/lisp.h"

/********************************************************************/

tort_v _tort_M_pair__new(tort_thread_param tort_v pair_mt, tort_v a, tort_v d)
{
  tort_pair *pair = tort_send(tort__s(_allocate), pair_mt, sizeof(*pair));
  pair->car = a;
  pair->cdr = d;
  return pair;
}


#define ACCESSOR(X)							\
  tort_v _tort_m_pair__##X(tort_thread_param tort_v rcvr)		\
  {									\
    return tort_ref(tort_pair, rcvr)->X;				\
  }									\
  tort_v tort_##X(tort_v rcvr) {					\
    return tort_send(tort_s(X), rcvr);					\
  }									\
  tort_v _tort_m_pair__setD##X##E(tort_thread_param tort_v rcvr,	\
			       tort_v val)				\
  {									\
    tort_ref(tort_pair, rcvr)->X = val;					\
    return rcvr;							\
  }

ACCESSOR(car)
ACCESSOR(cdr)

#undef ACCESSOR

tort_v tort_caar(tort_v v) 
{
  return tort_car(tort_car(v));
}
tort_v tort_cdar(tort_v v) 
{
  return tort_cdr(tort_car(v));
}
tort_v tort_cadr(tort_v v) 
{
  return tort_car(tort_cdr(v));
}
tort_v tort_cddr(tort_v v) 
{
  return tort_cdr(tort_cdr(v));
}
tort_v tort_caddr(tort_v v) 
{
  return tort_cdr(tort_cddr(v));
}


tort_v _tort_m_list__size(tort_tp tort_pair *rcvr) /**/
{
  size_t i = 0;
  while ( rcvr != tort_nil )  {
    ++ i;
    if ( tort_h_mtable(rcvr) == tort_mt(pair) ) {
      rcvr = rcvr->cdr;
    } else {
      break;
    }
  }
  return tort_i(i);
}


tort_v _tort_m_list__lisp_write(tort_thread_param tort_v rcvr, tort_v io) /**/
{
  tort_printf(io, "(");
  while ( rcvr != tort_nil ) {
    if ( tort_h_mtable(rcvr) == tort_mt(pair) ) {
      tort_send(tort_s(lisp_write), tort_ref(tort_pair, rcvr)->car, io);
      rcvr = tort_ref(tort_pair, rcvr)->cdr;
      if ( rcvr == tort_nil ) break;
    } else {
      tort_printf(io, ". ");
      tort_send(tort_s(lisp_write), rcvr, io);
      break;
    }
    tort_printf(io, " "); 
  } 
  tort_printf(io, ")");
  return tort_nil;
}


tort_v _tort_m_list__list_TO_vector(tort_thread_param tort_v rcvr, tort_v io) /**/
{
  tort_v size = tort_send(tort__s(size), rcvr);
  tort_v vec = tort_vector_new(0, tort_I(size));
  size_t i = 0;
  while ( rcvr != tort_nil ) {
    if ( tort_h_mtable(rcvr) == tort_mt(pair) ) {
      tort_vector_data(vec)[i ++] = tort_ref(tort_pair, rcvr)->car;
      rcvr = tort_ref(tort_pair, rcvr)->cdr;
    } else {
      tort_vector_data(vec)[i ++] = rcvr;
      break;
    }
  } 
  return vec;
}


#define IO (io ? io : tort_stdout)
#define printf(fmt, args...) tort_printf(IO, fmt, ##args)


tort_v _tort_m_object__lisp_write(tort_thread_param tort_v rcvr, tort_v io)
{
  printf("(make <object> @%p)", (void *) rcvr);
  return tort_nil;
}


tort_v _tort_m_vector__lisp_write(tort_tp tort_vector *rcvr, tort_v io)
{
  printf("#(");
  tort_vector_loop(rcvr, obj) {
    if ( obj_i > 0 ) printf(" ");
    tort_send(tort_s(lisp_write), obj, IO);
  } tort_vector_loop_end(rcvr);
  printf(")");
  return tort_nil;
}


tort_v _tort_m_symbol__lisp_write(tort_tp tort_symbol *rcvr, tort_v io)
{
  if ( rcvr->name != tort_nil ) {
    printf("%s", (char *) tort_symbol_data(rcvr));
  } else {
    printf("(make <symbol> @%p)", (void*) rcvr);
  }
  return tort_nil;
}


tort_v _tort_m_boolean__lisp_write(tort_thread_param tort_v rcvr, tort_v io)
{
  printf(rcvr == tort_false ? "#f" : "#t");
  return tort_nil;
}


tort_v _tort_m_map__lisp_write(tort_thread_param tort_v rcvr, tort_v io)
{
  size_t entry_i = 0;
  printf("(make <map> ");
  tort_map_EACH(rcvr, entry) {
    if ( entry_i > 0 ) printf(" ");
    tort_send(tort_s(lisp_write), entry->key, IO);
    printf(" ");
    tort_send(tort_s(lisp_write), entry->value, IO);
    entry_i ++;
  } tort_map_EACH_END();
  printf(")");
  return tort_nil;
}


tort_v _tort_m_eos__lisp_write(tort_thread_param tort_v rcvr, tort_v io)
{
  printf("#e");
  return tort_nil;
}


#undef printf
#undef IO


/********************************************************************/

extern 
tort_v _tort_m_io__lisp_read (tort_thread_param tort_v stream)
  ;

#define FP(s) tort_ref(tort_io, s)->fp

#define VALUE tort_v
#define READ_DECL VALUE _tort_m_io__lisp_read (tort_thread_param tort_v stream)
#define READ_CALL() tort_send(tort_s(lisp_read), stream)
#define MALLOC(s) tort_malloc(s)
#define REALLOC(p, s) tort_realloc(p, s)
#define GETC(s) fgetc(FP(s))
#define UNGETC(s, c) ungetc(c, FP(s))
#define EOS tort_eos
#define CONS(x,y) tort_send(tort_s(new), tort_mt(pair), x, y)
#define SET_CDR(CONS,V) tort_send(tort_s(setDcdrE), CONS, V)
#define MAKE_CHAR(I) tort_i(I)
#define STRING(b, l) tort_string_new(b, l)
#define LIST_2_VECTOR(X) tort_send(tort_s(list_TO_vector), X)
#define SYMBOL_DOT tort_s(DOT)
#define SYMBOL(NAME) tort_s(NAME)
#define STRING_2_NUMBER(s, radix) _tort_string_to_number(s, radix)
#define STRING_2_SYMBOL(s) tort_symbol_make(tort_string_data(s))
#define EQ(X, Y) ((X) == (Y))
#define NIL tort_nil
#define T  tort_true
#define F  tort_false
#define U  tort_nil
#define ERROR(format, args...) tort_error(format, ##args)

tort_v _tort_string_to_number(tort_v s, int radix) /**/
{
  long d = 0;
  if ( radix == 10 && sscanf(tort_string_data(s), "%ld", &d) == 1 ) {
    return tort_i(d);
  } else {
    return tort_false;
  }
}

#include "lispread.c"

tort_v tort_runtime_initialize_lisp()
{
  tort_v _mt_pair = tort_mtable_make("pair", 0);
  tort_mtable_make("list", 0);

  /* Reused methods. */
  tort_add_method(tort__mt(tagged), "lisp_write", _tort_m_tagged___inspect);
  tort_add_method(tort__mt(string), "lisp_write", _tort_m_string___inspect);
  tort_add_method(tort__mt(method), "lisp_write", _tort_m_method___inspect);
  tort_add_method(tort__mt(message), "lisp_write", _tort_m_message___inspect);
  tort_add_method(tort__mt(nil),    "lisp_write", _tort_m_nil___inspect);

  tort_add_method(_mt_pair, "value", _tort_m_pair__car);

  tort_add_method(_mt_pair, "lisp_write", _tort_m_list__lisp_write);
  tort_add_method(tort__mt(nil),  "lisp_write", _tort_m_list__lisp_write);
  tort_add_method(_mt_pair, "size", _tort_m_list__size);
  tort_add_method(tort__mt(nil),  "size", _tort_m_list__size);
  tort_add_method(_mt_pair, "list->vector", _tort_m_list__list_TO_vector);
  tort_add_method(tort__mt(nil),  "list->vector", _tort_m_list__list_TO_vector);

  return _mt_pair;
}

