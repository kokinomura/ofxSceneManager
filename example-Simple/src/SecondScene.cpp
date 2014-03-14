//
//  SecondScene.cpp
//  example-Simple
//
//  Created by Koki Nomura on 2014/03/12.
//
//

#include "SecondScene.h"
#include "FirstScene.h"

void SecondScene::setup(ofPtr<ofxScene> previousScene) {
    FirstScene* scene = dynamic_cast<FirstScene *>(previousScene.get());
    y = scene->y;
}

void SecondScene::update() {
    
}

void SecondScene::draw() {
    ofSetColor(255, 255, 0);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());

    ofSetColor(0);
    x = (x+2) % ofGetWidth();
    ofRect(x, 0, 10, ofGetHeight());
    
    ofSetColor(245);
    ofRect(0, y, ofGetWidth(), 10);
}
