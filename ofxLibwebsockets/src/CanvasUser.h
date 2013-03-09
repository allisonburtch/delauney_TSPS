#ifndef _CANVAS_USER_
#define _CANVAS_USER_

#include "ofMain.h"
#include "WebSocketProtocolsInfo.h"

struct CanvasLine {
	string hexColorString;
	unsigned int hexColor;
	int x1;
	int y1;
	int x2;
	int y2;
	
	
};

class CanvasUser
{
	
	public:
		CanvasUser();
		~CanvasUser();
		per_session_data__lws_mirror *pss;
	
		void draw();
		void addCanvasInfo(string canvasData);
		vector<CanvasLine> lines;
};

#endif