what's on my mind? really? it's pretty simpleton.

you have to create many auxillary functions that helps piece move from src to
the dest. such as finding the coordinate by index and/or vice versa. find index
by square that used chess notations such as 1b, 1c, etc and/or vice versa fr.
populate coordinates when necessary this creates centered validation for
validating if such move is legal.

i want to test out my functions so far because i've been doubting about it and yes
i found out a that i have been doing the set square wrong so i have fixed it.
i have to also test out the init piece=54321 from king to pawn respectively
i have to somehow separate them so i can test the validation function that i
have created called set piece to dest by char so yeah it is the piece for
validating piece moves.

todo: create a function that set the en passant status on the piece specifically
only the piece=0 or pawn on special move ohhhh that's what you call it. other's
don't have it boooo other pieces duhh anyway... the downside is that you have to
disable it when you want to, that is when it's your turn and you didn't en
passant enemy oh we have a problem here turn it off. this i'm stuck.
