#include "testApp.h"

#include "FirstScene.h"
#include "SecondScene.h"

//--------------------------------------------------------------
void testApp::setup(){	
    sceneManager.addScene(ofPtr<ofxScene>(new FirstScene));
    sceneManager.addScene(ofPtr<ofxScene>(new SecondScene));
    sceneManager.setExitByTime(true);
    sceneManager.setSceneDuration(0.3, 1.5, 0.3);
    
    sceneManager.run();
}

//--------------------------------------------------------------
void testApp::update(){
    sceneManager.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	sceneManager.draw();
}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void testApp::lostFocus(){

}

//--------------------------------------------------------------
void testApp::gotFocus(){

}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){

}

