#Directory Macros
IDIR = ./include
ODIR = ./obj
SDIR = ./src
OUTDIR = output

#compiler macros
CC = g++
CFLAGS = -I $(IDIR) -Wall -std=c++11
HFILES = $(IDIR)/main.h $(IDIR)/terminal.h $(IDIR)/fileio.h $(IDIR)/errorlog.h
OFILES = $(ODIR)/main.o $(ODIR)/terminal.o $(ODIR)/fileio.o $(ODIR)/errorlog.o

$(OUTDIR)/typing_simulator: $(OFILES) 
	$(CC) -o $@ $(OFILES)

$(ODIR)/main.o: $(SDIR)/main.cpp $(HFILES)
	$(CC) -c $(SDIR)/main.cpp $(CFLAGS) -o $@

$(ODIR)/terminal.o: $(SDIR)/terminal.cpp $(HFILES)
	$(CC) -c $(SDIR)/terminal.cpp $(CFLAGS) -o $@

$(ODIR)/fileio.o: $(SDIR)/fileio.cpp $(HFILES)
	$(CC) -c $(SDIR)/fileio.cpp $(CFLAGS) -o $@

$(ODIR)/errorlog.o: $(SDIR)/errorlog.cpp $(HFILES)
	$(CC) -c $(SDIR)/errorlog.cpp $(CFLAGS) -o $@

clean:
	-rm -f $(OFILES) $(OUTDIR)/typing_simulator

rebuild: clean $(OUTDIR)/typing_simulator
