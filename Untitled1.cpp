#include <graphics.h>
#include <windows.h>
#include <winuser.h>
#include <winbgim.h>
short n[]={-1,0,1};
///////////////////////////////////Solid_Round//////////////////////////////////
void SR(int,int,int);
void SR(int x,int y,int t) {
     if (t>0){
        if (t==2) {
           setcolor(0);//BLACK
        }else{
           setcolor(15);//WHITE
        }
        for (int i = 1;i<=15;i++){
            circle(x*32+16,y*32+16,i);
        }
     }
}
////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////Can_it_Boarded/////////////////////////////////
bool CIB(long[],long,long,long,long,long,long,bool);
bool CIB(long AR[],long x,long y,long n1,long n2,long t,long c,bool b2){
     if (t==0){
        bool b=false;
        for (long i=0;i<3;i++){
            for (long i2 = 0;i2 < 3;i2++){
                if ((i!=1||i2!=1)&&CIB(AR,x,y,n[i],n[i2],1,c,b2)){ 
                   b = true;
                }
            }
        }
        return b;
     }else if (AR[x+y*8]==c && t>2) {
           return true;
     }else if ((x==7&&n1==1||x==0&&n1==-1||y==7&&n2==1||y==0&&n2==-1)&&(AR[x+y*8]!=c||t<=2)){
           return false;
     }else if (AR[x+y*8]==(3-c)||t==1) {
           if (CIB(AR,x+n1,y+n2,n1,n2,t+1,c,b2)){
                 AR[x+y*8]=c;
              if (b2){
                 SR(x,y,AR[x+y*8]);
              }
              return true;
           }
           return false;
     }else{
           return false;
     }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////Audit_Bureau_of_function////////////////////////////
long ABoF(long[],long,long,long[],long);
long ABoF(long AR[],long l,long El,long USt[],long Ut){
    long polong =0;
    if (l ==0){
       polong =-2147483647;
    }
    if (l==El){
       polong = 0;
       for (long i=0;i<Ut;i++){
           switch (AR[USt[i]]){
                  case 1:
                      if ((i<8||i>55)&&(i%8==0||i%8==7)){
                         polong-=99999;
                      }else if(i<8||i>55||i%8==0||i%8==7){
                         polong-=100;   
                      }else{
                         polong-=1;
                      }
                      break;
                  case 2:
                      if ((i<8||i>55)&&(i%8==0||i%8==7)){
                         polong+=300;
                      }else if(i<8||i>55||i%8==0||i%8==7){
                         polong+=10;   
                      }else{
                         polong+=1;
                      }
                      break;
           }
       }
       return polong;
    }else{
      long NAR[64];
      for (long i =0;i<64;i++){
          NAR[i]=AR[i];
      }
      if (l%2==0){
         long XY =0,t=0;
         for (long i=0;i<64;i++){
           if (NAR[i]==0&&CIB(NAR,(i%8),(i/8),-2,-2,0,2,false)){
              t+=1;
              USt[Ut]=i;
              long NP = ABoF(NAR,l+1,El,USt,Ut+1);
              if ((i<8||i>55)&&(i%8==0||i%8==7)){
                 NP+=300;
              }else if(i<8||i>55||i%8==0||i%8==7){
                 NP+=10;   
              }else{
                 NP+=1;
              }
              if (l==0){
                 if (NP > polong){
                    polong=NP;
                    XY=i;
                 }
              }else{
                 polong +=NP;
              }
              for (long i2=0;i2<=Ut;i2++){
                  NAR[USt[i2]]=AR[USt[i2]];
              }
           }
         }
         if (t>0){
            if (l==0){
               USt[Ut]=XY;
               CIB(AR,XY%8,XY/8,-2,-2,false,2,true);
            }else{
               return polong/t;   
            }
         }else{
            if (l==0){
               return 0;
            }else{
               return -100;   
            }
         }
      }else{
         polong=0;
         long t=0;
         for (long i=0;i<64;i++){
           if (NAR[i]==0 && CIB(NAR,(i%8),(i/8),-2,-2,0,1,false)){
              t+=1;
              USt[Ut]=i;
              polong= ABoF(NAR,l+1,El,USt,Ut+1);
              if ((i<8||i>55)&&(i%8==0||i%8==7)){
                 polong-=59999;
              }else if(i<8||i>55||i%8==0||i%8==7){
                 polong-=100;   
              }else{
                 polong-=1;
              }
              for (long i2=0;i2<=Ut;i2++){
                  NAR[USt[i2]]=AR[USt[i2]];
              }
           }
         }
         if (t>0){
            return polong/t;   
         }else{
            return 100;  
         }
      }
    }
}
////////////////////////////////////////////////////////////////////////////////
int main()
{
    initwindow(256,256);
    setbkcolor(10);
    cleardevice();
    setcolor(2);
    for (long i = 0 ;i<=255;i++){
        if (i%32==0||i%32==31){
           line(i,0,i,255);
           line(0,i,255,i);
        }
    }
    long USt[64],Ut=0;
    long AR[64];
    for (long i=0;i<=7;i++){
        for (long i2=0;i2<=7;i2++){
            if (i>=3&&i<=4&&i2>=3&&i2<=4){
               USt[Ut]=i+i2*8;
               Ut+=1;
               if (i==i2){
                  AR[i+i2*8]=1;
               }else{
                  AR[i+i2*8]=2;
               }
               SR(i,i2,AR[i+i2*8]);
            }else{
               AR[i+i2*8]=0;
            }
        }
    }
    bool computer = 0;
    while((!kbhit()) ) {
         delay(1);
         if (ismouseclick(WM_LBUTTONDOWN)){//mouseLeftClick
            if (computer==0) {
               int x,y ;
               getmouseclick(WM_LBUTTONDOWN, x, y);
               x /=32;
               y /=32;
               if (AR[x+y*8]==0){
                  if (CIB(AR,x,y,-2,-2,0,1,true)){
                     USt[Ut]=x+y*8;
                     Ut+=1;
                     computer = 1;
                     ABoF(AR,0,6,USt,Ut);
                     Ut+=1;
                     computer = 0;
                  }
               }
            }
        }
    }
}

