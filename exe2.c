#include "codexion.h"

typedef struct s_printer {
    int id;
}   t_printer;

typedef struct s_office {
    int         id;
    t_printer   *left;
    t_printer   *right;
}   t_office;

int main()
{
    t_printer   printers[3];
    t_office    offices[3];

    int i;

    i = 0;
    while (i < 3)
    {
        printers[i].id = i;
        offices[i].id = i;
        // if (i - 1 < 0){
        //     offices[i].left = &printers[2];
        //     offices[i].right = &printers[i];
        // }
        // else
        // {
        //     offices[i].left = &printers[i - 1];
        //     offices[i].right = &printers[i];
        // }
        offices[i].left = &printers[(i - 1 + 3) % 3];
        offices[i].right = &printers[i];
        i++;
    }
    i = 0;
    while (i < 3)
    {
        printf("Office %d: left=%d  right=%d\n", i+1, offices[i].left->id, offices[i].right->id);
        i++;
    }
    
}
