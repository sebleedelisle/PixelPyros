

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetLogLevel(OF_LOG_WARNING);
	useFbo = true;
	fboWarper1.label = "leftScreen";
	fboWarper2.label = "rightScreen";
	
	//triggerArea.set(APP_WIDTH*0.15,APP_HEIGHT*0.85,APP_WIDTH*0.7,APP_HEIGHT*0.5);
    
	fboWarper1.setDstPoint(0, ofVec2f(0,0));
	fboWarper1.setDstPoint(1, ofVec2f(APP_WIDTH/2,0));
	fboWarper1.setDstPoint(2, ofVec2f(APP_WIDTH/2,APP_HEIGHT));
	fboWarper1.setDstPoint(3, ofVec2f(0,APP_HEIGHT));
	fboWarper1.setSrcPoint(0, ofVec2f(0,0));
	fboWarper1.setSrcPoint(1, ofVec2f(APP_WIDTH/2,0));
	fboWarper1.setSrcPoint(2, ofVec2f(APP_WIDTH/2,APP_HEIGHT));
	fboWarper1.setSrcPoint(3, ofVec2f(0,APP_HEIGHT));
	
	fboWarper2.setDstPoint(0, ofVec2f(APP_WIDTH/2 +1,0));
	fboWarper2.setDstPoint(1, ofVec2f(APP_WIDTH,0));
	fboWarper2.setDstPoint(2, ofVec2f(APP_WIDTH,APP_HEIGHT));
	fboWarper2.setDstPoint(3, ofVec2f(APP_WIDTH/2 +1,APP_HEIGHT));
	fboWarper2.setSrcPoint(0, ofVec2f(APP_WIDTH/2,0));
	fboWarper2.setSrcPoint(1, ofVec2f(APP_WIDTH,0));
	fboWarper2.setSrcPoint(2, ofVec2f(APP_WIDTH,APP_HEIGHT));
	fboWarper2.setSrcPoint(3, ofVec2f(APP_WIDTH/2,APP_HEIGHT));

  
	fboWarper1.loadSettings();
	fboWarper2.loadSettings();
	
	initSounds();
	
    paused = false;
	triggerShowDebug = false;
	triggersDisabled = false;
    
    drawCameraIntoFBO = true;
    
	renderer.load("shaders/default");
    
	lastUpdateTime = ofGetElapsedTimef();
  
    ofBackground(0);

	
	cameraManager.init();
	cameraManager.addVidPlayer("../../../TestMovies/TestPyrosCamCropped.mov");
	cameraManager.addIPPlayer("network cam1", "http://10.0.1.18/axis-cgi/mjpg/video.cgi?resolution=640x480", "root", "password", 640, 480);
	cameraManager.addIPPlayer("network cam2", "http://10.0.1.19/axis-cgi/mjpg/video.cgi?resolution=640x480", "root", "password", 640, 480);
	motionManager.init(cameraManager.getWidth(), cameraManager.getHeight());

	fbo.allocate(APP_WIDTH, APP_HEIGHT, GL_RGBA, 4); 
	controlPanels.main = fbo;
	fbo.begin();
	ofClear(0,0,0);
	fbo.end(); 

    paused = false;
    altPressed = false;
	shiftPressed = false;

    triggerManager.setDisplaySize(APP_WIDTH, APP_HEIGHT);
	
	laserManager.setup(APP_WIDTH, APP_HEIGHT);

	appParams.setName("App settings");	
	appParams.add(timeSpeed.set("time speed", 1, 0,2));
	// these should be loaded and saved, but not time speed
	appParams.add(edgeBlendSize.set("edge blend size", 0, 0, 50));
	appParams.add(sceneManager.musicVolume);
	appParams.add(soundPlayer.globalVolume);
	
	
	parameterManager.registerParameterGroup("app", &appParams );
    parameterManager.registerParameterGroup("laser", &laserManager.parameters );
    parameterManager.registerParameterGroup("renderer", &renderer.paramters );
    parameterManager.registerParameterGroup("triggers", &triggerManager.parameters);
    parameterManager.registerParameterGroup("motion", &motionManager.parameters);
    parameterManager.registerParameterGroup("particles", &particleSystemManager.parameters);
    parameterManager.registerParameterGroup("laser calibration", &laserManager.calibrationParameters );
    parameterManager.registerParameterGroup("camera", &cameraManager.parameters );
       
    // Now that all of the parameters should be registered with the
	// ParameterManager, setup the control gui
    
	//calculateScreenSizes();
	
    //controlPanels.laserWarp = & laserManager.warp;
	controlPanels.setup( &parameterManager);
	timeSpeed = 1;
	
	updateScreenSizes();
	setupScenes();
	
	
	
}

