#pragma once

typedef struct _Entry Entry;
typedef struct _HashMap HashMap;

typedef int (*HashFunction)(void*);
typedef int (*KeyCompare)(void*, void*);

/**
 * Create a new hash map with default capacity
 * Param:
 *  - hash_function: hash function that allow to map entries
 *  - cmp: pointer to function that execute key comparison
 * Return:
 *  - pointer to hash map structure
 */ 
HashMap* HashMap_new (HashFunction hash_function, KeyCompare cmp);

/**
 * Create a new hash map with fixed capacity
 * Param:
 *  - hash_function : hash function that allow to map entries
 *  - cmp : pointer to function that execute key comparison
 *  - capacity: capacity of hash map
 * Return:
 *  - pointer to hash map structure
 */
HashMap* HashMap_new_with_capacity (HashFunction hash_function, KeyCompare cmp, int capacity);

/**
 * Delete entire hash map
 * Param:
 *  - map: pointer to hash map structure
 */
void HashMap_free (HashMap* map);  // FATTO

/**
 * Verify if hash map containe not-null entries
 * Param:
 *  - map: pointer to hash map structure
 * Return
 *  - value: 1 if hashmap size is 0, 0 otherwise
 */
int HashMap_is_empty (HashMap* map); 

/**
 * Return hash map size (number of not-null entries)
 * Param:
 *  - map: pointer to hash map structure
 * Return:
 *  - size: size of map
 */
int HashMap_size (HashMap* map);

/**
 * Return hash map capacity
 * Param:
 *  - map: pointer to hash map structure
 * Return:
 *  - capacity: capacity of map
 */
int HashMap_capacity (HashMap* map);

/**
 * Clear all entries of hash map
 * Param:
 *  - map: pointer to hash map structure
 */
void HashMap_clear (HashMap* map);

/**
 * Verify if hash map contains specific key
 * Param:
 *  - map: pointer to hash map structure
 *  - key: entry key
 * Return:
 *  - 1 if hash map contains key, 0 otherwise
 */
int HashMap_contains (HashMap* map, void* key);

/**
 * Insert an entry in hash map
 * Param:
 *  - map: pointer to hash map structure
 *  - key: entry key
 *  - value: entry value
 */
void HashMap_insert (HashMap* map, void* key, void* value);

/**
 * Return entry given key
 * Param:
 *  - map: pointer to hash map structure
 *  - key: entry key
 * Return:
 *  - entry
 */
void* HashMap_get (HashMap* map, void* key);

/**
 * Remove specific entry from hash map
 * Param:
 *  - map: pointer to hash map structure
 *  - key: entry key
 * Return:
 *   - result: deleted entry's value
 */
void* HashMap_remove (HashMap* map, void* key);

/**
 * Return all hashmap key's entries. Returns NULL if hashmap is empty
 * Param:
 *  - map: pointer to hash map structure
 * Return:
 *  - array of pointers to all key's entries of hash map
 */
void** HashMap_get_keys (HashMap* map);