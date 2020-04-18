//---------------------------------------------------------------------------
#include <stdio.h>
#pragma hdrstop

#define n_max	10
#define n_rows	3

typedef bool board [n_rows] [n_max] ;

#define max_iter	100


//---------------------------------------------------------------------------
int pop_count (board b, int n, int irow, int icol)
{  	int up, down, l, r;

	up = (irow + n_rows - 1) % n_rows;
    down = (irow + 1) % n_rows;
    l = (icol + n - 1) % n;
    r = (icol + 1) % n;

    return (b [up] [l] + b [irow] [l] + b [down] [l] + b [up] [icol] + b [down] [icol] +
    		b [up] [r] + b [irow] [r] + b [down] [r]);
}

bool try_osc (board ib, int n_col, bool printit)
{	board cur_state;
	board next_state;
    int iter;
    int irow;
    int icol;
    bool solved;
    bool not_static;
    int pc;

    solved = false;
    for (irow = 0; irow < n_rows; irow++) {
    	for (icol = 0; icol < n_col; icol++) {
        	cur_state [irow] [icol] = ib [irow] [icol];
        }
    }

    not_static = true;
    for (iter = 0; iter < max_iter && !solved && not_static; iter++) {
		solved = true;
    	not_static = false;

    	for (irow = 0; irow < n_rows; irow++) {
    		for (icol = 0; icol < n_col; icol++) {
            	if (printit) {
                	printf (" %d", (int) cur_state [irow] [icol]);
                }
            	pc = pop_count (cur_state, n_col, irow, icol);
                next_state [irow] [icol] = (pc == 3) || (cur_state [irow] [icol] && (pc == 2 || pc == 3));
                not_static |= (next_state [irow] [icol] != cur_state [irow] [icol]);

                if (next_state [irow] [icol] != ib [irow] [icol]) {
                	solved = false;
                }
            }
            if (printit) {
            	printf ("\n");
            }
        }
    	for (irow = 0; irow < n_rows; irow++) {
    		for (icol = 0; icol < n_col; icol++) {
            	cur_state [irow] [icol] = next_state [irow] [icol];
            }
        }
        if (printit) {
        	printf ("\n");
        }
    }
    if (!printit && solved && iter > 1) {
    	printf ("solved n = %d iter = %d", n_col, iter);
    	for (irow = 0; irow < n_rows; irow++) {
    		for (icol = 0; icol < n_col; icol++) {
            	printf (" %d", (int) ib [irow] [icol]);
            }
        }
        printf ("\n");
        return true;
    }
    return false;

}


void try_puz (int n)
{	board init_board;
    int istate;
	int n_states;
    int irow;
    int icol;

    n_states = 1 << (n_rows * n);
    for (istate = 1; istate < n_states; istate++)
    {	for (irow = 0; irow < n_rows; irow++) {
    		for (icol = 0; icol < n; icol++) {
            	init_board [irow] [icol] = (istate >> ((n * irow) + icol)) & 1;
            }
    	}
/*
    	printf ("try n = %d", n);
    	for (irow = 0; irow < n_rows; irow++) {
    		for (icol = 0; icol < n; icol++) {
            	printf (" %d", (int) init_board [irow] [icol]);
            }
        }
        printf ("\n");
*/
        if (try_osc (init_board, n, false)) {
        printf ("%d\n", istate);
        	try_osc (init_board, n, true);
        }
    }
}

#pragma argsused
int main(int argc, char* argv[])
{	int n;

	for (n = 2; n < n_max; n++) {
    	try_puz (n);
    }
	return 0;
}
//---------------------------------------------------------------------------


