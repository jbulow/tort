#include "tort/tort.h"
#include <stdarg.h>

static ssize_t the_answer = 42;
tort_v _tort_m_class__return_42(tort_tp tort_v rcvr)
{
  return tort_i(the_answer);
}

static tort_v selector_1;
static tort_v rcvr_1;
static tort_v arg_1;
tort_v _tort_m_class__call_other(tort_tp tort_v rcvr, tort_v sel)
{
  tort_send(selector_1, rcvr_1, arg_1);
  return_tort_send(sel, rcvr);
}

tort_v _tort_plain_c(void *arg0, tort_v arg1, tort_v arg2, tort_v arg3, tort_v arg4, tort_v arg5, tort_v arg6)
{
  extern void a7(void *arg0, tort_v arg1, tort_v arg2, tort_v arg3, tort_v arg4, tort_v arg5, tort_v arg6);
  extern void ip(long long arg0, void *arg1);
  extern void pp(void *arg0, void *arg1);
  a7(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
  ip(0, arg0);
  ip(1, arg1);
  ip(2, arg2);
  ip(3, arg3);
  ip(4, arg4);
  ip(6, arg6);
  pp((void*) 0, arg0);
  pp((void*) 1, arg1);
  pp((void*) 2, arg2);
  pp((void*) 3, arg3);
  pp((void*) 4, arg4);
  pp((void*) 5, arg5);
  pp((void*) 6, arg6);
  return arg0;
}

const char * _tort_if_stmt(tort_v x)
{
  if ( x != tort_false ) {
    printf("true %p\n", x);
  } else {
    printf("false %p\n", x);
  }
  return x;
}

const char * _tort_while_stmt(tort_pair *x)
{
  while ( x != tort_false ) {
    printf("true %p\n", x);
    x = x->second;
  }
  return (char*) x;
}

tort_v _tort_box_int(tort_vi i)
{
  return tort_i(i);
}

tort_vi _tort_unbox_int(tort_v o)
{
  return tort_I(o);
}

tort_v _tort_return_func_ptr()
{
  return tort_p(printf);
}

tort_v _tort_rest_arg(int n, va_list *vap)
{
  tort_v l = tort_nil, *lp = &l;
  extern tort_v tort_cons(tort_v, tort_v);
  while ( n -- > 0 ) {
    *lp = tort_cons(va_arg(*vap, tort_v), tort_nil);
    lp = ((tort_v*) lp) + 1; /* car + 0, cdr + 1 */
  }
  return l;
}

int _tort_argc;
tort_v _tort_vararg_1(tort_v a1, ...)
{
  va_list val;
  tort_v l;
  va_start(val, a1);
  l = _tort_rest_arg(_tort_argc - 1, &val);
  va_end(val);
  return l;
}

tort_v _tort_vararg_2(tort_v a1, tort_v a2, ...)
{
  va_list val;
  tort_v l;
  va_start(val, a2);
  l = _tort_rest_arg(_tort_argc - 2, &val);
  va_end(val);
  return l;
}

tort_v _tort_vararg_3(tort_v a1, tort_v a2, tort_v a3, ...)
{
  va_list val;
  tort_v l;
  va_start(val, a3);
  l = _tort_rest_arg(_tort_argc - 3, &val);
  va_end(val);
  return l;
}

/* 
x86 64: calling sequence:

http://en.wikipedia.org/wiki/X86_calling_conventions#Microsoft_x64_calling_convention

System V AMD64 ABI convention

The calling convention of the System V AMD64 application binary interface[9] is followed on Linux and other non-Microsoft operating systems. 
The registers RDI, RSI, RDX, RCX, R8 and R9 are used for integer and pointer arguments while XMM0, XMM1, XMM2, XMM3, XMM4, XMM5, XMM6 and XMM7 are used for floating point arguments.
For system calls, R10 is used instead of RCX.[9] As in the Microsoft x64 calling convention, additional arguments are pushed onto the stack and the return value is stored in RAX.


At Entry into callee:

(arg0, arg1, arg2, arg3, arg4, arg5, arg6)
 %rdi  %rsi  %rdx  %rcx  %r8   %r9   16(%rbp)

Callee saves %rbp:

	pushq	%rbp
	movq	%rsp, %rbp

???? prbp arg6
0    8    16
^
|
rsp
rbp

Callee saves registers:

	movq	%rbx, -40(%rbp)
	movq	%r12, -32(%rbp)
	movq	%r13, -24(%rbp)
	movq	%r14, -16(%rbp)
	movq	%r15, -8(%rbp)
	subq	$80, %rsp // extra space for %r9 temp and additional arg?

Callee saves arguments on stack:
	movq    %r9,  -56(%rbp)

????  or9   ???? orbx or12 or13 or14 or15 orbp
-64  -56    -48  -40  -32  -24  -16  -8   0
^                                         ^
|                                         |
%rsp                                      %rbp

... DO STUFF...

Callee restores registers:

	movq	-40(%rbp), %rbx
	movq	-32(%rbp), %r12
	movq	-24(%rbp), %r13
	movq	-16(%rbp), %r14
	movq	-8(%rbp), %r15

Callee restores %rbp and %rsp:

	leave

Returns result in %rax:

	ret
 
*/

