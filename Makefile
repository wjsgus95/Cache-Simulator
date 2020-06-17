EXEC := cache_simulator
LIB := libcachemodel.a

SRCDIR := src
OBJDIR := obj

MAIN := $(SRCDIR)/main.cc
SRC := $(filter-out $(MAIN), $(wildcard $(SRCDIR)/*.cc))
OBJ := $(patsubst $(SRCDIR)/%.cc, $(OBJDIR)/%.o, $(SRC))

CC := g++-7
CCFLAG := -std=c++11 -Wall -I $(SRCDIR)
LDFLAG := -L $(PWD) -lcachemodel

.PHONY: all executable lib debug clean

all: executable

debug: CCFLAG += -g -O0 -DDEBUG
debug: executable

executable: lib
	$(CC) $(CCFLAG) $(MAIN) -o $(EXEC) $(LDFLAG)

lib: $(OBJDIR) $(OBJ)
	ar qcv $(LIB) $(OBJ)
	ranlib $(LIB)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o : $(SRCDIR)/%.cc
	$(CC) $(CCFLAG) -o $@ -c $<

clean:
	rm -rf $(EXEC) $(LIB) $(OBJDIR)
