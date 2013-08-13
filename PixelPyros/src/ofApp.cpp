

#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	
	useFbo = true;
	fboWarper1.label = "leftScreen";
	fboWarper2.label = "rightScreen";
	
	triggerArea.set(APP_WIDTH*0.15,APP_HEIGHT*0.85,APP_WIDTH*0.7,APP_HEIGHT*0.5); 
	
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
//	fboWarper2.setSrcPoint(0, ofVec2f(0,0));
//	fboWarper2.setSrcPoint(1, ofVec2f(APP_WIDTH/2,0));
//	fboWarper2.setSrcPoint(2, ofVec2f(APP_WIDTH/2,APP_HEIGHT));
//	fboWarper2.setSrcPoint(3, ofVec2f(0,APP_HEIGHT));

  
	fboWarper1.loadSettings();
	fboWarper2.loadSettings();
	
	initSounds();
	
    paused = false;
	triggerShowDebug = false;
	triggersDisabled = false;
    
    drawCameraIntoFBO = true;
    renderer.load("shaders/default");
    
	ofSetFrameRate(60);
	//ofSetVerticalSync(true); // now on by default
	lastUpdateTime = ofGetElapsedTimef();
	
	
	    
    ofBackground(0);

	setupScenes(); 
	
	cameraManager.init();
	cameraManager.addVidPlayer("../../../TestMovies/TestPyrosCamCropped.mov");

	
	motionManager.init(cameraManager.getWidth(), cameraManager.getHeight());
	
	setupControlPanel();
	

	
	gui.hide();
	
	fbo.allocate(APP_WIDTH, APP_HEIGHT);
	fbo.begin();
	ofClear(0,0,0);
	fbo.end(); 

	oscManager.setup () ;
	
    paused = false;
	shiftPressed = false;

	


}

