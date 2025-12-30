CC=gcc
CFLAGS=$(shell pkg-config --cflags gtk4) -pedantic -g -Wall -Werror=all
CLIBS=$(shell pkg-config --libs gtk4)

all: main config

main: PCM_Évolution.c
	@echo "Checking if GTK4 is present in the system"
	pkg-config --exists gtk4 && echo "OK" || echo "GTK4 not found" && exit
	$(CC) $(CFLAGS) PCM_Évolution.c -o PCM_Évolution $(CLIBS)
	@echo "Executable file PCM_Évolution created"
	
config: config.c
	$(CC) $(CFLAGS) config.c -o config $(CLIBS)
	@echo "Executable file config created"
	
clean: 
	rm PCM_Évolution config