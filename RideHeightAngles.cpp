#include <RideHeightAngles.h>
#include <vector>

int alpha = 0;
int beta = 0;

RideHeightAngles::RideHeightAngles() {

}

// Value = { Y Height in Meters, Z Offset in Meters, Alpha Angle in Degrees, Beta Angle in Degrees}
// Values computed using MATLAB 'RideHeightTableGeneratorV2.m' file. Refer to it for more information.
std::vector<double> value1 = { 0.194000,0.000000,0,0 };
std::vector<double> value2 = { 0.193970,0.000698,-1,2 };
std::vector<double> value3 = { 0.193935,-0.000645,-2,3 };
std::vector<double> value4 = { 0.193823,0.000053,-3,5 };
std::vector<double> value5 = { 0.193652,0.000752,-4,7 };
std::vector<double> value6 = { 0.193547,-0.000588,-5,8 };
std::vector<double> value7 = { 0.193293,0.000113,-6,10 };
std::vector<double> value8 = { 0.192981,0.000813,-7,12 };
std::vector<double> value9 = { 0.192805,-0.000519,-8,13 };
std::vector<double> value10 = { 0.192411,0.000184,-9,15 };
std::vector<double> value11 = { 0.191958,0.000888,-10,17 };
std::vector<double> value12 = { 0.191713,-0.000434,-11,18 };
std::vector<double> value13 = { 0.191179,0.000274,-12,20 };
std::vector<double> value14 = { 0.190586,0.000982,-13,22 };
std::vector<double> value15 = { 0.190272,-0.000325,-14,23 };
std::vector<double> value16 = { 0.189599,0.000388,-15,25 };
std::vector<double> value17 = { 0.189240,-0.000907,-16,26 };
std::vector<double> value18 = { 0.188486,-0.000188,-17,28 };
std::vector<double> value19 = { 0.187675,0.000531,-18,30 };
std::vector<double> value20 = { 0.187248,-0.000743,-19,31 };
std::vector<double> value21 = { 0.186358,-0.000016,-20,33 };
std::vector<double> value22 = { 0.185410,0.000711,-21,35 };
std::vector<double> value23 = { 0.184918,-0.000540,-22,36 };
std::vector<double> value24 = { 0.183892,0.000196,-23,38 };
std::vector<double> value25 = { 0.182811,0.000931,-24,40 };
std::vector<double> value26 = { 0.182253,-0.000292,-25,41 };
std::vector<double> value27 = { 0.181095,0.000453,-26,43 };
std::vector<double> value28 = { 0.180495,-0.000750,-27,44 };
std::vector<double> value29 = { 0.179261,0.000006,-28,46 };
std::vector<double> value30 = { 0.177971,0.000761,-29,48 };
std::vector<double> value31 = { 0.177310,-0.000409,-30,49 };
std::vector<double> value32 = { 0.175946,0.000358,-31,51 };
std::vector<double> value33 = { 0.175244,-0.000787,-32,52 };
std::vector<double> value34 = { 0.173807,-0.000008,-33,54 };
std::vector<double> value35 = { 0.172316,0.000771,-34,56 };
std::vector<double> value36 = { 0.171555,-0.000336,-35,57 };
std::vector<double> value37 = { 0.169993,0.000456,-36,59 };
std::vector<double> value38 = { 0.169194,-0.000624,-37,60 };
std::vector<double> value39 = { 0.167562,0.000182,-38,62 };
std::vector<double> value40 = { 0.166725,-0.000869,-39,63 };
std::vector<double> value41 = { 0.165878,0.000989,-39,64 };
std::vector<double> value42 = { 0.165023,-0.000048,-40,65 };
std::vector<double> value43 = { 0.163272,0.000773,-41,67 };
std::vector<double> value44 = { 0.162381,-0.000234,-42,68 };
std::vector<double> value45 = { 0.160562,0.000603,-43,70 };
std::vector<double> value46 = { 0.159637,-0.000372,-44,71 };
std::vector<double> value47 = { 0.157752,0.000481,-45,73 };
std::vector<double> value48 = { 0.156794,-0.000461,-46,74 };
std::vector<double> value49 = { 0.154844,0.000408,-47,76 };
std::vector<double> value50 = { 0.153854,-0.000499,-48,77 };
std::vector<double> value51 = { 0.151842,0.000387,-49,79 };
std::vector<double> value52 = { 0.150820,-0.000485,-50,80 };
std::vector<double> value53 = { 0.148746,0.000419,-51,82 };
std::vector<double> value54 = { 0.147695,-0.000417,-52,83 };
std::vector<double> value55 = { 0.145561,0.000506,-53,85 };
std::vector<double> value56 = { 0.144481,-0.000294,-54,86 };
std::vector<double> value57 = { 0.142290,0.000648,-55,88 };
std::vector<double> value58 = { 0.141182,-0.000113,-56,89 };
std::vector<double> value59 = { 0.140062,-0.000855,-57,90 };
std::vector<std::vector<double>> ValueTable = {
	value1,value2,value3,value4,value5,value6,value7,value8,value9,value10,
	value11,value12,value13,value14,value15,value16,value17,value18,value19,value20,
	value21,value22,value23,value24,value25,value26,value27,value28,value29,value30,
	value31,value32,value33,value34,value35,value36,value37,value38,value39,value40,
	value41,value42,value43,value44,value45,value46,value47,value48,value49,value50,
	value51,value52,value53,value54,value55,value56,value57,value58,value59
};

// Find closest angle values to reach desired height
void RideHeightAngles::calculateAngles(double desiredHeight) {
	int closestValue = 0;
	double difference = 10.0;
	for (int i = 0; i < Table.size(); i++) {
		if (abs(ValueTable(i)(0) - desiredHeight) < difference) {
			difference = abs(ValueTable(i)(0) - desiredHeight);
			closestValue = i;
		}
	}
	alpha = ValueTable(closestValue)(2);
	beta = ValueTable(closestValue)(3);
}

int RideHeightAngles::getAlpha() {
	return alpha;
}

int RideHeightAngles::getBeta() {
	return beta;
}