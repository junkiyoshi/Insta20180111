#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	ofSetLineWidth(0.5);
}

//--------------------------------------------------------------
void ofApp::update() {
	float x = ofMap(ofNoise(ofGetFrameNum() * 0.05), 0, 1, -10, 10);
	float y = ofMap(ofNoise(ofGetFrameNum() * 0.05 + 100), 0, 1, -10, 10);
	float z = ofMap(ofNoise(ofGetFrameNum() * 0.05 + 200), 0, 1, -10, 10);

	this->target = ofVec3f(x, y, z);
	this->target.normalize();
	this->target *= 250;

	this->target_log.push_back(this->target);

	if (this->target_log.size() > 1280) {
		this->target_log.clear();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	this->cam.begin();
	ofRotateX(ofGetFrameNum() * 0.5);
	ofRotateY(ofGetFrameNum() * 0.25);

	ofSetColor(255);
	ofDrawLine(this->target, ofVec3f());

	ofSetColor(255, 32);
	float distance;
	for (int i = 0; i < this->target_log.size(); i++) {
		vector<ofVec3f> near_points;

		for (int j = i; j < this->target_log.size(); j++) {
			distance = this->target_log[i].distanceSquared(this->target_log[j]);
			if (distance < 100 * 100) {
				near_points.push_back(this->target_log[j]);
			}
		}

		if (near_points.size() >= 3) {
			ofBeginShape();
			for (int j = 0; j < near_points.size(); j++){
				ofVertex(near_points[j]);
			}
			ofEndShape(true);
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
