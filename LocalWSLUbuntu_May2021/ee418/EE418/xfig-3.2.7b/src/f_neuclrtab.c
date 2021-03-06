/*
 * FIG : Facility for Interactive Generation of figures
 * Copyright (c) 1994 Anthony Dekker
 * Parts Copyright (c) 1989-2007 by Brian V. Smith
 *
 * [NEUQUANT Neural-Net quantization algorithm by Anthony Dekker, 1994.
 * See "Kohonen neural networks for optimal colour quantization"
 * in "Network: Computation in Neural Systems" Vol. 5 (1994) pp 351-367.
 * for a discussion of the algorithm.]
 *
 * Any party obtaining a copy of these files is granted, free of charge, a
 * full and unrestricted irrevocable, world-wide, paid up, royalty-free,
 * nonexclusive right and license to deal in this software and documentation
 * files (the "Software"), including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense and/or sell copies of
 * the Software, and to permit persons who receive copies from any such
 * party to do so, with the only requirement being that the above copyright
 * and this permission notice remain intact.
 *
 */


/*
 * Neural-Net quantization algorithm based on work of Anthony Dekker
 */

#include "fig.h"
#include "resources.h"
#include "object.h"
#include "f_neuclrtab.h"
#include "f_util.h"

/* #include <stdio.h>	inluded in fig.h */
#include <limits.h>	/* INT_MAX */

static	void initnet(void);
static	void learn(void);
static	void unbiasnet(void);
static	void cpyclrtab(void);
static	void inxbuild(void);
static	int  contest(register int b, register int g, register int r);
static	void alterneigh(int rad, int i, register int b, register int g, register int r);
static	void altersingle(register int alpha, register int i, register int b, register int g, register int r);
static	int  inxsearch(register int b, register int g, register int r);

#define MAXNETSIZE	256

/* our color table (global) */
BYTE	clrtab[256][3];

static int	netsize;

#ifndef DEFSMPFAC
#  ifdef SPEED
#    define DEFSMPFAC	(240/SPEED+3)
#  else
#    define DEFSMPFAC	30	/* only sample every 30th pixel */
#  endif /* SPEED */
#endif /* DEFSMPFAC */

int	samplefac = DEFSMPFAC;	/* sampling factor */

		/* Samples array starts off holding spacing between adjacent
		 * samples, and ends up holding actual BGR sample values.
		 */
static BYTE	*thesamples;
static int	nsamples;
static BYTE	*cursamp;
static long	skipcount;

#define MAXSKIP		(1<<24-1)

#define nskip(sp)	((long)(sp)[0]<<16|(long)(sp)[1]<<8|(long)(sp)[2])

#define setskip(sp,n)	((sp)[0]=(n)>>16,(sp)[1]=((n)>>8)&255,(sp)[2]=(n)&255)

/* npixels is the total number of pixels defined */


void neu_dith_colrs (register BYTE *bs, register COLR (*cs), int n);

int
neu_init(long int npixels)		/* initialize our sample array */

{
	if (npixels < MIN_NEU_SAMPLES)
		samplefac = 1;
	else
		samplefac = DEFSMPFAC;
	return neu_init2(npixels);
}

int
neu_init2(long int npixels)		/* initialize our sample array */

{
	register int	nsleft;
	register long	sv;
	double	rval, cumprob;
	long	npleft;

	nsamples = npixels/samplefac;
	if (nsamples < MIN_NEU_SAMPLES)
		return((int)-MIN_NEU_SAMPLES/nsamples-1); /* THIS IS DIFFERENT FROM THE ORIGINAL -1 */
	thesamples = (BYTE *)malloc(nsamples*3);
	if (thesamples == NULL)
		return(-1);
	cursamp = thesamples;
	npleft = npixels;
	nsleft = nsamples;
	while (nsleft) {
		rval = frandom();	/* random distance to next sample */
		sv = 0;
		cumprob = 0.;
		while ((cumprob += (1.-cumprob)*nsleft/(npleft-sv)) < rval)
			sv++;
		if (nsleft == nsamples)
			skipcount = sv;
		else {
			setskip(cursamp, sv);
			cursamp += 3;
		}
		npleft -= sv+1;
		nsleft--;
	}
	setskip(cursamp, npleft);	/* tag on end to skip the rest */
	cursamp = thesamples;
	return(0);
}


void
neu_pixel(register BYTE *col)			/* add pixel to our samples */
{
	if (!skipcount--) {
		skipcount = nskip(cursamp);
		cursamp[0] = col[N_BLU];
		cursamp[1] = col[N_GRN];
		cursamp[2] = col[N_RED];
		cursamp += 3;
	}
}


