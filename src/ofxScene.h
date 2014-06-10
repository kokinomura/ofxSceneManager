//
//  ofxScene.h
//  ofxSceneManager
//
//  Created by Koki Nomura on 2014/01/22.
//
//

#pragma once

#include "ofMain.h"
#include "ofxTween.h"

class ofxScene {
public:

#pragma mark - Basics
    void setupScene(ofPtr<ofxScene> previousScene) {
        setup();
        if (!_isSetupOverridden) {
            // If a subclass overrides setup(),
            // ofxScene won't call setup(previousScene).
            setup(previousScene);
        }
        startFadingIn();
    }
    
    void updateScene() {
        _alphaTween.update();
        
        if (finishedFadeIn()) {
            startDrawing();
        } else if (finishedDrawing()) {
            startFadingOut();
        } else if (finishedFadeOut()) {
            finishScene();
        } else if (isFinished()) {
            return;
        }
        update();
    }
    
    void drawScene() {
        draw();
    }
    
    void exitScene() {
        // Call this function to exit scene.
        startFadingOut();
    }
    
#pragma mark - Status
    bool isFadingIn() {
        return _status == FADINGIN;
    }
    
    bool isDrawing() {
        return _status == DRAWING;
    }
    
    bool isFadingOut() {
        return _status == FADINGOUT;
    }
    
    bool isFinished() {
        return _status == FINISHED;
    }
    
#pragma mark - Duration
    void setSceneDuration(float fadeInSec, float fadeOutSec) {
        _fadeInSec = fadeInSec;
        _fadeOutSec = fadeOutSec;
    }
    
    void setSceneDuration(float fadeInSec, float drawingSec, float fadeOutSec) {
        _fadeInSec = fadeInSec;
        _drawingSec = drawingSec;
        _fadeOutSec = fadeOutSec;
    }
    
    float getFadeInDuration() {
        return _fadeInSec;
    }
    
    float getDrawingDuration() {
        return _drawingSec;
    }
    
    float getFadeOutDuration() {
        return _fadeOutSec;
    }
    
#pragma mark - Etc
    void setExitByTime(bool b) {
        _bExitByTime = b;
    }
    
    float getSceneAlpha() {
        return _alphaTween.getTarget(0);
    }
    
#pragma mark - Events
    ofEvent<bool> startFadingInEvent;  // The arg is currently not used.
    ofEvent<bool> startDrawingEvent;
    ofEvent<bool> finishedDrawingEvent;    
    ofEvent<bool> startFadingOutEvent;
    ofEvent<bool> finishSceneEvent;

private:
    bool _bExitByTime = false;
    enum {FADINGIN, DRAWING, FADINGOUT, FINISHED} _status = FINISHED;
    
    float _fadeInSec = 0.3;
    float _drawingSec = 1.0;
    float _fadeOutSec = 0.3;
    float _statusEndTime = 0;
    
    ofxTween _alphaTween;
    ofxEasingLinear _easing;
    
    bool _isSetupOverridden = true;  // a bit hacky...
    
#pragma mark - To be overridden
    virtual void setup() {_isSetupOverridden = false;}  // a bit hacky...
    virtual void setup(ofPtr<ofxScene> previousScene) {}
    virtual void update() {}
    virtual void draw() {}
    
    virtual void willFadeIn() {}
    virtual void willDraw() {}
    virtual void willFadeOut() {}
    virtual void willExit() {}
    
#pragma mark - Start/finish
    void startFadingIn() {
        if (_status == FADINGIN) {
            return;
        }
        _status = FADINGIN;
        _statusEndTime = _fadeInSec + ofGetElapsedTimef();
        _alphaTween.setParameters(_easing, ofxTween::easeOut, 0, 255, _fadeInSec*1000, 0);
        willFadeIn();
        
        bool b = true;
        ofNotifyEvent(startFadingInEvent, b, this);
    }
    
    void startDrawing() {
        if (_status == DRAWING) {
            return;
        }
        _status = DRAWING;
        if (_bExitByTime) {
            _statusEndTime = _drawingSec + ofGetElapsedTimef();
        }
        willDraw();
        
        bool b = true;        
        ofNotifyEvent(startDrawingEvent, b, this);
    }
    
    void startFadingOut() {
        if (_status == FADINGOUT) {
            return;
        }
        _status = FADINGOUT;
        _statusEndTime = _fadeOutSec + ofGetElapsedTimef();
        _alphaTween.setParameters(_easing, ofxTween::easeOut, 255, 0, _fadeOutSec*1000, 0);  
        willFadeOut();
        
        bool b = true;        
        ofNotifyEvent(startFadingOutEvent, b, this);        
    }
    
    void finishScene() {
        if (_status == FINISHED) {
            return;
        }
        _status = FINISHED;
        willExit();
        
        bool b = true;        
        ofNotifyEvent(finishSceneEvent, b, this);
    }
    
#pragma mark - Status
    bool finishedFadeIn() {
        return _status == FADINGIN && _statusEndTime < ofGetElapsedTimef();
    }
    
    bool finishedDrawing() {
        if (_bExitByTime) {
            bool b = _status == DRAWING && _statusEndTime < ofGetElapsedTimef();
            if (b) {
                ofNotifyEvent(finishedDrawingEvent, b, this);
            }
            return b;
        } else {
            return false;
        }
    }
    
    bool finishedFadeOut() {
        return _status == FADINGOUT && _statusEndTime < ofGetElapsedTimef();
    }
};