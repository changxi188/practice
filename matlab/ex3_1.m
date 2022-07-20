x = linspace(0, 2*pi)
gain = [5, 10, 20, 30, 50, 80, 100]
temp = sin(x)./(x.*x + 1);
for i = 1:7
    y = gain(i) * temp;
    plot(x, y)
    hold on
end