#include <stdlib.h>
#include "../include/hash.h"
#include "../../Resources/C/Unity/unity.h"

static int *int_to_pointer (int n) {
    int *res = (int*)malloc(sizeof(int));
    *res = n;
    return res;
}

static int hash_function(int *key) {
  return *key;
}

static int compare_key(int* obj1, int* obj2) {
    return *obj1 == *obj2;
}

static void hashmap_create_empty() {
    HashMap* map = HashMap_new((HashFunction) hash_function, (KeyCompare) compare_key);
    TEST_ASSERT_EQUAL(1, HashMap_is_empty(map));
    HashMap_free(map);
}

static void hashmap_create_empty_with_capacity() {
    HashMap* map = HashMap_new_with_capacity((HashFunction) hash_function, (KeyCompare) compare_key, 128);
    TEST_ASSERT_EQUAL(HashMap_size(map), 0);
    TEST_ASSERT_EQUAL(HashMap_capacity(map), 128);
    HashMap_free(map);
}

static void hashmap_insert() {
    HashMap* map = HashMap_new((HashFunction) hash_function, (KeyCompare) compare_key);
    HashMap_insert(map, (void*)int_to_pointer(1), (void*)int_to_pointer(10));
    TEST_ASSERT_EQUAL (1,HashMap_size(map));
    HashMap_free(map);
}

static void hashmap_insert_existing_value() {
    HashMap* map = HashMap_new_with_capacity((HashFunction) hash_function, (KeyCompare) compare_key, 4);
    HashMap_insert(map, (void*)int_to_pointer(1), (void*) int_to_pointer(30));
    HashMap_insert(map, (void*)int_to_pointer(2), (void*) int_to_pointer(75));
    HashMap_insert(map, (void*)int_to_pointer(3), (void*) int_to_pointer(12));
    HashMap_insert(map, (void*)int_to_pointer(2), (void*) int_to_pointer(35));
    TEST_ASSERT_EQUAL (35,*((int*) HashMap_get(map, (void*) int_to_pointer(2))));
    HashMap_free(map);
}

static void hashmap_get_existing_value() {
    HashMap* map = HashMap_new((HashFunction) hash_function, (KeyCompare) compare_key);
    HashMap_insert(map, (void*)int_to_pointer(1), (void*) int_to_pointer(30));
    HashMap_insert(map, (void*)int_to_pointer(2), (void*) int_to_pointer(75));
    HashMap_insert(map, (void*)int_to_pointer(3), (void*) int_to_pointer(12));
    TEST_ASSERT_EQUAL (75, *((int*) HashMap_get(map, (void*) int_to_pointer(2))));
    HashMap_free(map);
}

static void hashmap_get_non_existing_value() {
    HashMap* map = HashMap_new((HashFunction) hash_function, (KeyCompare) compare_key);
    HashMap_insert(map, (void*)int_to_pointer(1), (void*) int_to_pointer(30));
    HashMap_insert(map, (void*)int_to_pointer(2), (void*) int_to_pointer(75));
    HashMap_insert(map, (void*)int_to_pointer(3), (void*) int_to_pointer(12));
    TEST_ASSERT_EQUAL (NULL, HashMap_get(map, (void*) int_to_pointer(10)));
    HashMap_free(map);
}

static void hashmap_remove_existing_value() {
    HashMap* map = HashMap_new((HashFunction) hash_function, (KeyCompare) compare_key);
    HashMap_insert(map, (void*)int_to_pointer(1), (void*) int_to_pointer(30));
    HashMap_insert(map, (void*)int_to_pointer(2), (void*) int_to_pointer(75));
    HashMap_insert(map, (void*)int_to_pointer(3), (void*) int_to_pointer(12));
    TEST_ASSERT_EQUAL (75, *((int*) HashMap_remove(map, (void*)int_to_pointer(2))));
    HashMap_free(map);
}

static void hashmap_remove_non_existing_value() {
    HashMap* map = HashMap_new((HashFunction) hash_function, (KeyCompare) compare_key);
    HashMap_insert(map, (void*)int_to_pointer(1), (void*) int_to_pointer(30));
    HashMap_insert(map, (void*)int_to_pointer(2), (void*) int_to_pointer(75));
    HashMap_insert(map, (void*)int_to_pointer(3), (void*) int_to_pointer(12));

    TEST_ASSERT_EQUAL (1, HashMap_contains(map, (void*)int_to_pointer(2)));
    HashMap_free(map);
}

static void hashmap_contains_existing_value() {
    HashMap* map = HashMap_new((HashFunction) hash_function, (KeyCompare) compare_key);
    HashMap_insert(map, (void*)int_to_pointer(1), (void*) int_to_pointer(30));
    HashMap_insert(map, (void*)int_to_pointer(2), (void*) int_to_pointer(75));
    HashMap_insert(map, (void*)int_to_pointer(3), (void*) int_to_pointer(12));

    TEST_ASSERT_EQUAL (1, HashMap_contains(map, (void*)int_to_pointer(2)));
    HashMap_free(map);
}

static void hashmap_contains_non_existing_value() {
    HashMap* map = HashMap_new((HashFunction) hash_function, (KeyCompare) compare_key);
    HashMap_insert(map, (void*)int_to_pointer(1), (void*) int_to_pointer(30));
    HashMap_insert(map, (void*)int_to_pointer(2), (void*) int_to_pointer(75));
    HashMap_insert(map, (void*)int_to_pointer(3), (void*) int_to_pointer(12));

    TEST_ASSERT_EQUAL (0, HashMap_contains(map, (void*)int_to_pointer(5)));
    HashMap_free(map);
}

