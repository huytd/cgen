PROJECT=cgen

all: clean
	gcc -o $(PROJECT) $(PROJECT).c

clean:
	rm -rf $(PROJECT)

install:
	sudo cp $(PROJECT) /usr/local/bin/

uninstall:
	sudo rm -f /usr/local/bin/$(PROJECT)
