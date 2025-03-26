#include <stdio.h>

typedef {
    char* key;
    char* value;
} Item;

typedef {
    int size;
    int count;
    Item** items;
} HashTable;

Item createNewItem(char* k, char* v){
    Item i = malloc(sizeof(Item));
    i->key = k;
    i->value = v;
    return i;
}

HashTable createNewHashTable(int s){
    HashTable* ht = malloc(sizeof(HashTable));

    ht->size = s;
    ht->count = 0;
    ht-> items = calloc((size_t)HashTable->size, sizeof(Item*));
    return ht;
}


int main(){
    printf("Hash table");
}