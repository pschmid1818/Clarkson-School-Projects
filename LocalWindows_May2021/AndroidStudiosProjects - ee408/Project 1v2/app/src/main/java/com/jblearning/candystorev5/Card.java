package com.jblearning.candystorev5;

public class Card
{
    public final String Address;
    public final String CardType;
    public final int CVC;
    public final long Number;
    public final String Name;
    public final String ExpDate;

    public Card(String FirstName, String MI, String LastName, String Address, String City, String State, String Zip, String ExpMonth, String ExpYear, String CardType, int CVC, long Number)
    {
        this.Name = LastName + " " + FirstName + " " + MI +".";
        this.Address = Address + ", " + City + ", " + State + ", " + Zip;
        this.ExpDate = ExpMonth+ "/" + ExpYear;
        this.CardType = CardType;
        this.CVC = CVC;
        this.Number = Number;
    }

    public Card(String Name, String Address, String ExpDate, String CardType, int CVC, long Number)
    {
        this.Name = Name;
        this.Address = Address;
        this.ExpDate = ExpDate;
        this.CardType = CardType;
        this.CVC = CVC;
        this.Number = Number;
    }

//    public static Card Search(Card test, int numcheck,int cvccheck)
//    {
//        if(test.Number==numcheck)
//        {
//            if(test.CVC==cvccheck)
//            {
//                Print(test);
//                return test;
//            }
//            else
//            {
//                System.out.println("CVC number is wrong");
//            }
//        }
//        else
//        {
//            System.out.println("Card Number not found");
//        }
//        return null;
//    }
//
//    public static void Print(Card that)
//    {
//        System.out.println("Name:            " + that.Name);
//        System.out.println("Address:         " + that.Address);
//        System.out.println("Expiration Date: " + that.ExpDate);
//        System.out.println("Card Type:       " + that.CardType);
//        System.out.println("CVC:             " + that.CVC);
//        System.out.println("Card Number:     " + that.Number);
//    }
//
//    public static void main(String[] args)
//    {
//        String FirstName="John";
//        String MI="a";
//        String LastName="Doe";
//        String Address="123 Common St";
//        String City="Townsville";
//        String State="NY";
//        String Zip="12345";
//        String ExpMonth="01";
//        String ExpYear="22";
//        String CardType="MasterCard";
//        int CVC=123;
//        int Number=123456789;
//
//        Card test = new Card(FirstName,MI,LastName,Address,City,State,Zip,ExpMonth,ExpYear,CardType,CVC,Number);
//
//        Search(test,123456789,123);
//    }
}
