#include "tort/core.h"

tort_v tort_ptr_new(void *ptr)
{
  tort_v val = tort_allocate(tort__mt(ptr), sizeof(tort_ptr));
  tort_P(val) = ptr;
  return val;
}

tort_v _tort_m_ptr___ptr_data(tort_tp tort_v p, void **pptr)
{
  *pptr = tort_P(p);
  return p;
}

tort_v _tort_m_ptr___ccall(tort_tp tort_v p)
{
  void *ptr = tort_P(p);
  return ((tort_v(*)(void)) ptr)();
}

tort_v _tort_m_ptr___ccallv(tort_tp tort_v p, tort_vector *args)
{
  void *ptr = tort_P(p);
#define a(i) tort_vector_data(args)[i]
#define T tort_v
  switch ( tort_vector_size(args) ) {
  case 0:
    return ((T(*)(void)) ptr)
      ();
  case 1:
    return ((T(*)(T)) ptr)
      (a(0));
  case 2:
    return ((T(*)(T,T)) ptr)
      (a(0), a(1));
  case 3:
    return ((T(*)(T,T,T)) ptr)
      (a(0), a(1), a(2));
  case 4:
    return ((T(*)(T,T,T,T)) ptr)
      (a(0), a(1), a(2), a(3));
  case 5:
    return ((T(*)(T,T,T,T,T)) ptr)
      (a(0), a(1), a(2), a(3), a(4));
  case 6:
    return ((T(*)(T,T,T,T,T,T)) ptr)
      (a(0), a(1), a(2), a(3), a(4), a(5));
  case 7:
    return ((T(*)(T,T,T,T,T,T,T)) ptr)
      (a(0), a(1), a(2), a(3), a(4), a(5), a(6));
  case 8:
    return ((T(*)(T,T,T,T,T,T,T,T)) ptr)
      (a(0), a(1), a(2), a(3), a(4), a(5), a(6), a(7));
  case 9:
    return ((T(*)(T,T,T,T,T,T,T,T,T)) ptr)
      (a(0), a(1), a(2), a(3), a(4), a(5), a(6), a(7), a(8));
  case 10:
    return ((T(*)(T,T,T,T,T,T,T,T,T,T)) ptr)
      (a(0), a(1), a(2), a(3), a(4), a(5), a(6), a(7), a(8), a(9));
#undef a
#undef T
  default:
    abort();
    return tort_nil;
  }
}

tort_v _tort_m_object___object_ptr(tort_tp tort_v obj)
{
  return tort_ptr_new(obj);
}

tort_v _tort_m_nil___object_ptr(tort_tp tort_v obj)
{
  return tort_ptr_new(0);
}

tort_v _tort_m_tagged___object_ptr(tort_tp tort_v obj)
{
  return tort_nil;
}

void *tort_ptr_data(tort_v v)
{
  void *ptr = 0;
  tort_send(tort__s(_ptr_data), v, &ptr);
  return ptr;
}

tort_v _tort_m_object__nullQ(tort_tp tort_v a)
{
  return a == tort_nil ? tort_true : tort_false;
}

tort_v _tort_m_ptr__nullQ(tort_tp tort_v a)
{
  return tort_P(a) ? tort_false : tort_true;
}

#define ROP(N,OP) tort_v _tort_m_ptr__##N(tort_tp tort_v a, tort_v b);
#define LOP(N,OP) ROP(N,OP)
#define LUP(N,OP) tort_v _tort_m_ptr__##N(tort_tp tort_v a);
#include "tort/ops.h"

#define ROP(N,OP)							\
  tort_v _tort_m_ptr__##N(tort_tp tort_v a, tort_v b)			\
  { return (tort_P(a) OP tort_ptr_data(b)) ? tort_true : tort_false; } 
#define LOP(N,OP) ROP(N,OP)
#define LUP(N,OP)						    \
  tort_v _tort_m_ptr__##N(tort_tp tort_v a)			    \
  { return (OP tort_P(a)) ? tort_true : tort_false; } 
#include "tort/ops.h"

tort_v _tort_m_ptr__ADD(tort_tp tort_v a, tort_v b)
{
  return tort_p(a + tort_I(b));
}

tort_v _tort_m_ptr__SUB(tort_tp tort_v a, tort_v b)
{
  if ( tort_h_mtable(a) == tort_h_mtable(b) )
    return tort_i(a - tort_P(b)); // FIXME: may overflow fixnum.
  else
    return tort_p(a - tort_I(b));
}

