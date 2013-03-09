//
//  WebSocketsModuleApp.h
//  WebSocketsModule
//
//  Created by Van Cleave, Jason on 6/16/11.
//

#pragma once

#include "ofMain.h"
#include "ofxWebSocketServer.h"
#include "WebSocketProtocolsInfo.h"
#include "CanvasUser.h"

//========================================================================
class WebSocketsModuleApp : public ofBaseApp {

	public:
		void setup();
		void update();
		void draw();
		void exit();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		ofxWebSocketServer *webSocketServer;
		bool hasStarted;

	
		void onopen(ofxWebSocketServer::WebSocketEventArgs& args);
		void onclose(ofxWebSocketServer::WebSocketEventArgs& args);
		void onmessage(ofxWebSocketServer::WebSocketEventArgs& args);
		void onexecute(ofxWebSocketServer::WebSocketEventArgs& args);

	
		vector<CanvasUser *>canvasUsers;
		void addCanvasUser(per_session_data__lws_mirror *_pss);
		void removeCanvasUser(per_session_data__lws_mirror *_pss);
		void addToCanvas(per_session_data__lws_mirror *_pss, string canvasInfo);

};
extern "C" 
{
		
	int
	callback_http(struct libwebsocket_context* context,
				  struct libwebsocket* wsi,
				  enum libwebsocket_callback_reasons reason,
				  void* user,
				  void* in, size_t len);
	
	
	int
	callback_dumb_increment(struct libwebsocket_context * context,
							struct libwebsocket *wsi,
							enum libwebsocket_callback_reasons reason,
							void *user, void *in, size_t len);
	int
	callback_lws_mirror(struct libwebsocket_context * context,
						struct libwebsocket *wsi,
						enum libwebsocket_callback_reasons reason,
						void *user, void *in, size_t len);
	void
	dump_handshake_info(struct lws_tokens *lwst);
}

extern WebSocketsModuleApp *app;