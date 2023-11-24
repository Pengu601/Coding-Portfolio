#include <stdio.h>

int main(){
    //-------1

    //a
     printf("%c\n", 'c');

     //b
     printf("%.3f\n", 9.375);

     //c
      printf("%.1s\n", "Monday");

      //d
      puts("\"A string in quotes\"");

      //e
      printf("%d%d\n", 12, 20);

      //f
      printf("%c\n", 'x');

      //g
      printf("%s\n", "Richard");

      //--------2

      //a
      printf("%10d\n", 1234);

      //b
      printf("%+.3e\n", 123.456789);

      //c
      double x = scanf("%lf", &x);
      puts("");

      //d
      printf("0%o\n", 100);

      //e
      char arr[5];
      scanf("%s", arr);
      printf("%s\n", arr);

      //f
      char a[100];
      char c;
    
      for(int i =0; i < 100; i++){
        scanf("%c", &c);
        if(c >= '0' && c <= '9'){
            a[i] = c;
        }
        else{
            break;
        }
      }

      //g
      int x = 10; // Field width
      int y = 2;  // Precision

      double value = 87.4573;

      printf("Formatted double value: %*.*f\n", x, y, value);

      //h
      float percent;
      char percentSymbol;

      printf("Enter a percentage value (e.g., 3.5%%): ");

      if (scanf("%f%c", &percent, &percentSymbol) == 2 && percentSymbol == '%') {
          // Check if both the float and '%' character were successfully scanned
          printf("You entered %.2f%%\n", percent);
      }

      //i
      printf("%+20.3lf\n", 3.333333);

      //---------3

      //a
      unsigned int value = 40000;
      printf("%-15.8u\n", value);

      //b
      int hex;

      printf("Enter a hexadecimal value: ");
      if (scanf("%x", &hex) == 1) {
          printf("You entered the hexadecimal value: 0x%x\n", hex);
      }

      //c
      printf("With a sign: %+d\n", 200);  
      printf("Without a sign: %d\n", 200);

      //d
      printf("0x%#x\n", 100);

      //e
      char s[100];
      char s;
      int i = 0;

      while(1){
        scanf("%c", &s);

        if(s == 'p'){
            break;
        }
        else{
            s[i] = s;
            i++;
        }
      }

      //f
      printf("Formatted number: %09f\n", 1.234);

      //g
      int hour, minute, second;

      printf("Enter a time (hh:mm:ss): ");
    
      if (scanf("%d:%d:%d", &hour, &minute, &second) == 3) {
          printf("You entered the following time: %02d:%02d:%02d\n", hour, minute, second);
      }

      //h
      char s[100]; // Define a character array to store the string (adjust the size as needed)

      printf("Enter a string in the form \"characters\": ");
    
      if (scanf("\"%99[^\"]\"", s) == 1) {
          rintf("You entered the string: %s\n", s);
      }

      //i
      printf("Enter a time (hh:mm:ss): ");
    
      if (scanf("%d:%d:%d", &hour, &minute, &second) == 3) {
          while (getchar() != '\n');  // Consume the newline character and any extra input
          printf("You entered the following time: %02d:%02d:%02d\n", hour, minute, second);
      }

      //--------4

      //a
      printf("%-10d\n", 10000);

      //b
      printf("%s\n", "This is a string"); 

      //c
      printf("%*.*lf\n", 8, 3, 1024.987654);

      //d
      printf("%#o\n%#X\n%#e\n", 17, 17, 1008.83689);

      //e
      printf("%ld\n%+ld\n", 1000000, 1000000);

      //f
      printf("%10.2E\n", 444.93738);

      //g
      printf("%10.2g\n", 444.93738);

      //h
      printf("%d\n", 10.987);

      //----------5
      
      //a
      printf("%s\n", "Happy Birthday");

      //b
      printf("%s\n", "Hello");

      //c
      printf("%s\n", "This is a string");

      //d
      printf("%s", "\"Bon Voyage\"");

      //e
      char day[] = "Sunday";
      printf("%c\n", day[3]);

      //f
      puts("Enter your name: ");

      //g
      printf("%f", 123.456);

      //h
      printf("%c%c\n", 'O', 'K');

      //i
      char s[10];
      scanf("%c", &s[7]);

      

}