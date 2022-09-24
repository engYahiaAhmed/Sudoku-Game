#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<mmstream.h>
#include <time.h>
#include"sudoku.h"
#define N_of_Rows    9
#define N_of_Columns 9
int deleteFlagCol;//Flag to track column after the deletion process
int deleteFlagRow;//Flag to track row after the deletion process
int deleteFlagBox;//Flag to track Box after the deletion process
int c;//global variable to counting number of Squares that user has filled -->arr_user[9][9]
int countOfInitialValues;//global variable for counting initial numerical values of arr[9][9]
/*******************    The initial static array for the game, user can     ***************************/
/*******************    only use locations that hold space character ' '   **************************/
int arr[N_of_Rows][N_of_Columns]= { {7,32,32,4,9,32,32,3,32}
    ,{32,9,32,32,5,32,32,6,7}
    ,{32,8,32,32,3,1,32,32,32}
    ,{32,32,32,32,32,32,2,1,4}
    ,{32,32,32,9,32,3,32,32,32}
    ,{6,7,5,32,32,32,32,32,32}
    ,{32,32,32,3,2,32,32,8,32}
    ,{2,6,32,32,1,32,32,4,32}
    ,{32,1,32,32,6,4,32,32,5}
};
/************   user array that array user will user to play the game and hold numbers that he insert       ***********/
/************   any location in the array either hold 0 or user entered number so 0 means unused location   **********/
int arr_user[N_of_Rows][N_of_Columns];
/************   array of flags every location in that array represent a state of a number either user entered   ***********/
/************   number or static initial number if the number in the right position then its flag will be 1     **********/
/************   and if it was in the wrong location its flag will be 0 so this array will track every number   **********/
/************   user enter and check its state but note that all initial value will be represented by 1       **********/
/************   and the empty location will be represented by -1                                             **********/
int arr_flags[N_of_Rows][N_of_Columns];


