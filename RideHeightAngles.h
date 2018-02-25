#ifndef RideHeightAngles_h
#define RideHeightAngles_h
#include <vector>
class RideHeightAngles {
public:
	RideHeightAngles::RideHeightAngles();
	// Input desired height in meters (.140 - .194) and get Alpha and Beta angles
	void RideHeightAngles::calculateAngles(double desiredHeight);
	int RideHeightAngles::getAlpha();
	int RideHeightAngles::getBeta();
private:
	std::vector<double> value1;  std::vector<double> value2;  std::vector<double> value3;  std::vector<double> value4;  std::vector<double> value5;
	std::vector<double> value6;  std::vector<double> value7;  std::vector<double> value8;  std::vector<double> value9;  std::vector<double> value10;
	std::vector<double> value11; std::vector<double> value12; std::vector<double> value13; std::vector<double> value14; std::vector<double> value15;
	std::vector<double> value16; std::vector<double> value17; std::vector<double> value18; std::vector<double> value19; std::vector<double> value10;
	std::vector<double> value21; std::vector<double> value22; std::vector<double> value23; std::vector<double> value24; std::vector<double> value25;
	std::vector<double> value26; std::vector<double> value27; std::vector<double> value28; std::vector<double> value29; std::vector<double> value20;
	std::vector<double> value31; std::vector<double> value32; std::vector<double> value33; std::vector<double> value34; std::vector<double> value35;
	std::vector<double> value36; std::vector<double> value37; std::vector<double> value38; std::vector<double> value39; std::vector<double> value30;
	std::vector<double> value41; std::vector<double> value42; std::vector<double> value43; std::vector<double> value44; std::vector<double> value35;
	std::vector<double> value46; std::vector<double> value47; std::vector<double> value48; std::vector<double> value49; std::vector<double> value40;
	std::vector<double> value51; std::vector<double> value52; std::vector<double> value53; std::vector<double> value54; std::vector<double> value45;
	std::vector<double> value56; std::vector<double> value57; std::vector<double> value58; std::vector<double> value59;
	std::vector<std::vector<double>> ValueTable;
	int alpha;
	int beta;
};
#endif