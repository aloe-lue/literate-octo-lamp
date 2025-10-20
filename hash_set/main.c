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
        hash_set_add(&keys, &buckets, "apple");
        hash_set_add(&keys, &buckets, "orange");
        hash_set_add(&keys, &buckets, "tengerine");
        hash_set_add(&keys, &buckets, "figs");
        hash_set_add(&keys, &buckets, "guava");
        hash_set_add(&keys, &buckets, "banana");
        hash_set_add(&keys, &buckets, "leaves");
        hash_set_add(&keys, &buckets, "sky");
        hash_set_add(&keys, &buckets, "cellphone");
        hash_set_add(&keys, &buckets, "GOD");
        hash_set_add(&keys, &buckets, "Jesus");
        hash_set_add(&keys, &buckets, "Holy Spirit");
        hash_set_add(&keys, &buckets, "angels");
        hash_set_add(&keys, &buckets, "demons"); 
        hash_set_add(&keys, &buckets, "ballpen");
        hash_set_add(&keys, &buckets, "computer");
        hash_set_add(&keys, &buckets, "birch");
        hash_set_add(&keys, &buckets, "goth girl");
        printf("setter test done \n\n"); 

        printf("test removes start ... \n");
        hash_set_remove(&keys, &buckets, "apple"); 
        hash_set_remove(&keys, &buckets, "demons"); 
        printf("test remove done \n\n"); 

        printf("test getter start \n");
        printf("%s \n", hash_set_get(&buckets, "GOD")->key);
        printf("%s \n", hash_set_get(&buckets, "orange")->key);
        printf("%s \n", hash_set_get(&buckets, "figs")->key);
        printf("%s \n", hash_set_get(&buckets, "leaves")->key);
        printf("%s \n", hash_set_get(&buckets, "Jesus")->key);
        printf("%s \n", hash_set_get(&buckets, "banana")->key);
        printf("%s \n", hash_set_get(&buckets, "angels")->key);
        printf("%s \n", hash_set_get(&buckets, "birch")->key);
        printf("%s \n", hash_set_get(&buckets, "ballpen")->key);
        printf("%s \n", hash_set_get(&buckets, "sky")->key);
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
