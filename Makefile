
build:
	@bazel build //main:data-structures
	@clear

run: build
	@bazel-bin/main/data-structures
