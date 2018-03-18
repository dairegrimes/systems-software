CC = gcc
objects = main.o backup.o date.o transfer.o file_locking.o fileAudit.o client.o
headers = backup.h date.h transfer.h file_locking.h fileAudit.h client.h
files = main.c backup.c date.c transfer.c file_locking.c fileAudit.c client.c
name = p

p : $(objects)
	$(CC) -o $(name) $(objects) -lm -lrt

main.o : main.c $(headers) -lrt
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

client.o : client.c
	$(CC) -c client.c -lrt

clean:
	rm $(name) $(objects)
