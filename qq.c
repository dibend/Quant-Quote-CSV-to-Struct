#include "qq.h"

struct Quote_List qq_file_to_Quote_List(char *filename)
{
    char *f, *element;
    int size, num_quotes, q_index, pos, column, row, val, mkt_open;
    struct Quote_List My_Quote_List;    
    struct stat s;
    int fd = open (filename, O_RDONLY);

    /* Get the size of the file. */
    fstat (fd, & s);
    size = s.st_size;

    f = (char *) mmap (0, size, PROT_READ, MAP_PRIVATE, fd, 0);
    
    num_quotes = 0;
    for(int i = 0; i < size; i++) {
        if(f[i] == '\n') {
            num_quotes ++; 
        }
    }
    My_Quote_List.Quotes = malloc(num_quotes * sizeof(struct Quote)); 

    pos = 0;
    column = 0;
    row = 0;
    mkt_open = 0;
    q_index = 0;
    for(int i = 0; i < size; i++) {
        if(f[i] == ',') {
            if(column == 0) {
                int el_size = ((i-pos) * sizeof(char)) + 1;
                element = (char *) malloc(el_size);
                memcpy(element, &f[pos], el_size);
                element[el_size] = 0; //null terminate
                val = atoi(element);
                free(element);
                //if regular market hours
                if(val > 34200000 && val < 57600000) {
                    mkt_open = 1;
                    My_Quote_List.Quotes[q_index].time = val;
                } else {
                    mkt_open = 0;
                }
            } else if(column == 1 && mkt_open) {
                int el_size = ((i-pos) * sizeof(char)) + 1;
		element = (char *) malloc(el_size);
                memcpy(element, &f[pos], el_size);
                element[el_size] = 0; //null terminate
                val = atoi(element);
                free(element);
                My_Quote_List.Quotes[q_index].price = val;
                q_index ++;
            }
            pos = i+1;
            column ++;
        } else if(f[i] == '\n') {
            pos = i+1;
            row ++;
            column = 0;
        }
    }
    munmap(f, size);
    My_Quote_List.size = q_index;
    return My_Quote_List;
}

