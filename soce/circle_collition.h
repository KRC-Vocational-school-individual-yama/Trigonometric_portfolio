#pragma once
bool circlecollition(int my_x,int my_y,int my_r,int ene_x,int ene_y,int ene_r) {
	int x=my_x-ene_x;
	int y=my_y-ene_y;
	int radius_distance=my_r+ene_r;
	if (x* x+y*y<=radius_distance*radius_distance) return true;
	return false;
}