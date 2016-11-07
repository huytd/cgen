#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAKEFILE_SRC "\nall: clean\n	gcc -o $(PROJECT) $(PROJECT).c\n\nclean:\n	rm -rf $(PROJECT)\n"
#define MAIN_SRC "#include <stdio.h>\n#include <unistd.h>\n\nint main() {\n  \n}"

struct stat st = {0};

int main(int argc, char* argv[]) {
  if (argc <= 1) {
    printf("Error: Missing project name!\n\nUsage:\n\n   cgen <project-name>\n\n");
    return 0;
  }

  char* project = argv[1];

  if (stat(project, &st) != -1) {
    printf("Error: Folder %s already exist!", project);
    return 0;
  }

  mkdir(project, 0700);

  char* mkfile;
  asprintf(&mkfile, "%s/Makefile", project);
  char* mksrc;
  asprintf(&mksrc, "PROJECT=%s\n%s", project, MAKEFILE_SRC);
  FILE* mkdesc = fopen(mkfile, "w+");
  fprintf(mkdesc, "%s", mksrc);
  fclose(mkdesc);

  char* mainfile;
  asprintf(&mainfile, "%s/%s.c", project, project);
  FILE* maindesc = fopen(mainfile, "w+");
  fprintf(maindesc, "%s", MAIN_SRC);
  fclose(maindesc);
  
  return 0;
}
