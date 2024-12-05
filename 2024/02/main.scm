(define (read-file-as-string filename)
  (call-with-input-file filename
    (lambda (port)
      (let ((contents (get-string-all port)))
        contents))))

(define (read-file-lines filename)
  (call-with-input-file filename
    (lambda (port)
      (let loop ((lines '()) (current-line '()))
        (let ((char (read-char port)))
          (cond
           ((eof-object? char)
            ;; End of file: Add the last line if there's any content
            (if (null? current-line)
                (reverse lines)
                (reverse (cons (list->string (reverse current-line)) lines))))
           ((char=? char #\newline)
            ;; End of a line: Add the current line to lines
            (loop (cons (list->string (reverse current-line)) lines) '()))
           (else
            ;; Keep building the current line
            (loop lines (cons char current-line)))))))))

(define input1 (read-file-lines "input/input1_mini.txt"))

(define (test)
  (for-each (lambda (line) (display line) (newline)) input1))

