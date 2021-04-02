# RPN-Ti84

### Advanced Reverse Polish Notation entry program for the Ti-84+CE calculators

<p align="center"><img src=".github/demo.gif" alt="Demo GIF" /></p>

Designed for the UIL Texas Calculator Applications competition, where the raw speed of Reverse Polish Notation combined with the familiarity of a Ti-84+CE can provide a significant competitive advantage.

*Arjun's RPN Calculator v2.0 (ASM) - git.io/ti84rpn*

### Story

The first version of this program was `RPN.8xp`, written in TI-BASIC. Unfortunately, it had too much input lag to be usable in a competition setting. I decided that I wanted to write an improved version of it for the 2021 UIL/TMSCA season, and planned to work on it over my spring break before the TMSCA State Meet.

Naturally, I waited until the night before the exam to start working on this program. Considering that I put the finishing touches on it minutes before starting the exam itself, the program worked incredibly well—I saw no crashes, freezes, or any other discernible bugs!

### Building and Installing

```bash
source env.sh
make #compiles .8xp file
tilp bin/RPN2ASM.8xp #transfers to calculator
```

### Features

| <p align="center">**Real Arithmetic Functions**</p>![](.github/arithmetic.png) | <p align="center">**Scientific Notation**</p>![](.github/scientific.png) |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| <p align="center">**Constants**</p>![](.github/constants.png) | <p align="center">**Degrees/Radians Trigonometry**</p>![](.github/degrad.png) |

- Infinite stack
- Easy line editing
- Extensible code
- and many more

### Credits

- [CE-Programming/toolchain](https://github.com/CE-Programming/toolchain) (`.toolchain/`)
- [tgrysztar/fasmg](https://github.com/tgrysztar/fasmg) (`.fasmg/`)