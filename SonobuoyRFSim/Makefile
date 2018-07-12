#Directory Macros
IDIR = ./include
ODIR = ./obj
SDIR = ./src
OUTDIR = ./output

#compiler macros
CC = g++
CFLAGS = -I $(IDIR) -Wall
HFILES = $(IDIR)/main.h $(IDIR)/hybridcoupler.h $(IDIR)/phasor.h
OFILES = $(ODIR)/main.o $(ODIR)/hybridcoupler.o $(ODIR)/phasor.o

$(OUTDIR)/RFSim: $(OFILES) 
	$(CC) -o $@ $(OFILES)

$(ODIR)/main.o: $(SDIR)/main.cpp $(HFILES)
	$(CC) -c $(SDIR)/main.cpp $(CFLAGS) -o $@

$(ODIR)/hybridcoupler.o: $(SDIR)/hybridcoupler.cpp $(HFILES)
	$(CC) -c $(SDIR)/hybridcoupler.cpp $(CFLAGS) -o $@

$(ODIR)/phasor.o: $(SDIR)/phasor.cpp $(HFILES)
	$(CC) -c $(SDIR)/phasor.cpp $(CFLAGS) -o $@

clean:
	-rm -f $(OFILES) $(OUTDIR)/*

rebuild: clean $(OUTDIR)/RFSim

	 
