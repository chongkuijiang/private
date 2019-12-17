package com.jiang.shop.myapplication;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.view.ViewPager;
import android.support.v7.app.AppCompatActivity;

/**
 * Created by Administrator on 2018/2/13.
 */

public class NextActiviy extends AppCompatActivity {
    private AppStart app;
    private ViewPager viewPager;
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.nextlayout);
        viewPager = (ViewPager)findViewById(R.id.mian_image);
        app = AppStart.getApp();

    }
}
