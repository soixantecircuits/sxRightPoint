#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofAddListener(tuioClient.cursorAdded, this, &testApp::tuioAdded);
	ofAddListener(tuioClient.cursorRemoved, this, &testApp::tuioRemoved);
	ofAddListener(tuioClient.cursorUpdated, this, &testApp::tuioUpdated);
	tuioClient.start(3333);

  _firstPoint.set(100, 100);
  _secondPoint.set(ofGetWidth()-100, ofGetHeight()-100);

}

//--------------------------------------------------------------
void testApp::update(){
	tuioClient.getMessage();
}

//--------------------------------------------------------------
void testApp::draw(){
  ofBackground(0);
  drawCorners();
  list<ofxTuioCursor*> cursorList = tuioClient.getTuioCursors();
  list<ofxTuioCursor*>::iterator tit;
  for (tit=cursorList.begin(); tit != cursorList.end(); tit++) {
    drawCursor((*tit)[0]);
  }
}

//--------------------------------------------------------------
void testApp::drawCorners(){
      string str = "PRESS SPACEBAR TO START";
  switch (_state){
    case WAITING:
      glColor3f(1.0, 1.0, 0.0);
      ofEllipse(_firstPoint.x, _firstPoint.y, 20.0, 20.0);
      glColor3f(1.0, 1.0, 0.0);
      ofEllipse(_secondPoint.x, _secondPoint.y, 20.0, 20.0);
      ofDrawBitmapString(str, ofGetWidth()/2, ofGetHeight()/2);
      break;
    case FIRSTPOINT:
      glColor3f(1.0, 0.0, 0.0);
      ofEllipse(_firstPoint.x, _firstPoint.y, 20.0, 20.0);
      glColor3f(1.0, 1.0, 0.0);
      ofEllipse(_secondPoint.x, _secondPoint.y, 20.0, 20.0);
      break;
    case SECONDPOINT:
      glColor3f(1.0, 1.0, 0.0);
      ofEllipse(_firstPoint.x, _firstPoint.y, 20.0, 20.0);
      glColor3f(1.0, 0.0, 0.0);
      ofEllipse(_secondPoint.x, _secondPoint.y, 20.0, 20.0);
      break;
  }
}
      
//--------------------------------------------------------------
void testApp::keyPressed(int key){
  if(key == 'f'){
    ofToggleFullscreen();
  }
  else if(key == ' '){
    if (_state == WAITING){
      _state = FIRSTPOINT;
    }
  }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void testApp::tuioAdded(ofxTuioCursor &tuioCursor){	
  if (_state == FIRSTPOINT){
    _firstPointTuio.set(tuioCursor.getX(), tuioCursor.getY());
    _state = SECONDPOINT;
  }
  else if (_state == SECONDPOINT){
    _secondPointTuio.set(tuioCursor.getX(), tuioCursor.getY());
    _state = WAITING;
    calibrate();
  }
}

//--------------------------------------------------------------
void testApp::tuioUpdated(ofxTuioCursor &tuioCursor){
}

//--------------------------------------------------------------
void testApp::tuioRemoved(ofxTuioCursor &tuioCursor){
}

//--------------------------------------------------------------
void testApp::drawCursor(ofxTuioCursor &tuioCursor){
  float x = tuioCursor.getX()*ofGetWidth();
  float y = tuioCursor.getY()*ofGetHeight();
  glColor3f(1.0,1.0,1.0);
  ofEllipse(x, y, 10.0, 10.0);
  string str = "SessionId: "+ofToString((int)(tuioCursor.getSessionId()));
  ofDrawBitmapString(str, x - 10.0, y + 25.0);
  x = (_ax * tuioCursor.getX()) + _bx;
  y = (_ay * tuioCursor.getY()) + _by;
  glColor3f(0.0,0.0,1.0);
  ofEllipse(x, y, 10.0, 10.0);
}

//--------------------------------------------------------------
void testApp::calibrate(){
  _ax = (_firstPoint.x - _secondPoint.x) / (_firstPointTuio.x - _secondPointTuio.x);
  _bx = _firstPoint.x - (_ax * _firstPointTuio.x);
  _ay = (_firstPoint.y - _secondPoint.y) / (_firstPointTuio.y - _secondPointTuio.y);
  _by = _firstPoint.y - (_ay * _firstPointTuio.y);
}

