//
//  WebSocketsModuleApp.cpp
//  WebSocketsModule
//
//  Created by Van Cleave, Jason on 6/16/11.


#include "WebSocketsModuleApp.h"

static struct libwebsocket_protocols protocols[] = {
	{ "http", callback_http, 0 },
	{ "dumb-increment-protocol", callback_dumb_increment, sizeof(struct per_session_data__dumb_increment) },
	{"lws-mirror-protocol",callback_lws_mirror, sizeof(struct per_session_data__lws_mirror)}
};

//--------------------------------------------------------------
void WebSocketsModuleApp::setup() {
	ofSetFrameRate(60);
	hasStarted = false;
	webSocketServer = new ofxWebSocketServer();

	webSocketServer->setup(protocols);
	ofAddListener(ofxWebSocketServer::onopen, this, &WebSocketsModuleApp::onopen);
	ofAddListener(ofxWebSocketServer::onclose, this, &WebSocketsModuleApp::onclose);
	ofAddListener(ofxWebSocketServer::onmessage, this, &WebSocketsModuleApp::onmessage);
	ofAddListener(ofxWebSocketServer::onexecute, this, &WebSocketsModuleApp::onexecute);
	hasStarted = true;
}

//--------------------------------------------------------------
void WebSocketsModuleApp::update() {
	
	
	
}
void WebSocketsModuleApp::addCanvasUser(per_session_data__lws_mirror *_pss)
{
	cout << "addCanvasUser" << endl;
	bool foundUser = false;
	for (int i=0; i<canvasUsers.size(); i++)
	{
		if(_pss == canvasUsers[i]->pss)
		{
			foundUser = true;
		}
	}
	if (!foundUser)
	{
		CanvasUser *canvasUser = new CanvasUser();
		canvasUser->pss = _pss;
		canvasUsers.push_back(canvasUser);
	}
	cout << "num canvasUsers" << canvasUsers.size() << endl;
	
}
void WebSocketsModuleApp::removeCanvasUser(per_session_data__lws_mirror *_pss)
{
	bool foundUser = false;
	int userIdToRemove;
	for (int i=0; i<canvasUsers.size(); i++)
	{
		if(_pss == canvasUsers[i]->pss)
		{
			cout << "WE SHOULD REMOVE: " << i << " CURRENT SIZE: " << canvasUsers.size() << endl;
			foundUser = true;
			userIdToRemove = i;
			
		}
	}
	if (foundUser)
	{
		canvasUsers.erase(canvasUsers.begin()+userIdToRemove);
		cout << " POST SIZE: " << canvasUsers.size() << endl;
	}
}
void WebSocketsModuleApp::addToCanvas(per_session_data__lws_mirror *_pss, string canvasInfo)
{
	for (int i=0; i<canvasUsers.size(); i++)
	{
		if(_pss == canvasUsers[i]->pss)
		{
			cout << "user: " << i << " addToCanvas: " << canvasInfo << endl;
			canvasUsers[i]->addCanvasInfo(canvasInfo);
		}
	}
	
}
//--------------------------------------------------------------
void WebSocketsModuleApp::draw() {
	for (int i=0; i<canvasUsers.size(); i++)
	{
		canvasUsers[i]->draw();
	}
	
	ofDrawBitmapString("Open http://localhost:7681/test.html in Chrome", 200, 20);
}

//--------------------------------------------------------------
void WebSocketsModuleApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void WebSocketsModuleApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void WebSocketsModuleApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void WebSocketsModuleApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void WebSocketsModuleApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void WebSocketsModuleApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void WebSocketsModuleApp::windowResized(int w, int h) {

}

void WebSocketsModuleApp::onopen(ofxWebSocketServer::WebSocketEventArgs& args)
{
	cout << "WebSocketsModuleApp onopen " << "args.message" << args.message << endl;
}
void WebSocketsModuleApp::onexecute(ofxWebSocketServer::WebSocketEventArgs& args)
{
	//cout << "WebSocketsModuleApp onexecute " << "args.message" << args.message << endl;
	webSocketServer->broadcast(PROTOCOL_DUMB_INCREMENT, "x", 100, false);
	libwebsocket_service(webSocketServer->context, 50);
	
}
void WebSocketsModuleApp::onmessage(ofxWebSocketServer::WebSocketEventArgs& args)

{
	cout << "WebSocketsModuleApp onmessage " << "args.message" << args.message << endl;
}
void WebSocketsModuleApp::onclose(ofxWebSocketServer::WebSocketEventArgs& args)
{
	cout << "WebSocketsModuleApp onclose " << "args.message" << args.message << endl;
}


