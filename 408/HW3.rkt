#lang racket
;1
(display "1. ")
;a
(display "a)")(newline)
(define (compare p1 p2 n)
  (if (= (p1 n) (p2 n))
     #t
     #f))

(define (square x)
  (* x x))

(define (cube x)
  (* x x x))

(display "Testing (compare square cube 2) should be false: ")
(compare square cube 2) 
(display "Testing (compare square cube 1) should be true: ")
(compare square cube 1) 

;b
(display "b)")(newline)
(define (make-comparator p1 p2)
  (define (new-comparator n)
    (compare p1 p2 n))
  new-comparator)
(display "Testing (compare -sc) should be true: ")
(define compare-sc 
  (make-comparator square cube))
(compare-sc 1)

;c
(display "c)")(newline)
(define (test comparator from to)
  (if (comparator from)
      (if (= from to)
          #t
          (test comparator (+ from 1) to))
      #f))
(display "Testing (test compare-sc 1 3) should be false: ")
(test compare-sc 1 3) ;; tests compare-sc with 1, 2 and 3

;d
(display "d)")(newline)
(define (make-test from to)
  (define (generate-test comp)
    (test comp from to))
  generate-test)
(define test-1-3
  (make-test 1 3)) ;; a test with 1, 2 and 3 as test values
(display "Testing (test-1-3 compare sc) should be false: ")
(test-1-3 compare-sc)

;2
;a
(display "2. a)")(newline)
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
(display "Testing (some-proc 1) should be true: ")
(some-proc 1) 
(display "Testing ((complement some-proc) 1) should be false: ")
((complement some-proc) 1) 
(display "Defined odd? as (complement even?). No output.")
(define (odd? n)
  ((complement even?) n))
(display "Testing (even? 5) should be false: ")
(even? 5)
(display "Testing (odd? 5) should be true: ")
(odd? 5)

;b
(display "b)")(newline)
(define x 5)
(define expression1 
  (lambda (a b c) (+ (* a (square x)) (* b x) c)))
(display "Testing lambda function, output should be 38: ")
(expression1 1 2 3)
(display "Testing let function, output should be 38: ")
(let ((a 1) (b 2) (c 3))
  (+ (* a (square x)) (* b x) c))

;c
(display "c)")(newline)
;let* required to set multiple lets sequentially
(display "Testing original function with the bug, returns 10 due to x already being defined as 5 from 2b: ")
(let ((x 4) 
      (y (+ x 1))) 
  (+ x y))
(display "Updated function to a let*, inorder to generate the terms sequentially instead of simutaneously. Should output 9: ") 
(let* ((x 4)
      (y (+ x 1)))
  (+ x y))

;d
(display "d)")(newline)
(display "Testing original function, should output 24: ")
(let ((+ -) 
      (- +) 
      (* /) 
      (/ *)) 
  (* (/ (- (+ -6) (- 3 2 5)) 3) 2))
(display "Testing new let*, should output 24: ")
(let* ((a +)
      (+ -) 
      (- a)
      (b *)
      (* /) 
      (/ b)) 
  (* (/ (- (+ -6) (- 3 2 5)) 3) 2))

;e
(display "e)")(newline)
(define (iffy test consequent alternative)
  (cond ((eq? test #t) consequent)
        ((eq? test #f) alternative)))
(display "Created iffy, testing problem 1 recreated using iffy. ")(newline)

(define (compareN p1 p2 n)
  (iffy (= (p1 n) (p2 n))
     #t
     #f))
(display "Should be false: ")
(compareN square cube 2) 
(display "Should be true: ")
(compareN square cube 1) 
(define compare-scN
  (make-comparator square cube))
(display "Should be true: ")
(compare-scN 1)
(display "Should be false: ")
(test compare-scN 1 3) ;; tests compare-sc with 1, 2 and 3
(define test-1-3N
  (make-test 1 3)) ;; a test with 1, 2 and 3 as test values
(display "Should be false: ")
(test-1-3N compare-scN)
(display "This seems to be an acceptable replacement for the special form if.")