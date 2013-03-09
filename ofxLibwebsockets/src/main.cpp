//
//  main.cpp
//  WebSocketsModule
//
//  Created by Van Cleave, Jason on 6/16/11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//

#include "ofMain.h"
#include "WebSocketsModuleApp.h"
#include "ofAppGlutWindow.h"


WebSocketsModuleApp *app;
int main() {

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);

	app = new WebSocketsModuleApp();
	ofRunApp(app);

}
