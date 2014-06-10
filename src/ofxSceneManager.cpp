
//
//  ofxSceneManager.cpp
//  ofxSceneManager
//
//  Created by Koki Nomura on 2014/03/12.
//
//

#include "ofxSceneManager.h"

void ofxSceneManager::run() {
    _fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    _nextFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    
    _fbo.begin();
    ofClear(255, 255, 255, 0);
    _fbo.end();
    
    _nextFbo.begin();
    ofClear(255, 255, 255, 0);
    _nextFbo.end();
    
    ofPtr<ofxScene> previousScene;
    previousScene = _currentScene;
    _currentScene = scenes.at(_sceneIndex);
    _currentScene->setupScene(previousScene);
}

void ofxSceneManager::update() {
    if (transition == TRANSITION_DISSOLVE && _isInTransition) {
        _nextScene->updateScene();
    }
    _currentScene->updateScene();
}

void ofxSceneManager::draw() {
    if (transition == TRANSITION_DISSOLVE && _isInTransition) {
        _nextFbo.begin();
        _nextScene->drawScene();
        _nextFbo.end();
    }

    _fbo.begin();
    _currentScene->drawScene();
    _fbo.end();
    
    ofPushStyle();
    ofSetColor(255, 255, 255, _currentScene->getSceneAlpha());
    _fbo.draw(0, 0);
    ofPopStyle();

    if (transition == TRANSITION_DISSOLVE && _isInTransition) {
        ofPushStyle();
        ofSetColor(255, 255, 255, _nextScene->getSceneAlpha());
        _nextFbo.draw(0, 0);
        ofPopStyle();
    }
}

void ofxSceneManager::changeScene() {
    changeScene((_sceneIndex+1) % scenes.size());
}

void ofxSceneManager::changeScene(int sceneIndex) {
    if (sceneIndex == _sceneIndex) {
        return;
    }
    _nextSceneIndex = sceneIndex;
    _currentScene->exitScene();
}

void ofxSceneManager::addScene(ofPtr<ofxScene> pScene) {
    ofAddListener(pScene->startFadingInEvent, this, &ofxSceneManager::_onStartFadingIn);
    ofAddListener(pScene->startDrawingEvent, this, &ofxSceneManager::_onStartDrawing);
    ofAddListener(pScene->finishedDrawingEvent, this, &ofxSceneManager::_onFinishedDrawing);    
    ofAddListener(pScene->startFadingOutEvent, this, &ofxSceneManager::_onStartFadingOut);
    ofAddListener(pScene->finishSceneEvent, this, &ofxSceneManager::_onFinishScene);
    scenes.push_back(pScene);
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

void ofxSceneManager::setTransitionDissolve() {
    transition = TRANSITION_DISSOLVE;
}

void ofxSceneManager::setTransitionFade() {
    transition = TRANSITION_FADE;
}

#pragma mark - Private Methods

void ofxSceneManager::_onStartFadingIn(bool &b) {

}

void ofxSceneManager::_onStartDrawing(bool &b) {

}

void ofxSceneManager::_onFinishedDrawing(bool &b) {
    // called when scenes exit by time
    _nextSceneIndex = (_sceneIndex + 1) % scenes.size();
}

void ofxSceneManager::_onStartFadingOut(bool &b) {
    if (transition == TRANSITION_FADE) {
        ;
    } else if (transition == TRANSITION_DISSOLVE) {
        _nextScene = scenes.at(_nextSceneIndex);
        _nextScene->setupScene(_currentScene);
        _isInTransition = true;
    }
}

void ofxSceneManager::_onFinishScene(bool &b) {
    if (transition == TRANSITION_FADE) {
        _sceneIndex = _nextSceneIndex;
        ofPtr<ofxScene> previousScene;
        previousScene = _currentScene;
        _currentScene = scenes.at(_sceneIndex);
        _currentScene->setupScene(previousScene);
    } else if (transition == TRANSITION_DISSOLVE) {
        _isInTransition = false;
        _currentScene = _nextScene;
        _sceneIndex = _nextSceneIndex;
    }
}