void
neu_colrs(register COLR (*cs), register int n)	/* add a scanline to our samples */
{
	while (n > skipcount) {
		cs += skipcount;
		n -= skipcount+1;
		skipcount = nskip(cursamp);
		cursamp[0] = cs[0][N_BLU];
		cursamp[1] = cs[0][N_GRN];
		cursamp[2] = cs[0][N_RED];
		cs++;
		cursamp += 3;
	}
	skipcount -= n;
}


int
neu_clrtab(int ncolors)		/* make new color table using ncolors */
{
	netsize = ncolors;
	if (netsize > MAXNETSIZE) netsize = MAXNETSIZE;
	initnet();
	learn();
	unbiasnet();
	cpyclrtab();
	inxbuild();
				/* we're done with our samples */
	free((char *)thesamples);
				/* reset dithering function */
	neu_dith_colrs((BYTE *)NULL, (COLR *)NULL, 0);
				/* return new color table size */
	return(netsize);
}


int
neu_map_pixel(register BYTE *col)		/* get pixel for color */
{
	return(inxsearch(col[N_BLU],col[N_GRN],col[N_RED]));
}


void neu_map_colrs(register BYTE *bs, register COLR (*cs), register int n)	/* convert a scanline to color index values */
{
	while (n-- > 0) {
		*bs++ = inxsearch(cs[0][N_BLU],cs[0][N_GRN],cs[0][N_RED]);
		cs++;
	}
}


void neu_dith_colrs(register BYTE *bs, register COLR (*cs), int n)	/* convert scanline to dithered index values */
{
	static short	(*cerr)[3] = NULL;
	static int	N = 0;
	int	err[3], errp[3];
	register int	x, i;

	if (n != N) {		/* get error propogation array */
		if (N) {
			free((char *)cerr);
			cerr = NULL;
		}
		if (n)
			cerr = (short (*)[3])malloc(3*n*sizeof(short));
		if (cerr == NULL) {
			N = 0;
			neu_map_colrs(bs, cs, n);
			return;
		}
		N = n;
		bzero((char *)cerr, 3*N*sizeof(short));
	}
	err[0] = err[1] = err[2] = 0;
	for (x = 0; x < n; x++) {
		for (i = 0; i < 3; i++) {	/* dither value */
			errp[i] = err[i];
			err[i] += cerr[x][i];
#ifdef MAXERR
			if (err[i] > MAXERR) err[i] = MAXERR;
			else if (err[i] < -MAXERR) err[i] = -MAXERR;
#endif /* MAXERR */
			err[i] += cs[x][i];
			if (err[i] < 0) err[i] = 0;
			else if (err[i] > 255) err[i] = 255;
		}
		bs[x] = inxsearch(err[N_BLU],err[N_GRN],err[N_RED]);
		for (i = 0; i < 3; i++) {	/* propagate error */
			err[i] -= clrtab[bs[x]][i];
			err[i] /= 3;
			cerr[x][i] = err[i] + errp[i];
		}
	}
}

/* The following was adapted and modified slightly from the original */

#define bool		int
#define false		0
#define true		1

/* network defs */
#define maxnetpos	(netsize-1)
#define netbiasshift	4			/* bias for colour values */
#define ncycles		100			/* no. of learning cycles */

/* defs for freq and bias */
#define intbiasshift    16			/* bias for fractions */
#define intbias		(((int) 1)<<intbiasshift)
#define gammashift	10			/* gamma = 1024 */
#define gamma		(((int) 1)<<gammashift)
#define betashift	10
#define beta		(intbias>>betashift)	/* beta = 1/1024 */
#define betagamma	(intbias<<(gammashift-betashift))

/* defs for decreasing radius factor */
#define initrad		(netsize>>3)		/* for 256 cols, radius starts */
#define radiusbiasshift	6			/* at 32.0 biased by 6 bits */
#define radiusbias	(((int) 1)<<radiusbiasshift)
#define initradius	(initrad*radiusbias)	/* and decreases by a */
#define radiusdec	30			/* factor of 1/30 each cycle */

/* defs for decreasing alpha factor */
#define alphabiasshift	10			/* alpha starts at 1.0 */
#define initalpha	(((int) 1)<<alphabiasshift)
int alphadec;					/* biased by 10 bits */

/* radbias and alpharadbias used for radpower calculation */
#define radbiasshift	8
#define radbias		(((int) 1)<<radbiasshift)
#define alpharadbshift  (alphabiasshift+radbiasshift)
#define alpharadbias    (((int) 1)<<alpharadbshift)

