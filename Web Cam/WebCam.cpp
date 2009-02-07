// WebCam.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "cv.h"
#include "highgui.h"

// r,g,b values are from 0 to 1
// h = [0,360], s = [0,1], v = [0,1]
//		if s == 0, then h = -1 (undefined)

#define min2(a,b)            (((a) < (b)) ? (a) : (b))
#define min3(a,b,c)            (min2(min2(a,b),c))
#define max2(a,b)            (((a) > (b)) ? (a) : (b))
#define max3(a,b,c)            (max2(max2(a,b),c))

void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v )
{
	float min, max, delta;
	min = min3( r, g, b );
	max = max3( r, g, b );
	*v = max;				// v
	delta = max - min;
	if( max != 0 )
		*s = delta / max;		// s
	else {
		// r = g = b = 0		// s = 0, h is undefined
		*s = 0;
		*h = -1;
		return;
	}
	if( r == max )
		*h = ( g - b ) / delta;		// between magenta & yellow
	else if( g == max )
		*h = 2 + ( b - r ) / delta;	// between yellow & cyan
	else
		*h = 4 + ( r - g ) / delta;	// between cyan & magenta
	*h *= 60;				// degrees
	if( *h < 0 )
		*h += 360;
}

int main(int argc, char* argv[])
{
    CvCapture* capture = 0;
    IplImage *frame, *frame_Hue = 0, *frame_Saturation = 0, *frame_InterestAreas = 0;
	
	capture = cvCaptureFromCAM(0);
	//capture = cvCaptureFromAVI("d:\\skoda2002.avi"); 
    cvNamedWindow( "Color", 1 );
    cvNamedWindow( "Hue", 1 );
    cvNamedWindow( "Saturation", 1 );
    cvNamedWindow( "Interest Areas", 1 );

    if( capture )
    {
        cvGrabFrame( capture );
        frame = cvRetrieveFrame( capture );

        frame_Hue = cvCreateImage( cvSize(frame->width,frame->height),
                                    IPL_DEPTH_8U, frame->nChannels );
        frame_Saturation = cvCreateImage( cvSize(frame->width,frame->height),
                                    IPL_DEPTH_8U, frame->nChannels );
        frame_InterestAreas = cvCreateImage( cvSize(frame->width,frame->height),
                                    IPL_DEPTH_8U, frame->nChannels );
        for(;;)
        {
            if( !cvGrabFrame( capture ))
                break;
            frame = cvRetrieveFrame( capture );
            if( !frame )
                break;

            cvFlip( frame, frame, 0 ); //se pare ca intotdeauna imaginile vin cu capu in jos

			int line, col;
            unsigned char* pSrcPixels = (unsigned char*)frame->imageData;
            unsigned char* pHuePixels = (unsigned char*)frame_Hue->imageData;
            unsigned char* pSaturationPixels = (unsigned char*)frame_Saturation->imageData;
            unsigned char* pInterestAreasPixels = (unsigned char*)frame_InterestAreas->imageData;
			for (line = 0; line < frame->height; line++)
				for (col = 0; col < frame->width; col++)
				{
					int PixelOffset = line*frame->widthStep + col*3;
					unsigned char r = pSrcPixels[PixelOffset];
					unsigned char g = pSrcPixels[PixelOffset+1];
					unsigned char b = pSrcPixels[PixelOffset+2];
					//just copy
/*					pHuePixels[PixelOffset] = r;
					pHuePixels[PixelOffset+1] = g;
					pHuePixels[PixelOffset+2] = b;
*/					//rgb to hsv
					float fh, fs, fv;
					RGBtoHSV(r/255.f, g/255.f, b/255.f, &fh, &fs, &fv);
					unsigned char h = (unsigned char)(fh*255/360);
					unsigned char s = (unsigned char)(fs*255);
					unsigned char v = (unsigned char)(fv*255);
					pHuePixels[PixelOffset] = h;
					pHuePixels[PixelOffset+1] = h;
					pHuePixels[PixelOffset+2] = h;

					pSaturationPixels[PixelOffset] = s;
					pSaturationPixels[PixelOffset+1] = s;
					pSaturationPixels[PixelOffset+2] = s;
					
					int InterestValue;
					if (s > 150 && (h > 170 && h < 185))
						InterestValue = 255;
					else
						InterestValue = 0;
					pInterestAreasPixels[PixelOffset] = InterestValue;
					pInterestAreasPixels[PixelOffset+1] = InterestValue;
					pInterestAreasPixels[PixelOffset+2] = InterestValue;
					
					//rgb to gray
/*					unsigned char gray = (r + g + b)/3;
					pHuePixels[PixelOffset] = gray;
					pHuePixels[PixelOffset+1] = gray;
					pHuePixels[PixelOffset+2] = gray;
*/				}
          

			//IplImage* gray = cvCreateImage( cvSize(frame_copy->width,frame_copy->height), 8, 1 );
			//cvCvtColor( frame_copy, gray, CV_BGR2GRAY );
            cvFlip( frame, frame, 0 );
			cvShowImage( "Color", frame );
			cvShowImage( "Hue", frame_Hue );
			cvShowImage( "Saturation", frame_Saturation );
			cvShowImage( "Interest Areas", frame_InterestAreas );
			//cvReleaseImage( &gray );


            if( cvWaitKey( 10 ) >= 0 )
                break;
        }

        cvReleaseImage( &frame_Hue );
        cvReleaseImage( &frame_Saturation );
        cvReleaseImage( &frame_InterestAreas );
        cvReleaseCapture( &capture );
    }
    
    cvDestroyWindow("Color");
    cvDestroyWindow("Hue");
    cvDestroyWindow("Saturation");
    cvDestroyWindow("Interest Areas");
	
	return 0;
}

