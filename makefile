CC = gcc
objects = main.o backup.o date.o transfer.o file_locking.o fileAudit.o
headers = backup.h date.h transfer.h file_locking.h fileAudit.h
files = main.c backup.c date.c transfer.c file_locking.c fileAudit.c
name = p

p : $(objects)
	$(CC) -o $(name) $(objects) -lm

main.o : main.c $(headers)
	$(CC) -c main.c

backup.o : backup.c
	$(CC) -c backup.c

date.o : date.c
	$(CC) -c date.c

transfer.o : transfer.c
	$(CC) -c transfer.c

file_locking.o : file_locking.c
	$(CC) -c file_locking.c

fileAudit.o : fileAudit.c
	$(CC) -c fileAudit.c

clean:
	rm $(name) $(objects)
