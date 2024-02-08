#include "TkrData.h"

TkrData::TkrData(int eventNumber)
{
  this->eventNumber = eventNumber;
	nLayers = 0;
	stripPitch = 0.228;
	zLayer.reserve(8);
	orientation.reserve(8);
	ladderOffsetLeft.reserve(8);
	ladderOffsetRight.reserve(8);
	hits.reserve(8);
	xHitMC.reserve(8);
	yHitMC.reserve(8);
}

void TkrData::addLyr(char orient, double z, double offsetLeft, double offsetRight) {
	nLayers++;
	zLayer.push_back(z);
	orientation.push_back(orient);
	ladderOffsetLeft.push_back(offsetLeft);
	ladderOffsetRight.push_back(offsetRight);
	vector<double> hitList;
	hits.push_back(hitList);
	vector<double> xhits;
	xHitMC.push_back(xhits);
	vector<double> yhits;
	yHitMC.push_back(yhits);
	vector<double> xPR;
	xHitPR.push_back(xPR);
	vector<double> yPR;
	yHitPR.push_back(yPR);
	vector<double> sig;
	sigma.push_back(sig);
}

void TkrData::print(string s) {
	cout << "Event " << eventNumber << " RK tracker data " << s << "  Number of layers = " << nLayers << endl;
	for (int lyr = 0; lyr < nLayers; lyr++) {
		cout << "    Layer " << lyr << " orientation is " << orientation[lyr];
		cout << "  z = " << zLayer[lyr] << "  Offsets= " << ladderOffsetLeft[lyr] << " " << ladderOffsetRight[lyr] << endl;
		cout << "          Hits = ";
		for (unsigned int hit = 0; hit < hits[lyr].size(); hit++) {
			cout << hits[lyr].at(hit) << "+-" << sigma[lyr].at(hit) << " ";
		}
		cout << endl;
	}
}

void TkrData::addHit(int layer, double value, int nStrips) {
	addHit(layer, value, nStrips, 0., 0., 0., 0.);
}

void TkrData::addHit(int layer, double value, int nStrips, double xMC, double yMC, double xPR, double yPR) {
	if (layer < nLayers) {
		hits[layer].push_back(value);
		xHitMC[layer].push_back(xMC);
		yHitMC[layer].push_back(yMC);
		xHitPR[layer].push_back(xPR);
		yHitPR[layer].push_back(yPR);
		double sigma;
		if (nStrips == 1) {
			sigma = stripPitch / sqrt(12.0);
		}
		else if (nStrips == 2) {
			sigma = stripPitch / sqrt(24.0);
		}
		else {
			sigma = 2.0 * stripPitch / sqrt(12.0);
		}
		this->sigma[layer].push_back(sigma);
	}
	else {
		cout << "TkrData::addLyr: layer " << layer << " is not yet defined" << endl;
	}
}

void TkrData::clrHits() {
	for (int layer = 0; layer < nLayers; layer++) {
		hits[layer].clear();
		sigma[layer].clear();
		xHitMC[layer].clear();
		yHitMC[layer].clear();
		xHitPR[layer].clear();
		yHitPR[layer].clear();
	}
}

TkrData::~TkrData()
{
	zLayer.clear();
	orientation.clear();
	ladderOffsetLeft.clear();
	ladderOffsetRight.clear();
	for (int lyr = 0; lyr < nLayers; lyr++) hits.at(lyr).clear();
	hits.clear();
	sigma.clear();
	yHitMC.clear();
	xHitMC.clear();
	xHitPR.clear();
	yHitPR.clear();
}


