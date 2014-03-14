//
//  SecondScene.h
//  example-SceneEmpty
//
//  Created by Koki Nomura on 2014/03/12.
//
//

#ifndef __example_SceneEmpty__SecondScene__
#define __example_SceneEmpty__SecondScene__

#include "ofxScene.h"

class SecondScene : public ofxScene {
public:
//    void setup();
    void setup(ofPtr<ofxScene> pPreviousScene);
    void update();
    void draw();
};

#endif /* defined(__example_Empty__SecondScene__) */
