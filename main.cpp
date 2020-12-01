/* 
 // TODO(Banni): 
 
-- Add key mappings
 -- Write a parser to parse the config file to set turbo and virtual key mappings
 
*/
#include "win32_fileapi.h"
#include "debug.h"
#include "string_utils.h"
#include "config_parser.h"
#include "num_utils.h"

static int TurboKeys[200];
static int NumberOfTurboKeys = 0;

#define EAT_KEY_STROKE TRUE
#define CONFIG_FILE_PATH "../.config"

void simulate_key_press(int KeyCode){
	keybd_event(KeyCode, 0, 0, 0);
	keybd_event(KeyCode, 0, KEYEVENTF_KEYUP, 0);
}

BOOL key_is_turbo(int KeyCode){
	for(int i = 0; i<NumberOfTurboKeys;i++){
		if(KeyCode == TurboKeys[i]){
			return true;
		}
	}
	return false;
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
    win32_file ConfigFile;
    if(read_entire_file(CONFIG_FILE_PATH,&ConfigFile)){
        parse_config(ConfigFile.Data,
                     TurboKeys,
                     &NumberOfTurboKeys);
        close_file(&ConfigFile);
    }
	//TurboKeys[NumberOfTurboKeys++] = 0x57;
}

int main()
{
	win32_file ConfigFile;
#if 0    
	bool Contains = string_contains("kingfullmakesetthere","pig");
    int StringLength = string_length("Banni");
    char SplittedString[10];
    const char * SplittableString = "Banni:Dhaliwal";
    split_string(SplittableString,
                 SplittedString,
                 10,
                 ':');
    const char * ForwardableString = "Banni%Dhaliwal";
    const char * NonForwardableString = "Bannidhaliwal";
    forward_string_pointer_upto((char**)&ForwardableString,'%');
    forward_string_pointer_upto((char**)&NonForwardableString,'%');
    char * char_hex_convert_to_decimal("0x5787564");
#endif
    
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