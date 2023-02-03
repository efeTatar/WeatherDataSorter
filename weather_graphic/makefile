EXO : exe

saves/sorter.o : sources/sorter.c sources/sorter.h
	gcc -c $< -o $@

saves/main.o : sources/main.c sources/sorter.h
	gcc -c $< -o $@

exe : saves/sorter.o saves/main.o
	gcc  $^ -o $@

clean:
	rm -f saves/*.o
	rm exe
	
shell:
	chmod +x data_filter.sh
	chmod +x exe
