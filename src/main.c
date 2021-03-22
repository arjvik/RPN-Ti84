#include <tice.h>
#include <keypadc.h>

void init_keys(uint8_t* last) {
    kb_EnableOnLatch();
    kb_ClearOnLatch();
    kb_Scan();
    for (uint8_t i = 0; i < 8; i++)
        last[i] = kb_Data[i];
}

typedef enum {
    key_NONE = 0,
    key_0,
    key_1,
    key_2,
    key_2nd
} key_t;

key_t get_key(uint8_t* last) {
    kb_Scan();
    key_t ret = key_NONE;
    if         ((kb_Data[3] & ~last[3]) & kb_0)
        ret = key_0;
    else if ((kb_Data[3] & ~last[3]) & kb_1)
        ret = key_1;
    else if ((kb_Data[4] & ~last[4]) & kb_2)
        ret = key_2;
    else if ((kb_Data[1] & ~last[1]) & kb_2nd)
        ret = key_2nd;
    
    for (uint8_t i = 1; i < 8; i++)
        last[i] = kb_Data[i];
    return ret;
}

void main() {
    os_ClrHome();
    uint8_t last[8];
    init_keys(last);
    key_t key;

    while (!kb_On) {
	
        key = get_key(last);
        os_SetCursorPos(0, 0);
        switch (key) {
        case key_0:
        	os_PutStrFull("0");
        	break;
    	case key_1:
        	os_PutStrFull("1");
        	break;
    	case key_2:
        	os_PutStrFull("2");
        	break;
        case key_2nd:
        	os_PutStrFull("^");
        	break;
    	case key_NONE:
    		os_PutStrFull(" ");
    		break;
        }
    }
}
