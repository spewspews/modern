CXXFLAGS=-Wall -Wpedantic -Wextra -O3 -std=c++1z -g

include cleanfiles
clean:
	rm -f $(CLEANFILES)

.PHONY: clean
