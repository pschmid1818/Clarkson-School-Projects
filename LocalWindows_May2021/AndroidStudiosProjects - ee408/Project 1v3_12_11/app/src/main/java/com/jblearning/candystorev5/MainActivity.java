package com.jblearning.candystorev5;

import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Point;
import android.os.Bundle;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.widget.Toast;
import java.util.regex.*;

import com.jblearning.candystorev5.DatabaseManager;
import com.jblearning.candystorev5.R;

import org.w3c.dom.Text;

import java.text.NumberFormat;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {
    private DatabaseManager dbManager;
    private final Context context = this;
    Button getInfo, submit;
    EditText cardNumber, cvc, firstName, lastName, middleInitial, expdatemonth, expdateyear, address, city;
    EditText state, zipCode;
    RadioGroup cardType;

//    private void testData() {
//        cardNumber.setText("1111222233334444");
//        cvc.setText("123");
//        firstName.setText("John");
//        middleInitial.setText("A");
//        lastName.setText("Doe");
//        expdatemonth.setText("12");
//        expdateyear.setText("31");
//        address.setText("10 Clarkson Ave");
//        city.setText("Potsdam");
//        state.setText("NY");
//        zipCode.setText("13699");
//        cardType.check(R.id.ten);
//    }
//
//    private void testData2() {
//        cardNumber.setText("1111222233334445");
//        cvc.setText("123");
//        firstName.setText("John");
//        middleInitial.setText("B");
//        lastName.setText("Doe");
//        expdatemonth.setText("12");
//        expdateyear.setText("31");
//        address.setText("10 Clarkson Ave");
//        city.setText("Potsdam");
//        state.setText("NY");
//        zipCode.setText("13699");
//        cardType.check(R.id.ten);
//    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        cardNumber = (EditText) findViewById(R.id.info_card_number);
        cvc = (EditText) findViewById(R.id.info_cvc);
        firstName = (EditText) findViewById(R.id.info_first_name);
        lastName = (EditText) findViewById(R.id.info_last_name);
        middleInitial = (EditText) findViewById(R.id.info_middle_name);
        expdatemonth = (EditText) findViewById(R.id.info_exp_month);
        expdateyear = (EditText) findViewById(R.id.info_exp_year);
        address = (EditText) findViewById(R.id.info_address);
        city = (EditText) findViewById(R.id.info_city);
        state = (EditText) findViewById(R.id.info_state);
        zipCode = (EditText) findViewById(R.id.info_zip_code);
        cardType = (RadioGroup) findViewById(R.id.card_type);
        getInfo = (Button) findViewById(R.id.get_info);
        submit = (Button) findViewById(R.id.submit);
        dbManager = new DatabaseManager(this);

        View.OnClickListener ButtonFunction = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Button b = (Button) v;
                if (b.getId() == getInfo.getId()) {
                    AlertDialog.Builder builder = new AlertDialog.Builder(context);
                    View dialog = View.inflate(context, R.layout.get_info_dialog, null);
                    builder.setView(dialog);
                    builder.setCancelable(false);
                    final EditText getCardNumber = (EditText) dialog.findViewById(R.id.get_info_card_number);
                    final EditText getCVC = (EditText) dialog.findViewById(R.id.get_info_cvc);
                    builder.setPositiveButton("SEARCH", new DialogInterface.OnClickListener() {
                        public void onClick(DialogInterface dialog, int id) {
                            long searchNumber = Long.parseLong("1111222233334444");
                            int searchCVC = 123;
                            if (!(checkEmpty(getCardNumber) || checkEmpty(getCVC))) {
                                searchNumber = Long.parseLong(getCardNumber.getText().toString());
                                searchCVC = Integer.parseInt(getCVC.getText().toString());
                            }
                            Card searchCard = dbManager.searchData(searchNumber, searchCVC);
                            if (searchCard == null){
                                alertMessage("Account Not Found.");
                            }
                            else{
                                alertMessage("Account Information:" + "\nName: " + searchCard.Name);
                            }
//                            String message;
//                            if(searchCard == null) {
//                                message = "Not Found!";
//                            }
//                            else{
//                                message = searchCard.Name + '\n' + searchCard.Address;
//                            }
//                            final Dialog showInfo = new Dialog(context);
//                            showInfo.setTitle("Search Results");
//                            TextView showMessage = new TextView(context);
//                            showMessage.setText(message);
//                            showInfo.setContentView(showMessage);
//                            showInfo.show();
                        }
                    });
                    builder.setNegativeButton("CANCEL", new DialogInterface.OnClickListener() {
                        public void onClick(DialogInterface dialog, int id) {
                            //do things
                            dialog.dismiss();
                        }
                    });
                    final AlertDialog alert = builder.create();
                    alert.setOnShowListener(new DialogInterface.OnShowListener() {
                        @Override
                        public void onShow(DialogInterface arg0) {
                            alert.getButton(AlertDialog.BUTTON_POSITIVE).setTextColor(getResources().getColor(R.color.colorPrimaryDark));
                            alert.getButton(AlertDialog.BUTTON_POSITIVE).setTextSize(20);
                        }
                    });
                    alert.show();

                //SUBMIT BUTTON
                } else if (b.getId() == submit.getId()) {
                    //Get Data from User
                    EditText[] allInputs = {cardNumber, cvc, firstName, lastName, middleInitial, expdatemonth,
                            expdateyear, address, city, state, zipCode};

                    System.out.println("Validate: " + validateInput(allInputs));

                    if (validateInput(allInputs)) {
                        RadioButton ctype = (RadioButton) findViewById(cardType.getCheckedRadioButtonId());
//            //Create Card
                        Card inCard = new Card(
                                firstName.getText().toString(),
                                middleInitial.getText().toString(),
                                lastName.getText().toString(),
                                address.getText().toString(),
                                city.getText().toString(),
                                state.getText().toString(),
                                zipCode.getText().toString(),
                                expdatemonth.getText().toString(),
                                expdateyear.getText().toString(),
                                ctype.getText().toString(),
                                Integer.parseInt(cvc.getText().toString()),
                                Long.parseLong(cardNumber.getText().toString())
                        );

                        //Insert Card
                        dbManager.insert(inCard);

                        //Clear Data
                        for (int k = 0; k < allInputs.length; k++) {
                            allInputs[k].setText("");
                        }
                        alertMessage("Information Submitted.");
                    } else{
                        alertMessage("Please Fill Out All Fields.");
                    }

                }
            }
        };

        getInfo.setOnClickListener(ButtonFunction);
        submit.setOnClickListener(ButtonFunction);
    }


    ////////////////////////////////////ALERT MESSAGE BUILDER////////////////////////////////////////////////
    public void alertMessage (String mess){
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setMessage(mess)
                .setCancelable(false)
                .setPositiveButton("X", new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int id) {
                        //do things
                    }
                });
        AlertDialog alert = builder.create();
        alert.show();

    }



    //---------------------BEGIN VERIFY BLOCK-----------------//

    ///Verify All/// FORMAT: ADDRESS, STATE, MONTH, YEAR, CVC, NUMBER -> cardNumber, cvc, firstName, lastName, middleInitial, expdatemonth, expdateyear, address, city, state, zipCode
    public static boolean validateInput(EditText[] allInputs)
    {
        String Number = allInputs[0].getText().toString();
        int CVC = Integer.parseInt(allInputs[1].getText().toString());
        String firstName = allInputs[2].getText().toString();
        String lastName = allInputs[3].getText().toString();
        String middleInitial = allInputs[4].getText().toString();
        String ExpMonth = allInputs[5].getText().toString();
        String ExpYear = allInputs[6].getText().toString();
        String Address = allInputs[7].getText().toString();
        String City = allInputs[8].getText().toString();
        String State = allInputs[9].getText().toString();


        boolean fincheck=true;
        if(firstName.length() < 1){
            //Error launching EPWave: [Could not parse file: 26: Unknown character encountered: 'U' before: '$']. Could not load './dump.vcd'Please enter a valid first name
            System.out.println("Please enter a valid first name.");
            fincheck = false;
        }
        if(middleInitial.length() < 1){
            //Please enter a valid middle initial
            System.out.println("Please enter a valid middle initial.");
            fincheck = false;
        }
        if(lastName.length() < 1){
            //Please enter a valid last name
            System.out.println("Please enter a valid last name.");
            fincheck = false;
        }
        if(City.length() < 1 || hasNumber(City)){
            //Please enter a valid City
            System.out.println("Please enter a valid city. hasNum: " + hasNumber((City)));
            fincheck = false;
        }
        if(!verAddress(Address))
        {
            System.out.println("Address Entered Incorrectly Manner");
            fincheck=false;
        }
        if(!verState(State))
        {
            System.out.println("State Not Found. State: " + State + ", !verState = " + verState(State));
            fincheck=false;
        }
        if(!verMonth(ExpMonth))
        {
            System.out.println("Month Not In Bounds");
            fincheck=false;
        }
        if(!verYear(ExpYear))
        {
            System.out.println("Year Not In Bounds");
            fincheck=false;
        }
        if(!verCVC(CVC))
        {
            System.out.println("CVC Too Short");
            fincheck=false;
        }
        if(!verCard(Number))
        {
            System.out.println("Card Number Too Short");
            fincheck=false;
        }
        //finally//
        return fincheck;
    }

    ///Verify State///
    public static boolean verState(String state)
    {
        System.out.println("State is:'" + state + "'");
        String[] stateList = {"AL" , "AK" , "AR" , "CA" , "CO" , "CT" , "DE" ,"DC","FL","GA","HI","ID","IL","IN","IA","KS","KY","LA","ME","MD","MA","MI","MN","MS","MO","MT","NE","NV","NH","NJ","NM","NY","NC","ND","OH","OK","OR","PA","RI","SC","SD","TN","TX","UT","VT","VA","WA","WV","WI","WY"};
        for (String a: stateList){
            if (a.equals(state)){
                return true;
            }
        }
        return false;
    }

    ///Verify Address///
    public static boolean verAddress(String address)
    {
        if (Pattern.matches("^\\d+\\s+\\w+.*", address)){
            return true;
        }
        return false;
    }

    ///Verify CVC///
    public static boolean verCVC(int CVC)
    {
        String test=Integer.toString(CVC);
        if(test.length()<3)
        {
            return false;
        }
        return true;
    }

    ///Verify Card#///
    public static boolean verCard(String card)
    {
        if(card.length()<16)
        {
            return false;
        }
        return true;
    }

    ///Verify Month///
    public static boolean verMonth(String month)
    {
        int test=Integer.parseInt(month);
        if(test>0&&test<13)
        {
            return true;
        }
        return false;
    }

    ///Verify Year///
    public static boolean verYear(String year)
    {
        int test=Integer.parseInt(year);
        if(test>0||test<99)
        {
            return true;
        }
        return false;
    }

    ///string has a number?
    private static boolean hasNumber(String a){
        for (int i = 0; i < a.length(); i++){   if (Character.isDigit(a.charAt(i))) {return true;}   }
        return false;
    }

    ///is EditText empty?
    private static boolean checkEmpty(EditText v) {
        if (v.getText().toString().trim().length() > 0) { return false; }
        else { return true; }
    }
    // ---------------------END VERIFY BLOCK-----------------//


}