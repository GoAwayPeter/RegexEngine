CC=clang
CFLAGS= -g -O0
LDFLAGS= 
SOURCES= main.c cradle.c automata.c
OBJECTS= $(SOURCES:.c=.o)
EXECUTABLE= main.app

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.INTERMEDIATE: $(OBJECTS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
		rm -f $(OBJECTS) $(EXECUTABLE)
