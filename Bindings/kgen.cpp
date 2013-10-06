#include <stdio.h>
#include <stdlib.h>
char** lines;

void out(int pos,int &x, int &y, const char* s, int a, int b, int c)
{
        char* ss=(char*)malloc(30);
        sprintf(ss,"%s(%i, %i, %i);", s, a, b, c);
        y+=30;
        free(lines[pos]);
        lines[pos]=ss;
}
int tx,ty;
void str2(int lvl, int &x, int &y, int a, int b, int l, int n, int k, int& superbase)
         {
                int canv=30*5;
                int pos=0;
                x=10+100*(lvl-1);
                y = y - canv;
                pos=5*((lvl-1)*ty+(y-110+canv)/canv);
                out(pos+0,x,y,"equ",superbase,b+l,l);
                out(pos+1,x,y,"sub",superbase,b,l);
                out(pos+2,x,y,"equ",superbase+l,b+l+l,l);
                out(pos+3,x,y,"sub",superbase+l,b+3*l,l);
                out(pos+4,x,y,"xchg",b+l,b+l+l,l);
                int olda=superbase;
                superbase+=2*l;
                if(l!=1)
                {
                int yy=y;
                str2(lvl+1,x,y,a-n/2,b,l/2,n,k,superbase);
                y = y + 30*5;
                str2(lvl+1,x,y,a-n/2+l,b+l+l,l/2,n,k,superbase);
                y = y + 30*5;
                str2(lvl+1,x,y,a+n/2,olda,l/2,n,k,superbase);
                //superbase+=l;
                //y=yy;
                }
                else
                {
                        x=10+100*k;
                        int yy=y-canv;
                        pos=(5*(k-1)*ty+3*(y-110)/canv);
                        out(pos+0,x,yy,"mul",b,b+1,1);
                        out(pos+1,x,yy,"mul",b+2,b+3,1);
                        out(pos+2,x,yy,"mul",olda,olda+1,1);
                }
                y = y - canv;
                x=10+100*(k+k-lvl+1);
                pos=(5*(k-1)*ty+3*ty*(1+k-lvl)+3*(y-110)/canv);
                out(pos+0,x,y,"add",olda,b,2*l);
                out(pos+1,x,y,"add",olda,b+l+l,2*l);
                out(pos+2,x,y,"add",b+l,olda,2*l);
                y = y + 30*2;
         }
void str(int lvl, int &x, int &y, int a, int b, int l, int n, int k, int& superbase)
         {
                int canv=30*5;
                int pos=0;
                x=10+100*(lvl-1);
                y = y - canv;
                pos=5*((lvl-1)*ty+(y-110+canv)/canv);
                out(pos+0,x,y,"equ",a,b+l,l);
                out(pos+1,x,y,"sub",a,b,l);
                out(pos+2,x,y,"equ",a+l,b+l+l,l);
                out(pos+3,x,y,"sub",a+l,b+3*l,l);
                out(pos+4,x,y,"xchg",b+l,b+l+l,l);
                if(l!=1)//lvl==k-1//p3=3^k-1
                {
                int yy=y;
                str(lvl+1,x,y,a-n/2,b,l/2,n,k,superbase);
                y = y + 30*5;
                str(lvl+1,x,y,a-n/2+l,b+l+l,l/2,n,k,superbase);
                y = y + 30*5;
                str2(lvl+1,x,y,a+n/2,a,l/2,n,k,superbase);
                //superbase+=l;
                //y=yy;
                }
                else
                {
                        x=10+100*k;
                        int yy=y-canv;
                        pos=(5*(k-1)*ty+3*(y-110)/canv);
                        out(pos+0,x,yy,"mul",b,b+1,1);
                        out(pos+1,x,yy,"mul",b+2,b+3,1);
                        out(pos+2,x,yy,"mul",a,a+1,1);
                }
                y = y - canv;
                x=10+100*(k+k-lvl+1);
                pos=(5*(k-1)*ty+3*ty*(1+k-lvl)+3*(y-110)/canv);
                out(pos+0,x,y,"add",a,b,2*l);
                out(pos+1,x,y,"add",a,b+l+l,2*l);
                out(pos+2,x,y,"add",b+l,a,2*l);
                y = y + 30*2;
         }
int mul(int x, int y)
{
        return 0;
}
int main(int argc, char* argv[])
{
        // n == РАЗМЕР РЕЗУЛЬТАТА
        
        int x=10, y=110;
        int n=atoi(argv[1]);
        int k=0, m=n;
        while((m&1)==0){m=m>>1;k++;}
        if (m!=1)return 0;
        int superbase = 1+n + n/2 * (k-1);
        ty=1;
        for(int i =1; i<k-1;i++)ty*=3;
        tx=k+k+1;

	int numops=ty*3+8*ty*k;
        lines=(char**)malloc(sizeof(char*)*numops);
        for(int i=0;i<numops;i++)lines[i]=0;
        str(1,x,y,1+n + n/2 * (k-1-1),1,(1<<(k-1-1)),n,k,superbase);
        // l - длина операций всегда равна 1<<(k-1-lvl)
        for(int i=0;i<numops;i++)
        if(lines[i]!=0)
                printf("%s\n",lines[i]);
        free(lines);
        return 0;
}

