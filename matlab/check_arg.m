function [outArg1 outArg2] = check_arg(inputArg1, inputArg2, inputArg3)
%CHECK_ARG Summary of this function goes here
%   Detailed explanation goes here
if(nargin == 1)
    outArg1 = inputArg1;
elseif(nargin == 2)
    outArg1 = inputArg1 + inputArg2;
elseif(nargin == 3)
    outArg1 = inputArg1 * inputArg2 * inputArg3 / 2;
end
if(nargout == 2)
    outArg2 = outArg1;
end
end

