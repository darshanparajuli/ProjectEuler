DEBUG_FLAGS="-Wall -Wno-vla-extension -g -pedantic -O0 -DDEBUG_MODE"
RELEASE_FLAGS="-Wall -O2"

.PHONY: default
default: debug

.PHONY: debug
debug: pre-build
	@cd build/debug && CC=clang CXX=clang++ cmake ../../ -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS_DEBUG=$(DEBUG_FLAGS) && cmake --build .

.PHONY: release
release: pre-build
	@cd build/release/ && CC=clang CXX=clang++ cmake ../../ -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS_RELEASE=$(RELEASE_FLAGS) && cmake --build .

.PHONY: pre-build
pre-build:
	@mkdir -p build/debug
	@mkdir -p build/release
	@mkdir -p build/xcode

.PHONY: rebuild
rebuild: clean debug

.PHONY: rebuild-release
rebuild-release: clean release

.PHONY: run
run:
	@build/debug/src/ProjectEuler

.PHONY: lldb
lldb:
	@lldb build/debug/src/ProjectEuler

.PHONY: gen-xcode
gen-xcode:
	@mkdir -p xcode
	@cd xcode && cmake ../ -G Xcode

.PHONY: lldb-release
lldb-release:
	@lldb build/release/src/ProjectEuler

.PHONY: run-release
run-release:
	@build/release/src/ProjectEuler

.PHONY: clean
clean:
	@rm -rf build/debug/*
	@rm -rf build/release/*
