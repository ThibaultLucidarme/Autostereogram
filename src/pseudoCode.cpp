
#define round(X) (int)((X)+0.5)
#define DPI 72
#define E round(2.5*DPI)
#define mu (1/3.0)
#define separation(Z) round((1-mu*Z)*E/(2-mu*Z))
#define far separation(0)
#define maxX 256
#define maxY 256

/*
ENABLE/DISABLE OpenMP

If you do not compile with -fopenmp option, you won't get the parallel code.
#ifndef SINGLETHREADED
#pragma omp
#endif

When you compile, add -DSINGLETHREADED to disable OpenMP:

cc  -DSINGLETHREADED <other flags go here> code.c

*/

// TILING in OpenCV
// http://funwithkinect.blogspot.com.br/2012/02/copying-and-tiling-with-opencv.html
//http://docs.opencv.org/3.0-rc1/d2/de8/group__core__array.html#ga496c3860f3ac44c40b48811333cfda2d

/*

eyes    0  eyesep  0
         \        /
obsdist   \      /
           \sep /
screen   ===========
featureZ     \/       
3dobject  _n_nm_n_m_


eyesep = eyeSeparation // separation between the eyes
sep = eyeSeparationOnScreen // projection of the eye separation on the screen when looking at an object
obsdist = eye2screenDist // distance from observer to the screen
featureZ = objectDepth // depths of the object heightmap

//
//   sep = (eyesep * featureZ) / (featureZ + obsdist)
//

*/

/*
//
//  GENERAL ALGORITHM
//

Start with a "depth-map" - array of z-values for each (x,y) point on the screen.
Working left to right along each horizontal line, for each point on the depth-map identify the associated pair of screen points and `link' them - give each a reference to its other half.
Again working from left to right, assign a random colour to each unlinked point, and colour linked points according to the colour of their (already coloured) other half.

*/


// xdpi=75   // x-resolution of typical monitor
// ydpi=75   // y-resolution of typical monitor
// width  // width of display in pixels
// height // height of display in pixels

// obsDist=xdpi*12; // 12inchs * dot/inch resolution = obsdist in dots - EXPERIMENT WITH VALUE. IS IT THE OPTIMAL DISTANCE TO SEE THE OBJECT APPEAR?
// eyeSep=xdpi*2.5; //2.5 inches * dot/inch resolution = eyesep in dots



/*
range of depths used in a stereogram should be chosen carefully
good starting point is to make the maximum depth equal to the observer distance
From equation (1) it can be shown that the minimum permissible depth in the stereogram consistent with the first rule
is given by:

//   mindepth=(sepfactor*maxdepth*obsdist)/((1-sepfactor)*maxdepth+obsdist)
where sepfactor is the ratio of the smallest allowable separation to the maximum separation used. A typical value would be 0.55.


if a depth-map height-function is used then the following formula should be used:   

//   featureZ=maxdepth-h(x,y)*(maxdepth-mindepth)/256 

where h(x,y) is a height function with values from 0 (farthest) to 255 (nearest). 
h may be obtained from a grey scale depth-map picture,  
maxdepth is the farthest depth (corresponding to 0 in the height function), 
and  mindepth is the nearest depth, (corresponding to 255 in the height function).

*/
 


void DrawAutoStereogram(float Z[][])
{
 int patHeight=patternbmp->GetHeight();

 const maxwidth=640*6;  // allow space for up to 6 times oversampling
 int xdpi=75; int ydpi=75;

 int yShift=ydpi/16;

 int width=640;
 int height=480;

 int oversam=4; // oversampling ratio
 int lookL[maxwidth]; int lookR[maxwidth];
 COLOUR colour[maxwidth], col;
 int lastlinked; int i;


}


// SPEED-UPS

// Colour palette matching - a major speedup for palette-based displays. If the display device supports 15- or 24-bit
// colour (32768 or 16.7million colours) then displaying in-between colours presents no difficulty. In reality though,
// common displays use a palette of just 256 colours. Provided there is a good tonal range in the palette of the
// original pattern then the nearest available colour can be used in place of the ideal in-between. However, the process
// of matching nearest colours is intrinsically slow; prior to optimisation in my program, calls to Windows' built-in
// GetNearestPaletteIndex() accounted for 60% of the run-time! In SISgen, I quantised the specification of each
// requested colour to 15-bit (5-bits per R/G/B channel), and implemented a lookup-table buffer to store the results of
// previous matches. That way, the best palette-entry for a particular colour only has to be found once in the drawing
// of the whole stereogram.

