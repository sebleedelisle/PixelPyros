
#import "AppDelegate.h"

@implementation AppDelegate


- (void) applicationDidFinishLaunching: (NSNotification*) notification {
	
    //force construction of singleton prior to creation of ofApp
	ofxNSWindower::instance();
    
    ofApp* app = new ofApp();
	ofxNSWindower::instance()->addWindow(app,"Pixel Pyros Main", NSTitledWindowMask, 0);
    
    ofxNSWindower::instance()->addWindow(new controlWindow(app),"Pixel Pyros Control Panel", NSTitledWindowMask, 15 );
	
	//detailed way...
	//ofxNSWindower::instance()->addWindow(new testApp(), "a_window", NSTitledWindowMask, 30);
	//addWindow(application_object, name, window_options, framerate)

	//see https://developer.apple.com/library/mac/#documentation/Cocoa/Reference/ApplicationKit/Classes/NSWindow_Class/Reference/Reference.html
	//for window_options
	
	//if framerate is 0 then the framerate is synced with the refresh rate of the monitor
}

- (void) applicationWillTerminate: (NSNotification*) notification {

	ofxNSWindower::destroy();
}


@end
