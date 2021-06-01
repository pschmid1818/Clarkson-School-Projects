package edu.clarkson.ee408;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;


public class MainActivity extends AppCompatActivity {

    private TextView eqDisplay, ansDisplay, botDisplay, scoreDisplay, textDisplay;
    private Button bPlus, bMinus, bMult, bDiv,b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, nextQuestion, enter, clear;
    private int score = 0;

    private int operand1, operand2, result, blank, temp;
    private char operator;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //button set up
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
        bPlus = (Button)findViewById(R.id.buttonPlus);  //sets plus button
        bMinus = (Button)findViewById(R.id.buttonMinus);    //sets minus button
        bMult = (Button)findViewById(R.id.buttonMult);  //sets multiply button
        bDiv = (Button)findViewById(R.id.buttonDiv);    //sets division button
        nextQuestion = (Button)findViewById(R.id.next_button);
        enter = (Button)findViewById(R.id.buttonEnter);
        clear = (Button)findViewById(R.id.buttonclr);


        //display set ups
        eqDisplay = (TextView) findViewById(R.id.eqDisplay);
        ansDisplay = (TextView) findViewById(R.id.ansDisplay);
        botDisplay = (TextView) findViewById(R.id.bottomDisplay);
        textDisplay = (TextView) findViewById(R.id.textDisplay);
        scoreDisplay = (TextView) findViewById(R.id.score_display);

        String equation;
        final EquationGenerator eqGen = new EquationGenerator();

        eqGen.generate(score);

        operand1 = eqGen.getOp1();  //gets operand 1
        operand2 = eqGen.getOp2();  //gets operand 2
        operator = eqGen.getOperator(); //gets operator
        result = eqGen.getRes();    //get result
        blank = eqGen.getBlankLoc(); //get blank location
        equation = eqGen.getString(); //get equation

        //display equation with specified blank
        eqDisplay.setText(equation);
        textDisplay.setText("Answer");

        //if operator blank show operator buttons and hide number buttons otherwise
        //hide operator buttons and show number buttons
        if(blank != 2)
        {
            bPlus.setVisibility(View.INVISIBLE);
            bMinus.setVisibility(View.INVISIBLE);
            bMult.setVisibility(View.INVISIBLE);
            bDiv.setVisibility(View.INVISIBLE);

            b0.setVisibility(View.VISIBLE);
            b1.setVisibility(View.VISIBLE);
            b2.setVisibility(View.VISIBLE);
            b3.setVisibility(View.VISIBLE);
            b4.setVisibility(View.VISIBLE);
            b5.setVisibility(View.VISIBLE);
            b6.setVisibility(View.VISIBLE);
            b7.setVisibility(View.VISIBLE);
            b8.setVisibility(View.VISIBLE);
            b9.setVisibility(View.VISIBLE);
            clear.setVisibility(View.VISIBLE);
            enter.setVisibility(View.VISIBLE);

        }
        else{
            bPlus.setVisibility(View.VISIBLE);
            bMinus.setVisibility(View.VISIBLE);
            bMult.setVisibility(View.VISIBLE);
            bDiv.setVisibility(View.VISIBLE);

            b0.setVisibility(View.INVISIBLE);
            b1.setVisibility(View.INVISIBLE);
            b2.setVisibility(View.INVISIBLE);
            b3.setVisibility(View.INVISIBLE);
            b4.setVisibility(View.INVISIBLE);
            b5.setVisibility(View.INVISIBLE);
            b6.setVisibility(View.INVISIBLE);
            b7.setVisibility(View.INVISIBLE);
            b8.setVisibility(View.INVISIBLE);
            b9.setVisibility(View.INVISIBLE);
            clear.setVisibility(View.INVISIBLE);
            enter.setVisibility(View.INVISIBLE);
        }

        View.OnClickListener plusListen = new View.OnClickListener() {  //plus button listener
            public void onClick(View v)
            {
                if(operator == '+') {
                    botDisplay.setText("Correct");     //if + is correct display correct
                    score += 2;
                    scoreDisplay.setText(Integer.toString(score));
                }
                else{
                    botDisplay.setText("Wrong");       //if incorrect display wrong
                }

                bPlus.setEnabled(false);
                bMinus.setEnabled(false);
                bMult.setEnabled(false);
                bDiv.setEnabled(false);
            }

        };

