#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "hash_map.h"

int main()
{
        list_node *buckets = (list_node *)malloc(16 * sizeof(list_node));
        list_node *entries = NULL;
        init_buckets(&buckets);

        printf("test setter ...\n");
        hsh_mp_set(&entries, &buckets, "apple", "red");
        hsh_mp_set(&entries, &buckets, "orange", "tangerine");
        hsh_mp_set(&entries, &buckets, "tengerine", "orange");
        hsh_mp_set(&entries, &buckets, "figs", "red violet");
        hsh_mp_set(&entries, &buckets, "guava", "light green");
        hsh_mp_set(&entries, &buckets, "banana", "yellow");
        hsh_mp_set(&entries, &buckets, "leaves", "green");
        hsh_mp_set(&entries, &buckets, "sky", "sky blue");
        hsh_mp_set(&entries, &buckets, "cellphone", "black");
        hsh_mp_set(&entries, &buckets, "GOD", "Jasper and Ruby");
        hsh_mp_set(&entries, &buckets, "Jesus Robe", "red");
        hsh_mp_set(&entries, &buckets, "angels", "white");
        hsh_mp_set(&entries, &buckets, "birch", "black and white");
        hsh_mp_set(&entries, &buckets, "demons", "dark"); 
        hsh_mp_set(&entries, &buckets, "ballpen", "blue");
        printf("setter test done \n\n"); 

        printf("test removes start ... \n");
        hsh_mp_remove(&entries, &buckets, "apple"); 
        hsh_mp_remove(&entries, &buckets, "demons"); 
        printf("test remove done \n\n"); 

        printf("test getter start \n");
        printf("GOD color is %s \n", (char *)hsh_mp_get(&buckets, "GOD")->data);
        printf("orange color is %s \n", (char *)hsh_mp_get(&buckets, "orange")->data);
        printf("figs color is  %s \n", (char *)hsh_mp_get(&buckets, "figs")->data);
        printf("leaves color is %s \n", (char *)hsh_mp_get(&buckets, "leaves")->data);
        printf("Jesus Robe color is %s \n", (char *)hsh_mp_get(&buckets, "Jesus Robe")->data);
        printf("banana color is %s \n", (char *)hsh_mp_get(&buckets, "banana")->data);
        printf("angels color is %s \n", (char *)hsh_mp_get(&buckets, "angels")->data);
        printf("birch color is %s \n", (char *)hsh_mp_get(&buckets, "birch")->data); 
        printf("ballpen color is %s \n", (char *)hsh_mp_get(&buckets, "ballpen")->data);
        printf("sky color is %s \n", (char *)hsh_mp_get(&buckets, "sky")->data);
        printf("getter done \n\n"); 

        printf("print buckets as linked list. \n");
        hsh_mp_pretty_print(&buckets);
        printf("end print buckets as linked list. \n\n");

        printf("print hash_map entries. \n");
        print_nodes_key_value(&entries);
        printf("end print hash_map entries. \n");
        
        hsh_mp_clear(&entries, &buckets);
        return 0;
}
