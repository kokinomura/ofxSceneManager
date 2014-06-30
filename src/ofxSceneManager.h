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

class ofxSceneManager {
public:
    void run();
    
    void update();
    void draw();

    void changeScene();
    void gotoScene(int sceneNum);

    void addScene(ofPtr<ofxScene> pScene);
    void addScene(ofPtr<ofxScene> pScene, float fadeInSec, float fadeOutSec);
    void addScene(ofPtr<ofxScene> pScene, float fadeInSec, float drawingSec, float fadeOutSec);

    void setExitByTime(bool b);
    void setSceneDuration(float fadeInSec, float fadeOutSec);
    void setSceneDuration(float fadeInSec, float drawingSec, float fadeOutSec);    

    vector<ofPtr<ofxScene> > scenes;

 private:
    int _sceneIndex = 0;
    int _nextSceneIndex = 1;
    ofPtr<ofxScene> _currentScene;

    ofFbo _fbo;

    void _initScene(int sceneIndex);
};

#endif /* defined(__KokiNomura__ofxSceneManager__) */