//--------------------------------------------------------------
void ofApp::update(){

		
	if(cameraManager.update()){
		
		ofImage image(cameraManager.getPixelsRef()); 

		motionManager.update(cameraManager.getPixelsRef(), cameraManager.getCameraLabel());
		
		triggerManager.updateMotion(motionManager, cameraManager.warper.inverseHomography );
		
	}
	
	
	
	float time = ofGetElapsedTimef(); 
	deltaTime =  time - lastUpdateTime;
	
	if(deltaTime>0.1) deltaTime = 0.1;
	
	deltaTime*=timeSpeed;
	
	lastUpdateTime = time;
	
	
	if ( triggersDisabled != triggerManager.triggersDisabled ) {
		triggerManager.setTriggersDisabled(triggersDisabled) ;
		
	}
	
    if( !paused ) {
		
		triggerManager.update(deltaTime);
	    sceneManager.update(deltaTime);
        particleSystemManager.update(deltaTime);
    }
	
	laserManager.update();
	
//	ofPoint mousePos(ofGetMouseX(), ofGetMouseY());
//	if(uiScreenRect.inside(mousePos)) {
//		ofShowCursor();
//	} else {
//		ofHideCursor();
//	}
//	ofHideCursor();
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackground(0);
	ofSetColor(255);
	
	if(!drawCameraIntoFBO)
		cameraManager.draw();
	
	if(useFbo) {
		fbo.begin();
		ofClear(0);
	}
	
	if(drawCameraIntoFBO)
		cameraManager.draw();

	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	particleSystemManager.draw();
	
	sceneManager.draw();

	triggerManager.draw();

	laserManager.draw();

	
	if(useFbo) {
		fbo.end();
        
			
		renderer.draw(fbo, fboWarper1, fboWarper2, edgeBlendSize);
	}
	
	ofDisableBlendMode();
	ofDisableAlphaBlending();
	
	// draw the warper UIs if necessary
	fboWarper1.draw();
	fboWarper2.draw();
	
	//laserManager.drawGUI(uiScreenRect);

	
//	laserManager.showLaserPath = laserManager.showLaserPath || (controlPanels.panelMode == controlPanels.PANEL_MODE_LASER);
//	laserManager.showWarpPoints = laserManager.showWarpPoints || (controlPanels.panelMode == controlPanels.PANEL_MODE_LASER);


	
	ofPushStyle();
	float d = ofGetLastFrameTime();
	
	if(d<1.0/50.0)
		ofSetColor(ofColor::black);
	else if(d<1.0/40.0)
		ofSetColor(ofColor::green);
	else if(d<1.0/30.0)
		ofSetColor(ofColor::yellow);
	else if(d<1.0/20.0)
		ofSetColor(ofColor::orange);
	else 
		ofSetColor(ofColor::red);
	if(d>1.0/30.0)
		ofRect(uiScreenRect.x, uiScreenRect.y, (d-(1.0/30.0))*4000,4);
	ofPopStyle();
	ofDrawBitmapString(ofToString(ofGetFrameRate()),uiScreenRect.x+8,uiScreenRect.y+14);

	
	ofPoint mousePos(ofGetMouseX(), ofGetMouseY());
	float modval = 0.3;
	if(!uiScreenRect.inside(mousePos) && (modff((float)ofGetElapsedTimef(), &modval) > 0.2)) {
		ofDrawBitmapString("CHECK MOUSE CURSOR",uiScreenRect.x+8,uiScreenRect.y+34);
	}
	
	ofPushMatrix();
	ofTranslate(uiScreenRect.x+8, uiScreenRect.y+54);
	
	ofDrawBitmapString("Current Scene       : "+sceneManager.getCurrentSceneName(),0,0);
	
	ofTranslate(0,20);
	ofDrawBitmapString("Current Arrangement : "+sceneManager.getCurrentTriggerPatternName(),0,0);
	
	ofTranslate(0,20);
	ofDrawBitmapString("particle systems : "+ofToString(particleSystemManager.particleSystems.size()),0,0);
	
	ofTranslate(0,20);
	ofDrawBitmapString("spare part sys     : "+ofToString(particleSystemManager.spareParticleSystems.size()),0,0);
	
	ofTranslate(0,20);
	ofDrawBitmapString("active part sys    : "+ofToString(particleSystemManager.activeParticleSystemCount),0,0);
	
	ofTranslate(0,20);
	ofDrawBitmapString("particles          : "+ofToString(particleSystemManager.allParticleCount),0,0);
	
	ofTranslate(0,20);
	ofDrawBitmapString("spare particles    : "+ofToString(particleSystemManager.spareParticleCount),0,0);
	
	ofTranslate(0,20);
	ofDrawBitmapString("active particles   : "+ofToString(particleSystemManager.activeParticleCount),0,0);
	
	ofTranslate(0,20);
	ofDrawBitmapString("physics objects    : "+ofToString(particleSystemManager.physicsObjects.size()),0,0);
	
	ofTranslate(0,20);
	ofDrawBitmapString("spare physics objs : " +ofToString(particleSystemManager.sparePhysicsObjects.size()),0,0);

	ofTranslate(0,20);
	ofDrawBitmapString("active physics objs: " +ofToString(particleSystemManager.activePhysicsObjectCount),0,0);

	ofPopMatrix();
	
    controlPanels.draw(motionManager);
	sceneManager.drawGUI();
	if(screens.size()==1) {
		laserManager.renderLaserPath(ofRectangle(0,0,APP_WIDTH, APP_HEIGHT), (controlPanels.panelMode == controlPanels.PANEL_MODE_LASER));
	} else {
		laserManager.renderLaserPath(controlPanels.getPreviewScreenRect(), (controlPanels.panelMode == controlPanels.PANEL_MODE_LASER));
	}
	
	/*
	ofVec3f testpoint(ofGetMouseX(),ofGetMouseY(),-1000);
	ofCamera camera;
	camera.begin();
	ofNoFill();
	ofSetColor(255,0,0);
	
	ofCircle(testpoint,40);
	ofSetColor(255);
	cout << (camera.worldToScreen(testpoint)) << endl;
	camera.end();
	ofCircle(camera.worldToScreen(testpoint), 100);*/
	
	//ofGetCurrentRenderer();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
	//bool shiftPressed = (glutGetModifiers() & GLUT_ACTIVE_SHIFT);
	if(key == OF_KEY_SHIFT) {
        shiftPressed = true;
    }

	if(key == OF_KEY_ALT){
        altPressed = true;
    }

   // if( shiftPressed ) {
        if(key=='w') {
            cameraManager.toggleWarperGui();
        }else if(key=='e') {
            drawCameraIntoFBO = !drawCameraIntoFBO;
        } else if (key=='1') {
            fboWarper1.visible = !fboWarper1.visible;
        } else if (key=='2') {
            fboWarper2.visible = !fboWarper2.visible;
        }

        //if(!cameraManager.warper.guiVisible) {

        if(key==OF_KEY_LEFT) {
            if(altPressed)
                sceneManager.prevScene();
            else
                sceneManager.previousPattern();
        } else if(key==OF_KEY_RIGHT) {
            if(altPressed)
                sceneManager.nextScene();
            else
                sceneManager.nextPattern();
        }

        //}
        if(key=='c') {
            cameraManager.next();
        } else if( key == 'R' ) {
            if(!cameraManager.capturing)
                cameraManager.beginCapture();
            else
                cameraManager.endCapture();
            
        } else if( key == 'p' ) {
            paused = !paused;
        }
        else if ( key == 't' )
        {
            triggersDisabled = !triggersDisabled ;
        }
        else if ( key == 'd' )
        {
            triggerManager.toggleDebug();//triggerShowDebug = !triggerShowDebug ;
        }
        else if ( key == 'k' )
        {
            particleSystemManager.killAllParticlesParam = true ;
        }
        else if ( key == 'r' )
        {
            //sequencer.runSequence("Intro");
        }
	else if(key == 'f') {
		ofToggleFullscreen();
		updateScreenSizes();
	}
   // }
    
    controlPanels.keyPressed(key);
	
	
}

