#include <stdint.h>
#include <stdbool.h>
#include "ktypes.h"

typedef struct Tree {
	
	struct Tree *branch;
	Lword id;
	
	
}Tree;

typedef struct Table {

	Lword type;
	void *data;
	
}Table;

typedef struct Label {

	Lword id;
	Byte *label;
	struct Label *last_label
}Label;

typedef enum State {
	
	QUIT = 0,
	COMMAND,
	EDIT
	
}State;

void urban( Tree *tree, Table *table){

	State state = COMMAND;
	Lword bcount = 0, currentid = 0;
	Byte *buffer = (Byte *) alloc(MAX_BUFFER);
	Label *lastlabel = NULL;

	while (state != QUIT){
		
		switch(state){
			case COMMAND:
				
				buffer[bcount] = input();
				
				currentid = walkTree(tree,buffer);
				if (currentid != 0){
					parse(lastlabel,currentid);
					displayMeta(currentid);
				}


				break;
			case EDIT:
				
		}
	}
}

