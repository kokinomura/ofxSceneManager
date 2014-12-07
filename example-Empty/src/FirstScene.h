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
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
};

#endif /* defined(__example_Empty__FirstScene__) */
