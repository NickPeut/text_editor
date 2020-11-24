FLAGS = -Werror 

all: program

program: obj obj/main.o obj/menu.o obj/processing_text.o obj/sentence.o obj/text.o obj/sort_sentence_product.o obj/unique_sentence_in_text.o obj/update_format_date.o
	gcc obj/main.o obj/menu.o obj/processing_text.o obj/sentence.o obj/text.o obj/sort_sentence_product.o obj/unique_sentence_in_text.o obj/update_format_date.o -o program
	
obj:
	mkdir obj
	
obj/main.o:
	gcc -c $(FLAGS) src/main.c -o obj/main.o -I include
obj/processing_text.o:
	gcc -c $(FLAGS) src/processing_text.c -o obj/processing_text.o -I include

obj/menu.o:
	gcc -c $(FLAGS) src/menu.c -o obj/menu.o -I include
	

obj/sentence.o:
	gcc -c $(FLAGS) src/sentence.c -o obj/sentence.o -I include
	

obj/sort_sentence_product.o:
	gcc -c $(FLAGS) src/sort_sentence_product.c -o obj/sort_sentence_product.o -I include
	
obj/unique_sentence_in_text.o:
	gcc -c $(FLAGS) src/unique_sentence_in_text.c -o obj/unique_sentence_in_text.o -I include
	
	
obj/update_format_date.o:
	gcc -c $(FLAGS) src/update_format_date.c -o obj/update_format_date.o -I include
	
	
obj/text.o:
	gcc -c $(FLAGS) src/text.c -o obj/text.o -I include
		
	
clean:
	rm -rf obj program