//--------------------------------------------------------------
void ofApp::update(){

	
	
	oscManager.update () ;
	
	settingsManager.update(); 
	
	if(cameraManager.update()){
		
		ofImage image(cameraManager.getPixelsRef()); 

		motionManager.update(cameraManager.getPixelsRef());
		
		sceneManager.updateMotion(motionManager, cameraManager.warper.inverseHomography );
		
	}
	
	float time = ofGetElapsedTimef(); 
	float deltaTime =  time - lastUpdateTime;

	lastUpdateTime = time;
	
	if (( triggerAreaWidth*APP_WIDTH!=triggerArea.width ) ||
		(triggerAreaHeight*APP_HEIGHT != triggerArea.height) ||
		(triggerAreaCentreY*APP_HEIGHT != triggerArea.getCenter().y) ||
		(triggerSpacing != sceneManager.triggerSpacing ) ) {
		triggerArea.width = triggerAreaWidth*APP_WIDTH;
		triggerArea.x = (APP_WIDTH - triggerArea.width)/2;
		triggerArea.height = (APP_HEIGHT * triggerAreaHeight);
		triggerArea.y = (APP_HEIGHT * triggerAreaCentreY) - (triggerArea.height/2) ;
		
		sceneManager.updateTriggerSettings(triggerArea, triggerSpacing) ;
	}
	
	if ( triggerShowDebug != sceneManager.triggerShowDebug ) {
		sceneManager.updateTriggerDebug(triggerShowDebug) ;
		
	}
	
	if ( triggersDisabled != sceneManager.triggersDisabled ) {
		sceneManager.setTriggersDisabled(triggersDisabled) ;
		
	}
	
    if( !paused ) {
		
        sceneManager.update(deltaTime*0.5);
        particleSystemManager.update(deltaTime*0.5);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackground(0);
	ofSetColor(255);
	
	if(!drawCameraIntoFBO)
		cameraManager.draw(0,0);
	
	if(useFbo) {
		fbo.begin();
		
		
		
//		FOR TRAILS :
//		ofEnableAlphaBlending();
//		ofSetColor(0, 100);
//		ofRect(0,0,APP_WIDTH,APP_HEIGHT);
//		ofDisableAlphaBlending();
//		
		ofClear(0);
		//ofSetColor(255);
        
	}
	
	if(drawCameraIntoFBO)
		cameraManager.draw(0,0);
	

	ofPushMatrix();
	
	// change perspective so we're looking up
	// THIS SHOULD BE MOVED INTO PARTICLE SYSTEMS I THINK
	//ofTranslate(0,ofGetHeight()*0.9);
	//ofRotateX(5);
	//ofTranslate(0,ofGetHeight()*-0.9);

	ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ADD);

	particleSystemManager.draw();
	
    ofPopMatrix();
    
	// this draws all the triggers, should be outside of the rotation upwards
    // a better solution would be to alter matrix for the particle system dependent on
    // start position. 
	sceneManager.draw(); 
	
	float rectWidth = APP_WIDTH*0.6;
	float rectHeight = APP_HEIGHT*0.3;
	
	// For testing the text box!
	if(ofGetMousePressed()) {
		
		rectWidth = ofGetMouseX() - APP_WIDTH*0.2;
		rectHeight = ofGetMouseY() - APP_HEIGHT *0.1;
		
	}



	ofSetColor(255);
	//ofNoFill();
	//ofRect(triggerArea);
	
	
	if(useFbo) {
		fbo.end();
        
		ofEnableBlendMode(OF_BLENDMODE_ADD);
			
		renderer.draw(fbo, fboWarper1, fboWarper2);
	}
	
	ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
//	ofDrawBitmapString(ofToString(particleSystemManager.particleSystems.size()),20,35);
//	ofDrawBitmapString(ofToString(particleSystemManager.activeParticleCount),20,50);
//	ofDrawBitmapString(ofToString(particleSystemManager.activePhysicsObjectCount),20,65);
    
//	ofDrawBitmapString("L: " + ofToString(gui.getValueF("SHADER_BLACK")),20,150);
//	ofDrawBitmapString("H: " + ofToString(gui.getValueF("SHADER_WHITE")),20,165);
//	ofDrawBitmapString("G: " + ofToString(gui.getValueF("SHADER_GAMMA")),20,180);
//	ofDrawBitmapString("Bloom: " + ofToString(gui.getValueF("SHADER_BLOOM")),20,195);
    
	// DEBUG DATA FOR SCENES / ARRANGEMENTS / TRIGGERS.
	// Should probably put this in a GUI or something... :) 
	
	
	
	ofDisableBlendMode();
	ofFill();
	
	
	// draw the warper UIs if necessary
	fboWarper1.draw(ofGetKeyPressed('l'));
	fboWarper2.draw(ofGetKeyPressed('l'));
	
 
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
	//bool shiftPressed = (glutGetModifiers() & GLUT_ACTIVE_SHIFT);
	if(key == OF_KEY_SHIFT) shiftPressed = true;
	
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
			if(shiftPressed)
				sceneManager.prevScene();
			else
				sceneManager.previousArrangement();
		} else if(key==OF_KEY_RIGHT) {
			if(shiftPressed)
				sceneManager.nextScene();
			else
				sceneManager.nextArrangement();
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
		triggerShowDebug = !triggerShowDebug ;
	}
	else if ( key == 'k' )
	{
		particleSystemManager.killAllParticlesFlag = true ;
	}
	else if ( key == 'r' )
	{
		sceneManager.showSlideShow = true ;
	}
	
}

void ofApp::keyReleased(int key){
	if(key == OF_KEY_SHIFT) shiftPressed = false;
	
	
	
}

void ofApp:: mousePressed(int x, int y, int button ) { 

}

