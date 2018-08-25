#include <stdint.h>
#include <stdio.h>

struct matchreturn {
	
	uint64_t matched;
	uint64_t consumed;
	
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
	
	struct matchreturn matchret;
	matchret.matched = 0;
	matchret.consumed = 1;
	printf("MATCH:%s,%s\n",str,pattern);
	switch (*pattern){
		case '\\':
			matchret.consumed = 2;
			if (pattern[1] == 'w'){
				if (matchrange(str,'a','z') || matchrange(str,'A','Z') || matchrange(str,'0','9'))
					matchret.matched = 1;
			}else if (pattern[1] == 'W'){
				if (matchrange(str,'z','a') || matchrange(str,'Z','A') || matchrange(str,'9','0'))
					matchret.matched = 1;
			}else if (pattern[1] == 'd'){
				if (matchrange(str,'0','9'))
					matchret.matched = 1;
			}else if (pattern[1] == 'D'){
				if (matchrange(str,'9','0'))
					matchret.matched = 1;
			}
			break;
		default:
			if (*str == *pattern)
				matchret.matched = 1;
			break;
	}
	return matchret;
}

uint8_t regex(uint8_t *str, uint8_t *pattern){
	
	uint64_t matched = 0, consumed = 0;
	struct matchreturn matchret;
	
	while (str[matched] != '\0' && pattern[consumed] != '\0'){
		printf("REGEX:%s,%s\n",&str[matched],&pattern[consumed]);
		switch (pattern[consumed]){ // All Prefixes escape all Prefixes
			case '*':

				if (pattern[++consumed] == '\0') //Ignore if tailing *
					return matched;	
				matchret = match(&str[matched], &pattern[consumed]);
				do {
					matched++;
					matchret = match(&str[matched], &pattern[consumed]);
				} while (matchret.matched);
				
				consumed+=matchret.consumed;
				break;

			default:
				matchret = match(&str[matched], &pattern[consumed]);
				if (matchret.matched){
					matched++;
					consumed+=matchret.consumed;
				}else{
					return matched;
				}
		}		
	}
	return matched;
}
