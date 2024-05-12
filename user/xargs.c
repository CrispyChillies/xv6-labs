#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h" 

#define is_blank(chr) (chr == ' ' || chr == '\t') 

int main(int argc, char *argv[]){
	char buf[2048];
	char ch;
	char *p = buf;
	char *v[MAXARG];
	int c;
	int space = 0;
	int offset = 0;

	if(argc <= 1){
		fprintf(2, "Wrong syntax!!!\n");
		exit(1);
	}

	for (c = 1; c < argc; c++) {
		v[c-1] = argv[c];
	}
	--c;

	while (read(0, &ch, 1) > 0) {
		if (is_blank(ch)) {
			space++;
			continue;
		}

		if (space != 0) {  
			buf[offset++] = 0;

			v[c++] = p;
			p = buf + offset;

			space = 0;
		}

		if (ch != '\n') {
			buf[offset++] = ch;
		} 
		else {
			v[c++] = p;
			p = buf + offset;

			if (!fork()) {
				exec(v[0], v);
				exit(0);
			}
			wait(0);
			
			c = argc - 1;
		}
	}

	exit(0);
}