// Integer maths - on general purpose computers without math co-processors, integer maths is much faster than floating
// point. (On my PC I estimate a standard float multiplication to take around 100 times longer than the equivalent
// 16-bit integer operation.) Consequently the program was written in such a way that no floating point was required
// within the main loops. In my latest program I have eliminated almost all maths in the main loop anyway by using a
// lookup table to relate image depth to stereo separation.

// GetPixel()- and SetPixel()-type calls Built-in pixel manipulation functions in most computer languages are often much
// slower than they need be - important as a stereogram may easily involve the order of a million calls! It may well be
// worth writing your own (see below).

// Machine-specific optimization. I found that it is approaching 10 times faster under Microsoft Windows to directly
// manipulate 256-colour device-independant bitmaps than to use the built-in pixel-manipulation functions on standard
// (device-specific) bitmaps. Finally, make sure any compiler options are set to optimise for fast execution - and time
// it - sometimes the compiler gets it wrong!





void Algo1 ( void )
{

  //
  // ...
  //

 for (y=0; y<height; y++)
 {
  for (x=0; x<width; x++)
  { lookL[x]=x; } // initLink to itself

  for (x=0; x<width; x++)
  {
   featureZ=<depth of image at (x,y)>; //refer to depth-map here

   // get sep from depth
   // the multiplication below is 'long' to prevent overflow errors
   sep=(int)(((long)eyeSep*featureZ)/(featureZ+obsDist));

   //get corresponding pixels from sep
   left=x-sep/2; right=left+sep;
   //link the two pixels
   if ((left>=0) && (right<width)) lookL[right]=left;
  }

  // give random color to left links and unlinked and matching color to right link
  for (x=0; x<width; x++)
  {
   if (lookL[x]==x)
    colour[x]=<random colour>; // unconstrained
   else
    colour[x]=colour[lookL[x]]; // constrained
  }

  // assign color (merge with previous for loop?)
  for (x=0; x<width; x++)
  {
   SetPixel(x,y, colour[x]);
  }

  }
}


void Algo2 ( void )
/*
Solves the problem of artifacts To the immediate right of any step that becomes deeper as you go rightwards
The problem arises because links are made even for points on the object that are only visible to one eye.

eyes   0            0
        \          /
screen  ============
          \      /
depth1  ------- /
left ray    `  /     incorrect link because only seen with 1 eye
obscured     `/       
depth2        ------- 


Given that:
- near objects obscure far ones
- stereo separation increases with depth
we can conclude that short links should always be made in preference to longer ones 



eyes       0      0
            \    /
screen  ============
              \/
depth1  -------      corrected link
               
depth2        ------- 

*/
{
  //
  // ...
  //
int lookR[maxwidth];
 BOOL vis;

 for (y=0; y<height; y++)
 {

  for (x=0; x<width; x++)
  { lookL[x]=x; lookR[x]=x; }    // clear lookR[] as well

  for (x=0; x<width; x++)
  {
   featureZ=<depth of image at (x,y)>; // refer to depth-map here

   sep=(int)(((long)eyeSep*featureZ)/(featureZ+obsDist));

   left=x-sep/2; right=left+sep;

   vis=TRUE;  // default to visible to both eyes

   if ((left>=0) && (right<width))
   {
    if (lookL[right]!=right) // right pt already linked
    {
     if (lookL[right]<left) // deeper than current
     {
      lookR[lookL[right]]=lookL[right]; // break old links
      lookL[right]=right;
     }
     else vis=FALSE;
    }
     
    if (lookR[left]!=left) // left pt already linked
    {
     if (lookR[left]>right) // deeper than current
     {
      lookL[lookR[left]]=lookR[left]; // break old links
      lookR[left]=left;
     }
     else vis=FALSE;
    }
    if (vis==TRUE) { lookL[right]=left; lookR[left]=right; } // make link
   }
  }
}
}


