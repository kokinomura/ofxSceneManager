
//
//  ofxSceneManager.cpp
//  ofxSceneManager
//
//  Created by Koki Nomura on 2014/03/12.
//
//

#include "ofxSceneManager.h"

ofxSceneManager::ofxSceneManager() {
    _fbo.allocate(ofGetWidth(), ofGetHeight());
}

void ofxSceneManager::run() {
    _initScene(_sceneIndex);
}

void ofxSceneManager::update() {
    if (_currentScene->isFinished()) {
        _sceneIndex++;
        _sceneIndex %= scenes.size();
        _initScene(_sceneIndex);
    }
    
    _currentScene->updateScene();
}

void ofxSceneManager::draw() {
    _fbo.begin();
    ofClear(255, 255, 255);
    _currentScene->drawScene();
    _fbo.end();
    
    ofPushStyle();
    ofSetColor(255, 255, 255, _currentScene->getSceneAlpha());
    _fbo.draw(0, 0);
    ofPopStyle();
}

void ofxSceneManager::changeScene() {
    _currentScene->exitScene();
}

void ofxSceneManager::addScene(ofPtr<ofxScene> pScene) {
    scenes.push_back(pScene);
}

void ofxSceneManager::addScene(ofPtr<ofxScene> pScene, float fadeInSec, float fadeOutSec) {
    scenes.push_back(pScene);
    scenes.back()->setSceneDuration(fadeInSec, fadeOutSec);
}

void ofxSceneManager::addScene(ofPtr<ofxScene> pScene, float fadeInSec, float drawingSec, float fadeOutSec) {
    scenes.push_back(pScene);
    scenes.back()->setSceneDuration(fadeInSec, drawingSec, fadeOutSec);
}

void ofxSceneManager::setExitByTime(bool b) {
    for (int i=0; i<scenes.size(); i++) {
        scenes.at(i)->setExitByTime(b);
    }
}

void ofxSceneManager::setSceneDuration(float fadeInSec, float fadeOutSec) {
    for (int i=0; i<scenes.size(); i++) {
        scenes.at(i)->setSceneDuration(fadeInSec, fadeOutSec);
    }
}

void ofxSceneManager::setSceneDuration(float fadeInSec, float drawingSec, float fadeOutSec) {
    for (int i=0; i<scenes.size(); i++) {
        scenes.at(i)->setSceneDuration(fadeInSec, drawingSec, fadeOutSec);
    }
}

void ofxSceneManager::_initScene(int sceneIndex) {
    ofPtr<ofxScene> previousScene;
    if (sceneIndex != 0) {
        previousScene = _currentScene;
    }
    _currentScene = scenes.at(sceneIndex);
    _currentScene->setupScene(previousScene);
}
