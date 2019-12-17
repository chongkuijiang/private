package com.abido.jiang.scantracker;

import android.content.Context;
import android.os.Handler;
import android.os.Message;
import android.widget.SimpleAdapter;
import android.widget.TextView;

import com.baidu.mapapi.map.BaiduMap;
import com.baidu.mapapi.map.BitmapDescriptor;
import com.baidu.mapapi.map.BitmapDescriptorFactory;
import com.baidu.mapapi.map.InfoWindow;
import com.baidu.mapapi.map.MapStatusUpdate;
import com.baidu.mapapi.map.MapStatusUpdateFactory;
import com.baidu.mapapi.map.Marker;
import com.baidu.mapapi.map.MarkerOptions;
import com.baidu.mapapi.map.OverlayOptions;
import com.baidu.mapapi.model.LatLng;
import com.baidu.trace.LBSTraceClient;
import com.baidu.trace.api.entity.EntityListRequest;
import com.baidu.trace.api.entity.EntityListResponse;
import com.baidu.trace.api.entity.FilterCondition;
import com.baidu.trace.api.entity.OnEntityListener;
import com.baidu.trace.api.entity.SearchRequest;
import com.baidu.trace.api.entity.SearchResponse;
import com.baidu.trace.model.CoordType;

import org.json.JSONException;
import org.json.JSONObject;

import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Created by Administrator on 2017/8/5.
 */

