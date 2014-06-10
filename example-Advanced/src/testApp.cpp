#include "testApp.h"

#include "FirstScene.h"
#include "SecondScene.h"

//--------------------------------------------------------------
void testApp::setup(){
    FirstScene* firstScene = new FirstScene;
    firstScene->setSceneDuration(0.5, 1.5, 0.5);
    
    SecondScene* secondScene = new SecondScene;
    secondScene->setSceneDuration(0.5, 3.0, 0.5);
    
    sceneManager.addScene(ofPtr<ofxScene>(firstScene));
    sceneManager.addScene(ofPtr<ofxScene>(secondScene));
    sceneManager.setExitByTime(true);
    
    sceneManager.setTransitionDissolve();
//    sceneManager.setTransitionFade();
    
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
    } else if (key == '0') {
        sceneManager.changeScene(0);
    } else if (key == '1') {
        sceneManager.changeScene(1);
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