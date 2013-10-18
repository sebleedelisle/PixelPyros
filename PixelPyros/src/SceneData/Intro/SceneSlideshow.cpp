//
//  SceneSlideshow.cpp
//  PixelPyros
//
//  Created by Paul King on 30/08/2012.
//

#include "SceneSlideshow.h"


SceneSlideshow::SceneSlideshow(string scenename ): Scene(scenename) {
    
	TriggerSettings* trigger = new TriggerSettings ;
	TriggerPattern pattern;
	//pattern.addTrigger(trigger);
	addTriggerPattern(pattern);
	pattern.addTriggerSettings(trigger);
	addTriggerPattern(pattern);
	
	//starfield = Starfield(500);
	//starfield.speed = 50;
  
    currentSlide = 0;
    lastUpdateTime = 0;
    defaultFontSize = 4.0;
	
	ofColor textColor(100,180,170);
    foreground = 200;
	background = 20;
                                       
    defaultBackground.loadImage(ofToDataPath("slideshow/Interstitial-Nottingham.png"));

	
	
	
//    Do you want your box guides back to layout the text? Uncomment lines 80-82 in TextWriter.cpp and big blue boxes will return
    
    // Slide 1 -- festivaly opening! ----------------------------------------
    
    SceneSlide *slide = new SceneSlide(&defaultBackground);
   // slide->add(timer);
    
    // Auto-centred box, x, y are offsets from the middle
    slide->add(new CentredSlideText(APP_WIDTH, APP_HEIGHT,
        ofRectangle(0, -70, 700, 60),
//        ofRectangle(0, 0 + 100, 700, 60),
        textColor,
        defaultFontSize,
        ""
    ));
    
    
    // Auto-centred box, x, y are offsets from the middle
    
    slide->add(new CentredSlideText(APP_WIDTH, APP_HEIGHT,
        ofRectangle(0, 80, 700, 60),
        //ofRectangle(0, 120 + 100, 700, 60),
        textColor,
        0.7 * defaultFontSize,
        "" //§"pixelpyros.org"
        ));
 
	
	
    slide->add(new CentredSlideText(APP_WIDTH, APP_HEIGHT,
		ofRectangle(0, 150, 700, 60),
		textColor,
		 defaultFontSize,
		"" //"showtimes :  7pm  8pm  9pm"
		));
    // Duration to show, in seconds
    slide->duration = 10;
    slides.push_back(slide);
    
    // Slide 2  -- people thanks! -----------------------------------------------------
    
    slide = new SceneSlide(&defaultBackground);
    //slide->add(timer);
    
    slide->add(new CentredSlideText(APP_WIDTH, APP_HEIGHT,
         ofRectangle(0, -25, 700, 50),
         //ofRectangle(0, 0 + 120, 600, 100),
         textColor,
         0.6 * defaultFontSize,
         "" //"thanks to our local sponsors"
    ));
    slide->add(new CentredSlideText(APP_WIDTH, APP_HEIGHT,
		ofRectangle(0, 25, 700, 50),
		//ofRectangle(0, 200, 300, 100),
		textColor,
		defaultFontSize,
		"" //"Heart Internet"
    ));
    
    // Duration to show, in seconds
    slide->duration = 10;
    slides.push_back(slide);
    

    // Slide 3 -- biz thanks!
    
    slide = new SceneSlide(&defaultBackground);
    //slide->add(timer);
    slide->add(new CentredSlideText(APP_WIDTH, APP_HEIGHT,
    	ofRectangle(0, -25, 700, 50),
    	textColor,
    	0.6 * defaultFontSize,
		"" //"thanks to our production partners"
));
    slide->add(new CentredSlideText(APP_WIDTH, APP_HEIGHT,
		ofRectangle(0, 25, 700, 50),
        textColor,
      	defaultFontSize,
      	"" //"LM Productions\nHOP Engineers"
));
    
    // Duration to show, in seconds
    slide->duration = 10;
    slides.push_back(slide);
    
}


bool SceneSlideshow::update(float deltaTime) {
	if(Scene::update(deltaTime)) {
		//starfield.update(deltaTime);
		return true;
	} else {
		return false;
	}
}

bool SceneSlideshow::draw() {
    if( !Scene::draw() ) {
        return false;
    }
    
    if( (slides.size() == 0) || (currentSlide >= slides.size()) ) {
        return false;
    }
    
	//starfield.draw();
	
    SceneSlide *slide = slides[currentSlide];
    
    ofPushMatrix();
    ofPushStyle();
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofTranslate(APP_WIDTH / 2, APP_HEIGHT / 2);
    
    float xScale = APP_WIDTH / slide->background->getWidth();
    float yScale = APP_HEIGHT / slide->background->getHeight();
    float scale = min(xScale, yScale);
    
    if( scale < 1.0 ) {
        ofScale(xScale, yScale);
    }
    ofSetColor(background);
	ofFill(); 
	ofRect(0,0,APP_WIDTH, APP_HEIGHT);
	ofSetColor(foreground);
    slide->background->draw(0, 0);
    
    ofPopStyle();
    ofPopMatrix();
    /*
    for( int i = 0; i < slide->objects.size(); i++ ) {
        slide->objects[i]->draw();
    }
    
    float deltaTime = ofGetElapsedTimef() - lastUpdateTime;
    if( deltaTime > slide->duration ) {
        currentSlide++;
        
        if( currentSlide >= slides.size() ) {
            currentSlide = 0;
        }
    
        lastUpdateTime += deltaTime;
    }
	
	*/
}

bool SceneSlideshow::changeTriggerPattern(int i) {
	Scene::changeTriggerPattern(i);
    currentSlide = 0;
    return true;
}

