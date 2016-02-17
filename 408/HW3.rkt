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