/* four primes near 500 - assume no image has a length so large */
/* that it is divisible by all four primes */
#define prime1		499
#define prime2		491
#define prime3		487
#define prime4		503

/* hardwire these */

#define thepicture	thesamples
#define lengthcount	(nsamples*3)
#define samplefac	1		/* this MUST be 1 */

typedef int pixel[4];  /* BGRc */
pixel network[MAXNETSIZE];

int netindex[256];	/* for network lookup - really 256 */

int bias [MAXNETSIZE];	/* bias and freq arrays for learning */
int freq [MAXNETSIZE];
int radpower[MAXNETSIZE>>3];	/* radpower for precomputation */


/* initialise network in range (0,0,0) to (255,255,255) */

static void
initnet(void)
{
	register int i;
	register int *p;

	for (i=0; i<netsize; i++) {
		p = network[i];
		p[0] = p[1] = p[2] = (i << (netbiasshift+8))/netsize;
		freq[i] = intbias/netsize;  /* 1/netsize */
		bias[i] = 0;
	}
}


/* do after unbias - insertion sort of network and build netindex[0..255] */

static void
inxbuild(void)
{
	register int i,j,smallpos,smallval;
	register int *p,*q;
	int previouscol,startpos;

	previouscol = 0;
	startpos = 0;
	for (i=0; i<netsize; i++) {
		p = network[i];
		smallpos = i;
		smallval = p[1];	/* index on g */
		/* find smallest in i..netsize-1 */
		for (j=i+1; j<netsize; j++) {
			q = network[j];
			if (q[1] < smallval) {	/* index on g */
				smallpos = j;
				smallval = q[1]; /* index on g */
			}
		}
		q = network[smallpos];
		/* swap p (i) and q (smallpos) entries */
		if (i != smallpos) {
			j = q[0];   q[0] = p[0];   p[0] = j;
			j = q[1];   q[1] = p[1];   p[1] = j;
			j = q[2];   q[2] = p[2];   p[2] = j;
			j = q[3];   q[3] = p[3];   p[3] = j;
		}
		/* smallval entry is now in position i */
		if (smallval != previouscol) {
			netindex[previouscol] = (startpos+i)>>1;
			for (j=previouscol+1; j<smallval; j++) netindex[j] = i;
			previouscol = smallval;
			startpos = i;
		}
	}
	netindex[previouscol] = (startpos+maxnetpos)>>1;
	for (j=previouscol+1; j<256; j++) netindex[j] = maxnetpos; /* really 256 */
}

static int
inxsearch(register int b, register int g, register int r)  /* accepts real BGR values after net is unbiased */

{
	register int i,j,dist,a,bestd;
	register int *p;
	int best;

	bestd = 1000;	/* biggest possible dist is 256*3 */
	best = -1;
	i = netindex[g]; /* index on g */
	j = i-1;	 /* start at netindex[g] and work outwards */

	while ((i<netsize) || (j>=0)) {
		if (i<netsize) {
			p = network[i];
			dist = p[1] - g;	/* inx key */
			if (dist >= bestd) i = netsize; /* stop iter */
			else {
				i++;
				if (dist<0) dist = -dist;
				a = p[0] - b;   if (a<0) a = -a;
				dist += a;
				if (dist<bestd) {
					a = p[2] - r;   if (a<0) a = -a;
					dist += a;
					if (dist<bestd) {bestd=dist; best=p[3];}
				}
			}
		}
		if (j>=0) {
			p = network[j];
			dist = g - p[1]; /* inx key - reverse dif */
			if (dist >= bestd) j = -1; /* stop iter */
			else {
				j--;
				if (dist<0) dist = -dist;
				a = p[0] - b;   if (a<0) a = -a;
				dist += a;
				if (dist<bestd) {
					a = p[2] - r;   if (a<0) a = -a;
					dist += a;
					if (dist<bestd) {bestd=dist; best=p[3];}
				}
			}
		}
	}
	return(best);
}


/* finds closest neuron (min dist) and updates freq */
/* finds best neuron (min dist-bias) and returns position */
/* for frequently chosen neurons, freq[i] is high and bias[i] is negative */
/* bias[i] = gamma*((1/netsize)-freq[i]) */

static int
contest(register int b, register int g, register int r)	/* accepts biased BGR values */

