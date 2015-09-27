/*  -*- Last-Edit:  Mon Dec  7 10:31:51 1992 by Tarak S. Goradia; -*- */

extern void	exit();
# include <stdio.h>

void	Caseerror();

//typedef char char;
# define false 0
# define true  1
# define NULL 0

# define MAXSTR 100
# define MAXPAT MAXSTR

# define ENDSTR  '\0'
# define ESCAPE  '@'
# define CLOSURE '*'
# define BOL     '%'
# define EOL     '$'
# define ANY     '?'
# define CCL     '['
# define CCLEND  ']'
# define NEGATE  '^'
# define NCCL    '!'
# define LITCHAR 'c'
# define DITTO   -1
# define DASH    '-'

# define TAB     9
# define NEWLINE 10

# define CLOSIZE 1

typedef char	character;
typedef char string[MAXSTR];
#define SCORE
#ifdef SCORE
#include <score.h>
int MAX = 64;
char *my_fgets(char *s, int size, FILE *stream){
    int n = (MAX+1 < size)? MAX+1 : size;
    int i;
    if (MAX <= 0){
        return NULL;
    }
    for (i=0; i<n-1; i++){
        char var_name[10];
        snprintf(var_name, sizeof(var_name), "stdin[%d]", i);
        SCORE_char(s[i], var_name);
        MAX--;
        if (s[i] == '\n'){
            i++;
            break;
        }
    }
    s[i] = 0;
    return s;
}
#endif
char
getline_(s, maxsize)
char	*s;
int	maxsize;
{
    char *result;
#ifdef SCORE
    result = my_fgets(s, maxsize, stdin);
#else
    result = fgets(s, maxsize, stdin);
#endif
    return (result != NULL);
}
int
addstr(c, outset, j, maxset)
char	c;
char	*outset;
int	*j;
int	maxset;
{
    char	result;
    if (*j >= maxset)
	result = false;
    else {
	outset[*j] = c;
	*j = *j + 1;
	result = true;
    }
    return result;
}

char
esc(s, i)
char 	*s;
int	*i;
{
    char	result;
    if (s[*i] != ESCAPE)
	result = s[*i];
    else
	if (s[*i + 1] == ENDSTR)
	    result = ESCAPE;
	else 
	{
	    *i = *i + 1;
	    if (s[*i] == 'n')
		result = NEWLINE;
	    else
		if (s[*i] == 't')
		    result = TAB;
		else
		    result = s[*i];
	}
    return result;
}

void change();

 void
dodash(delim, src, i, dest, j, maxset)
char	delim;
char	*src;
int	*i;
char	*dest;
int	*j;
int	maxset;
{
    int	k;
    char	junk;
    char	escjunk;

    while ((src[*i] != delim) && (src[*i] != ENDSTR)) 
    {
	if (src[*i - 1] == ESCAPE) {
	    escjunk = esc(src, i);
	    junk = addstr(escjunk, dest, j, maxset);
	} else	
	    if (src[*i] != DASH)
		junk = addstr(src[*i], dest, j, maxset);
	    else if (*j <= 1 || src[*i + 1] == ENDSTR)
		junk = addstr(DASH, dest, j, maxset);
	    else if ((isalnum(src[*i - 1])) && (isalnum(src[*i + 1])) 
		&& (src[*i - 1] <= src[*i + 1]))
		{
		    for (k = src[*i-1]+1; k<=src[*i+1]; k++) 
		    {
			junk = addstr(k, dest, j, maxset);
		    }	
		    *i = *i + 1;	
		} 
	    else	
		junk = addstr(DASH, dest, j, maxset);
	(*i) = (*i) + 1;
    }
}

char
getccl(arg, i, pat, j)
char	*arg;
int	*i;
char	*pat;
int	*j;
{
    int	jstart;
    char	junk;

    *i = *i + 1;
    if (arg[*i] == NEGATE) {
	junk = addstr(NCCL, pat, j, MAXPAT);
	*i = *i + 1;
    } else
	junk = addstr(CCL, pat, j, MAXPAT);
    jstart = *j;
    junk = addstr(0, pat, j, MAXPAT);
    dodash(CCLEND, arg, i, pat, j, MAXPAT);
    pat[jstart] = *j - jstart - 1;
    return (arg[*i] == CCLEND);
}

 void
stclose(pat, j, lastj)
char	*pat;
int	*j;
int	lastj;
{
    int	jt;
    int	jp;
    char	junk;


    for (jp = *j - 1; jp >= lastj ; jp--) 
    {
	jt = jp + CLOSIZE;
	junk = addstr(pat[jp], pat, &jt, MAXPAT);
    }
    *j = *j + CLOSIZE;
    pat[lastj] = CLOSURE;
}

