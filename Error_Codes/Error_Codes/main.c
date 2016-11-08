//
//  main.c
//  Error_Codes
//
//  Created by Dan Weston on 08/11/2016.
//  Copyright © 2016 Dan Weston. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

enum errorCode {
    NO_ERROR,
    BAD_ALLOC,
    BAD_FILE,
    USER_ERROR
};

char * getErrorText(enum errorCode);

int main(int argc, const char * argv[]) {
    
    enum errorCode status = NO_ERROR;
    
    double *buffer = malloc(512*sizeof(double));
    if (buffer == NULL) {
        status = BAD_ALLOC;
        goto cleanup;
    }//If memory allocation fails program now returns status BAD_ALLOC
    
    FILE *fp = fopen("bob.txt", "r");
    if (fp == NULL) {
        status = BAD_FILE;
        goto cleanup;
    }
    
    goto cleanup;
    
cleanup:
    
    free(buffer);
    fclose(fp);
    
    printf("%s\n", getErrorText(status));
    
    return status;
}

char * getErrorText(enum errorCode err) {
    switch (err) {
        case NO_ERROR:
            return "";
        case BAD_ALLOC:
            return "Memory allocation failed";
        case BAD_FILE:
            return "Oops";
        case USER_ERROR:
            return "You muppet";
        default:
            return "Unknown error";
    }
}
//Look on IoSR for error handling code!
