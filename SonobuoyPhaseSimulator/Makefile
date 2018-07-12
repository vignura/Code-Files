#Directory Macros
IDIR = ./include
ODIR = ./obj
SDIR = ./src
OUTDIR = ./output

#compiler macros
CC = g++
CFLAGS = -I $(IDIR) -Wall
HFILES = $(IDIR)/main.h $(IDIR)/sonobuoy.h $(IDIR)/coordinate.h $(IDIR)/antenna.h $(IDIR)/helicopter.h
OFILES = $(ODIR)/main.o $(ODIR)/sonobuoy.o $(ODIR)/coordinate.o $(ODIR)/antenna.o $(ODIR)/helicopter.o

$(OUTDIR)/PhaseDiff: $(OFILES) 
	$(CC) -o $@ $(OFILES)

$(ODIR)/main.o: $(SDIR)/main.cpp $(HFILES)
	$(CC) -c $(SDIR)/main.cpp $(CFLAGS) -o $@

$(ODIR)/sonobuoy.o: $(SDIR)/sonobuoy.cpp $(HFILES)
	$(CC) -c $(SDIR)/sonobuoy.cpp $(CFLAGS) -o $@

$(ODIR)/coordinate.o: $(SDIR)/coordinate.cpp $(HFILES)
	$(CC) -c $(SDIR)/coordinate.cpp $(CFLAGS) -o $@

$(ODIR)/helicopter.o: $(SDIR)/helicopter.cpp $(HFILES)
	$(CC) -c $(SDIR)/helicopter.cpp $(CFLAGS) -o $@ 

$(ODIR)/antenna.o: $(SDIR)/antenna.cpp $(HFILES)
	$(CC) -c $(SDIR)/antenna.cpp $(CFLAGS) -o $@

clean:
	-rm -f $(OFILES) $(OUTDIR)/*

rebuild: clean $(OUTDIR)/*

	 
