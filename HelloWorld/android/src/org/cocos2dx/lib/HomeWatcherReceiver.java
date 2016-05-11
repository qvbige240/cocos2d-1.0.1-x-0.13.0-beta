package org.cocos2dx.lib;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

public class HomeWatcherReceiver extends BroadcastReceiver {

    private static final String SYSTEM_DIALOG_REASON_KEY = "reason";
    private static final String SYSTEM_DIALOG_REASON_RECENT_APPS = "recentapps";
    private static final String SYSTEM_DIALOG_REASON_HOME_KEY = "homekey";
    private static final String SYSTEM_DIALOG_REASON_LOCK = "lock";
    private static final String SYSTEM_DIALOG_REASON_ASSIST = "assist";

    @Override
    public void onReceive(Context context, Intent intent) {
        String action = intent.getAction();
		Log.w("COCOS2D", "Duz onReceive: action: " + action);
        if (action.equals(Intent.ACTION_CLOSE_SYSTEM_DIALOGS)) {
            String reason = intent.getStringExtra(SYSTEM_DIALOG_REASON_KEY);
			Log.w("COCOS2D", "Duz reason: " + reason);

            if (SYSTEM_DIALOG_REASON_HOME_KEY.equals(reason)) {
                // 短按Home键
				Log.w("COCOS2D", "Duz HomeKey");
				Cocos2dxActivity.audioAbandonFocus();
            }else if (SYSTEM_DIALOG_REASON_RECENT_APPS.equals(reason)) {
                // 长按Home键 或者 activity切换键
				Log.w("COCOS2D", "Duz long press home key or activity switch");
				Cocos2dxActivity.audioAbandonFocus();
            }else if (SYSTEM_DIALOG_REASON_LOCK.equals(reason)) {
                // 锁屏
				Log.w("COCOS2D", "Duz lock");
				Cocos2dxActivity.audioAbandonFocus();
            }else if (SYSTEM_DIALOG_REASON_ASSIST.equals(reason)) {
                // samsung 长按Home键
				Log.w("COCOS2D", "Duz assist");
				Cocos2dxActivity.audioAbandonFocus();
            }

        }
    }

}
