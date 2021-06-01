package com.jblearning.tipcalculatorv3;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import com.jblearning.tipcalculatorv1.TipCalculator;

import java.text.NumberFormat;

public class MainActivity extends AppCompatActivity
{
  private TipCalculator tipCalc;
  public NumberFormat money=NumberFormat.getCurrencyInstance( );

  protected void onCreate(Bundle savedInsatnceState)
  {
    super.onCreate(savedInsatnceState);
    tipCalc=new TipCalculator(0.17f, 100.0f);
    setContentView(R.layout.activity_main);
  }








  @Override
  protected void onCreate(Bundle savedInstanceState)
  {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);
  }
}
