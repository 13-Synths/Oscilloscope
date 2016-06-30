#include "OsciView.h"
#include <Poco/Delegate.h>
#include "sounddevices.h"
#include "ofxFontAwesome.h"
#include "ofApp.h"
#include "L.h"


OsciView::OsciView( float x_, float y_, float width_, float height_)
: mui::Container( x_, y_, width_, height_ ){
	float x = 10, y = 10, w = 400, h = 30;
	bg = ofColor(125,50);
	opaque = true;
	micMenu = NULL;

	string xx = ofxFontAwesome::play; 
	
		stopButton = new FaButton( ofxFontAwesome::cogs, x, y, h, h );
	ofAddListener( stopButton->onPress, this, &OsciView::buttonPressed );
	y += stopButton->height + 10;
	add( stopButton );
	
	scaleLabel = addLabel( "Scale" );
	scaleSlider1 = new mui::SliderWithLabel( x, y, w, h, 0.1, 2, 1, 2 );
	scaleSlider1->label->fg = ofColor(255);
	ofAddListener( scaleSlider1->slider->onChange, this, &OsciView::sliderChanged );
	y += scaleSlider1->height + 10;
	add( scaleSlider1 );
	
	scaleSlider2 = new mui::SliderWithLabel( x, y, w, h, 0.1, 2, 1, 2 );
	scaleSlider2->label->fg = ofColor(255);
	ofAddListener( scaleSlider2->slider->onChange, this, &OsciView::sliderChanged );
	y += scaleSlider2->height + 10;
	add( scaleSlider2 );
	
	spreadLabel = addLabel( "Spread" );
	spreadSlider = new mui::SliderWithLabel( x, y, w, h, 0, 1, 0, 2 );
	spreadSlider->label->fg = ofColor(255);
	ofAddListener( spreadSlider->slider->onChange, this, &OsciView::sliderChanged );
	y += spreadSlider->height + 10;
	add( spreadSlider );
	
	
	w = 90;
	flipXY = new FaToggleButton( ofxFontAwesome::repeat, ofxFontAwesome::repeat, x, y, h, h );
	ofAddListener( flipXY->onPress, this, &OsciView::buttonPressed );
	add( flipXY );
	x += 100;
	
	invertX = new FaToggleButton( ofxFontAwesome::arrows_h, ofxFontAwesome::arrows_h, x, y, h, h );
	ofAddListener( invertX->onPress, this, &OsciView::buttonPressed );
	add( invertX );
	x += 100;
	
	invertY = new FaToggleButton( ofxFontAwesome::arrows_v, ofxFontAwesome::arrows_v, x, y, h, h );
	ofAddListener( invertY->onPress, this, &OsciView::buttonPressed );
	add( invertY );
	x += 100;
	
	fullscreenButton = new FaToggleButton( ofxFontAwesome::expand, ofxFontAwesome::compress, x, y, h, h );
	ofAddListener( fullscreenButton->onPress, this, &OsciView::buttonPressed );
	add( fullscreenButton );
	
	loadFileButton = new FaButton( ofxFontAwesome::folder_open, x, y, h, h );
	ofAddListener( loadFileButton->onPress, this, &OsciView::buttonPressed );
	add( loadFileButton );
	
	useMicButton = new FaToggleButton( ofxFontAwesome::microphone, ofxFontAwesome::microphone_slash, x, y, h, h );
	ofAddListener( useMicButton->onPress, this, &OsciView::buttonPressed );
	add( useMicButton );
	
	playButton = new FaToggleButton( ofxFontAwesome::play, ofxFontAwesome::pause, x, y, h, h );
	ofAddListener( playButton->onPress, this, &OsciView::buttonPressed );
	add( playButton );
	
	x = 10;
	y += invertY->height + 10;
	
	timeSlider = new mui::Slider( 0, 0, w, h );
	add( timeSlider );
	
	
	outputVolumeLabel = addLabel( "Volume" );
	outputVolumeSlider = new mui::SliderWithLabel(0, 0, 100, h, 0, 1, 0.8, 2 );
	ofAddListener( outputVolumeSlider->slider->onChange, this, &OsciView::sliderChanged );
	outputVolumeSlider->label->fg = ofColor(255);
	add(outputVolumeSlider);
	
	strokeWeightLabel = addLabel( "Stroke Weight" );
	strokeWeightSlider = new mui::SliderWithLabel(0, 0, 100, h, 1, 50, 4, 1 );
	ofAddListener( strokeWeightSlider->slider->onChange, this, &OsciView::sliderChanged );
	strokeWeightSlider->label->fg = ofColor(255);
	add( strokeWeightSlider );
	
	blurLabel = addLabel( "Blur" );
	blurSlider = new mui::SliderWithLabel(0,0, 100, h, 0, 255, 30, 0);
	ofAddListener( blurSlider->slider->onChange, this, &OsciView::sliderChanged );
	blurSlider->label->fg = ofColor(255);
	add(blurSlider);
	
	numPtsLabel = addLabel( "Points" );
	numPtsSlider = new mui::SliderWithLabel(0,0,100,h, 1, 100, 20, 0);
	ofAddListener( numPtsSlider->slider->onChange, this, &OsciView::sliderChanged );
	numPtsSlider->label->fg = ofColor(255);
	add(numPtsSlider);

	hueLabel = addLabel( "Hue" );
	hueSlider1 = new mui::SliderWithLabel(0,0,100,h,0,360, 127, 0);
	ofAddListener( hueSlider1->slider->onChange, this, &OsciView::sliderChanged );
	hueSlider1->label->fg = ofColor(255);
	add(hueSlider1);
	
	hueSlider2 = new mui::SliderWithLabel(0,0,100,h,0,360, 127, 0);
	ofAddListener( hueSlider2->slider->onChange, this, &OsciView::sliderChanged );
	hueSlider2->label->fg = ofColor(255);
	add(hueSlider2);
	
	intensityLabel = addLabel( "Intensity" );
	intensitySlider = new mui::SliderWithLabel(0,0,100,h,0,1, 0.5, 2);
	ofAddListener( intensitySlider->slider->onChange, this, &OsciView::sliderChanged );
	intensitySlider->label->fg = ofColor(255);
	add(intensitySlider);
	
	afterglowLabel = addLabel( "Afterglow" );
	afterglowSlider = new mui::SliderWithLabel(0,0,100,h,0,1, 0.3, 2);
	ofAddListener( afterglowSlider->slider->onChange, this, &OsciView::sliderChanged );
	afterglowSlider->label->fg = ofColor(255);
	add(afterglowSlider);
	
	
	

	
	layout();
}

