x = -8:0.5:8;
y=x;
[X,Y]=meshgrid(x,y);
R=sqrt(X.^2+Y.^2)+eps;
Z=sin(R)./R;
mesh(X,Y,Z)
grid on
%axis([-10 10 -10 10 -1 1])
xlabel('x')
ylabel('y')
zlabel('z')