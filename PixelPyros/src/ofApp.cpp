

#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	ofSetLogLevel(OF_LOG_WARNING);
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
	
	// TODO FBO oversamples now so check performance / smoothing
	fbo.allocate(APP_WIDTH, APP_HEIGHT, GL_RGBA, 4);
	
	fbo.begin();
	ofClear(0,0,0);
	fbo.end(); 

	oscManager.setup () ;
	
    paused = false;
    altPressed = false;
	shiftPressed = false;

    triggerManager.setDisplaySize(APP_WIDTH, APP_HEIGHT);
	//triggerManager.updateTriggerSettings(triggerArea, triggerSpacing);
	/*
	Trigger trigger;
	TriggerPattern pattern;
	pattern.addTrigger(trigger);
	triggerManager.setPattern(pattern);
	*/
	
	laserManager.setup();
	//laserManager.renderLaserPath = true;
	
    parameterManager.registerParameterGroup("laser", &laserManager.parameters );
    parameterManager.registerParameterGroup("renderer", &renderer.paramters );
    parameterManager.registerParameterGroup("triggers", &triggerManager.parameters);
    parameterManager.registerParameterGroup("motion", &motionManager.parameters);
    parameterManager.registerParameterGroup("particles", &particleSystemManager.parameters);

    /*
        Now that all of the parameters should be registered with the 
        ParameterManager, setup the control gui
     */
    controlPanels.setup( &parameterManager );

}

