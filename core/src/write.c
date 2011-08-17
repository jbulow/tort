#include "tort/core.h"

#define IO (io ? io : tort_stdout)
#define printf(fmt, args...) tort_printf(IO, fmt, ##args)

tort_v _tort_m_object___inspect(tort_thread_param tort_v rcvr, tort_v io)
{
  const char *str = tort_object_name_(rcvr);
  if ( str ) {
    printf("%s", str);
  } else {
    printf("@object @%p", (void *) rcvr);
  }
  return tort_nil;
}

tort_v _tort_m_tagged___inspect(tort_thread_param tort_v rcvr, tort_v io)
{
  if ( sizeof(tort_v) == sizeof(long long) ) {
    printf("%lld", (long long) tort_tagged_data(rcvr));
  } else {
    printf("%ld", (long) tort_tagged_data(rcvr));
  }
  return tort_nil;
}

tort_v _tort_m_ptr___inspect(tort_tp tort_v rcvr, tort_v io)
{
  printf("@%p", tort_P(rcvr));
  return tort_nil;
}

tort_v _tort_m_string___inspect(tort_thread_param tort_v rcvr, tort_v io)
{
  printf("\"%s\"", (char *) tort_string_data(rcvr));
  return tort_nil;
}

tort_v _tort_m_vector___inspect(tort_thread_param tort_v rcvr, tort_v io)
{
  printf("@vector( ");
  tort_vector_loop(rcvr, obj) {
    if ( obj_i > 0 ) printf(", ");
    tort_inspect(IO, obj);
  } tort_vector_loop_end(rcvr);
  printf(" )");
  return tort_nil;
}

tort_v _tort_m_symbol___inspect(tort_tp tort_symbol *rcvr, tort_v io)
{
  if ( rcvr->name != tort_nil ) {
    printf("%s", (char *) tort_symbol_data(rcvr));
  } else {
    printf("@symbol(@%p)", (void*) rcvr);
  }
  return tort_nil;
}

tort_v _tort_m_nil___inspect(tort_thread_param tort_v rcvr, tort_v io)
{
  printf("nil");
  return tort_nil;
}

tort_v _tort_m_boolean___inspect(tort_thread_param tort_v rcvr, tort_v io)
{
  printf(rcvr == tort_false ? "false" : "true");
  return tort_nil;
}

tort_v _tort_m_method___inspect(tort_tp tort_method *meth, tort_v io)
{
  tort_v meth_name = meth->name;
  const char *meth_cstr = meth_name ? tort_symbol_data(meth_name) : "#<unknown>";
  printf("@method(%s,@%p)", meth_cstr, (void *) meth->applyf);
  return tort_nil;
}

tort_v _tort_m_message___inspect(tort_tp tort_message *msg, tort_v io)
{
  printf("@message( ");
  tort_inspect(IO, msg->selector);
  printf(", ");
  tort_inspect(IO, msg->receiver);
  printf(", ");
  tort_inspect(IO, msg->method);
  printf(", ");
  tort_inspect(IO, msg->mtable);
  printf(")"); 
  return tort_nil;
}

tort_v _tort_m_pair___inspect(tort_thread_param tort_pair *rcvr, tort_v io)
{
  printf("@pair(%T, %T)", rcvr->first, rcvr->second);
  return tort_nil;
}

tort_v _tort_m_map___inspect(tort_thread_param tort_v rcvr, tort_v io)
{
  size_t entry_i = 0;
  printf("@map( \n  ");
  tort_map_EACH(rcvr, entry) {
    if ( entry_i > 0 ) printf(",\n  ");
    tort_inspect(IO, entry->first);
    printf(" => ");
    tort_inspect(IO, entry->second);
    entry_i ++;
  } tort_map_EACH_END();
  printf("  )");
  return tort_nil;
}

#undef printf
#undef IO

tort_v tort_runtime_initialize_write()
{
  return tort__s(write);
}
