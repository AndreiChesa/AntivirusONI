#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

ifstream f("antivirus.in");
ofstream g("antivirus.out");

int teste;
int n, k;
const int NMAX = 2005;
int valori[NMAX];
int dp[NMAX][NMAX];
int sume[NMAX];

int main()
{
	f >> teste;
	while (teste--)
	{
		f >> n >> k;
		for (int i = 1; i <= n; i++)
		{
			f >> valori[i];
			if(valori[i] == 0)
				k--;
			sume[i] = sume[i - 1] + valori[i];
		}

		for (int i = 0; i <= n; i++)
		{
			for (int j = 0; j <= k; j++)
			{
				dp[i][j] = 1e9;
			}
		}

		for(int i = 0; i <= n; i++)
		{
			dp[i][0] = 0;
		}

		int last = 0;

		for (int i = 1; i <= n; i++)
		{
			if (valori[i] > 0)
			{
				if (last > 0)
				{
					for (int j = k; j >= 1; j--)
					{
						dp[i][j] = dp[i - 1][j];
						if (j - (i - last) >= 0 && dp[last][j - (i - last)] != 1e9)
						{
							dp[i][j] = min(dp[i][j], dp[last][j - (i - last)] + sume[i] - sume[last]);
						}
					}
				}
			}
			else {
				for (int j = 1; j <= k; j++)
				{
					dp[i][j] = dp[i - 1][j];
					for (int x = i - 1; x >= last; x--)
					{
						if (j - (i - x - 1) >= 0 && dp[x][j - (i - x - 1)] != 1e9)
						{
							dp[i][j] = min(dp[i][j], dp[x][j - (i - x - 1)] + sume[i] - sume[x]);
						}
					}
				}
				last = i;
			}
		}

		int ans = dp[n][k];
		g << ans << '\n';
	}
}