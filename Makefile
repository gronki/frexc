
INCLUDE = -I include
LDLIBS = -lpng -lz
OBJECTS = args.o frexc.o renderer.o space.o

prefix = /usr/local
bindir = $(prefix)/bin

frexc: $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

install: frexc
	mkdir -p $(DESTDIR)$(bindir)
	install frexc $(DESTDIR)$(bindir)

%.o: %.cpp
	$(CXX) $(INCLUDE) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) frexc *.o
