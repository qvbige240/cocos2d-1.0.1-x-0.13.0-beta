/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.application;

import java.io.IOException;
import java.util.HashMap;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxEditText;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.cocos2dx.lib.GameAppConfig;
import org.xmlpull.v1.XmlPullParserException;

import android.content.res.Resources;
import android.content.res.XmlResourceParser;
import android.os.Bundle;

public class ApplicationDemo extends Cocos2dxActivity{
	private Cocos2dxGLSurfaceView mGLView;
	
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		
		// get the packageName,it's used to set the resource path
		String packageName = getApplication().getPackageName();
		super.setPackageName(packageName);
		
		setContentView(R.layout.helloworld_demo);
        	mGLView = (Cocos2dxGLSurfaceView) findViewById(R.id.helloworld_gl_surfaceview);
        	mGLView.setTextField((Cocos2dxEditText)findViewById(R.id.textField));
		
		GameAppConfig.mHashMap = parserKeyValueXML(this, R.xml.keymap);
	}
	

	// Key value XML parser
	public static HashMap<Integer, Integer> parserKeyValueXML(ApplicationDemo activity, int xmlID) {  
		Resources res = activity.getResources();    
		XmlResourceParser xmlParser = res.getXml(xmlID);  
		HashMap<Integer, Integer> mMap = new HashMap<Integer, Integer>();  
		   
		try {  
			int eventType = xmlParser.getEventType();  
		     // File end?   
			while (eventType != XmlResourceParser.END_DOCUMENT) {  
				if (eventType == XmlResourceParser.START_TAG) {    
					String tagname = xmlParser.getName();    
					if (tagname.endsWith("key")) {
						//Log.v("====Error", xmlParser.getAttributeValue(null, "eurowing") + " ####  " + xmlParser.getAttributeValue(null, "game"));
						mMap.put(
							Integer.parseInt(xmlParser.getAttributeValue(null, "eurowing")), //eurowing actual key value
							Integer.parseInt(xmlParser.getAttributeValue(null, "game")));    //mapping game needs key value
	 				}   
				} else if (eventType == XmlResourceParser.END_TAG) {    
					
				} else if (eventType == XmlResourceParser.TEXT) {    
					
				}  
				eventType = xmlParser.next();    
			}  
		} catch (XmlPullParserException e) {    
		             
		} catch (IOException e) {  
			e.printStackTrace();  
		}  
		xmlParser.close();  
		return mMap;  
	} 

	 @Override
	 protected void onPause() {
	     super.onPause();
	     mGLView.onPause();
	 }

	 @Override
	 protected void onResume() {
	     super.onResume();
	     mGLView.onResume();
	 }
	
     static {
         System.loadLibrary("helloworld");
     }
}
