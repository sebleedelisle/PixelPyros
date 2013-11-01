//
//  QuadWarp.cpp
//  PixelPyros
//
//  Created by Seb Lee-Delisle on 30/08/2012.
//
//  The QuadWarp object is used to calculate homography between two quads.
//  Its functionality overlaps Warper, except that Warper owns a bitmap, whereas
//  this doesn't. In many ways this method is better as it doesn't actually do any
//  pixel manipulation. It's primarily used to warp the projector images to map onto
//  the screen, but it's also used to warp the laser output to match the screen. 

#include "QuadWarp.h"

#include "matrix_funcs.h"

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

QuadWarp :: QuadWarp (string saveLabel) {
	
	label = saveLabel;

	pointColour = ofColor :: white;
	dstPoints.resize(4);
	srcPoints.resize(4);
    dstControlPoints.resize(8);
    dstPointsStartDrag.resize(4);
    offset = ofVec2f(0,0);
	
	for(int i = 0; i<4;i++) {
		srcPoints[i].set( (i%2)*100, (i/2)*100);
		dstPoints[i].set( (i%2)*100, (i/2)*100);
        
        float cpDistance = 50;
        int n = (i/2^(i%2))&1;
        dstControlPoints[i*2].set( ( 0.5 - n ) * cpDistance, 0 );
        dstControlPoints[i*2+1].set( 0, ( 0.5 - floor(i/2) )*cpDistance );
	}
    
    
	/*
	ofVec3f midpoint = srcPoints[0] + ((srcPoints[3] - srcPoints[0]) / 2);
	srcPoints[4] = dstPoints[4] = midpoint;
	*/
	updateHomography();
	
	visible = false;
    useBoundsRect = false;
	pointRadius = 10;
	controlPointRadius = 8;
    curDragPointIndex = -1;
	lastMousePress = 0;
	
	ofAddListener(ofEvents().mousePressed, this, &QuadWarp::mousePressed);
	ofAddListener(ofEvents().mouseDragged, this, &QuadWarp::mouseDragged);
	ofAddListener(ofEvents().mouseReleased, this, &QuadWarp::mouseReleased);


}

QuadWarp :: ~QuadWarp() {
	
	ofRemoveListener(ofEvents().mousePressed, this, &QuadWarp::mousePressed);
	ofRemoveListener(ofEvents().mouseDragged, this, &QuadWarp::mouseDragged);
	ofRemoveListener(ofEvents().mouseReleased, this, &QuadWarp::mouseReleased);

}

void QuadWarp :: draw() {
	draw(ofGetKeyPressed(OF_KEY_SHIFT));

}