char in_set_2(c)
char c;
{
  return (c == BOL || c == EOL || c == CLOSURE);
}      

char in_pat_set(c)
char c;
{
  return (   c == LITCHAR || c == BOL  || c == EOL || c == ANY 
          || c == CCL     || c == NCCL || c == CLOSURE);
}      

int
makepat(arg, start, delim, pat)
char	*arg;
int	start;
char	delim;
char	*pat;
{
    int	result;
    int	i, j, lastj, lj;
    char	done, junk;
    char	getres;
    char	escjunk;

    j = 0;
    i = start;
    lastj = 0;
    done = false;
    while ((!done) && (arg[i] != delim) && (arg[i] != ENDSTR)) {
	lj = j;
	if ((arg[i] == ANY))
	    junk = addstr(ANY, pat, &j, MAXPAT);
	else if ((arg[i] == BOL) && (i == start))
	    junk = addstr(BOL, pat, &j, MAXPAT);
	else if ((arg[i] == EOL) && (arg[i+1] == delim))
	    junk = addstr(EOL, pat, &j, MAXPAT);
	else if ((arg[i] == CCL)) 
	{
	    getres = getccl(arg, &i, pat, &j);
	    done = (char)(getres == false);
	} 
	else if ((arg[i] == CLOSURE) && (i > start)) 
	{
	    lj = lastj;
	    if (in_set_2(pat[lj]))
		done = true;
	    else
		stclose(pat, &j, lastj);
	} 
	else 
	{
	    junk = addstr(LITCHAR, pat, &j, MAXPAT);
	    escjunk = esc(arg, &i);
	    junk = addstr(escjunk, pat, &j, MAXPAT);
	}
	lastj = lj;
	if ((!done))
	    i = i + 1;
    }	
    junk = addstr(ENDSTR, pat, &j, MAXPAT);
    if ((done) || (arg[i] != delim))
	result = 0;
    else
	if ((!junk))
	    result = 0;
	else
	    result = i;
    return result;
}

int
getpat(arg, pat)
char*	arg;
char*	pat;
{
    int	makeres;

    makeres = makepat(arg, 0, ENDSTR, pat);
    return (makeres > 0);
}

int
makesub(arg, from, delim, sub)
	char*	arg;
	int	from;
	character	delim;
	char*	sub;
{
    int  result;
    int	i, j;
    char	junk;
    character	escjunk;

    j = 0;
    i = from;
    while ((arg[i] != delim) && (arg[i] != ENDSTR)) {
	if ((arg[i] == (unsigned)('&')))
	    junk = addstr(DITTO, sub, &j, MAXPAT);
	else {
	    escjunk = esc(arg, &i);
	    junk = addstr(escjunk, sub, &j, MAXPAT);
	}
	i = i + 1;
    }
    if (arg[i] != delim)
	result = 0;
    else {
	junk = addstr(ENDSTR, &(*sub), &j, MAXPAT);
	if ((!junk))
	    result = 0;
	else
	    result = i;
    }	
    return result;
}

char
getsub(arg, sub)
	char*	arg;
	char*	sub;
{
    int	makeres;

    makeres = makesub(arg, 0, ENDSTR, sub);
    return (makeres > 0);
}

void subline();

 char
locate(c, pat, offset)
	character	c;
	char *	pat;
	int	offset;
{
    int	i;
    char flag;

    flag = false;
    i = offset + pat[offset];
    while ((i > offset))
    {
	if (c == pat[i]) {
	    flag = true;
	    i = offset;
	} else
	    i = i - 1;
    }
    return flag;
}

char
omatch(lin, i, pat, j)
	char*	lin;
	int	*i;
	char*	pat;
	int	j;
{
    char	advance;
    char result;
    
    advance = -1;
    if ((lin[*i] == ENDSTR))
	result = false;
    else 
    {
	if (!in_pat_set(pat[j]))
	{
	    (void)fprintf(stdout, "in omatch: can't happen\n");
	    abort();	
	} else
	{
	     switch (pat[j]) 
	     {			
	     case LITCHAR:
		 if (lin[*i] == pat[j + 1])
		     advance = 1;
		 break ;	
	     case BOL:
		 if (*i == 0)
		     advance = 0;
		 break ;
	     case ANY:
		 if (lin[*i] != NEWLINE)
		     advance = 1;
		 break ;
	     case EOL:
		 if (lin[*i] == NEWLINE)
		     advance = 0;
		 break ;
	     case CCL:
		 if (locate(lin[*i], pat, j + 1))
		     advance = 1;	
		 break ;
	     case NCCL:
		 if ((lin[*i] != NEWLINE) && (!locate(lin[*i], pat, j+1)))
		     advance = 1;	
		 break ;
	     default:
		 Caseerror(pat[j]);
	     };
	 }	
    }
    if ((advance >= 0)) 
    {
	*i = *i + advance;
	result = true;
    } else
	result = false;
    return result;
}