        View.OnClickListener minusListen = new View.OnClickListener() { //minus button listener
            public void onClick(View v)
            {
                if(operator == '-') {
                    botDisplay.setText("Correct"); //if - is correct display correct
                    score += 2;
                    scoreDisplay.setText(Integer.toString(score));
                }
                else{
                    botDisplay.setText("Wrong");   //if incorrect display wrong
                }

                bPlus.setEnabled(false);
                bMinus.setEnabled(false);
                bMult.setEnabled(false);
                bDiv.setEnabled(false);
            }

        };

        View.OnClickListener multListen = new View.OnClickListener() {  //multiply button listener
            public void onClick(View v)
            {
                if(operator == '*') {
                    botDisplay.setText("Correct"); //if * is correct display correct
                    score += 2;
                    scoreDisplay.setText(Integer.toString(score));
                }
                else{
                    botDisplay.setText("Wrong");   //if incorrect display wrong
                }

                bPlus.setEnabled(false);
                bMinus.setEnabled(false);
                bMult.setEnabled(false);
                bDiv.setEnabled(false);
            }
        };

        View.OnClickListener divListen = new View.OnClickListener() {
            public void onClick(View v)
            {
                if(operator == '/') {
                    botDisplay.setText("Correct"); //if / is correct display correct
                    score += 2;
                    scoreDisplay.setText(Integer.toString(score));
                }
                else{
                    botDisplay.setText("Wrong");   //if incorrect display wrong
                }

                bPlus.setEnabled(false);
                bMinus.setEnabled(false);
                bMult.setEnabled(false);
                bDiv.setEnabled(false);
            }
        };

        View.OnClickListener nextQ = new View.OnClickListener() {
            public void onClick(View v) {

                // re-enable buttons when next question is clicked
                bPlus.setEnabled(true);
                bMinus.setEnabled(true);
                bMult.setEnabled(true);
                bDiv.setEnabled(true);
                b0.setEnabled(true);
                b1.setEnabled(true);
                b2.setEnabled(true);
                b3.setEnabled(true);
                b4.setEnabled(true);
                b5.setEnabled(true);
                b6.setEnabled(true);
                b7.setEnabled(true);
                b8.setEnabled(true);
                b9.setEnabled(true);
                clear.setEnabled(true);
                enter.setEnabled(true);

                eqGen.generate(score);
                botDisplay.setText("");
                textDisplay.setText("Answer");
                eqDisplay.setText(eqGen.getString());
                ansDisplay.setText("");
                operand1 = eqGen.getOp1();  //gets operand 1
                operand2 = eqGen.getOp2();  //gets operand 2
                operator = eqGen.getOperator(); //gets operator
                result = eqGen.getRes();    //get result
                blank = eqGen.getBlankLoc();

                //if the operator is blank hide number buttons and show operator buttons
                if (blank != 2) {
                    bPlus.setVisibility(View.INVISIBLE);
                    bMinus.setVisibility(View.INVISIBLE);
                    bMult.setVisibility(View.INVISIBLE);
                    bDiv.setVisibility(View.INVISIBLE);

                    b0.setVisibility(View.VISIBLE);
                    b1.setVisibility(View.VISIBLE);
                    b2.setVisibility(View.VISIBLE);
                    b3.setVisibility(View.VISIBLE);
                    b4.setVisibility(View.VISIBLE);
                    b5.setVisibility(View.VISIBLE);
                    b6.setVisibility(View.VISIBLE);
                    b7.setVisibility(View.VISIBLE);
                    b8.setVisibility(View.VISIBLE);
                    b9.setVisibility(View.VISIBLE);
                    clear.setVisibility(View.VISIBLE);
                    enter.setVisibility(View.VISIBLE);

                } else { //otherwise hide operator buttons and show number buttons
                    bPlus.setVisibility(View.VISIBLE);
                    bMinus.setVisibility(View.VISIBLE);
                    bMult.setVisibility(View.VISIBLE);
                    bDiv.setVisibility(View.VISIBLE);

                    b0.setVisibility(View.INVISIBLE);
                    b1.setVisibility(View.INVISIBLE);
                    b2.setVisibility(View.INVISIBLE);
                    b3.setVisibility(View.INVISIBLE);
                    b4.setVisibility(View.INVISIBLE);
                    b5.setVisibility(View.INVISIBLE);
                    b6.setVisibility(View.INVISIBLE);
                    b7.setVisibility(View.INVISIBLE);
                    b8.setVisibility(View.INVISIBLE);
                    b9.setVisibility(View.INVISIBLE);
                    clear.setVisibility(View.INVISIBLE);
                    enter.setVisibility(View.INVISIBLE);
                }
            }
        };

