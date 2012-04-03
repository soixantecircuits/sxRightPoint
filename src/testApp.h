#pragma once

#include "ofMain.h"
#include "ofxTuio.h"


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
	  myTuioClient tuioClient;
    void	tuioAdded(ofxTuioCursor & tuioCursor);
    void	tuioRemoved(ofxTuioCursor & tuioCursor);
    void	tuioUpdated(ofxTuioCursor & tuioCursor);
    void	drawCursor(ofxTuioCursor & tuioCursor);
		void drawCorners();
		void calibrate();

    enum State{
      WAITING,
      FIRSTPOINT,
      SECONDPOINT
    };

    State _state;
    ofPoint _firstPoint;
    ofPoint _secondPoint;
    ofPoint _firstPointTuio;
    ofPoint _secondPointTuio;
    float _ax, _bx, _ay, _by;
};
