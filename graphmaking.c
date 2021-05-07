int main()
{
 int V,Vtemp,E,Etemp1;
 scanf("%d",&V);
 for(int i=0;i<V;i++)
 {
 scanf("%d",&Vtemp);
 addnode(i,Vtemp);
 }
 scanf("%d",&E);
 for(int i=0;i<E;i++)
 {
 scanf("%d %d",&Vtemp,&Etemp1);
 addedge(Vtemp,Etemp1,weight(Vtemp,Etemp1));
 }
 return 0;
}
