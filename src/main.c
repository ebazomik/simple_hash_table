// This is a simple implementation of hash table for study purpose.
// Thanks James Routley https://github.com/jamesroutley?tab=overview&from=2024-12-01&to=2024-12-31 for its implementation.

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char* key;
    char* value;
} Item;

typedef struct {
    int size;
    int count;
    Item** items;
} HashTable;

Item* createNewItem(char* k, char* v){
    Item* i = malloc(sizeof(Item));
    i->key = k;
    i->value = v;
    return i;
}

HashTable* createNewHashTable(int s){
    HashTable* ht = malloc(sizeof(HashTable));

    ht->size = s;
    ht->count = 0;
    ht-> items = calloc((size_t)ht->size, sizeof(Item*));
    return ht;
}

void deleteItem(Item* i){
    free(i->key);
    free(i->value);
    free(i);
}

void deleteHashMap(HashTable* ht){
    for(int i = 0; i<ht->size; i++){
        Item* currentItem = ht->items[i];
        if(currentItem != NULL){
            deleteItem(currentItem);
        }
    }
    free(ht->items);
    free(ht);
}




int main(){
    HashTable* ht = createNewHashTable(50);
    deleteHashMap(ht);
}