/* 
 // TODO(Banni): 
 
-- Add key mappings
 -- Write a parser to parse the config file to set turbo and virtual key mappings
 
*/
#include <Windows.h>

static int TurboKeys[200];
static int NumberOfTurboKeys = 0;

#define EAT_KEY_STROKE TRUE

#if defined(DEBUG)
#define Assert(expression) if(!(expression))*(int*)0 = 0
#endif

void simulate_key_press(int KeyCode){
	keybd_event(KeyCode, 0, 0, 0);
	keybd_event(KeyCode, 0, KEYEVENTF_KEYUP, 0);
}

bool key_is_turbo(int KeyCode){
	for(int i = 0; i<NumberOfTurboKeys;i++){
		if(KeyCode == TurboKeys[i]){
			return true;
		}
	}
	return false;
}

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

LRESULT CALLBACK LowLevelKeyboardProc(int Code, WPARAM WParam, LPARAM LParam)
{
    BOOL InterestedKey = FALSE;
	PKBDLLHOOKSTRUCT Param = (PKBDLLHOOKSTRUCT)LParam;
	
    if (Code == HC_ACTION)
    {
        switch (WParam)
        {
			case WM_KEYDOWN:
            if (InterestedKey = key_is_turbo(Param->vkCode)) {
				simulate_key_press(Param->vkCode);
				break;
			}
			break;
		}
	}
	return((EAT_KEY_STROKE && InterestedKey) ? 1 : CallNextHookEx(NULL, Code, WParam, LParam));
}

void initialize(){
	TurboKeys[NumberOfTurboKeys++] = 0x57;
}

int main()
{
	Assert(0);
	char_hex_convert_to_decimal("0x5787564");
	initialize();
	HHOOK Hook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);
	MSG Msg;
	while (!GetMessage(&Msg, NULL, NULL, NULL)) {    
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	UnhookWindowsHookEx(Hook);
	return(0);
}