public class Entity {/*
    private static int TAG_OK;
    private static int TAG_ERR;

    private Context context;
    private BaiduMap mBaiduMap;
    private LBSTraceClient mTraceClient;
    private List<Map<String,Object>> titydataSouer = new ArrayList<>();
    private List<Map<String,String>> entityList = new ArrayList<>();
    private List<Marker> Listmarker = new ArrayList<>();
    private List<String> listAdress = new ArrayList<>();
    private EntityListRequest Listrequest;
    private SearchRequest Searchrequest;
    private InfoWindow mInfoWindow;
    private FilterCondition filterCondition;
    private CoordType coordTypeOutput;
    private OnEntityListener entityListener;
    private BitmapDescriptor bitmap;

    private EntityInfo entityinfo;

    private DecimalFormat lngf = new DecimalFormat(".##########");

    private int total;
    private static final int GEOCODER_OK = 5;
    private static final int GEOCODER_ERR = 6;
    private Handler handler;

    private TextView txtView;
    private Handler handler_geocode = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            switch (msg.what){
                case GEOCODER_OK:

                    StringBuilder adr = new StringBuilder();
                    try {
                        JSONObject json = new JSONObject((String) msg.obj);
                        if(json.getInt("status")==0){
                            JSONObject result = json.getJSONObject("result");
                            JSONObject address = result.getJSONObject("addressComponent");
                            adr.append(address.get("country"));
                            adr.append(address.get("province"));
                            adr.append(address.get("district"));
                            adr.append("("+address.get("city")+")");
                            adr.append(address.get("street"));
                            listAdress.add(adr.toString());

                        }
                    }catch (JSONException e) {
                        e.printStackTrace();
                    }
                    break;
            }
        }
    };
    public void setText(TextView txt){
        txtView = txt;
    }


    public void setmBaiduMap(BaiduMap mMap) {
        this.mBaiduMap = mMap;
        this.mBaiduMap.setOnMarkerClickListener(new BaiduMap.OnMarkerClickListener(){
            @Override
            public boolean onMarkerClick(Marker marker) {
                addMarker(marker);
                return true;
            }
        });
    }

    public Entity(final Context context, LBSTraceClient mTraceClient,
                  long serviceId, Handler hand, int ok, int err){

        TAG_OK = ok;
        TAG_ERR = err;
        this.context = context;
        this.mTraceClient = mTraceClient;
        this.handler = hand;

        bitmap = BitmapDescriptorFactory.fromResource(R.drawable.gcoding);
        filterCondition = new FilterCondition(); // 过滤条件
        coordTypeOutput = CoordType.bd09ll; // 返回结果坐标类型
        Listrequest = new EntityListRequest(TAG_OK, serviceId);
        Searchrequest = new SearchRequest(TAG_OK,serviceId);
        // 初始化监听器
        entityListener = new OnEntityListener() {
            @Override
            public void onEntityListCallback(EntityListResponse response) {
                if(response.getStatus()==0){
                    total = response.getTotal();
                    for (int i=0;i<total;i++){
                        addEntity(response.getEntities().get(i).getEntityName(),
                                response.getEntities().get(i).getEntityDesc(),
                                response.getEntities().get(i).getCreateTime());
                        OverlayMarker(response.getEntities().get(i).getLatestLocation().getLocation().getLongitude(),
                                response.getEntities().get(i).getLatestLocation().getLocation().getLatitude());
                    }
                    addAdress();

                }else{
                    Message msg = new Message();
                    msg.what = TAG_ERR;
                    handler.sendMessage(msg);

                }
            }

            @Override
            public void onSearchEntityCallback(SearchResponse searchResponse) {
                double lon, lat;
                if(searchResponse.getStatus() == 0){
                    total = searchResponse.getTotal();
                    if(total == 1){
                        lon = searchResponse.getEntities().get(0).getLatestLocation().getLocation().getLongitude();
                        lat = searchResponse.getEntities().get(0).getLatestLocation().getLocation().getLatitude();
                        entityinfo.getEntityInfo(
                                searchResponse.getEntities().get(0).getEntityName(),
                                searchResponse.getEntities().get(0).getEntityDesc(),
                                searchResponse.getEntities().get(0).getCreateTime(),
                                searchResponse.getEntities().get(0).getModifyTime(),
                                String.valueOf(lngf.format(lon)),String.valueOf(lngf.format(lat))
                        );
                    }else{
                        entityList.clear();
                        for(int i=0;i<total;i++){
                            addSearchList(searchResponse.getEntities().get(i).getEntityName(),
                                    searchResponse.getEntities().get(i).getEntityDesc(),
                                    searchResponse.getEntities().get(i).getCreateTime()
                            );
                        }
                        entityinfo.getEntityList();
                    }

                   //    txtView.setText(searchResponse.toString());
                }
            }
        };


    }


    private void addEntity(String name, String phon, String creatTime){
        Map<String,Object> map = new HashMap<>();
        map.put("name",name);
        map.put("phon",phon);
        map.put("creatTime",creatTime);
        map.put("distance","0km");
        titydataSouer.add(map);

    }

    public void EntityList(){

        long activeTime = System.currentTimeMillis() / 1000 - 5*60;
        filterCondition.setActiveTime(0);  //ActiveTime(activeTime);

        // 创建Entity列表请求实例
        Listrequest.setCoordTypeOutput(coordTypeOutput);
        Listrequest.setFilterCondition(filterCondition);
        Listrequest.setPageIndex(1);
        Listrequest.setPageSize(100);

        // 查询Entity列表
        mTraceClient.queryEntityList(Listrequest, entityListener);

    }
    public void EntitySearch(String keyword){
        Searchrequest.setKeyword(keyword);
        filterCondition.setActiveTime(0);  //ActiveTime(activeTime);

        Searchrequest.setCoordTypeOutput(coordTypeOutput);
        Searchrequest.setFilterCondition(filterCondition);
        Searchrequest.setPageIndex(1);
        Searchrequest.setPageSize(100);

        mTraceClient.searchEntity(Searchrequest,entityListener);
    }
    private  void OverlayMarker(double lon,double lat){
        //定义Maker坐标点
        LatLng point = new LatLng(lat, lon);
//构建MarkerOption，用于在地图上添加Marker
        OverlayOptions option = new MarkerOptions()
                .position(point)
                .icon(bitmap);
//在地图上添加Marker，并显示
        Marker m =  (Marker) (mBaiduMap.addOverlay(option));
        Listmarker.add(m);

    }
    private void addAdress(){
        new Thread(){
            public void run() {
                HttpURL http = new HttpURL(handler_geocode,GEOCODER_OK,GEOCODER_ERR);
                for (Marker marker:Listmarker) {
                    StringBuilder url = new StringBuilder("http://api.map.baidu.com/geocoder/v2/?");
                    LatLng ll = marker.getPosition();
                    url.append("location=" + ll.latitude +","+ ll.longitude);
                    url.append("&output=json&ak=mRwNHB49l6W4cHFWuelkvN3OnK6rZ8sg&extensions_poi=null");
                    http.doGet(url.toString());
                }

                Message adrmsg = new Message();
                adrmsg.what = TAG_OK;
                handler.sendMessage(adrmsg);
            };
        }.start();

    }
    public void addMarker(Marker marker){
        Infotity info =  new Infotity(context);
        info.setBackgroundResource(R.drawable.popup);
        info.setMinimumHeight(280);
        info.setMinimumWidth(500);
        LatLng ll = marker.getPosition();
        info.setTity_Location(ll);
        int i = Listmarker.indexOf(marker);
        info.setTity_name((String)titydataSouer.get(i).get("name"));
        info.setTity_phon((String)titydataSouer.get(i).get("phon"));
        info.setTity_adr(listAdress.get(i));
        InfoWindow.OnInfoWindowClickListener listener = null;
        listener = new InfoWindow.OnInfoWindowClickListener() {
            @Override
            public void onInfoWindowClick() {
                mBaiduMap.hideInfoWindow();
            }
        };
        mInfoWindow = new InfoWindow(BitmapDescriptorFactory.fromView(info), ll, -50, listener);
        mBaiduMap.showInfoWindow(mInfoWindow);
        MapStatusUpdate mBaiduMapStatus = MapStatusUpdateFactory.newLatLng(ll);
        mBaiduMap.setMapStatus(mBaiduMapStatus);

    }
    public Marker getMarker(int i){
        Marker marker = Listmarker.get(i);
        return marker;
    }



    public List<Map<String, String>> getEntityList() {
        return entityList;
    }

    private void addSearchList(String name, String phon,String creatTime){
        Map<String,String> map = new HashMap<>();
        map.put("name",name);
        map.put("phon",phon);
        map.put("creatTime",creatTime);
        entityList.add(map);

    }
    public void setEntityinfo(EntityInfo entityinfo) {
        this.entityinfo = entityinfo;
    }

    public interface EntityInfo {
        void getEntityInfo(String name, String phon, String creatTime, String modifyTime,
                           String lon,String lat);
        void getEntityList();

    }
*/
}
