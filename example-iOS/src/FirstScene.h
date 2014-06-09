//
//  FirstScene.h
//  example-Simple
//
//  Created by Koki Nomura on 2014/03/12.
//
//

#ifndef __example_Simple__FirstScene__
#define __example_Simple__FirstScene__

#include "ofxScene.h"

class FirstScene : public ofxScene {
public:
    void setup();
    void update();
    void draw();
    
    void willFadeIn();
    void willDraw();
    void willFadeOut();
    void willExit();
    
    int y=0;
};

#endif /* defined(__example_Simple__FirstScene__) */
