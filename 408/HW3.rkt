#lang racket
;1
;a
(define (compare p1 p2 n)
  (if (= (p1 n) (p2 n))
     #t
     #f))

;b
(define (make-comparator p1 p2)
  (define (new-comparator n)
    (compare p1 p2 n))
  new-comparator)

;c
(define (test comparator from to)
  (if (comparator from)
      (if (= from to)
          #t
          (test comparator (+ from 1) to))
      #f))

;d
(define (make-test from to)
  (define (generate-test comp)
    (test comp from to))
  generate-test)

(define (square x)
  (* x x))

(define (cube x)
  (* x x x))

(compare square cube 2) 
;Value: #f
(compare square cube 1) 
;Value #t 
(define compare-sc 
  (make-comparator square cube))
(compare-sc 1)
;Value: #t
(test compare-sc 1 3) ;; tests compare-sc with 1, 2 and 3
;Value: #f
(define test-1-3
  (make-test 1 3)) ;; a test with 1, 2 and 3 as test values
(test-1-3 compare-sc)
;Value: #f

;2
;a
(define (complement proc)
  (define (new-proc n)
    (if (proc n)
      #f
      #t))
  new-proc)
(define (some-proc n)
  (if (= n 1)
      #t
      #f))
(some-proc 1) 
;Value: #t 
((complement some-proc) 1) 
;Value: #f

(define (odd? n)
  ((complement even?) n))

;b
(define x 5)

(define expression1 
  (lambda (a b c) (+ (* a (square x)) (* b x) c)))
(expression1 1 2 3)
;(define expression2)
(let ((a 1) (b 2) (c 3))
  (+ (* a (square x)) (* b x) c))

;c
;let* required to set multiple lets sequentially
(let* ((x 4)
      (y (+ x 1)))
  (+ x y))

;d
;24
(display "Original")(newline)
(let ((+ -) 
      (- +) 
      (* /) 
      (/ *)) 
  (* (/ (- (+ -6) (- 3 2 5)) 3) 2))
(display "New let*")(newline)
(let* ((a +)
      (+ -) 
      (- a)
      (b *)
      (* /) 
      (/ b)) 
  (* (/ (- (+ -6) (- 3 2 5)) 3) 2))

;e
(define (iffy test consequent alternative)
  (cond ((eq? test #t) consequent)
        ((eq? test #f) alternative)))

(define (compareN p1 p2 n)
  (iffy (= (p1 n) (p2 n))
     #t
     #f))
(compareN square cube 2) 
;Value: #f
(compareN square cube 1) 
;Value #t 
(define compare-scN
  (make-comparator square cube))
(compare-scN 1)
;Value: #t
(test compare-scN 1 3) ;; tests compare-sc with 1, 2 and 3
;Value: #f
(define test-1-3N
  (make-test 1 3)) ;; a test with 1, 2 and 3 as test values
(test-1-3N compare-scN)