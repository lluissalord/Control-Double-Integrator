int PWMport=6; //PWM
int v1value=0; // TO store voltage 1
int v2value=0; // To store voltage 2
double v1=0;
double v2=0;
float ref=-1.5; //Canviat en -0.5 V
float u=0;
int cont=0;
int h=50; //Sampling rate
float Nx[2]={1,0};// Fill the gap
float Nu=0 ;// Fill the gap
double K[2]={0.5398,-0.6518};//Fill the gap
unsigned long timeIn=0;
unsigned long timeOut=0;
char intoutputbytes[12]; char floatoutputbytes[12];
int width=7; int precision=3;

//Estat de l'observador
#define SIZE 3
double estat[SIZE]={0, 0, 0};
//Per guardar la variable en aquest mateix instant, sino es modifica i no calcula be x2
double estat_bef[SIZE]={0, 0, 0};
double gam[SIZE]={
  0.708615362812500,
  -1.190475000000000,
                   0};
double phi[SIZE][SIZE]={
{1,  -1.190475, 0.708615362812500},
{0,  1,         -1.190475},
{0,  0,         1}};

//L de constant
double L[SIZE]={
  1.444580171955080,
  -0.681488187207379,
   0.050271250844659};

//auxiliar variable
char i = 0;

void setup()
{
pinMode(PWMport,OUTPUT); //inputs
pinMode(A5, INPUT);
pinMode(A4, INPUT);
Serial.begin(115200);
while(!Serial){}
Serial.println("X1_ct;X2_ct;X3_ct;Ref_ct;U_ct;V1_ct;V2_ct");
Serial.println("Volt [V];Volt [V];Volt [V];Volt [V];Volt [V];Volt [V];Volt [V];");
}


void loop()
{
Serial.print(estat[0]);
Serial.print(";");
Serial.print(estat[1]);
Serial.print(";");
Serial.print(estat[2]);
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

u=K[0]*(Nx[0]*ref-estat[0]) + K[1]*(Nx[1]*ref-estat[1]) - estat[2];
u=u+Nu*ref;

//Actualitzacio estats
i=0;
while(i<SIZE){
  estat_bef[i]=estat[i];
  i++;
}

estat[0]=gam[0]*u + L[0]*(v1-estat_bef[0]) + estat_bef[0]*phi[0][0] + estat_bef[1]*phi[0][1] + estat_bef[2]*phi[0][2];
estat[1]=gam[1]*u + L[1]*(v1-estat_bef[0]) + estat_bef[0]*phi[1][0] + estat_bef[1]*phi[1][1] + estat_bef[2]*phi[1][2];
estat[2]=           L[2]*(v1-estat_bef[0]) + estat_bef[2];

//offset artificial
//u=u+0.1;

u=u+2.5;

u=u*255./5;
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
