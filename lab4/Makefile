all: lib1 lib2 main1 main2

main1:
	g++ first.cpp -L. -ld1 -o main1 -Wl,-rpath -Wl,.
main2:
	g++ second.cpp -L. -ld1 -ld2 -o main2 -Wl,-rpath -Wl,.
lib1:
	g++ -fPIC -c lib1.cpp -o d1.o
	g++ -shared d1.o -o libd1.so
lib2:
	g++ -fPIC -c lib2.cpp -o d2.o
	g++ -shared d2.o -o libd2.so
clear:
	rm -rf *.so *.o main1 main2