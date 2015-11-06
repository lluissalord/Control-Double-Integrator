%Control amb refus de perturbacions (Cas perturbacions sinusoidals i constants)
%parametres model
A= [0 -23.8095;0 0];
B= [0;-23.8095];
C= eye(2);
D=[0;0];

%buscar controlador discret
P=[-5+20i,-5-20i];
h=5E-2;
[phi, gam] = c2d(A,B,h);
P_dis=[exp(P(1)*h), exp(P(2)*h)];
K_dis=acker(phi,gam,P_dis);

%Transformada Laplace
%0.5*(log(s^2+100*pi()^2)-2*log(s))

%Taylor (manual ja que wolfram donava amb log(s) que no es pot utilitzar)
%log(100*pi()^2)+2*(s/(200*pi()^2+s)+(1/3)*(s/(200*pi()^2+s))^3)-4*((s-1)/(s+1)+(1/3)*((s-1)/(s+1))^3)
%Agrupació pel Wolfram
c6=6*log(2)+6*log(5)+6*log(pi())-8;
c5=6*(4+3*log(2)+3*log(5)+600*pi()^2*(-2+log(2)+log(5))+3*(1+200*pi()^2)*log(pi()));
c4=6*(4+3*log(2)+3*log(5)+40000*pi()^4*(1+600*pi()^2+40000*pi()^4)*log(pi()));
c3=-2*(-12-3*log(2)+8E6*pi()^6*(8-3*log(2)-3*log(5))-3*log(5)-360000*pi()^4*(1+3*log(2)+3*log(5))-1800*pi()^2*(2+3*log(2)+3*log(5))-3*(1+1800*pi()^2+360000*pi()^4+8E6*pi()^6)*log(pi()));
c2=1200*pi()^2*(10+3*log(2)+3*log(5)+120000*pi()^4*(log(2)+log(5))+600*pi()^2*(1+3*log(2)+3*log(5))+3*(1+600*pi()^2+40000*pi()^4)*log(pi()));
c1=720000*pi()^4*(3+log(2)+log(5)+200*pi()^2*(log(2)+log(5))+(1+200*pi()^2)*log(pi()));
c0=16E6*pi()^6*(8+3*log(2)+3*log(5)+3*log(pi()));

d=poly([-1,-1,-1,-200*pi()^2,-200*pi()^2,-200*pi()^2]);
n=[c6,c5,c4,c3,c2,c1,c0];

[A_d, B_d, C_d, D_d] = tf2ss(n,d);

%Simplificada en un terme menys de Taylor
%log(100*pi()^2)+2*(s/(200*pi()^2+s))-4*((s-1)/(s+1))
c2=-2+2*log(2)+2*log(5)+2*log(pi()^2);
c1=-2*(-3-log(2)+pi()^2*(400-200*log(2)-200*log(5))-log(5)+(-1-200*pi()^2)*log(pi()));
c0=400*pi()^2*log(pi())+2*pi()^2*(400+200*log(2)+200*log(5));

d=poly([-1,-200*pi()^2]);
n=[c2,c1,c0];

[A_d, B_d, C_d, D_d] = tf2ss(n,d)
%ERROR (numeros massa grans i despres la L no podia ser suficientment
%acurada)
%Warning: Matrix is close to singular or badly scaled. Results may be inaccurate. RCOND =  3.852914e-28. 
%> In acker at 41

%Transformant directament de Taylor a Laplace (no precis)
%root_real = 20.2059642903233;
%root_imag = 12.7098734405416;
%b=50*[3*pi()^2, 0, -150*pi()^4, 0, 10000*pi()^6];
%a=[3, 0, 0, 0, 0, 0, 0];
%[A_d, B_d, C_d, D_d] = tf2ss(b,a);
phi_sin=c2d(A_d,[1 0]',h);
phi_pert=[phi gam*C_d [0;0]; zeros(2,2) phi_sin [0;0]; zeros(1,4) 1];
gam_pert=[gam; zeros(3,1)];
C_pert=eye(5);

P_obs=[-10,-5];
P_obs_dis_pert=[exp(P_obs(1)*h), exp(P_obs(2)*h),0.9, 0.2, 0.2];
K_obs_dis_pert=acker(phi_pert', [1 0 0 0 0]', P_obs_dis_pert);
L_pert=K_obs_dis_pert'