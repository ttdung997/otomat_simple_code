#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int m, n, k; 	// m: so trang thai
			// n: so chu cai trong bang chu cai A
			// k: so trang thai ket thuc

int pb[100][100], f[100], hc[100][100];
int ddm[100], hcm[100][100];
int nh[100];
int nhom = 0;
vector<bool> dd(m, false);

void khoitao(){               			
	// Kiem tra trang thai i co thuoc tap cac trang thai ket thuc khong
	for(int i_k= 0;i_k< k;i_k++){
		dd[f[i_k]] = true;
	}	

	for(int i_m = 0; i_m < m; i_m++){
		if(dd[i_m] == false)
			for(int i_k = 0; i_k < k; i_k++)
				if(i_m != f[i_k]){
					pb[i_m][f[i_k]] = 1;
					pb[f[i_k]][i_m] = 1;
				}
	}	
}

void bang_trang_thai_pb(){
	int d = 1;
	bool ok = true;
	while(ok){
		ok = false;
		d++;
		for(int p= 0 ; p < m;p++)
			for(int q = (p + 1); q < m; q++)
				if(pb[p][q] == 0){
					for (int a = 0; a < n; a++)
						if(hc[p][a] != -1 && hc[q][a] != -1){
							int pa = hc[p][a];
							int qa = hc[q][a];                                 
							if(pb[pa][qa] != 0){
								pb[p][q] = d;
								pb[q][p] = d;
								ok = true;	
							}
						}
				}
	}	
}

void nhom_trang_thai_tuong_duong(){
	memset(ddm, 0, sizeof(ddm));
	for (int p= 0; p < m; p++) nh[p] = -1;
	nh[0] = 0;
	for (int p = 0; p < m; p++){
		if(nh[p] == -1){
			nhom += 1;
			nh[p] = nhom;
		}
		for(int q = 0; q < m; q++){
			if(pb[p][q] == 0) nh[q] = nh[p];	
		}	
	}      
	nhom++; 
	for (int i = 0;i < k;i++){
		ddm[nh[f[i]]] = 1;
	}          
}

void ham_chuyen_moi(){
	for (int i = 0;i < nhom;i++)
		for(int a = 0; a < n;a++){
			hcm[i][a] = -1;
			for(int p = 0; p < m; p++)
				if(nh[p] == i && hc[p][a] != -1){
					hcm[i][a] = nh[hc[p][a]];
					break;		
				}
		}	
}

int main(){
	ifstream fi("input.txt");
	ofstream fo("output.txt");
	fi >> m >> n >> k;
                                   
	// Nhap cac trang thai ket thuc
	for(int i_k = 0;i_k < k;i_k++)
		fi >> f[i_k];
	// Nhap ham chuyen
	for(int i_m = 0; i_m < m; i_m++)
		for(int i_n = 0;i_n < n; i_n++)
			fi >> hc[i_m][i_n];
	// Thuc hien buoc 1
	khoitao();
	bang_trang_thai_pb();
	nhom_trang_thai_tuong_duong();
	ham_chuyen_moi();
	fo << "Bang trang thai phan biet:\n";
	for (int i_m = 0;i_m < m; i_m++){
		for (int j_m = 0;j_m < m; j_m++){
			fo << pb[i_m][j_m] << ' ';
		}
		fo << '\n';
	}
	fo << "\nDFA toi thieu: M = (Q, A, q0, F, hcm)\n";
	fo << "Q = {";
	for(int i = 0; i < nhom; i++){
		fo << i << ((i != nhom - 1)?", ":"");	
	}
	fo << "}\n";
	fo << "q0 = 0\n";
	fo << "F = {";
	bool ok = true;
	for (int i = 0;i < nhom; i++) 
		if(ddm[i] == 1){
			fo << ((ok == true)? "":", ") << i;
			ok = false;
		}
	fo << "}\n";
	fo << "\nHam chuyen hcm:\n";
	fo << "  | ";
	for(int i = 0;i < n; i++) fo << i << ' ';
	fo << '\n';
	for(int i = 0;i < (3*(n+1)); i++) fo << "-";
	fo << '\n';
	for(int i = 0; i < nhom; i++){
		fo << i << " | ";
		for(int a = 0; a < n; a++)
			fo << hcm[i][a] << ' ';
		fo << '\n';
	} 
	
	fi.close();
	fo.close();
	return 0;
}
                                   
