//
//  ofxSceneManager.h
//  ofxSceneManager
//
//  Created by Koki Nomura on 2014/03/12.
//
//

#ifndef __KokiNomura__ofxSceneManager__
#define __KokiNomura__ofxSceneManager__

#include "ofxScene.h"

enum ofxSmTransition{
    TRANSITION_FADE,
    TRANSITION_DISSOLVE
};

class ofxSceneManager {
public:
    void run();
    
    void update();
    void draw();

    void changeScene();
    void changeScene(int sceneIndex);

    void addScene(ofPtr<ofxScene> pScene);

    void setExitByTime(bool b);
    void setSceneDuration(float fadeInSec, float fadeOutSec);
    void setSceneDuration(float fadeInSec, float drawingSec, float fadeOutSec);  
    void setTransitionFade();
    void setTransitionDissolve();

    vector<ofPtr<ofxScene> > scenes;

 private:
    int _sceneIndex = 0;
    int _nextSceneIndex;
    
    ofPtr<ofxScene> _currentScene;
    ofPtr<ofxScene> _nextScene;

    ofFbo _fbo;
    ofFbo _nextFbo;
    
    ofxSmTransition transition = TRANSITION_FADE;
    bool _isInTransition = false;
    
    void _onStartFadingIn(bool &b);
    void _onStartDrawing(bool &b);
    void _onFinishedDrawing(bool &b);    
    void _onStartFadingOut(bool &b);
    void _onFinishScene(bool &b);
};

#endif /* defined(__KokiNomura__ofxSceneManager__) */
