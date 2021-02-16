#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

#define HASHCAPACITY 1024 /*Standard HashMap Size*/

struct _Entry {
    void* key;
    void* value;
    struct _Entry *prev;
    struct _Entry *next;
};

struct _HashMap {
    struct _Entry **entry;
    int capacity;
    int size;
    HashFunction hash_function;
    KeyCompare cmpKey;
};

void print_hashmap(HashMap* map, int capacity) {
    Entry* temp;
    printf("Start\n");
    for (int i = 0; i < capacity; i++) {
        if (map->entry[i] != NULL){
            temp = map->entry[i];
            printf ("\t%i", i);
            while (temp != NULL) {
                printf("\tk:%d v:%d",(int)*((int*)temp->key),(int)*((int*)temp->value));
                temp = temp->next;
            }
        } else {
            printf ("\t%i\t----", i);
        }
        printf("\n");
    }
    printf("End\n");
}


void initialize_entries(HashMap* map) {
    for (int i = 0; i < map->capacity; i++) {
        map->entry[i] = NULL;
    }
}

void HashMap_rehash (HashMap* map, int capacity) {
    HashMap* new_map = (HashMap*)malloc(sizeof(HashMap));
    new_map->entry = (Entry**)malloc(sizeof(Entry*) * (map->capacity * 2));
    new_map->capacity = capacity;
    new_map->size = 0;
    new_map->hash_function = map->hash_function;
    new_map->cmpKey = map->cmpKey;
    
    initialize_entries(new_map);
    Entry* temp;
    for (int i = 0; i < map->capacity; i++) {
        temp = map->entry[i];
        while (temp != NULL) {
            HashMap_insert(new_map, temp->key, temp->value);
            temp = temp->next;
        }
    }

    free(map->entry);
    map->entry = new_map->entry;
    map->capacity = new_map->capacity;
    map->size = new_map ->size;
}

HashMap* HashMap_new (HashFunction hash_function, KeyCompare cmp) {
    if (hash_function == NULL || cmp == NULL) 
        return NULL;
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    map->entry = (Entry**)malloc(sizeof(Entry*) * HASHCAPACITY);
    map->capacity = HASHCAPACITY;
    initialize_entries(map);
    map->size = 0;
    map->hash_function = hash_function;
    map->cmpKey = cmp;
    return map;
}

HashMap* HashMap_new_with_capacity (HashFunction hash_function, KeyCompare cmp, int capacity) {
    if (hash_function == NULL || cmp == NULL || capacity <= NULL) {
        return NULL;
    }
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    map->entry = (Entry**)malloc(sizeof(Entry*) * capacity);
    map->capacity = capacity;
    initialize_entries(map);
    map->size = 0;
    map->hash_function = hash_function;
    map->cmpKey = cmp;
    return map;
} 

void HashMap_free (HashMap* map) {
    if (map != NULL) {
        for (int i = 0; i < map->capacity; i++) {
            free(map->entry[i]);
        }
        free(map->entry);
        free(map);
    }
}

int HashMap_is_empty (HashMap* map) {
    if (map != NULL) {
        return map->size == 0;
    }
    return 0;
}

int HashMap_size (HashMap* map) {
    if (map != NULL) {
        return map->size;
    }
    return 0;
}

int HashMap_capacity (HashMap* map) {
    if (map != NULL) {
        return map->capacity;
    }
    return 0;
}

void HashMap_clear (HashMap* map) {
    if (map != NULL) {
        for (int i = 0; i < map->capacity; i++) {
            free(map->entry[i]);
        }
        free(map->entry);
        map->entry = (Entry**)malloc(sizeof(Entry*) * map->capacity);
        initialize_entries(map);
        map->size = 0;
    }
}

int HashMap_contains (HashMap* map, void* key) {
    if (map != NULL) {
        int found = 0;
        int pos = map->hash_function(key);
        Entry* entries = map->entry[pos];
        if (entries != NULL) {
            while(entries != NULL && found == 0) {
                if(map->cmpKey(entries->key,key))
                    found = 1;
                entries = entries->next;
            }
        }
        return found;
    }
}

Entry* newEntry(void* key, void* value, Entry* next) {
    Entry* entry = (Entry*)malloc(sizeof(Entry));
    entry->key = key;
    entry->value = value;
    entry->prev = NULL;
    entry->next = (struct Entry*)next;
    return entry;
}

void HashMap_insert (HashMap* map, void* key, void* value) {
    if (map != NULL) {
        int pos = map->hash_function(key);
        if (map->entry[pos] == NULL) {
            map->entry[pos] = newEntry(key, value, NULL);
            map->size++;
        } else {  
            int found = 0;
            Entry* entries = map->entry[pos];  
            while(entries != NULL && found == 0) { 
                if (map->cmpKey(entries->key,key)) {
                    entries->value = value;
                    found = 1;
                }
                entries = entries->next;
            }
            if (found == 0) {
                Entry* temp = newEntry(key, value, map->entry[pos]);
                temp->prev = NULL;
                temp->key = key;
                temp->value = value;
                temp->next = map->entry[pos];
                map->entry[pos] = temp;
            }
        }

        if (map->size >= ((map->capacity) * 0.75)) {
            HashMap_rehash(map, map->capacity * 2);
        }
    }
}

void* HashMap_get (HashMap* map, void* key) {
    if (map != NULL) {
        void* result = NULL;
        int found = 0;
        int pos = map->hash_function(key);
        Entry* entries = map->entry[pos];
    
        while(entries != NULL && found == 0) { 
            if (map->cmpKey(entries->key,key)) {
                result = entries->value;
                found = 1;
            }
            entries = entries->next;
        }
        return result;
    }
}

void* HashMap_remove (HashMap* map, void* key) {
    if (map != NULL) {
        void* result = NULL;
        int found = 0;
        int pos = map->hash_function(key);
        Entry* entries = map->entry[pos];
        Entry* prev = NULL;
        if (entries != NULL) {
            while (entries != NULL && found == 0) {
                if (map->cmpKey(entries->key, key)) {
                    result = entries->value;
                    map->size -= 1;
                    found = 1;
                    if (prev != NULL)
                        prev->next = entries->next;
                    else
                        map->entry[pos] = entries->next; 
                    free(entries);
                } else {
                    prev = entries;
                    entries = entries->next;
                }
            }           
        }
        if (map->size <= ((map->capacity) * 0.25)) {
            HashMap_rehash(map, map->capacity / 2);
        }

        return result;
    }
}

void** HashMap_get_keys (HashMap* map) {
    void** keys = NULL;
    if(map != NULL && map->size > 0) {
        keys = (void**) malloc(sizeof(void*) * map->size);
        Entry* entry;
        int n = 0;
        for (int i = 0; i < map->capacity; i++) {
            entry= map->entry[i];
            while (entry != NULL) {
                keys[n] = entry->key;
                entry = entry->next;
                n++;
            }
        }
    }
    return keys;
}