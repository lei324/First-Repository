package com.xxxx.game;

import java.awt.*;

public interface BaseData {
    Font topicFont=new Font("微软雅黑",Font.BOLD,50);
    Font scoreFont=new Font("微软雅黑",Font.BOLD,28);
    Font normalFont=new Font("宋体",Font.PLAIN,20);
    Font font1=new Font("宋体",Font.BOLD,46);
    Font font2=new Font("宋体",Font.BOLD,40);
    Font font3=new Font("宋体",Font.BOLD,34);
    Font font4=new Font("宋体", Font.BOLD,28);
    Font font5=new Font("宋体",Font.BOLD,22);
    int normalFontData=20;
    int topicFontData=30;
    void init();
    void showView();
}
