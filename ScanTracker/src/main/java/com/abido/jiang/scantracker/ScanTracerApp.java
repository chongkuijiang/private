package com.abido.jiang.scantracker;

import android.app.Application;
import android.content.Context;
import android.os.Handler;

import com.baidu.mapapi.SDKInitializer;
import com.baidu.trace.LBSTraceClient;

/**
 * Created by Administrator on 2017/8/8.
 */

public class ScanTracerApp extends Application {
    static final long serviceId = 144062;
    private Context context;
 //   private LBSTraceClient mTraceClient;
    private Handler handler;
//    private Entity entity;
    private static final int ENTITY_OK = 1;
    private static final int ENTITY_ERROR = 2;
    private static final int TRACE_OK = 3;
    private static final int TRACE_ERROR = 4;

    @Override
    public void onCreate() {
        super.onCreate();
        context = getApplicationContext();
     /*   SDKInitializer.initialize(context);
        mTraceClient = new LBSTraceClient(context);
        entity = new Entity(context,mTraceClient,serviceId,
                handler,ENTITY_OK,ENTITY_ERROR);
                */
    }

//    public Entity getEntity() {
//        return entity;
//    }

    public Context getContext() {
        return context;
    }

  //  public LBSTraceClient getmTraceClient() {
 //       return mTraceClient;
 //   }

}
