function fourier_plot(y,h)
figure

set(0,'DefaultTextInterpreter', 'latex')

fontsize = 24;
set(0,'defaultaxesfontsize',fontsize);
set(0,'defaulttextfontsize',fontsize);

NFFT=2048;
L=length(y);	 	 
X=fftshift(fft(y,NFFT));	 	 
Px=X.*conj(X)/(NFFT*L); %Power of each freq components	 	 
fVals=(1/h)*(-NFFT/2:NFFT/2-1)/NFFT;	 	 
plot(fVals,Px,'b');	 	 
title('Densitat Espectral de $\mathrm{Pot\grave{e}ncia}$');	 	 
xlabel('$\mathrm{Freq\ddot{u}\grave{e}ncia}$ [Hz]')	 	 
ylabel('DEP [$$V^2/Hz$$]');
end