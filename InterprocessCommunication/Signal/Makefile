# THIS IS AN AUTOGENERATED FILE. DO NOT EDIT!
all: build/signal.exe
	@echo Run: build/signal.exe
	@echo
	@./build/signal.exe
build/signal.exe: build/ build/signal.o
	@echo Link: signal.exe
	@clang  build/*.o -o build/signal.exe
build/:
	@echo Create: build/
	@mkdir build/
build/signal.o: signal.c
	@echo Compile: signal.c
	@clang -std=c17 -D_DEFAULT_SOURCE  -c signal.c -o $@
clean:
	@echo Clean
	@rm -fr build
