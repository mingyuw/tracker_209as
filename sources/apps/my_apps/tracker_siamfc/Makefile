target=tracker_siamfc
cybridge=caller_tracker

CC=gcc
CFLAGS= `python3-config --cflags`
LDFLAGS= `python3-config --ldflags`
# Use --embed use python >= 3.8
# LDFLAGS= `python3-config --embed --ldflags`

all:
	cython $(cybridge).pyx
	$(CC) *.c $(CFLAGS) -c 
	$(CC) *.o $(LDFLAGS) -fno-lto -o $(target)

clean:
	rm -f *.o $(target)
	rm -f $(cybridge).h
	rm -f $(cybridge).c
	rm -rf __pycache__
	rm -rf models/__pycache__