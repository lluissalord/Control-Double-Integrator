function V_nomean=V_nomean(V,Npulses,startId,endId)
%Treu la mitja d'una senyal que vengui donada per pulsos
lastId=length(V);

V_nomean=[];
for i=0:floor(lastId/Npulses)-1
    %Si sobra temps ja ho faré optim
    V_nomean = [V_nomean; V(i*Npulses+startId:i*Npulses+endId)-mean(V(i*Npulses+startId:i*Npulses+endId))];
end
i=i+1;
if(i*Npulses+endId < lastId)
    lastId = i*Npulses+endId;
end
V_nomean = [V_nomean; V(i*Npulses+startId:lastId)-mean(V(i*Npulses+startId:lastId))];
end