int PWMport=6; //PWM
int v1value=0; // TO store voltage 1
int v2value=0; // To store voltage 2
float v1=0;
float v2=0;
float ref=-1.5; //Canviat en -0.5 V
float u=0;
int cont=0;
int h=50; //Sampling rate
float Nx[2]={1,0};// Fill the gap
float Nu=0 ;// Fill the gap
float K[2]={0.5398,-0.6518};//Fill the gap
unsigned long timeIn=0;
unsigned long timeOut=0;
char intoutputbytes[12]; char floatoutputbytes[12];
int width=7; int precision=3;

//Estat de l'observador
float x1=0;
//Per guardar la variable en aquest mateix instant, sino es modifica i no calcula be x2
float x1k=0; 
float x2=0;
float gam[2]={0.7086,-1.1905};
float phi[4]={1, -1.1905, 0, 1};
float L[2]={1.3446, -0.5985};

void setup()
{
pinMode(PWMport,OUTPUT); //inputs
pinMode(A5, INPUT);
pinMode(A4, INPUT);
Serial.begin(115200);
while(!Serial){}
Serial.println("X1;X2;Ref;U;V1;V2");
Serial.println("Volt [V];Volt [V];Volt [V];Volt [V];Volt [V];Volt [V];");
}


void loop()
{
Serial.print(x1);
Serial.print(";");
Serial.print(x2);
Serial.print(";");
cont=cont+1;
if (cont==200) {
  ref=0.5; //Canviat en -0.5 V
}else if (cont==400){
  ref=-1.5; //Canviat en -0.5 V
  cont=0;  
}
  
//YOUR CONTROL ALGORITHM SHOULD BE HERE
v1value=analogRead(A5); // 0 a 1024
v2value=analogRead(A4);
v1=v1value*5./1023; // 0 a 5
v1=v1-2.5; //-2.5 a 2.5
v2=v2value*5./1023;
v2=v2-2.5;

//Test
//x1=v1;
//x2=v2;

u=K[0]*(Nx[0]*ref-x1) + K[1]*(Nx[1]*ref-x2); //Provar agafant v1
u=u+Nu*ref;
x1k=x1;

x1=(gam[0]*u+L[0]*(v1-x1k)+x1k*phi[0]+x2*phi[1]);
x2=(gam[1]*u+L[1]*(v1-x1k)+x1k*phi[2]+x2*phi[3]);

u=u+2.5;

u=u*255./5;
//if(u<0){u=0;}
analogWrite(PWMport,u);


Serial.print(ref);
Serial.print(";");
Serial.print(u*5/255-2.5);
Serial.print(";");
Serial.print(v1value*5./1023-2.5);
Serial.print(";");
Serial.print(v2value*5./1023-2.5);
Serial.println(";");


delay(h);
}