        View.OnClickListener numListen = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Button b = (Button) v;

                String text;
                text = ansDisplay.getText().toString()+b.getText().toString();

                ansDisplay.setText(text);
            }
        };

        View.OnClickListener enterListen = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String answer;
                answer = ansDisplay.getText().toString();

                if (blank == 1) {
                    if (operand1 == Integer.valueOf(answer)) {
                        botDisplay.setText("Correct");
                        score += 2;
                        scoreDisplay.setText(Integer.toString(score));
                    } else {
                        botDisplay.setText("Wrong");
                        ansDisplay.setText("");
                    }
                }

                if (blank == 3) {
                    if (operand2 == Integer.valueOf(answer)) {
                        botDisplay.setText("Correct");
                        score += 2;
                        scoreDisplay.setText(Integer.toString(score));
                    } else {
                        botDisplay.setText("Wrong");
                        ansDisplay.setText("");
                    }
                }

                if(blank == 4)
                {
                    if(operator == '/')
                    {
                        if(temp == 0)  // integer case
                        {
                            if (result == Integer.valueOf(answer)) {
                                botDisplay.setText("Correct");
                                textDisplay.setText("Remainder:");
                                ansDisplay.setText("");
                                score += 2;                                       // fix this later
                                scoreDisplay.setText(Integer.toString(score));
                                temp++;
                            }
                            else {
                                botDisplay.setText("Wrong");
                                ansDisplay.setText("");
                                temp = 0;
                            }
                        }
                        else{         // remainder case
                            if (eqGen.getRemain() == Integer.valueOf(answer)) {
                                botDisplay.setText("Correct");
                                textDisplay.setText("Answer:");
                                ansDisplay.setText("");
                                score += 2;                                       // change this insead
                                scoreDisplay.setText(Integer.toString(score));
                                temp = 2;  // "2" will signify that an input has been given
                            }
                            else {
                                botDisplay.setText("Wrong");
                                ansDisplay.setText("");
                                temp = 1;
                            }
                        }
                    }
                    else{          // whole number division case
                        if (result == Integer.valueOf(answer)) {
                            botDisplay.setText("Correct");
                            score += 2;
                            scoreDisplay.setText(Integer.toString(score));
                        }
                        else {
                            botDisplay.setText("Wrong");
                            ansDisplay.setText("");
                        }
                    }
                }

                // disable buttons until next question is clicked
                if(blank != 4 || eqGen.getRemain() == 0 || temp == 2) {
                    bPlus.setEnabled(false);
                    bMinus.setEnabled(false);
                    bMult.setEnabled(false);
                    bDiv.setEnabled(false);
                    b0.setEnabled(false);
                    b1.setEnabled(false);
                    b2.setEnabled(false);
                    b3.setEnabled(false);
                    b4.setEnabled(false);
                    b5.setEnabled(false);
                    b6.setEnabled(false);
                    b7.setEnabled(false);
                    b8.setEnabled(false);
                    b9.setEnabled(false);
                    clear.setEnabled(false);
                    enter.setEnabled(false);

                    temp = 0; // resets temp after buttons are properly disabled
                }
            }
        };

        View.OnClickListener clearListen = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ansDisplay.setText("");
            }
        };

        //listener declarations
        bPlus.setOnClickListener(plusListen);
        bMinus.setOnClickListener(minusListen);
        bMult.setOnClickListener(multListen);
        bDiv.setOnClickListener(divListen);
        b0.setOnClickListener(numListen);
        b1.setOnClickListener(numListen);
        b2.setOnClickListener(numListen);
        b3.setOnClickListener(numListen);
        b4.setOnClickListener(numListen);
        b5.setOnClickListener(numListen);
        b6.setOnClickListener(numListen);
        b7.setOnClickListener(numListen);
        b8.setOnClickListener(numListen);
        b9.setOnClickListener(numListen);
        nextQuestion.setOnClickListener(nextQ);
        enter.setOnClickListener(enterListen);
        clear.setOnClickListener(clearListen);
    }
}