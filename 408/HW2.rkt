#lang racket
(display "1. ")(newline)
(define (reverse-digits n)
  (define (reverse in out digitsMoved)
    (if (= in 0)
        out
        (reverse (floor (/ in 10)) (+ (* out 10) (modulo in 10))  (+ digitsMoved 1))
        )
    )
  (reverse n 0 0))
(reverse-digits 456)
(reverse-digits 123456789123456)
(define (same-digits? a b)
  (4))