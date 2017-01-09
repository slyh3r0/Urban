#ifndef URBAN_H__
#define URBAN_H__
#include <stdio.h>
#include <string.h>


//#################
//# URBAN GLOBALS #
//#################

const int URBAN_VERSION = 0;
const int URBAN_MAX_VARNAME = 50;
const int URBAN_INT = 1;
const int URBAN_CHAR = 2;
const int URBAN_STRING = 3;





//##################
//# VARIABLE TYPES #
//##################

// STANDARD VARIABLE STRUCT (pointed to by URBAN_VAR_TABLE_STRUCT.URBAN_VAR_PTR)
struct URBAN_VAR_STRUCT { 
	int VAR_TYPE;
	int VAR_SCOPE = 0;
	char VAR_NAME[URBAN_MAX_VARNAME];
	void *VAR_PTR = NULL;
	void *VAR_TYPE_EXTRA = NULL;
	
};


// STRING-SPECIFIC STRUCT
struct URBAN_STRING_STRUCT {
	int VAR_STRING_LENGTH;
};

//#######################
//# VARIABLE MANAGEMENT #
//#######################

// GLOBAL VARIABLE TABLE
struct URBAN_GLOBAL_VAR_TABLE_STRUCT {
	void *URBAN_VAR_PTR = NULL;
	void *URBAN_VAR_TABLE_NEXT = NULL;
};

//#################
//# ALL FUNCTIONS #
//#################

void URBAN_GVT_SETUP(struct URBAN_GLOBAL_VAR_TABLE_STRUCT *gvt);
void URBAN_GVT_ADD(struct URBAN_GLOBAL_VAR_TABLE_STRUCT *gvt);
void URBAN_GVT_EASY_ADD(struct URBAN_GLOBAL_VAR_TABLE_STRUCT *gvt);
void URBAN_INT_ADD(struct URBAN_GLOBAL_VAR_TABLE_STRUCT *gvt);
struct URBAN_VAR_STRUCT *URBAN_VAR_CONSTRUCT(char VAR_NAME[URBAN_MAX_VARNAME],void *VAR_TYPE,void *VAR_PTR);
void *URBAN_VAR_TYPE_CONSTRUCT(int VAR_TYPE);
void URBAN_CHECK_NAME(char VAR_NAME[]);

//####################
//# FUNCTIONS: SETUP #
//####################

// SETUP URBAN'S GLOBAL VARIABLE TABLE
void URBAN_GVT_SETUP(struct URBAN_GLOBAL_VAR_TABLE_STRUCT *gvt){
	*gvt = malloc(sizeof(URBAN_GLOBAL_VAR_TABLE_STRUCT));
	gvt->*URBAN_VAR_PTR = NULL
}

void URBAN_GVT_ADD(void *gvt, void *new_var){
	gvt->URBAN_VAR_PTR = new_var;
}





//########################
//# FUNCTIONS: VARIABLES #
//########################

// CREATES VARIABLES

struct URBAN_VAR_STRUCT *URBAN_VAR_CONSTRUCT(char VAR_NAME[URBAN_MAX_VARNAME],int VAR_TYPE,void *VAR_PTR,void *VAR_TYPE_EXTRA){
	
	struct URBAN_VAR_STRUCT new_var;
	switch(VAR_TYPE) {
		case(URBAN_STRING):
			new_var.VAR_TYPE_EXTRA = VAR_TYPE_EXTRA;
		case(URBAN_CHAR):
	
		case(URBAN_INT):
			
			
		default: 
			URBAN_CHECK_NAME(VAR_NAME[]);
			strcpy(new_var.VAR_NAME, VAR_NAME);
			new_var.VAR_TYPE = VAR_TYPE;
	}
	

	

}

// CREATES THE TYPE-SPECIFIC STRUCT

void *URBAN_VAR_TYPE_CONSTRUCT(int VAR_TYPE){
	
	return 
}


void URBAN_VAR_ADD(struct URBAN_GLOBAL_VAR_TABLE_STRUCT *uvt,struct URBAN_VAR_STRUCT *new_var{
	
	*uvt->URBAN_VAR_PTR = &new_var

}

void URBAN_CHECK_NAME(char VAR_NAME[]){
	
}

#endif //URBAN_H__