static void hashmap_clear() {
    HashMap* map = HashMap_new((HashFunction) hash_function, (KeyCompare) compare_key);
    HashMap_insert(map, (void*)int_to_pointer(1), (void*) int_to_pointer(30));
    HashMap_insert(map, (void*)int_to_pointer(2), (void*) int_to_pointer(75));
    HashMap_insert(map, (void*)int_to_pointer(3), (void*) int_to_pointer(12));
    HashMap_clear(map);
    TEST_ASSERT_EQUAL(0, HashMap_size(map));
    HashMap_free(map);
}

static void hashmap_clear_empty() {
    HashMap* map = HashMap_new((HashFunction) hash_function, (KeyCompare) compare_key);
    HashMap_clear(map);
    TEST_ASSERT_EQUAL(0, HashMap_size(map));
    HashMap_free(map);
}

static void hashmap_get_keys() {
    HashMap* map = HashMap_new((HashFunction) hash_function, (KeyCompare) compare_key);
    HashMap_insert(map, (void*)int_to_pointer(1), (void*) int_to_pointer(30));
    HashMap_insert(map, (void*)int_to_pointer(2), (void*) int_to_pointer(75));
    HashMap_insert(map, (void*)int_to_pointer(3), (void*) int_to_pointer(12));
    int** keys = (int**)HashMap_get_keys(map);
    int key_ref[3] = {1, 2, 3};
    
    int i, j, result;
    for(i = 0; i < 3; i++) {
        result = 0;
        for(j = 0; j < HashMap_size(map); j++) {
            if(key_ref[i] == *keys[j])
                result = 1;
            else 
                result = 0;
        }
    }

    TEST_ASSERT_EQUAL(result, 1);
    free(keys);
    HashMap_free(map);
}

static void hashmap_get_keys_empty_hashmap() {
    HashMap* map = HashMap_new((HashFunction) hash_function, (KeyCompare) compare_key);
    int** keys = (int**)HashMap_get_keys(map);
    TEST_ASSERT_EQUAL(NULL, keys);
}

static void hash_map_rehash_insert () {
    HashMap* map = HashMap_new_with_capacity((HashFunction) hash_function, (KeyCompare) compare_key,10);
    HashMap_insert(map, (void*)int_to_pointer(1), (void*) int_to_pointer(30));
    HashMap_insert(map, (void*)int_to_pointer(2), (void*) int_to_pointer(75));
    HashMap_insert(map, (void*)int_to_pointer(3), (void*) int_to_pointer(12));
    HashMap_insert(map, (void*)int_to_pointer(4), (void*) int_to_pointer(22));
    HashMap_insert(map, (void*)int_to_pointer(5), (void*) int_to_pointer(51));
    HashMap_insert(map, (void*)int_to_pointer(6), (void*) int_to_pointer(98));
    HashMap_insert(map, (void*)int_to_pointer(7), (void*) int_to_pointer(65));
    HashMap_insert(map, (void*)int_to_pointer(8), (void*) int_to_pointer(88));
    int capacity_new = HashMap_capacity(map);

    TEST_ASSERT_EQUAL(20, capacity_new);
    HashMap_free(map);
}

static void hash_map_rehash_remove() {
    HashMap* map = HashMap_new_with_capacity((HashFunction) hash_function, (KeyCompare) compare_key,10);
    HashMap_insert(map, (void*)int_to_pointer(1), (void*) int_to_pointer(30));
    HashMap_insert(map, (void*)int_to_pointer(2), (void*) int_to_pointer(75));
    HashMap_insert(map, (void*)int_to_pointer(3), (void*) int_to_pointer(12));
    HashMap_insert(map, (void*)int_to_pointer(4), (void*) int_to_pointer(22));
    HashMap_insert(map, (void*)int_to_pointer(5), (void*) int_to_pointer(51));

    HashMap_remove(map, (void*)int_to_pointer(1));
    HashMap_remove(map, (void*)int_to_pointer(2));
    HashMap_remove(map, (void*)int_to_pointer(3));

    int capacity_new = HashMap_capacity(map);

    TEST_ASSERT_EQUAL(5, capacity_new);
    HashMap_free(map);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(hashmap_create_empty);
    RUN_TEST(hashmap_create_empty_with_capacity);
    RUN_TEST(hashmap_insert);
    RUN_TEST(hashmap_insert_existing_value);
    RUN_TEST(hashmap_get_existing_value);
    RUN_TEST(hashmap_get_non_existing_value);
    RUN_TEST(hashmap_remove_existing_value);
    RUN_TEST(hashmap_remove_non_existing_value);
    RUN_TEST(hashmap_contains_existing_value);
    RUN_TEST(hashmap_contains_non_existing_value);
    RUN_TEST(hashmap_clear);
    RUN_TEST(hashmap_clear_empty);
    RUN_TEST(hashmap_get_keys);
    RUN_TEST(hashmap_get_keys_empty_hashmap);
    RUN_TEST(hash_map_rehash_insert);
    RUN_TEST(hash_map_rehash_remove);
    UNITY_END();
}
