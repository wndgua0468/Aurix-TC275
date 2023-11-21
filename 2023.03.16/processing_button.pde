import processing.net.*;
int[] indata_a = {0,0,0,0,0,0,0,0};
int[] outdata = {0,0,0,0,0,0,0,0};

void setup() {
  size(1000,700);
  smooth();
}

void draw(){
 
  fill(0,102,204);
  rect(50,500,900,60);
  fill(0,102,204);
  rect(50,320,900,60);
   
  for(int i=0; i<8; i++){
   fill(0);
   ellipse(140+100*i,350,40,40);
   ellipse(160+100*i,350,40,40);
   rect(140+100*i,330,20,40);
 
   if(indata_a[i]==0){
      fill(255);
      ellipse(140+100*i,350,40,40);
    } else{
      fill(255);
      ellipse(160+100*i,350,40,40);
    }
 
   
   if(indata_a[i]==0){
      if((mouseX-140-100*i)*(mouseX-140-100*i)+(mouseY-350)*(mouseY-350)<=400){
        if(mousePressed){
          indata_a[i]=1;
          delay(150);
        }
      }
    } else{
      if((mouseX-160-100*i)*(mouseX-160-100*i)+(mouseY-350)*(mouseY-350)<=400){
        if(mousePressed){
          indata_a[i]=0;
          delay(150);
        }
      }
    }
   if( indata_a[i]==0){
      outdata[i]=0;
    } else {
      outdata[i]=1;
    }
   if(outdata[i]==0){
      fill(255);
      } else{
        fill(255,0,0);
      }
      ellipse(150+100*i,530,40,40);
    }
  }
