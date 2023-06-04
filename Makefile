.DEFAULT_GOAL := compile

.PHONY: all
all: install compile-windows

.PHONY: cleanall
cleanall: clean uninstall

.PHONY: install
install: compile
	mkdir -p /usr/local/bin/
	mkdir -p /usr/local/share/cli-mg
	mkdir -p /usr/local/share/applications
	cp cli-mg /usr/local/bin/cli-mg
	cp src/icon.ico /usr/local/share/cli-mg/icon.ico
	cp LICENSE /usr/local/share/cli-mg/LICENSE
	cp src/cli-mg.desktop /usr/local/share/applications
	rm cli-mg

.PHONY: uninstall
uninstall:
	rm -f /usr/local/bin/cli-mg
	rm -rf /usr/local/share/cli-mg
	rm -f /usr/local/share/applications/cli-mg.desktop

.PHONY: install-termux
install-termux: compile
	cp cli-mg /data/data/com.termux/files/usr/bin/cli-mg
	mkdir -p /data/data/com.termux/files/usr/share/cli-mg/
	cp src/icon.ico /data/data/com.termux/files/usr/share/cli-mg/icon.ico
	cp LICENSE /data/data/com.termux/files/usr/share/cli-mg/LICENSE
	cp src/cli-mg.desktop /data/data/com.termux/files/usr/share/applications
	rm cli-mg

.PHONY: uninstall-termux
uninstall-termux:
	rm -f /data/data/com.termux/files/usr/bin/cli-mg
	rm -rf /data/data/com.termux/files/usr/share/cli-mg
	rm -f /data/data/com.termux/files/usr/share/applications/cli-mg.desktop

.PHONY: compile
compile: 
	$(CXX) -o cli-mg src/*.cpp

.PHONY: compile-windows
compile-windows:
	x86_64-w64-mingw32-windres src/icon.rc src/icon.o
	x86_64-w64-mingw32-g++ -o cli-mg-64bit-windows.exe src/*.cpp src/icon.o -static
	i686-w64-mingw32-windres src/icon.rc src/icon.o
	i686-w64-mingw32-g++ -o cli-mg-32bit-windows.exe src/*.cpp src/icon.o -static
	rm src/icon.o

.PHONY: clean
clean:
	rm cli-mg cli-mg-32bit-windows.exe cli-mg-64bit-windows.exe

