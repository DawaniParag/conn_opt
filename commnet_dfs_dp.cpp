#include <bits/stdc++.h>
using namespace std;

struct IdxCompare
{
    const std::vector<int>& target;

    IdxCompare(const std::vector<int>& target): target(target) {}

    bool operator()(int a, int b) const { return target[a] < target[b]; }
};

vector < int > dp[1000];

void dfs(int ctr,vector < int > flag,int k,int parent,vector<int> cost[],vector<int> v[],int n,int m)
{
    //cout<<k<<" ";
    flag[k]=1;
    if(k>=n && k<n+m)
        ctr++;
    if(parent<n)
    {
         for(int i=0;i<v[k].size();i++)
        {
            if(v[k][i]>=n+m)
            {
                //cout<<ctr<<"and";
                //cout<<cost[parent][v[k][i]-n-m];
             if(ctr<cost[parent][v[k][i]-n-m])
             {
                 cost[parent][v[k][i]-n-m]=ctr;
                 //cout<<"ud"<<" "<<cost[parent][v[k][i]-n-m]<<" ";
             }

             continue;
            }
            else
            {
                for(int j=0;j<n;j++)
                {
                    if(dp[v[k][i]-n][j]!=-1)
                        cost[parent][j]=dp[v[k][i]-n][j]+1;
                }
            }
        }
    }
    else if(parent>=n && parent<n+m)
    {
        cout<<k;

        for(int i=0;i<v[k].size();i++)
        {
            if(v[k][i]>=n+m)
            {
                //cout<<ctr<<"and";
                //cout<<cost[parent][v[k][i]-n-m];
             if(ctr<dp[parent-n][v[k][i]-n-m] || dp[parent-n][v[k][i]-n-m]==-1)
             {
                 dp[parent][v[k][i]-n-m]=ctr;
                 //cout<<"ud"<<" "<<cost[parent][v[k][i]-n-m]<<" ";
             }

             continue;
            }
            else
            {
                if(flag[v[k][i]]==0)
                    dfs(ctr,flag,v[k][i],parent,cost,v,n,m);
            }
        }
    }
    flag[k]=0;
    return;

}

int main()
{
    int n,m,k;
    char c1,c2;
    int i1,i2;
    vector < int > v[1000];
    cin>>n>>m>>k;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
            dp[i].push_back(-1);
    }
    vector <int> cost[n];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            cost[i].push_back(100000);
    }
    vector < int > flag(2*n+m);
    fill(flag.begin(), flag.end(), 0);
    for(int i=0;i<k;i++)
    {
        cin>>c1>>i1>>c2>>i2;
        //cout<<c1<<i1<<c2<<i2;
        if(c1=='u')
        {
            if(c2=='u')
            {
            // v[i1-1].push_back(i2-1);
            }
            else if(c2=='t')
            {
                //cout<<'y';
                //cout<<i1-1<<i2+n-1;
             v[i1-1].push_back(i2+n-1);
            }
            else if(c2=='T')
            {
             v[i1-1].push_back(i2+n+m-1);
            }
        }
        else if(c1=='t')
        {
              if(c2=='u')
            {
             v[i2-1].push_back(i1+n-1);
            }
            else if(c2=='t')
            {
             v[i1+n-1].push_back(i2+n-1);
             v[i2+n-1].push_back(i1+n-1);
            }
            else if(c2=='T')
            {
             v[i1+n-1].push_back(i2+n+m-1);
            }
        }
        else if(c1=='T')
        {
              if(c2=='u')
            {
             v[i2-1].push_back(i1+n+m-1);
            }
            else if(c2=='t')
            {
              v[i2+n-1].push_back(i1+n+m-1);
            }
            else if(c2=='T')
            {
            //  v[i1+n+m-1].push_back(i2+n+m-1);
            }
        }
    }
    for(int i=0;i<n+m;i++)
    {
        sort(v[i].begin(),v[i].end());
    }
    for(int i=n;i<n+m;i++)
    {
        dfs(-1,flag,i,i,cost,v,n,m);
    }
    cout<<"no";
    for(int i=0;i<n;i++)
    {
        dfs(0,flag,i,i,cost,v,n,m);
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            cout<<cost[i][j]<<" ";
        cout<<endl;
    }

     std::vector<int> x;
    std::vector<int> y;

    int w,m1;
    int totcost=0;
    int mpref[n][n],wpref[n][n];
    queue<int> freemen;
    int wpartner[n];

    for(int p=0;p<n;p++)
    {
        x.clear();
        y.clear();
        x=cost[p];
         // initialize indexes
        for(size_t i = 0; i < x.size(); ++i)
            y.push_back(i);

        std::sort(y.begin(), y.end(), IdxCompare(x));

    //    std::cout << "\nvector x: " << '\n';
    //    for(size_t i = 0; i < x.size(); ++i)
    //        std::cout << x[i] << '\n';

    //    std::cout << "\nvector y: " << '\n';
        for(size_t i = 0; i < x.size(); ++i)
            mpref[p][i]=y[i];
        //std::cout << y[i] << '\n';
    }

     for(int p=0;p<n;p++)
    {
        x.clear();
        y.clear();
        for(int q=0;q<n;q++)
        {
            x.push_back(cost[q][p]);
        }
         // initialize indexes
        for(size_t i = 0; i < x.size(); ++i)
            y.push_back(i);

        std::sort(y.begin(), y.end(), IdxCompare(x));

    //    std::cout << "\nvector x: " << '\n';
    //    for(size_t i = 0; i < x.size(); ++i)
    //        std::cout << x[i] << '\n';

    //    std::cout << "\nvector y: " << '\n';
        for(size_t i = 0; i < x.size(); ++i)
            wpref[p][i]=y[i];
        //std::cout << y[i] << '\n';
    }


    memset(wpartner, -1, sizeof(wpartner));

    for(int i=0;i<n;i++)
        freemen.push(i);

    while(!(freemen.empty()))
    {
        m1=freemen.front();
        for (int i = 0; i < n; i++)
        {
            if(m1!=freemen.front())
                break;
            w = wpref[m1][i];
            if (wpartner[w] == -1)
            {
                wpartner[w] = m1;
                freemen.pop();
                break;
            }

            else
            {
                for (int j = 0; j < n; j++)
                {
                    if (mpref[w][j] == wpartner[w])
                        break;

                    if (mpref[w][j] == m1)
                    {
                        freemen.push(wpartner[w]);
                        wpartner[w] = m1;
                        freemen.pop();
                        break;
                    }
                }
            }
        }
    }
    for (w = 0; w < n; w++)
        {
            printf("%d %d\n", w+1,wpartner[w]+1);
            totcost+=cost[w][wpartner[w]];
        }
        cout<<totcost+n;


return 0;
}

