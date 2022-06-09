
build:
	@BAZEL_USE_CPP_ONLY_TOOLCHAIN=1 bazel build //main:data-structures

run: build
	@bazel-bin/main/data-structures
