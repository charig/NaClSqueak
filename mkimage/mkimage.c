/* Convert image file to C data

Copyright (c) 2011 by Yoshiki Ohshima
All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the 'Software'),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, provided that the above copyright notice(s) and this
permission notice appear in all copies of the Software.  Acknowledgement
of the use of this Software in supporting documentation would be
appreciated but is not required.

THE SOFTWARE IS PROVIDED 'AS IS'.  USE ENTIRELY AT YOUR OWN RISK.
*/

#include <stdio.h>

static char header[] = "\
#include <stdint.h>\n\
\n\
unsigned char default_image_file_buffer[] = {\n\
  ";

static char footer[] = "\n\
};\n\
\n\
int32_t default_image_file_size = sizeof(default_image_file_buffer);\n\
";

int
main(int argc, char **argv)
{
  FILE *output= stdout;
  FILE *input= stdin;

  int count = 0;
  int c;

  if (argc == 3) {
    if (!(output= fopen(argv[2], "w"))) {
       perror(*argv);
       return 1;
    }
  }
  if (argc > 1) {
    if (argv[1][0] == '-' && argv[1][1] == 0) {
      ;
    } else {
      if (!(input= fopen(argv[1], "rb"))) {
        perror(*argv);
	return 1;
      }
    }
  }

  fputs(header, output);

  while ((c = fgetc(input)) >= 0) {
    fprintf(output, "%u,", c);
    if (!(++count % 20)) {
      fprintf(output, "\n  ");
    }
  }
  fputs(footer, output);

  if (output != stdout) {
    fclose(output);
  }

  return 0;
}
