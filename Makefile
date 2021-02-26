CFLAGS := -O1 -g

slist_test: slist_test.o slist.o
	gcc -o $@ $^

*.o: *.c *.h
	gcc -o $@ $(CFLAGS) -c $<

clean:
	rm -f *.o slist_test