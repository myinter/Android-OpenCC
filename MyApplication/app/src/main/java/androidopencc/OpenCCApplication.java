package androidopencc;

import android.app.Application;
import android.content.Context;

/**
 * Created by xiongwei on 16/5/19.
 */
//调用的时候，必须将本Application设置为 当前应用的 Application
public class OpenCCApplication extends Application {
    private static Context context;
    @Override
    public void onCreate() {
        super.onCreate();
        context = getApplicationContext();
    }
    public static Context getContext(){
        return context;
    }

}