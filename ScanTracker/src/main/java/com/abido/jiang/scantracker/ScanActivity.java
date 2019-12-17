package com.abido.jiang.scantracker;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.view.WindowManager;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;

import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;



/**
 * Created by Administrator on 2017/8/3.
 */

public class ScanActivity extends Activity {

/*
    Button but_back,but_go_scan;
    Button btn_StartTime,btn_goEntity,btn_goTrace;
    EditText edit_Scan;
    ListView list_scan,tityEn_list;
    LinearLayout layout_entity,list_entity;
    Entity entity;


    private List<Map<String,String>> scan_ListData = new ArrayList<>();
    private List<Map<String,String>> resultList = new ArrayList<>();
    private SimpleAdapter scan_adapter,entity_adapter;
    private long currentTime = System.currentTimeMillis() / 1000;
    private String traceStartTime;

    private DateDialog dateDialog = null;
    private DateDialog.Callback startTimeCallback = null;
    private SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm");
    private DecimalFormat df = new DecimalFormat(".##");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.layout_scan);

//
        entity = ((ScanTracerApp)getApplication()).getEntity();
        entity.setEntityinfo(new Entity.EntityInfo() {
            @Override
            public void getEntityInfo(String name, String phon, String creatTime, String modifyTime,
                                      String lon,String lat)
            {
                TextView entity_name,entity_phon,entity_lng,entity_creatTime,entity_modifyTime;
                TextView entity_adderss,txt_Distancebtn;
                entity_name = (TextView)findViewById(R.id.entity_name);
                entity_phon = (TextView)findViewById(R.id.entity_phon);
                entity_lng = (TextView)findViewById(R.id.entity_lng);
                entity_creatTime = (TextView)findViewById(R.id.entity_creatTime);
                entity_modifyTime = (TextView)findViewById(R.id.entity_modifyTime);
                entity_adderss = (TextView)findViewById(R.id.entity_adderss);
                txt_Distancebtn = (TextView)findViewById(R.id.txt_Distancebtn);

                entity_name.setText(name);
                entity_phon.setText(phon);
                entity_creatTime.setText(creatTime);
                entity_modifyTime.setText(modifyTime);
                entity_lng.setText(lat+", "+lon);
                display(2);
            }

            @Override
            public void getEntityList() {
                entity_adapter.notifyDataSetChanged();
                display(3);
            }
        });


        layout_entity = (LinearLayout)findViewById(R.id.laout_entity);
        list_entity = (LinearLayout)findViewById(R.id.list_entity);

  //---------------------------------------------------------------------------------------------
        edit_Scan = (EditText)findViewById(R.id.edit_Scan);
        edit_Scan.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {

            }

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                searchEntity(charSequence.toString());
                scan_adapter.notifyDataSetChanged();
            }

            @Override
            public void afterTextChanged(Editable editable) {

            }
        });
   //--------------------------------------------------------------------------------------------
        View.OnClickListener bntListener = new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                switch (view.getId()){
                    case R.id.but_back:
                        finish();
                        break;
                    case R.id.but_go_scan:
                        String keyword = edit_Scan.getText().toString().trim();
                        if(!keyword.isEmpty()) entity.EntitySearch(keyword);
                        break;
                    case R.id.btn_goEntity:
                        break;
                    case R.id.btn_goTrace:
                        break;
                    case R.id.btn_StartTime:
                        setStartTime(ScanActivity.this);
                        break;
                }
            }
        };
        but_back = (Button)findViewById(R.id.but_back);
        but_go_scan = (Button)findViewById(R.id.but_go_scan);
        btn_goEntity = (Button)findViewById(R.id.btn_goEntity);
        btn_goTrace = (Button)findViewById(R.id.btn_goTrace);
        btn_StartTime = (Button)findViewById(R.id.btn_StartTime);

        but_back.setOnClickListener(bntListener);
        but_go_scan.setOnClickListener(bntListener);
        btn_goEntity.setOnClickListener(bntListener);
        btn_goTrace.setOnClickListener(bntListener);
        btn_StartTime.setOnClickListener(bntListener);
        btn_StartTime.setText(getStartTime());
   //-------------------------------------------------------------------------------------------
        AdapterView.OnItemClickListener scanlistener = new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                String entity_name;
                switch (adapterView.getId()) {
                    case R.id.list_scan:
                        entity_name = resultList.get(i).get("phon");
                        edit_Scan.setText(entity_name);
                        display(0);
                        break;
                    case R.id.tityEn_list:
                        entity_name = entity.getEntityList().get(i).get("phon");
                        edit_Scan.setText(entity_name);
                        display(0);
                        break;
                }
            }
        };
        for(int i=0;i<6;i++){
            addScanItme("feffff", "1122322122");
        }
        scan_adapter =  new SimpleAdapter(this, resultList, R.layout.style_scan,
                new String[]{"name", "phon"}, new int[]{R.id.scan_name, R.id.scan_phon});

        entity_adapter =  new SimpleAdapter(this, entity.getEntityList(), R.layout.entitylist_style,
                new String[]{"name", "phon","creatTime"}, new int[]{R.id.name, R.id.phon,R.id.creatTime});


        list_scan = (ListView)findViewById(R.id.list_scan);
        tityEn_list = (ListView)findViewById(R.id.tityEn_list);
        list_scan.setOnItemClickListener(scanlistener);
        tityEn_list.setOnItemClickListener(scanlistener);
        list_scan.setAdapter(scan_adapter);
        tityEn_list.setAdapter(entity_adapter);
   //------------------------------------------------------------------------------------------
        display(0);
    //    entity.EntitySearch("myTrace");
      //  entity.EntitySearch("12345678901");

    }
    private void addScanItme(String name, String phon){
        Map<String,String> map = new HashMap<>();
        map.put("name",name);
        map.put("phon",phon);
        map.put("creatTime",String.valueOf(currentTime));
        scan_ListData.add(map);
    }
    private void deleteScanItem(int i){
        long passTime = currentTime - Long.valueOf(scan_ListData.get(i).get("creatTime"));
       // if(passTime >)
    }
    private void searchEntity(String entity){
        resultList.clear();
        if(!entity.isEmpty()){
            display(1);
            for (Map<String,String> map: scan_ListData) {
                if( map.get("name").contains(entity) || map.get("phon").contains(entity) ){
                    Map<String,String> src = new HashMap<>();
                    src.put("name",map.get("name"));
                    src.put("phon",map.get("phon"));
                    resultList.add(src);
                }
            }
        }

    }
    private String getStartTime(){
        StringBuilder startTimeBuilder = new StringBuilder();
        long startTime = System.currentTimeMillis()-24*60*60*1000;
        startTimeBuilder.append(simpleDateFormat.format(startTime));
        return startTimeBuilder.toString();
    }
    private void setStartTime(Activity activity) {
        if (null == startTimeCallback) {
            startTimeCallback = new DateDialog.Callback() {
                @Override
                public void onDateCallback(long timeStamp) {
                    long startTime = System.currentTimeMillis()/1000 -24*60*60; //s
                    if(timeStamp < startTime) startTime = timeStamp;

                    StringBuilder startTimeBuilder = new StringBuilder();
                    startTimeBuilder.append(simpleDateFormat.format(startTime*1000));
                    traceStartTime = startTimeBuilder.toString();
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
    private void display(int i){
        switch (i){
            case 1:
                list_scan.setVisibility(View.VISIBLE);
                layout_entity.setVisibility(View.INVISIBLE);
                list_entity.setVisibility(View.INVISIBLE);
                break;
            case 2:
                list_scan.setVisibility(View.INVISIBLE);
                layout_entity.setVisibility(View.VISIBLE);
                list_entity.setVisibility(View.INVISIBLE);
                break;
            case 3:
                list_scan.setVisibility(View.INVISIBLE);
                layout_entity.setVisibility(View.INVISIBLE);
                list_entity.setVisibility(View.VISIBLE);
                break;
            default:
                list_scan.setVisibility(View.INVISIBLE);
                layout_entity.setVisibility(View.INVISIBLE);
                list_entity.setVisibility(View.INVISIBLE);
                break;
        }

    }


    private class scanAdapter extends BaseAdapter{
        private Context context;
        public scanAdapter(Context context){
            this.context = context;
        }
        @Override
        public View getView(int i, View view, ViewGroup viewGroup) {
            View v = view;
          //  if(view == null){
                v = LayoutInflater.from(context).inflate(R.layout.style_scan,viewGroup,false);
          //  }
            TextView scan_name = (TextView)v.findViewById(R.id.scan_name);
            TextView scan_phon = (TextView)v.findViewById(R.id.scan_phon);
            scan_name.setText(scan_ListData.get(i).get("name"));
            scan_phon.setText(scan_ListData.get(i).get("phon"));
            return v;
        }

        @Override
        public int getCount() {
            return scan_ListData.size();
        }

        @Override
        public Object getItem(int i) {
            return i;
        }

        @Override
        public long getItemId(int i) {
            return i;
        }
    }
*/
}
