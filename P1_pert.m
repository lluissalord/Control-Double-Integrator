%Control amb refus de perturbacions (Cas perturbacions constants)
%parametres model
A= [0 -23.8095;0 0];
B= [0;-23.8095];
C= eye(2);
D=[0;0];

%buscar controlador continu(realimentacio)
P=[-5+20i,-5-20i];
h=5E-2;
[phi, gam] = c2d(A,B,h);
P_dis=[exp(P(1)*h), exp(P(2)*h)];
K_dis=acker(phi,gam,P_dis);


phi_pert=[phi gam; 0 0 1];
gam_pert=[gam; 0];
C_pert=eye(3);

P_obs=[-10+20i,-10-20i];
P_obs_dis_pert=[exp(P_obs.*h), 0.9];
K_obs_dis_pert=acker(phi_pert', [1 0 0]', P_obs_dis_pert);
L_pert=K_obs_dis_pert';