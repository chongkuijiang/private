package com.abido.jiang.scantracker;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.Bitmap;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.baidu.location.BDLocation;
import com.baidu.location.BDLocationListener;
import com.baidu.location.LocationClient;
import com.baidu.location.LocationClientOption;
import com.baidu.mapapi.SDKInitializer;
import com.baidu.mapapi.map.BaiduMap;
import com.baidu.mapapi.map.MapStatusUpdate;
import com.baidu.mapapi.map.MapStatusUpdateFactory;
import com.baidu.mapapi.map.MapView;
import com.baidu.mapapi.map.MyLocationData;
import com.baidu.mapapi.model.LatLng;
import com.baidu.trace.LBSTraceClient;
import com.google.zxing.activity.CaptureActivity;
import com.google.zxing.utils.CommonUtil;

import java.text.SimpleDateFormat;


public class MainActivity extends Activity/* implements SensorEventListener */{
/*
    MapView mMapView = null;
    BaiduMap mBaiduMap;
    MapStatusUpdate mBaiduMapStatus;
    Entity entity;
    Button openQrCodeScan,but_Scan,btnLng;

    String qrCodeText;

    private ScanTracerApp app;

    private int mCurrentDirection = 0;
    private double mCurrentLat = 0.0;
    private double mCurrentLon = 0.0;
    private float mCurrentAccracy;
    private MyLocationData locData;
 //   public MyLocationListenner myListener = new MyLocationListenner();
    private Double lastX = 0.0;
    SQLiteDatabase scanDB;


    //打开扫描界面请求码
    private int REQUEST_CODE = 0x01;
    //扫描成功返回码
    private int RESULT_OK = 0xA1;
*/
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
       // app = (ScanTracerApp)getApplication();
   //     requestWindowFeature(Window.FEATURE_NO_TITLE);
    //    getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
      // setContentView(R.layout.activity_start);
        setContentView(R.layout.fgdgdfg);
/*
        mMapView = (MapView) findViewById(R.id.bmapView);
        mBaiduMap = mMapView.getMap();

        mBaiduMapStatus = MapStatusUpdateFactory.zoomTo(6.0f);
        mBaiduMap.setMapStatus(mBaiduMapStatus);
        mBaiduMap.setMyLocationEnabled(true);
        initLocation(app.getContext());


        entity = app.getEntity();
        entity.setmBaiduMap(mBaiduMap);
        entity.setText((TextView)findViewById(R.id.txt));

        openQrCodeScan = (Button)findViewById(R.id.openQrCodeScan);
        but_Scan = (Button)findViewById(R.id.but_Scan);
        btnLng = (Button)findViewById(R.id.but_lng);

        View.OnClickListener butClickListener = new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                switch (view.getId()) {
                    case R.id.openQrCodeScan:
                        //打开二维码扫描界面
                        if(CommonUtil.isCameraCanUse()){
                            Intent intent = new Intent(MainActivity.this, CaptureActivity.class);
                           startActivityForResult(intent, REQUEST_CODE);

                        }else{
                            Toast.makeText(MainActivity.this,"请打开此应用的摄像头权限！",Toast.LENGTH_SHORT).show();
                        }
                        break;
                    case R.id.but_Scan:
                        Intent intent = new Intent("com.scantraceker.scan");
                        startActivity(intent);
                        break;
                    case R.id.but_lng:
                        LatLng ll = new LatLng(mCurrentLat,mCurrentLon);
                        mBaiduMapStatus = MapStatusUpdateFactory.newLatLng(ll);
                        mBaiduMap.setMapStatus(mBaiduMapStatus);
                        mBaiduMapStatus = MapStatusUpdateFactory.zoomTo(19.0f);
                        mBaiduMap.setMapStatus(mBaiduMapStatus);
                        btnLng.setBackgroundResource(R.drawable.lng_2);
                        break;

                }
            }
        } ;
        openQrCodeScan.setOnClickListener(butClickListener);
        but_Scan.setOnClickListener(butClickListener);
        btnLng.setOnClickListener(butClickListener);



*/
    }
 /*   @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        //扫描结果回调
        if (resultCode == RESULT_OK) { //RESULT_OK = -1
            Bundle bundle = data.getExtras();
            qrCodeText = bundle.getString("qr_scan_result");
            entity.EntitySearch(qrCodeText);
            Intent intent = new Intent("com.scantraceker.scan");
            startActivity(intent);
            //将扫描出的信息显示出来
          //  but_Scan.setText(qrCodeText);
        }
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int i) {

    }

    private void initLocation(Context context){
        LocationClient mLocClient;
        mLocClient = new LocationClient(context); // 定位初始化
        mLocClient.registerLocationListener(myListener);
        LocationClientOption option = new LocationClientOption();
        option.setLocationMode(LocationClientOption.LocationMode.Hight_Accuracy);
        option.setOpenGps(true); // 打开gps
        option.setCoorType("bd09ll"); // 设置坐标类型
        option.setScanSpan(1500);
        mLocClient.setLocOption(option);
        mLocClient.start();
    }

    @Override
    public void onSensorChanged(SensorEvent sensorEvent) {
        double x = sensorEvent.values[SensorManager.DATA_X];
        if (Math.abs(x - lastX) > 1.0) {
            mCurrentDirection = (int) x;
            locData = new MyLocationData.Builder()
                    .accuracy(mCurrentAccracy)
                    // 此处设置开发者获取到的方向信息，顺时针0-360
                    .direction(mCurrentDirection).latitude(mCurrentLat)
                    .longitude(mCurrentLon).build();
            mBaiduMap.setMyLocationData(locData);
        }
        lastX = x;
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        //在activity执行onDestroy时执行mMapView.onDestroy()，实现地图生命周期管理
       mMapView.onDestroy();
    }

    @Override
    protected void onResume() {
        super.onResume();

        // tityadapter.notifyDataSetChanged();
        //在activity执行onResume时执行mMapView. onResume ()，实现地图生命周期管理
        mMapView.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
        //在activity执行onPause时执行mMapView. onPause ()，实现地图生命周期管理
        mMapView.onPause();
    }

    private  class MyLocationListenner implements BDLocationListener {

        @Override
        public void onReceiveLocation(BDLocation location) {
            // map view 销毁后不在处理新接收的位置
            if (location == null || mMapView == null) {
                return;
            }
            mCurrentLat = location.getLatitude();
            mCurrentLon = location.getLongitude();
            mCurrentAccracy = location.getRadius();
            locData = new MyLocationData.Builder()
                    .accuracy(location.getRadius())
                    // 此处设置开发者获取到的方向信息，顺时针0-360
                    .direction(mCurrentDirection).latitude(location.getLatitude())
                    .longitude(location.getLongitude()).build();
            mBaiduMap.setMyLocationData(locData);

        }

        @Override
        public void onConnectHotSpotMessage(String s, int i) {

        }
    }
 */
}
