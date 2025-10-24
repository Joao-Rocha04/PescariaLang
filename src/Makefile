# ===========================================================
# Makefile — PescariaLang Compiler
# Compila análise léxica (Flex) e sintática (Bison)
# e executa o exemplo padrão (examples.fl)
# ===========================================================

# Nome do executável final
EXEC = pescaria

# Arquivos-fonte
LEXER = lexer.l
PARSER = parser.y

# Arquivos gerados automaticamente
LEXER_C = lex.yy.c
PARSER_C = parser.tab.c
PARSER_H = parser.tab.h

# Caminho do exemplo (ajuste se necessário)
EXAMPLE = ../examples.fl/pescar.fl

# ===========================================================
# Alvo padrão: compila tudo
# ===========================================================
all: $(EXEC)
	@echo "Compilação concluída! Executável gerado: ./$(EXEC)"

# ===========================================================
# Geração do executável
# ===========================================================
$(EXEC): $(LEXER_C) $(PARSER_C)
	@echo "Ligando objetos e gerando executável..."
	gcc -o $(EXEC) $(PARSER_C) $(LEXER_C) -lfl

# ===========================================================
# Geração do parser e lexer
# ===========================================================
$(PARSER_C) $(PARSER_H): $(PARSER)
	@echo "Gerando parser (Bison)..."
	bison -d $(PARSER)

$(LEXER_C): $(LEXER)
	@echo "Gerando lexer (Flex)..."
	flex $(LEXER)

# ===========================================================
# Teste automático (roda o exemplo padrão)
# ===========================================================
run: all
	@echo "Executando exemplo padrão: $(EXAMPLE)"
	@./$(EXEC) < $(EXAMPLE)

# ===========================================================
# Limpeza
# ===========================================================
clean:
	@echo "Limpando arquivos temporários..."
	rm -f $(LEXER_C) $(PARSER_C) $(PARSER_H) $(EXEC)

.PHONY: all clean run
