OBJ = compress.o decompr.o io.o main.o misc.o

squeeze : $(OBJ)
	cc $(OBJ) -o squeeze

$(OBJ) : squeeze.h

writetree : io.o writetree.o
	cc io.o writetree.o -o writetree 

writetree.o : squeeze.h

.PHONY : clean
clean : 
	rm -f *.o

.PHONY : all
all : clean squeeze writetree
