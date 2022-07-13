-- Heap's Algorithm
local function permuta(A, lp)
	
	local n = #A
	
	local c = {}
	for i=1,n do
		c[i] = 1
	end
	
	index = 1
	lp[index] = {}
	for j=1,n do
		lp[index][j] = A[j]
	end
	
	
	local i = 2
	while i <= n do
		if c[i] < i then
			if i%2 == 1 then
				A[1], A[i] = A[i], A[1]
			else
				A[c[i]], A[i] = A[i], A[c[i]]
			end
			
			index = index + 1
			lp[index] = {}
			for j=1,n do
				lp[index][j] = A[j]
			end
			
			c[i] = c[i] + 1
			i = 2
		else
			c[i] = 1
			i = i + 1
		end
	end 
end

local function numberInversions(A)
	
	local s = 0
	for i=1,#A do
		for j=i,#A do
			if A[i] > A[j] then s = s +1 end
		end
	end
	return s%2
end


local function determinant(A)

	local det = 0
	
	local l = {}
	for i=1,#A do
		l[i] = i
	end
	
	local lp = {}
	
	permuta(l, lp)

	for _,__ in ipairs(lp) do
		local prod = 1
		local sign = numberInversions(__)
		for i,j in ipairs(__) do
			prod = prod * A[i][j]
		end
		det = det + ((-1)^sign)*prod
	end
	
	return det
end

matrix = {
	{1,12,4,-1},
	{4,5,-3,11},
	{-15,7,8,9},
	{5,12,45,67}
}

print(determinant(matrix))