// USING BITMAPPED PATTERNS
void Algo3 ( void )
/*
Solves the problem of  Slopes appear as steps and curved objects appear to be made from a stack of flat planes
a pattern of random dots 600 to the inch looks like an even grey mass and the stereogram is very difficult to see because there is no large-scale detail
but a more pleasing technique is to use a pattern or picture rather than random dots as the basis for the stereogram


The pattern must be at least as wide as the maximum stereo separation otherwise there is a problem. 
You cannot just loop around and begin the pattern again because the repeat will be interpreted by the observer as three-dimensional information and artifacts will result 
- visible fragments of 3D surfaces that weren't supposed to be there
If the chosen pattern is designed to "tile" then to optimise the matching the stereogram paramters can be adjusted and/or the pattern resized in advance so that the pattern width is equal to the maximum stereo separation.

 int maxsep=(int)(((long)eyeSep*maxdepth)/(maxdepth+obsDist)); // pattern must be at least this wide

However these must not duplicate pattern already used on that line of the stereogram otherwise artifacts arise
I chose to fill-in using pattern taken from a number of lines higher or lower than the current line. 
Experiment showed that vertical offsets in increments of 1/16th inch are quite adequate to prevent the observer's brain making incorrect associations, and hence eliminate artifacts.



*/
{
 int yShift=ydpi/16;
// patternbmp->GetHeight() returns the height of the pattern in pixels.
 int patHeight=patternbmp->GetHeight();
 lastlinked=-10; // dummy initial value

  for (x=0; x<width; x++)
  {
   if (lookL[x]==x)
   {
    if (lastlinked==(x-1)) colour[x]=colour[x-1];
    else
    {
      // get pixel from pattern image instead of random
// GetPixelFromPattern(x,y) is a function that returns the colour of the pixel at (x,y) within the original pattern bitmap.
     colour[x]=GetPixelFromPattern(x % maxsep,
                                   (y+(x/maxsep)*yShift) % patHeight);
    }
   }
   else
   {
    colour[x]=colour[lookL[x]];
 
    lastlinked=x; // keep track of the last pixel to be constrained
   }
  }

}


// RESOLUTION ENHANCEMENT
void Algo4 ( void )
/*
The easiest way to implement resolution-enhancement is to process each line of the stereogram at a resolution several times greater than that of the display device, 
then merge a number of `virtual' pixels into each physical pixel for display. In this way each physical pixel takes on the average colour of its associated `virtual' pixels.

human eye at a typical reading distance (14 inches) does not exceed about 300dpi
Computationally it is convenient to set the limit at 256 depths
*/
{

oversam // oversampling ratio ie. ratio of virtual pixels to real pixels 
vwidth // the new `virtual' width 
veyeSep // eye separation in `virtual' pixels 
vmaxsep // maximum stereo separation in 'virtual' pixels
int oversam=4; // oversampling ratio
 int lookL[maxwidth]; int lookR[maxwidth];
 COLOUR colour[maxwidth], col;
 int lastlinked; int i;

 int vwidth=width*oversam;

 int obsDist=xdpi*12;
 int eyeSep=xdpi*2.5; int veyeSep=eyeSep*oversam;

 int maxdepth=xdpi*12;
 int maxsep=(int)(((long)eyeSep*maxdepth)/(maxdepth+obsDist)); // pattern must be at
                                                               // least this wide
 int vmaxsep=oversam*maxsep

 int featureZ, sep;
 int x,y, left,right;
 BOOL vis;
 

 for (y=0; y<height; y++)
 {
  for (x=0; x<vwidth; x++)
  { lookL[x]=x; lookR[x]=x; }

  for (x=0; x<vwidth; x++)
  {
   if ((x % oversam)==0) // SPEEDUP for oversampled pictures
   {
    featureZ=<depth of image at (x/oversam,y)>

    sep=(int)(((long)veyeSep*featureZ)/(featureZ+obsDist));
   }

   left=x-sep/2; right=left+sep;

   vis=TRUE;

   if ((left>=0) && (right<vwidth))
   {
    if (lookL[right]!=right) // right pt already linked
    {
     if (lookL[right]<left) // deeper than current
     {
      lookR[lookL[right]]=lookL[right]; // break old links
      lookL[right]=right;
     }
     else vis=FALSE;
    }

    if (lookR[left]!=left) // left pt already linked
    {
     if (lookR[left]>right) // deeper than current
     {
      lookL[lookR[left]]=lookR[left]; // break old links
      lookR[left]=left;
     }
     else vis=FALSE;
    }
    if (vis==TRUE) { lookL[right]=left; lookR[left]=right; } // make link
   }
  }

  lastlinked=-10; // dummy initial value

  for (x=0; x<vwidth; x++)
  {
   if (lookL[x]==x)
   {
    if (lastlinked==(x-1)) colour[x]=colour[x-1];
    else
    {
     colour[x]=GetPixelFromPattern((x % vmaxsep)/oversam,
                                   (y+(x/vmaxsep)*yShift) % patHeight);
    }
   }
   else
   {
    colour[x]=colour[lookL[x]];
 
    lastlinked=x; // keep track of the last pixel to be constrained
   }
  }

  int red, green, blue;

  for (x=0; x<vwidth; x+=oversam)
  {
   red=0; green=0; blue=0;
   
   // use average colour of virtual pixels for screen pixel
   for (i=x; i<(x+oversam); i++)
   {
    col=colour[i];
    red+=col.R;
    green+=col.G;
    blue+=col.B;
   }
   col=RGB(red/oversam, green/oversam, blue/oversam);

   SetPixel(x/oversam,y, col);
  }
 }
}




