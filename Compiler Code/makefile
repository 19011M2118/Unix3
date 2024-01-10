all:
	bison -y -d lexyacc-code/calc3.y --output=lexyacc-code/y.tab.c
	flex  -o lexyacc-code/lex.yy.c lexyacc-code/calc3.l
	gcc -c lexyacc-code/lex.yy.c -o bin/lex.yy.o
	gcc -c lexyacc-code/y.tab.c -o bin/y.tab.o	
	gcc bin/y.tab.o bin/lex.yy.o lexyacc-code/calc3a.c -o bin/calc3a.exe
	gcc bin/y.tab.o bin/lex.yy.o lexyacc-code/calc3b.c -o bin/calc3b.exe
	gcc bin/y.tab.o bin/lex.yy.o lexyacc-code/calc3g.c -o bin/calc3g.exe
	gcc bin/y.tab.o bin/lex.yy.o lexyacc-code/calc3i.c -o bin/calc3i.exe
clean:
	rm -rf  bin/calc3a.exe  bin/calc3b.exe  bin/calc3g.exe  bin/calc3i.exe  bin/calc3itest.exe
	rm -rf bin/*.o
	rm -rf lexyacc-code/y.tab.c
	rm -rf lexyacc-code/lex.yy.c
	rm -f *.s
	rm -f *.o
	rm -f *.exe

