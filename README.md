# roll
A calculator for shell wizards

## Flags

|Flag |Function
|--- |---
|-i |Infix mode (default) 
|-p |Reverse polish notation mode
|-t |Translate Infix -> RPN
|-h \| -? |help
|-v |verbose (Linux only)

Example:
> roll -i "1 d 20"


## About roll

roll is a command line frontend for a custom library called "libroll". \
The intent of this distinction is that libroll is meant to be integrated into other programs for easy implementation of complex calculations involving dice rolling with weird numbers. \
libroll's approach is based on common Tabletop gaming [Dice Notation systems]( https://en.wikipedia.org/wiki/Dice_notation/ ), treating dice rolling as a mathematical operator with each die beginning at 1 and couting upwards to the specified amount of sides. \
Currently these mathematical operators are being defined as "d" for normal rolls, as well as "d!" for rolls using exploding dice. \
Both are right-to-left associative, meaning `A d B d C` is equivalent to `A d ( B d C )` **not** `( A d B ) d C`. \
For more information about calculations/programming in libroll, see [the Wiki.](http://www.github.com/zibonbadi/roll/wiki/Home)
