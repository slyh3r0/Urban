#include <stdint.h>
#include <stdio.h>

struct matchreturn {
	
	uint64_t matched; //Returns how many bytes of str where matched
	uint64_t consumed; //Returns how many Bytes of pattern where consumed
	uint8_t valid; //Returns if match was valid, 0=notvalidmatch, 1=validmatch
	
};

uint8_t matchrange(const uint8_t *str, uint8_t start, uint8_t stop ){

	if (stop < start){ //If reversed match outside of range
		if (*str < stop || *str > start){
			return 1;
		}
	return 0;
	}
	if (*str >= start && *str <= stop){
    	return 1;   
	}
return 0;
}

struct matchreturn match(uint8_t *str, uint8_t *pattern){
	
	struct matchreturn local;
	local.matched = 0;
	local.consumed = 0;
	local.valid = 0;


	printf("MATCH:%s,%s\n",str,pattern);
	switch (*pattern){
		case '\\':
			local.consumed = 2;
			if (pattern[1] == 'w'){
				if (matchrange(str,'a','z') || matchrange(str,'A','Z') || matchrange(str,'0','9'))
					local.matched = 1;
					local.valid = 1;
			}else if (pattern[1] == 'W'){
				if (matchrange(str,'z','a') || matchrange(str,'Z','A') || matchrange(str,'9','0'))
					local.matched = 1;
					local.valid = 1;
			}else if (pattern[1] == 'd'){
				if (matchrange(str,'0','9'))
					local.matched = 1;
					local.valid = 1;
			}else if (pattern[1] == 'D'){
				if (matchrange(str,'9','0'))
					local.matched = 1;
					local.valid = 1;
			}else if (pattern[1] == '\0'){
				local.consumed = 1;
				local.valid = 0;
			}
			break;
		default:
			local.consumed = 1;
			if (*str == *pattern)
				local.matched = 1;
				local.valid = 1;
			break;
	}
	return local;
}

struct matchreturn handleprefixes(uint8_t *str, uint8_t *pattern){
	
	struct matchreturn local;
	local.matched = 0;
	local.consumed = 0;
	local.valid = 0;
	struct matchreturn matchret;
	
	
	printf("MATCHPREFIX:%s,%s\n",&str[local.matched],&pattern[local.consumed]);
	switch (pattern[local.consumed]){ // All Prefixes escape all Prefixes
		case '*':
			local.consumed = 1;
			
			if (pattern[local.consumed] == '\0') //Tailing * !!
				break; // local.valid and local.matched are initiated to 0 so no need to set

			matchret = match(&str[local.matched], &pattern[local.consumed]);
			while (matchret.valid) {

				local.matched += matchret.matched;
				matchret = match(&str[local.matched], &pattern[local.consumed]);
			}
			local.consumed += matchret.consumed;
			local.valid = 1; // * matches even if empty
			break;
		case '+':
			local.consumed = 1;

			if (pattern[local.consumed] == '\0') //Tailing + !!
				break;

			matchret = match(&str[local.matched],&pattern[local.consumed]);
			if (!matchret.valid) // + Needs to match at least 1
				break;

			while (matchret.valid){

				local.matched += matchret.matched;	
				matchret = match(&str[local.matched],&pattern[local.consumed]);
			}
			local.consumed += matchret.consumed;
			local.valid = 1;
			break;
/*
		case '{':
			local.consumed = 1;
			if (matchrange(str[]))
			
			
			while (matchrange(str[local.consumed],'0','9')){
				
			}
*/
		default:
			matchret = match(&str[local.matched], &pattern[local.consumed]);
			if (matchret.matched){
				local.matched++;
				local.consumed+=matchret.consumed;
			}else{
				return local;
			}
			
	}
	return local;
}



