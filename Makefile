EXEC := cache_simulator
LIB := libcachemodel.a

SRCDIR := src
OBJDIR := obj

MAIN := $(SRCDIR)/main.cc
SRC := $(filter-out $(MAIN), $(wildcard $(SRCDIR)/*.cc))
OBJ := $(patsubst $(SRCDIR)/%.cc, $(OBJDIR)/%.o, $(SRC))

CC := g++-7
CCFLAG := -std=c++11 -Wall -g -O0 -I $(SRCDIR)
LDFLAG := -L $(PWD) -lcachemodel

.PHONY: default lib clean $(SRCDIR) $(OBJDIR)

default: lib
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
