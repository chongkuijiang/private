package com.abido.jiang.scantracker;

import android.app.Activity;
import android.graphics.Color;
import android.os.Handler;
import android.os.Message;
import android.widget.Button;
import android.widget.TextView;

import com.baidu.mapapi.map.BaiduMap;
import com.baidu.mapapi.map.OverlayOptions;
import com.baidu.mapapi.map.Polyline;
import com.baidu.mapapi.map.PolylineOptions;
import com.baidu.mapapi.model.LatLng;
import com.baidu.trace.LBSTraceClient;
import com.baidu.trace.api.track.HistoryTrackRequest;
import com.baidu.trace.api.track.HistoryTrackResponse;
import com.baidu.trace.api.track.OnTrackListener;

import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Created by Administrator on 2017/8/7.
 */

public class Trace {
    /*
    private static int TAG_OK;
    private static int TAG_ERR;
    private BaiduMap mBaiduMap;
    private LBSTraceClient mTraceClient;
    private List<Map<String,Object>> tracedataSouer;
    private OnTrackListener trackListener;
    private HistoryTrackRequest historyTrackRequest;
    private long traceStartTime;
    private List<LatLng> Trackpoints = new ArrayList<LatLng>();
    private List<Map<String,Object>> resultList = new ArrayList<>();
    private Handler handler;

    private Activity activity;
    private Button startTime_btn;
    private DateDialog dateDialog = null;
    private DateDialog.Callback startTimeCallback = null;
    private SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm");
    private DecimalFormat df = new DecimalFormat(".##");

    private TextView txtView;

    public Trace(BaiduMap bmap,LBSTraceClient mTraceClient,
                       long serviceId,Handler mhandler,int ok,int err) {

        TAG_OK = ok;
        TAG_ERR = err;
        this.mBaiduMap = bmap;
        this.mTraceClient = mTraceClient;
        this.handler = mhandler;
        historyTrackRequest = new HistoryTrackRequest(TAG_OK, serviceId);
        trackListener = new OnTrackListener() {
            @Override
            public void onHistoryTrackCallback(HistoryTrackResponse historyTrackResponse) {
                double lat,lng;
                if(historyTrackResponse.getStatus() == 0){
                    for(int i =0;i<historyTrackResponse.getTrackPoints().size();i++) {
                        lat = historyTrackResponse.getTrackPoints().get(i).getLocation().getLatitude();
                        lng = historyTrackResponse.getTrackPoints().get(i).getLocation().getLongitude();
                        Trackpoints.add(new LatLng(lat,lng));
                    }
                    setDistance(historyTrackResponse.getEntityName(),historyTrackResponse.getDistance());
                    Message msg = new Message();
                    msg.what = TAG_OK;
                    handler.sendMessage(msg);
                    drawTrace(Trackpoints);
                }

            }
        };
    }
    public void drawTrace(List<LatLng> points){
        OverlayOptions ooPolyline = new PolylineOptions().width(10)
                .color(Color.RED)
                .points(points);
        Polyline mPolyline = (Polyline) mBaiduMap.addOverlay(ooPolyline);
    }
    private void setDistance(String entityName,double distance){
        String dist_str = String.valueOf(df.format(distance/1000))+"km";
        for (Map<String,Object> map:tracedataSouer) {
            if(((String)map.get("name")).compareTo(entityName) == 0){
                map.put("distance",dist_str);
                break;
            }
        }
        for (Map<String,Object> map:resultList) {
            if(((String)map.get("name")).compareTo(entityName) == 0){
                map.put("distance",dist_str);
                break;
            }
        }
    }


    public List<Map<String, Object>> getTracedataSouer() {
        return resultList;
    }
    public void searchTraceName(String entity){
        resultList.clear();
        for (Map<String,Object> map: tracedataSouer) {
            if(((String)map.get("name")).contains(entity)||((String)map.get("phon")).contains(entity)){
                Map<String,Object> src = new HashMap<>();
                src.put("name",map.get("name"));
                src.put("distance",map.get("distance"));
                resultList.add(src);
            }

        }
    }
    public void initTraceData(List<Map<String, Object>> datalist){
        tracedataSouer = datalist;
        for (Map<String,Object> map: tracedataSouer){
            Map<String,Object> src = new HashMap<>();
            src.put("name",map.get("name"));
            src.put("distance","0km");
            resultList.add(src);
        }
    }
    public void findHistoryTrack(){

        new Thread(){
            @Override
            public void run() {
                // 是否返回精简结果
                int simpleReturn = 0;
// 是否纠偏
                int isProcessed = 0;
// 纠偏选项
                String processOption = null;
                //    traceStartTime = Long.valueOf(startTime_btn.getText().toString());
                //   traceStartTime = System.currentTimeMillis()/1000 -24*60*60;
// 结束时间
                //    long endTime = traceStartTime + 24*60*60*1000;
                long endTime =  traceStartTime + 24*60*60;
// 分页大小
                int pageSize = 5000;
// 分页索引
                int pageIndex = 1;


                //     for (Map<String,String> map:tracedataSouer) {
                String entityName = "myTraceClient";//tracedataSouer.get(0).get("name");
                historyTrackRequest.setEntityName(entityName);
                historyTrackRequest.setStartTime(traceStartTime);
                historyTrackRequest.setEndTime(endTime);
                //  historyTrackRequest.setProcessed();
                historyTrackRequest.setPageIndex(pageIndex);
                historyTrackRequest.setPageSize(pageSize);
                mTraceClient.queryHistoryTrack(historyTrackRequest, trackListener);

                //     }
            }
        }.start();
    }
    public void getStartTime() {
        if (null == startTimeCallback) {
            startTimeCallback = new DateDialog.Callback() {
                @Override
                public void onDateCallback(long timeStamp) {
                    long startTime = System.currentTimeMillis()/1000 -24*60*60; //s
                    if(timeStamp < startTime) startTime = timeStamp;

                    traceStartTime = startTime;
                    StringBuilder startTimeBuilder = new StringBuilder();
                    startTimeBuilder.append(simpleDateFormat.format(startTime*1000));
                    startTime_btn.setText(startTimeBuilder.toString());
                    findHistoryTrack();
                }
            };
        }
        if (null == dateDialog) {

            dateDialog = new DateDialog(activity, startTimeCallback);
        } else {
            dateDialog.setCallback(startTimeCallback);
        }
        dateDialog.show();
    }
    public void setView(TextView txt){
        txtView = txt;
    }
    public void setActivityButton(Activity activity, Button btn){
        this.activity = activity;
        this.startTime_btn = btn;
    }
*/
}