void OsciView::layout(){
	mui::L(fullscreenButton).pos(width-30, 0);
	mui::L(stopButton).leftOf(fullscreenButton,1);
	
	mui::L(playButton).pos(10,40);
	mui::L(timeSlider).rightOf(playButton, 10).stretchToRightEdgeOf(this, 10);
	
	mui::L(loadFileButton).below(playButton, 10);
	mui::L(useMicButton).rightOf(loadFileButton, 10 );
	mui::L(outputVolumeLabel).rightOf(useMicButton,20);
	mui::L(outputVolumeSlider).rightOf(outputVolumeLabel,5).stretchToRightEdgeOf(this,10);
	
	mui::L(invertX).below(loadFileButton, 20);
	mui::L(invertY).rightOf(invertX, 10);
	mui::L(flipXY).rightOf(invertY,10);
	mui::L(scaleLabel).rightOf(flipXY,20);
	mui::L(scaleSlider1).rightOf(scaleLabel,5).stretchToRightEdgeOf(this,10);
	mui::L(scaleSlider2).below(scaleSlider1).stretchToRightEdgeOf(this,10);
	mui::L(strokeWeightLabel).below(scaleSlider2).alignRightEdgeTo(scaleLabel);
	mui::L(strokeWeightSlider).rightOf(strokeWeightLabel,5).stretchToRightEdgeOf(this,10);
	
	/*mui::L(blurLabel).below(strokeWeightLabel).alignRightEdgeTo(strokeWeightLabel);
	mui::L(blurSlider).rightOf(blurLabel,5).stretchToRightEdgeOf(this,10);
	
	mui::L(numPtsLabel).below(blurLabel).alignRightEdgeTo(blurLabel);
	mui::L(numPtsSlider).rightOf(numPtsLabel,5).stretchToRightEdgeOf(this,10);*/
	blurLabel->visible = false;
	blurSlider->visible = false;
	numPtsLabel->visible = false;
	numPtsSlider->visible = false;
	
	mui::L(hueLabel).below(strokeWeightLabel).alignRightEdgeTo(strokeWeightLabel);
	mui::L(hueSlider1).rightOf(hueLabel,5).stretchToRightEdgeOf(this,10);
	mui::L(hueSlider2).below(hueSlider1).stretchToRightEdgeOf(this,10);
	
	mui::L(spreadLabel).below(hueSlider2).alignRightEdgeTo(hueLabel);
	mui::L(spreadSlider).rightOf(spreadLabel,5).stretchToRightEdgeOf(this,10);
	
	
	
	mui::L(intensityLabel).below(spreadLabel).alignRightEdgeTo(spreadLabel);
	mui::L(intensitySlider).rightOf(intensityLabel,5).stretchToRightEdgeOf(this,10);
	
	mui::L(afterglowLabel).below(intensityLabel).alignRightEdgeTo(intensityLabel);
	mui::L(afterglowSlider).rightOf(afterglowLabel,5).stretchToRightEdgeOf(this,10);
	
	
	height = afterglowSlider->y + afterglowSlider->height;
}


