A=[0 -23.8095;0 0]
B=[0;-23.8095]

C=[1 0];
D=0;



N=inv([A B;C 0])*[0;0;1]
 
Nu=N(3)
Nx=N(1:2)

K=acker(A,B,[-5+20*i -5-20*i]);

C=eye(2);
D=[0;0]
N=inv([A B;C [0;0])*[0;0;0;1]
