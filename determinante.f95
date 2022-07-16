program main
	implicit none
	
	character (len = 20), dimension(2) :: argv
	real (kind = 8), dimension(:,:), allocatable :: matrix
	integer :: dimn, i, factorial
	real ( kind = 8 ):: det, determinante
	
	call get_command_argument(1, argv(1))
	read(argv(1), '(i5)') dimn
	
	if ( .not. allocated(matrix) ) allocate(matrix(dimn, dimn))
	
	call get_command_argument(2, argv(2))
	open(1, file=argv(2))

	
	do i=1, dimn
		read(1,*) matrix(i,:)
	end do
	
	close(1)
	
	det = determinante(matrix, dimn, factorial(dimn))
	
	print*, det
	
	deallocate(matrix)
	
end program

function determinante(matrix, n, m) result(det)
	implicit none
	
	real ( kind = 8 ) :: det, prod
	integer :: n, m, sig, i, j, numberInversions
	real ( kind = 8 ), dimension(n, n) :: matrix
	integer, dimension(n) :: v
	integer, dimension(m, n) :: lp
	
	det = 0.
	do i=1,n
		v(i) = i
	end do

	call permuta(v, lp, n, m)
	
	do j=1,m
		prod = 1.
		sig = numberInversions(lp(j,:), n)
		
		do i=1,n
			prod = prod * matrix(i, lp(j,i))
		end do
		det = det + sig*prod
	end do
	
end function

subroutine permuta(A, lp, n, m)
	implicit none
	
	integer :: n, m, cnt
	integer, dimension(m, n), intent(out) :: lp
	integer,dimension(n), intent(out) :: A
	integer, dimension(n) :: c
	integer :: i, j, vaux
	
	c = 1
	
	cnt = 1
	lp(cnt,:)=A
	
	i=2
	do while ( i <= n )
		if ( c(i) < i ) then
			if ( mod(i, 2) == 1 ) then
				vaux = A(1)
				A(1) = A(i)
				A(i) = vaux
			else
				vaux = A(i)
				A(i) = A(c(i))
				A(c(i)) = vaux
			end if
			
			cnt = cnt + 1
			lp(cnt, :) = A
			
			c(i) = c(i) + 1
			i = 2
		else
			c(i) = 1
			i = i + 1
		end if
	end do
	
end subroutine

function numberInversions (vec, dimn) result(sol)
	implicit none
	
	integer :: sol
	integer :: dimn, i, j
	integer, dimension(dimn) :: vec
	
	sol = 0
	do i=1,dimn
		do j=i,dimn
			if (vec(i)>vec(j)) sol = sol + 1
		end do
	end do
	
	if ( mod(sol,2)==0 ) then
		sol = 1
	else
		sol = -1
	end if
	
end function

function factorial (n) result(fact)
	implicit none
	integer :: n, i, fact
	
	fact = n
	do i=2,n-1
		fact = fact * i
	end do

end function
