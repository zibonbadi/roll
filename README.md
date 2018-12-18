# roll
A calculator for shell wizards

## Flags:

|Flag |Function
|--- |---
|-i |Infix mode (default)  \
|-p |Reverse polish notation mode \
|-t |Translate Infix -> RPN \
|-h \| -? |help

Example:
> roll -i "1d20"


## About roll

roll is a command line frontend for a custom library called "libroll". \
The intent of this distinction is that libroll is meant to be integrated into other programs for easy implementation of complex calculations involving dice rolling or other types of random number generation. \
libroll's approach is based on common Tabletop RPG [Dice Notation systems]( https://en.wikipedia.org/wiki/Dice_notation/ ), treating dice rolling as a mathematical operator with each die beginning at 1 and couting upwards to the specified amount of sides. \
Currently these mathematical operators are being defined as "d" for normal rolls, as well as "D" for rolls using exploding dice. \
Both are right-to-left associative, meaning "AdBdC" is equivalent to "Ad(BdC)" but not "(AdB)dC". \
For more information about Calculations in libroll, see [the Wiki.](http://www.github.com/zibonbadi/roll/wiki/Home)
