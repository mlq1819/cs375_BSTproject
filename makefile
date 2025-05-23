P=BSTprogram
R=Filereader
Q=BSTree
G=test_generator
CFLAGS= -g -Wall

all: $(P)

$(P): $(P).o $(R).o $(Q).o $(G)
	g++ $(CFLAGS) $(P).o $(R).o $(Q).o -o $(P)

$(P).o: $(P).cpp $(R).h $(Q).h
	g++ $(CFLAGS) -c $(P).cpp -o $(P).o

$(R).o: $(R).cpp $(R).h
	g++ $(CFLAGS) -c $(R).cpp -o $(R).o

$(Q).o: $(Q).cpp $(Q).h
	g++ $(CFLAGS) -c $(Q).cpp -o $(Q).o
$(G):
	g++ $(CFLAGS) $(G).cpp -o $(G)

clean:
	rm -rf $(P)
	rm -rf $(P).o
	rm -rf $(R).o
	rm -rf $(Q).o
	rm -rf $(G)
