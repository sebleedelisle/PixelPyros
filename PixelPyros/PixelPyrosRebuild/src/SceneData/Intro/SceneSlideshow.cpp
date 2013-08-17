//
//  SceneSlideshow.cpp
//  PixelPyros
//
//  Created by Paul King on 30/08/2012.
//

#include "SceneSlideshow.h"


SceneSlideshow::SceneSlideshow(string scenename, ParticleSystemManager &psm, ofRectangle triggerarea): Scene(scenename, psm, triggerarea) {
    
	
	
	
	TriggerSimple trigger(psm);
	TriggerPattern pattern;
	//pattern.addTrigger(trigger);
	addArrangement(pattern);
	pattern.addTrigger(trigger);
	addArrangement(pattern);
	
	//starfield = Starfield(500);
	//starfield.speed = 50;
  
    currentSlide = 0;
    lastUpdateTime = 0;
    defaultFontSize = 4.0;
	
	ofColor textColor(128,180,150);
    
                                       
    defaultBackground.loadImage(ofToDataPath("slideshow/pixelpyros-slide-background.png"));

//    Do you want your box guides back to layout the text? Uncomment lines 80-82 in TextWriter.cpp and big blue boxes will return
    
    // Slide 1 -- festivaly opening!
    
    SceneSlide *slide = new SceneSlide(&defaultBackground);
   // slide->add(timer);
    
    // Auto-centred box, x, y are offsets from the middle
    slide->add(new CentredSlideText(APP_WIDTH, APP_HEIGHT,
        ofRectangle(0, -70, 700, 60),
//        ofRectangle(0, 0 + 100, 700, 60),
        textColor,
        defaultFontSize,
        "the official launch of the 2012 \nbrighton digital festival!"
    ));
    
    // Absolute x,y coordinates for top left of box
//    slide->add(new SlideText(
//         ofRectangle(100, 300, 100, 50), 
//         ofColor(128, 128, 128), 
//         0.5 * defaultFontSize,
//         "Absolute Text"
//    ));
    
//    // Auto-sized, horribleness
//    slide->add(new SlideAutoText(
//         ofRectangle(APP_WIDTH / 2 - 400, APP_HEIGHT / 2 - 100, 800, 300), 
//         ofColor(128, 128, 128), 
//        "2012.brightondigitalfestival.co.uk"
//    ));
    
    // Auto-centred box, x, y are offsets from the middle
    
    slide->add(new CentredSlideText(APP_WIDTH, APP_HEIGHT,
        ofRectangle(0, 80, 700, 60),
        //ofRectangle(0, 120 + 100, 700, 60),
        textColor,
        0.7 * defaultFontSize,
        "2012.brightondigitalfestival.co.uk"
        ));
 
	
	
    slide->add(new CentredSlideText(APP_WIDTH, APP_HEIGHT,
		ofRectangle(0, 150, 700, 60),
		textColor,
		 defaultFontSize,
		"showtimes :  8:30  9:30  10:15"
		));
    // Duration to show, in seconds
    slide->duration = 10;
    slides.push_back(slide);
    
    // Slide 2  -- people thanks!
    
    slide = new SceneSlide(&defaultBackground);
    //slide->add(timer);
    
    slide->add(new CentredSlideText(APP_WIDTH, APP_HEIGHT,
         ofRectangle(0, -25, 600, 50),
         //ofRectangle(0, 0 + 120, 600, 100),
         ofColor(128, 128, 128),
         defaultFontSize,
         "thanks to:"
    ));
    slide->add(new CentredSlideText(APP_WIDTH, APP_HEIGHT,
         ofRectangle(0, 25, 600, 50),
         //ofRectangle(0, 200, 300, 100),
         ofColor(128, 128, 128),
         0.6 * defaultFontSize,
         "Jubilee Library, Chilli Pickle, Pizza Express, The Basement,\n, Jonathan Orrell at HOP, Honor Harger,\nLaurence Hill, Jamie Wyld, Jon Pratty,\nPhil Jones, Devi Lozdan, Julie Sharp, Kyle McDonald, \nVal Head, Paul King, John Davey"
    ));
    
    // Duration to show, in seconds
    slide->duration = 10;
    //slides.push_back(slide);
    

    // Slide 3 -- biz thanks!
    
    slide = new SceneSlide(&defaultBackground);
    //slide->add(timer);
    slide->add(new CentredSlideText(APP_WIDTH, APP_HEIGHT,
    	ofRectangle(0, -25, 600, 50),
    	ofColor(128, 128, 128),
    	defaultFontSize,
		"Production :"
));
    slide->add(new CentredSlideText(APP_WIDTH, APP_HEIGHT,
		ofRectangle(0, 25, 600, 50),
        ofColor(128, 128, 128),
      	0.6 * defaultFontSize,
      	"Becky Stevens, Mark Scarratt, Firefly Solar, Facelift, Jack Lang  "
));
    
    // Duration to show, in seconds
    slide->duration = 10;
   // slides.push_back(slide);
    
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
    
    slide->background->draw(0, 0);
    
    ofPopStyle();
    ofPopMatrix();
    
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
	
	
}

bool SceneSlideshow::changeArrangement(int i) {
	Scene::changeArrangement(i);
    currentSlide = 0;
    return true;
}