void QuadWarp :: draw(bool lockAxis) {
	
	if(!visible) return;
	
    /* dragging center point */
    if( curDragPointIndex==8 ){
        ofVec3f diff(ofGetMouseX() - offset.x - dragStartPoint.x, ofGetMouseY() - offset.y - dragStartPoint.y );
                
        for( int i=0; i< dstPoints.size();i++){
            dstPoints[i] = dstPointsStartDrag[i] + diff;
        }
        
        clampPoints();
        updateHomography();
        
    }
    /* dragging corner point */
	else if(curDragPointIndex>=0 && curDragPointIndex<4) {
		
		ofVec3f diff(ofGetMouseX() - offset.x, ofGetMouseY() - offset.y );
        
        /* single point dragging */
        if(dragAltPressed){
            
            if(lockAxis) {
                if(abs(diff.x)-abs(diff.y)>1) diff.y = 0;
                else if (abs(diff.y)-abs(diff.x)>1) diff.x = 0;
            }
            
            
            diff-=dragStartPoint;
            diff*=dragSpeed;
            
            ofVec3f& curPoint = dstPoints[curDragPointIndex];
            
            curPoint = dragStartPoint+diff+clickOffset;
            
            curPoint.x = round(curPoint.x*10)/10;
            curPoint.y = round(curPoint.y*10)/10;
            
            if(useBoundsRect) {
                if(curPoint.x<boundsRectangle.getLeft()) curPoint.x = boundsRectangle.getLeft();
                if(curPoint.x>boundsRectangle.getRight()) curPoint.x = boundsRectangle.getRight();
                if(curPoint.y<boundsRectangle.getTop()) curPoint.y = boundsRectangle.getTop();
                if(curPoint.y>boundsRectangle.getBottom()) curPoint.y = boundsRectangle.getBottom();
            }
        }
        /* scale dragging */
        else {
            ofVec3f center = dragCenterStart;
            
            if(cornerScalingMode) {
                int i=curDragPointIndex;
                int j=(i+1)%dstPoints.size();
                int k=(i+dstPoints.size()-1)%dstPoints.size();
                int oppositeCornerIndex = (i+2)%dstPoints.size();
                ofVec3f curPoint = dstPoints[curDragPointIndex];
                ofVec3f oppositePoint = dstPointsStartDrag[oppositeCornerIndex];
                ofVec3f dragPointRelative = curPoint - dstPointsStartDrag[oppositeCornerIndex];
                
                float scale = diff.distance( oppositePoint ) / dragStartPoint.distance(oppositePoint);
                float len = dstPointsStartDrag[i].distance( oppositePoint );
                float l2 = dstPointsStartDrag[j].distance( oppositePoint );
                float l3 = dstPointsStartDrag[k].distance( oppositePoint );
                
                bool nextPointIsHorizontalClamped = i&1;
                
                dstPoints[i] = oppositePoint + ( dstPointsStartDrag[i] - oppositePoint ).normalize() * len * scale;
                
                ofVec3f nextPoint = ( oppositePoint + ( dstPointsStartDrag[j] - oppositePoint ).normalize() * l2 * scale );
                ofVec3f lastPoint = ( oppositePoint + ( dstPointsStartDrag[k] - oppositePoint ).normalize() * l3 * scale );
                
                if( nextPointIsHorizontalClamped ){
                    
                    dstPoints[j].x = nextPoint.x;
                    dstPoints[k].y = lastPoint.y;
                }
                else{
                    dstPoints[j].y = nextPoint.y;
                    dstPoints[k].x = lastPoint.x;
                }
            }
            else{
            
                float scale = diff.distance( center ) / dragStartPoint.distance(center);
                
                for( int i=0; i< dstPoints.size();i++){
                    float len = dstPointsStartDrag[i].distance( center );
                    
                    dstPoints[i] = center + ( dstPointsStartDrag[i] - center ).normalize() * len * scale;
                }
            }
        }

        clampPoints();
        updateHomography();
				
	}
    /* dragging side point */
    else if(curDragPointIndex>=4 && curDragPointIndex<8){
        ofVec3f diff(ofGetMouseX() - offset.x - dragStartPoint.x, ofGetMouseY() - offset.y - dragStartPoint.y );
        
        if(lockAxis) {
            if(abs(diff.x)-abs(diff.y)>1) diff.y = 0;
            else if (abs(diff.y)-abs(diff.x)>1) diff.x = 0;
        }
        
        diff += clickOffset;
        int i = curDragPointIndex-4;
        int j = (i+1)%dstPoints.size();
        dstPoints[i] = dstPointsStartDrag[i] + diff;
        dstPoints[j] = dstPointsStartDrag[j] + diff;
        
        clampPoints();
        updateHomography();
    }
    else if(curDragPointIndex>8){
        ofVec3f diff(ofGetMouseX() - offset.x, ofGetMouseY() - offset.y );
        
        int cpIndex = curDragPointIndex-9;
        int i = floor( cpIndex / 2 );
        dstControlPoints[cpIndex] = diff + clickOffset - dstPoints[i];
    
    }
	
	
	ofPushStyle();
	ofNoFill();
	
	ofPushMatrix();
	
    ofTranslate(offset.x, offset.y);
	
	//ofEnableSmoothing();
	//ofScale(1024, 768);
	for(int i = 0; i < dstPoints.size(); i++) {
		
		
		ofVec3f& point = dstPoints[i];
        drawMarker(point, pointColour, pointRadius);
	
        if( useBarrelingCorrection ){
            int j = (i+1)%dstPoints.size();
            ofVec3f hControlPoint = dstControlPoints[i*2]+point;
            ofVec3f vControlPoint = dstControlPoints[i*2+1]+point;
            ofVec3f nextPoint =  dstPoints[j];
            ofVec3f nextHControlPoint =  dstControlPoints[j*2]+nextPoint;
            ofVec3f nextVControlPoint =  dstControlPoints[j*2+1]+nextPoint;
            
            drawMarker(hControlPoint,pointColour,controlPointRadius);
            drawMarker(vControlPoint,pointColour,controlPointRadius);
            
            ofPolyline curve;
            curve.addVertex(point);
            if( i&1 )
                curve.bezierTo( vControlPoint, nextVControlPoint, nextPoint );
            else
                curve.bezierTo( hControlPoint, nextHControlPoint, nextPoint );
            
            curve.draw();
        }
        
		if(i == curDragPointIndex){
			
			ofLine(point.x, point.y - 100, point.x, point.y+100); 
			ofLine(point.x-100, point.y, point.x+100, point.y);
			
			//ofDrawBitmapStringHighlight(ofToString(point.x), point.x, point.y-30, ofColor(0,0,0,100));
			//ofDrawBitmapStringHighlight(ofToString(point.y), point.x-30, point.y, ofColor(0,0,0,100));
		}
        
        int j = (i+1)%dstPoints.size();
        ofVec3f side = 0.5f * ( dstPoints[i] + dstPoints[j] );
		drawMarker(side, ofColor::cyan, pointRadius);
		
	}
	
    ofVec3f center = getCenter();
    drawMarker(center, ofColor::greenYellow, pointRadius);
    if( curDragPointIndex == 4 ){
        ofLine(center.x, center.y - 100, center.x, center.y+100);
        ofLine(center.x-100, center.y, center.x+100, center.y);
    }
    
	ofPopMatrix();
	ofPopStyle();
	
}