//--------------------------------------------------------------
void ofApp::update(){

	
	
	oscManager.update () ;
	
	settingsManager.update(); 
	
	if(cameraManager.update()){
		
		ofImage image(cameraManager.getPixelsRef()); 

		motionManager.update(cameraManager.getPixelsRef());
		
		triggerManager.updateMotion(motionManager, cameraManager.warper.inverseHomography );
		
	}
	
	
	
	float time = ofGetElapsedTimef(); 
	float deltaTime =  time - lastUpdateTime;

	lastUpdateTime = time;
	
	/*
	if ( triggerShowDebug != triggerManager.triggerShowDebug ) {
		triggerManager.setShowTriggerDebug(triggerShowDebug) ;
		
	}*/
	
	if ( triggersDisabled != triggerManager.triggersDisabled ) {
		triggerManager.setTriggersDisabled(triggersDisabled) ;
		
	}
	
    if( !paused ) {
		
		triggerManager.update(deltaTime);
	    sceneManager.update(deltaTime);
        particleSystemManager.update(deltaTime);
		sequencer.update(); 
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
		ofClear(0);
	}
	
	if(drawCameraIntoFBO)
		cameraManager.draw(0,0);


	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	particleSystemManager.draw();
	laserManager.update();
	
	triggerManager.draw();
	    
	sceneManager.draw(); 
		
	if(useFbo) {
		fbo.end();
        
		ofEnableBlendMode(OF_BLENDMODE_ADD);
			
		renderer.draw(fbo, fboWarper1, fboWarper2);
	}
	
	ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
//	ofDrawBitmapString(ofToString(particleSystemManager.particleSystems.size()),20,35);
//	ofDrawBitmapString(ofToString(particleSystemManager.activeParticleCount),20,50);
//	ofDrawBitmapString(ofToString(particleSystemManager.activePhysicsObjectCount),20,65);

	ofDisableBlendMode();
	ofDisableAlphaBlending();
	
	// draw the warper UIs if necessary
	fboWarper1.draw();
	fboWarper2.draw();
	
	sequencer.draw();
	
    controlPanels.draw();
    
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
            sequencer.runSequence("Intro");
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
	
	sceneManager.addScene(new SceneCalibration("Calibration"));
	sceneManager.addScene(new SceneSlideshow("SlideShow"));
	
	// This scene was to launch the Brighton Digital Festival
	//sceneManager.addScene(new SceneLaunch("Launch", particleSystemManager));

	sceneManager.addScene(new SceneIntro("Intro"));
	Sequence* seq = sequencer.loadSequence("Intro", "Intro", "02 In Motion.aif");
	seq->addCommand(0, SEQ_PATTERN_CHANGE, 0);
	seq->addCommand(2, SEQ_PATTERN_CHANGE, 1);
	seq->addCommand(9, SEQ_PATTERN_CHANGE, 2);
	seq->addCommand(10, SEQ_PATTERN_CHANGE, 3);
	seq->addCommand(11, SEQ_PATTERN_CHANGE, 1);
	seq->addCommand(12, SEQ_PATTERN_CHANGE, 2);
	seq->addCommand(13, SEQ_PATTERN_CHANGE, 3);
	
	
	
	
	sceneManager.addScene(new SceneRetro("Retro"));
	
	//sceneManager.addScene(new SceneRealistic("Lights", particleSystemManager));
	sceneManager.addScene(new SceneVectorizer("Vectorizer"));
	sceneManager.addScene(new SceneNadia("Nadia"));
	
	//sceneManager.addScene(new SceneSpace("Stargazer", particleSystemManager));
	
	sceneManager.changeScene(0);
	
	
	
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
	
	// TO DO
	// this stuff is so we can manually trigger fireworks with the mouse.
//	
//	vector <Scene*>& scenes = sceneManager.scenes;
//	for(int j = 0 ; j<scenes.size(); j++ ) { 
//		Scene* scene1 = scenes[j];
//		vector<Arrangement*> * triggerPatterns = &scene1->triggerPatterns;
//		for(int k = 0; k<triggerPatterns->size(); k++)
//		{
//			vector <TriggerBase*> triggers = triggerPatterns->at(k)->triggers;
//			for(int i = 0; i<triggers.size(); i++) { 
//				TriggerBase * trigger = triggers[i]; 
//				float distance = trigger->pos.distance(ofVec3f(x,y));
//				if(distance<20) {
//					trigger->registerMotion(1.0f-(distance/20.0f)); 
//					
//				}
//				
//			}
//		}
//	}
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

//	gui.setWhichColumn(1);
    
//	gui.addPanel("Motion");
//	
//	motionManager.initControlPanel(gui);
//	
//	gui.addPanel("Triggers");
//	gui.addSlider("Area width", "TRIGGER_AREA_WIDTH", 0, 0, 1.0, false);//->setDimensions(400, 10);
//	gui.addSlider("Area height", "TRIGGER_AREA_HEIGHT", 0, 0, 0.5, false);//->setDimensions(400, 10);
//	gui.addSlider("Area y pos", "TRIGGER_AREA_Y", 0, 0.5, 1, false);//->setDimensions(400, 10);
//	gui.addSlider("Spacing", "TRIGGER_SPACING", 0, 0, 400, false);//->setDimensions(400, 10);
//	

	//ofAddListener(gui.guiEvent, this, &ofApp::eventsIn);
	
	
	//gui.setupEvents();
	//gui.enableEvents();
	//gui.loadSettings("controlPanelSettings.xml");

	
	
	settingsManager.setup(&oscManager, &gui) ;
	
	
//	settingsManager.addSettingFloat(&motionManager.thresholdLevel, "THRESHOLD", "/PixelPyros/Setup/Threshold/x", 0, 255);
//	settingsManager.addSettingFloat(&motionManager.motionSensitivity, "MOTION_SENSITIVITY", "/PixelPyros/Setup/Sensitivity/x", 1, 5);
//	
//	settingsManager.addSettingFloat(&triggerAreaWidth, "TRIGGER_AREA_WIDTH", "/PixelPyros/Setup/Width/x", 0, 1);
//	settingsManager.addSettingFloat(&triggerAreaHeight, "TRIGGER_AREA_HEIGHT", "/PixelPyros/Setup/Height/x",0, 0.5);
//	settingsManager.addSettingFloat(&triggerAreaCentreY, "TRIGGER_AREA_Y", "/PixelPyros/Setup/VPOS/x",0.5, 1);
//	settingsManager.addSettingFloat(&triggerSpacing, "TRIGGER_SPACING", "/PixelPyros/Setup/Spacing/x",0, 400);
//	settingsManager.addSettingFloat(&triggerSpacing, "TRIGGER_SPACING", "/PixelPyros/Spacing/x",0, 400);
//	
	settingsManager.addSettingBool(&showDiffImage, "", "/PixelPyros/Setup/ShowDiff/x", true);
	
	settingsManager.addSettingBool(&triggersDisabled, "", "/PixelPyros/Setup/MotionDisable/x", true);
	settingsManager.addSettingBool(&triggerShowDebug, "", "/PixelPyros/Setup/TriggerDebug/x", true);
	settingsManager.addSettingBool(&triggersDisabled, "", "/PixelPyros/MotionDisable/x", true);
	settingsManager.addSettingBool(&triggerShowDebug, "", "/PixelPyros/TriggerDebug/x", true);
	
//	settingsManager.addSettingFloat(&renderer.blackPoint, "SHADER_BLACK", "/PixelPyros/Setup/BlackLevel/x",0, 1);
//	settingsManager.addSettingFloat(&renderer.whitePoint, "SHADER_WHITE", "/PixelPyros/Setup/WhiteLevel/x",0, 1);
//	settingsManager.addSettingFloat(&renderer.gammaValue, "SHADER_GAMMA", "/PixelPyros/Setup/GammaLevel/x",0, 10);
//	settingsManager.addSettingFloat(&renderer.bloomValue, "SHADER_BLOOM", "/PixelPyros/Setup/BloomLevel/x",0, 3);
//	settingsManager.addSettingFloat(&renderer.bloomValue, "SHADER_BLOOM", "/PixelPyros/BloomLevel/x",0, 3);
	
//	settingsManager.addSettingBool(&particleSystemManager.killAllParticlesFlag, "", "/PixelPyros/KillParticles/x", false );
	
	settingsManager.addSettingBool(&renderer.resetFlag, "", "/PixelPyros/Setup/ResetDefault/x", true);

	settingsManager.addSettingBool(&sceneManager.nextFlag, "", "/PixelPyros/SceneNext/x", true, false);
	settingsManager.addSettingBool(&sceneManager.previousFlag, "", "/PixelPyros/ScenePrevious/x", true, true);
	settingsManager.addSettingBool(&sceneManager.nextPatternFlag, "", "/PixelPyros/ArrNext/x", true, true);
	settingsManager.addSettingBool(&sceneManager.previousPatternFlag, "", "/PixelPyros/ArrPrevious/x", true, true);
	
	sceneManager.initSceneControls(settingsManager);
	
	
}

