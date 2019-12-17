package com.jiang.shop.myapplication;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;

import com.squareup.picasso.Picasso;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Administrator on 2018/2/22.
 */

public class MainList extends BaseAdapter {
    private Context mContext;
    private ListView listView;
    private List<View> listmains = new ArrayList<>();

    public MainList(Context mContext) {
        this.mContext = mContext;
    }

    public void addListView(String[] url, String[] text){
        View view = LayoutInflater.from(mContext).inflate(R.layout.mian_list,null);
        ImageView img1 = (ImageView)view.findViewById(R.id.imageView1);
        ImageView img2 = (ImageView)view.findViewById(R.id.imageView2);
        ImageView img3 = (ImageView)view.findViewById(R.id.imageView3);
        Picasso.with(mContext).load(url[0]).resize(200,200).into(img1);
        Picasso.with(mContext).load(url[1]).resize(200,200).into(img2);
        Picasso.with(mContext).load(url[2]).resize(200,200).into(img3);
        TextView txt1 = (TextView)view.findViewById(R.id.editText1);
        TextView txt2 = (TextView)view.findViewById(R.id.editText2);
        TextView txt3 = (TextView)view.findViewById(R.id.editText3);
        txt1.setText(text[0]);
        txt2.setText(text[1]);
        txt3.setText(text[2]);
        listmains.add(view);
    }

    public void setAdaper(ListView listView){
        this.listView = listView;
        this.listView.setAdapter(this);
    }
    @Override
    public int getCount() {
        return listmains.size();
    }

    @Override
    public Object getItem(int position) {
        return listmains.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        return listmains.get(position);
    }


}
