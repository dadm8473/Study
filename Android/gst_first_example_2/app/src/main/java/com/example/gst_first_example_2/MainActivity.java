package com.example.gst_first_example_2;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;
import android.widget.Toast;

import org.freedesktop.gstreamer.GStreamer;

public class MainActivity extends AppCompatActivity {
    private native String nativeGetGStreamerInfo();
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        try {
            GStreamer.init(this);
        } catch (Exception e) {
            Toast.makeText(this, e.getMessage(), Toast.LENGTH_LONG).show();
            finish();
            return;
        }
        setContentView(R.layout.activity_main);
        TextView tv = (TextView)findViewById(R.id.textview_info);
        tv.setText("Welcome to " + nativeGetGStreamerInfo() + " !");
    }
    static {
        System.loadLibrary("gstreamer_android");
        System.loadLibrary("tutorial-1");
    }
}