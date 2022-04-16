#Directory Macros
IDIR = .
ODIR = .
SDIR = .
OUTDIR = .

#compiler macros
CC = gcc
LIBS = 
CFLAGS = -I $(IDIR) -Wall
HFILES = $(IDIR)/*.h
OFILES = $(ODIR)/linkedlist.o
OUTPUT = $(OUTDIR)/Nth_element_from_end_linkedlist.out $(OUTDIR)/is_list_cyclic.out $(OUTDIR)/check_for_loops_in_list.out\
		 $(OUTDIR)/remove_loop.out $(OUTDIR)/reverse_list.out $(OUTDIR)/find_intersection_in_list.out

all: $(OUTPUT)

$(OUTDIR)/Nth_element_from_end_linkedlist.out: $(OFILES) $(SDIR)/Nth_element_from_end_linkedlist.c 
	$(CC) $(SDIR)/Nth_element_from_end_linkedlist.c -o $@ $(OFILES) $(LIBS)

$(OUTDIR)/is_list_cyclic.out: $(OFILES) $(SDIR)/is_list_cyclic.c 
	$(CC) $(SDIR)/is_list_cyclic.c -o $@ $(OFILES) $(LIBS)

$(OUTDIR)/check_for_loops_in_list.out: $(OFILES) $(SDIR)/check_for_loops_in_list.c 
	$(CC) $(SDIR)/check_for_loops_in_list.c -o $@ $(OFILES) $(LIBS)

$(OUTDIR)/remove_loop.out: $(OFILES) $(SDIR)/remove_loop.c 
	$(CC) $(SDIR)/remove_loop.c -o $@ $(OFILES) $(LIBS)

$(OUTDIR)/reverse_list.out: $(OFILES) $(SDIR)/reverse_list.c 
	$(CC) $(SDIR)/reverse_list.c -o $@ $(OFILES) $(LIBS)

$(OUTDIR)/find_intersection_in_list.out: $(OFILES) $(SDIR)/find_intersection_in_list.c 
	$(CC) $(SDIR)/find_intersection_in_list.c -o $@ $(OFILES) $(LIBS)

$(ODIR)/linkedlist.o: $(SDIR)/linkedlist.c $(HFILES)
	$(CC) -c $(SDIR)/linkedlist.c $(CFLAGS) -o $@

clean:
	-rm -f $(OFILES) $(OUTPUT)

rebuild: clean all
