#Directory Macros
IDIR = ../include
ODIR = ./obj
SDIR = ./src
OUTDIR = ./output

#list of source files
SRC1 = $(SDIR)/Coordinate_eg.cpp ../$(SDIR)/coordinate.cpp
SRC2 = $(SDIR)/Find_phase.cpp

SRC = $(SRC1) $(SRC2)

#compiler macros
CC = g++
CFLAGS = -I $(IDIR) -Wall

all: $(SRC)
	$(CC) $(SRC1) $(CFLAGS) -o $(OUTDIR)/Coordinate_eg.out  
	$(CC) $(SRC2) $(CFLAGS) -o $(OUTDIR)/Find_phase.out

clean:
	-rm -f $(OUTDIR)/*.out

rebuild: clean all
	
