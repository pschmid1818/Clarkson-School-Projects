package edu.clarkson.ee408;


import android.media.MediaPlayer;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

import edu.clarkson.ee408.R;

public class MainActivity extends AppCompatActivity {

    private MediaPlayer mp;
    private TextView display;
    private TextView error;
    private Button b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, bPlus, bMinus, bMult, bDiv, bClear, bEq , bOpen , bClose;

    private static boolean op1Set=false;
    private static int operand1=0;
    private static int op=-1; // -1: no op; 0: +; 1:-;2:*;3:/
    private static boolean calc=false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        b0 = (Button)findViewById(R.id.button0);
        b1 = (Button)findViewById(R.id.button1);
        b2 = (Button)findViewById(R.id.button2);
        b3 = (Button)findViewById(R.id.button3);
        b4 = (Button)findViewById(R.id.button4);
        b5 = (Button)findViewById(R.id.button5);
        b6 = (Button)findViewById(R.id.button6);
        b7 = (Button)findViewById(R.id.button7);
        b8 = (Button)findViewById(R.id.button8);
        b9 = (Button)findViewById(R.id.button9);
        bPlus = (Button)findViewById(R.id.buttonPlus);
        bMinus = (Button)findViewById(R.id.buttonMinus);
        bMult = (Button)findViewById(R.id.buttonMult);
        bDiv = (Button)findViewById(R.id.buttonDiv);
        bClear = (Button)findViewById(R.id.buttonClear);
        bEq = (Button)findViewById(R.id.buttonEq);
        bOpen = (Button)findViewById(R.id.buttonOpen);
        bClose = (Button)findViewById(R.id.buttonClose);

        display = (TextView) findViewById(R.id.display);
        error = (TextView) findViewById(R.id.error);

        OnClickListener lNum = new OnClickListener() {
        @Override
        public void onClick(View v) {
            Button b = (Button)v;
            if (b == b0 && display.getText().toString().equals("0"))
            {
                display.setText("");
            }
            if (calc){
                calc=false;
                display.setText("");
            }

            String text;
            text = display.getText().toString()+b.getText().toString();
            display.setText(text);
        }
    };
        OnClickListener lDo= new OnClickListener(){
            @Override
            public void onClick(View view) {
                try {
                    int output = ParserII.DO(display.getText().toString());
                    display.setText(Integer.toString(output));
                    if(output==69)
                    {
                        error.setText("Nice");
                    }
                } catch (Exception e) {
                    // TODO Auto-generated catch block
                    error.setText(e.toString());
                }
            }
        };
        OnClickListener lCl = new OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                display.setText("");
                error.setText("");
            }
        };

        b0.setOnClickListener(lNum);
        b1.setOnClickListener(lNum);
        b2.setOnClickListener(lNum);
        b3.setOnClickListener(lNum);
        b4.setOnClickListener(lNum);
        b5.setOnClickListener(lNum);
        b6.setOnClickListener(lNum);
        b7.setOnClickListener(lNum);
        b8.setOnClickListener(lNum);
        b9.setOnClickListener(lNum);
        bOpen.setOnClickListener(lNum);
        bClose.setOnClickListener(lNum);
        bPlus.setOnClickListener(lNum);
        bMinus.setOnClickListener(lNum);
        bMult.setOnClickListener(lNum);
        bDiv.setOnClickListener(lNum);

        bEq.setOnClickListener(lDo);

        bClear.setOnClickListener(lCl);

        // starts the music
        mp = MediaPlayer.create(this, R.raw.creepy_noise);
        mp.start();

    }
}
