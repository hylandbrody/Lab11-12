CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=-ljpeg
SOURCES=mandel.c jpegrw.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=mandel

all: $(EXECUTABLE) mandelmovie

-include $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

mandelmovie: mandelmovie.c
	$(CC) -Wall -g mandelmovie.c -o mandelmovie

.c.o:
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) mandelmovie *.d
	