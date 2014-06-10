#include "testApp.h"

#include "FirstScene.h"
#include "SecondScene.h"

//--------------------------------------------------------------
void testApp::setup(){
    sceneManager.addScene(ofPtr<ofxScene>(new FirstScene));
    sceneManager.addScene(ofPtr<ofxScene>(new SecondScene));
    sceneManager.setExitByTime(false);
    sceneManager.setSceneDuration(0.3, 1.5, 0.3);
    sceneManager.setTransitionFade();
    
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
void testApp::keyPressed(int key){
    if (key == ' ') {
        sceneManager.changeScene();
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

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