void Algo5 ( void )
/*
Solves the problem of When the pattern is applied by working from one side to the other (left to right for example), the pattern can become very distorted on the far side of the picture.
The total distortion can be reduced by using a from-the-centre-outwards approach: start with the original pattern in a vertical stripe down the centre, and mutate the pattern towards the edges. 
This also gives a much more pleasing `balanced' appearance to the work, but requires separate coding for left-to-right and right-to-left pattern application.
*/
{
 int patHeight=patternbmp->GetHeight();

 const maxwidth=640*6;  // allow space for up to 6 times oversampling
 int xdpi=75; int ydpi=75;

 int yShift=ydpi/16;

 int width=640;
 int height=480;

 int oversam=4; // oversampling ratio
 int lookL[maxwidth]; int lookR[maxwidth];
 COLOUR colour[maxwidth], col;
 int lastlinked; int i;

 int vwidth=width*oversam;

 int obsDist=xdpi*12;
 int eyeSep=xdpi*2.5; int veyeSep=eyeSep*oversam;

 int maxdepth=xdpi*12;
 int maxsep=(int)(((long)eyeSep*maxdepth)/(maxdepth+obsDist)); // pattern must be at
                                                               // least this wide
 int vmaxsep=oversam*maxsep

 int s=vwidth/2-vmaxsep/2; int poffset=vmaxsep-(s % vmaxsep);

 int featureZ, sep;
 int x,y, left,right;
 BOOL vis;
 

 for (y=0; y<height; y++)
 {
  for (x=0; x<vwidth; x++)
  { lookL[x]=x; lookR[x]=x; }

  for (x=0; x<vwidth; x++)
  {
   if ((x % oversam)==0) // SPEEDUP for oversampled pictures
   {
    featureZ=<depth of image at (x/oversam,y)>

    sep=(int)(((long)veyeSep*featureZ)/(featureZ+obsDist));
   }

   left=x-sep/2; right=left+sep;

   vis=TRUE;

   if ((left>=0) && (right<vwidth))
   {
    if (lookL[right]!=right) // right pt already linked
    {
     if (lookL[right]<left) // deeper than current
     {
      lookR[lookL[right]]=lookL[right]; // break old links
      lookL[right]=right;
     }
     else vis=FALSE;
    }

    if (lookR[left]!=left) // left pt already linked
    {
     if (lookR[left]>right) // deeper than current
     {
      lookL[lookR[left]]=lookR[left]; // break old links
      lookR[left]=left;
     }
     else vis=FALSE;
    }
    if (vis==TRUE) { lookL[right]=left; lookR[left]=right; } // make link
   }
  }

  lastlinked=-10; // dummy initial value

  for (x=s; x<vwidth; x++)
  {
   if ((lookL[x]==x) || (lookL[x]<s))
   {
    if (lastlinked==(x-1)) colour[x]=colour[x-1];
    else
    {
     colour[x]=GetPixelFromPattern(((x+poffset) % vmaxsep)/oversam,
                                   (y+((x-s)/vmaxsep)*yShift) % patHeight);
    }
   }
   else
   {
    colour[x]=colour[lookL[x]];
 
    lastlinked=x; // keep track of the last pixel to be constrained
   }
  }

  lastlinked=-10; // dummy initial value

  for (x=s-1; x>=0; x--)
  {
   if (lookR[x]==x)
   {
    if (lastlinked==(x+1)) colour[x]=colour[x+1];
    else
    {
     colour[x]=GetPixelFromPattern(((x+poffset) % vmaxsep)/oversam,
                                (y+((s-x)/vmaxsep+1)*yShift) % patHeight);
    }
   }
   else
   {
    colour[x]=colour[lookR[x]];
 
    lastlinked=x; // keep track of the last pixel to be constrained
   }
  }

  int red, green, blue;

  for (x=0; x<vwidth; x+=oversam)
  {
   red=0; green=0; blue=0;
   
   // use average colour of virtual pixels for screen pixel
   for (i=x; i<(x+oversam); i++)
   {
    col=colour[i];
    red+=col.R;
    green+=col.G;
    blue+=col.B;
   }
   col=RGB(red/oversam, green/oversam, blue/oversam);

   SetPixel(x/oversam,y, col);
  }
 }
}
