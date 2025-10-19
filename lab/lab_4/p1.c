/*
 * scanf takes as input a pattern.
 * For instance, scanf("%d %d", &x, &y) represents two ints seperated by space. So, it would
 read an int & store it in x, a space, and another int & store it in y.
 * You can also use [] to specify characters to read. For instance, [abc] would only read
 a sequence of characters with a,b & c and store it, anything else will be ignored. On the other 
 hand, [^abc] would do the opposite.
 * When you specify %* then it means to ignore this character.
 * When a pattern doesn't match, scanf simply leaves that character in the input buffer.
*/



#include <stdio.h>
#define MAX_LIMIT 10

int main()
{
    char word[MAX_LIMIT];
    
    // If you enter aa aa, then aa will be read but second aa will be ignored
    printf("Enter a char (a, b or c): ");
    scanf("%[abc]", word);
    printf("\nstring entered: %s\n", word);
    
    int num1, num2;
    // The second aa will be read by this and thats why you wont get prompted to enter anything.
    printf("Enter a comma separated nums (a,b): ");
    scanf("%d,%d", &num1, &num2); 
    printf("\nnums entered: %d %d\n", num1, num2);
    
    int num;
    printf("Enter two numbers seperated by space: ");
    scanf("%*d %d", &num);
    printf("\nNum entered: %d\n", num); // Note how first entered char is ignored.
    return 0;
}
