#include "num_utils.h"

int raise_to_power(int Number, int Power){
	if(Power == 0){
		return(1);
	}
	int ToReturn = 1;
	for(int i = 1; i<=Power; i++){
		ToReturn *= Number;
	}
	return(ToReturn);
}

int char_hex_convert_to_decimal(const char * Hex){
	while(*Hex != 'x' && *Hex != 'X'){
		Hex++;
	}
	*Hex++;
	int HexcodeStringLength = 0;
	while(*Hex != '\0'){
		Hex++;
		HexcodeStringLength++;
	}
	Hex -= HexcodeStringLength;
	int MaxPower = HexcodeStringLength - 1;
	int ToInt = 0;
	for(int i = 0; i<HexcodeStringLength; i++){
		int Temp = ((int)(*Hex++)) - '0';
		ToInt +=  raise_to_power(16,MaxPower--) * Temp;
	}
	return(ToInt);
}
