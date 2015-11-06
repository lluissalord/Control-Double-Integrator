function time=time_var(n,h)
clear time;
time(1,1)=0;
for i=2:n
time(i,1)=time(i-1,1)+h;
end
clear i;