void ofApp::keyReleased(int key){
	if(key == OF_KEY_SHIFT) shiftPressed = false;
    if(key == OF_KEY_ALT) altPressed = false;
}

void ofApp:: mousePressed(int x, int y, int button ) { 

}

void ofApp:: setupScenes() { 
	
	
	TriggerRechargeSettings::superFastMultiples->minTriggerInterval = 0.1;
	TriggerRechargeSettings::fastMultiples->triggerPower = 0.3;
	
	TriggerRechargeSettings::mediumMultiples->minTriggerInterval = 0.2;
	TriggerRechargeSettings::mediumMultiples->triggerPower = 0.3;
	TriggerRechargeSettings::mediumMultiples->restoreSpeed = 0.5;
	
	TriggerRechargeSettings::fastMultiples->minTriggerInterval = 0.1;
	TriggerRechargeSettings::fastMultiples->triggerPower = 0.3;
	TriggerRechargeSettings::fastMultiples->restoreSpeed = 0.7;
	

	
	sceneManager.addScene(new SceneCalibration("Calibration"));
	sceneManager.addScene(new SceneSlideshow("SlideShow"));
	
	// This scene was to launch the Brighton Digital Festival
	//sceneManager.addScene(new SceneLaunch("Launch", particleSystemManager));

	SceneIntro* intro = new SceneIntro("Intro");
	sceneManager.addScene(intro);
	intro->loadMusicFile("InMotionEdit.aif");

	sceneManager.addScene(new SceneVectorizer("Vectorizer"));
	
	sceneManager.addScene(new SceneRealistic("Realistic - UFO"));
	
	sceneManager.addScene(new SceneRetro("Retro"));
	
	sceneManager.addScene(new SceneGame("Game"));
	
	sceneManager.addScene(new SceneNadia("Nadia"));
	
	sceneManager.addScene(new SceneSpace("Space"));

	sceneManager.changeScene("Intro");
	
	
	
}

