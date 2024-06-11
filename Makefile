.PHONY: setup_debian, shaders_header

setup_debian:
	./Scripts/setup-debian.sh

shaders_header:
	python ./Scripts/generate-shaders-header-files.py
