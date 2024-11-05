MPICXX = mpic++
CXXFLAGS = -Wall

SRC = pi.cpp pi.h
EXEC = pi

all: $(EXEC)

$(EXEC): $(SRC)
	$(MPICXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(EXEC)
