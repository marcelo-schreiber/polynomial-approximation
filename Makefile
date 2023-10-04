PROJ_NAME=interpola
 
# .c files
C_SOURCE=$(wildcard *.c)
 
# .h files
H_SOURCE=$(wildcard *.h)
 
# Object files
OBJ=$(C_SOURCE:.c=.o)
 
# Compiler
CC=gcc
 
# Flags for compiler
CC_FLAGS=-c         \
				 -O3				\
				 -mavx			\
				 -march=native	\
         -Wall      \

 LIKWID_FLAGS=-DLIKWID_PERFMON \
 						 -I{LIKWID_INCLUDE} \
 						 -L{LIKWID_LIB} \

DISTFILES = *.c *.h README* Makefile likwid.py
DISTDIR = `basename mars22-fqv21`

#
# Compilation and linking
#
all: $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
		$(CC) $(LIKWID_FLAGS) $^ -o $@ -llikwid -lm
 
%.o: %.c %.h
		$(CC) -o $@ $< $(CC_FLAGS) $(LIKWID_C) -lm
 
main.o: main.c $(H_SOURCE)
		$(CC) $< $(CC_FLAGS) $(LIKWID_FLAGS) -o $@ -llikwid -lm
 
clean:
		@rm -f *~ *.bak

purge:  clean
		@rm -f $(PROG) *.o core a.out interpola 
		@rm -rf $(DISTDIR) $(DISTDIR).tar

dist:
		@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
		@ln -s . $(DISTDIR)
		@tar -cvf $(DISTDIR).tar $(addprefix ./$(DISTDIR)/, $(DISTFILES))
		@rm -rf $(DISTDIR)

distcheck:
		@echo "Verificando se o código compila ..."
		@make dist
		@tar -xvf $(DISTDIR).tar
		@cd $(DISTDIR) && make
		@cd $(DISTDIR) && make check
		@rm -rf ./$(DISTDIR)
		@echo "Tudo certo!"

# check:
# 		@echo "Verificando se o tem a saida correta..."
# 		./$(PROJ_NAME) 3.5 < pontos.in > output.out
# 		@grep 7. output.out
# 		@rm -f output.out
		
.PHONY: all