
const XMSG_BUFFER_SIZE		= 2048;

struct XMessageBuffer
{
	MSG** table;

	int Size;
	int FirstIndex;
	int LastIndex;

	void clear(void);
	void put(MSG* p);
	void put(void* hWnd,int msg,int wParam,int lParam);
	int get(MSG* p);

	XMessageBuffer(void);
};

extern XMessageBuffer* XMsgBuf;
