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
double K[2]={0.539753286511977,  -0.651795973236137};
unsigned long timeIn=0;
unsigned long timeOut=0;
char intoutputbytes[12]; char floatoutputbytes[12];
int width=7; int precision=3;

//Estat de l'observador
#define SIZE 5
double estat[SIZE]={0, 0, 0, 0, 0};
//Per guardar la variable en aquest mateix instant, sino es modifica i no calcula be x2
double estat_bef[SIZE]={0, 0, 0, 0, 0};
double gam[SIZE]={0.708615362812500, -1.190475, 0, 0, 0};
double phi[SIZE][SIZE]={
{1,  -1.190475, 0.708615362812500, 0.708615362812500,   0},
{0,  1,       -1.190475,         -1.190475,           0},
{0,  0,       1,                 0,                   0},
{0,  0,       0,                 0.985798003782398,   0.049763075194479},
{0,  0,       0,                 -0.566731369161185, 0.985798003782398}};

//L de const i sinus (pols en S -10, -5 i pols en Z 0.4, 0.4, 0.9)
double L[SIZE] = {
  0.886264564780693,
  -0.201743561486637,
   0.002162093816566,
   0.008686621488739,
  -0.055319881225164};
//auxiliar variable
char i = 0;

void setup()
{
pinMode(PWMport,OUTPUT); //inputs
pinMode(A5, INPUT);
pinMode(A4, INPUT);
Serial.begin(115200);
while(!Serial){}
Serial.println("X1_sin_ct; X2_sin_ct;X3_sin_ct; X4_sin_ct;X5_sin_ct;Ref_sin_ct;U_sin_ct;V1_sin_ct;V2_sin_ct");
Serial.println("Volt [V];Volt [V];Volt [V];Volt [V];Volt [V];Volt [V];Volt [V];Volt [V];Volt [V];");
}


void loop()
{
Serial.print(estat[0]);
Serial.print(";");
Serial.print(estat[1]);
Serial.print(";");
Serial.print(estat[2]);
Serial.print(";");
Serial.print(estat[3]);
Serial.print(";");
Serial.print(estat[4]);
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

u=K[0]*(Nx[0]*ref-estat[0]) + K[1]*(Nx[1]*ref-estat[1]) - estat[2]  - estat[3];
u=u+Nu*ref;

//Actualitzacio estats
i=0;
while(i<SIZE){
  estat_bef[i]=estat[i];
  i++;
}

estat[0]=gam[0]*u + L[0]*(v1-estat_bef[0]) + estat_bef[0]*phi[0][0] + estat_bef[1]*phi[0][1] + estat_bef[2]*phi[0][2] + estat_bef[3]*phi[0][3];
estat[1]=gam[1]*u + L[1]*(v1-estat_bef[0]) + estat_bef[0]*phi[1][0] + estat_bef[1]*phi[1][1] + estat_bef[2]*phi[1][2] + estat_bef[3]*phi[1][3];
estat[2]=           L[2]*(v1-estat_bef[0])                                                   + estat_bef[2]*phi[2][2];
estat[3]=           L[3]*(v1-estat_bef[0])                                                                            + estat_bef[3]*phi[3][3] + estat_bef[4]*phi[3][4];
estat[4]=           L[4]*(v1-estat_bef[0])                                                                            + estat_bef[3]*phi[4][3] + estat_bef[4]*phi[4][4];

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