void QuadWarp::clampPoints(){
    if(useBoundsRect) {
        for(int i=0;i<dstPoints.size();i++){
            ofVec3f& point = dstPoints[i];
            if(point.x<boundsRectangle.getLeft()) point.x = boundsRectangle.getLeft();
            if(point.x>boundsRectangle.getRight()) point.x = boundsRectangle.getRight();
            if(point.y<boundsRectangle.getTop()) point.y = boundsRectangle.getTop();
            if(point.y>boundsRectangle.getBottom()) point.y = boundsRectangle.getBottom();
        }
    }
}

void QuadWarp::drawMarker(ofVec3f& point, const ofColor & color, float radius){
    ofSetColor(ofColor::black);
    ofSetLineWidth(3);
    ofCircle(point, 1);
    ofSetColor(color);
    ofSetLineWidth(1);
    ofCircle(point, radius);
    ofCircle(point, 1);
}

void QuadWarp::setOffset(float x,float y){
    offset.x = x;
    offset.y = y;
}

void QuadWarp ::setDstPoint(int index, ofVec3f point){
	
	if(index>=dstPoints.size()) {
		dstPoints.resize(index+1);
		setSrcPoint(index, point);
	}
	
	dstPoints[index] = point;
	updateHomography();
	
	
}

void QuadWarp ::setSrcPoint(int index, ofVec3f point){
	
	if(index>=srcPoints.size()) {
		srcPoints.resize(index+1);
		setDstPoint(index, point); 
	}
	
	srcPoints[index] = point;
	updateHomography();
	
	
}

ofVec3f QuadWarp::getCenter(){
    ofVec3f centre = ofVec3f(0,0,0);
    for(int i = 0; i < dstPoints.size(); i++) {
        centre+=dstPoints[i];
    }
    centre /= dstPoints.size();
    
    return centre;
}

// stolen from ofxAppUtils - thanks danomatika !

void QuadWarp ::apply(ofRectangle sourceRect){
	
	
	// we set it to the default - 0 translation
	// and 1.0 scale for x y z and w
	for(int i = 0; i < 16; i++) {
		if(i % 5 != 0) _glWarpMatrix[i] = 0.0;
		else _glWarpMatrix[i] = 1.0;
	}
	
	// source and destination points
	double src[srcPoints.size()][2];
	double dest[dstPoints.size()][2];
	
	// we set the warp coordinates
	// source coordinates as the dimensions of our window

	for(int i = 0; i<srcPoints.size(); i++) {
		src[i][0] = srcPoints[i].x;
		src[i][1] = srcPoints[i].y;
	}

	for(int i = 0; i < dstPoints.size(); i++){
		dest[i][0] = dstPoints[i].x;
		dest[i][1] = dstPoints[i].y;
	}
	
	// perform the warp calculation
	mapQuadToQuad(src, dest, _warpMatrix);
	
	// copy the values
	_glWarpMatrix[0]	= _warpMatrix[0][0];
	_glWarpMatrix[1]	= _warpMatrix[0][1];
	_glWarpMatrix[3]	= _warpMatrix[0][2];
	
	_glWarpMatrix[4]	= _warpMatrix[1][0];
	_glWarpMatrix[5]	= _warpMatrix[1][1];
	_glWarpMatrix[7]	= _warpMatrix[1][2];
	
	_glWarpMatrix[12]	= _warpMatrix[2][0];
	_glWarpMatrix[13]	= _warpMatrix[2][1];
	_glWarpMatrix[15]	= _warpMatrix[2][2];
	
	// finally lets multiply our matrix
	glMultMatrixf(_glWarpMatrix);

	
	
	
}; 

