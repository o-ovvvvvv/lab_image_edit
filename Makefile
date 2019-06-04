# Makefile
image_edit: image_edit.o edit_function.o
	gcc image_edit.o edit_function.c -o image_edit -lm
image_edit.o: image_edit.c image_edit.h
	gcc -c image_edit.c -lm
edit_function.o: edit_function.c image_edit.h
	gcc -c edit_function.c -lm
