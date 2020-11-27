#include <Windows.h>

#define KEY_TO_TURBO 0x57 //Key 'w'
#define EAT_KEY_STROKE TRUE

void simulate_key_press(int KeyCode){
	keybd_event(KeyCode, 0, 0, 0);
	keybd_event(KeyCode, 0, KEYEVENTF_KEYUP, 0);
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
            if (InterestedKey = (Param->vkCode == KEY_TO_TURBO)) {
				simulate_key_press(KEY_TO_TURBO);
				break;
            }
            break;
        }
    }
    return((EAT_KEY_STROKE && InterestedKey) ? 1 : CallNextHookEx(NULL, Code, WParam, LParam));
}

int main()
{
    HHOOK Hook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);
    MSG Msg;
    while (!GetMessage(&Msg, NULL, NULL, NULL)) {    
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    UnhookWindowsHookEx(Hook);
    return(0);
}