//
//  FirstScene.h
//  example-Empty
//
//  Created by Koki Nomura on 2014/03/12.
//
//

#ifndef __example_Empty__FirstScene__
#define __example_Empty__FirstScene__

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
};

#endif /* defined(__example_Empty__FirstScene__) */
