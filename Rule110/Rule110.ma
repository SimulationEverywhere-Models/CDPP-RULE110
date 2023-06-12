[top]
components : Rule110 

[Rule110] 
type : cell
%Change dimensions for different size of iterations
dim : (100,100)
delay : transport
defaultDelayTime : 10
border : nowrapped 
neighbors : Rule110(-1,-1) Rule110(-1,0) Rule110(-1,1) Rule110(0,0)

initialValue : 0
%change Rule110.val for different dimensions as spcified above
initialCellsValue : Rule110.val
localtransition : Rule110-rule

[Rule110-rule]

% Karnaugh mapping the boolean equation reduces it from
%   |A|B|C + |A|B C + |A B|C + |A B C +  A|B|C +  A|B C +  A B|C +  A B C 
% where A = (-1,-1)
% where B = (-1,0)
% where C = (-1,1)
% to
%   |BC + |AB + B|C
rule : 1 10{ ( ( (-1,0) = 0 and (-1,1) = 1 ) or ( (-1,-1) = 0 and (-1,0) = 1 ) or ( (-1,0) = 1 and (-1,1) = 0 ) ) }
rule : { (0,0) } 10 { t }
 




