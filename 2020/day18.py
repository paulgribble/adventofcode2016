with open("day18_input.txt") as f:
	inp = [r.strip('\n') for r in f]

e = "1 + (2 * 3) + (4 * (5 + 6))"


def mathme(val1,op,val2):
	val1,val2 = int(val1), int(val2)
	print("{} {} {}".format(val1,op,val2))
	if op=='+':
		return val1 + val2
	elif op=='-':
		return val1 - val2
	elif op=='*':
		return val1 * val2
	elif op=='/':
		return val1 / val2


def parse(e):
	if e.find(' ')==-1: # must be a single integer
		print("{}: returning {}".format(e,int(e)))
		return int(e)
	elif e[0] in '0123456789': # more than one term is left
		i = e.find(' ')
		val1 = int(e[:i])
		op = e[i+1]
		print("{}: returning {} {} {}".format(e,val1,op,e[i+3:]))
		val2 = parse(e[i+3:])
		r = mathme(val1,op,val2)
		return r
	elif e[0]=='(':
		depth = 1
		i = 1
		while depth>0 and i<len(e):
			if e[i]=='(':
				depth += 1
			elif e[i]==')':
				depth -= 1
			i += 1
		i -= 1
		print("{}: returning parse({})".format(e,e[1:i]))
		return parse(e[1:])











def parse(e):
	print('e: {}'.format(e))
	if e=='':
		print("{}: returning 0".format(e))
		return 0
	elif e.find(' ')==-1:
		print("{}: returning {}".format(e,int(e)))
		return int(e)
	elif e[0] in '0123456789':
		i = e.find(' ')
		val1 = int(e[:i])
		op = e[i+1]
		val2 = parse(e[i+3:])
		r = mathme(val1,op,val2)
		print("{}: returning {}".format(e,r))
		return r
	elif e[0]=='(':
		depth = 1
		i = 1
		while depth>0 and i<len(e[1:]):
			if e[i]=='(':
				depth += 1
			elif e[i]==')':
				depth -= 1
			i += 1
		if i!=len(e):
			i -= 1
		val1 = parse(e[1:i])
		if i < len(e):
			op = e[i+2]
			val2 = parse(e[i+4:])
			r = mathme(val1,op,val2)
			print("{}: returning {}".format(e,r))
			return r
		else:
			print("{}: returning {}".formate(e,val1))
			return val1




