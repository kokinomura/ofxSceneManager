# ofxSceneManager

A lightweight addon for openFrameworks supporting crossfading, data passing and event handling.

You can write your own scenes just like ofApp!

## Dependency

- ofxTween (https://github.com/arturoc/ofxTween)


## Getting Started

- Write your own subclasses of ofxScene.

```cpp
#include "ofxScene.h"

class FirstScene : public ofxScene {
public:
    void setup();
    void update();
    void draw();
    void exit();
}
```

- Fill all functions you need.

You have basic functions of ofApp and four additional functions you can override, and none of them are mandatory.

```cpp
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
```

- Instantiate ofxSceneManager and add scenes.

```cpp
class testApp : public ofBaseApp {
public:
    // definitions
    ofxSceneManager sceneManager;
}
```

```cpp
void testApp::setup() {
    sceneManager.addScene(ofPtr<ofxScene>(new FirstScene));
    sceneManager.addScene(ofPtr<ofxScene>(new SecondScene));
}
```


- Run the ofxSceneManager.

```cpp
void testApp::setup() {
    sceneManager.addScene(ofPtr<ofxScene>(new FirstScene));
    sceneManager.addScene(ofPtr<ofxScene>(new SecondScene));

    sceneManager.run();
}

void testApp::update() {
    sceneManager.update();
}

void testApp::draw() {
    sceneManager.draw();
}
```


## Functionality

### Transition
ofxSceneManager supports two types of transition.
- Transition when you trigger. (default)
- Transition after certain period of time.

```cpp
void testApp::setup() {
    sceneManager.addScene(ofPtr<ofxScene>(new FirstScene));
    sceneManager.addScene(ofPtr<ofxScene>(new SecondScene));
    sceneManager.setExitByTime(false);  // You don't need this line since it's false by default.
    sceneManager.setSceneDuration(0.3, 0.3);  //fade-in, fade-out time.
}

void testApp::keyPressed(int key){
    if (key == ' ') {
        sceneManager.changeScene();
    }
}
```

```cpp
void testApp::setup() {
    sceneManager.addScene(ofPtr<ofxScene>(new FirstScene));
    sceneManager.addScene(ofPtr<ofxScene>(new SecondScene));
    sceneManager.setExitByTime(true);
    sceneManager.setSceneDuration(0.3, 15.0, 0.3);  //fade-in, drawing, fade-out time respectively.
}
```

Call ofxSceneManager::changeScene() to change scenes.


### Fading
ofxSceneManager does fading by default, and the background color while transition is a default color of oF.
If you want another color or a picture as a background, you can change in `testApp::draw()`;

```cpp
void testApp::draw() {
	ofBackground(255, 255, 0);
	sceneManager.draw();
}
```

### Data Passing
You have two kinds of setup(). ofxSceneManager calls one you implement.
```cpp
    void setup()
    void setup(ofPtr<ofxScene> previousScene)
```

If a scene needs data of a previous scene,
implement ```void setup(ofPtr<ofxScene> previousScene)``` instead of ```void setup()```.
You can get data as public variables of the previous scene.

```cpp
void SecondScene::setup() {

}
```

```cpp
void SecondScene::setup(ofPtr<ofxScene> previousScene) {

}
```

Note: If you implement both, only ```setup()``` will be called and ```setup(ofPtr<ofxScene> previousScene)``` will be ignored.