void ofApp:: setupScenes() { 
	
	sceneManager.addScene(new SceneCalibration("Calibration", particleSystemManager, triggerArea));
	sceneManager.addScene(new SceneSlideshow("SlideShow", particleSystemManager, triggerArea));
	
	// This scene was to launch the Brighton Digital Festival
	//sceneManager.addScene(new SceneLaunch("Launch", particleSystemManager, triggerArea));

	sceneManager.addScene(new SceneIntro("Intro", particleSystemManager, triggerArea));
	
	sceneManager.addScene(new SceneRetro("Retro", particleSystemManager, triggerArea));
	
	sceneManager.addScene(new SceneRealistic("Lights", particleSystemManager, triggerArea));
	sceneManager.addScene(new SceneTron("Vectorizer", particleSystemManager, triggerArea));
	
	sceneManager.addScene(new SceneSpace("Stargazer", particleSystemManager, triggerArea));
	
	sceneManager.changeScene(1);
	
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
	
	vector <Scene*>& scenes = sceneManager.scenes;
	for(int j = 0 ; j<scenes.size(); j++ ) { 
		Scene* scene1 = scenes[j];
		vector<Arrangement*> * arrangements = &scene1->arrangements;
		for(int k = 0; k<arrangements->size(); k++)
		{
			vector <TriggerBase*> triggers = arrangements->at(k)->triggers;
			for(int i = 0; i<triggers.size(); i++) { 
				TriggerBase * trigger = triggers[i]; 
				float distance = trigger->pos.distance(ofVec3f(x,y));
				if(distance<20) {
					trigger->registerMotion(1.0f-(distance/20.0f)); 
					
				}
				
			}
		}
	}
}


