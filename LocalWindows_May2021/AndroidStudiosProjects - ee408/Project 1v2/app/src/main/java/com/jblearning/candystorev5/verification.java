package com.jblearning.candystorev5;

public class verification
{
    private static boolean valid;

    public verification(){
        valid = false;
    }

    public static boolean verState(String state)
    {
        valid = false;
        String[] stateList = {"AL" , "AK" , "AR" , "CA" , "CO" , "CT" , "DE" ,"DC","FL","GA","HI","ID","IL","IN","IA","KS","KY","LA","ME","MD","MA","MI","MN","MS","MO","MT","NE","NV","NH","NJ","NM","NY","NC","ND","OH","OK","OR","PA","RI","SC","SD","TN","TX","UT","VT","VA","WA","WV","WI","WY"};
        for (String a: stateList){
            if (a.equals(state)){
                valid = true;
            }
        }
        return valid;
    }

    public static boolean verAddress(String address)
    {
        valid = false;
        for(int c=0; c<address.length();c++)
        {
            if(address.charAt(c)!=' ')
            {
                if(Character.isDigit(address.charAt(c)))
                {
                    valid = true;
                }
                else
                {
                    break;
                }
            }
        }
        return valid;
    }

    public static boolean verCVC(String CVC)
    {

        valid = true;
        if(CVC.length()<3)
        {
            valid =  false;
        }
        return valid;
    }

    public static boolean verCard(String card)
    {
        valid = true;
        if(card.length()<16)
        {
            valid =  false;
        }
        return valid;
    }

    public static boolean verMonth(String month)
    {
        valid = false;
        int test=Integer.parseInt(month);
        if(test>0||test<13)
        {
            valid = true;
        }
        return valid;
    }

    public static boolean verYear(String year)
    {
        valid = false;
        int test=Integer.parseInt(year);
        if(test>0||test<99)
        {
            valid = true;
        }
        return valid;
    }

//    public static boolean verify(String Address, String State, String ExpMonth, String ExpYear, int CVC, String Number)
//    {
//        boolean fincheck=true;
//        if(verAddress(Address))
//        {
//            if(verState(State))
//            {
//                if(verMonth(ExpMonth))
//                {
//                    if(verYear(ExpYear))
//                    {
//                        if(verCVC(CVC))
//                        {
//                            if(verCard(Number))
//                            {
//
//                            }
//                            else
//                            {
//                                //System.out.println("Card Number Too Short");
//                                fincheck=false;
//                            }
//                        }
//                        else
//                        {
//                            //System.out.println("CVC Too Short");
//                            fincheck=false;
//                        }
//                    }
//                    else
//                    {
//                        //System.out.println("Year Not In Bounds");
//                        fincheck=false;
//                    }
//                }
//                else
//                {
//                    //System.out.println("Month Not In Bounds");
//                    fincheck=false;
//                }
//            }
//            else
//            {
//                //System.out.println("State Not Found");
//                fincheck=false;
//            }
//        }
//        else
//        {
//            //System.out.println("Address Entered In An Incorect Manner");
//            fincheck=false;
//        }
//        if(fincheck=true)
//        {
//            return true;
//        }
//        else
//        {
//            return false;
//        }
//    }

}