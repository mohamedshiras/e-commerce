#include <stdio.h>
#include <stdlib.h>
#include<string.h>

//globle variables
    char address[50];
    int contact;
    char methodtype[50];
    int tot=0;
    int quantity;
    int quantitycount=0;

int main()
{
    //greeting
    printf(".........Welcome.........\n To NIBM E-Commerce Site\n\n");

    //Calling login function
    login();

    return 0;
}

// read user type
void login()
{
    FILE *exp=fopen("CusData.txt","r");
    FILE *newp=fopen("CusData.txt","a");
    char key[50],pw[20],cpw[20];
    char xkey[50],xpw[20];
    int user,found=0;

    printf("Select Below option\n......................\n\t1.Existing Customer\n\t2.New User\n");
    scanf("%d",&user);

//reading the user input for existing user
    switch (user){
case 1:

    printf("\nEnter your Email or Username\n");
    scanf("%s",&key);
    printf("Enter password\n");
    scanf("%s",&pw);
    while (fscanf(exp,"%s%s",&xkey,&xpw)==2) {

        //comparing the both passwords from all user count in data set
        if (strcmp(key,xkey)==0)
        {
            found=1;
            if (strcmp(pw,xpw)==0) {
                printf(".....................\nSuccessfully logged in\n\n");
                order();
                break;
            }
            else
            {
                printf("Password does not match\n");
                return login();
                break;
            }
        }
    }
    //No data entries registered under the user input
    if (!found) {
        printf("Username does not exist\n");
        return login();
    }
    break;

//New User sign in process
case 2:

    printf("\nEnter your Email or Username\n");
    scanf("%s",&key);
    printf("Enter a password\n");
    scanf("%s",&pw);
    printf("Confirm your password\n");
    scanf("%s",&cpw);

    //comparing the password and confirm passwords are matching
        if (strcmp(pw,cpw)==0)
        {
            //Recording the entry of a new customer/user in a new file
            fprintf(newp,"\n%s\ %s\n",key,pw);
            fclose(newp);

            printf(".....................\nSuccessfully registered\n\n");
            order();
            break;
        }
        else
        {
            //unless the both passwords mismatch returns to login again
            printf("Password does not match\n");
            return login();
        }
default:

    printf("Invalid Option\n");
    return login();
    }
}



//Product Ordering Process
void order()
{

    char proname[20];
    char pro[10];
    char proid[10];
    int proprice;
    int found = 0;
    int aprotot=0;
    int productcount=0;

    //2D array which stores string values
    char selectedproducts[50][20];

    //Reading product data file
    FILE *fpro=fopen("ProductData.txt","r");

        printf("Available Items Below\n\n");
        printf("\tLaptop ID-1001\n\tHeadphone ID-1002\n\tSpeakers ID-1003\n\tMicrophone ID-1004\n\tWebcam ID-1005\n");
        printf("\tMonitor ID-1006\n\tKeyboard ID-1007\n\tMouse ID-1008\n\tPrinter ID-1009\n\tRAM ID-1010\n.............\n");

    //infinity loop which reads input until user exit by own
    while(1) {
        printf("\nEnter product ID for product price or 0 to exit\n");
        scanf("%s",&pro);

        if(strcmp(pro,"0")==0) {
            break;
        }

        //comparing the user input with data in file whether available in data file
        while (fscanf(fpro,"%s%s%d",&proid,&proname,&proprice)==3) {
            if (strcmp(pro,proid)==0) {

                //when reading made confirm found value gets 1 and display product info
                found = 1;
                printf("\n......... Product details below.............\n");
                printf("%s\t%s\t\tRs.%d/=\n",proid,proname,proprice);
                printf("\nProvide the Quantity\n");
                scanf("%d",&quantity);
                quantitycount++;

                //calculating a product total amount by its rate into quantity
                aprotot+=proprice*quantity;

                // Add product name to selected products to 2 dimension array
                strcpy(selectedproducts[productcount],proname);
                productcount++;
                break;
            }
        }

        //unless the product id isn't available in data
        if (!found) {
            printf("invalid ID please try again\n");
            order();
        }

        //re-reading the file
        rewind(fpro);
    }

    //after the user exiting file close
    fclose(fpro);

    //Sending a products amount to tot variable until process continue to submit the whole total amount
    tot+=aprotot;

    //display the total after selections made
    printf("\nTotal for selected products Rs.%d\n\n",tot);
    printf("  Your selected products below\n...............................\n");

    //Display the selected product name/names and display after exit made
    for (int x=0;x<productcount;x++){
        printf("%s\n",selectedproducts[x]);
    }

    deliveryinfo();

}

//read the total amount to check possible discounts for card payment users
void discount(int x)
{

    if (x>35000)
    {
        x=x-(x*0.10);
    }
    else if (x>25000)
    {
        x=x-(x*0.05);
    }
    else
    {
        x=x;
    }

    //declare the x value for tot variable after discount made
    tot=x;
}

//Read Delivery information by user
void deliveryinfo()
{
    int confirmation;
    printf("\n\nProvide your permanent address\n");
    scanf("%s",&address);
    printf("Enter your contact number\n");
    scanf("%d",&contact);

    //re-confirming once again by the user before goto payment
    printf("\nConfirm Address and Contact info ?\n");
    printf("1.Confirm\n2.Edit\n");
    scanf("%d",&confirmation);
        if (confirmation==1){
            payment();
        }
        else if (confirmation==2)
        {
            return deliveryinfo();
        }
        else
        {
            printf("Invalid input\n");
            return deliveryinfo();
        }

}
void payment()
{
    int method;
    char input;
    int cardnumber,exdate,cvv;

    //Providing choices for user in payment
    printf("\nSelect your payment method");
    printf("\n1.Card Payment (Receive Discounts)\n2.Cash On delivery\n");
    scanf("%d",&method);
    switch (method){
case 1:

    //Make payment through cards
    printf("Enter Card Number\n");
    scanf("%d",&cardnumber);
    printf("Expiry Date\n");
    scanf("%d",&exdate);
    printf("CVV\n");
    scanf("%d",&cvv);
    discount(tot);
    break;
case 2:

    //Cash on Delivery applied 30rs from the customer
    printf("\nRs.30 will be added to your total bill as service charge willing to place ?\n");

    //verifying whether user accepting the condition
    printf("Y-Yes / N-No\n");
    scanf(" %c",&input);
    if (input=='Y'||'y') {
        tot+=30;
    }
    else if (input=='N'||'n')
    {
        printf("Order has been canceled\n");
        return 0;
    }
    else
    {
        printf("invalid Input\n");
        return payment();

    }
    break;
default:
    printf("Wrong input\n");
    return payment();
    }

    display();

}

//Display total,quantity,customer info
void display()
{
    printf("\n\tYour total bill amount is Rs.%d with product quantity of %d\n\t\tCustomer address %s Contact %d\n",tot,quantitycount,address,contact);
    printf(".............................................................................\n");
    printf("\t\t\tThanks for choosing us <3\n\n\n\n\n");
}

