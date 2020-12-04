/* 
 // TODO(Banni): 
 -- Add the functionality for detecting System keys such as Alt + f4
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


struct key_repeater{
    int TurboKeys[NUMBER_OF_KEYS];
    int NumberOfTurboKeys = 0;
    mapped_key MappedKeys[NUMBER_OF_KEYS];
    int NumberOfMappedKeys = 0;
    bool Activated = true;
};

static key_repeater * GlobalKeyRepeaterPtr;

void simulate_key_press(int KeyCode){
	keybd_event(KeyCode, 0, 0, 0);
	keybd_event(KeyCode, 0, KEYEVENTF_KEYUP, 0);
}

bool key_is_turbo(int KeyCode){
	for(int i = 0; i<GlobalKeyRepeaterPtr->NumberOfTurboKeys;i++){
		if(KeyCode == GlobalKeyRepeaterPtr->TurboKeys[i]){
			return true;
		}
	}
	return false;
}

int get_key_mapping(int KeyCode){
    for(int i = 0; i<GlobalKeyRepeaterPtr->NumberOfMappedKeys;i++){
		if(KeyCode == GlobalKeyRepeaterPtr->MappedKeys[i].KeyCode){
			return GlobalKeyRepeaterPtr->MappedKeys[i].MappedKeyCode;
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
                if (GlobalKeyRepeaterPtr->Activated && (InterestedKey = key_is_turbo(MappedKeyCode))) {
                    simulate_key_press(MappedKeyCode);
                }
                break;
            }
            case WM_SYSKEYDOWN:{
                if(Param->vkCode == VK_F9){
                    GlobalKeyRepeaterPtr->Activated = !GlobalKeyRepeaterPtr->Activated;
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
                     GlobalKeyRepeaterPtr->TurboKeys,
                     &GlobalKeyRepeaterPtr->NumberOfTurboKeys,
                     GlobalKeyRepeaterPtr->MappedKeys,
                     &GlobalKeyRepeaterPtr->NumberOfMappedKeys);
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
    key_repeater KeyRepeater;
    GlobalKeyRepeaterPtr = &KeyRepeater;
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