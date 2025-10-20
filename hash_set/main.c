#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "hash_set.h"

int main()
{
        list_node *buckets = (list_node *)malloc(16 * sizeof(list_node));
        list_node *keys = NULL;
        init_buckets(&buckets);

        printf("test setter ...\n");
        hash_set_add(&keys, &buckets, "1");
        hash_set_add(&keys, &buckets, "3");
        hash_set_add(&keys, &buckets, "4");
        hash_set_add(&keys, &buckets, "5");
        hash_set_add(&keys, &buckets, "7");
        hash_set_add(&keys, &buckets, "8");
        hash_set_add(&keys, &buckets, "9");
        hash_set_add(&keys, &buckets, "10");
        hash_set_add(&keys, &buckets, "2");
        hash_set_add(&keys, &buckets, "11");
        hash_set_add(&keys, &buckets, "12");
        hash_set_add(&keys, &buckets, "14");
        hash_set_add(&keys, &buckets, "23");
        hash_set_add(&keys, &buckets, "32423");
        hash_set_add(&keys, &buckets, "234234234"); 
        hash_set_add(&keys, &buckets, "98798723");
        hash_set_add(&keys, &buckets, "2472489");
        hash_set_add(&keys, &buckets, "342");
        hash_set_add(&keys, &buckets, "3342");
        printf("setter test done \n\n"); 

        printf("test removes start ... \n");
        hash_set_remove(&keys, &buckets, "7"); 
        hash_set_remove(&keys, &buckets, "11"); 
        printf("test remove done \n\n"); 

        printf("test getter start \n");
        printf("%s \n", hash_set_get(&buckets, "14")->key);
        printf("%s \n", hash_set_get(&buckets, "12")->key);
        printf("%s \n", hash_set_get(&buckets, "23")->key);
        printf("%s \n", hash_set_get(&buckets, "32423")->key);
        printf("%s \n", hash_set_get(&buckets, "342")->key);
        printf("%s \n", hash_set_get(&buckets, "10")->key);
        printf("%s \n", hash_set_get(&buckets, "1")->key);
        printf("%s \n", hash_set_get(&buckets, "3")->key);
        printf("%s \n", hash_set_get(&buckets, "4")->key);
        printf("%s \n", hash_set_get(&buckets, "2")->key ? "no number" : "Yes meron");
        printf("getter done \n\n"); 

        printf("print buckets as linked list. \n");
        hash_set_pretty_print(&buckets);
        printf("end print buckets as linked list. \n\n");

        printf("print hash_map keys. \n");
        print_nodes_key(&keys);
        printf("end print hash_map keys. \n");
        
        hash_set_clear(&keys, &buckets);
        return 0;
}
