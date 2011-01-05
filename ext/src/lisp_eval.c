#include "tort/lisp.h"

/********************************************************************/

tort_v _tort_m_symbol__lisp_eval(tort_tp tort_v sym, tort_v env)
{
  return tort_send(tort__s(get), env, sym);
}

tort_v _tort_m_object__lisp_eval(tort_tp tort_v obj, tort_v env)
{
  return obj;
}

tort_v _tort_m_pair__lisp_eval(tort_tp tort_pair *obj, tort_v env)
{
  tort_v val;
  if ( obj->car == tort_s(quote) ) {
    return tort_send(tort_s(car), obj->cdr);
  }
  else if ( obj->car == tort_s(if) ) {
    val = tort_send(tort_s(lisp_eval), tort_car(obj->cdr), env);
    if ( val == tort_false ) {
      return tort_caddr(obj->cdr);
    } else {
      return tort_cadr(obj->cdr);
    }
  }
  else {
    val = tort_send(tort_s(lisp_eval_car), obj->car, env);
    tort_v args = tort_send(tort_s(lisp_eval_args), obj->cdr, env);
    return tort_send(tort_s(lisp_apply), val, args, env);
  }

  return obj;
}

tort_v _tort_m_object__lisp_eval_car(tort_tp tort_v obj, tort_v env)
{
  return obj;
}

tort_v _tort_m_symbol__lisp_apply(tort_tp tort_v obj, tort_pair *args, tort_v env)
{
  return tort_send(obj, args->car);
}

tort_v _tort_m_pair__lisp_eval_args(tort_tp tort_pair *obj, tort_v env)
{
  return tort_cons(tort_send(tort_s(lisp_eval), obj->car, env),
		   tort_send(tort_s(lisp_eval_args), obj->cdr, env));
    
}


tort_v _tort_m_nil__lisp_eval_args(tort_tp tort_pair *obj, tort_v env)
{
  return obj;
}


tort_v _tort_m_io__lisp_repl(tort_tp tort_v io, tort_v out, tort_v globals)
{
  tort_v expr, result = tort_nil;
  tort_v env = tort_send(tort_s(new), tort_mt(dmap), globals, tort_nil);
  do {
    tort_printf(out, " >  ");
    expr = tort_send(tort_s(lisp_read), io);
    if ( expr == tort_eos ) break;
    tort_printf(out, " == ");
    tort_send(tort_s(lisp_write), expr, out);
    tort_printf(out, "\n");
    result  = tort_send(tort_s(lisp_eval), expr, env);
    tort_printf(out, " => ");
    tort_send(tort_s(lisp_write), result, out);
    tort_printf(out, "\n");
  } while ( 1 );
  return result;
}


tort_v tort_runtime_initialize_lisp_eval()
{
  return 0;
}
