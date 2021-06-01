package edu.clarkson.ee408;

public class EquationGenerator {

    private static int op1;
    private static int op2;
    private static char operator;
    int operatorint;
    private static int res;
    private static int remain;
    private static int blank;
    private static String out;

    public EquationGenerator() {
        out = "";
        remain = 0;
    }

    public int getOp1() {
        return op1;
    }

    public int getOp2() {
        return op2;
    }

    public int getRes() {
        return res;
    }

    public int getRemain() {
        return remain;
    }

    public int getBlankLoc() {
        return blank;
    }

    public char getOperator() {
        return operator;
    }

    public String getString() {
        return out;
    }

    private void randomize(int score) {
        int max = 9;
        int min = 0;
        op1 = (int) (Math.random() * (max - min + 1)) + min;
//		System.out.println(op1);
        op2 = (int) (Math.random() * 10);
//		System.out.println(op2);

        int opermax = 4;
        int opermin = 1;


        if (score <= 40) {
            opermax = 2;
        }
        operatorint = (int) (Math.random() * (opermax - opermin + 1)) + opermin;
        operator = ' ';
        res = 0;
        remain = 0;
        if(operatorint == 1) {
            operator = '+';
            res = op1 + op2;
        }else if(operatorint == 2) {
            operator = '-';
            if(op2 > op1) {
                int temp = op2;
                op2 = op1;
                op1 = temp;
            }
            res = op1 - op2;
        }else if(operatorint == 3) {
            operator = '*';
            res = op1 * op2;
        }else if(operatorint == 4) {
            operator = '/';
            while (op2 == 0) {
                op2 = (int) (Math.random() * 10);
            }
            while (op1 == 1 || op1 == 0) {
                op1 = (int) (Math.random() * 10);
            }
            res = op1 / op2;
            remain = op1 % op2;
        }else {
            System.out.println("err");
        }
    }

    public void generate(int score) {

        randomize(score);

        int blankmax = 4;
        int blankmin = 1;

        if(score <= 20 || (score >= 40 && score <= 60)) {
            blankmax = 2;
            blankmin = 2;
        }

        blank = (int) (Math.random() * (blankmax - blankmin + 1)) + blankmin;

        //re-roll blank if there is an ambiguous question
        while((blank == 3 && operator == '*' && op1 == 0) || ((blank == 1 || blank == 3) && op2 > op1 && operator == '/') || (blank == 2 && ((op2 == 0 && ((operatorint == 1 || operatorint == 2)) || (op2 == 1 &&(operatorint == 3 || operatorint == 4))) || (op1 == 2 && op2 ==2 && (operator == '+' || operator == '*')) || (op1 ==4 && op2 == 2) && (operator == '-' || operatorint == '/')))) {
            randomize(score);
        }

        if(blank == 1) {
            out = " _ " + operator + " " + op2 + " " + " = " + res;
        }else if(blank == 2) {
            out = op1 + " _ " + op2 + " = " + res;
        }else if(blank == 3) {
            out = op1 + " " + operator + " _ " + " = " + res;
        }else if(blank == 4) {
            out = op1 + " " + operator + " " + op2 + " = " + " _ ";
        }else {
            System.out.println("err");
        }


        if(remain != 0 && blank != 4) {
            out += " Remainder " + remain;
        }else if(blank == 4 && operatorint == 4) {
            out += " Remainder " + " _ ";
        }

    }

}