//void ofApp::eventsIn(guiCallbackData & data){

	
//	if( data.getXmlName() == "SHADER_BLACK" ) {
//        renderer.blackPoint = data.getFloat(0);
//    }
//	else if( data.getXmlName() == "SHADER_WHITE" ) {
//         renderer.whitePoint = data.getFloat(0);
//    }
//	else if( data.getXmlName() == "SHADER_GAMMA" ) {
//        renderer.gammaValue = data.getFloat(0);
//    }
//	else if( data.getXmlName() == "SHADER_BLOOM" ) {
//        renderer.bloomValue = data.getFloat(0);
//    } else if( data.getXmlName() == "TRIGGER_AREA_WIDTH" ) {
//        triggerAreaWidth = data.getFloat(0);
//    } else if( data.getXmlName() == "TRIGGER_AREA_HEIGHT" ) {
//        triggerAreaHeight = data.getFloat(0);
//    } else if( data.getXmlName() == "TRIGGER_AREA_Y" ) {
//        triggerAreaCentreY = data.getFloat(0);
//    } else if( data.getXmlName() == "TRIGGER_SPACING" ) {
//        triggerSpacing = data.getFloat(0);
//    }
		
	//gui.saveSettings();
//}




void ofApp::exit() { 
    controlPanels.exit();
}
