//
//  SceneSlideshow.h
//  PixelPyros
//
//  Created by Paul King on 30/08/2012.
//

#pragma once

#include "Scene.h"
#include "SlideShow.h"
#include "TextWriter.h"
//nclude "Starfield.h"

#define DEFAULT_SLIDE_DURATION 5.0
#define NON_CURRENT_SLOTS_TO_SHOW 2

class SlideObject {
    
public:
    SlideObject(ofRectangle rect, ofColor c) {
        box = rect;
        col = c;
    }
    
    virtual void draw() {
        ofPushMatrix();
        ofPushStyle();
        
        ofSetColor(col);
        ofFill();
        ofRect(box);
        
        ofPopStyle();
        ofPopMatrix();
    }
    
    ofRectangle box;
    ofColor col;
};

class SlideText: public SlideObject {
    
public: 
    SlideText(ofRectangle rect, ofColor c, float fontSize, string s): SlideObject(rect, c) {
        text = s;
        this->fontSize = fontSize;
    }
    
    virtual void draw() {
        ofPushStyle();
        
        ofSetColor(col);
        writer.drawFixedSize(box, text, fontSize, false);
        
        ofPopStyle();
    }
    
    string text;
    float fontSize;
    TextWriter writer;
};



class CentredSlideText: public SlideText {
    
public:
    CentredSlideText(int screenWidth, int screenHeight, ofRectangle rect, ofColor c, float fontSize, string s): SlideText(rect, c, fontSize, s) {
        box.x += (screenWidth / 2.0) - (box.width / 2.0);
        box.y += (screenHeight / 2.0) - (box.height / 2.0);
    }
    
    virtual void draw() {
        ofPushStyle();
        
        //ofSetColor(col);
		writer.colour = col;
        writer.drawFixedSize(box, text, fontSize, true);
        
        ofPopStyle();
    }
};



class SlideTimer: public CentredSlideText {
    
public:
    
    SlideTimer(int screenWidth, int screenHeight, ofRectangle rect, ofColor c, float fontSize, vector<string> times): CentredSlideText(screenWidth, screenHeight, rect, c, fontSize, "") {
        showTimes = times;
        
        for( int i = 0; i < showTimes.size(); i++ ) {
            showTimeStamps.push_back(hoursMinutesToEpoch(showTimes[i]));
        }
    }
    
    time_t toTimeStamp(string timeString = "") {
        struct tm tm;
        
        if( timeString == "" ) {
            timeString = ofGetTimestampString("%Y-%m-%d %H:%M:%S");
        }
        
        if( strptime(timeString.c_str(), "%Y-%m-%d %H:%M:%S", &tm) != NULL ) {
            time_t epoch = mktime(&tm);
            return epoch;
        }
        
        return 0;
    }
    
    time_t hoursMinutesToEpoch(string t) {
        string timeString = ofGetTimestampString("%Y-%m-%d ") + t + ":00";
        return toTimeStamp(timeString);
    }
    
    time_t getTime() {
        return toTimeStamp();
    }
    
    int getNextShowTimeIndex(unsigned long now) {
        for( int i = 0; i < showTimeStamps.size(); i++ ) {
            if( now < showTimeStamps[i] ) {
                return i;
            }
        }
        return -1;
    }
    
    unsigned long getNextShowTime(unsigned long now) {
        int idx = getNextShowTimeIndex(now);
        
        if( idx < 0 ) {
            return now;
        }
        
        return showTimeStamps[idx];
    }
    
    string getTimeToNextShowString(unsigned long now) {
        unsigned long nextShow = getNextShowTime(now);
        string lhs, rhs;
        
        unsigned long diff = nextShow - now;
        
        // If for some reason the next show is over an hour away, show the difference in HH:MM
        if( diff > 3600 ) {
            unsigned long hours = diff / 3600;
            lhs = ofToString(hours);
            rhs = ofToString((diff - (hours * 3600)) / 60);
        } else {
            lhs = ofToString(diff / 60);
            rhs = ofToString(diff % 60);
        }
        
        if( lhs.length() < 2 ) {
            lhs = "0" + lhs;
        }
        
        if( rhs.length() < 2 ) {
            rhs = "0" + rhs;
        }
        
        return lhs + ":" + rhs;
    }

    virtual void draw() {
        unsigned long now = getTime();
        int i = getNextShowTimeIndex(now);
        
        // Nothing left to do, this is just to ensure the last historical entry gets displayed when we're past the last show time
        if( i < 0 ) {
            i = showTimeStamps.size();
        }
        
        ofPushStyle();
        ofNoFill();
        
        // Display the next n shows that are upcoming
        ofSetColor(128, 128, 128);
        for( int j = i, ctr = 1; ctr <= NON_CURRENT_SLOTS_TO_SHOW; j++, ctr++ ) {
            if( j < showTimes.size() ) {
                writer.drawFixedSize(ofRectangle(box.x - (250 * ctr), box.y, box.width, box.height), "\n" + showTimes[j], fontSize, true);
            }
        }
        
        // Display the next showing time
        string nextShowTime = getTimeToNextShowString(now);
        if( nextShowTime != "00:00" ) {
            ofSetColor(200, 200, 200);
            ofRect(ofRectangle(box.x, box.y - 20, box.width, box.height));
            writer.drawFixedSize(box, "Next Show\n" + nextShowTime, fontSize, true);
        }
        
        // Display the last n shows that have passed
        ofSetColor(75, 75, 75);
        for( int j = i - 1, ctr = 1; ctr <= NON_CURRENT_SLOTS_TO_SHOW; j--, ctr++ ) {
            if( j >= 0 ) {
                writer.drawFixedSize(ofRectangle(box.x + (250 * ctr), box.y, box.width, box.height), "\n" + showTimes[j], fontSize, true);
            }
        }
        
        ofPopStyle();
    }
    
    vector<string> showTimes;
    vector<time_t> showTimeStamps;
    TextWriter writer;
};

class SlideAutoText: public SlideText {
    
public:
    SlideAutoText(ofRectangle rect, ofColor c, string s): SlideText(rect, c, 1.0, s) {
    }
    
    virtual void draw() {
        ofPushStyle();
        
        ofSetColor(col);
        writer.draw(box, text, true);
        
        ofPopStyle();
    }
};

class SceneSlide {
    
public:
    
    SceneSlide(ofImage *backgroundImage) {
        background = backgroundImage;
        duration = DEFAULT_SLIDE_DURATION;
    }
    
    void add(SlideObject *object) {
        objects.push_back(object);
    }
    
    vector<SlideObject *> objects;
    ofImage *background;
    float duration;
};


class SceneSlideshow : public Scene {

public:
    
    SceneSlideshow(string scenename);
    
    virtual bool draw();
	virtual bool update(float deltaTime);

	virtual bool changeTriggerPattern(int);
	//Starfield starfield;
   
            
    SlideShow slideShow;
    
    ofImage defaultBackground;
    vector<SceneSlide *> slides;
    float defaultFontSize;
    
    int currentSlide;
    float lastUpdateTime;
    
};