void ofApp::initSounds() {
	soundPlayer.defaultPath = "../../../Sounds/";
	
	
	soundPlayer.addSound("Crackle", "RocketFountain", 1, 1.2, 0.5,"mp3");
	soundPlayer.addSound("ExplosionSynth1", "ExplosionSynth1");
	
	soundPlayer.addSound("mortar", "SynthThud", 1, 0.8, 0.2, "mp3");
	soundPlayer.addSound("mortar", "mortar", 1, 0.8, 0.2, "mp3");
	soundPlayer.addSound("DirtyTechno", "DirtyTechno", 0.1, 0.8, 0.4, "aif", 0.1);
	
	
	soundPlayer.addSound("LaunchTechno", "LaunchTechnoLow", 1, 0.3, 0.2, "aif", 0.01);
	soundPlayer.addSound("LaunchSweep", "LaunchSweep", 0.2, 2, 0.2, "wav", 0.02);
	soundPlayer.addSound("RetroLaunch", "RetroLaunch", 0.2, 1, 0.2, "wav", 0.02);
	soundPlayer.addSound("RetroExplosion", "RetroExplosion", 0.9, 1, 0.2, "aif", 0.02);
	soundPlayer.addSound("RetroFountain", "RetroFountain", 0.2, 1.5, 0.8, "wav", 0.02);

	soundPlayer.addSound("SynthKick", "SynthKick", 0.3, 1.0, 0.1, "wav", 0.01);
	
	soundPlayer.addSound("Banger", "Banger", 1.0, 0.4, 0.0, "wav", 0.2);
	soundPlayer.addSound("Crackle", "Crackle", 0.1, 0.8, 0.3, "wav", 0.2);
	
	soundPlayer.addSound("Launch", "Launch", 0.8, 1.0, 0.1, "wav", 0.2);
	soundPlayer.addSound("LaunchRocketSharp", "LaunchRocketSharp", 0.6, 1.0, 0.05, "wav", 0.2);
	soundPlayer.addSound("SoftExplosion", "SoftExplosion", 1.0, 1.0, 0.2, "wav", 0.2);
	soundPlayer.addSound("Fuse", "Fuse", 0.2, 1.0, 0.2, "aif", 0.2);
	soundPlayer.addSound("Sparkler", "Sparkler", 1.0, 1.0, 0.2, "aif", 0.2);
	soundPlayer.addSound("Woosh", "Woosh", 0.15, 0.9, 0.2, "wav", 0.2);

	
	
	soundPlayer.globalVolume = 1;
	
}



