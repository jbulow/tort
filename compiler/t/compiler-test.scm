(load "compiler/lib/compiler.scm")

(let
  ((t 
     (lambda (expr expect-expr)
       (let ((result expr)
	      (expect #f)
	      (func #f))
	 (display "\n===================================================================\n");
	 (set! func (compile result #f))
	 (set! result ('_ccallv func '#(0 1 2 3 4 5)))
	 (display "expr     = ")(write expr)(newline)
	 (display "result   = ")(write result)(newline)
	 (cond
	   ((pair? expect-expr)
	     (set! expect (car expect-expr))))
	 (if expect-expr
	   (begin
	     (display "expect   = ")(write expect)(newline)))
	 (if (and expect-expr (not (equal? result expect)))
	   (error "result != expect"))
	 )
       #f)))
  (define (void x))
  (void ('load <dynlib> "/usr/lib/libc")) ;; printf
  (t '1 '(1))
  (t '(quote (a b))  '((a b)))
  (t '(begin)        `(,(if #f #f)))
  (t '(begin 1)      '(1))
  (t '(begin 1 'y)   '(y))
  (t '(begin 1 2 3)  '(3))
  (t '(eq? 1 2)      '(#f))
  (t '(eq? 1 1)      '(#t))
  (t '(if 1 2)       '(2))
  (t '(if #f #f)     `(,(if #f #f)))
  (t '(if #f 2 3)    '(3))
  (t '(or)           '(#f))
  (t '(or 1)         '(1))
  (t '(or #f)        '(#f))
  (t '(or 1 2)       '(1))
  (t '(or #f 2)      '(2))
  (t '(and)          '(#t))
  (t '(and 1)        '(1))
  (t '(and #f)       '(#f))
  (t '(and 1 #f)     '(#f))
  (t '(and 1 2)      '(2))
  (t '(let ((a 1) (b 2)) 3 a)
    '(1))
  (t '(let ((a (&p (&stack-alloc 15))) (b 2)) a b)
    '(2))
  (t '(case 'a ((a 1) '1) (else 2))
    '(1))
  (t '(lambda (a b) 1 a)
    #f)
  (t '(&i 1) '(5))
  (t '(&I 5) '(1))
  (t '(&i ((&extern tort_prints) (&P "Hello, World!\n")))
    '(42))
  
  ;; Inline assembly.
  (t '(&i (&&+ (&I 2) (&I 3)))
    '(5))
  (t '(&i (&&* (&I 2) (&I 3)))
    '(6))
  (t '(&i (&&- (&I 2) (&I 3)))
    '(-1))
  (t '(&i (&&/ (&I -6) (&I 3)))
    '(-2))
  (t '(&r %rdi)
    '(0))
  (t '(&r %rsi)
    '(1))

  ;; Message send.
  (t '(&send '+ 1 2)
    '(3))
  #|
  (t '(&i ((&extern printf) (&P "Hello, World!\n")))
  '14)
  |#
  (t '(let ((foo (&c-func #f (a b)
		   ((&extern tort_prints) (&P "in foo (&f-func)\n"))
		   b)))
	((&extern tort_prints) (&P "in (let ((foo ...\n"))
	((&P foo) 1 2))
    '(2))
  (t '(let ((a 1)) (lambda (x) (+ a x)))
    #f)
  ;; rewrite-2
  (t '((lambda (p1 p2) b) a1 a2)
    #f)
  (t '('+ 1 2)
    '(3))
  (t '(&c-func myfunc (a b c) (+ a c))
    #f)
  )