void ofApp::setupControlPanel() { 
	gui.setup(450, ofGetHeight());

	ofxControlPanel::setBackgroundColor(simpleColor(30, 30, 60, 200));
	ofxControlPanel::setTextColor(simpleColor(240, 50, 50, 255));
	
//	gui.loadFont("Andale Mono.ttf", 8);		
	gui.bIgnoreLayout = true;   // doesn't seem to do anything.
                                // and hungarian notation? Ew! 
	gui.addPanel("Cameras");
	
	cameraManager.initControlPanel(gui);

	gui.setWhichColumn(1);
    
	gui.addLabel("Levels");
	
	gui.addSlider("Black Point", "SHADER_BLACK", 0, 0, 1.0, false);//->setDimensions(400, 10);
	gui.addSlider("Gamma", "SHADER_GAMMA", 0, 0, 10.0, false);//->setDimensions(400, 10);
	gui.addSlider("White Point", "SHADER_WHITE", 0, 0, 1.0, false);//->setDimensions(400, 10);
	gui.addSlider("Bloom", "SHADER_BLOOM", 0, 0, 10.0, false);//->setDimensions(400, 10);
	
	 
	gui.addPanel("Motion");
	
	motionManager.initControlPanel(gui);
	
	gui.addPanel("Triggers");
	
	gui.addSlider("Area width", "TRIGGER_AREA_WIDTH", 0, 0, 1.0, false);//->setDimensions(400, 10);
	gui.addSlider("Area height", "TRIGGER_AREA_HEIGHT", 0, 0, 0.5, false);//->setDimensions(400, 10);
	gui.addSlider("Area y pos", "TRIGGER_AREA_Y", 0, 0.5, 1, false);//->setDimensions(400, 10);
	gui.addSlider("Spacing", "TRIGGER_SPACING", 0, 0, 400, false);//->setDimensions(400, 10);
	

	ofAddListener(gui.guiEvent, this, &ofApp::eventsIn);
	
	
	gui.setupEvents();
	gui.enableEvents();

	
	gui.loadSettings("controlPanelSettings.xml");

	
	
	settingsManager.setup(&oscManager, &gui) ;
	
	
	settingsManager.addSettingFloat(&motionManager.thresholdLevel, "THRESHOLD", "/PixelPyros/Setup/Threshold/x", 0, 255);
	settingsManager.addSettingFloat(&motionManager.motionSensitivity, "MOTION_SENSITIVITY", "/PixelPyros/Setup/Sensitivity/x", 1, 5);
	
	settingsManager.addSettingFloat(&triggerAreaWidth, "TRIGGER_AREA_WIDTH", "/PixelPyros/Setup/Width/x", 0, 1);
	settingsManager.addSettingFloat(&triggerAreaHeight, "TRIGGER_AREA_HEIGHT", "/PixelPyros/Setup/Height/x",0, 0.5);
	settingsManager.addSettingFloat(&triggerAreaCentreY, "TRIGGER_AREA_Y", "/PixelPyros/Setup/VPOS/x",0.5, 1);
	settingsManager.addSettingFloat(&triggerSpacing, "TRIGGER_SPACING", "/PixelPyros/Setup/Spacing/x",0, 400);
	settingsManager.addSettingFloat(&triggerSpacing, "TRIGGER_SPACING", "/PixelPyros/Spacing/x",0, 400);
	
	settingsManager.addSettingBool(&showDiffImage, "", "/PixelPyros/Setup/ShowDiff/x", true);
	
	settingsManager.addSettingBool(&triggersDisabled, "", "/PixelPyros/Setup/MotionDisable/x", true);
	settingsManager.addSettingBool(&triggerShowDebug, "", "/PixelPyros/Setup/TriggerDebug/x", true);
	settingsManager.addSettingBool(&triggersDisabled, "", "/PixelPyros/MotionDisable/x", true);
	settingsManager.addSettingBool(&triggerShowDebug, "", "/PixelPyros/TriggerDebug/x", true);
	
	settingsManager.addSettingFloat(&renderer.blackPoint, "SHADER_BLACK", "/PixelPyros/Setup/BlackLevel/x",0, 1);
	settingsManager.addSettingFloat(&renderer.whitePoint, "SHADER_WHITE", "/PixelPyros/Setup/WhiteLevel/x",0, 1);
	settingsManager.addSettingFloat(&renderer.gammaValue, "SHADER_GAMMA", "/PixelPyros/Setup/GammaLevel/x",0, 10);
	settingsManager.addSettingFloat(&renderer.bloomValue, "SHADER_BLOOM", "/PixelPyros/Setup/BloomLevel/x",0, 3);
	settingsManager.addSettingFloat(&renderer.bloomValue, "SHADER_BLOOM", "/PixelPyros/BloomLevel/x",0, 3);
	
	settingsManager.addSettingBool(&particleSystemManager.killAllParticlesFlag, "", "/PixelPyros/KillParticles/x", false );
	
	settingsManager.addSettingBool(&renderer.resetFlag, "", "/PixelPyros/Setup/ResetDefault/x", true);

	settingsManager.addSettingBool(&sceneManager.nextFlag, "", "/PixelPyros/SceneNext/x", true, true);
	settingsManager.addSettingBool(&sceneManager.previousFlag, "", "/PixelPyros/ScenePrevious/x", true, true);
	settingsManager.addSettingBool(&sceneManager.nextArrangementFlag, "", "/PixelPyros/ArrNext/x", true, true);
	settingsManager.addSettingBool(&sceneManager.previousArrangementFlag, "", "/PixelPyros/ArrPrevious/x", true, true);
	
	
	sceneManager.initSceneControls(settingsManager);
	
	
}

void ofApp::eventsIn(guiCallbackData & data){
    
	
	if( data.getXmlName() == "SHADER_BLACK" ) {
        renderer.blackPoint = data.getFloat(0);
    }
	else if( data.getXmlName() == "SHADER_WHITE" ) {
         renderer.whitePoint = data.getFloat(0);
    }
	else if( data.getXmlName() == "SHADER_GAMMA" ) {
        renderer.gammaValue = data.getFloat(0);
    }
	else if( data.getXmlName() == "SHADER_BLOOM" ) {
        renderer.bloomValue = data.getFloat(0);
    } else if( data.getXmlName() == "TRIGGER_AREA_WIDTH" ) {
        triggerAreaWidth = data.getFloat(0);
    } else if( data.getXmlName() == "TRIGGER_AREA_HEIGHT" ) {
        triggerAreaHeight = data.getFloat(0);
    } else if( data.getXmlName() == "TRIGGER_AREA_Y" ) {
        triggerAreaCentreY = data.getFloat(0);
    } else if( data.getXmlName() == "TRIGGER_SPACING" ) {
        triggerSpacing = data.getFloat(0);
    }
	
	
	//gui.saveSettings();
}




void ofApp::exit() { 


}
