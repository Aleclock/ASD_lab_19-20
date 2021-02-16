#include "hash.h"
#include "sorter.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ERROR_EXIT_CODE 1
#define SIZE 6321078 //file rows
#define ARRAY_KEYS_SIZE 10000000

typedef struct{
  int hash_function;
  char const *filename;
} Options;

typedef struct {
    int key;
    int value;
} ArrayAss;

static int compare_key(int* obj1, int* obj2) {
    return *obj1 == *obj2;
}

static int compare_array(ArrayAss* k1,ArrayAss* k2) {
    return (k1->key)-(k2->key);
}

static int hash_function(int* key) {
    return *key%SIZE;
}

static int *int_to_pointer (int n) {
    int *res = (int*)malloc(sizeof(int));
    *res = n;
    return res;
}

int binarySearch (ArrayAss** array, int value, int start, int end) {
  if (start > end)
    return -1;
  int m = (start + end)/2;
  if (array[m]->key == value)
    return array[m]->value;
  else if (value < array[m]->key)
    return binarySearch (array, value, start, m-1);
  else
    return binarySearch (array, value, m+1, end);
}

void print_usage() {
  printf("es03_app <filename> \n");
}

Options parse_options(int argc, char const *argv[]) {
  if (argc != 2) {
    printf("Parameters error\n");
        print_usage();
        exit(ERROR_EXIT_CODE);
  }
  Options options;
  options.filename = argv[1];
  return options;
}

void load_data_hashmap (HashMap* map, char const* filename) {
  if (map == NULL) {
    printf ("Map is null");
    return;
  }

  FILE* file = fopen(filename, "r");
  if(file != NULL){
    int  key, value;
    int lineno = 0;
    while(!feof(file)) {
      int n = fscanf(file, "%d,%d\n", &key, &value);
      lineno++;
      
      if(n != 2) {
        if(feof(file)) {
          continue;
        }
        printf("Error while reading file at line: %d\n", lineno);
        exit(ERROR_EXIT_CODE);
      }
      HashMap_insert(map, int_to_pointer(key),int_to_pointer(value));
      
    }
    
    fclose(file);
  } else {
    printf("File doesn't exixt\n");
    exit(ERROR_EXIT_CODE);
  }
}

void load_data_array_structure (ArrayAss** array, char const* filename) {
  if (array == NULL) {
    printf ("Map is null");
    return;
  }

  FILE* file = fopen(filename, "r");
  if(file != NULL){
    int  key, value;
    int lineno = 0;
    while(!feof(file)) {
      ArrayAss* association = (ArrayAss*)malloc(sizeof(ArrayAss));
      int n = fscanf(file, "%d,%d\n", &key, &value);

      if(n != 2) {
        if(feof(file)) {
          continue;
        }
        printf("Error while reading file at line: %d\n", lineno);
        exit(ERROR_EXIT_CODE);
      }

      association->key = key;
      association->value = value;
      array[lineno] = association;
      lineno++;
    }
    
    fclose(file);
  } else {
    printf("File doesn't exixt\n");
    exit(ERROR_EXIT_CODE);
  }
}

void create_array_keys (int* keys, int size) {
  for (int i = 0; i < size; i++) {
    keys[i] = rand() % (size + 1);
  }
}

int retrieve_hash_keys (HashMap* map, int* keys) {
  int found = 0;
  for (int i = 0; i < ARRAY_KEYS_SIZE; i++) {
      if (HashMap_get(map,&keys[i]) != NULL) {
        found ++;
      }
  }
  return found;
}

int retrieve_array_keys (ArrayAss** array, int* keys) {
  int found = 0;
  for (int i = 0; i < ARRAY_KEYS_SIZE; i++) {
    if (binarySearch(array, keys[i], 0, SIZE-1) != -1) {
      found ++;
    }
  }
  return found;
}

// bin/es03_app hashes.csv 
// bin/es03_app hashes_prova.csv
int main(int argc, char const *argv[]) {
  clock_t begin, end;

  Options options = parse_options(argc, argv);
  // TODO neeed to add rehash, otherwise goes to seg fault
  HashMap* map = HashMap_new_with_capacity((HashFunction)hash_function, (KeyCompare) compare_key, SIZE);
  ArrayAss** array = (ArrayAss**)malloc(sizeof(ArrayAss*)*SIZE);

  printf ("\nLoading data into hash map\n");
  begin = clock();
  load_data_hashmap(map, options.filename);
  end = clock();
  printf("\tCOMPLETED:\tRequired time %f seconds\n", ((double)end-begin)/CLOCKS_PER_SEC);

  printf ("\nLoading data into array\n");
  begin = clock();
  load_data_array_structure(array, options.filename);
  end = clock();
  printf("\tCOMPLETED:\tRequired time %f seconds\n", ((double)end-begin)/CLOCKS_PER_SEC);

  printf("\nSorting array data\n");
  begin = clock();
  quick_sort((void**) array, 0, SIZE, (CompareFunction)compare_array, 1);
  end = clock();
  printf("\tCOMPLETED:\tRequired time %f seconds\n", ((double)end-begin)/CLOCKS_PER_SEC);

  printf ("\nCreating random keys array\n");
  begin = clock();
  int* keys = (int*) malloc(sizeof(int) * ARRAY_KEYS_SIZE);
  create_array_keys(keys, ARRAY_KEYS_SIZE);
  end = clock();
  printf("\tCOMPLETED:\tRequired time %f seconds\n", ((double)end-begin)/CLOCKS_PER_SEC);

  printf ("\nRetrieving keys from hash map\n");
  begin = clock();
  int found_hash_map = retrieve_hash_keys (map, keys);
  end = clock();
  printf("\tCOMPLETED:\tRequired time %f seconds\n", ((double)end-begin)/CLOCKS_PER_SEC);
  printf("\tRetrieved %d keys\n", found_hash_map);

  printf ("\nRetrieving keys from array\n");
  begin = clock();
  int found_array = retrieve_array_keys (array, keys);
  end = clock();
  printf("\tCOMPLETED:\tRequired time %f seconds\n", ((double)end-begin)/CLOCKS_PER_SEC);
  printf("\tRetrieved %d keys\n", found_array);
}