void QuadWarp::updateHomography() {
	
	
	vector<Point2f> srcCVPoints, dstCVPoints;
	if(srcPoints.size()!=dstPoints.size()) {
		cout << "RUH ROH" << endl;
	}
		
	
	for(int i = 0; i < srcPoints.size(); i++) {
		srcCVPoints.push_back(Point2f(srcPoints[i].x , srcPoints[i].y));
		dstCVPoints.push_back(Point2f(dstPoints[i].x, dstPoints[i].y));
	}

	
	//cout << srcPoints[3] << " " << dstPoints[3] << endl;
	homography = cv::findHomography(cv::Mat(srcCVPoints), cv::Mat(dstCVPoints));
	inverseHomography = homography.inv();
}

ofVec3f QuadWarp::getWarpedPoint(ofVec3f point){
	
	vector<cv::Point2f> pre, post;
	
	pre.push_back(cv::Point2f(point.x, point.y));
	post.push_back(cv::Point2f());
	
	//cout << "getWarpedPoint" << pre[0] << endl;
	
	cv::perspectiveTransform(pre, post, homography);
	//cout << "warped" << post[0] << endl;

	
//	return ofxCv::toOf(pre[0]);
	
//	return point;s
    
    point = ofxCv::toOf(post[0]);
    if( useBarrelingCorrection ) point = barrelCorrection( point );
    
    return point;

}

ofVec3f QuadWarp::barrelCorrection(ofVec3f point){
    return barrelCorrection(point,false);
}

ofVec3f QuadWarp::barrelUncorrection(ofVec3f point){
    return barrelCorrection(point,true);
}

ofVec3f QuadWarp::barrelCorrection(ofVec3f point,bool inverse){
    
    /*
    float aspectRatio = srcRangeRect / srcRangeRect.height;
    float radius = SQRT2 * srcRangeRect.width;
    
    point.x = ofMap( point.x, srcRangeRect.getMinX(), srcRangeRect.getMaxX(), 0.0f, 1.0f);
    point.y = ofMap( point.x, srcRangeRect.getMinY(), srcRangeRect.getMaxY(), 0.0f, 1.0f);
    
    point = point.normalize() * ( point.length() + barrellingAmount * ( radius - point.length() ) );
    
     ofVec3f normPoint(
     ofMap( point.x, srcRangeRect.getMinX(), srcRangeRect.getMaxX(), 0.0f, 1.0f),
     ofMap( point.x, srcRangeRect.getMinY(), srcRangeRect.getMaxY(), 0.0f, 1.0f)
     );
     
     srcRangeRect.set(srcPoints[0], 0.0f, 0.0f);
     srcRangeRect.growToInclude(srcPoints[1]);
     srcRangeRect.growToInclude(srcPoints[2]);
     srcRangeRect.growToInclude(srcPoints[3]);
     
     
     */
    
    ofVec3f center = getCenter();
    
    /* 
        Find the first quad side that intersects with the ray cast from the quad center through our point.
     
        Then find the distance of that intersection, and the distance of intersection with the bezier of that quad side.
     
        Finally scale the points distance from the center to the ratio of these two distances.
     */
    for(int i=0;i<dstPoints.size();i++){
        
        int j = (i+1)%dstPoints.size();
        int cpI = ( i*2+(i&1) );
        int cpJ = ( j*2+(~i&1) );
        
        ofVec3f dstStartPoint = dstPoints[i];
        ofVec3f dstEndPoint = dstPoints[j];
        ofVec3f cp1 = dstControlPoints[cpI] + dstStartPoint;
        ofVec3f cp2 = dstControlPoints[cpJ] + dstEndPoint;
        
        ofVec3f ray = (point-center).normalize();
        ofVec3f intersection;
        
        if( rayInterectionWithLine( center, ray, dstPoints[i], dstPoints[j], intersection ) ){
            cout << "Intersection: " << intersection << endl;
            float lineDistance = intersection.distance(center);
            
            if( rayIntersectionWithBezier( center, ray, dstStartPoint, dstEndPoint, cp1, cp2, intersection ) ){
                float intersectionDistance = intersection.distance( center );
                
                return ( point - center ).normalize() * ( intersectionDistance / lineDistance ) + center;
            }
            
            
        }
        
        
    }
    
    return point;
        
}