// tiny helper functions.
// these should somehow be in mui, they're so handy
// returns false if the user changed the value
bool updateSlider( mui::Slider * slider, float targetValue, float &lastValue ){
	if( slider->hasFocus() ){
		if( lastValue != slider->value ){
			lastValue = slider->value;
			return false;
		}
		else{
			return true;
		}
	}
	else{
		slider->value = targetValue;
		return true;
	}
	
}

//--------------------------------------------------------------
void OsciView::update(){
	static float lastTimeVal = -1;
	useMicButton->selected = globals.micActive;
	timeSlider->visible = !globals.micActive;
	outputVolumeSlider->visible = !globals.micActive;
	
	if( !globals.micActive ){
		if( !updateSlider(timeSlider, globals.player.getPosition(), lastTimeVal ) ){
			globals.player.setPosition(timeSlider->value);
		}

		if( globals.player.isPlaying != playButton->selected ){
			playButton->selected = globals.player.isPlaying;
			playButton->commit();
		}
	}

	if (scaleSlider1->singleTouchId < 0) globals.scale1 = scaleSlider1->slider->value;
	if (scaleSlider2->singleTouchId < 0) globals.scale2 = scaleSlider2->slider->value;
	if (hueSlider1->singleTouchId < 0) globals.hue1 = hueSlider1->slider->value;
	if (hueSlider2->singleTouchId < 0) globals.hue2 = hueSlider2->slider->value;
	if (spreadSlider->singleTouchId < 0) globals.spread = spreadSlider->slider->value;
	if (afterglowSlider->singleTouchId < 0) globals.afterglow = afterglowSlider->slider->value; 
}


//--------------------------------------------------------------
void OsciView::draw(){
	ofSetColor(150);
	ofLine( 10, flipXY->y - 10, width-10, flipXY->y - 10 );
	ofSetColor(255);
}



//--------------------------------------------------------------
void OsciView::touchDown( ofTouchEventArgs &touch ){
}


//--------------------------------------------------------------
void OsciView::touchMoved( ofTouchEventArgs &touch ){
}


//--------------------------------------------------------------
void OsciView::touchUp( ofTouchEventArgs &touch ){
}


//--------------------------------------------------------------
void OsciView::touchDoubleTap( ofTouchEventArgs &touch ){
}


void OsciView::fromGlobals(){
	outputVolumeSlider->slider->value = globals.outputVolume;
	
	if( globals.player.isPlaying != playButton->selected ){
		playButton->selected = globals.player.isPlaying;
		playButton->commit();
	}
	
	scaleSlider1->slider->value = globals.scale1;
	scaleSlider2->slider->value = globals.scale2;
	strokeWeightSlider->slider->value = globals.strokeWeight;
	blurSlider->slider->value = globals.blur;
	numPtsSlider->slider->value = globals.numPts;
	hueSlider1->slider->value = globals.hue1;
	hueSlider2->slider->value = globals.hue2;
	spreadSlider->slider->value = globals.spread;
	intensitySlider->slider->value = globals.intensity;
	afterglowSlider->slider->value = globals.afterglow;
	invertX->selected = globals.invertX;
	invertX->commit();
	invertY->selected = globals.invertY;
	invertY->commit();
	flipXY->selected = globals.flipXY;
	flipXY->commit();
}

