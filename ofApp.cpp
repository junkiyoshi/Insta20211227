#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(255);
	ofEnableDepthTest();
	
	auto ico_sphere = ofIcoSpherePrimitive(250, 5);
	this->triangle_list = ico_sphere.getMesh().getUniqueFaces();
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();
	this->yolk.clear();

	for (auto& triangle : this->triangle_list) {

		glm::vec3 avg = (triangle.getVertex(0) + triangle.getVertex(1) + triangle.getVertex(2)) / 3;

		vector<glm::vec3> vertices;
		vertices.push_back(triangle.getVertex(0));
		vertices.push_back(triangle.getVertex(1));
		vertices.push_back(triangle.getVertex(2));

		for (auto& vertex : vertices) {

			auto noise_value = 0.28 + ofNoise(glm::vec4(vertex * 0.01, ofGetFrameNum() * 0.0065));
			noise_value = pow(noise_value, 2);
			auto noise_radius = 280 * noise_value;
			vertex = glm::normalize(vertex) * noise_radius;
		}

		this->yolk.addVertices(vertices);
		this->yolk.addTriangle(this->yolk.getNumVertices() - 1, this->yolk.getNumVertices() - 2, this->yolk.getNumVertices() - 3);
	}

	for (auto& triangle : this->triangle_list) {

		glm::vec3 avg = (triangle.getVertex(0) + triangle.getVertex(1) + triangle.getVertex(2)) / 3;
		auto noise_value = 0.28 + ofNoise(glm::vec4(avg * 0.01, ofGetFrameNum() * 0.0065));
		noise_value = pow(noise_value, 2);
		auto noise_radius = 280 * noise_value;
		
		if (noise_radius < 180) {

			this->mesh.addVertex(triangle.getVertex(0));
			this->mesh.addVertex(triangle.getVertex(1));
			this->mesh.addVertex(triangle.getVertex(2));
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * -0.3333);

	ofSetColor(255);
	
	this->mesh.draw();

	ofSetLineWidth(1);
	this->yolk.drawWireframe();

	ofSetColor(0);

	ofSetLineWidth(2);
	this->mesh.drawWireframe();

	this->yolk.draw();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}