void WebSocketsModuleApp::exit()
{
	webSocketServer->exit();
}
extern "C"
{

	
	int
	callback_http(struct libwebsocket_context* context,
				  struct libwebsocket* wsi,
				  enum libwebsocket_callback_reasons reason,
				  void* user,
				  void* in, size_t len)
	{
		char client_name[128];
		char client_ip[128];
		
		char* url = (char*)in;
		
		switch (reason)
		{
			case LWS_CALLBACK_HTTP:
			{
				fprintf(stderr, "callback_http LWS_CALLBACK_HTTP\n");
				fprintf(stderr, "serving HTTP URL %s with file:%s\n", url, url);
				
				/*if (libwebsockets_serve_http_file(wsi,
				 _http_server.filenameForUrl(url),
				 _http_server.mimetypeForUrl(url)))
				 fprintf(stderr, "Failed to send HTTP file\n");*/
				if (url == NULL) {
					return 0;
				}
				std::string urlToString;
				urlToString = url;
				if(urlToString.substr(0,1) == "/")
				{
					urlToString = urlToString.substr(1, urlToString.size()-1);
				}
				
				string fullPath = ofToDataPath(urlToString, true);
				cout << "getFullPath fullPath" << fullPath << endl;
				
				cout << "callback_http htmlFile: " << fullPath << endl;
				
				if (libwebsockets_serve_http_file(wsi, fullPath.c_str(), "text/html"))
				{
					fprintf(stderr, "Failed to send HTTP file\n");
					
				}
				break;
			}
				
				
				
			case LWS_CALLBACK_FILTER_NETWORK_CONNECTION:
			{
				fprintf(stderr, "callback_http LWS_CALLBACK_FILTER_NETWORK_CONNECTION\n");
				libwebsockets_get_peer_addresses((int)(long)user,
												 client_name, sizeof(client_name),
												 client_ip, sizeof(client_ip));
				
				fprintf(stderr, "Received network connect from %s (%s)\n",
						client_name, client_ip);
				break;
			}
				
			default:
			{
				break;
			}
		}
		
		return 0;
	}
	
	int
	callback_dumb_increment(struct libwebsocket_context * context,
							struct libwebsocket *wsi,
							enum libwebsocket_callback_reasons reason,
							void *user, void *in, size_t len)
	{
		
		struct per_session_data__dumb_increment *pss = (per_session_data__dumb_increment *)user;
		switch (reason) 
		{
				
			case LWS_CALLBACK_ESTABLISHED:
			{
				fprintf(stderr, "callback_dumb_increment LWS_CALLBACK_ESTABLISHED\n");
				pss->number = 0;
				break;
				
				/*
				 * in this protocol, we just use the broadcast action as the chance to
				 * send our own connection-specific data and ignore the broadcast info
				 * that is available in the 'in' parameter
				 */
			}
				
			case LWS_CALLBACK_BROADCAST:
			{
				//cout << "callback_dumb_increment LWS_CALLBACK_BROADCAST" << endl;
				std::stringstream ss;
				ss << pss->number++;
				//cout << "ss.str()" << ss.str() << endl;
				string output = ss.str();
				_websocket_server.send(wsi, output.c_str(), output.size(), false);
				
				//libwebsocket_close_and_free_session(context, wsi, LWS_CLOSE_STATUS_NORMAL);
				break;
			}
				
			case LWS_CALLBACK_RECEIVE:
			{
				fprintf(stderr, "LWS_CALLBACK_RECEIVE %d\n", (int)len);
				fprintf(stderr, "LWS_CALLBACK_RECEIVE in:  %s\n", (const char *)in);
				if (len < 6)
				{
					break;
				}
					
				if (strcmp((const char *)in, "reset\n") == 0)
				{
					pss->number = 0;
					break;	
				}
					
				
			}
				
			/*
			 * this just demonstrates how to use the protocol filter. If you won't
			 * study and reject connections based on header content, you don't need
			 * to handle this callback
			 */	
				
			case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION:
			{
				dump_handshake_info((struct lws_tokens *)(long)user);
				/* you could return non-zero here and kill the connection */
				break;
			}
				
			default:
			{
				break;
			}
		}
		
		return 0;
	}
	
	int
	callback_lws_mirror(struct libwebsocket_context * context,
						struct libwebsocket *wsi,
						enum libwebsocket_callback_reasons reason,
						void *user, void *in, size_t len)
	{
		int n;
		struct per_session_data__lws_mirror *pss = (per_session_data__lws_mirror *)user;
		
		switch (reason)
		{
				
			case LWS_CALLBACK_ESTABLISHED:
			{
				cout << "callback_lws_mirror LWS_CALLBACK_ESTABLISHED" << endl;
				app->addCanvasUser(pss);
				pss->ringbuffer_tail = ringbuffer_head;
				pss->wsi = wsi;
				break;
			}
				
			case LWS_CALLBACK_SERVER_WRITEABLE:
			{
				/*if (close_testing)
				 break;*/
				if (pss->ringbuffer_tail != ringbuffer_head) {
					
					std::stringstream ss;
					ss << (unsigned char *)ringbuffer[pss->ringbuffer_tail].payload+LWS_SEND_BUFFER_PRE_PADDING;
					cout << "ss.str()" << ss.str() << endl;
					string output = ss.str();
					_websocket_server.send(wsi, 
										   output.c_str(),
										   ringbuffer[pss->ringbuffer_tail].len,
										   false);
					
					if (pss->ringbuffer_tail == (MAX_MESSAGE_QUEUE - 1))
						pss->ringbuffer_tail = 0;
					else
						pss->ringbuffer_tail++;
					
					if (((ringbuffer_head - pss->ringbuffer_tail) %
						 MAX_MESSAGE_QUEUE) < (MAX_MESSAGE_QUEUE - 15))
						libwebsocket_rx_flow_control(wsi, 1);
					
					libwebsocket_callback_on_writable(context, wsi);
					
				}
				break;
			}
				
			case LWS_CALLBACK_BROADCAST:
			{
				std::stringstream ss;
				ss << (unsigned char *)in;
				string output = ss.str();
				
				_websocket_server.send(wsi, output.c_str(), output.size(), LWS_WRITE_TEXT);
				break;
			}
				
			case LWS_CALLBACK_RECEIVE:	
			{
				cout << "callback_lws_mirror LWS_CALLBACK_RECEIVE" << (const char *)in << endl;
				char* canvasInfoChar = (char*)in;
				string canvasInfo;
				canvasInfo = canvasInfoChar;
				
				app->addToCanvas(pss, canvasInfo);
				if (ringbuffer[ringbuffer_head].payload)	
				{
					free(ringbuffer[ringbuffer_head].payload);
				}
				
				ringbuffer[ringbuffer_head].payload = malloc(LWS_SEND_BUFFER_PRE_PADDING + len + LWS_SEND_BUFFER_POST_PADDING);
				ringbuffer[ringbuffer_head].len = len;
				memcpy((char *)ringbuffer[ringbuffer_head].payload + LWS_SEND_BUFFER_PRE_PADDING, in, len);
				
				if (ringbuffer_head == (MAX_MESSAGE_QUEUE - 1))	
				{
					ringbuffer_head = 0;
				}else 
				{
					ringbuffer_head++;
				}

					
				
				if ( ((ringbuffer_head - pss->ringbuffer_tail) % MAX_MESSAGE_QUEUE) > (MAX_MESSAGE_QUEUE - 10) ) 
				{
					libwebsocket_rx_flow_control(wsi, 0);
				}
				
				libwebsocket_callback_on_writable_all_protocol( libwebsockets_get_protocol(wsi));
				break;
			}
			
			/*
			 * this just demonstrates how to use the protocol filter. If you won't
			 * study and reject connections based on header content, you don't need
			 * to handle this callback
			 */
				
			case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION:
			{
				dump_handshake_info((struct lws_tokens *)(long)user);
				/* you could return non-zero here and kill the connection */
				break;
			}
			
				
			case LWS_CALLBACK_CLOSED:
			{
				app->removeCanvasUser(pss);
				break;	
			}
				

			default:
			{
				cout << "callback_lws_mirror DEFAULT THROWN: " << reason << endl;
				break;
			}
		}
		
		return 0;
	}
	
	void
	dump_handshake_info(struct lws_tokens *lwst)
	{
		int n;
		static const char *token_names[] = {
			/*[WSI_TOKEN_GET_URI]		=*/ "GET URI",
			/*[WSI_TOKEN_HOST]		=*/ "Host",
			/*[WSI_TOKEN_CONNECTION]	=*/ "Connection",
			/*[WSI_TOKEN_KEY1]		=*/ "key 1",
			/*[WSI_TOKEN_KEY2]		=*/ "key 2",
			/*[WSI_TOKEN_PROTOCOL]		=*/ "Protocol",
			/*[WSI_TOKEN_UPGRADE]		=*/ "Upgrade",
			/*[WSI_TOKEN_ORIGIN]		=*/ "Origin",
			/*[WSI_TOKEN_DRAFT]		=*/ "Draft",
			/*[WSI_TOKEN_CHALLENGE]		=*/ "Challenge",
			
			/* new for 04 */
			/*[WSI_TOKEN_KEY]		=*/ "Key",
			/*[WSI_TOKEN_VERSION]		=*/ "Version",
			/*[WSI_TOKEN_SWORIGIN]		=*/ "Sworigin",
			
			/* new for 05 */
			/*[WSI_TOKEN_EXTENSIONS]	=*/ "Extensions",
			
			/* client receives these */
			/*[WSI_TOKEN_ACCEPT]		=*/ "Accept",
			/*[WSI_TOKEN_NONCE]		=*/ "Nonce",
			/*[WSI_TOKEN_HTTP]		=*/ "Http",
		};
		
		for (n = 0; n < WSI_TOKEN_COUNT; n++) {
			if (lwst[n].token == NULL)
				continue;
			
			fprintf(stderr, "    %s = %s\n", token_names[n], lwst[n].token);
		}
	}
}