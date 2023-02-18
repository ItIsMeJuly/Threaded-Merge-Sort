CXXFLAGS=-Wall -Werror -Wextra -O0 -ggdb -Icode -std=c++17
LDDFLAGS=-lpthread

SOURCES=code/main.cpp \
		code/FileStructure.cpp \
		code/List.cpp \
		code/Log.cpp \
		code/Value.cpp

CC=g++

.phony: all clean run klocwork klocwork_after_makefile_change

all: sort

sort: $(SOURCES) Makefile
	$(CC) $(CXXFLAGS) $(SOURCES) -o $@ $(LDDFLAGS)
	
clean:
	@rm -rf sort* trace.txt debug.txt
	@rm -rf kwinject.out .kwlp .kwps

run: sort
	@./sort

klocwork:
	kwcheck run

klocwork_after_makefile_change: clean
	@/opt/klocwork/kwenv.sh
	@kwcheck run
