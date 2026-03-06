objs = main.o chess.o doubly_linked_list.o dll_test.o \
       merge_sort.o array.o

main: $(objs)
	gcc -std=gnu99 -Wall -pedantic-errors -Wpedantic $(objs) -o main

main.o: chess.h
chess.o: chess.h
doubly_linked_list.o: doubly_linked_list.h
dll_test.o: dll_test.h
merge_sort.o: merge_sort.h
array.o: array.h

.PHONY: clean
	rm -r main $(objs)


