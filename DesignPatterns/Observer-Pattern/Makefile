#Directory Macros
IDIR = .
ODIR = .
SDIR = .
OUTDIR = .

#compiler macros
CC = gcc
LIBS = -lpthread
CFLAGS = -I $(IDIR) -Wall
HFILES = $(IDIR)/*.h
OFILES = $(ODIR)/main.o $(ODIR)/WeatherData.o $(ODIR)/CurrentConditionsDisplay.o $(ODIR)/StatisticsDisplay.o

$(OUTDIR)/WeatherStation: $(OFILES) 
	$(CC) -o $@ $(OFILES) $(LIBS)

$(ODIR)/main.o: $(SDIR)/main.c $(HFILES)
	$(CC) -c $(SDIR)/main.c $(CFLAGS) -o $@

$(ODIR)/WeatherData.o: $(SDIR)/WeatherData.c $(HFILES)
	$(CC) -c $(SDIR)/WeatherData.c $(CFLAGS) -o $@

$(ODIR)/CurrentConditionsDisplay.o: $(SDIR)/CurrentConditionsDisplay.c $(HFILES)
	$(CC) -c $(SDIR)/CurrentConditionsDisplay.c $(CFLAGS) -o $@

$(ODIR)/StatisticsDisplay.o: $(SDIR)/StatisticsDisplay.c $(HFILES)
	$(CC) -c $(SDIR)/StatisticsDisplay.c $(CFLAGS) -o $@	

clean:
	-rm -f $(OFILES) $(OUTDIR)/WeatherStation

rebuild: clean $(OUTDIR)/WeatherStation