void color(int color_val)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,color_val);
}
void moveToX_Y(int x,int y)
{
    COORD coord= {x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void sudoku_Y_axisPrint(void){
    moveToX_Y( 51,1);//to move cursor at a certain position
    color(0xa);////to color the output text
    printf("Y\n\n");
    printf("\t\t\t ");
    for(int i=0; i<N_of_Rows; i++)
    {
        color(0xa);
        printf("====");

        color(0xf);
        printf("%d",i+1);
        if((i+1)%3==0)
        {
            color(0x0a);
            printf("==");
        }
    }
    printf("===");
    printf("\n");
    /****************************************************/
}

void sudoku_print(int val,int x,int y)
{

    int i,j;
    countOfInitialValues=0;//global variable for counting initial values array of arr[9][9]
    c=0;//global variable to counting number of Squares that user has filled  arr_user[9][9]
    /********this part for printing Y axis values ********/
    sudoku_Y_axisPrint();
    for(i=0; i<N_of_Rows; i++)
    {
        for(j=0; j<N_of_Columns; j++)
        {
/***********this part for printing X axis values ************/
            if(j==0)
            {

                if(i==4)
                {
                    color(0xa);
                    printf("\t\t   X     ");
                }
                else
                {
                    printf("\t\t\t ");
                }
                color(0xa);
                printf("|");
                color(0xf);
                printf("%d",i+1);
            }
/************************************************************************/
/******************the static initial values printing part***************/
            if(arr[i][j]!=32)
            {
                countOfInitialValues++;//Global variable counts number of static initial array numerical values->>arr[9][9]
                color(0x0);//to hide the '|' symbol before numerical values of arr[9][9]
                if(j%3==0)
                {
                    color(0xa);//to color or show the '|' symbol (Green) before numerical values of arr[9][9] at Y-indices->{0,3,6}
                }
                printf("|");
                //normal color of initial array numbers --->arr[9][9]
                color(30);
                if(arr[i][j]==val&&(i==x-1||j==y-1))
                {
                    //To color the same number that user has used on x-axis or Y-axis (arr[9][9])
                    //with different color as indication
                    color(55);
                }
                printf(" %d  ",arr[i][j]);

                arr_flags[i][j]=1;//always the initial numbers on the right position
            }
            else
            {
/******************the spaces of initial array arr[9][9]*****************************/
                color(0x0);//to hide the '|' symbol before spaces of arr[9][9]
                if(j%3==0)
                {
                    color(0xa);//to color or show the '|' symbol (Green) before spaces of arr[9][9] at Y-indices->{0,3,6}
                }
                printf("|");
/******************the User array numbers printing part arr_user[9][9]***************/
                if(arr_user[i][j]!=0)
                {
                    c++;//Global variable counts number of squares that user has filled
                    color(47);//normal color of user array numbers --->arr_user[9][9]
                    if(arr_flags[i][j]==0)
                    {
                        color(44);//To color the number with different color (Red) if the number was in the wrong position
                    }
                    printf(" %d  ",arr_user[i][j]);
                }
                else
                {
                    /*************************************************************************************/
                    /************if arr_user [i][j]==0 then arr_flags take -1 as indication**************/
                    /********************** that it's not true or false position************************/
                    /**************************** no one set the flag yet *****************************/
                    arr_flags[i][j]=-1;
/******************************display the space character ' ' in the positions that user has not used yet********************/
                    color(0x15);
                    printf(" %c  ",arr[i][j]);
                }


            }
/******************************To display the middle parts********************/
            if((j+1)%3==0)
            {
                color(0x0a);
                printf("|:");//To display '|:' symbol after Y-axis ->{3,6,9}
            }
            if(j==8)
            {
                color(0x0a);
                printf("|");//To display last '|' symbol after Y-axis ->{9}
            }
        }
        printf("\n");

        if((i+1)%3==0){
/******************To display this line after x-axis ->{3,6,9}**************************/
            color(0x0a);
            printf("\t\t\t ======================================================\n");
        }
    }

//   printf("C=%d,Val=%d\n",c,val);
}
void sudoku_SetValue(int x,int y,int val)
{
    arr_user[x-1][y-1]=val;
}
/*******************Function To check if squares of sudoku has filled***************************/
int sudoku_IsFull()
{
    return (c == ((N_of_Rows*N_of_Columns)-countOfInitialValues));
   // return (c == 6); //to test by first box
}
/******************Function To check if a certain number is repeated in a box 3*3 ***************/
/******************set arr_flag[9][9] to 0 on repeated positions of arr_user[9][9] *************/
/*********************and return 0 if the number was repeated and 1 if it's not ***************/
//FuncCheckFlag for distinguish who call the sudoku_CheckBox() if the call from main
//then it takes 0 if it was from another check function it take 1
int sudoku_CheckBox(int x,int y,int val,int FuncCheckFlag)
{
    int i,j,first_i=0,first_j=0,rowOffset,colOffset,countOfRep=0,flagFirst=1;
    arr_flags[x-1][y-1]=1;
    //to determine the box like if x=2 -> offset=1 - 1%3 ->then offset=0
    //and if  y=4 -> offset=3 - 3%3 ->then offset=3 and so on
    rowOffset = (x-1) - (x-1) % 3;
    colOffset = (y-1) - (y-1) % 3;


    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            //if value appears in either arr_user[i][j] or  arr[i][j]
            if((arr_user[i+rowOffset][j+colOffset]==val)||(arr[i+rowOffset][j+colOffset]==val))
            {
                countOfRep++;
                //I'm interested just in user array because I will not set 0 on numerical locations of arr[][] even if it was repeated
                // numerical locations flags of arr[][] always equal -->1 -->arr_flag[][]=1;
                if(arr_user[i+rowOffset][j+colOffset]==val)
                {
                    //To ensure that it repeated more than one time or not
                    if(flagFirst == 1)
                    {
                        first_i=i+rowOffset;
                        first_j=j+colOffset;
                        flagFirst=0;
                    }
                    if(countOfRep>1)
                    {
                        //set array of flags equal 0 to all repeated values of user array
                        arr_flags[i+rowOffset][j+colOffset]=0;
                    }

                }
            }
        }
    }
    if(countOfRep==1&&flagFirst==0)
    {
        //if the function call was from another check function after deleting process
        //and the value appears just one time in the box then check box return true

		if(FuncCheckFlag==1){
			arr_flags[first_i][first_j]=1;
			return arr_flags[first_i][first_j];
		}
        if(deleteFlagBox==1)
        {
            //if the value occurrence is one time on box after the deleting process
            //I cannot determine if it is on the right position or not except after checking its column and row
            //if the value repeated in the column or row then it's still in the wrong position so array flags[][]=0
            deleteFlagBox=0;
            arr_flags[first_i][first_j]=sudoku_colCheckTraverse(first_i+1,first_j+1,val,1);
            if( arr_flags[first_i][first_j]){
              arr_flags[first_i][first_j]=sudoku_rowCheckTraverse(first_i+1,first_j+1,val,1);
            }

        }else{
             //if the value occurrence is one time on the row and there was no deleting happened
            //that is mean this is the first value the user insert in the row
            arr_flags[first_i][first_j]=1;
        }

    }else if(countOfRep>1&&flagFirst==0){
        arr_flags[first_i][first_j]=0;
    }else{
        deleteFlagBox=0;
    }
    return arr_flags[x-1][y-1];
}
void sudoku_deleteValue(int x,int y)
{
    arr_user[x-1][y-1]=0;
    deleteFlagCol=1;
    deleteFlagRow=1;
    deleteFlagBox=1;
}
/********************Function To check if a certain number is repeated in the row ***************/
/******************set arr_flag[9][9] to 0 on repeated positions of arr_user[9][9] *************/
/*********************and return 0 if the number was repeated and 1 if it's not ***************/
//FuncCheckFlag for distinguish who call the sudoku_rowCheckTraverse if the call from main
//then it takes 0 if it was from another check function it take 1
int sudoku_rowCheckTraverse(int x,int y,int val,int FuncCheckFlag)
{
    int j,first_j,count=0,flagFirst=1;
    arr_flags[x-1][y-1]=1;
    for(j=0; j<N_of_Columns; j++)
    {
        //if value appears in either array user[i][j] or  arr[i][j]
        if(arr[x-1][j]==val||arr_user[x-1][j]==val)
        {

            count++;
            //I'm interested just in user array because I will not set 0 on numerical locations of arr[][] even if it was repeated
            // numerical locations flags of arr[][] always equal -->1 -->arr_flag[][]=1;
            if(arr_user[x-1][j]==val)
            {
                //To ensure that it repeated more than one time or not
                if(flagFirst==1)
                {
                    first_j=j;
                    flagFirst=0;
                }
                else
                {
                    //set array of flags equal 0 to all repeated values on the row
                    arr_flags[x-1][j]=0;
                }

            }

        }
    }
    if(count==1&&flagFirst==0)
    {
        //if the function call was from another check function after deleting process
        //and the value appears just one time in the row then check row return true
		if(FuncCheckFlag==1){
			arr_flags[x-1][first_j]=1;
			return arr_flags[x-1][first_j];
		}
        if(deleteFlagRow==1)
        {
            //if the value occurrence is one time on the row after the deleting process
            //I cannot determine if it is on the right position or not except after checking its column
            //if the value repeated in the column then it's still in the wrong position so array flags[][]=0
            deleteFlagRow=0;
            arr_flags[x-1][first_j]=sudoku_colCheckTraverse(x,first_j+1,val,1);
            if( arr_flags[x-1][first_j]){
               arr_flags[x-1][first_j]=sudoku_CheckBox(x,first_j+1,val,1);
            }

        }else{
             //if the value occurrence is one time on the row and there was no deleting happened
            //that is mean this is the first value the user insert in the row
            arr_flags[x-1][first_j]=1;
        }

    }else if(count>1&&flagFirst==0){
        arr_flags[x-1][first_j]=0;
    }else{
        deleteFlagRow=0;
    }
    return arr_flags[x-1][y-1];

}
/********************Function To check if a certain number is repeated in the column ************/
/******************set arr_flag[9][9] to 0 on repeated positions of arr_user[9][9] *************/
/*********************and return 0 if the number was repeated and 1 if it's not ***************/
//FuncCheckFlag for distinguish who call the sudoku_colCheckTraverse if the call from main
//then it takes 0 if it was from another check function it take 1
int sudoku_colCheckTraverse(int x,int y,int val,int FuncCheckFlag)
{
    int i,count=0,first_i=-1,flagFirst=1;
    arr_flags[x-1][y-1]=1;
    for(i=0; i<N_of_Rows; i++)
    {
        //if the value appears in either array user[i][j] or  arr[i][j]
        if(arr[i][y-1]==val||arr_user[i][y-1]==val)
        {
            count++;
            //I'm interested just in user array because I will not set 0 on numerical locations of arr[][] even if it was repeated
            // numerical locations flags of arr[][] always equal -->1 -->arr_flag[][]=1;
            if(arr_user[i][y-1]==val)
            {
                //To ensure that it repeated more than one time or not
                if(flagFirst==1)
                {
                    first_i=i;
                    flagFirst=0;
                }
                else
                {
                    //set array of flags equal 0 to all repeated values on the column
                   arr_flags[i][y-1]=0;
                }

            }

        }
    }
    /**************************if the value occurrence is one time *********************/
    if(count==1&&flagFirst==0)
    {
        //if the function call was from another check function after deleting process
        //and the value appears just one time in the column then check col return true
		if(FuncCheckFlag==1){
			arr_flags[first_i][y-1]=1;
			return arr_flags[first_i][y-1];
		}
        if(deleteFlagCol==1)
        {
            //if the value occurrence is one time on the column after the deleting process
            //I cannot determine if it is on the right position or not except after checking its row
            //if the value repeated in the row then it's still in the wrong position so array flags[][]=0
            deleteFlagCol=0;
            arr_flags[first_i][y-1]=sudoku_rowCheckTraverse(first_i+1,y,val,1);
            if( arr_flags[first_i][y-1]){
                arr_flags[first_i][y-1]=sudoku_CheckBox(first_i+1,y,val,1);
            }

        }else{
             //if the value occurrence is one time on the column and there was no deleting happened
            //that is mean this is the first value the user insert in the column
            arr_flags[first_i][y-1]=1;
        }
    }else if(count>1&&flagFirst==0){
        arr_flags[first_i][y-1]=0;
    }else{
        deleteFlagCol=0;
    }
    return arr_flags[x-1][y-1];
}
/**************************To print array of flags to check the algorithm********************/
void arr_2DPrint(void)
{
    int i,j;
    for(i=0; i<N_of_Rows; i++)
    {
        for(j=0; j<N_of_Columns; j++)
        {
            printf("%3d ",arr_flags[i][j]);
        }
        printf("\n");
    }
}
/**************************To check Coordinate (x,y)***********************/
int sudoku_isValidCoordinate(int x,int y)
{
    return (arr[x-1][y-1]==' ')&&(x>=1&&x<=9)&&(y>=1&&y<=9);
}

