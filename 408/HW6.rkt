#lang plai

(define (convert x)
  (cdr (case x
    [(+) (cons x +)]
    [(-) (cons x -)]
    [(*) (cons x *)]
    [(/) (cons x /)]
    )))

(define (parse sexp)
  (cond
    [(number? sexp) (num sexp)]
    [(symbol? sexp) (id sexp)]
    [(list? sexp)
     (case (first sexp)
; modify by parsing the following into a binop
       [(+ - * /) (binop (convert (first sexp)) (parse (second sexp)) (parse (third sexp)))]
; modify by parsing the following into an app with multiple params
       [ (with) (app (fun
                      (map (lambda (x) (first x)) (second sexp))
                      (parse (third sexp)))
                     (map (lambda (x) (parse (second x))) (second sexp)))]
; modify by parsing the following to handle multiple params
       [(fun) (fun
               (second sexp)
               (parse (third sexp))
               )
                   ]
       [else
        (cond ((list? (first sexp))
; modify by parsing the following to handle multiple params
               (app (parse (first sexp))
                    (map (lambda (x) (parse x)) (cdr sexp)))))
        ]
       )]))

(define-type FAE
  [ num (n number?)]
  [ binop (op procedure?) (lhs FAE?) (rhs FAE?)]
  [ id (name symbol?)]
  [ fun (args (listof symbol?)) (body FAE?)]
  [ app (fun-expr FAE?) (args (listof FAE?))])

(define-type FAE-Value
  [ numV (n number?)]
  [ closureV (params (listof symbol?))
             (body FAE?)
             (ds DefrdSub?)])

(define-type DefrdSub
  [ mtSub ]
  [ aSub (name symbol?) (value FAE-Value?) (ds DefrdSub?)])

;; lookup : symbol DefrdSub â†’ FAE-Value
(define (lookup name ds)
  (type-case DefrdSub ds
    [ mtSub () (error 'lookup "no binding for identifier" )]
    [ aSub (bound-name bound-value rest-ds)
           (if (symbol=? bound-name name)
               bound-value
               (lookup name rest-ds))]))

(define (links bound-ids bound-body ds)
  (if (null? bound-ids)
      ds
      ( closureV (car bound-ids) bound-body (links (cdr bound-ids) bound-body ds))))

(define (appMulti params args ds)
  (if (null? params)
      ds
      (aSub (car params) (interp (car args) ds) (appMulti (cdr params) (cdr args) ds))))

(define (build-sublist params args ds)
  (if (null? params)
      ds
      (aSub (car params) (interp (car args)) (build-sublist params args ds))))

;; interp : FAE DefrdSub â†’ FAE-Value
(define (interp expr ds)
  (type-case FAE expr
    [ num (n) ( numV n)]
    [ binop (b l r) ( numV (b (numV-n (interp l ds)) (numV-n (interp r ds))))]
    [ id (v) (lookup v ds)]
    [ fun (bound-id bound-body)
          ( closureV bound-id bound-body ds)]
    [ app (fun-expr args)
          (local ([define fun-val (interp fun-expr ds)])
            (interp (closureV-body fun-val)
                    (appMulti (closureV-params fun-val) args (closureV-ds fun-val))))]))


(display "Testing (parse '{{fun {x} {+ x x}} 5})")(newline)
(parse '{{fun {x} {+ x x}} 5})
(display "Testing (parse '{{fun {x y} {+ x y}} 5 4})")(newline)
(parse '{{fun {x y} {+ x y}} 5 4})
(display "Testing (parse '{{fun {x y z} {+ x {+ y z}}} 5 4 18})")(newline)
(parse '{{fun {x y z} {+ x {+ y z}}} 5 4 18})
(display "Testing (parse '{{fun {x y z} {+ x y z}} 5 4 18})")(newline)
(parse '{{fun {x y z} {+ x y z}} 5 4 18})
(display "Testing (parse '{fun {x y z} {+ x y z}})")(newline)
(parse '{fun {x y z} {+ x y z}})
(display "Testing (interp (parse '{{fun {x} {+ x x}} 5}) (mtSub) )")(newline)
(interp (parse '{{fun {x} {+ x x}} 5}) (mtSub) )
(display "Testing (interp (parse '{{fun {x y} {+ x y}} 5 3}) (mtSub) )")(newline)
(interp (parse '{{fun {x y} {+ x y}} 5 3}) (mtSub) )
(display "Testing (interp (parse '{{fun {x y z} {+ x {+ y z}}} 5 4 18}) (mtSub) )")(newline)
(interp (parse '{{fun {x y z} {+ x {+ y z}}} 5 4 18}) (mtSub) )
(display "Testing (interp (parse '{{fun {x} {- x 4}} 5}) (mtSub) )")(newline)
(interp (parse '{{fun {x} {- x 4}} 5}) (mtSub) )
(display "Testing (interp (parse '{{fun {x} {- x x}} 5}) (mtSub) )")(newline)
(interp (parse '{{fun {x} {- x x}} 5}) (mtSub) )
(display "Testing (interp (parse '{{fun {x} {* x x}} 5}) (mtSub) )")(newline)
(interp (parse '{{fun {x} {* x x}} 5}) (mtSub) )
(display "Testing (interp (parse '{{fun {x} {/ x x}} 5}) (mtSub) )")(newline)
(interp (parse '{{fun {x} {/ x x}} 5}) (mtSub) )
(display "Testing (interp (parse '{with {{x 10} {y 20}} {+ x y}}) (mtSub) )")(newline)
(interp (parse '{with {{x 10} {y 20}} {+ x y}}) (mtSub) )
(display "Testing (interp (parse '{with {{x 2} {y 3}} {with {{z {+ x y}}} {+ x z}}}) (mtSub) )")(newline)
(interp (parse '{with {{x 2} {y 3}} {with {{z {+ x y}}} {+ x z}}}) (mtSub) )