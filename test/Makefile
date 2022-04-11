CC=gcc
Val=valgrind
Flags=-g -ggdb -Wall -std=c11 -pedantic
MemFlags=--leak-check=full
CallgrindFlags=--tool=callgrind
StrDup=-D_XOPEN_SOURCE=700
Format=astyle --options=./doc/apache.ini

# Format
format: ./*.c ./*.h
	astyle  --style=gnu --indent=spaces=4 --delete-empty-lines --break-blocks $^
	rm -f *.orig


# Hash_table

hash_table: ../src/hash_table.c ../src/linked_list.c
	$(CC) $(Flags) $^ -o $@


hash_tests: ../src/hash_table.c ../src/hash_table_tests.c ../src/linked_list.c
	$(CC) $(Flags) $^ -o $@ -lcunit

## Hash_table testing

hash_testing: ../src/hash_table.c ../src/linked_list.c hash_testing.c
	$(CC) $(Flags) $^ -o $@

# Linked list

linked_list: linked_list_tests.c
	$(CC) $(Flags) $^ -o $@


linked_tests: linked_list.c linked_list_tests.c
	$(CC) $(Flags) $^ -o $@ -lcunit


linked_mem_test: linked_list.c linked_list_tests.c
	$(Val) $(MemFlags) ./linked_tests



# Iterator

iterator: iterator.c
	$(CC) $(Flags) $^ -o $@


iterator_tests: iterator.c iterator_tests.c linked_list.c
	$(CC) $(Flags) $^ -o $@ -lcunit


iterator_mem_test: iterator.c iterator_tests.c
	$(Val) $(MemFlags) ./iterator_tests

#Clear

clear:
	rm -f *.o
	rm -f hash_table hash_table_tests linked_list linked_tests iterator iterator_tests freq




.PHONY: test clean mem_test
