(let* ( 
	(arg-regs     '#(%rdi %rsi %rdx %rcx %r8 %r9))
	(rtn          '(&r %rax))
	(arg0         rtn)
	(arg1         `(&r ,(vector-ref arg-regs 1)))
	(arg2         `(&r ,(vector-ref arg-regs 2)))
	(macros    ('new <map>))
	(word-size  (send 'get &root 'word_size))
	(object-header-size (send 'get &root 'object_header_size))
	(<message>-alloc-size (+ object-header-size (send 'instance_size <message>)))
	(<message>-slots (send 'slots <message>))
	(<message>->selector (send 'offset (send 'get <message>-slots 'selector)))
	(<message>->receiver (send 'offset (send 'get <message>-slots 'receiver)))
	(<message>->previous_message  (send 'offset (send 'get <message>-slots 'previous_message)))
	(<message>->method   (send 'offset (send 'get <message>-slots 'method)))
	(<message>->argc     (send 'offset (send 'get <message>-slots 'argc)))
	(<method>->applyf    (- word-size))
	(tag-bits (send 'get &root 'tag_bits))
	(&I (lambda (x) (>> x tag-bits)))
       )
 
  (define-macro (&send sel rcvr . args)
    (let ((msg (make-symbol #f)))
      `(let ((,msg (&stack-alloc ,<message>-alloc-size)))
	 (set! ,msg (&&+ ,msg ,(&I object-header-size)))
	 (set! (&o ,<message>->selector ,msg) ,sel)
	 (set! (&o ,<message>->receiver ,msg) ,rcvr)
	 (set! (&o ,<message>->previous_message ,msg) &msg)
	 (set! (&o ,<message>->argc ,msg) ,(+ (list-length args) 1)) 
	 (set! ,msg (&c (&extern tort_lookup) &msg ,msg))
	 (&c (&o ,<method>->applyf (&o ,<message>->method ,msg)) ,@args)
	 )))
)
