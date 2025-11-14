objs = main.o hash_set.o queue_linked_list.o knight_moves.o

main: $(objs)
	cc -o main $(objs)

main.o: knight_moves.h
hash_set.o: hash_set.h
queue_linked_list.o: queue_linked_list.h
knight_moves.o: knight_moves.h

.PHONY: clean
clean:
	-rm main $(objs)	
