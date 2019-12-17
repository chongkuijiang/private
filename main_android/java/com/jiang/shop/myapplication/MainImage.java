package com.jiang.shop.myapplication;

import android.content.Context;
import android.support.v4.view.PagerAdapter;
import android.support.v4.view.ViewPager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import com.squareup.picasso.Picasso;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Administrator on 2018/2/12.
 */

public class MainImage extends PagerAdapter {
    private Context mContext;
    private List<String> mUrl;
    private IamgeBanner mIamgeBanner;
    private List<ImageView> mImage = new ArrayList<>();
    private ImageLoader imageLoader;
    public interface ImageLoader{
        void displayImage(Context context, String path, ImageView imageView);
    }
    //product  details
    public MainImage(Context context, List<String> url,ImageLoader imageLoader) {
        this.mContext = context;
        this.mUrl = url;
        this.imageLoader = imageLoader;
        for(int i=0;i<mUrl.size();i++){
            ImageView image = new ImageView(mContext);
            image.setScaleType(ImageView.ScaleType.FIT_CENTER);
            this.imageLoader.displayImage(context,mUrl.get(i),image);
          //  Picasso.with(mContext).load(mUrl[i]).into(image);
            mImage.add(image);
        }
    }

    public void setView(IamgeBanner iamgeBanner) {
        this.mIamgeBanner = iamgeBanner;
        this.mIamgeBanner.viewPager.setAdapter(this);
    }

    @Override
    public Object instantiateItem(ViewGroup container, int position) {
        container.addView(mImage.get(position));
        return mImage.get(position);
    }

    @Override
    public void destroyItem(ViewGroup container, int position, Object object) {
        container.removeView(mImage.get(position));
    }

    @Override
    public int getCount() {
        return (mImage!=null)? mImage.size():0;
    }

    @Override
    public boolean isViewFromObject(View view, Object object) {
        return (view == object);
    }
}
