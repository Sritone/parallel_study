CXX = g++
CXXFLAGS = -fopenmp -O2

SRC_DIR = src
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
PROGS = $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%, $(SRCS))

all: $(PROGS)

$(BIN_DIR)/%: $(SRC_DIR)/%.cpp
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@
	@echo "✨ 컴파일 완료: $@"

clean:
	rm -rf $(BIN_DIR)/*
	@echo "🧹 청소 완료!"