/* Does the line p1-p2 intersect with p3-p4 */
bool QuadWarp::rayInterectionWithLine(ofVec3f p1, ofVec3f r1, ofVec3f p3, ofVec3f p4, ofVec3f& intersection ){
    
    ofVec3f p2 = p1 + r1;
    ofVec3f u = p4-p3;
    ofVec3f v = p2-p1;
    ofVec3f normalV = v.perpendicular(ofVec3f(0,0,1));
    ofVec3f normalU = u.perpendicular(ofVec3f(0,0,1));
    
    ofVec3f w = p1 - p3;
    
    float normalVDotW = -normalV.dot(w);
    float normalVDotU = normalV.dot(u);
    float normalUDotW = normalU.dot(w);
    float normalUDotV = normalU.dot(v);
    if( normalVDotU == 0.0f ) return false;
    
    float s = normalVDotW / normalVDotU;
    float t = normalUDotW / normalUDotV;
    
    if( s < 0.0f || s > 1.0f ) return false;
    if( t < 0.0f ) return false;
    
    intersection = s*u+p3;
    return true;
}

bool QuadWarp::rayIntersectionWithBezier(ofVec3f lp1, ofVec3f r1,ofVec3f bp1,ofVec3f bp2,ofVec3f cp1, ofVec3f cp2, ofVec3f& closestIntersection){
    
    ofVec3f lp2 = lp1+r1;
    float A = lp2.y - lp1.y;
    float B = lp1.x - lp2.x;
    float C = lp1.x * ( lp1.y - lp2.y ) + lp1.y * ( lp2.x - lp1.x );
    
    vector<float> bx = bezierCoeffs(bp1.x, cp1.x, cp2.x, bp2.x);
    vector<float> by = bezierCoeffs(bp1.y, cp1.y, cp2.y, bp2.y);
    
    
    float a = A*bx[0]+B*by[0];
    float b = A*bx[1]+B*by[1];	
    float c = A*bx[2]+B*by[2];	
    float d = A*bx[3]+B*by[3] + C;
    
    vector<float> roots = cubicRoots(a, b, c, d);
    
    float lowestS = MAXFLOAT;
    for( int i=0; i<roots.size(); i++){
        float t=roots[i];
        float s;
        ofPoint intersection( bx[0]*t*t*t+bx[1]*t*t+bx[2]*t+bx[3], by[0]*t*t*t+by[1]*t*t+by[2]*t+by[3] );
        
        /* check to see if line is vertical */
        if( lp2.x - lp1.x != 0 ){
            s=intersection.x-lp1.x/(lp2.x-lp1.x);
        }
        else{
            s=intersection.y-lp1.y/(lp2.y-lp1.y);
        }
        
        if( s < 0 || t < 0 || t > 1 ) continue;
        
        if( s < lowestS ){
            closestIntersection = intersection;
            lowestS = s;
        }
        
    }
    
    return ( lowestS != MAXFLOAT );
}

