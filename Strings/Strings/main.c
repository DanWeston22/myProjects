//
//  main.c
//  Strings
//
//  Created by Dan Weston on 18/10/2016.
//  Copyright © 2016 Dan Weston. All rights reserved.
//

#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[]) {

    // Gets forename from command line
    printf("Enter Forename:\n");
    char forename[20];
    fgets(forename, 20, stdin);
    
    //Remove newline
    size_t len;
    len = strlen(forename);
    if( forename[len-1] == '\n' )
        forename[len-1] = ' ';
    
    // Gets surname from command line
    printf("Enter Surname:\n");
    char surname[20];
    fgets(surname, 20, stdin);
    

    //Concentrates forename & surname into full name
    char *fullname;
    fullname = strcat(forename, surname);
    
    //Prints Full Name
    printf("Your Name Is: ");
    puts(fullname);
    
    //Special Message
    char danWeston[20] = "Dan Weston\n";
    if (strcmp(fullname, danWeston) ==0){
        printf("You're The Special One!\n");
    }

    return 0;
    
}
