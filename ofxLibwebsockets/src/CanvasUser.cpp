/*
 *  CanvasUser.cpp
 *  WebSocketsModule
 *
 *  Created by jason van cleave on 6/21/11.
 *  Copyright 2011 jasonvancleave.com. All rights reserved.
 *
 */

#include "CanvasUser.h"



CanvasUser::CanvasUser()
{
	
}


void CanvasUser::addCanvasInfo(string canvasData)
{
	cout << "CanvasUser::addCanvasInfo canvasData: "  << canvasData << endl;
	int position = canvasData.find( ";" );
	string choppedString = canvasData.substr(0, position);
	cout << "choppedString: " << choppedString << endl;
	istringstream iss(choppedString);
    string token = " ";  
	vector<string> tokens;
	while (iss >> token) {
		tokens.push_back(token); 
	} 
	
	for(int i=0; i<tokens.size(); i++)
	{
		cout << "token" << i << " : " << tokens[i] << endl;
	}
	if (tokens.size() > 0)
	{
		CanvasLine canvasLine;
		canvasLine.hexColorString = tokens[1].substr(1, tokens[1].length());
		canvasLine.x1 = ofToInt(tokens[2]);
		canvasLine.y1 = ofToInt(tokens[3]);
		canvasLine.x2 = ofToInt(tokens[4]);
		canvasLine.y2 = ofToInt(tokens[5]);
		std::stringstream ss;
		ss << std::hex << canvasLine.hexColorString;
		ss >> canvasLine.hexColor;
		lines.push_back(canvasLine);
	}

	
}
void CanvasUser::draw()
{
	for (int i=0; i<lines.size(); i++) 
	{
		ofSetHexColor(lines[i].hexColor);
		ofLine(lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2);
	}
}
CanvasUser::~CanvasUser()
{
	
}