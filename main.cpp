/* 
 // TODO(Banni): 
 -- Add the functionality for detecting System keys such as Alt + f4
-- Add the functionality to activate or deactivate the program from key presses. ie. Alt + f9
*/
#include "win32_fileapi.h"
#include "debug.h"
#include "string_utils.h"
#include "config_parser.h"
#include "num_utils.h"
#include "output.h"

#define EAT_KEY_STROKE true
#define NUMBER_OF_KEYS 200
#if defined(DEBUG)
#define CONFIG_FILE_PATH "../.config"
#endif

#if !defined(DEBUG)
#define CONFIG_FILE_PATH ".config"
#endif

static int TurboKeys[NUMBER_OF_KEYS];
static int NumberOfTurboKeys = 0;

static mapped_key MappedKeys[NUMBER_OF_KEYS];
static int NumberOfMappedKeys = 0;
//Flag to determine if we should we doing the turbo and mappings
static bool Activated = true;

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

int get_key_mapping(int KeyCode){
    for(int i = 0; i<NumberOfMappedKeys;i++){
		if(KeyCode == MappedKeys[i].KeyCode){
			return MappedKeys[i].MappedKeyCode;
		}
	}
	return KeyCode;
}

LRESULT CALLBACK LowLevelKeyboardProc(int Code, WPARAM WParam, LPARAM LParam)
{
    bool InterestedKey = false;
	PKBDLLHOOKSTRUCT Param = (PKBDLLHOOKSTRUCT)LParam;
	
    if (Code == HC_ACTION)
    {
        switch (WParam)
        {
			case WM_KEYDOWN:{
                int MappedKeyCode = get_key_mapping(Param->vkCode);
                if (Activated && (InterestedKey = key_is_turbo(MappedKeyCode))) {
                    simulate_key_press(MappedKeyCode);
                }
                break;
            }
            case WM_SYSKEYDOWN:{
                
                if(Param->vkCode == VK_F9){
                    Activated = !Activated;
                }
                break;
            }
		}
	}
	return((EAT_KEY_STROKE && InterestedKey) ? 1 : CallNextHookEx(NULL, Code, WParam, LParam));
}

void setup_keys(){
    win32_file ConfigFile;
    if(read_entire_file(CONFIG_FILE_PATH,&ConfigFile)){
        parse_config(ConfigFile.Data,
                     TurboKeys,
                     &NumberOfTurboKeys,
                     MappedKeys,
                     &NumberOfMappedKeys);
        close_file(&ConfigFile);
    }
    else{
        std_output("Config file could not be opened\n");
    }
}

void initialize(){
    initialize_std_output();
    setup_keys();
}

int main()
{
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