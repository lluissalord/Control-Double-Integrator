%Control amb observador
%parametres model
A= [0 -23.8095;0 0];
B= [0;-23.8095];
C= [1 0];
D=[0;0];

%pols de llaç tancat en continu
P=[-5+20i,-5-20i];

%buscar controlador discret
h=5E-2;
[phi, gam] = c2d(A,B,h);
P_dis=[exp(P(1)*h), exp(P(2)*h)];
K_dis=acker(phi,gam,P_dis);

%busco parametres Nu i Nx
W=[phi-eye(2) gam;C 0];
N=inv(W)*[0;0;1];
Nx=N(1:2);
Nu=N(3);

P_obs=[-10+20i,-10-20i];
P_obs_dis=exp(P_obs.*h);
K_obs_dis=acker(phi', C', P_obs_dis);
L=K_obs_dis';
C_obs=[1 0];
