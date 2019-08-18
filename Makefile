run: out
	./out

clean:
	rm out

out: main.c
	cc main.c -o out
