CFLAGS=-g -O0 -I include -I ../Resources/C/Unity/

all: bin/hash_test bin/es03_app

clean: 
	$(RM) -rf bin/*
	$(RM) -rf build/*

bin/es03_app: app/es03_app.c build/hash.o include/hash.h build/sorter.o include/sorter.h
	$(CC) $(CFLAGS) -o bin/es03_app build/hash.o build/sorter.o app/es03_app.c

build/sorter.o: src/sorter.c include/sorter.h
	$(CC) $(CFLAGS) -c src/sorter.c -o build/sorter.o

build/hash.o: src/hash.c include/hash.h
	$(CC) $(CFLAGS) -c src/hash.c -o build/hash.o

bin/hash_test: test/hash_test.c build/hash.o include/hash.h
	$(CC) $(CFLAGS) test/hash_test.c build/hash.o ../Resources/C/Unity/unity.c -o bin/hash_test