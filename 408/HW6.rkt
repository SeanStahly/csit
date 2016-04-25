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
;       [(with) (with (first (second sexp))
;                     (parse (second (second sexp)))
;                     (parse (third sexp)))
;               ]
; modify by parsing the following to handle multiple params
       [(fun) (fun
               ;(map (lambda (x) (x)) (second sexp))
               ;(first (second sexp))
               (second sexp)
               ;(map (lambda (x) (parse x)) (third sexp))
               (parse (third sexp))
               )
              ;(display sexp)
                   ]
       [else
        (cond ((list? (first sexp))
; modify by parsing the following to handle multiple params
               ;(app (parse (first sexp)) (parse (second sexp)))))
               (app (parse (first sexp))
                    (map (lambda (x) (parse x)) (cdr sexp)))))
                    ;(list (parse (second sexp))))))
        ]
       )]))

(define-type FAE
  [ num (n number?)]
  [ binop (op procedure?) (lhs FAE?) (rhs FAE?)]
  [ id (name symbol?)]
  [ fun (args (listof symbol?)) (body FAE?)]
  ;[ fun (param symbol?) (body FAE?)]
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
  
;(define (appMulti fun-expr arg-expr ds)
;  (local ([define fun-val (interp fun-expr ds)])
;    (if (null? arg-expr)
;        (closureV-ds fun-val)
;        (interp (closureV-body fun-val)
;                ( aSub (closureV-param fun-val)
;                       (interp (car arg-expr) ds)
;                       (appMulti fun-expr (cdr arg-expr) ds))))))

;; interp : FAE DefrdSub â†’ FAE-Value
(define (interp expr ds)
  (type-case FAE expr
    [ num (n) ( numV n)]
    [ binop (b l r) ( numV (b (numV-n (interp l ds)) (numV-n (interp r ds))))]
    [ id (v) (lookup v ds)]
    [ fun (bound-id bound-body)
          ( closureV bound-id bound-body ds)]
;    [ fun (bound-ids bound-body)
;          (links bound-ids bound-body ds)]
;    [ app (fun-expr arg-expr)
;        (appMulti fun-expr arg-expr ds)]))
    [ app (fun-expr args)
          (local ([define fun-val (interp fun-expr ds)])
            (interp (closureV-body fun-val)
                    (appMulti (closureV-params fun-val) args (closureV-ds fun-val))))]))
;                    ( aSub (closureV-param fun-val)
;                           (interp args ds)
;                           (closureV-ds fun-val))))]))

;    [ app (fun-expr arg-expr)
;          (local ([define fun-val (interp fun-expr ds)])
;            (interp (closureV-body fun-val)
;                  ( aSub (closureV-param fun-val)
;                         (appMulti arg-expr ds)
;                         (closureV-ds fun-val))))]))
;    [ app (fun-expr arg-expr)
;          (local ([define fun-val (interp fun-expr ds)])
;            (interp (closureV-body fun-val)
;                    ( aSub (closureV-param fun-val)
;                           (interp arg-expr ds)
;                           (closureV-ds fun-val))))]))


(parse '{{fun {x} {+ x x}} 5})
(parse '{{fun {x y} {+ x y}} 5 4})

(parse '{{fun {x y z} {+ x y z}} 5 4 18})
(parse '{fun {x y z} {+ x y z}})
(interp (parse '{{fun {x} {+ x x}} 5}) (mtSub) )
(interp (parse '{{fun {x y} {+ x y}} 5 3}) (mtSub) )
(display "Blarg should be 27")(interp (parse '{{fun {x y z} {+ x y z}} 5 4 18}) (mtSub) )
(interp (parse '{{fun {x} {- x 4}} 5}) (mtSub) )
(interp (parse '{{fun {x} {- x x}} 5}) (mtSub) )
(interp (parse '{{fun {x} {* x x}} 5}) (mtSub) )
(interp (parse '{{fun {x} {/ x x}} 5}) (mtSub) )
;(display "Testing multi-argument")(interp (parse '{{fun {x y} {+ x y}} 5 3}) (mtSub) )

