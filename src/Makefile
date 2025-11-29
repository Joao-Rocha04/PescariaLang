# ===========================================================
# Makefile — PescariaLang Compiler + VM Runner
# ===========================================================

EXEC = pescaria
LEXER = lexer.l
PARSER = parser.y

LEXER_C = lex.yy.c
PARSER_C = parser.tab.c
PARSER_H = parser.tab.h

EXAMPLE_SRC = ../examples.fl/pescar.fl
EXAMPLE_PVM = ../examples.fl/pescar.pvm

all: $(EXEC)

# ===========================================================
# Compilar o compilador pescaria
# ===========================================================
$(EXEC): $(LEXER_C) $(PARSER_C)
	@echo "Ligando compilador..."
	gcc -o $(EXEC) $(PARSER_C) $(LEXER_C) -lfl

# ===========================================================
# Gerar parser e lexer
# ===========================================================
$(PARSER_C) $(PARSER_H): $(PARSER)
	@echo "Gerando parser (Bison)..."
	bison -d $(PARSER)

$(LEXER_C): $(LEXER)
	@echo "Gerando lexer (Flex)..."
	flex $(LEXER)

# ===========================================================
# Gerar o .pvm automaticamente
# ===========================================================
pvm: $(EXEC)
	@echo "Gerando arquivo .pvm a partir do exemplo..."
	./$(EXEC) < $(EXAMPLE_SRC) > $(EXAMPLE_PVM)
	@echo "Arquivo gerado: $(EXAMPLE_PVM)"

# ===========================================================
# Rodar a VM em cima do .pvm
# ===========================================================
run: pvm
	@echo "Executando VM com $(EXAMPLE_PVM)..."
	python3 pescaria_vm.py $(EXAMPLE_PVM)

# ===========================================================
# Limpeza
# ===========================================================
clean:
	rm -f $(LEXER_C) $(PARSER_C) $(PARSER_H) $(EXEC)
	rm -f $(EXAMPLE_PVM)

.PHONY: all run clean pvm
