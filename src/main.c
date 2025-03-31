// This is a simple implementation of hash table for study purpose.
// Thanks James Routley
// https://github.com/jamesroutley?tab=overview&from=2024-12-01&to=2024-12-31
// for its implementation.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *key;
  char *value;
} Item;

typedef struct {
  int size;
  int count;
  Item **items;
} HashTable;

Item *createNewItem(char *k, char *v) {
  Item *i = malloc(sizeof(Item));
  i->key = k;
  i->value = v;
  return i;
}

HashTable *createNewHashTable(int s) {
  HashTable *ht = malloc(sizeof(HashTable));

  ht->size = s;
  ht->count = 0;
  ht->items = calloc((size_t)ht->size, sizeof(Item *));
  return ht;
}

void deleteItem(Item *i) {
  free(i->key);
  free(i->value);
  free(i);
}

void deleteHashMap(HashTable *ht) {
  for (int i = 0; i < ht->size; i++) {
    Item *currentItem = ht->items[i];
    if (currentItem != NULL) {
      deleteItem(currentItem);
    }
  }
  free(ht->items);
  free(ht);
}

// This simple hash function uses the prime number 31 and the size of the table
// to return a well-distributed integer based on tableSize.
// Why use prime number?
// In operations such as multiplication and modulo, prime numbers spread the
// bits more randomly and prevent collisions.
// *************************************************************************
// Example -> key = 'hello' and table size 101
// In this example the key[n] in int is:
// key[0] = 104;
// key[1] = 101;
// key[2] = 108;
// key[3] = 108;
// key[4] = 111;
// *************************************************************************
// key[0] -> 0 * 31 + 104 % 101 = 3
// key[1] -> 3 * 31 + 101 % 101 = 93
// key[2] -> 93 * 31 + 108 % 101 = 62
// key[3] -> 62 * 31 + 108 % 101 = 10
// key[4] -> 10 * 31 + 111 % 101 = 17
// hash = 17
int hashFunction(const char *key, unsigned int tableSize) {
  int hash = 0;
  for (unsigned int i = 0; i < strlen(key); i++) {
    hash = (hash * 31 + key[i]) % tableSize;
  }
  return hash;
}

// Calculate hash with double hashing (open addressing)
int getHashWithPreventCollision(const char *key, const HashTable *ht,
                                const int attempt) {
  int index = 0;
  unsigned int tableSize = ht->size;
  index = hashFunction(key, tableSize) +
          (attempt * hashFunction(key, tableSize)) % tableSize;
  return index;
}

int insertItem(HashTable *ht, char *key, char *value) {
  Item *newItem = createNewItem(key, value);
  int hash = getHashWithPreventCollision(key, ht, 0);
  Item *item = ht->items[hash];
  if (item == NULL) {
    ht->items[hash] = newItem;
    ht->count++;
    return 0;
  }
  return 1;
}

char *search(HashTable *ht, char *key) {
  int hash = getHashWithPreventCollision(key, ht, 0);
  Item *item = ht->items[hash];
  if (item != NULL) {
    if (strcmp(item->key, ht->items[hash]->key) == 0) {
      return item->value;
    }
    // if item != NULL but keys are different?
  }
  return NULL;
}

void removeItem(HashTable *ht, char *key) {
  int hash = getHashWithPreventCollision(key, ht, 0);
  Item *item = ht->items[hash];
  if (strcmp(item->key, key) == 0) {
    deleteItem(item);
    ht->count--;
  }
}

int main(int argc, char *argv[]) {
  int tableSize = 101;
  HashTable *ht = createNewHashTable(tableSize);

  printf("Item to insert is -> { %s, %s } \n", argv[1], argv[2]);

  int insert = insertItem(ht, argv[1], argv[2]);
  char *value = search(ht, argv[1]);
  printf("Value insert is -> %s \n", value);

  removeItem(ht, argv[1]);
  char *value1AfterDelete = search(ht, argv[1]);
  printf("Value searched after delete is -> %s \n", value1AfterDelete);

  deleteHashMap(ht);
}