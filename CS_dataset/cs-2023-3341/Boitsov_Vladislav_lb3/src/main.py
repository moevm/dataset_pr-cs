memory=list(input())
q='q1'
ind=0
while(q!='qT'):
    if q=='q1':
        if memory[ind]=='a':
            memory[ind]='a'
            ind+=0
            q='q2'
        elif memory[ind]=='b':
            memory[ind]='b'
            ind+=0
            q='q2'
        elif memory[ind]=='c':
            memory[ind]='c'
            ind+=0
            q='q2'
        elif memory[ind]==' ':
            memory[ind]=' '
            ind+=1
            q='q1'
    elif q=='q2':
        if memory[ind]=='a':
            memory[ind]='a'
            ind+=1
            q='q3'
        elif memory[ind]=='b':
            memory[ind]='b'
            ind+=1
            q='q2'
        elif memory[ind]=='c':
            memory[ind]='c'
            ind+=1
            q='q2'
        elif memory[ind]==' ':
            memory[ind]=' '
            ind+=0
            q='qT'
    elif q=='q3':
        if memory[ind]=='a':
            memory[ind]='a'
            ind-=1
            q='q4'
        elif memory[ind]=='b':
            memory[ind]='b'
            ind-=1
            q='q7'
        elif memory[ind]=='c':
            memory[ind]='c'
            ind-=1
            q='q10'
        elif memory[ind]==' ':
            memory[ind]=' '
            ind-=1
            q='q4'
    elif q=='q4':
        if memory[ind]=='a':
            memory[ind]='a'
            ind-=1
            q='q4'
        elif memory[ind]=='b':
            memory[ind]='b'
            ind-=1
            q='q4'
        elif memory[ind]=='c':
            memory[ind]='c'
            ind-=1
            q='q4'
        elif memory[ind]==' ':
            memory[ind]=' '
            ind+=1
            q='q5'
    elif q=='q5':
        if memory[ind]=='a':
            memory[ind]='a'
            ind+=1
            q='q5'
        elif memory[ind]=='b':
            memory[ind]='b'
            ind+=1
            q='q5'
        elif memory[ind]=='c':
            memory[ind]='c'
            ind-=1
            q='q6'
        elif memory[ind]==' ':
            memory[ind]=' '
            ind+=0
            q='qT'
    elif q=='q6':
        if memory[ind]=='a':
            memory[ind]='a'
            ind+=0
            q='qT'
        elif memory[ind]=='b':
            memory[ind]='a'
            ind+=0
            q='qT'
        elif memory[ind]=='c':
            memory[ind]='a'
            ind+=0
            q='qT'
        elif memory[ind]==' ':
            memory[ind]='a'
            ind+=0
            q='qT'
    elif q=='q7':
        if memory[ind]=='a':
            memory[ind]='a'
            ind-=1
            q='q7'
        elif memory[ind]=='b':
            memory[ind]='b'
            ind-=1
            q='q7'
        elif memory[ind]=='c':
            memory[ind]='c'
            ind-=1
            q='q7'
        elif memory[ind]==' ':
            memory[ind]=' '
            ind+=1
            q='q8'
    elif q=='q8':
        if memory[ind]=='a':
            memory[ind]='a'
            ind+=1
            q='q8'
        elif memory[ind]=='b':
            memory[ind]='b'
            ind+=1
            q='q8'
        elif memory[ind]=='c':
            memory[ind]='c'
            ind-=1
            q='q9'
        elif memory[ind]==' ':
            memory[ind]=' '
            ind+=0
            q='qT'
    elif q=='q9':
        if memory[ind]=='a':
            memory[ind]='b'
            ind+=0
            q='qT'
        elif memory[ind]=='b':
            memory[ind]='b'
            ind+=0
            q='qT'
        elif memory[ind]=='c':
            memory[ind]='b'
            ind+=0
            q='qT'
        elif memory[ind]==' ':
            memory[ind]='b'
            ind+=0
            q='qT'

    elif q=='q10':
        if memory[ind]=='a':
            memory[ind]='a'
            ind-=1
            q='q10'
        elif memory[ind]=='b':
            memory[ind]='b'
            ind-=1
            q='q10'
        elif memory[ind]=='c':
            memory[ind]='c'
            ind-=1
            q='q10'
        elif memory[ind]==' ':
            memory[ind]=' '
            ind+=1
            q='q11'
    elif q=='q11':
        if memory[ind]=='a':
            memory[ind]='a'
            ind+=1
            q='q11'
        elif memory[ind]=='b':
            memory[ind]='b'
            ind+=1
            q='q11'
        elif memory[ind]=='c':
            memory[ind]='c'
            ind-=1
            q='q12'
        elif memory[ind]==' ':
            memory[ind]=' '
            ind+=0
            q='qT'
    elif q=='q12':
        if memory[ind]=='a':
            memory[ind]='c'
            ind+=0
            q='qT'
        elif memory[ind]=='b':
            memory[ind]='c'
            ind+=0
            q='qT'
        elif memory[ind]=='c':
            memory[ind]='c'
            ind+=0
            q='qT'
        elif memory[ind]==' ':
            memory[ind]='c'
            ind+=0
            q='qT'
ans=''
for x in memory:
    ans=ans+x
print(ans)