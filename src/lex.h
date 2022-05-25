#ifndef LEX_H
#define LEX_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "file.h"
#include "token.h"

TokenStream *lex(FILE *src);

#endif
