#include "my_math.h"

int32_t sum_of_array(uint8_t* arr,uint8_t count){
	uint16_t sum = 0;
	
	for(uint8_t i = 0; i<count; i++)
		sum += *(arr+i);
	return sum;
}