patsize(pat, n)
	char*	pat;
	int	n;
{
    int size;
    if (!in_pat_set(pat[n])) {
	(void)fprintf(stdout, "in patsize: can't happen\n");
	abort();
    } else
	switch (pat[n]) 
	{
	case LITCHAR: size = 2; break;
	    
	case BOL:  case EOL:  case ANY:
	    size = 1;
	    break;
	case CCL:  case NCCL:
	    size = pat[n + 1] + 2;
	    break ;
	case CLOSURE:
	    size = CLOSIZE;
	    break ;
	default:
	    Caseerror(pat[n]);
	}
    return size;
}

int
amatch(lin, offset, pat, j)
	char*	lin;
	int	offset;
	char*	pat;
	int	j;
{
    int	i, k;
    char	result, done;

    done = false;
    while ((!done) && (pat[j] != ENDSTR))
	if ((pat[j] == CLOSURE)) {
	    j = j + patsize(pat, j);
	    i = offset;
	    while ((!done) && (lin[i] != ENDSTR)) {
		result = omatch(lin, &i, pat, j);
		if (!result)	
		    done = true;
	    }
	    done = false;
	    while ((!done) && (i >= offset)) {
		k = amatch(lin, i, pat, j + patsize(pat, j));
		if ((k >= 0))
		    done = true;
		else
		    i = i - 1;
	    }
	    offset = k;
	    done = true;
	} else {
	    result = omatch(lin, &offset, pat, j);
	    if ((!result)) {	
		offset = -1;
		done = true;
	    } else
		j = j + patsize(pat, j);
	}
     return offset;
}

void
putsub(lin, s1, s2, sub)
  char *	lin;
  int	s1, s2;
  char *	sub;
{
    int	i;
    int		j;

    i = 0;
    while ((sub[i] != ENDSTR)) {
	if ((sub[i] == DITTO))
	    for (j = s1; j < s2; j++) 
	    {
		fputc(lin[j],stdout);
	    }	
	else	
	{
	    fputc(sub[i],stdout);
	}
	i = i + 1;
    }
}

void
subline(lin, pat, sub)
 char	*lin;
 char   *pat;
 char   *sub;
{	
	int	i, lastm, m;

	lastm = -1;
	i = 0;
	while ((lin[i] != ENDSTR)) 
	{
	    m = amatch(lin, i, pat, 0);
	    if ((m >= 0) && (lastm != m)) {
		putsub(lin, i, m, sub);
		lastm = m;
	    }
	    if ((m == -1) || (m == i)) {
		fputc(lin[i],stdout);
		i = i + 1;
	    } else
		i = m;
	}
}

 void
change(pat, sub)
char *pat, *sub;
{
    string  line;
    char result;
    
    result = getline_(line, MAXSTR);
    while ((result)) {
	subline(line, pat, sub);
	result = getline_(line, MAXSTR);
    }
}

main(argc, argv)
int	argc;
char	*argv[];
{
   string pat, sub;
   char result;
#ifdef SCORE
   int i;
   SCORE_int(argc, "argc");
#endif
   if (argc < 2) 
   {
       (void)fprintf(stdout, "usage: change from [to]\n");
       exit(1);
   };
#ifdef SCORE
   argv[1] = malloc(23+1);
   argv[1][23] = 0;
   for (i=0; i<23; i++){
       char var_name[20];
       snprintf(var_name, sizeof(var_name), "argv[1][%d]", i);
       SCORE_char(argv[1][i], var_name);
   }
#endif
   //printf("pat: %s\n", argv[1]);
   result = getpat(argv[1], pat);
   if (!result)
   {
       (void)fprintf(stdout, "change: illegal \"from\" pattern\n");
       exit(2);
   }

   if (argc >= 3)
   {
#ifdef SCORE
       argv[2] = malloc(28+1);
       argv[2][28] = 0;
       for (i=0; i<28; i++){
           char var_name[20];
           snprintf(var_name, sizeof(var_name), "argv[2][%d]", i);
           SCORE_char(argv[2][i], var_name);
       }
#endif
       //printf("sub: %s\n", argv[2]);
       result = getsub(argv[2], sub);
       if (!result)
       {	
	   (void)fprintf(stdout, "change: illegal \"to\" string\n");
	   exit(3);
       }
   } else
   {
       sub[0] = '\0';
   }
   
   change(pat, sub);
   return 0;
}

void
Caseerror(n)
	int	n;
{
	(void)fprintf(stdout, "Missing case limb: line %d\n", n);
	exit(4);
}
