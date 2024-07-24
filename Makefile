##target: arguments
	##command to run

pacman:
	gcc -g queue.c PacMan.c -o pacman
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./pacman

