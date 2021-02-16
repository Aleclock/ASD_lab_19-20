CFLAGS=-g -O0 -I include -I ../Resources/C/Unity/

all: bin/insertion_sort_test bin/quick_sort_test bin/es01_app

clean: 
	$(RM) -rf bin/*
	$(RM) -rf build/*

build/sorter.o: src/sorter.c include/sorter.h
	$(CC) $(CFLAGS) -c src/sorter.c -o build/sorter.o

bin/es01_app: app/es01_app.c build/sorter.o include/sorter.h
	$(CC) $(CFLAGS) -o bin/es01_app build/sorter.o app/es01_app.c

bin/insertion_sort_test: test/insertion_sort_test.c build/sorter.o include/sorter.h
	$(CC) $(CFLAGS) test/insertion_sort_test.c build/sorter.o ../Resources/C/Unity/unity.c -o bin/insertion_sort_test
	
bin/quick_sort_test: test/quick_sort_test.c build/sorter.o include/sorter.h
	$(CC) $(CFLAGS) test/quick_sort_test.c build/sorter.o ../Resources/C/Unity/unity.c -o bin/quick_sort_test
