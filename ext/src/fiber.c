#include "tort/core.h"
#include "tort/fiber.h"
#include <assert.h>

tort_v _tort_m_message__fiber(tort_thread_param tort_message *msg)
{
  return msg->fiber;
}

tort_v _tort_m_message__set_fiber(tort_thread_param tort_message *msg, tort_v fiber)
{
  return msg->fiber = fiber;
}

struct tort_fiber_data
{
  tort_message *message;
  tort_v block;
};

static
tort_fiber_func_DECL(fiber_func)
{
  tort_v _tort_fiber = (tort_v) _tort_fiber_ptr;
  struct tort_fiber_data *d = data;
  tort_message *_tort_message = d->message;
  assert(_tort_message);
  _tort_message->fiber = _tort_fiber;
  return (tort_v) tort_send(tort__s(value), d->block);
}

tort_v _tort_M_fiber__new(tort_thread_param tort_v rcvr, tort_v block)
{
  struct tort_fiber_data d = {
    _tort_message,
    block,
  };
  assert(_tort_message);
  tort_v _tort_fiber = _tort_message->fiber;
  return __tort_fiber_new((tort_fiber_t*) _tort_fiber, fiber_func, &d, 0);  
}

tort_v _tort_m_fiber__yield (tort_thread_param tort_v rcvr)
{
  tort_v _tort_fiber = _tort_message->fiber;
  assert(_tort_fiber);
  return (tort_v) __tort_fiber_yield(_tort_fiber, tort_ref(tort_fiber_t, rcvr));
}

static void *allocate(size_t size)
{
  return tort_allocate(tort_mt(fiber), size);
}

tort_v tort_runtime_initialize_fiber()
{
  tort_v _mt_fiber = tort_mtable_make("fiber", 0);

  __tort_fiber_allocate = allocate;

  return _mt_fiber;
}

