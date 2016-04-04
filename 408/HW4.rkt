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
(display "Testing (containsN? (list 1 2 3 4) 3), should return #t: ")
(containsN? (list 1 2 3 4) 3) ;Value: #t
(display "Testing (containsN? (list 1 2 7 4) 3), should return #f: ")
(containsN? (list 1 2 7 4) 3) ;Value: #f

(display "b)")(newline)
(define (removeR object list)
  (define (extract blist elist object)
    (if (null? elist)
        (reverse blist)
        (if (equal? (car elist) object)
            (extract blist (cdr elist) object)
            (extract (cons (car elist) blist) (cdr elist) object))))
  (extract null list object))

(display "Testing (removeR 2 (list 1 2)), should return (1): ")
(removeR 2 (list 1 2)) ;Value: (1)
(display "Testing (removeR 2 (list 1 2 3 2 1)), should return (1 3 1): ")
(removeR 2 (list 1 2 3 2 1)) ;Value: (1 3 1)
(display "Testing (removeR 2 (list 1 2 3 2 1 1)), should return (1 3 1 1): ")
(removeR 2 (list 1 2 3 2 1 1)) ;Value: (1 3 1 1)

(define (removeA object list)
  (accumulate (lambda (item rest)
                (cons item rest))
              null
              list))
(removeA 2 (list 1 2 3 2 1 2)) ;Value: (1 3 1)

;2