void ofApp::mouseMoved( int x, int y ){
	
	triggerManager.mouseMoved(x, y);

}

void ofApp::calculateScreenSizes(){
    int monitorCount;
	
	GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
	
	cout << "RESIZE" << " " << ofGetWindowMode()<< endl;
    screens.clear();
    
    int leftMost = 0,
		topMost = 0;
    
    for(int i = 0; i < monitorCount; i++){
		
		ofRectangle screen;
		
		int x=0,
		y=0,
		w=0,
		h=0;
		
        glfwGetMonitorPos(monitors[i],&x,&y);
        const GLFWvidmode * desktopMode = glfwGetVideoMode(monitors[i]);
		screen.x = x;
		screen.y = y;
        screen.width = desktopMode->width;
        screen.height = desktopMode->height;
        
        screens.push_back(screen);
        cout << i << " " << screen << endl;
		if( leftMost > screen.x ) leftMost = screen.x;
		if( topMost > screen.y ) topMost = screen.y;

    }
    
    for(int i = 0; i < monitorCount; i++){
		screens[i].x -= leftMost;
		screens[i].y -= topMost;

    }
    
	std::sort( screens.begin(), screens.end(), screenSort );
	
    for(int i = 0; i < monitorCount; i++){
		cout << i << " " << screens[i] << endl;
    }
    
	uiScreenRect = screens.back();
		

}

void ofApp::updateScreenSizes() {
	
//	ofToggleFullscreen();
	//cout << ofGetWindowMode()<< endl;
	
    calculateScreenSizes();

	controlPanels.updatePositions(screens);
	sceneManager.updateUIScreen(uiScreenRect);
	//laserManager.updatePreviewScreenRect();
	// todo - this should probably take into account the size
	// of the preview screen too!
	laserManager.warp.setOffset( uiScreenRect.x, uiScreenRect.y );
	
	

}
//--------------------------------------------------------------
void ofApp::windowResized(int width, int height){
	
	updateScreenSizes();
	
}


void ofApp::exit() { 
    controlPanels.exit();
    sceneManager.exit();
}
