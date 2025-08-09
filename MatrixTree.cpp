// 给定一张无向图和每条边可能存在的概率，求出现各个生成树的概率之和 (Matrix定理变式)
// 一般情况
// Matrix Tree其实求的是所有可能生成树边权之积的和。
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define endl '\n'
#define inc(i,a,b) for(int i(a);i<=b;i++)
#define dec(i,a,b) for(int i(a);i>=b;i--)
double ans;
const int MAXN(405);
const double eps(1e-8);
double matrix[MAXN][MAXN];
/**
 * 高斯消元，消除下三角
 * (long double)matrix   需要消元的矩阵
 * (int)n    方阵的大小
 * 最后计算det(matrix)只需要将对角线的所有数字相乘即可
 */
void gauss(int n)
{
    inc(j,1,n-1)
    {
        if(fabs(matrix[j][j])<eps)
        {
            int target(0);
            inc(i,j+1,n)
            {
                if(fabs(matrix[i][j])>=eps)
                {
                    target=i;
                    break;
                }
            }
            if(target)
            {
                inc(k,1,n)
                {
                    matrix[j][k]*=-1;   
                    swap(matrix[j][k],matrix[target][k]);
                }
            }
            else continue;
        }
        inc(i,j+1,n)
        {
            double tmp=matrix[i][j]/matrix[j][j];
            inc(k,1,n)
            {
                matrix[i][k]-=matrix[j][k]*tmp;
            }
        }
    }
}
void solve(){
    int n;
    ans=1;
    cin>>n;
    inc(i,1,n)inc(j,1,n)cin>>matrix[i][j];
    inc(i,1,n)inc(j,1,n)
    {
        double p=matrix[i][j];
        if(fabs(p)<eps)p=eps;
        if(fabs(1-p)<eps)p=1-eps;
        if(i<j)ans*=1-p;
        p=p/(1-p);
        matrix[i][j]=p;
    }
    inc(i,1,n)
    {
        matrix[i][i]=0;
        inc(j,1,n)
        {
            if(i!=j)
            matrix[i][i]-=matrix[i][j];
        }
    }
    gauss(n-1);
    inc(i,1,n-1)ans*=matrix[i][i];
    cout<<fixed<<setprecision(7)<<fabs(ans)<<endl;
}
signed main()
{
    ios::sync_with_stdio(false);
    int _;
    _=1;
    // cin>>_;
    while(_--)solve();
    system("pause");
}