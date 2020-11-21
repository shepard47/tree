#include <u.h>
#include <libc.h>

int level;

void
indent(void)
{
	int i;
	for(i=0; i<level; ++i){
		print("  ");
	}
}

void
tree(char *path)
{
	Dir *dir = dirstat(path);
	indent();
	print("%s\n", dir->name);
	level++;
	free(dir);
	int fd = open(path, OREAD);
	long ndir = dirreadall(fd, &dir);
	int i;
	for(i=0; i<ndir; ++i){
		if((dir+i)->qid.type){
			int len = strlen(path) + strlen((dir+i)->name);
			char *name = malloc(sizeof(char) * len);
			sprint(name, "%s/%s", path, (dir+i)->name);
			tree(name);
			level--;
			/*free(name);*/
		}else{
			indent();
			print("%s\n", (dir+i)->name);
		}
	}
	free(dir);
}

void
main(int argc, char **argv)
{
	if(argc == 1) argv[1] = ".";
	level = 0;
	tree(argv[1]);
}
