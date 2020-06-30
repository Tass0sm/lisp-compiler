# Simple Lisp Language Compiler #

An excersise in making a compiler.

## TODOs ##

1. DONE Four Arithmetic Functions
2. DONE Nested Sexps
3. TODO Variables
4. Custom Functions

## Eventual Plan ##

I want to make a script based video editor. The language will look vaguely like this:

```lisp
;; Play the video forward at a given speed with a crop applied.
(insert-video (crop (linear "one.mp4" speed) 1 2 3 4))
;; Play random parts from the clip in rapid succession.
(insert-video (random "two.mp4" frequency))
;; Insert black screen with silence for 15s.
(insert-blank 15s)

;; Define a new way to play a clip by defining a new player function.
(defun boomerang (clip ss t speed)
  (linear clip ss t speed)
  (linear clip ss t -speed))

;; Play three.mkv from 3 s to 13 s and then back to 3 s at pos x = 35, y = 65.
(insert-video (pos (boomerang "three.mkv" 3 10 1.0) 35 65))
```
