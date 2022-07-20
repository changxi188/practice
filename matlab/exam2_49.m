A=rand(3);
E=0*A;
F=eye(size(A));
N = 1;
while norm(E+F-E)>0
    E = E + F;
    F = A * F / N;
    N = N + 1;
end