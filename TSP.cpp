#include<bits/stdc++.h>
#include <random>
using namespace std;

float a[5000][5000] = {};
long double cost = 0.0;


typedef struct point
{
	float x;
	float y;
}point;

float dist(point a,point b)
{
	float a1 = (a.x-b.x);	
	float a2 = (a.y-b.y);
	float a3 = pow(a1,2)+pow(a2,2);
	return (sqrt(a3));
	
}



float dist2(point a,point b)
{
	float a1 = abs((a.x-b.x));		
	float a2 = abs((a.y-b.y));
	return (a1+a2);
}

int get()
{
	string type;
	cin >> type;
	if(type == "euclidean")
	{
		int N;
		cin >> N;
		point pnts[N];
		int i,j,k;
		float X,Y;
		for(i = 0;i < N;++i)
		{
			cin >> X >> Y;
			pnts[i].x = X;
			pnts[i].y = Y;
		}
		for(i = 0;i < N;++i)
		{
			for(j = 0;j < N;++j)
			{
				if(a[j][i] != 0.0)a[i][j] = a[j][i];
				else a[i][j] = dist(pnts[i],pnts[j]);
			//	cout << a[i][j] << " ";
			}
			//cout << endl;
		}
		return N;
	}
	else
	{
		int N;
		cin >> N;
		//float a[N][N] = {};
		int visited[N];
		point pnts[N];
		int i,j,k;
		float X,Y;
		for(i = 0;i < N;++i)
		{
			cin >> X >> Y;
			pnts[i].x = X;
			pnts[i].y = Y;
		}
		for(i = 0;i < N;++i)
		{
			for(j = 0;j < N;++j)
			{
				if(a[j][i] != 0.0)a[i][j] = a[j][i];
				else a[i][j] = dist2(pnts[i],pnts[j]);
			}
		}
		return N;
	}
}

int random_int_range(int min,int max)// range includes both min and max 
{
std::random_device rd;     // only used once to initialise (seed) engine
std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
std::uniform_int_distribution<int> uni(min,max); // guaranteed unbiased

auto random_integer = uni(rng);	
return random_integer;	
	
}

double random_double()
{
	double r = ((double) rand() / (RAND_MAX));
	return r;
}

long double returns_cost(vector<int> &vec)
{
    long double result = 0.0;
    for(int i = 0;i < vec.size()-1;++i)
       result += a[vec[i]][vec[i+1]]; 
    result += a[vec[vec.size()-1]][0];
    return result;
}


vector<int> greedy(int n)
{
	map<int,bool>mymap;
	int i,j,k;
	for(i = 0;i < n;++i)mymap[i] = false;
	mymap[0] = true;
	vector<int> vec;
	vec.push_back(0);//cout << "0 --> ";
	i = 0;
	long double c = 0.0;
	while(1)
	{
		float min = FLT_MAX;
		float min_index = 0;
		for(j = 0;j < n;++j)
		{
			if(mymap[j] == false)
			{
				if(min > a[i][j])
				{
					min = a[i][j];
					min_index = j;	
				}	
			}	
		}
		if(min != FLT_MAX)
		{
			c += min;
			mymap[min_index] = true;
			i = min_index;
			//cout << min_index << " --> ";
			vec.push_back(min_index);
		}
		else break;
	}
	return vec;
}

bool acceptance(long double current,long double next,float T)
{
    if(next < current)return true;
    else
    {
        long double p = exp((current - next)/T);
        double r = random_double();
        if(p > r)return true;
        else return false;
    }
}

vector<int> generateNextSolution(vector<int> &vec)
{
  int min = 1;
  int max = vec.size()-1;
  int a = 0,b = 0;
  vector<int> vec1 = vec;
  while(a == b)
  {
      a = random_int_range(min,max);
      b = random_int_range(min,max);
  }
  int temp;
  temp = vec1[a];
  vec1[a] = vec1[b];
  vec1[b] = temp;
  return vec1;
}
void print(vector<int> &vec)
{
    for(int i = 0;i < vec.size();++i)
        cout << vec[i] << " --> ";
    cout << endl;
}


void simulatedAnnealing(int n)
{
    vector<int> vec(n);
    vector<int> vecb(n);
    int i,j,k;
    vec = greedy(n);vecb = vec;
  // for(i = 0;i < n;++i)vec[i] = i,vecb[i] = i;
    float temp = 100000000.0,result = FLT_MAX;
    float rate = 0.03,current = returns_cost(vec),next;
    while(temp > 1)
    {
        vector<int> vec1 = generateNextSolution(vec);
        next = returns_cost(vec1);
        bool acct = acceptance(current,next,temp);
        if(acct == true)
        {
            vec = vec1;current = next;
        }
        if(current < result){result = current;vecb = vec;}
        temp *= (1-rate);
    }
    cost = result;
    print(vecb);
}
int main()
{
    int n = get();
    simulatedAnnealing(n);
    cout << "The cost is " << cost << endl;
	//cout << random_double() << endl;
	return 0;
}

