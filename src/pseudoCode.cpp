
#define round(X) (int)((X)+0.5)
#define DPI 72
#define E round(2.5*DPI)
#define mu (1/3.0)
#define separation(Z) round((1-mu*Z)*E/(2-mu*Z))
#define far separation(0)
#define maxX 256
#define maxY 256




// This "stereo separation" at the screen can be quantified by applying similar triangles, and assuming that the point
// on the object is straight ahead of the viewer:

//    sep = (eyesep * featureZ) / (featureZ + obsdist)


// From equation (1) it can be shown that the minimum permissible depth in the stereogram consistent with the first rule
// is given by:

//   mindepth=(sepfactor*maxdepth*obsdist)/((1-sepfactor)*maxdepth+obsdist)


// if a depth-map height-function is used then the following formula should be used:   

// 	 featureZ=maxdepth-h(x,y)*(maxdepth-mindepth)/256 

// where h(x,y) is a height function with values from 0 (farthest) to 255 (nearest). 
// h may be obtained from a grey scale depth-map picture,  
// maxdepth is the farthest depth (corresponding to 0 in the height function), 
// and  mindepth is the nearest depth, (corresponding to 255 in the height function).


// oversam = oversampling ratio ie. ratio of virtual pixels to real pixels 
// vwidth  = the new `virtual' width 
// veyeSep = eye separation in `virtual' pixels 
// vmaxsep = maximum stereo separation in 'virtual' pixels



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
