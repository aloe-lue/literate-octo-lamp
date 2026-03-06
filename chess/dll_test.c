#include "dll_test.h"
#include "doubly_linked_list.h"

void dll_test() 
{ 
	dlinked_list *dll = init_dlinked_list();

	enqueue_dnode_list(dll, "0");
	enqueue_dnode_list(dll, "1");
	enqueue_dnode_list(dll, "2");
	enqueue_dnode_list(dll, "3");
	enqueue_dnode_list(dll, "4");

	print_from_tail_dnodelist(dll);
	clear_dnode_lists(dll);
	print_from_tail_dnodelist(dll);
}
