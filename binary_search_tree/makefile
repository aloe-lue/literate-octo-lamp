objects = main.o queue_linked_list.o linked_list.o merge_sort.o \
	  binary_search_tree.o hash_set.o

main: $(objects)
	cc -o main $(objects)

main.o : queue_linked_list.h
queue_linked_list.o : queue_linked_list.h
linked_list.o : linked_list.h
merge_sort.o : merge_sort.h
binary_search_tree.o : binary_search_tree.h
hash_set.o : hash_set.h

.PHONY : clean
clean :
	-rm main $(objects)


