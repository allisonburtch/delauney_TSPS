#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    

    tspsReceiver.connect(12000);
    //grabber.initGrabber(0, 0);
    
    // ofSetBackgroundAuto(false);
    //ofBackground(255);
    
    ofSetFrameRate(30);
    ofEnableAlphaBlending();
    ofSetCircleResolution(60);
      ofSetBackgroundColor(0);
    ofBackground(0);
}

//--------------------------------------------------------------
void testApp::update(){
//    grabber.update();
//    
//    if (grabber.isFrameNew()) {
  
    
    //vector<ofxTSPS::Person *> people = tspsReceiver.getPeople();

     people = tspsReceiver.getPeople();

    ofSetColor(255);
    ofDrawBitmapString("people size: " + ofToString(people.size()), 20, 20);
    
    if (people.size() >= 2) {
        
        for (int i=0; i<people.size(); i++) {
            ofPoint p;
            p = people[i] -> centroid;
            p.x *= ofGetWidth();
            p.y *= ofGetHeight();
            centroids.push_back(p);
            //pushback adds it to the vector of ofpoints
        }
        
    }
    
    triangulation.reset();
    triangulation.addPoints(centroids);
    triangulation.triangulate();
        cout << centroids.size() << endl;
    
    

}

//--------------------------------------------------------------
void testApp::draw(){
    
  
    
    //ofRect(0,0,ofGetWidth(),ofGetHeight());
    
//    vector<ofxTSPS::Person *>  people = tspsReceiver.getPeople();
    

    ofSetLineWidth(5);
 
    
//    ofDrawBitmapString("people size: " + ofToString(people.size()), 20, 20);
//    
//    if (people.size() >= 2) {
//        
//        for (int i=0; i<people.size(); i++) {
//            ofPoint p;
//            p = people[i] -> centroid;
//            p.x *= ofGetWidth();
//            p.y *= ofGetHeight();
//            centroids.push_back(p);
//            //pushback adds it to the vector of ofpoints
//        }   
//        
//    }
    //lines = ofPolyline(centroids);
    //lines.draw();
    //delaunay
    
    
    /*
    for(int i=0; i<centroids.size(); i++) {
        
        for (int j=0; j<centroids.size(); j++) {
            //ofFill(grabber.centroids.size());
            
            ofLine(centroids[i].x, centroids [i].y, centroids[j].x, centroids[j].y);

        
        }
    }
     */
    ofFloatColor color;
    color.set(ofRandom(255), ofRandom(255), ofRandom(255));
    
    triangulation.triangleMesh.addColor(color);
    
    triangulation.draw();
        
    
    
    centroids.clear();
 }


//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}