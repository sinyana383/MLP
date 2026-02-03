CC = g++

CFLAGS = -Wall -Werror -Wextra --std=c++17
BUILD_DIR = build
CLANG_TIDY_CMD = clang-format -style=google -n

.PHONY:  all install uninstall clean dvi dist tests lint

all: install

$(BUILD_DIR):
	mkdir -p $@


install: $(BUILD_DIR)
	qmake -makefile -Wall -o $(BUILD_DIR) view/mlp.pro
	make -C $(BUILD_DIR)
	./$(BUILD_DIR)/mlp.app/Contents/MacOS/mlp


uninstall:
	rm -rf build

dist:
	zip -r $(BUILD_DIR)/mlp.zip $(BUILD_DIR)/mlp.app/Contents/MacOS/mlp

dvi:
#	документация (через doxygen)

test:
#	тесты функций связанных с вычислениями (GTest)

clean: uninstall
#	 удаление dvi

lint:
#	 проверка на google-style