#include "sorter.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ERROR_EXIT_CODE 1
#define MAX_BUF_LEN 1024
#define ASCENDING -1

typedef struct {
    void** array;
    int size;
} SortedArray;

typedef struct {
    int id;
    char* field1;
    int field2;
    float field3;
} Record;

typedef struct {
    CompareFunction comparison_fun;
    int alg;
    char const* filename;
} Options;

static int size;


int compare_string(Record* r1, Record* r2) {
    return strcmp(r1->field1, r2->field1);
}

int compare_int(Record* r1, Record* r2) {
    return r1->field2 - r2->field2;
}

int compare_float(Record* r1, Record* r2) {
    return r1->field3 - r2->field3;
}

// TODO modify prinf usage
void print_usage(){
    printf("es01_app <-i | -q> <-1 | -2 | -3> <filename>\n");
    printf("\t-i: sort using Insertion-Sort algorithm\n");
    printf("\t-q: sort using Quick-Sort algorithm\n");
    printf("\t-1: sort according to the first field (type String)\n");
    printf("\t-2: sort according to the second field (type Int)\n");
    printf("\t-3: sort according to the third field (type Float)\n");
}

Options parse_options (int argc, char const *argv[]) {
    if(argc != 4 || strlen(argv[1]) != 2) {
        printf("Parameters error!\n");
        print_usage();
        exit(ERROR_EXIT_CODE);
    }

    Options options;

    // Algorithm method 
    if (!strcmp(argv[1], "-i")) {
        options.alg = 0;    // insertion sort
    } else if (!strcmp(argv[1], "-q")) {
        options.alg = 1;    // quick sort
    } else {
        printf("Algorithm parameter error\n");
        print_usage();
        exit(ERROR_EXIT_CODE);
    }

    // Column/field to sort
    if (!strcmp(argv[2], "-1")) {
        options.comparison_fun = (CompareFunction) compare_string;
    } else if (!strcmp(argv[2], "-2")) {
        options.comparison_fun = (CompareFunction) compare_int;
    } else if (!strcmp(argv[2], "-3")) { 
    options.comparison_fun = (CompareFunction) compare_float;
    } else {
        printf("Element parameter error\n");
        print_usage();
        exit(ERROR_EXIT_CODE);
    }

    // Data file
    options.filename = argv[3];

    return options;
}

Record** load_data(char const* filename, int* size) {
    FILE* file = fopen(filename, "r");

    int id, field2;
    char buf[MAX_BUF_LEN];
    float field3;
    int record_n = 0, lines = 0;

    if(file != NULL){
        while(!feof(file)){
            fgets(buf, 1024, file);
            lines++;
        }
        lines--;
        fseek(file, 0, SEEK_SET);

        Record** array = (Record**) malloc(sizeof(Record*) * lines);

        while(!feof(file)) {
            Record* record = (Record*) malloc(sizeof(Record));
            int n = fscanf(file,"%d,%[^,],%d,%f\n",&id, buf, &field2, &field3);
    
            if (n != 4) {
                if(feof(file)) {
                    continue;
                }
            
                printf ("Error while reading file at line: %d\n", record_n);
                exit(ERROR_EXIT_CODE);
            }

            record->id = id;
            record->field1 = strndup(buf, MAX_BUF_LEN);
            record->field2 = field2;
            record->field3 = field3;

            array[record_n] = record;
            record_n++;
        }
        *size = record_n;

        return array;
    } else {
        printf("File doesn't exixt\n");
        exit(ERROR_EXIT_CODE);
    }
}

void print_results(Record **array, int size) {
    for (int i = 0; i<size; i++) {
        printf("%5d\t, %10s\t, %5d\t, %3f\n", array[i]->id, array[i]->field1, array[i]->field2, array[i]->field3);
    }
}

void free_data(Record **array, int size) {
    for (int i = 0; i<size; i++) {
        free(array[i]->field1);
        free(array[i]);
    } 
    free(array);
}

// bin/es01_app -q -1 records.csv 
// bin/es01_app -q -1 records_10.csv
int main(int argc, char const *argv[]) {

    clock_t begin, end;

    Options options = parse_options(argc, argv);
    Record** array = load_data(options.filename, &size);

    switch(options.alg)
    {
        case 0:
            begin = clock();
            printf("Insertion sort\n");
            insertion_sort((void**) array, size, options.comparison_fun, ASCENDING);
            end = clock();
            break;
        case 1:
            begin = clock();
            printf("Quick sort\n");
            quick_sort((void**) array, 0, size, options.comparison_fun, ASCENDING);
            end = clock();
            break;
        default:
            printf("Something went wrong\n");
            exit(ERROR_EXIT_CODE);
            break;    
    }

    printf("\nSorting completed in: %f seconds\n", ((double)end-begin)/CLOCKS_PER_SEC);
    //print_results (array,size);
    //free_data(array,size);

    return 0;
}
