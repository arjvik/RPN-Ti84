#include <tice.h>

real_t stack[99];
char buffer[50];
uint8_t idx;
bool decimal;
bool negative;
bool constantsmode = false;
bool scimode = true;
bool radians = true;
real_t decimalfactor;

real_t r_0, r_1, r_2, r_3, r_4, r_5, r_6, r_7, r_8, r_9, r_10, r_ln10, r_pi, r_e;

void init_real_constants() {
	r_0  = os_Int24ToReal(0);
	r_1  = os_Int24ToReal(1);
	r_2  = os_Int24ToReal(2);
	r_3  = os_Int24ToReal(3);
	r_4  = os_Int24ToReal(4);
	r_5  = os_Int24ToReal(5);
	r_6  = os_Int24ToReal(6);
	r_7  = os_Int24ToReal(7);
	r_8  = os_Int24ToReal(8);
	r_9  = os_Int24ToReal(9);
	r_10 = os_Int24ToReal(10);
	r_ln10 = os_FloatToReal(2.30258509299);
	r_pi   = os_FloatToReal(3.14159265359);
	r_e    = os_FloatToReal(2.71828182846);
}

void draw_line_clear(bool clear) {
	os_RealToStr(buffer, &stack[idx], 0, 1, -1);
	if (clear) {
		os_SetCursorPos(9, 0);
		os_PutStrFull("               ");
	}
	os_SetCursorPos(9, 0);
	os_PutStrFull(buffer);
}

#define OVERDRAW_IS_REDRAW false
void draw_line() {
	draw_line_clear(OVERDRAW_IS_REDRAW);
}

void drawdecimal_line() {
	os_SetCursorPos(9, 0);
	os_PutStrFull(buffer);
	os_PutStrFull(".");
}

void draw_stack_clear(uint8_t row, bool clear) {
	if (row >= 9) {
		os_SetCursorPos(8, 0);
		os_PutStrFull("...            ");
		real_t len = os_Int24ToReal((int24_t) idx);
		os_RealToStr(buffer, &len, 0, 1, -1);
		os_SetCursorPos(8, 4);
		os_PutStrFull(buffer);
	} else {
		if (scimode) {
			os_RealToStr(buffer, &stack[row], 0, 2, 2);
		} else {
			os_RealToStr(buffer, &stack[row], 0, 1, -1);
		}
		if (clear) {
			os_SetCursorPos(row, 0);
			os_PutStrFull("               ");
		}
		os_SetCursorPos(row, 0);
		os_PutStrFull(buffer);
	}
}

void draw_stack(uint8_t row) {
	draw_stack_clear(row, false);
}

void draw_full_stack() {
	for (uint8_t row = 0; row < idx && row <= 9; row++)
		draw_stack_clear(row, true);
}

void delete_stack(uint8_t row) {
	if (row < 9) {
		os_SetCursorPos(row, 0);
		os_PutStrFull("               ");
	}
}

void hint(char *str) {
	os_SetCursorPos(0, 25);
	os_PutStrFull(str);
}

void constants_mode(bool enabled) {
	if (enabled) {
		constantsmode = true;
		hint("^");
	} else {
		constantsmode = false;
		hint(" ");
	}
}

void new_entry() {
	decimal = false;
	negative = false;
	stack[idx] = r_0;
	draw_line_clear(true);

}

void new_problem() {
	idx = 0;
	os_ClrHome();
	buffer[0] = 0;
	new_entry();
}

#define BINARY_OP(os_func)												\
do {																	\
	if (os_RealCompare(&stack[idx], &r_0) != 0) {						\
		if (idx >= 1) {													\
			stack[idx-1] = os_func(&stack[idx-1], &stack[idx]);			\
			draw_stack_clear(idx-1, true);								\
			new_entry();												\
		}																\
	} else {															\
		if (idx >= 2) {													\
			stack[idx-2] = os_func(&stack[idx-2], &stack[idx-1]);		\
			draw_stack_clear(idx-2, true);								\
			delete_stack(idx-1);										\
			idx--;														\
			new_entry();												\
		}																\
	}																	\
} while (false);

