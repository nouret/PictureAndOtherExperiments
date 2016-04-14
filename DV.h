#include <vector>

int DV(vector<int> PointsX, vector<int> PointsY, vector<vector<int> > & map){
}

int TD(vector<int> & PointsX, vector<int> & PointsY, vector<int> & Colors, (int) L, (int) R, (int) start){
	if (R > (int) PointsX.size()){
		return -1;
	}
	if (R > (int) PointsY.size()){
		return -1;
	}
	if (R > (int) Colors.size()){
		return -1;
	}
	if (R - L < 3){
		for (int _ = L; _ < R; ++_){
			Colors[_] = start;
		}
		return 0;
	}
}