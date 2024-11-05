.PHONY: setup_debian, shaders

# -----------------------------------------------------------------------------
# Variables
# -----------------------------------------------------------------------------

PYTHON = python3
ifeq ($(OS),Windows_NT)
	PYTHON = python
endif

# -----------------------------------------------------------------------------
# Targets
# -----------------------------------------------------------------------------

clean:
	rm -rf Build/

setup_debian:
	./Scripts/setup-debian.sh

shaders:
	@echo "Generating shaders header files..."
	@$(PYTHON) --version
	@$(PYTHON) ./Scripts/generate-shaders-header-files.py

# -----------------------------------------------------------------------------