#define UNARY_OP(os_func) 												\
do {																	\
	if (os_RealCompare(&stack[idx], &r_0) != 0) {						\
		stack[idx] = os_func(&stack[idx]);								\
		draw_line_clear(true);											\
	} else {															\
		if (idx >= 1) {													\
			stack[idx-1] = os_func(&stack[idx-1]);						\
			draw_stack_clear(idx-1, true);								\
			new_entry();												\
		}																\
	}																	\
} while (false);

#define REAL_TRIG(name, os_func)										\
real_t name(real_t *a) {												\
	real_t t;															\
	if (radians)														\
		t = *a;															\
	else																\
		t = os_RealDegToRad(a);											\
	return os_func(&t);													\
}

REAL_TRIG(degRadSin, os_RealSinRad)
REAL_TRIG(degRadCos, os_RealCosRad)
REAL_TRIG(degRadTan, os_RealTanRad)

#define REAL_INVTRIG(name, os_func)										\
real_t name(real_t *a) {												\
	real_t t = os_func(a);												\
	if (!radians)														\
		t = os_RealRadToDeg(&t);										\
	return t;															\
}

REAL_INVTRIG(radDegAsin, os_RealAsinRad)
REAL_INVTRIG(radDegAcos, os_RealAcosRad)
REAL_INVTRIG(radDegAtan, os_RealAtanRad)

real_t realLogBase10(real_t *a) {
	real_t t = os_RealLog(a);
	return os_RealDiv(&t, &r_ln10);
}

real_t realSquare(real_t *a) {
	return os_RealMul(a, a);
}

real_t realTenExp(real_t *a) {
	return os_RealPow(&r_10, a);
}

real_t realScientificNotation(real_t *a, real_t *b) {
	real_t m = os_RealPow(&r_10, b);
	return os_RealMul(a, &m);
}

