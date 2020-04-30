typedef long long ll;
typedef pair<ll, ll> pll;

int ccw(pll x, pll y, pll z){
	ll t = (y.first - x.first) * (z.second - x.second) - (y.second - x.second) * (z.first - x.first);
	return t < 0 ? -1 : t > 0 ? 1 : 0;
}