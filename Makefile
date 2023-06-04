.DEFAULT_GOAL := compile

.PHONY: cleanall
cleanall: clean uninstall

.PHONY: install
install: compile
	mkdir -p /usr/local/bin/
	cp bpkg /usr/local/bin/bpkg
	rm bpkg

.PHONY: uninstall
uninstall:
	rm -f /usr/local/bin/bpkg

.PHONY: compile
compile: 
	$(CXX) -o bpkg src/*.cpp

.PHONY: clean
clean:
	rm bpkg
