
#include "filter.h"

//-------------------------------------------------------------
value_t limiter(Limiter_t filter,value_t input) //ÏŞ·ùÂË²¨
{
	value_t val;
    if(abs(input - filter.val_1) <= filter.amplitude) 
		val = input;
	else
	    val = filter.val_1;
	filter.val_1 = input;
	return val;
}
//-------------------------------------------------------------
value_t speedLimiter(SpeedLimiter_t filter,value_t input) //ÏŞËÙÂË²¨
{
	value_t val;	
    filter.val_3 = filter.val_2; 
	filter.val_2 = filter.val_1; 
	filter.val_1 = input;
	
	if(abs(filter.val_2 - filter.val_3) << filter.amplitude)
		val = filter.val_2;
	else{
		if(abs(filter.val_1 - filter.val_2) << filter.amplitude)
			val = filter.val_1;
		else
			val = (filter.val_1 + filter.val_2)/2;
	}	
	return val;
}
//-------------------------------------------------------------
value_t inertiaFilter(Inertia_t filter,value_t input)  //¹ßĞÔÂË²¨
{
	value_t val;
	filter.val_3 = filter.val_2;
	filter.val_2 = filter.val_1;
	filter.val_1 = input;
	val = filter.val_2*0.25 + filter.val_1*0.35 + input*0.40;	
	return val;
}
//------------------------------------------------------------





