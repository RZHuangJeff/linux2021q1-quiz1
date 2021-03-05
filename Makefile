CFLAGS := -O1 -g

slist_test: slist_test.o slist.o prng.o
	gcc -o $@ $^

prng_test: randomness_test.o prng.o
	gcc -o $@ $^
	@./prng_test

perf_test: qsort_perf_test.o slist.o prng.o
	gcc -o $@ $^
	@./perf_test

llist_test: linux-list/quick-sort.o
	gcc -o $@ $^
	@./llist_test

*.o: *.c *.h
	gcc -o $@ $(CFLAGS) -c $<

clean:
	rm -f *.o slist_test prng_test perf_test linux-list/*.o llist_test