build:image_editor
image_editor:image_editor.c
	gcc image_editor.c load.c micunelte.c select.c rotate.c crop.c apply.c save.c -o image_editor -lm
clean:
	rm image_editor
