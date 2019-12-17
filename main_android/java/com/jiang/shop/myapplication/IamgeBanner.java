package com.jiang.shop.myapplication;

import android.content.Context;
import android.support.annotation.AttrRes;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.view.ViewPager;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.FrameLayout;

/**compile 'com.youth.banner:banner:1.4.10'
 * Created by Administrator on 2018/3/5.
 */

public class IamgeBanner extends FrameLayout {
    private Context context;
    public ViewPager viewPager;
    public IamgeBanner(@NonNull Context context) {
        super(context,null);
    }

    public IamgeBanner(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs,0);
    }

    public IamgeBanner(@NonNull Context context, @Nullable AttributeSet attrs, @AttrRes int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        initView(context,attrs);
    }
    private void initView(Context context, AttributeSet attrs){
        View view = LayoutInflater.from(context).inflate(R.layout.iamgebanner_layout, this, true);
        viewPager = view.findViewById(R.id.banner_image);
    }
}
