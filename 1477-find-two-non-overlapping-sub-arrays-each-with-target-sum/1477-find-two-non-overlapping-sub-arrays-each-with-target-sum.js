var minSumOfLengths=(a,t)=>{
let l=0,s=0,m=A=1e9,b=[]
for(let r=0;r<a.length;r++){
s+=a[r];while(s>t)s-=a[l++]
if(s==t){let x=r-l+1;A=Math.min(A,x+(b[l-1]||1e9));m=Math.min(m,x)}
b[r]=m
}return A<1e9?A:-1}