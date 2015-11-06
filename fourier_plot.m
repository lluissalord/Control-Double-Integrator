function fourier_plot(y,h)
figure

set(0,'DefaultTextInterpreter', 'latex')

fontsize = 12;
set(0,'defaultaxesfontsize',fontsize);
set(0,'defaulttextfontsize',fontsize);

NFFT=2048;
L=length(y);	 	 
X=fftshift(fft(y,NFFT));	 	 
Px=X.*conj(X)/(NFFT*L); %Power of each freq components	 	 
fVals=(1/h)*(-NFFT/2:NFFT/2-1)/NFFT;	 	 
plot(fVals,Px,'b');	 	 
title('Power Spectral Density');	 	 
xlabel('Frequency [Hz]')	 	 
ylabel('Power [$$V^2/Hz$$]');
end