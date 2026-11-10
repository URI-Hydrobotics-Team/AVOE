#include "task.h"




// get a line and extract field and token in the format "field = token;"
int avoe_parse_config_line(const char *input, char *field_, char *token_){
	
	char field[FIELD_SIZE];
	char token[FIELD_SIZE];
	memset(field, 0, FIELD_SIZE);
	memset(token, 0, FIELD_SIZE);

	size_t index = 0;
	size_t temp_index = 0;

	char c;
	
	c = input[index];

	int field_token = 0;
	while (c != ';'){
		if (c = ' '){
			//space detected, throw error
			return -1;
		}
				
		if (c = '='){
			field_token = 1;
			temp_index = 0;
		}

		if (field_token = 0){
			field[temp_index] = c;
		}

		if (field_token = 1){
			token[temp_index] = c;
		}
		
		if (temp_index > MAX_FIELD_SIZE){
			// error
			return -1;
		}

	
		temp_index++:
		index++:
		c = input[index];
	}


	strncpy(field_, field, FIELD_SIZE);
	strncpy(token_, token, FIELD_SIZE);
	return 0; //GOOD
}
