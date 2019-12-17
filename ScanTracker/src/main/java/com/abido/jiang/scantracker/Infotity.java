package com.abido.jiang.scantracker;


import android.content.Context;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.baidu.mapapi.model.LatLng;


/**
 * Created by Administrator on 2017/7/19.
 */

public class Infotity extends LinearLayout {
    TextView tity_name,tity_phon,tity_adr,tity_Location;

    public Infotity(Context context) {
        super(context);
        init(context);
    }

    public Infotity(Context context, AttributeSet attrs) {
        super(context, attrs);
        init(context);
    }

    public Infotity(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        init(context);
    }

    void init(Context context){
        LayoutInflater.from(context).inflate(R.layout.entity_style,this,true);
        tity_name = (TextView)findViewById(R.id.entity_name);
        tity_phon = (TextView)findViewById(R.id.entity_phon);
        tity_adr = (TextView)findViewById(R.id.entity_adr);
        tity_Location = (TextView)findViewById(R.id.entity_Location);

    }

    public void setTity_name( String name) {
        this.tity_name.setText(name);
    }

    public void setTity_phon(String phon) {
        this.tity_phon.setText(phon);
    }

    public void setTity_adr(String tity_adr) {
        this.tity_adr.setText(tity_adr);
    }

    public void setTity_Location(LatLng latLng) {

        this.tity_Location.setText(Double.toString(latLng.longitude)+","+Double.toString(latLng.latitude));
    }



}
