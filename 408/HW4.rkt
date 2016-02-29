#lang racket
;1
(display "1) a)")(newline)
(define (containsR? list object)
  (if (equal? (car list) object)
      #t
      (if (equal? (cdr list)  '() )
          #f
          (containsR? (cdr list) object))))
(display "Testing (containsR? (list 1 2 3 4) 3), should return #t: ")
(containsR? (list 1 2 3 4) 3) ;Value: #t
(display "Testing (containsR? (list 1 2 7 4) 3), should return #f: ")
(containsR? (list 1 2 7 4) 3) ;Value: #f

(define (containsN? list object)
  (accumulate (lambda (x y) ...)
              (map (lambda (x) ...) ...)))
(display "Testing (containsN? (list 1 2 3 4) 3), should return #t: ")
(containsN? (list 1 2 3 4) 3) ;Value: #t
(display "Testing (containsN? (list 1 2 7 4) 3), should return #f: ")
(containsN? (list 1 2 7 4) 3) ;Value: #f