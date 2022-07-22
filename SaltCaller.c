/*******************************************************************************
 * @file    SaltCaller.c
 * @author  Clemens Haffner
 * @brief   Calls a crippled Android library to get a stupid salt.
 * @version 0.1
 * @date    2022-07-21
 * 
 * @copyright Copyright (c) 2022
 * 
 ******************************************************************************/

/* === Includes ============================================================= */

#include <stdio.h>
#include <dlfcn.h>
#include <elf.h>

/* === Types ================================================================ */

typedef void (*fptr_t)();

/* === Globals ============================================================== */

void    *libnative_handle = NULL;
fptr_t  func = NULL;

/* === Implementation ======================================================= */

int main(void)
{
    printf("Let's Go!\r\n");

    // Try to open library
    libnative_handle = dlopen("./libnative-lib.so", RTLD_NOW | RTLD_GLOBAL);
    if (libnative_handle == NULL)
    {
        fprintf(stderr, "Unable to open lib: %s\n", dlerror());
        return -1;
    }

    // extract function / symbol, write it to function pointer for calling it later
    func = (fptr_t)dlsym(libnative_handle, "Java_de_veedapp_veed_entities_Keys_salt");
    if (func == NULL) 
    {
        fprintf(stderr, "function not available\r\n");
        return -1;
    }

    // call the function
    func(); // TODO: if it works, get the return value (?char pointer?)

    // close library
    dlclose(libnative_handle);
    
    printf("End!\r\n");

    return 0;
}
