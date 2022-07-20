count = 0
Ra = rand(6, 10);
for i = 1 : 6
    for j = 1 : 10
        if Ra(i,j) > 0.5
            Ra(i,j) = Ra(i, j) - 1
            count = count+1;        
        end
    end
end