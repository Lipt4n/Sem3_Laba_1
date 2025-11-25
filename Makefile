CC = clang++
CFLAGS = -Wall -std=c++20

SOURCE = DataStructures.cpp
TARGET = test
# Правило для сборки проекта по умолчанию
all: $(TARGET)

$(TARGET): $(SOURCE)
	@echo "Сборка проекта..."
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)
	@echo "Сборка завершена. Запуск: ./$(TARGET)"

manual:
	@echo "1. Препроцессинг: создание main.ii..."
	$(CC) $(CFLAGS) -E $(SOURCE) -o main.ii
	@echo "2. Компиляция: создание main.s..."
	$(CC) $(CFLAGS) -S main.ii -o main.s
	@echo "3. Ассемблирование: создание main.o..."
	$(CC) $(CFLAGS) -c main.s -o main.o
	@echo "4. Линковка: создание исполняемого файла main..."
	$(CC) $(CFLAGS) main.o -o $(TARGET)
	@echo "Ручная сборка завершена. Запуск: ./$(TARGET)"

clear:
	rm -f *.ii *.s *.o $(TARGET)
	@echo "Очистка завершена."

one:
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)
	@echo "----------"
	@./$(TARGET)
	@rm -f test
