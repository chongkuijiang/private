package com.jiang.shop.myapplication;

import android.app.Application;

/**
 * Created by Administrator on 2018/2/13.
 */

public class AppStart extends Application {
    private MainImage mainImage;
    private MainList mainList;
    private static AppStart app;
    @Override
    public void onCreate() {
        super.onCreate();
        app = this;
    }

    public static AppStart getApp() {
        return app;
    }

    public MainImage getMainImage() {
        return mainImage;
    }

    public void setMainImage(MainImage mainImage) {
        this.mainImage = mainImage;
    }

    public MainList getMainList() {
        return mainList;
    }

    public void setMainList(MainList mainList) {
        this.mainList = mainList;
    }
}