//--------------------------------------------------------------
void OsciView::buttonPressed( const void * sender, ofTouchEventArgs & args ){
	mui::Container * container = (mui::Container*) sender;
	
	if( sender == stopButton ){
		ofBaseApp * app = ofGetAppPtr();
		app->gotMessage( ofMessage( "stop-pressed" ) );
	}
	else if( sender == playButton ){
		if( globals.player.isPlaying ){
			globals.player.stop();
		}
		else{
			globals.player.play();
		}
	}
	else if( sender == invertX ){
		globals.invertX = invertX->selected;
	}
	else if( sender == invertY ){
		globals.invertY = invertY->selected;
	}
	else if( sender == flipXY ){
		globals.flipXY = flipXY->selected;
	}
	else if( sender == fullscreenButton ){
		ofSetFullscreen(fullscreenButton->selected);
		// windows becomes black without this, not sure why...
		//TODO: check if this is still a problem in of0.9
		#ifdef _WIN32
		if(fullscreenButton->selected){
			int w = ofGetScreenWidth(); 
			int h = ofGetScreenHeight(); 
			ofSetWindowShape(w,h); 
		}
		#endif
	}
	else if( sender == loadFileButton ){
		ofFileDialogResult res = ofSystemLoadDialog("Load audio file", false );
		if( res.bSuccess ){
			ofSendMessage("load:" + res.filePath); 
		}
	}
	else if( sender == useMicButton ){
		if( globals.micActive ){
			ofSendMessage("stop-mic");
		}
		else{
			if( micMenu != NULL ){
				MUI_ROOT->safeRemoveAndDelete(micMenu);
			}
			
			micMenu = new FMenu(0,0,400,0);
			mui::Button * cancelButton = micMenu->addButton("Cancel");
			cancelButton->bg = ofColor(100,100);
			vector<ofSoundDevice> infos = ofSoundStream().getDeviceList();
			for( int i = 0; i < infos.size(); i++ ){
				ofSoundDevice &info = infos[i];
				if( info.inputChannels >= 2 ){
					micMenu->addButton(info.name);
					micDeviceIds[info.name] = i;
				}
			}
			ofAddListener(micMenu->onPress, this, &OsciView::buttonPressed);
			micMenu->autoSize();
			micMenu->bg = ofColor(150);
			micMenu->opaque = true; 
			
			add(micMenu);
		}
	}
	else if( micMenu != NULL && container->parent->parent == micMenu ){
		map<string,int>::iterator it = micDeviceIds.find(((mui::Button*)sender)->label->text);
		if( it != micDeviceIds.end() ){
			globals.micDeviceId = (*it).second;
			ofSendMessage("start-mic");
		}
		MUI_ROOT->safeRemoveAndDelete(micMenu);
		micMenu = NULL;
	}
}

void OsciView::sliderChanged( const void * sender, float & value ){
	if( sender == outputVolumeSlider->slider ){
		globals.outputVolume = outputVolumeSlider->slider->value;
	}
	else if( sender == scaleSlider1->slider ){
		globals.scale1 = scaleSlider1->slider->value;
	}
	else if( sender == scaleSlider2->slider ){
		globals.scale2 = scaleSlider2->slider->value;
	}
	else if( sender == spreadSlider->slider ){
		globals.spread = spreadSlider->slider->value;
	}
	else if( sender == strokeWeightSlider->slider ){
		globals.strokeWeight = strokeWeightSlider->slider->value;
	}
	else if( sender == blurSlider->slider ){
		globals.blur = blurSlider->slider->value;
	}
	else if( sender == numPtsSlider->slider ){
		globals.numPts = numPtsSlider->slider->value;
	}
	else if( sender == hueSlider1->slider ){
		globals.hue1 = hueSlider1->slider->value;
	}
	else if( sender == hueSlider2->slider ){
		globals.hue2 = hueSlider2->slider->value;
	}
	else if( sender == intensitySlider->slider ){
		globals.intensity = intensitySlider->slider->value;
	}
	else if( sender == afterglowSlider->slider ){
		globals.afterglow = afterglowSlider->slider->value;
	}
}


mui::Label * OsciView::addLabel( string text ){
	mui::Label * label = new mui::Label( text, 0, 0, 100, 30 );
	label->commit();
	label->width = label->boundingBox.width;
	label->horizontalAlign = mui::Right;
	add( label );
	return label;
}

