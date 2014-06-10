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

// ここ雑な命名で名前空間を汚してて良くない
// あとでStateパターンに変更する
enum Transition{
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
    void setTransitionDissolve();
    void setTransitionFade();
    void setTransitionCut();

    vector<ofPtr<ofxScene> > scenes;

 private:
    int _sceneIndex = 0;
    int _nextSceneIndex;
    
    ofPtr<ofxScene> _currentScene;
    ofPtr<ofxScene> _nextScene;

    ofFbo _fbo;
    ofFbo _nextFbo;
    
    Transition transition = TRANSITION_FADE;
    bool isInTransition = false;
    
    void onStartFadingIn(bool &b);
    void onStartDrawing(bool &b);
    void onStartFadingOut(bool &b);
    void onFinishScene(bool &b);
};

#endif /* defined(__KokiNomura__ofxSceneManager__) */