{
	register int i,dist,a,biasdist,betafreq;
	int bestpos,bestbiaspos,bestd,bestbiasd;
	register int *p,*f, *n;

	bestd = INT_MAX;
	bestbiasd = bestd;
	bestpos = -1;
	bestbiaspos = bestpos;
	p = bias;
	f = freq;

	for (i=0; i<netsize; i++) {
		n = network[i];
		dist = n[0] - b;   if (dist<0) dist = -dist;
		a = n[1] - g;   if (a<0) a = -a;
		dist += a;
		a = n[2] - r;   if (a<0) a = -a;
		dist += a;
		if (dist<bestd) {bestd=dist; bestpos=i;}
		biasdist = dist - ((*p)>>(intbiasshift-netbiasshift));
		if (biasdist<bestbiasd) {bestbiasd=biasdist; bestbiaspos=i;}
		betafreq = (*f >> betashift);
		*f++ -= betafreq;
		*p++ += (betafreq<<gammashift);
	}
	freq[bestpos] += beta;
	bias[bestpos] -= betagamma;
	return(bestbiaspos);
}


/* move neuron i towards (b,g,r) by factor alpha */

static void
altersingle(register int alpha, register int i, register int b, register int g, register int r)	/* accepts biased BGR values */

{
	register int *n;

	n = network[i];		/* alter hit neuron */
	*n -= (alpha*(*n - b)) / initalpha;
	n++;
	*n -= (alpha*(*n - g)) / initalpha;
	n++;
	*n -= (alpha*(*n - r)) / initalpha;
}


/* move neurons adjacent to i towards (b,g,r) by factor */
/* alpha*(1-((i-j)^2/[r]^2)) precomputed as radpower[|i-j|]*/

static void
alterneigh(int rad, int i, register int b, register int g, register int r)	/* accents biased BGR values */


{
	register int j,k,lo,hi,a;
	register int *p, *q;

	lo = i-rad;   if (lo<-1) lo = -1;
	hi = i+rad;   if (hi>netsize) hi=netsize;

	j = i+1;
	k = i-1;
	q = radpower;
	while ((j<hi) || (k>lo)) {
		a = (*(++q));
		if (j<hi) {
			p = network[j];
			*p -= (a*(*p - b)) / alpharadbias;
			p++;
			*p -= (a*(*p - g)) / alpharadbias;
			p++;
			*p -= (a*(*p - r)) / alpharadbias;
			j++;
		}
		if (k>lo) {
			p = network[k];
			*p -= (a*(*p - b)) / alpharadbias;
			p++;
			*p -= (a*(*p - g)) / alpharadbias;
			p++;
			*p -= (a*(*p - r)) / alpharadbias;
			k--;
		}
	}
}


static void
learn(void)
{
	register int i,j,b,g,r;
	int radius,rad,alpha,step,delta,samplepixels;
	register unsigned char *p;
	unsigned char *lim;

	alphadec = 30 + ((samplefac-1)/3);
	p = thepicture;
	lim = thepicture + lengthcount;
	samplepixels = lengthcount/(3*samplefac);
	delta = samplepixels/ncycles;
	alpha = initalpha;
	radius = initradius;

	rad = radius >> radiusbiasshift;
	if (rad <= 1) rad = 0;
	for (i=0; i<rad; i++)
		radpower[i] = alpha*(((rad*rad - i*i)*radbias)/(rad*rad));

	if ((lengthcount%prime1) != 0) step = 3*prime1;
	else {
		if ((lengthcount%prime2) !=0) step = 3*prime2;
		else {
			if ((lengthcount%prime3) !=0) step = 3*prime3;
			else step = 3*prime4;
		}
	}

	i = 0;
	while (i < samplepixels) {
		b = p[0] << netbiasshift;
		g = p[1] << netbiasshift;
		r = p[2] << netbiasshift;
		j = contest(b,g,r);

		altersingle(alpha,j,b,g,r);
		if (rad) alterneigh(rad,j,b,g,r);   /* alter neighbours */

		p += step;
		if (p >= lim) p -= lengthcount;

		i++;
		if (i%delta == 0) {
			alpha -= alpha / alphadec;
			radius -= radius / radiusdec;
			rad = radius >> radiusbiasshift;
			if (rad <= 1) rad = 0;
			for (j=0; j<rad; j++)
				radpower[j] = alpha*(((rad*rad - j*j)*radbias)/(rad*rad));
		}
	}
}

/* unbias network to give 0..255 entries */
/* which can then be used for colour map */
/* and record position i to prepare for sort */

static void
unbiasnet(void)
{
	int i,j;

	for (i=0; i<netsize; i++) {
		for (j=0; j<3; j++)
			network[i][j] >>= netbiasshift;
		network[i][3] = i; /* record colour no */
	}
}

/* Don't do this until the network has been unbiased */

static void
cpyclrtab(void)
{
	register int i,j,k;

	for (j=0; j<netsize; j++) {
		k = network[j][3];
		for (i = 0; i < 3; i++)
			clrtab[k][i] = network[j][2-i];
	}
}
