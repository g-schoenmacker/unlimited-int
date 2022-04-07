### Makefile created by GSMake 1.0 at 19-07-2012 13:50.
### Last updated at 12-08-2012 13:13.

### CONFIGURE - EDIT TO PREFERENCE

# Compiler, flags and include directories (-I)
CC    := g++
CCFL  := -Wall -Werror -Wextra -std=c++11 -O3
INC   := 

# Linker, flags and external libraries (-l) 
CCLD  := $(CC)
CCLDF := 
LIB   := 

# Executable name, source dir and compile dir
EXEC  := main
SRC   := src
BIN   := bin

# Colours used in messages
C_DEFAULT := \033[m
C_CORRECT := \033[0;32m
C_FTERROR := \033[0;31m
C_WARNING := \033[0;33m
C_MESSAGE := \033[0;34m

# Toggle fancy printing (colours and formatting) [true/false]
FANCY = false

### CANNED RECIPIES FOR COMPILING AND LINKING - EDIT TO PREFERENCE

# Recipe for compiling
ifeq ($(FANCY),true)
define compile
	@echo -en "$(C_MESSAGE)----- [$(N)/$(words $(OBJ))] $< ----- $(C_DEFAULT)"
	@$(CC) -c $(CCFL) $(INC) $< -o $@ 2> .temp.log || touch .temp.err
	$(result_eval)
endef
else
define compile
	@echo -n "[$(N)/$(words $(OBJ))] "
	$(CC) -c $(CCFL) $(INC) $< -o $@
endef
endif

# Recipe for linking
ifeq ($(FANCY),true)
define link
	@echo -ne "$(C_MESSAGE)----- LINKING ----- $(C_DEFAULT)"
	@$(CCLD) $(CCLDF) $(OBJ) -o $(EXEC) $(LIB) 2> .temp.log || touch .temp.err
	$(result_eval)
endef
else
define link
	@echo -n "[LINKING] "
	$(CCLD) $(CCLDF) $(OBJ) -o $(EXEC) $(LIB)
endef
endif

# Recipe for result evaluation, used for fancy printing
define result_eval
	@if test -e .temp.err; then echo -e "$(C_FTERROR)[ERR]"; elif test -s .temp.log; then echo -e "$(C_WARNING)[WARN]"; else echo -e "$(C_CORRECT)[OK]"; fi;
	@cat .temp.log && echo -en "$(C_DEFAULT)"
	@if test -e .temp.err; then rm -f .temp.log .temp.err && false; fi;
	@rm -f .temp.log
endef

### DO NOT CHANGE ANYTHING FROM THIS POINT ON, INCLUDING THIS LINE AND OTHER COMMENTS

### RULES FOR TRANSFORMING COMPILER ARGUMENTS

# Adding -I to $(INC)
INC := $(patsubst %,-I%,$(INC))

# Adding -l to $(LIB)
LIB := $(patsubst %,-l%,$(LIB))

### OBJECT FILE DATA

# Object files
OBJ   := $(BIN)/uint_test.o $(BIN)/main.o $(BIN)/int/pow.o $(BIN)/int/op_extract.o $(BIN)/int/divide.o $(BIN)/int/op_plus_assign.o $(BIN)/int/op_min_assign.o $(BIN)/int/ll.o $(BIN)/int/op_insert.o $(BIN)/int/compare.o $(BIN)/int/constr_string.o $(BIN)/int_test.o $(BIN)/str_uint_test.o $(BIN)/uint/ull.o $(BIN)/uint/constr_uint.o $(BIN)/uint/consolidate.o $(BIN)/uint/op_lshift_assign.o $(BIN)/uint/op_and_assign.o $(BIN)/uint/op_mult.o $(BIN)/uint/pow.o $(BIN)/uint/op_extract.o $(BIN)/uint/set_bit.o $(BIN)/uint/divide.o $(BIN)/uint/op_plus_assign.o $(BIN)/uint/op_min_assign.o $(BIN)/uint/op_insert.o $(BIN)/uint/str.o $(BIN)/uint/constr_int.o $(BIN)/uint/sqrt.o $(BIN)/uint/compare.o $(BIN)/uint/op_rshift.o $(BIN)/uint/op_xor_assign.o $(BIN)/uint/op_or_assign.o $(BIN)/uint/constr_string.o $(BIN)/str_uint/constr_uint.o $(BIN)/str_uint/op_mult.o $(BIN)/str_uint/op_extract.o $(BIN)/str_uint/divide.o $(BIN)/str_uint/op_plus_assign.o $(BIN)/str_uint/op_min_assign.o $(BIN)/str_uint/op_insert.o $(BIN)/str_uint/str.o $(BIN)/str_uint/constr_string.o

### PHONY RULES

.PHONY	: all clean createbin

# Main goal
all : createbin $(OBJ)
	$(link)

# Clean executable and object file directories
clean :
	rm -fr $(EXEC) $(BIN)

# Create object file directories
createbin :
	@mkdir -p $(sort $(dir $(OBJ)))

### OBJECT FILE RECIPIES FOR COMPILING

$(BIN)/uint_test.o : $(SRC)/uint_test.cc src/int/int.h src/uint/uint.h
	$(eval N := 1)
	$(compile)

$(BIN)/main.o : $(SRC)/main.cc src/main.h
	$(eval N := 2)
	$(compile)

$(BIN)/int/pow.o : $(SRC)/int/pow.cc src/int/int.h src/int/int.ih src/uint/uint.h
	$(eval N := 3)
	$(compile)

$(BIN)/int/op_extract.o : $(SRC)/int/op_extract.cc src/int/int.h src/int/int.ih src/uint/uint.h
	$(eval N := 4)
	$(compile)

$(BIN)/int/divide.o : $(SRC)/int/divide.cc src/int/int.h src/int/int.ih src/uint/uint.h
	$(eval N := 5)
	$(compile)

$(BIN)/int/op_plus_assign.o : $(SRC)/int/op_plus_assign.cc src/int/int.h src/int/int.ih src/uint/uint.h
	$(eval N := 6)
	$(compile)

$(BIN)/int/op_min_assign.o : $(SRC)/int/op_min_assign.cc src/int/int.h src/int/int.ih src/uint/uint.h
	$(eval N := 7)
	$(compile)

$(BIN)/int/ll.o : $(SRC)/int/ll.cc src/int/int.h src/int/int.ih src/uint/uint.h
	$(eval N := 8)
	$(compile)

$(BIN)/int/op_insert.o : $(SRC)/int/op_insert.cc src/int/int.h src/int/int.ih src/uint/uint.h
	$(eval N := 9)
	$(compile)

$(BIN)/int/compare.o : $(SRC)/int/compare.cc src/int/int.h src/int/int.ih src/uint/uint.h
	$(eval N := 10)
	$(compile)

$(BIN)/int/constr_string.o : $(SRC)/int/constr_string.cc src/int/int.h src/int/int.ih src/uint/uint.h
	$(eval N := 11)
	$(compile)

$(BIN)/int_test.o : $(SRC)/int_test.cc src/int/int.h src/uint/uint.h
	$(eval N := 12)
	$(compile)

$(BIN)/str_uint_test.o : $(SRC)/str_uint_test.cc src/str_uint/str_uint.h
	$(eval N := 13)
	$(compile)

$(BIN)/uint/ull.o : $(SRC)/uint/ull.cc src/int/int.h src/str_uint/str_uint.h src/uint/uint.h src/uint/uint.ih
	$(eval N := 14)
	$(compile)

$(BIN)/uint/constr_uint.o : $(SRC)/uint/constr_uint.cc src/int/int.h src/str_uint/str_uint.h src/uint/uint.h src/uint/uint.ih
	$(eval N := 15)
	$(compile)

$(BIN)/uint/consolidate.o : $(SRC)/uint/consolidate.cc src/int/int.h src/str_uint/str_uint.h src/uint/uint.h src/uint/uint.ih
	$(eval N := 16)
	$(compile)

$(BIN)/uint/op_lshift_assign.o : $(SRC)/uint/op_lshift_assign.cc src/int/int.h src/str_uint/str_uint.h src/uint/uint.h src/uint/uint.ih
	$(eval N := 17)
	$(compile)

$(BIN)/uint/op_and_assign.o : $(SRC)/uint/op_and_assign.cc src/int/int.h src/str_uint/str_uint.h src/uint/uint.h src/uint/uint.ih
	$(eval N := 18)
	$(compile)

$(BIN)/uint/op_mult.o : $(SRC)/uint/op_mult.cc src/int/int.h src/str_uint/str_uint.h src/uint/uint.h src/uint/uint.ih
	$(eval N := 19)
	$(compile)

$(BIN)/uint/pow.o : $(SRC)/uint/pow.cc src/int/int.h src/str_uint/str_uint.h src/uint/uint.h src/uint/uint.ih
	$(eval N := 20)
	$(compile)

$(BIN)/uint/op_extract.o : $(SRC)/uint/op_extract.cc src/int/int.h src/str_uint/str_uint.h src/uint/uint.h src/uint/uint.ih
	$(eval N := 21)
	$(compile)

$(BIN)/uint/set_bit.o : $(SRC)/uint/set_bit.cc src/int/int.h src/str_uint/str_uint.h src/uint/uint.h src/uint/uint.ih
	$(eval N := 22)
	$(compile)

$(BIN)/uint/divide.o : $(SRC)/uint/divide.cc src/int/int.h src/str_uint/str_uint.h src/uint/uint.h src/uint/uint.ih
	$(eval N := 23)
	$(compile)

$(BIN)/uint/op_plus_assign.o : $(SRC)/uint/op_plus_assign.cc src/int/int.h src/str_uint/str_uint.h src/uint/uint.h src/uint/uint.ih
	$(eval N := 24)
	$(compile)

$(BIN)/uint/op_min_assign.o : $(SRC)/uint/op_min_assign.cc src/int/int.h src/str_uint/str_uint.h src/uint/uint.h src/uint/uint.ih
	$(eval N := 25)
	$(compile)

$(BIN)/uint/op_insert.o : $(SRC)/uint/op_insert.cc src/int/int.h src/str_uint/str_uint.h src/uint/uint.h src/uint/uint.ih
	$(eval N := 26)
	$(compile)

$(BIN)/uint/str.o : $(SRC)/uint/str.cc src/int/int.h src/str_uint/str_uint.h src/uint/uint.h src/uint/uint.ih
	$(eval N := 27)
	$(compile)

$(BIN)/uint/constr_int.o : $(SRC)/uint/constr_int.cc src/int/int.h src/str_uint/str_uint.h src/uint/uint.h src/uint/uint.ih
	$(eval N := 28)
	$(compile)

$(BIN)/uint/sqrt.o : $(SRC)/uint/sqrt.cc src/int/int.h src/str_uint/str_uint.h src/uint/uint.h src/uint/uint.ih
	$(eval N := 29)
	$(compile)

$(BIN)/uint/compare.o : $(SRC)/uint/compare.cc src/int/int.h src/str_uint/str_uint.h src/uint/uint.h src/uint/uint.ih
	$(eval N := 30)
	$(compile)

$(BIN)/uint/op_rshift.o : $(SRC)/uint/op_rshift.cc src/int/int.h src/str_uint/str_uint.h src/uint/uint.h src/uint/uint.ih
	$(eval N := 31)
	$(compile)

$(BIN)/uint/op_xor_assign.o : $(SRC)/uint/op_xor_assign.cc src/int/int.h src/str_uint/str_uint.h src/uint/uint.h src/uint/uint.ih
	$(eval N := 32)
	$(compile)

$(BIN)/uint/op_or_assign.o : $(SRC)/uint/op_or_assign.cc src/int/int.h src/str_uint/str_uint.h src/uint/uint.h src/uint/uint.ih
	$(eval N := 33)
	$(compile)

$(BIN)/uint/constr_string.o : $(SRC)/uint/constr_string.cc src/int/int.h src/str_uint/str_uint.h src/uint/uint.h src/uint/uint.ih
	$(eval N := 34)
	$(compile)

$(BIN)/str_uint/constr_uint.o : $(SRC)/str_uint/constr_uint.cc src/str_uint/str_uint.h src/str_uint/str_uint.ih
	$(eval N := 35)
	$(compile)

$(BIN)/str_uint/op_mult.o : $(SRC)/str_uint/op_mult.cc src/str_uint/str_uint.h src/str_uint/str_uint.ih
	$(eval N := 36)
	$(compile)

$(BIN)/str_uint/op_extract.o : $(SRC)/str_uint/op_extract.cc src/str_uint/str_uint.h src/str_uint/str_uint.ih
	$(eval N := 37)
	$(compile)

$(BIN)/str_uint/divide.o : $(SRC)/str_uint/divide.cc src/str_uint/str_uint.h src/str_uint/str_uint.ih
	$(eval N := 38)
	$(compile)

$(BIN)/str_uint/op_plus_assign.o : $(SRC)/str_uint/op_plus_assign.cc src/str_uint/str_uint.h src/str_uint/str_uint.ih
	$(eval N := 39)
	$(compile)

$(BIN)/str_uint/op_min_assign.o : $(SRC)/str_uint/op_min_assign.cc src/str_uint/str_uint.h src/str_uint/str_uint.ih
	$(eval N := 40)
	$(compile)

$(BIN)/str_uint/op_insert.o : $(SRC)/str_uint/op_insert.cc src/str_uint/str_uint.h src/str_uint/str_uint.ih
	$(eval N := 41)
	$(compile)

$(BIN)/str_uint/str.o : $(SRC)/str_uint/str.cc src/str_uint/str_uint.h src/str_uint/str_uint.ih
	$(eval N := 42)
	$(compile)

$(BIN)/str_uint/constr_string.o : $(SRC)/str_uint/constr_string.cc src/str_uint/str_uint.h src/str_uint/str_uint.ih
	$(eval N := 43)
	$(compile)

