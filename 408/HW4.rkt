#lang racket
(define (accumulate operator null list)
  (if (null? list)
      null
      (operator (car list)
                (accumulate operator null (cdr list)))))
;1
(display "1) a)")(newline)
;recursive function
(define (containsR? list object)
  (if (equal? (car list) object)
      #t
      (if (equal? (cdr list)  '() )
          #f
          (containsR? (cdr list) object))))

;test recursive contains
(display "Using containsR which is recursive contains")(newline)
(display "Testing (containsR? (list 1 2 3 4) 3), should return #t: ")
(containsR? (list 1 2 3 4) 3) ;Value: #t
(display "Testing (containsR? (list 1 2 7 4) 3), should return #f: ")
(containsR? (list 1 2 7 4) 3) ;Value: #f

;non recursive function
(define (containsN? list object)
  (accumulate (lambda (x y) (or x y))
              #f
              (map (lambda (x) (equal? object x)) list)))
;test nonrecursive contains
(display "Using containsN which is non-recursive contains")(newline)
(display "Testing (containsN? (list 1 2 3 4) 3), should return #t: ")
(containsN? (list 1 2 3 4) 3) ;Value: #t
(display "Testing (containsN? (list 1 2 7 4) 3), should return #f: ")
(containsN? (list 1 2 7 4) 3) ;Value: #f

(newline)(display "b)")(newline)
;recursive function
(define (removeR object lst)
  (if (containsN? lst object)
      (if (equal? object (car lst))
          (removeR object (cdr lst))
          (cons (car lst) (removeR object (cdr lst))))
      lst))

;testing recursive function
(display "Using removeR which is recursive Remove")(newline)
(display "Testing (removeR 2 (list 1 2)), should return (1): ")
(removeR 2 (list 1 2)) ;Value: (1)
(display "Testing (removeR 2 (list 1 2 3 2 1)), should return (1 3 1): ")
(removeR 2 (list 1 2 3 2 1)) ;Value: (1 3 1)
(display "Testing (removeR 2 (list 1 2 3 2 1 1)), should return (1 3 1 1): ")
(removeR 2 (list 1 2 3 2 1 1)) ;Value: (1 3 1 1)
(display "Testing the function you included in the assignment with removeR, should return #t: ")
(let ((lst (list 1 2 3)))
   (and (equal? (list 1 3) (removeR 2 lst))
        (equal? lst (removeR 4 lst))))

(newline)

;non-recursive function
(define (removeN object lst)
  (accumulate (lambda (item rest)
                (if (equal? object item)
                    rest
                    (cons item rest)))
              null
              lst))

;test nonrecursive remove
(display "Using removeN which is non-recursive Remove")(newline)
(display "Testing (removeR 2 (list 1 2)), should return (1): ")
(removeN 2 (list 1 2)) ;Value: (1)
(display "Testing (removeR 2 (list 1 2 3 2 1)), should return (1 3 1): ")
(removeN 2 (list 1 2 3 2 1)) ;Value: (1 3 1)
(display "Testing (removeR 2 (list 1 2 3 2 1 1)), should return (1 3 1 1): ")
(removeN 2 (list 1 2 3 2 1 1)) ;Value: (1 3 1 1)
(display "Testing (removeR 2 (list 1 2 3 2 1 2)), should return (1 3 1): ")
(removeN 2 (list 1 2 3 2 1 2)) ;Value: (1 3 1)
(display "Testing the function you included in the assignment with removeN, should return #t: ")
(let ((lst (list 1 2 3)))
   (and (equal? (list 1 3) (removeN 2 lst))
        (equal? lst (removeN 4 lst)))) ;Value: #t

;2
(newline)(newline)(newline)
(display "2)")(newline)
(define expr
   (list +
         1
         (list /
               2
               (list +
                     (list * 3 5)
                     1))
         (list - 0 4)))
(display "Displaying expr: ")expr

;a
(newline)(display "a) ")(newline)
(define (operator? object)
  (ormap (lambda (x) (equal? object x)) (list + - * /)))
(display "Testing (operator? +), should return #t: ")(operator? +)
(display "Testing (operator? -), should return #t: ")(operator? -)
(display "Testing (operator? *), should return #t: ")(operator? *)
(display "Testing (operator? /), should return #t: ")(operator? /)
(display "Testing (operator? 4), should return #f: ")(operator? 4)
(display "Testing (operator? (car expr)), should return #t: ")(operator? (car expr))
(display "Testing (number? (cadr expr)), should return #t: ")(number? (cadr expr))

;b
(newline)(display "b) ")(newline)
(define (null-val operator)
  (car (cdr (assoc operator (list (list + 0) (list - 0) (list * 1) (list / 1))))))
(display "Testing (null-val? +), should return 0: ")(null-val +)
(display "Testing (null-val? -), should return 0: ")(null-val -)
(display "Testing (null-val? *), should return 1: ")(null-val *)
(display "Testing (null-val? /), should return 1: ")(null-val /)

;c
(newline)(display "c) ")(newline)
(define (expression? object)
  (if (list? object)
      (if (operator? (car object))
          (andmap (lambda (x)
                 (if (expression? x)
                     #t
                     (number? x)))
               (cdr object))
          #f)
      #f))
(display "Testing (expression? expr), should return #t: ")(expression? expr)
(display "Testing (expression? (list 1 + 2)), should return #f: ")(expression? (list 1 + 2))
(display "Testing (expression? (list + 1)), should return #f: ")(expression? (list + 1))
;d
(newline)(display "d) ")(newline)
(define (count-operators expr)
  (accumulate + 0 (map (lambda (x)
         (if (expression? x)
             (count-operators x)
             (if (operator? x)
                 1
                 0)))
       expr)))

(define (count-primitive-operands expr)
  (accumulate + 0 (map (lambda (x)
         (if (expression? x)
             (count-primitive-operands x)
             (if (number? x)
                 1
                 0)))
         expr)))
(display "Testing (count-operators expr), should return 5: ")(count-operators expr)
(display "Testing (count-primitive-operands expr), should return 7: ")(count-primitive-operands expr)

;e
(newline)(display "e) ")(newline)
(define (evaluate expr)
  (apply (car expr) (map (lambda (x)
                           (if (expression? x)
                               (evaluate x)
                               x))
                               (cdr expr))))
(display "Testing (evaluate expr), should return -23/8: ")(evaluate expr) 

(newline)(display "Showing all test examples again")(newline)
(display "Testing (operator? (car expr)), should return #t: ")(operator? (car expr)) 
;Value: #t 
(display "Testing (number? (cadr expr)), should return #t: ")(number? (cadr expr)) 
;Value: #t
(display "Testing (expression? expr), should return #t: ")(expression? expr) 
;Value: #t 
(display "Testing (expression? (list 1 + 2)), should return #f: ")(expression? (list 1 + 2)) 
;Value: #f
(display "Testing (expression? (list + 1)), should return #f: ")(expression? (list + 1))
;Value: #f
(display "Testing (count-operators expr), should return 5: ")(count-operators expr) 
;Value: 5
(display "Testing (count-primitive-operands expr), should return 7: ")(count-primitive-operands expr) 
;Value: 7 
(display "Testing (evaluate expr), should return -23/8: ")(evaluate expr) 
;Value: -23/8
