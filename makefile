all:
	gcc server.c -o server -lrt -pthread
	gcc client.c -o client -lrt -pthread
	gnome-terminal -e "./server"
	./client