int sudoku_checkVal(int val)
{
    return (val>=1)&&(val<=9);
}
/******************after solving the game with the static initial starting array ************************/
/********there is an optional choice for user he can search for a valid new initialization *************/
/*************************and set the new initialization to start a new game***************************/
void sudoku_inti(void)
{
    int i,j, val=0,x=1,y=1;

    for( i=0; i<N_of_Rows; i++)
    {
        for(j=0; j<N_of_Columns; j++)
        {
            arr[i][j]=32;//set all initial array elements equal -->' '
            arr_user[i][j]=0;
        }
    }
    sudoku_print(val,x,y);
    printf("\n\t\t\t\t      Note: You have to search for a valid initialization first\n\t\t\t\t           ... on the Internet to start an accurate Sudoku game!");
    for(i=0; i<N_of_Rows; i++)
    {
        for(j=0; j<N_of_Columns; j++)
        {

            printf("\n\t\t\t\t      Set The initial values of the Game: ");
            printf("\n\t\t\t\t      To skip Enter -> 0 ");
            printf("\n\t\t\t\t      Enter (%d,%d) initial value: ",i+1,j+1);
            scanf("%d",&val);
            if(val==0)
            {
                arr[i][j]=32;
                system("cls");
                sudoku_print(val,i+1,j+1);
                continue;
            }
            //if he entered invalid value like -1,15 and so on..
            while(sudoku_checkVal(val)==0)
            {
                system("cls");
                sudoku_print(0,i+1,j+1);
                color(7);

                printf("\n\n\t\t\t\t      Wrong number !");
                printf("\n\t\t\t\t      To skip Enter -> 0 ");
                printf("\n\t\t\t\t      Enter (%d,%d) initial value: ",i+1,j+1);
                Sleep(1500);
                scanf("%d",&val);
                if(val==0)
                {
                    arr[i][j]=32;
                    break;
                }
            }
            if(sudoku_checkVal(val)){
                arr[i][j]=val;
            }
            system("cls");
            sudoku_print(val,i+1,j+1);

        }
    }
}
/***************after solving the game with the static initial starting array **********************/
/********there is an optional choice for user to return to the default initialization *************/
/************************************and start a new game*****************************************/
void sudoku_intiStatic(void)
{
    for(int i=0; i<N_of_Rows; i++)
    {
        for(int j=0; j<N_of_Columns; j++)
        {
            if(arr_user[i][j]!=0)
            {
                arr_user[i][j]=0;
                arr[i][j]=' ';
            }
        }
    }
}
/***************Function check if the user managed to solve the game or not**********************/
/*****************after filling the user array with help of array of flags *********************/
/******************if all array of flags are equal 1 then he win*******************************/

