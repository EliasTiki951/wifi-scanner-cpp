# ============================================================
# WiFi Scanner C++ - Makefile
# ============================================================
# Compilador y opciones
CXX = g++
CXXFLAGS = -Wall -Wextra -O2
TARGET = wifi_scanner.exe
SOURCE = main.cpp

# Colores para la salida (opcional)
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m # No Color

# ============================================================
# Reglas principales
# ============================================================

# Regla por defecto: compilar el programa
all: $(TARGET)

# Compilar el ejecutable
$(TARGET): $(SOURCE)
	@echo "$(GREEN)Compilando WiFi Scanner C++...$(NC)"
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)
	@echo "$(GREEN)? Compilación exitosa: $(TARGET)$(NC)"
	@echo "$(YELLOW)Ejecuta como Administrador para ver contraseñas.$(NC)"

# Compilar con soporte para C++98 (compiladores antiguos)
cpp98:
	@echo "$(YELLOW)Compilando con estándar C++98...$(NC)"
	$(CXX) $(CXXFLAGS) -std=c++98 -o $(TARGET) $(SOURCE)
	@echo "$(GREEN)? Compilación exitosa (C++98): $(TARGET)$(NC)"

# Compilar con soporte para C++11
cpp11:
	@echo "$(YELLOW)Compilando con estándar C++11...$(NC)"
	$(CXX) $(CXXFLAGS) -std=c++11 -o $(TARGET) $(SOURCE)
	@echo "$(GREEN)? Compilación exitosa (C++11): $(TARGET)$(NC)"

# Compilar en modo debug (con símbolos de depuración)
debug:
	@echo "$(YELLOW)Compilando en modo debug...$(NC)"
	$(CXX) $(CXXFLAGS) -g -o $(TARGET) $(SOURCE)
	@echo "$(GREEN)? Compilación debug: $(TARGET)$(NC)"

# Limpiar archivos generados
clean:
	@echo "$(YELLOW)Limpiando archivos generados...$(NC)"
	@rm -f $(TARGET)
	@rm -f *.o
	@rm -f *.txt
	@echo "$(GREEN)? Limpieza completada.$(NC)"

# Ejecutar el programa (compila primero)
run: $(TARGET)
	@echo "$(GREEN)Ejecutando WiFi Scanner C++...$(NC)"
	@echo "$(RED)? Recuerda ejecutar como Administrador$(NC)"
	@./$(TARGET)

# Compilar y ejecutar en una sola línea
quick: $(TARGET)
	@./$(TARGET)

# Mostrar ayuda
help:
	@echo "================================================"
	@echo "  WiFi Scanner C++ - Makefile"
	@echo "================================================"
	@echo ""
	@echo "  $(GREEN)make$(NC)         - Compila el programa (por defecto)"
	@echo "  $(GREEN)make cpp98$(NC)   - Compila con estándar C++98"
	@echo "  $(GREEN)make cpp11$(NC)   - Compila con estándar C++11"
	@echo "  $(GREEN)make debug$(NC)   - Compila en modo debug"
	@echo "  $(GREEN)make clean$(NC)   - Elimina archivos generados"
	@echo "  $(GREEN)make run$(NC)     - Compila y ejecuta"
	@echo "  $(GREEN)make quick$(NC)   - Ejecuta sin recompilar"
	@echo "  $(GREEN)make help$(NC)    - Muestra esta ayuda"
	@echo ""
	@echo "  $(YELLOW)Requisitos:$(NC) g++ y make instalados"
	@echo "  $(RED)? Ejecutar siempre como Administrador$(NC)"

# ============================================================
# Reglas phony (no son archivos reales)
# ============================================================
.PHONY: all cpp98 cpp11 debug clean run quick help
