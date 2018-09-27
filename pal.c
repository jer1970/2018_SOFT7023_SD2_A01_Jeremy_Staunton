
/*
//Name: Jeremy Staunton
//id: R00158317
//class: sd2
*/
//--------------------------------------------------
// INCLUDE SECTION
//--------------------------------------------------
#include "pal.h"
#include<stdio.h>
//--------------------------------------------------
// gen_num
//--------------------------------------------------
int gen_num(int lb, int ub) {
	//1. We create the output variable with an initial value.
	int res = 0;

	//2. We assign num to a random value in the desired range
	res = (rand() % (ub - lb)) + lb;

	//3. We return the output variable
	return res;
}

//--------------------------------------------------
// my_getchar
//--------------------------------------------------
char my_get_char() {
	//1. We create the output variable with the value the user has input by keyboard
	char res = getchar();

	//2. We discard any extra character the user has input by keyboard
	boolean finish = False;
	char dummy_char = ' ';

	while (finish == False) {
		dummy_char = getchar();
		if (dummy_char == '\n')
			finish = True;
	}

	//3. We return the output variable
	return res;
}

//--------------------------------------------------
// initialise_array
//--------------------------------------------------
void initialise_array(int a[6], int num) {
    int i;
    for(i = 5;i >=0;i--){
    int digit = num%10;
    a[i] = digit;
    num = num/10;
    }
}
//--------------------------------------------------
// is_pal
//--------------------------------------------------
boolean is_pal(int a[6]) {
	boolean b = True;
    int i = 0;
    int x = 5;
    while(b == True && i < 3){
        if(a[i] != a[x])
            b = False;
        i++;
        x--;
    }
	return b;
}
//--------------------------------------------------
// ask_for_command
//--------------------------------------------------
char ask_for_command() {
    boolean valid = False;
	char res = ' ';
    do{
    printf("NEW MOVEMENT: Enter a valid command by keyword:\n");
    printf("Valid commands: a       d       w       x\n");
    res = my_get_char();
    if(res == 'a' || res == 'd' || res == 'w' || res == 'x')
        valid = True;
    }while(valid == False);
	return res;
}
//--------------------------------------------------
// process_movement
//--------------------------------------------------
void process_movement(int a[6], int** p_p, int* p_nm, char c){
    switch(c){
    case 'a':
        //if the address of the number in play is greater than the address of the array a, then a move to the left is allowed
        if(p_nm > a){
        *p_p = *p_p - 1;
        }
        break;
    case 'd':
        //if the address of the number in play is less than the address of the the last number of array a, i.e. a[5],
        //then a move to the right is allowed
        if(p_nm < &a[5]){
            *p_p = *p_p + 1;
        }
        break;
    case 'w':
        //if the digit in play is less than 9 then it can be incremented by 1
        if(*p_nm < 9){
                *p_nm = *p_nm + 1;
        }
        break;
    case 'x':
        //if the digit in play is greater than 0, then it can be decremented by 1
        if(*p_nm > 0){
            *p_nm = *p_nm - 1;
        }
        break;
    }
}
//--------------------------------------------------
// print_status
//--------------------------------------------------
void print_status(int a[6], int* p, int nm) {
    system("cls");

    printf("------ Game Status -------\n");
    printf("Number = {");
    int i;
    for(i = 0; i < 6; i++){
        printf("%d ", a[i]);
    }
    printf("\b}\n");
    char c = '^';
    int width = 11 + *p*2;//value p is multiplied by 2 to shift it 2 spaces to line up correctly with each array position
    printf( "%*c\n", width, c );

    printf("Number of moves %d\n", nm);
    printf("--------------------------\n");


}
//--------------------------------------------------
// user_game_palindrome
//--------------------------------------------------
void user_game_palindrome(int pal_num) {
    //generate a random number from 0-5, call it pos, to fix the start position of the game
    int pos = gen_num(0, 6);
    //create a pointer to this pos, pointer_pos, to access pos value later to set the place of '^'
    int* pointer_pos = &pos;
    int num = pal_num;
    //create an array for the game
    int array[6];
    //create a pointer to point at the starting array position/memory address
    int* pointer = &array[0] + pos;
    //create a pointer to this pointer, to allow change the position left or right in the array
    int** p_pointer = &pointer;
    //create a char variable to accept input from the user
    char command;
    //create a boolean to keep the game going until a palindrome is made of the array
    boolean repeat = True;
    //count keeps a record of the number of moves made
    int count = 0;

    //initialise array
    initialise_array(array, num);
    //play game
    do{
            //create an int variable, val, to store the number stored at the pointer value
            // This is used to check for any change in this value after the processMove function.
            int val = *pointer;
            //create a pointer to store the value of p_pointer, to check for any change, left or right, after processMove function.
            int* pointerPos = *p_pointer;
    //print status
    print_status(array, pointer_pos, count);
    //get input from user
    command = ask_for_command();

    //use the input
    process_movement(array, p_pointer, pointer, command);
    //check if a valid move is made: *pointer is the current number in the array,
    //if it has changed from previous, val, then add 1 to moves counter,
    //if *p_pointer is different to pointerPos then the target number in the array has changed. Add 1 to moves counter
    if(val != *pointer || pointerPos != *p_pointer)
        count += 1;
    //the difference between pointer and &array[0] is the (new)array position of the number in question, either 0, 1, 2, 3, 4, 5
    //this pos value is accessed in printStatus through its pointer, pointer_pos
    pos = (pointer - &array[0]);

    //check to see if it is a palindrome
    if(is_pal(array) == True){
            print_status(array, pointer_pos, count);
            printf("\n\nCongratulations, game completed in %d moves.\n\n", count);
        repeat = False;
    }

    }while((repeat == True));
}





