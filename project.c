#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct items{
    char item[20];
    float price;
    int qty;
};

typedef struct orders{
    char customer[50];
    char date[50];
    int numofItems;
    struct items itm[50];
}ord;
void generateBillHeader(char name[50],char date[30])
{
    printf("\n\n");
    printf("\t ADV. Restaurant");
    printf("\n\t--------------");
    printf("\n Date:%s",date);
    printf("\n Invoice To:%s",name);
    printf("\n");
    printf("----------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n---------------------------");
    printf("\n\n");
}
void generateBillBody(char item[30],int qty,float price)
{
    printf("%s\t\t",item);
    printf("%d\t\t",qty);
    printf("%.2f\t\t",qty*price);
    printf("\n");
}


void generateBillFooter(float total)
{
    printf("\n");
    float dis=0.1*total;
    float netTotal=total-dis;
    float cgst=0.09*netTotal;
    float grandTotal=netTotal+2*cgst;//Net total+CGST + sgst
    printf("------------------------------\n");
    printf("Sub Total\t\t\t%.2f",total);
    printf("\nDiscount @10%s\t\t\t\t%.2f","%",dis);
    printf("\n\t\t\t\t------------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nCGST @9\t\t\t %.2f" "%",cgst);
    printf("\nSGST @9\t\t\t %.2f" "%",cgst);
    printf("\n--------------------------");
    printf("\nGrand Total\t\t\t%.2f",grandTotal);
    printf("\n--------------------------\n");
}
int main()
{
    int opt,n;
    int qty;
   // float total;
    float price;
    struct orders ord;
    struct items item;
    struct orders order;
    char saveBill='y',contFlag='y';
    FILE *fp;
    char name[50];
   // struct items price;
   
    //Dashboard
    while(contFlag=='y')
    {
    float total=0;
    int invoiceFound=0;
    printf("\t======KHANA KHAZANA.RESTAURANT========");
    printf("\n\n Please select your choice:");
    printf("\n\n1.Generate Invoice");
    printf("\n2.Show all Invoices");
    printf("\n3.Search Invoices");
    printf("\n4.Exit");

    printf("\n\nYour choice:\t");
    scanf("%d",&opt);
    fgetc(stdin);

    switch(opt)
    {
        case 1:
        system("cls");
        printf("\nPlease enter the name of the customert:\t");
        fgets(ord.customer,50,stdin);
        ord.customer[strlen(ord.customer)-1]=0;
        strcpy(ord.date,__DATE__);
        printf("\nPlease enter the number of items:\t");
        scanf("%d",&n);
        ord.numofItems=n;
        for(int i=0;i<n;i++)
        {
            fgetc(stdin);
            printf("\n\n");
            printf("Please enter the item %d:\t",i+1);//because i=0
            fgets(ord.itm[i].item,20,stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
            printf("Please enter the quantity:\t");
            scanf("%d",&ord.itm[i].qty);
            printf("Please enter the unit price:\t");
            scanf("%f",&ord.itm[i].price);
            total +=ord.itm[i].qty * ord.itm[i].price;

        }
        generateBillHeader(ord.customer,ord.date);
        for(int i=0;i<ord.numofItems;i++)
        {
          generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
        }
        generateBillFooter(total);

        printf("\nDo you want to save invoice:\t\n");
        scanf("%s",&saveBill);

        if(saveBill=='y')
        {
            fp=fopen("RestaurantBill.dat","a+");
            fwrite(&ord,sizeof (struct orders),1,fp);
            if(fwrite !=0)
                printf("\nSuccesfully saved");
            else
                printf("\nError saving");
            fclose(fp);
        }
        break;
        
        case 2:
        system("cls");
        float tot;
        fp=fopen("RestaurantBill.dat","r");
        printf("\n ***Your previous invoices***\t");
        while(fread(&order,sizeof(struct orders),1,fp)){
            generateBillHeader(order.customer,order.date);
            for(int i=0;i<order.numofItems;i++)
            {
                generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                tot+=order.itm[i].qty * order.itm[i].price;
            }
            generateBillFooter(tot);
        }
        fclose(fp);
        break;

        case 3:
        printf("Enter name of the customer:\t");
        fgets(name,50,stdin);
        name[strlen(name)-1]=0;
        system("cls");
        //float tota;
        fp=fopen("RestaurantBill.dat","r");
        printf("\t***Invoice of %s***\n",name); 
        while(fread(&order,sizeof(struct orders),1,fp)){
            float tot=0;
            if(!strcmp(order.customer,name))
            {
                generateBillHeader(order.customer,order.date);
                for(int i=0;i<order.numofItems;i++)
                {
                generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                tot+=order.itm[i].qty * order.itm[i].price;
                }
                generateBillFooter(tot);
                invoiceFound=1;
            }
        }
        if(!invoiceFound){
            printf("Sorry the invoice for %s doesnot exists",name);
        }
        fclose(fp);

        break;

        case 4:
        printf("----Thanks for visiting ! Have a good day.:)----");
        break;

        default:
        printf("Please choose a right option.");
        break;


    }
       printf("\nDo you want to perform another operation?[y/n]:\t");
       scanf("%s",&contFlag);
    }
        printf("----Thanks for visiting ! Have a good day.:)----");
        printf("\n\n");

    return 0;
}