vector <float> QuadWarp::bezierCoeffs(float P0,float P1,float P2,float P3)
{
	vector <float> Z(4);
	Z[0] = -P0 + 3*P1 + -3*P2 + P3;
    Z[1] = 3*P0 - 6*P1 + 3*P2;
    Z[2] = -3*P0 + 3*P1;
    Z[3] = P0;
	return Z;
}

 /*
  * Finds the roots of the curve equation, returns between 0 and 3 values
  */
 vector<float> QuadWarp::cubicRoots(float a, float b, float c, float d){
    float A = a/b;
    float B = b/c;
    float C = c/d;
    float Q = ( 3*B - A*A ) / 9;
    float R = (9*A*B - 27*C - 2*A*A*A)/54;
    float D = Q*Q*Q + R*R;
    float Im;
    float t0, t1, t2;
     
    vector<float> t(0);
    
     if( D>=0 ){
        float S = sgn( R + sqrt( D ) ) * pow( abs( R + sqrt( D ) ), 1/3 );
        float T = sgn( R - sqrt( D ) ) * pow( abs( R - sqrt( D ) ), 1/3 );
         float t0 = -A/3 + ( S + T );
         
         Im = abs( sqrt(3) * (S-T)/2 );
         if( Im==0 ){
             float t1 = -A/3 - ( S + T )/2;
             float t2 = -A/3 - ( S + T )/2;
         }
     }
     else
     {
         float th = acos(R/sqrt(-pow(Q, 3)));
         t0 = 2 * sqrt(-Q) * cos(th/3) - A/3;
         t1 = 2 * sqrt(-Q) * cos((th + TWO_PI)/3) - A/3;
         t2 = 2 * sqrt(-Q) * cos((th + FOUR_PI)/3) - A/3;
     }
     
     if( 0.0f<=t0 && t0<=1.0f ) t.push_back( t0 );
     if( 0.0f<=t1 && t1<=1.0f ) t.push_back( t1 );
     if( 0.0f<=t2 && t2<=1.0f ) t.push_back( t2 );
    
    return t;
}

ofVec3f QuadWarp::getUnWarpedPoint(ofVec3f point){
	
	vector<cv::Point2f> pre, post;
	
	
	pre.push_back(cv::Point2f(point.x, point.y));
	post.push_back(cv::Point2f());
	
	//cout << "getWarpedPoint" << pre[0] << endl;
	
	cv::perspectiveTransform(pre, post, inverseHomography);
	//cout << "warped" << post[0] << endl;
	
	point = ofxCv::toOf(post[0]);
	//	return ofxCv::toOf(pre[0]);
	
	//	return point;
	
    if( useBarrelingCorrection ){
        point = barrelUncorrection( point );
    }
    
    return point;
}

void QuadWarp :: mousePressed(ofMouseEventArgs &e) {
	
	if(!visible) return;
	
		
	ofVec3f clickPoint(e.x - offset.x, e.y - offset.y);
	   
	for(int i = 0; i < dstPoints.size(); i++) {
        
        if(dstPoints[i].distance(clickPoint) < pointRadius) {
			curDragPointIndex = i;
			ofVec3f &curPoint = dstPoints[i];
            
			clickOffset = curPoint - clickPoint;
			dragStartPoint = clickPoint;
			dragCenterStart = getCenter();
            dragAltPressed = ofGetKeyPressed(OF_KEY_ALT);
            
            for(int j = 0; j < dstPoints.size(); j++) {
                dstPointsStartDrag[j].set( dstPoints[j] );
            }
			
            break;
		}
        
        int k = (i+1)%dstPoints.size();
        ofVec3f middlePoint = 0.5 * ( dstPoints[i] + dstPoints[k] );
        if(middlePoint.distance(clickPoint) < pointRadius) {
            curDragPointIndex = i+4;
            dragStartPoint = middlePoint;
            clickOffset = middlePoint - clickPoint;
            for(int j = 0; j < dstPoints.size(); j++) {
                dstPointsStartDrag[j].set( dstPoints[j] );
            }
            break;
        }
        
        ofVec3f controlPointHorizontal = dstControlPoints[i*2]+dstPoints[i];
        ofVec3f controlPointVertical = dstControlPoints[i*2+1]+dstPoints[i];
        if( controlPointHorizontal.distance(clickPoint)< controlPointRadius ){
            curDragPointIndex = (i*2)+9;
            dragStartPoint = controlPointHorizontal;
            clickOffset = controlPointHorizontal - clickPoint;
        }
        
        if( controlPointVertical.distance(clickPoint)< controlPointRadius ){
            curDragPointIndex = (i*2)+10;
            dragStartPoint = controlPointVertical;
            clickOffset = controlPointVertical - clickPoint;
        }
	}
    
    if( getCenter().distance( clickPoint ) < pointRadius ){
        curDragPointIndex = 8;
        dragStartPoint = clickPoint;
        clickOffset = getCenter() - clickPoint;
        for(int j = 0; j < dstPoints.size(); j++) {
            dstPointsStartDrag[j].set( dstPoints[j] );
        }
    }
		
};


