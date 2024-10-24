#include <stdio.h>
#include "bcode.h"

int main()
{
	struct compile_state cs;
	init(&cs);

	select_movi(&cs, R2, 0); // i
	select_movi(&cs, R1, 1000000000); // limit
	select_movi(&cs, R0, 0); // total

	bcval_t l = label(&cs); // top
	select_addr(&cs, R0, R0, R2); // add iter to total
	select_addi(&cs, R2, R2, 1);
	bcreloc_t r = select_bltr(&cs, R2, R1, 0); // 0 is placeholder value,
						// should maybe add in an
						// UNDEFINED macro or something
	end(&cs);

	patch(&cs, r, 0, l);

	/* specify register state to run, note that seven is taken from
	 * r = 7 in rules.py, should probably provide a macro for it? */
	ubcval_t ri[7] = {0};

	/* since we don't use floating point registers, we can pass in a NULL */
	run(&cs, ri, NULL);

	/* our 'ABI' specifies that the return register is 0 */
	printf("%llu\n", (unsigned long long)ri[0]);
	destroy(&cs);
}
