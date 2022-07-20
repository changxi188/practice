function outputArg = bspline(inputArg1)
%BSPLINE Summary of this function goes here
%   Detailed explanation goes here
    if inputArg1 < 0
        outputArg = 0
    elseif inputArg1 < 1
        outputArg = inputArg1
    elseif inputArg1 < 2
        outputArg = 2 - inputArg1
    else
        outputArg = 0
    end
end

