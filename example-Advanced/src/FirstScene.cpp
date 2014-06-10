//
//  FirstScene.cpp
//  example-Simple
//
//  Created by Koki Nomura on 2014/03/12.
//
//

#include "FirstScene.h"

void FirstScene::setup() {
    
}

void FirstScene::update() {
    
}

void FirstScene::draw() {
    ofSetColor(255, 0, 255);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
    ofSetColor(200);
    y = (y+2) % ofGetHeight();
    ofRect(0, y, ofGetWidth(), 10);
}

void FirstScene::willFadeIn() {

}

void FirstScene::willDraw() {

}

void FirstScene::willFadeOut() {

}

void FirstScene::willExit() {
    
}