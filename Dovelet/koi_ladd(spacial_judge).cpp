#include <iostream>
#include <memory.h>
using namespace std;

int N, L, K;
int Li[3005], Di[3005], Vi[3005];
double Si[3005];

double elve_time(int a, int b){
	int Da = Di[a], Db = Di[b], awidth = Li[a], bwidth = Li[b], avel = Vi[a], bvel = Vi[b];
	double adis = Si[a] * avel, bdis = Si[a] * bvel, result = Si[a];
	double aleft, bleft, atime, btime;

	if (awidth == L || bwidth == L)
		return result;

	while (adis >= ((L - awidth) * 2)) adis -= ((L - awidth) * 2);
	while (bdis >= ((L - bwidth) * 2)) bdis -= ((L - bwidth) * 2);

	if (adis >= L - awidth){
		Da = (Da + 1) % 2;
		adis -= (L - awidth);
	}
	if (bdis >= L - bwidth){
		Db = (Db + 1) % 2;
		bdis -= (L - bwidth);
	}
	if (Da) aleft = L - adis - awidth;
	else aleft = adis;
	if (Db) bleft = L - bdis - bwidth;
	else bleft = bdis;

	if (!(aleft > bleft + bwidth || bleft > aleft + awidth)){
		return result;
	}
	if (Da != Db){
		if (aleft < bleft && Da){
			adis = aleft;
			bdis = L - bleft - bwidth;
			atime = adis / avel;
			btime = bdis / bvel;
			if (atime < btime){
				aleft = 0;
				bleft += atime * bvel;
				Da = 0;
				result += atime;
			}
			else if (atime == btime){
				aleft = 0;
				bleft = L - bwidth;
				Da = 0;
				Db = 1;
				result += atime;
			}
			else{
				bleft = L - bwidth;
				aleft -= btime * avel;
				Db = 1;
				result += btime;
			}
		}
		if (bleft < aleft && Db){
			adis = L - aleft - awidth;
			bdis = bleft;
			atime = adis / avel;
			btime = bdis / bvel;
			if (btime < atime){
				bleft = 0;
				aleft += btime * avel;
				Db = 0;
				result += btime;
			}
			else if (atime == btime){
				bleft = 0;
				aleft = L - awidth;
				Db = 0;
				Da = 1;
				result += btime;
			}
			else{
				aleft = L - awidth;
				bleft -= atime * bvel;
				Da = 1;
				result += atime;
			}
		}
	}

	if (Da == Db){
		if ((Da && aleft < bleft) || (Da == 0 && aleft > bleft)){
			if (Da){
				adis = aleft;
				bdis = bleft - aleft - awidth;
			}
			else{
				adis = L - aleft - awidth;
				bdis = aleft - bleft - bwidth;
			}
			atime = adis / avel;
			if (bvel > avel){
				btime = bdis / (bvel - avel);
				if (btime <= atime) 
					return result + btime;
			}
			if (aleft < bleft){
				aleft = 0;
				bleft -= atime * bvel;
				Da = 0;
			}
			else{
				aleft = L - awidth;
				bleft += atime * bvel;
				Da = 1;
			}
			result += atime;
		}
		else{
			if (Db){
				bdis = bleft;
				adis = aleft - bleft - bwidth;
			}
			else{
				bdis = L - bleft - bwidth;
				adis = bleft - aleft - awidth;
			}
			btime = bdis / bvel;
			if (avel > bvel){
				atime = adis / (avel - bvel);
				if (atime <= btime) 
					return result + atime;
			}
			if (bleft < aleft){
				bleft = 0;
				aleft -= btime * avel;
				Db = 0;
			}
			else{
				bleft = L - bwidth;
				aleft += btime * avel;
				Db = 1;
			}
			result += btime;
		}
	}

	if (aleft < bleft)
		adis = bleft - aleft - awidth;
	else
		adis = aleft - bleft - bwidth;
	
	atime = adis / (avel + bvel);

	return result + atime;
}

void set_table(){
	double temp;
	for (int i = 1; i < N; i++){
		for (int j = i + 1; j - i <= K; j++){
			if (j <= N){
				temp = elve_time(i, j);
				if (Si[j] < 0) Si[j] = temp;
				else if (temp < Si[j]) Si[j] = temp;
			}
		}
	}
}

int main(){
	cout.setf(ios::fixed);
	cout.precision(5);

	cin >> N >> L >> K;

	for (int i = 1; i <= N; i++){
		cin >> Li[i] >> Di[i] >> Vi[i];
	}

	memset(Si, -100, sizeof(Si));
	Si[1] = 0.0;
	set_table();

	cout << Si[N] << endl;

	return 0;
}