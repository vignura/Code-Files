#Directory Macros
IDIR = ./include
ODIR = ./obj
SDIR = ./src
OUTDIR = ./output

#compiler macros
CC = g++
CFLAGS = -I $(IDIR) -Wall
HFILES = $(IDIR)/main.h $(IDIR)/signal.h $(IDIR)/digitalfilter.h
OFILES = $(ODIR)/main.o $(ODIR)/signal.o $(ODIR)/digitalfilter.o

$(OUTDIR)/DigitalFilter: $(OFILES) 
	$(CC) -o $@ $(OFILES)

$(ODIR)/main.o: $(SDIR)/main.cpp $(HFILES)
	$(CC) -c $(SDIR)/main.cpp $(CFLAGS) -o $@

$(ODIR)/signal.o: $(SDIR)/signal.cpp $(HFILES)
	$(CC) -c $(SDIR)/signal.cpp $(CFLAGS) -o $@
	
$(ODIR)/digitalfilter.o: $(SDIR)/digitalfilter.cpp $(HFILES)
	$(CC) -c $(SDIR)/digitalfilter.cpp $(CFLAGS) -o $@


clean:
	-rm -f $(OFILES) $(OUTDIR)/*

rebuild: clean $(OUTDIR)/DigitalFilter

	 
