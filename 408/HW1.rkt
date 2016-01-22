#lang racket
;1
(display "1. ")(newline)
(define (kilometres miles)
  (* 1.609 miles))
(define (miles km)
  (* .6215 km))
(display "Testing 1 miles to kilometers: ")(kilometres 1)
(display "Testing 5 miles to kilometers: ")(kilometres 5)
(display "Testing 1 kilometers to miles: ")(miles 1)
(display "Testing 5 kilometers to miles: ")(miles 5)

;2
(display "2. ")(newline)
(display "a. 4")(newline)
(display "b. 28")(newline)
(display "c. 9")(newline)

;3
(display "3. ")(newline)
(define (baz n)
  (define (bar a b)
    (define (foo a)
      (* a (+ a 2)))
    (if (= a 14)
        b
        (bar (+ a 1) (+ (foo a) b))))
  (bar 3 n))
(display "Testing baz 3: ")(baz 3)

;4
(display "4. ")(newline)
(define(sum-range from to [sum 0])
  (if (= from (+ to 1))
      sum
      (if (> from to)
          (sum-range to from sum)
          (sum-range (+ from 1) to (+ sum from)))))
(display "Testing sum-range 4 18: ")
(sum-range 4 18)
(display "Testing sum-range 18 4: ")
(sum-range 18 4)
(display "Testing sum-range 7 7 (should be 7 because it is inclusive): ")
(sum-range 7 7)
(display "Testing sum-range 5 10 (5 + 6 + 7 + 8 + 9 + 10): ")
(sum-range 5 10)