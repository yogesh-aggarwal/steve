# -----------------------------------------------------------------------------------------------------------
# Variables
# -----------------------------------------------------------------------------------------------------------

BUILD_DIR := build

PYTHON = python3
ifeq ($(OS),Windows_NT)
	PYTHON = python
endif


# -----------------------------------------------------------------------------------------------------------

all: clean build

format:
	@find ./source ./cmd \( -name '*.cpp' -or -name '*.hpp' -or -name '*.tcc' \) -exec clang-format -i {} +

clean:
	@rm -rf $(BUILD_DIR)

generate:
	@cmake -B $(BUILD_DIR) -S .

build: generate
	@cmake --build $(BUILD_DIR) --config Release

setup_debian:
	./scripts/setup-debian.sh

shaders:
	@echo "Generating shaders header files..."
	@$(PYTHON) --version
	@$(PYTHON) ./scripts/generate-shaders-header-files.py

# -----------------------------------------------------------------------------------------------------------
