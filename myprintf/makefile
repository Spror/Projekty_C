# Shell commands
RM := rm -rf

# Pretty print functions
define print_cc
	$(if $(Q), @echo "[CC]        $(1)")
endef

define print_bin
	$(if $(Q), @echo "[BIN]       $(1)")
endef

define print_rm
	$(if $(Q), @echo "[RM]        $(1)")
endef

# (Quiet or Verbose mode) type make V=1 to enable verbose mode
ifeq ("$(origin V)", "command line")
	Q :=
else
	Q ?= @
endif

# Directories
SDIR := ./src
IDIR := ./inc
ADIR := ./app
TDIR := ./test


# Files
SRC := $(wildcard $(SDIR)/*.c)

ASRC := $(SRC) $(wildcard $(ADIR)/*.c)
TSRC := $(SRC) $(wildcard $(TDIR)/*.c)

AOBJ := $(ASRC:%.c=%.o)
TOBJ := $(TSRC:%.c=%.o)
OBJ := $(AOBJ) $(TOBJ)


# Exernal libraries
LIB :=

# Binary files
AEXEC := app.out
TEXEC := test.out

# Compiler options
CC ?= gcc

C_STD := -std=c17
C_OPT := -O3
C_WARN :=
GGDB :=

ifeq ($(CC),clang)
	C_WARN += -Weverything -Wno-padded -Wno-vla -Wno-disabled-macro-expansion
else ifneq (, $(filter $(CC), cc gcc))
	C_OPT += -fPIC
	C_WARN += -Wall -Wextra -pedantic -Wcast-align \
			  -Winit-self -Wlogical-op -Wmissing-include-dirs \
			  -Wredundant-decls -Wshadow -Wstrict-overflow=5 -Wundef  \
			  -Wwrite-strings -Wpointer-arith -Wmissing-declarations \
			  -Wuninitialized -Wold-style-definition -Wstrict-prototypes \
			  -Wmissing-prototypes -Wswitch-default -Wbad-function-cast \
			  -Wnested-externs -Wconversion -Wunreachable-code
endif

# (Compilation for GDB) type make DEBUG=1 to enable gdb build mode
ifeq ("$(origin DEBUG)", "command line")
	GGDB := -ggdb3
else
	GGDB :=
endif

C_FLAGS = $(C_STD) $(C_OPT) $(C_WARN) $(GGDB)

# Headers and library for linker
H_INC := $(foreach d, $(IDIR), -I$d)
L_INC := $(foreach l, $(LIB), -l$l)


# Main dependency tree of Makefile
all: app test


app : $(AEXEC)

$(AEXEC) : $(AOBJ)
	$(call print_bin,$@)
	$(Q)$(CC) $(C_FLAGS) $(H_INC) $(AOBJ) -o $@ $(L_INC)

test: $(TEXEC)

$(TEXEC): $(TOBJ)
	$(call print_bin,$@)
	$(Q)$(CC) $(C_FLAGS) $(H_INC) $(TOBJ) -o $@ $(L_INC)

%.o:%.c
	$(call print_cc,$<)
	$(Q)$(CC) $(C_FLAGS) $(H_INC) -c $< -o $@

clean:
	$(call print_rm,AEXEC)
	$(Q)$(RM) $(AEXEC)
	$(call print_rm, TEXEC)
	$(Q)$(RM) $(TEXEC)
	$(call print_rm,OBJ )
	$(Q)$(RM) $(OBJ)
	
	
