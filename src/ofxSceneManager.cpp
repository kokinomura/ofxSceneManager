
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
    ofPtr<ofxScene> previousScene;
    previousScene = _currentScene;
    _currentScene = scenes.at(_sceneIndex);
    _currentScene->setupScene(previousScene);
}

void ofxSceneManager::update() {
    if (transition == TRANSITION_FADE) {
        _currentScene->updateScene();
    } else if (transition == TRANSITION_DISSOLVE) {
        if (isInTransition) {
            _nextScene->updateScene();
        }
        _currentScene->updateScene();
    }
}

void ofxSceneManager::draw() {
    if (transition == TRANSITION_FADE) {
        _fbo.begin();
        ofClear(255, 255, 255);
        _currentScene->drawScene();
        _fbo.end();
        
        ofPushStyle();
        ofSetColor(255, 255, 255, _currentScene->getSceneAlpha());
        _fbo.draw(0, 0);
        ofPopStyle();
    } else if (transition == TRANSITION_DISSOLVE) {
        if (isInTransition) {
            _nextFbo.begin();
            _nextScene->drawScene();
            _nextFbo.end();
        }

        _fbo.begin();
        ofClear(255, 255, 255);
        _currentScene->drawScene();
        _fbo.end();
        
        ofPushStyle();
        ofSetColor(255, 255, 255, _currentScene->getSceneAlpha());
        _fbo.draw(0, 0);
        ofPopStyle();

        if (isInTransition) {
            ofPushStyle();
            ofSetColor(255, 255, 255, _nextScene->getSceneAlpha());
            _nextFbo.draw(0, 0);
            ofPopStyle();
        }
    }
}

void ofxSceneManager::changeScene() {
    // 時間ではなく強制的にシーン変化
    if (transition == TRANSITION_FADE) {
        _currentScene->exitScene();        
    } else if (transition == TRANSITION_DISSOLVE) {
        _currentScene->exitScene();
    }
}

void ofxSceneManager::changeScene(int sceneIndex) {
    
}

void ofxSceneManager::addScene(ofPtr<ofxScene> pScene) {
    ofAddListener(pScene->startFadingInEvent, this, &ofxSceneManager::onStartFadingIn);
    ofAddListener(pScene->startDrawingEvent, this, &ofxSceneManager::onStartDrawing);
    ofAddListener(pScene->startFadingOutEvent, this, &ofxSceneManager::onStartFadingOut);
    ofAddListener(pScene->finishSceneEvent, this, &ofxSceneManager::onFinishScene);
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

void ofxSceneManager::setTransitionCut() {
#warning ToDo
}

#pragma mark - Private Methods

void ofxSceneManager::onStartFadingIn(bool &b) {
    cout << "s1" << endl;
}

void ofxSceneManager::onStartDrawing(bool &b) {
    cout << "s2" << endl;    
}

void ofxSceneManager::onStartFadingOut(bool &b) {
    cout << "s3" << endl;    
    //dissolveの場合はここから開始
    if (transition == TRANSITION_FADE) {
        _nextSceneIndex = _sceneIndex + 1;
        _nextSceneIndex %= scenes.size();
    } else if (transition == TRANSITION_DISSOLVE) {
        _nextSceneIndex = _sceneIndex + 1;
        _nextSceneIndex %= scenes.size();
        _nextScene = scenes.at(_nextSceneIndex);
        _nextScene->setupScene(_currentScene);
        isInTransition = true;
    }
}

void ofxSceneManager::onFinishScene(bool &b) {
    cout << "s4" << endl;    
    if (transition == TRANSITION_FADE) {
        _sceneIndex = _nextSceneIndex;
        ofPtr<ofxScene> previousScene;
        previousScene = _currentScene;
        _currentScene = scenes.at(_sceneIndex);
        _currentScene->setupScene(previousScene);
    } else if (transition == TRANSITION_DISSOLVE) {
        isInTransition = false;
        _currentScene = _nextScene;
        _sceneIndex = _nextSceneIndex;
    }
}
