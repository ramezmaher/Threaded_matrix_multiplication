all:
	gcc header.h method1.c method2.c main.c -pthread -o matmultp