int sudoku_GameSolve()
{
    int winFlag=1;
    for(int i=0; i<N_of_Rows; i++)
    {
        for(int j=0; j<N_of_Columns; j++)
        {
            if(arr_flags[i][j]!=1)
            {
                winFlag=0;
            }
        }
    }
    return winFlag;
}
void Sudoku_Game(void)
{
    int x,y,val=0,colCheckFlag,rowCheckFlag,boxcheckFlag,game_mode;
    char ch,choice;
    /*******************   Starting game sound effect  ******************/
    PlaySound(TEXT("GameStart.wav"),NULL,SND_ASYNC);
    while(1)
    {
        color(0xf);
        printf("\n\t\t\t\t      \x4 Enter + to set new value:");
        printf("\n\t\t\t\t      \x4 Enter - to delete value:");
        printf("\n\t\t\t\t      \x4 Enter your choice: ");
        scanf(" %c",&choice);
        printf("\n\t\t\t\t      \x4 Enter x,y and the value:");
        printf("\n\t\t\t\t      \x4 Enter X: ");
        scanf("%d",&x);
        printf("\t\t\t\t      \x4 Enter Y: ");
        scanf("%d",&y);
        /*******************   Invalid Coordinate handling  ******************/
        if(!sudoku_isValidCoordinate(x,y))
        {
            system("cls");
            color(0xc);
            /*******************   Invalid Coordinate sound effect   ******************/
            PlaySound(TEXT("Windows Background.wav"),NULL,SND_ASYNC);
            printf("\n\n\n\n\t\t\t\t\tIt's forbidden coordinate !");
            printf("\n\t\t\t\t\tPlease try another location !\n");
            Sleep(1000);
            moveToX_Y(58,5);
            system("cls");
            sudoku_print(0,x,y);
            continue;
        }
        switch(choice)
        {
        case '+':
            printf("\t\t\t\t      \x4 Enter the number: ");
            scanf("%d",&val);
            /********   if the place is full    *********/
            if(arr_user[x-1][y-1]!=0)
            {
                val=arr_user[x-1][y-1];
                color(0xb);
                system("cls");
                PlaySound(TEXT("Windows Background.wav"),NULL,SND_ASYNC);
                printf("\n\n\n\n\n\n\t\t      \x4 This place is full, delete it so you can use it!");
                Sleep(2000);
                system("cls");
                sudoku_print(val,x,y);
                continue;
            }
            /********   if he has entered wrong value    *********/
            if(sudoku_checkVal(val)==0)
            {
                color(0xc);
                PlaySound(TEXT("Windows Background.wav"),NULL,SND_ASYNC);
                printf("\n\n\t\t\t\t      Wrong number !");
                printf("\n\t\t\t\t      Please try again !\n");
                moveToX_Y(58,5);
                Sleep(1500);
                system("cls");
                sudoku_print(val,x,y);
                continue;
            }
            sudoku_SetValue(x,y,val);
            PlaySound(TEXT("KbdFunction.wav"),NULL,SND_ASYNC);
            break;
        case '-':
            if(arr_user[x-1][y-1]==0){
                system("cls");
                sudoku_print(0,x,y);
                continue;
            }
            val=arr_user[x-1][y-1];
            sudoku_deleteValue(x,y);
            PlaySound(TEXT("SUCTION.wav"),NULL,SND_ASYNC);
            break;
        default:
            PlaySound(TEXT("Windows Background.wav"),NULL,SND_ASYNC);
            color(0xc);
            printf("\n\n\t\t\t\t      Wrong selection!");
            printf("\n\t\t\t\t      try again !\n");
            Sleep(1500);
            system("cls");
            sudoku_print(0,x,y);
            continue;
            break;
        }

            boxcheckFlag=sudoku_CheckBox(x,y,val,0)?1:0;
            deleteFlagBox=0;
//            printf("deleteFlagBox=%d     deleteFlagCol=%d        deleteFlagRow=%d\n",deleteFlagBox,deleteFlagCol,deleteFlagRow);
//            Sleep(3000);
            colCheckFlag=sudoku_colCheckTraverse(x,y,val,0)?1:0;
            deleteFlagCol=0;
//            printf("deleteFlagBox=%d     deleteFlagCol=%d        deleteFlagRow=%d\n",deleteFlagBox,deleteFlagCol,deleteFlagRow);
//            Sleep(3000);
            rowCheckFlag=sudoku_rowCheckTraverse(x,y,val,0)?1:0;
            deleteFlagRow=0;
//            printf("deleteFlagBox=%d     deleteFlagCol=%d        deleteFlagRow=%d\n",deleteFlagBox,deleteFlagCol,deleteFlagRow);
//            Sleep(3000);
        if(colCheckFlag&&rowCheckFlag&&boxcheckFlag)
        {
            arr_flags[x-1][y-1]=1;
        }
        else
        {
            PlaySound(TEXT("failed.wav"),NULL,SND_ASYNC);
            arr_flags[x-1][y-1]=0;
        }
        system("cls");
        sudoku_print(val,x,y);
        //arr_2DPrint(void);
        /****************************       check fill the user array        ************************/
        if(sudoku_IsFull())
        {
            /****************************   check if all array flag -> 1   ************************/
            if(sudoku_GameSolve())
            {
                /****************************   celebration of the winning ************************/
                PlaySound(TEXT("SudokuFullWin.wav"),NULL,SND_ASYNC);
                Sleep(1500);
                system("cls");
                color(0xe);
                printf("\n\n\n\n\n\n\n\n\t\t\t \x11 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x1 \x1 \x1 \x1 \x1 \x1 \x1 \x1 \x1 \x1 \x1 \x1 \x1 \x1 \x1 \x1 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x10 \n");
                printf("\t\t\t \x11 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x1 \t\t\t\t   \x1 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x10 \n");
                printf("\t\t\t \x11 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x1 Well Done! Congratulations! \x1 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x10 \n");
                printf("\t\t\t \x11 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x1 \t\t\t\t   \x1 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x10 \n");
                printf("\t\t\t \x11 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x1 \x1 \x1 \x1 \x1 \x1 \x1 \x1 \x1 \x1 \x1 \x1 \x1 \x1 \x1 \x1 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x6 \x10 \n");
                printf("\n\t\t\t \x11\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x10 \n");
                printf("\t\t\t \x11\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2 \x3 Hats Off To You! \x3 \x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x10 \n");
                printf("\t\t\t \x11\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x2\x10 \n");

                PlaySound(TEXT("sudokuGameOver.wav"),NULL,SND_ASYNC);
                Sleep(4000);
                color(0xb);
                /****************************   To play another game ************************/
                printf("\n\n\t\t\t\t \x4 Do You want to play again ? Y/n");
                printf("\n\n\t\t\t\t \x4 Enter your answer: ");
                fflush(stdin);
                scanf(" %c",&ch);
                if(ch=='Y'||ch=='y')
                {
                    /****************************   play with the default initialization      *************************/
                    /****************************   Set a new initialization for a new game   ************************/
                    system("cls");
                    printf("\n\n\t\t\t \x4 Enter -> 1 to play with the default initialization........");
                    printf("\n\n\t\t\t \x4 Enter -> 2 Set new initialization : ");
                    scanf("%d",&game_mode);
                    system("cls");
                    switch(game_mode)
                    {
                    case 1:
                        PlaySound(TEXT("GameStart.wav"),NULL,SND_ASYNC);
                        sudoku_intiStatic();
                        break;
                    case 2:
                        sudoku_inti();
                        break;
                    default:
                        sudoku_intiStatic();
                        break;
                    }
                    sudoku_print(0,x,y);
                }
                else
                {
                    exit(0);
                }

            }

        }
    }
}

