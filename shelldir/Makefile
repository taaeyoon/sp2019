CC = gcc
STRIP = strip

SRC1 = main
SRC2 = loop
SRC3 = tokenNexecute
SRC4 = builtin
TARGET = shell

all : $(TARGET)

$(TARGET) : $(SRC1).o $(SRC2).o $(SRC3).o $(SRC4).o
	    $(CC) -o $(TARGET) $(SRC1).o $(SRC2).o $(SRC3).o $(SRC4).o
	    $(STRIP) $(TARGET)

$(SRC1).o : $(SRC1).c
	$(CC) -c $(SRC1).c

$(SRC2).o : $(SRC2).c
	$(CC) -c $(SRC2).c

$(SRC3).o : $(SRC3).c
	$(CC) -c $(SRC3).c

$(SRC4).o : $(SRC4).c
	$(CC) -c $(SRC4).c

clean :
	rm -f *.o $(TARGET)
