import matrix
values={}
#def history:
cal=[]
assign=[]
ini=[]
disp=[]
def funchist():
	print "--------------------HISTORY----------------- \n \n"
	print "\nInitializations done :"
	for x in range(len(ini)):
		print ini[x], "= " 
		values[ini[x]].display() 
	print "Assignments done :"
	for x in range(len(assign)):
		print assign[x], "= "
		values[assign[x][0]].display()
	print "Calculations done :"
	for x in range(len(cal)):
		print cal[x][0], "="
		cal[x][1].display()  
	print "Matrix displays done :"
	for x in range(len(disp)):
		print disp[x], "= "
		values[disp[x]].display()
	print "--------------------------------\n"

def store(st):
	inpstream=[]
	count=0
	colc=0
	rowc=0
	cols=1
	rows=1
	flag=1
	num=""
	for it in st:
		if it != ',' and it != '[' and it != ']' and it != ';':
			num=num+it
		elif it==',':
			fnum=float(num)
			num=""
			inpstream.append(fnum)
			colc=colc+1
		elif it==';':
			fnum=float(num)
			num=""
			inpstream.append(fnum)
			if flag:
				cols=colc+1
				flag=0
			rowc=rowc+1
		elif it==']':
			if flag:
				cols=colc+1
			fnum=float(num)
			num=""
			inpstream.append(fnum)
			rows=rowc+1
	A=matrix.matrix()
	A.dimensions(rows,cols)
	k=0
	for x in range(0,rows):
		for y in range(0,cols):
			A.read(inpstream[k],x,y)
			k=k+1
	return A
def func(mt):
	if len(mt)==1:
		values[mt[0]].display()
		disp.append(mt)
	elif len(mt)==2:
		if mt[1]=='i':
			A=values[mt[0]]&values[mt[0]]
			A.display()
			cal.append([mt,A])
	else:
		
		k=""
		for i in mt:
			if i==' ':
				continue
			k=k+i
		j=0	#a-b+c+d-e
		flag=1
		temp=0
		while j+1<len(spacefree):
			ky=spacefree[j:j+3]
			j=j+2
			if flag:
				flag=0
				if ky[1] == '+':
					A = values[ky[0]]
					B = values[ky[2]]
					temp=(A + B)
				elif ky[1] == '-':
					A = values[ky[0]]
					B = values[ky[2]]
					temp=(A - B)
				elif ky[1] == '*':
					A = values[ky[0]]
					B = values[ky[2]]
					temp=(A * B)
			else:
				if ky[1] == '+':
					B = values[ky[2]]
					temp=temp + B
				elif ky[1] == '-':
					B = values[ky[2]]
					temp=temp - B
				elif ky[1] == '*':
					B = values[ky[2]]
					temp=temp * B
		cal.append([mt,temp])
		temp.display()
while 1:
	read=raw_input("calc>")
	spacefree=""
	for i in read:
		if i!=' ':
			spacefree=spacefree+i
	if spacefree=="exit":
		break
	if spacefree=="hist":
		funchist()
	elif len(spacefree)==1 or spacefree[1]!='=':		#output a or output a+b
		func(spacefree)
	else:
		if spacefree[2]=='[':
			ini.append(spacefree[0])		
			values[spacefree[0]]=store(spacefree[2:])	#store a=[]
		elif len(spacefree)==3:
			assign.append(spacefree)
			values[spacefree[0]]=values[spacefree[2]]
		elif len(spacefree)==4: #a=bi
			values[spacefree[0]]=values[spacefree[2]]&values[spacefree[2]]
			assign.append(spacefree)
		else:	
			assign.append(spacefree)
			j=2	#a=b+c+d-e
			flag=1
			while j+1<len(spacefree):
				ky=spacefree[j:j+3]
				j=j+2
				if flag:
					flag=0
					if ky[1] == '+':
						A = values[ky[0]]
						B = values[ky[2]]
						temp=(A + B)
					elif ky[1] == '-':
						A = values[ky[0]]
						B = values[ky[2]]
						temp=(A - B)
					elif ky[1] == '*':
						A = values[ky[0]]
						B = values[ky[2]]
						temp=(A * B)
				else:
					if ky[1] == '+':
						B = values[ky[2]]
						temp=temp + B
					elif ky[1] == '-':
						B = values[ky[2]]
						temp=temp - B
					elif ky[1] == '*':
						B = values[ky[2]]
						temp=temp * B
			values[spacefree[0]]=temp
