#lang racket
(display "1. ")(newline)
(define (reverse-digits n)
  (define (reverse in out )
    (if (= in 0)
        out
        (reverse (floor (/ in 10)) (+ (* out 10) (modulo in 10)))
        )
    )
  (reverse n 0))
(display "Testing reverse-digits 456 ")(reverse-digits 456)
(display "Testing reverse-digits 123456789123456 ")(reverse-digits 123456789123456)
(display "Testing reverse-digits 397164 ")(reverse-digits 397164)

(define (same-digits? a b)
  (define (adjust in out)
    (if (= in 0)
        out
        (adjust (floor (/ in 10))(+ out (* 1 (expt 10 (modulo in 10)))))))
  (if (= (adjust a 0) (adjust b 0))
         #t
         #f))
(display "Testing same-digits 445, 544 ")(same-digits? 445 544)
(display "Testing same-digits 133042, 420313 ")(same-digits? 133042 420313)
(display "Testing same-digits 133043, 42013 ")(same-digits? 133042 42013)

(display "2.")(newline)