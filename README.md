# RPN-Ti84

### Advanced Reverse Polish Notation entry program for the Ti-84+CE calculators

<p align="center"><img src=".github/demo.gif" alt="Demo GIF" /></p>

Designed for the UIL Texas Calculator Applications competition, where the raw speed of Reverse Polish Notation combined with the familiarity of a Ti-84+CE can provide a significant competitive advantage.

*Arjun's RPN Calculator v2.1 (ASM) - git.io/ti84rpn*

### Story

The first version of this program was `RPN.8xp`, written in TI-BASIC. Unfortunately, it had too much input lag to be usable in a competition setting. I decided that I wanted to write an improved version of it for the 2021 UIL/TMSCA season, and planned to work on it over my spring break before the TMSCA State Meet.

Naturally, I waited until the night before the exam to start working on this program. Considering that I put the finishing touches on it minutes before starting the exam itself, the program worked incredibly well—I saw no crashes, freezes, or any other discernible bugs!

### Building and Installing

```bash
source env.sh
make # Compiles .8xp file
make install # Transfers to calculator (using TiLP)
```

### Features

| <p align="center">**Real Arithmetic Functions**</p>![](.github/arithmetic.png) | <p align="center">**Scientific Notation**</p>![](.github/scientific.png) |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| <p align="center">**Constants**</p>![](.github/constants.png) | <p align="center">**Degrees/Radians Trigonometry**</p>![](.github/degrad.png) |

- Infinite stack
- Easy line editing
- Extensible code
- and many more

### Keys

| Key                                                          | Action                                                       |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| <kbd>1</kbd>, <kbd>2</kbd>, <kbd>3</kbd>, <kbd>4</kbd>, <kbd>5</kbd>, <kbd>6</kbd>, <kbd>7</kbd>, <kbd>8</kbd>, <kbd>9</kbd>, <kbd>0</kbd>, <kbd>.</kbd>, <kbd>-</kbd> | Enter digits                                                 |
| <kbd>enter</kbd>                                             | Push current value to stack<br />(Resets stack if it grows to over 99 elements) |
| <kbd>clear</kbd>                                             | Clear current value, resetting it to zero                    |
| <kbd>🡰</kbd>                                                 | Backspace<br />(If entering decimals, clears to integer part) |
| <kbd>🡱</kbd>                                                 | Pop and discard entry from stack                             |
| <kbd>+</kbd>, <kbd>-</kbd>, <kbd>×</kbd>, <kbd>÷</kbd>, <kbd>^</kbd> | Binary arithmetic operations<br />Either pops one entry and uses current value, or pops two entries if current value is empty |
| <kbd>,</kbd><br />(or <kbd>2nd</kbd><kbd>,</kbd> aka `EE` for muscle memory) | Scientific notation binary operator, i.e. `x10^`<br />E.g. <kbd>1.23</kbd><kbd>enter</kbd><kbd>6</kbd><kbd>,</kbd> places `1.23E6` on the stack. |
| <kbd>log</kbd>, <kbd>ln</kbd>, <kbd>sin</kbd>, <kbd>cos</kbd>, <kbd>tan</kbd>, <kbd>x²</kbd>, <kbd>x⁻¹</kbd> | Unary arithmetic operations<br />Applies either to current value, or top stack entry if current value is empty |
| <kbd>sto🡲</kbd>                                              | Stores current value, or top stack entry if current value is empty, in OS variable `X` |
| <kbd>del</kbd>                                               | New problem<br />Clears current entry, stack; other settings remain |
| <kbd>mode</kbd>                                              | Switch between 3-sigfig-scientific-notation and standard view |
| <kbd>2nd</kbd><kbd>^</kbd> (`π`), <kbd>2nd</kbd><kbd>÷</kbd> (`e`) | Enter the constants pi or e into the current value<br />Continuing to type digits has strange effects here |
| <kbd>2nd</kbd><kbd>log</kbd> (`10^`), <kbd>2nd</kbd><kbd>ln</kbd> (`e^`),<br /><kbd>2nd</kbd><kbd>sin</kbd> (`sin⁻¹`), <kbd>2nd</kbd><kbd>cos</kbd> (`cos⁻¹`),<br /><kbd>2nd</kbd><kbd>tan</kbd> (`tan⁻¹`), <kbd>2nd</kbd><kbd>x²</kbd> (`√`) | More unary arithmetic operations<br />                       |
| <kbd>2nd</kbd><kbd>sto🡲</kbd> (rcl)                          | Recalls the value of OS variable `X` into the current value  |
| <kbd>2nd</kbd><kbd>apps</kbd> (angle)                        | Switch between degrees and radians for trigonometric functions<br />See hint in top right corner of screen |
| <kbd>2nd</kbd><kbd>2nd</kbd>                                 | Leave "<kbd>2nd</kbd> mode"                                  |
| <kbd>y=</kbd>                                                | About screen                                                 |
| <kbd>graph</kbd>                                             | Exit RPN program                                             |

Note: Most binary operations above are commutative or easy to reverse, except exponentiation. To compute `b^a` when `a` is before `b` on the stack, press <kbd>ln</kbd>, <kbd>×</kbd>, <kbd>2nd</kbd><kbd>ln</kbd>.

### Credits

- [CE-Programming/toolchain](https://github.com/CE-Programming/toolchain) (`.toolchain/`)
- [tgrysztar/fasmg](https://github.com/tgrysztar/fasmg) (`.fasmg/`)
