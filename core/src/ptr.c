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

tort_v _tort_m_ptr___ptr_object(tort_tp tort_v p, void **pptr)
{
  return tort_P(p); /* UNSAFE! */
}

tort_v _tort_m_ptr___object_ptr(tort_tp tort_v obj)
{
  return tort_p(obj);
}

tort_v _tort_m_ptr___to_string(tort_tp tort_v p)
{
  char buf[64];
  snprintf(buf, sizeof(buf) - 1, "%016llx", (unsigned long long) (ssize_t) tort_P(p));
  return tort_string_new(buf, strlen(buf));
}


void *tort_ptr_data(tort_v v)
{
  void *ptr = 0;
  tort_send(tort__s(_ptr_data), v, &ptr);
  return ptr;
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
