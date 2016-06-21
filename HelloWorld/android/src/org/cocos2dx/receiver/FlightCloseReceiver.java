package org.cocos2dx.receiver;
import java.io.File;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.os.*;


public class FlightCloseReceiver extends BroadcastReceiver {

	private static native void nativeCloseFlight();
	private static Context context;

	@Override
	public void onReceive(Context context, Intent intent) {
		
		//删除游戏进度（即删除游戏存档文件）
		
		//get packageName 
		String fielDir = context.getFilesDir().getAbsolutePath();
		Log.v("Duz fielDir", fielDir);
		String path = context.getPackageResourcePath();
		Log.v("Duz path", path);
		//String DataBase = context.getDatabasePath(s).getAbsolutePath();
		//Log.v("Duz DataPath", DataBase);

		String packageName = context.getPackageName();
		Log.v("Duz packageName", packageName);
		// < cocos2dx 2.1.5
		String fileName = "/data/data/"+packageName+"/UserDefault.xml";
		// >= cocos2dx 2.1.5 
		//String fileName = "/data/data/"+packageName+"/shared_prefs/Cocos2dxPrefsFile.xml";
		Log.v("Duz delete file:", fileName);
		File file = new File(fileName);
		if (file.isFile() && file.exists()) {
        		file.delete();
			Log.v("Duz delete ", "file ok");
        }		
		
		//关闭进程
		android.os.Process.killProcess(android.os.Process.myPid());
	}


	public static void setContext(Context context){
		FlightCloseReceiver.context = context;
	}
}

