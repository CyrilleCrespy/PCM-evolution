CC=gcc
CFLAGS=$(shell pkg-config --cflags gtk4) -pedantic -g
CLIBS=$(shell pkg-config --libs gtk4)

PCM_Évolution: PCM_Évolution.c
	@echo "Checking if GTK4 is present in the system"
	pkg-config --exists gtk4 && echo "OK" || echo "GTK4 not found" && exit
	$(CC) $(CFLAGS) PCM_Évolution.c -o PCM_Évolution $(CLIBS)
	@echo "Executable file PCM_Évolution created"
clean:
	@rm PCM_Évolution.o &>/dev/null
	@exit
	@echo "PCM_Évolution.o erased."