void QuadWarp :: mouseDragged(ofMouseEventArgs &e) {
	if(!visible) return;
	
	
		
};



void QuadWarp :: mouseReleased(ofMouseEventArgs &e) {
	if(!visible) return;
	
    if(curDragPointIndex==8){
        curDragPointIndex = -1;
        saveSettings();
    }
	else if(curDragPointIndex>=0) {
		
		if(ofGetElapsedTimef() - lastMousePress < 0.4 && curDragPointIndex<4) {
			dstPoints[curDragPointIndex] = srcPoints[curDragPointIndex];			
		}

		curDragPointIndex = -1;
		updateHomography();
		saveSettings();
	}
	
	lastMousePress  = ofGetElapsedTimef() ; 
	
};

bool QuadWarp::loadSettings() {
	  
	string filename = "warpdata/"+label+".xml";
	ofxXmlSettings xml;
	if(!xml.loadFile(filename)) {
		ofLog(OF_LOG_ERROR, "QuadWarp::loadSettings - file not found : "+filename);
		return false;
		
	}
	
	//cout << "Warp Pre load: " << filename << " " << dstPoints[0].x << ", " << dstPoints[0].y << endl;
    
    
	dstPoints[0].x	= xml.getValue("quad:upperLeft:x", 0.0);
	dstPoints[0].y	= xml.getValue("quad:upperLeft:y", 0.0);
	
	dstPoints[1].x	= xml.getValue("quad:upperRight:x", 1.0);
	dstPoints[1].y	= xml.getValue("quad:upperRight:y", 0.0);
	
	dstPoints[2].x	= xml.getValue("quad:lowerRight:x", 1.0);
	dstPoints[2].y	= xml.getValue("quad:lowerRight:y", 1.0);
	
	dstPoints[3].x	= xml.getValue("quad:lowerLeft:x", 0.0);
	dstPoints[3].y	= xml.getValue("quad:lowerLeft:y", 1.0);
	
    //cout << "Loading Warp: " << filename << " " << dstPoints[0].x << ", " << dstPoints[0].y << endl;
    
    if( useBarrelingCorrection ){
        //TODO Load control points for barrelling correction
    }

    
    updateHomography();
    
	return true;
}

void QuadWarp::saveSettings() {
	     
	ofxXmlSettings xml;
	
	string filename = "warpdata/"+label+".xml";
    
	xml.addTag("quad");
	xml.pushTag("quad");
	
	xml.addTag("upperLeft");
	xml.pushTag("upperLeft");
	xml.addValue("x", dstPoints[0].x);
	xml.addValue("y", dstPoints[0].y);
	xml.popTag();
	
	xml.addTag("upperRight");
	xml.pushTag("upperRight");
	xml.addValue("x", dstPoints[1].x);
	xml.addValue("y", dstPoints[1].y);
	xml.popTag();
	
	xml.addTag("lowerRight");
	xml.pushTag("lowerRight");
	xml.addValue("x", dstPoints[2].x);
	xml.addValue("y", dstPoints[2].y);
	xml.popTag();
	
	xml.addTag("lowerLeft");
	xml.pushTag("lowerLeft");
	xml.addValue("x", dstPoints[3].x);
	xml.addValue("y", dstPoints[3].y);
	xml.popTag();
    
    if( useBarrelingCorrection ){
        //TODO Store control points for barrelling correction
    }
	
	xml.saveFile(filename);
    
    
}

std::ostream& operator<< (std::ostream& stream, const QuadWarp& warp){

    for(int i=0;i<warp.dstPoints.size();i++){
        stream << (float) warp.dstPoints[i].x << ", ";
        stream << (float) warp.dstPoints[i].y << ": ";
    }
    
    return stream;
}

std::istream& operator>> (std::istream& stream, QuadWarp& warp){
    float component;
	
	// TODO I'm pretty sure we need some error checking here
	
    for(int i=0;i<warp.dstPoints.size();i++){
        stream >> component;
        warp.dstPoints[i].x = component;
        stream.ignore(2);
        stream >> component;
        warp.dstPoints[i].y = component;
        stream.ignore(2);
    }
    
    return stream;
}