void main() {
	uint8_t key;
	
	init_real_constants();
	new_problem();
	
	while ((key = os_GetCSC()) != sk_Graph) {
		if (constantsmode) {
			if (key == sk_Power) {
				stack[idx] = r_pi;
				constants_mode(false);
				draw_line_clear(true);
			} else if (key == sk_Div) {
				stack[idx] = r_e;
				constants_mode(false);
				draw_line_clear(true);
			} else if (key == sk_Log) {
				UNARY_OP(realTenExp);
				constants_mode(false);
			} else if (key == sk_Ln) {
				UNARY_OP(os_RealExp);
				constants_mode(false);
			} else if (key == sk_Sin) { // asin and cos switched intentionally
				UNARY_OP(radDegAcos);   // to correct TI OS or tice.h bug
				constants_mode(false);
			} else if (key == sk_Cos) { // asin and acos switched intentionally
				UNARY_OP(radDegAsin);   // to correct TI OS or tice.h bug
				constants_mode(false);
			} else if (key == sk_Tan) {
				UNARY_OP(radDegAtan);
				constants_mode(false);
			} else if (key == sk_Square) {
				UNARY_OP(os_RealSqrt);
				constants_mode(false);
			} else if (key == sk_Comma) {
				BINARY_OP(realScientificNotation);
				constants_mode(false);
			} else if (key == sk_Apps) {
				radians = !radians;
				constants_mode(false);
				hint(radians ? "r" : "d");
			} else if (key == sk_2nd) {
				constants_mode(false);
			} else if (key == sk_Del) {
				constants_mode(false);
				new_problem();
			}
		} else {
			if (key == sk_0 || key == sk_1 || key == sk_2 || key == sk_3 || key == sk_4 ||
				key == sk_5 || key == sk_6 || key == sk_7 || key == sk_8 || key == sk_9 ) {
				if (!decimal) {
					stack[idx] = os_RealMul(&stack[idx], &r_10);
					real_t toAdd = r_0;
					if (key == sk_1) toAdd = r_1;
					if (key == sk_2) toAdd = r_2;
					if (key == sk_3) toAdd = r_3;
					if (key == sk_4) toAdd = r_4;
					if (key == sk_5) toAdd = r_5;
					if (key == sk_6) toAdd = r_6;
					if (key == sk_7) toAdd = r_7;
					if (key == sk_8) toAdd = r_8;
					if (key == sk_9) toAdd = r_9;
					if (!negative)
						stack[idx] = os_RealAdd(&stack[idx], &toAdd);
					else
						stack[idx] = os_RealSub(&stack[idx], &toAdd);
					draw_line();
				} else {
					real_t toAdd = r_0;
					if (key == sk_1) toAdd = r_1;
					if (key == sk_2) toAdd = r_2;
					if (key == sk_3) toAdd = r_3;
					if (key == sk_4) toAdd = r_4;
					if (key == sk_5) toAdd = r_5;
					if (key == sk_6) toAdd = r_6;
					if (key == sk_7) toAdd = r_7;
					if (key == sk_8) toAdd = r_8;
					if (key == sk_9) toAdd = r_9;
					toAdd = os_RealMul(&toAdd, &decimalfactor);
					if (!negative)
						stack[idx] = os_RealAdd(&stack[idx], &toAdd);
					else
						stack[idx] = os_RealSub(&stack[idx], &toAdd);
					decimalfactor = os_RealDiv(&decimalfactor, &r_10);
						
					draw_line_clear(true);
				}
			} else if (key == sk_Chs) {
				stack[idx] = os_RealNeg(&stack[idx]);
				negative = !negative;
				draw_line_clear(true);
			} else if (key == sk_DecPnt) {
				if (!decimal) {
					decimal = true;
					decimalfactor = os_RealDiv(&r_1, &r_10);
					drawdecimal_line();
				}
			} else if (key == sk_Clear) {
				new_entry();
			} else if (key == sk_Left) {
				if (negative) os_RealNeg(&stack[idx]);
				if (!decimal) {
					stack[idx] = os_RealDiv(&stack[idx], &r_10);
				} else decimal = false;
				stack[idx] = os_RealFloor(&stack[idx]);
				if (negative) os_RealNeg(&stack[idx]);
				draw_line_clear(true);
			} else if (key == sk_Enter) {
				if (idx == 98) {
					new_problem();
				} else {
					draw_stack(idx++);
					new_entry();
				}
			} else if (key == sk_Mode) {
				scimode = !scimode;
				draw_full_stack();
			} else if (key == sk_Del) {
				new_problem();
			} else if (key == sk_Add) {
				BINARY_OP(os_RealAdd);
			} else if (key == sk_Sub) {
				BINARY_OP(os_RealSub);
			} else if (key == sk_Mul) {
				BINARY_OP(os_RealMul);
			} else if (key == sk_Div) {
				BINARY_OP(os_RealDiv);
			} else if (key == sk_Power) {
				BINARY_OP(os_RealPow);
			} else if (key == sk_Log) {
				UNARY_OP(realLogBase10);
			} else if (key == sk_Ln) {
				UNARY_OP(os_RealLog);
			} else if (key == sk_Sin) {
				UNARY_OP(degRadSin);
			} else if (key == sk_Cos) {
				UNARY_OP(degRadCos);
			} else if (key == sk_Tan) {
				UNARY_OP(degRadTan);
			} else if (key == sk_Square) {
				UNARY_OP(realSquare);
			} else if (key == sk_Recip) {
				UNARY_OP(os_RealInv);
			} else if (key == sk_Comma) {
				BINARY_OP(realScientificNotation);
			} else if (key == sk_2nd) {
				constants_mode(true);
			} else if (key == sk_Yequ) {
				os_ClrHome();
				os_SetCursorPos(0, 0);
				os_PutStrFull("Arjun's RPN Calculator");
				os_SetCursorPos(1, 0);
				os_PutStrFull("v2.0 (ASM)");
				os_SetCursorPos(3, 0);
				os_PutStrFull("git.io/ti84rpn");
				while (os_GetCSC() == 0);
				os_ClrHome();
				draw_full_stack();
				draw_line_clear(true);
			}
		}
	}
}
