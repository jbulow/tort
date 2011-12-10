(define <macro-environment> ('new_class <mtable> <vector>))
('add_method ('_mtable <macro-environment>) 'new 
  (lambda (mtable)
    (let ((instance (vector '<struct> #f #f #f ('new <map>))))
      ('_mtable= instance mtable)
      instance)))
('add_method <macro-environment> 'parent
  (lambda (self)
    (vector-ref self 3)))
('add_method <macro-environment> 'parent=
  (lambda (self v)
    (vector-set! self 3 v)))
('add_method <macro-environment> 'bindings
  (lambda (self)
    (vector-ref self 4)))
('add_method <macro-environment> 'lisp_write 
  (lambda (self port)
    ('_write port "#<macro-environment >")))
('add_method <macro-environment> 'set-transformer 
  (lambda (self symbol transformer)
    ('set ('bindings self) symbol transformer)
    (display "\n\n  ### set-macro ")(write symbol)(write transformer)(display "\n\n")
    ))
('add_method <macro-environment> 'get-transformer
  (lambda (self car-expr)
    (let ((x ('get ('bindings self) car-expr)))
      (if (null? x) 
	(if ('parent self)
	  ('get-transformer ('parent self) car-expr)
	  x)
	x))))
('add_method <macro-environment> 'define-transformer
  (lambda (self symbol transformer)
    (if ('parent self)
      ('define-transformer ('parent self) symbol transformer)
      ('set-transformer self symbol transformer))))
('add_method <macro-environment> 'apply-transformer
  (lambda (self transformer e)
    ;; (display "  apply-macro ")(write transformer)(display " to ")(write e)(newline)
    (set! e (cdr e))
    ;; (set! &trace 1)
    (set! e (transformer . e))
    ;; (display "  apply-macro => ")(write e)(newline)
    ;; (set! &trace 0)
    e))
('add_method <macro-environment> 'expand-expr
  (lambda (self e)
    ;; (display "    expand-expr ")(write e)(newline)
    (if (pair? e)
      (let ((head (car e)))
	(if (eq? 'quote head) 
	  e
	  (if (or (eq? 'set! head) (eq? 'lambda head))
	    (cons (car e) (cons (car (cdr e)) ('expand-args self (cdr (cdr e)))))
	    (if (eq? 'let head)
	      (cons (car e) (cons
			      (map (lambda (b) (cons (car b) ('expand-args self (cdr b))))
				(car (cdr e)))
			      ('expand-args self (cdr (cdr e)))))
	      (let ((transformer ('get-transformer self head)))
		;; (display "  macro for ")(display (car e))(display " = ")(write macro)(newline)
		(if (null? transformer)
		  ('expand-args self e)
		  ('apply-transformer self transformer e)))))))
      e)))
('add_method <macro-environment> 'expand-args
  (lambda (self e)
    (if (pair? e) 
      (let ()
	;; (display "      expand-args ")(write (car e))(newline)
	(cons 
	  ('expand-expr self (car e)) 
	  ('expand-args self (cdr e))))
      e)))

('add_method <macro-environment> 'expand
  (lambda (self e)
    (let ((e-last #f) (e-next e))
      (while (not (equal? e-next e-last))
	(set! e-last e-next)
	(set! e-next ('expand-expr self e-last))
	;; (display " e-last = ")(write e-last)(newline)	  
	;; (display " e-next = ")(write e-next)(newline)	  
	)
	;; (display " result = ")(write e-next)(newline)	  
      e-next)))

(define *top-level-macro-environment* ('new <macro-environment>))
(define (%define-macro name transformer)
  ('define-transformer *top-level-macro-environment* name transformer))

(%define-macro 'define-macro 
  (lambda (name . body)
    (if (pair? name)
      (list '%define-macro (list 'quote (car name)) (cons 'lambda (cons (cdr name) body)))
      (cons '%define-macro (cons (list 'quote name) body)))))
