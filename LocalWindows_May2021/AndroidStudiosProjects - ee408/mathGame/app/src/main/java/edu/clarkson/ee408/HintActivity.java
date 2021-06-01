package edu.clarkson.ee408;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.TextView;
import android.widget.ImageView;

public class HintActivity extends AppCompatActivity {

    private TextView optrDisplay;
    private ImageView op1Display, op2Display, ansDisplay1, ansDisplay2;
    private int operand1, operand2, result, min = 1, max = 4, randint;
    private char operator;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_hint);

        final EquationGenerator eqGen = new EquationGenerator();

        operand1 = eqGen.getOp1();  //gets operand 1
        operand2 = eqGen.getOp2();  //gets operand 2
        operator = eqGen.getOperator(); //gets operator
        result = eqGen.getRes();    //get result

        optrDisplay = (TextView) findViewById(R.id.operator); //sets operator on screen
        op1Display = (ImageView) findViewById(R.id.imgOp1); //sets operand1 image
        op2Display = (ImageView) findViewById(R.id.imgOp2); //sets operand2 image
        ansDisplay1 = (ImageView) findViewById(R.id.imgAns1); //sets answer image (if ans <= 9)
        ansDisplay2 = (ImageView) findViewById(R.id.imgAns2); //sets another answer image (if ans > 9)

        randint = (int) (Math.random() * (max - min + 1)) + min; //generate random int b/t 1-4 for fruit

        if (operator == '+'){
            optrDisplay.setText("+");
        }
        else if (operator == '-') {
            optrDisplay.setText("-");
        }
        else if (operator == '*') {
            optrDisplay.setText("*");
        }
        else if (operator == '/') {
            optrDisplay.setText("/");
        }
        else {
            optrDisplay.setText("??");
        }

        switch(randint){ //checks for randint value
            case 1:
                switch(operand1){ //checks operand 1 value
                    case 1:
                        op1Display.setImageResource(R.drawable.apple1);
                        break;
                    case 2:
                        op1Display.setImageResource(R.drawable.apple2);
                        break;
                    case 3:
                        op1Display.setImageResource(R.drawable.apple3);
                        break;
                    case 4:
                        op1Display.setImageResource(R.drawable.apple4);
                        break;
                    case 5:
                        op1Display.setImageResource(R.drawable.apple5);
                        break;
                    case 6:
                        op1Display.setImageResource(R.drawable.apple6);
                        break;
                    case 7:
                        op1Display.setImageResource(R.drawable.apple7);
                        break;
                    case 8:
                        op1Display.setImageResource(R.drawable.apple8);
                        break;
                    case 9:
                        op1Display.setImageResource(R.drawable.apple9);
                        break;
                }
                switch(operand2){ //checks operand 2 value
                    case 1:
                        op2Display.setImageResource(R.drawable.apple1);
                        break;
                    case 2:
                        op2Display.setImageResource(R.drawable.apple2);
                        break;
                    case 3:
                        op2Display.setImageResource(R.drawable.apple3);
                        break;
                    case 4:
                        op2Display.setImageResource(R.drawable.apple4);
                        break;
                    case 5:
                        op2Display.setImageResource(R.drawable.apple5);
                        break;
                    case 6:
                        op2Display.setImageResource(R.drawable.apple6);
                        break;
                    case 7:
                        op2Display.setImageResource(R.drawable.apple7);
                        break;
                    case 8:
                        op2Display.setImageResource(R.drawable.apple8);
                        break;
                    case 9:
                        op2Display.setImageResource(R.drawable.apple9);
                        break;
                }
                switch(result){ //checks result value
                    case 1:
                        ansDisplay1.setImageResource(R.drawable.apple1);
                        break;
                    case 2:
                        ansDisplay1.setImageResource(R.drawable.apple2);
                        break;
                    case 3:
                        ansDisplay1.setImageResource(R.drawable.apple3);
                        break;
                    case 4:
                        ansDisplay1.setImageResource(R.drawable.apple4);
                        break;
                    case 5:
                        ansDisplay1.setImageResource(R.drawable.apple5);
                        break;
                    case 6:
                        ansDisplay1.setImageResource(R.drawable.apple6);
                        break;
                    case 7:
                        ansDisplay1.setImageResource(R.drawable.apple7);
                        break;
                    case 8:
                        ansDisplay1.setImageResource(R.drawable.apple8);
                        break;
                    case 9:
                        ansDisplay1.setImageResource(R.drawable.apple9);
                        break;
                    case 10:
                        ansDisplay1.setImageResource(R.drawable.apple9);
                        ansDisplay2.setImageResource(R.drawable.apple1);
                        break;
                    case 11:
                        ansDisplay1.setImageResource(R.drawable.apple9);
                        ansDisplay2.setImageResource(R.drawable.apple2);
                        break;
                    case 12:
                        ansDisplay1.setImageResource(R.drawable.apple9);
                        ansDisplay2.setImageResource(R.drawable.apple3);
                        break;
                    case 13:
                        ansDisplay1.setImageResource(R.drawable.apple9);
                        ansDisplay2.setImageResource(R.drawable.apple4);
                        break;
                    case 14:
                        ansDisplay1.setImageResource(R.drawable.apple9);
                        ansDisplay2.setImageResource(R.drawable.apple5);
                        break;
                    case 15:
                        ansDisplay1.setImageResource(R.drawable.apple9);
                        ansDisplay2.setImageResource(R.drawable.apple6);
                        break;
                    case 16:
                        ansDisplay1.setImageResource(R.drawable.apple9);
                        ansDisplay2.setImageResource(R.drawable.apple7);
                        break;
                    case 17:
                        ansDisplay1.setImageResource(R.drawable.apple9);
                        ansDisplay2.setImageResource(R.drawable.apple8);
                        break;
                    case 18:
                        ansDisplay1.setImageResource(R.drawable.apple9);
                        ansDisplay2.setImageResource(R.drawable.apple9);
                        break;
                }
                break;
            case 2:
                switch(operand1){
                    case 1:
                        op1Display.setImageResource(R.drawable.banana1);
                        break;
                    case 2:
                        op1Display.setImageResource(R.drawable.banana2);
                        break;
                    case 3:
                        op1Display.setImageResource(R.drawable.banana3);
                        break;
                    case 4:
                        op1Display.setImageResource(R.drawable.banana4);
                        break;
                    case 5:
                        op1Display.setImageResource(R.drawable.banana5);
                        break;
                    case 6:
                        op1Display.setImageResource(R.drawable.banana6);
                        break;
                    case 7:
                        op1Display.setImageResource(R.drawable.banana7);
                        break;
                    case 8:
                        op1Display.setImageResource(R.drawable.banana8);
                        break;
                    case 9:
                        op1Display.setImageResource(R.drawable.banana9);
                        break;
                }
                switch(operand2){
                    case 1:
                        op2Display.setImageResource(R.drawable.banana1);
                        break;
                    case 2:
                        op2Display.setImageResource(R.drawable.banana2);
                        break;
                    case 3:
                        op2Display.setImageResource(R.drawable.banana3);
                        break;
                    case 4:
                        op2Display.setImageResource(R.drawable.banana4);
                        break;
                    case 5:
                        op2Display.setImageResource(R.drawable.banana5);
                        break;
                    case 6:
                        op2Display.setImageResource(R.drawable.banana6);
                        break;
                    case 7:
                        op2Display.setImageResource(R.drawable.banana7);
                        break;
                    case 8:
                        op2Display.setImageResource(R.drawable.banana8);
                        break;
                    case 9:
                        op2Display.setImageResource(R.drawable.banana9);
                        break;
                }
                switch(result){
                    case 1:
                        ansDisplay1.setImageResource(R.drawable.banana1);
                        break;
                    case 2:
                        ansDisplay1.setImageResource(R.drawable.banana2);
                        break;
                    case 3:
                        ansDisplay1.setImageResource(R.drawable.banana3);
                        break;
                    case 4:
                        ansDisplay1.setImageResource(R.drawable.banana4);
                        break;
                    case 5:
                        ansDisplay1.setImageResource(R.drawable.banana5);
                        break;
                    case 6:
                        ansDisplay1.setImageResource(R.drawable.banana6);
                        break;
                    case 7:
                        ansDisplay1.setImageResource(R.drawable.banana7);
                        break;
                    case 8:
                        ansDisplay1.setImageResource(R.drawable.banana8);
                        break;
                    case 9:
                        ansDisplay1.setImageResource(R.drawable.banana9);
                        break;
                    case 10:
                        ansDisplay1.setImageResource(R.drawable.banana9);
                        ansDisplay2.setImageResource(R.drawable.banana1);
                        break;
                    case 11:
                        ansDisplay1.setImageResource(R.drawable.banana9);
                        ansDisplay2.setImageResource(R.drawable.banana2);
                        break;
                    case 12:
                        ansDisplay1.setImageResource(R.drawable.banana9);
                        ansDisplay2.setImageResource(R.drawable.banana3);
                        break;
                    case 13:
                        ansDisplay1.setImageResource(R.drawable.banana9);
                        ansDisplay2.setImageResource(R.drawable.banana4);
                        break;
                    case 14:
                        ansDisplay1.setImageResource(R.drawable.banana9);
                        ansDisplay2.setImageResource(R.drawable.banana5);
                        break;
                    case 15:
                        ansDisplay1.setImageResource(R.drawable.banana9);
                        ansDisplay2.setImageResource(R.drawable.banana6);
                        break;
                    case 16:
                        ansDisplay1.setImageResource(R.drawable.banana9);
                        ansDisplay2.setImageResource(R.drawable.banana7);
                        break;
                    case 17:
                        ansDisplay1.setImageResource(R.drawable.banana9);
                        ansDisplay2.setImageResource(R.drawable.banana8);
                        break;
                    case 18:
                        ansDisplay1.setImageResource(R.drawable.banana9);
                        ansDisplay2.setImageResource(R.drawable.banana9);
                        break;
                }
                break;
            case 3:
                switch(operand1){
                    case 1:
                        op1Display.setImageResource(R.drawable.cherries1);
                        break;
                    case 2:
                        op1Display.setImageResource(R.drawable.cherries2);
                        break;
                    case 3:
                        op1Display.setImageResource(R.drawable.cherries3);
                        break;
                    case 4:
                        op1Display.setImageResource(R.drawable.cherries4);
                        break;
                    case 5:
                        op1Display.setImageResource(R.drawable.cherries5);
                        break;
                    case 6:
                        op1Display.setImageResource(R.drawable.cherries6);
                        break;
                    case 7:
                        op1Display.setImageResource(R.drawable.cherries7);
                        break;
                    case 8:
                        op1Display.setImageResource(R.drawable.cherries8);
                        break;
                    case 9:
                        op1Display.setImageResource(R.drawable.cherries9);
                        break;
                }
                switch(operand2){
                    case 1:
                        op2Display.setImageResource(R.drawable.cherries1);
                        break;
                    case 2:
                        op2Display.setImageResource(R.drawable.cherries2);
                        break;
                    case 3:
                        op2Display.setImageResource(R.drawable.cherries3);
                        break;
                    case 4:
                        op2Display.setImageResource(R.drawable.cherries4);
                        break;
                    case 5:
                        op2Display.setImageResource(R.drawable.cherries5);
                        break;
                    case 6:
                        op2Display.setImageResource(R.drawable.cherries6);
                        break;
                    case 7:
                        op2Display.setImageResource(R.drawable.cherries7);
                        break;
                    case 8:
                        op2Display.setImageResource(R.drawable.cherries8);
                        break;
                    case 9:
                        op2Display.setImageResource(R.drawable.cherries9);
                        break;
                }
                switch(result){
                    case 1:
                        ansDisplay1.setImageResource(R.drawable.cherries1);
                        break;
                    case 2:
                        ansDisplay1.setImageResource(R.drawable.cherries2);
                        break;
                    case 3:
                        ansDisplay1.setImageResource(R.drawable.cherries3);
                        break;
                    case 4:
                        ansDisplay1.setImageResource(R.drawable.cherries4);
                        break;
                    case 5:
                        ansDisplay1.setImageResource(R.drawable.cherries5);
                        break;
                    case 6:
                        ansDisplay1.setImageResource(R.drawable.cherries6);
                        break;
                    case 7:
                        ansDisplay1.setImageResource(R.drawable.cherries7);
                        break;
                    case 8:
                        ansDisplay1.setImageResource(R.drawable.cherries8);
                        break;
                    case 9:
                        ansDisplay1.setImageResource(R.drawable.cherries9);
                        break;
                    case 10:
                        ansDisplay1.setImageResource(R.drawable.cherries9);
                        ansDisplay2.setImageResource(R.drawable.cherries1);
                        break;
                    case 11:
                        ansDisplay1.setImageResource(R.drawable.cherries9);
                        ansDisplay2.setImageResource(R.drawable.cherries2);
                        break;
                    case 12:
                        ansDisplay1.setImageResource(R.drawable.cherries9);
                        ansDisplay2.setImageResource(R.drawable.cherries3);
                        break;
                    case 13:
                        ansDisplay1.setImageResource(R.drawable.cherries9);
                        ansDisplay2.setImageResource(R.drawable.cherries4);
                        break;
                    case 14:
                        ansDisplay1.setImageResource(R.drawable.cherries9);
                        ansDisplay2.setImageResource(R.drawable.cherries5);
                        break;
                    case 15:
                        ansDisplay1.setImageResource(R.drawable.cherries9);
                        ansDisplay2.setImageResource(R.drawable.cherries6);
                        break;
                    case 16:
                        ansDisplay1.setImageResource(R.drawable.cherries9);
                        ansDisplay2.setImageResource(R.drawable.cherries7);
                        break;
                    case 17:
                        ansDisplay1.setImageResource(R.drawable.cherries9);
                        ansDisplay2.setImageResource(R.drawable.cherries8);
                        break;
                    case 18:
                        ansDisplay1.setImageResource(R.drawable.cherries9);
                        ansDisplay2.setImageResource(R.drawable.cherries9);
                        break;
                }
                break;
            case 4:
                switch(operand1){
                    case 1:
                        op1Display.setImageResource(R.drawable.orange1);
                        break;
                    case 2:
                        op1Display.setImageResource(R.drawable.orange2);
                        break;
                    case 3:
                        op1Display.setImageResource(R.drawable.orange3);
                        break;
                    case 4:
                        op1Display.setImageResource(R.drawable.orange4);
                        break;
                    case 5:
                        op1Display.setImageResource(R.drawable.orange5);
                        break;
                    case 6:
                        op1Display.setImageResource(R.drawable.orange6);
                        break;
                    case 7:
                        op1Display.setImageResource(R.drawable.orange7);
                        break;
                    case 8:
                        op1Display.setImageResource(R.drawable.orange8);
                        break;
                    case 9:
                        op1Display.setImageResource(R.drawable.orange9);
                        break;
                }
                switch(operand2){
                    case 1:
                        op2Display.setImageResource(R.drawable.orange1);
                        break;
                    case 2:
                        op2Display.setImageResource(R.drawable.orange2);
                        break;
                    case 3:
                        op2Display.setImageResource(R.drawable.orange3);
                        break;
                    case 4:
                        op2Display.setImageResource(R.drawable.orange4);
                        break;
                    case 5:
                        op2Display.setImageResource(R.drawable.orange5);
                        break;
                    case 6:
                        op2Display.setImageResource(R.drawable.orange6);
                        break;
                    case 7:
                        op2Display.setImageResource(R.drawable.orange7);
                        break;
                    case 8:
                        op2Display.setImageResource(R.drawable.orange8);
                        break;
                    case 9:
                        op2Display.setImageResource(R.drawable.orange9);
                        break;
                }
                switch(result){
                    case 1:
                        ansDisplay1.setImageResource(R.drawable.orange1);
                        break;
                    case 2:
                        ansDisplay1.setImageResource(R.drawable.orange2);
                        break;
                    case 3:
                        ansDisplay1.setImageResource(R.drawable.orange3);
                        break;
                    case 4:
                        ansDisplay1.setImageResource(R.drawable.orange4);
                        break;
                    case 5:
                        ansDisplay1.setImageResource(R.drawable.orange5);
                        break;
                    case 6:
                        ansDisplay1.setImageResource(R.drawable.orange6);
                        break;
                    case 7:
                        ansDisplay1.setImageResource(R.drawable.orange7);
                        break;
                    case 8:
                        ansDisplay1.setImageResource(R.drawable.orange8);
                        break;
                    case 9:
                        ansDisplay1.setImageResource(R.drawable.orange9);
                        break;
                    case 10:
                        ansDisplay1.setImageResource(R.drawable.orange9);
                        ansDisplay2.setImageResource(R.drawable.orange1);
                        break;
                    case 11:
                        ansDisplay1.setImageResource(R.drawable.orange9);
                        ansDisplay2.setImageResource(R.drawable.orange2);
                        break;
                    case 12:
                        ansDisplay1.setImageResource(R.drawable.orange9);
                        ansDisplay2.setImageResource(R.drawable.orange3);
                        break;
                    case 13:
                        ansDisplay1.setImageResource(R.drawable.orange9);
                        ansDisplay2.setImageResource(R.drawable.orange4);
                        break;
                    case 14:
                        ansDisplay1.setImageResource(R.drawable.orange9);
                        ansDisplay2.setImageResource(R.drawable.orange5);
                        break;
                    case 15:
                        ansDisplay1.setImageResource(R.drawable.orange9);
                        ansDisplay2.setImageResource(R.drawable.orange6);
                        break;
                    case 16:
                        ansDisplay1.setImageResource(R.drawable.orange9);
                        ansDisplay2.setImageResource(R.drawable.orange7);
                        break;
                    case 17:
                        ansDisplay1.setImageResource(R.drawable.orange9);
                        ansDisplay2.setImageResource(R.drawable.orange8);
                        break;
                    case 18:
                        ansDisplay1.setImageResource(R.drawable.orange9);
                        ansDisplay2.setImageResource(R.drawable.orange9);
                        break;
                }
                break;
        }

    }
}
