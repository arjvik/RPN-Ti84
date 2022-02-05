# ----------------------------
# Makefile Options
# ----------------------------

NAME ?= RPN2ASM
DESCRIPTION ?= "Reverse Polish Notation"
COMPRESSED ?= NO
ARCHIVED ?= NO

CFLAGS ?= -Wall -Wextra -Oz
CXXFLAGS ?= -Wall -Wextra -Oz

# ----------------------------

ifndef CEDEV
$(error CEDEV environment path variable is not set)
endif

include $(CEDEV)/meta/makefile.mk

.PHONY: install
install: bin/$(TARGET8XP)
	$(Q)tilp bin/$(TARGET8XP)
