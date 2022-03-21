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

hash_table: hash_table.c linked_list.c
	$(CC) $(Flags) $^ -o $@


hash_tests: hash_table.c hash_table_tests.c linked_list.c
	$(CC) $(Flags) $^ -o $@ -lcunit


hash_mem_test: hash_table.c hash_table_tests.c linked_list.c
	$(Val) $(MemFlags) ./hash_tests



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

# Freq
freq: freq-count.c linked_list.c hash_table.c
	$(CC) $(Flags) -pg $(StrDup) $^ -o $@

freq_mem_test_10k: freq-count.c linked_list.c hash_table.c
	$(val) $(CallgrindFlags) ./freq ./10k-words.txt

freq_mem_test_16k: freq-count.c linked_list.c hash_table.c
	$(val) $(CallgrindFlags) ./freq ./16k-words.txt

freq_mem_test_small: freq-count.c linked_list.c hash_table.c
	$(val) $(CallgrindFlags) ./freq ./small.txt





# Tests

test: hash_tests linked_tests iterator_tests
	./hash_tests 
	./linked_tests 
	./iterator_tests



mem_test: hash_mem_test linked_mem_test iterator_mem_test
	$(Val) $(MemFlags) ./hash_tests
	$(Val) $(MemFlags) ./linked_tests
	$(Val) $(MemFlags) ./iterator_tests



#Clear

clear:
	rm -f *.o
	rm -f hash_table hash_table_tests linked_list linked_tests iterator iterator_tests freq




.PHONY: test clean mem_test
