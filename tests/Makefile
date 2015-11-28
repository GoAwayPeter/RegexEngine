CC=clang
CFLAGS= -g -O0
SOURCES= nfaTests.c ../automata.c
OBJECTS= $(SOURCES:.c=.o)
EXECUTABLE= tests.app

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.INTERMEDIATE: $(OBJECTS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
		rm -f $(OBJECTS) $(EXECUTABLE)
