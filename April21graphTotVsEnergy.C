void April21graphTotVsEnergy() {

	TCanvas* c1 = new TCanvas("c1", "errors", 200,100,700,500);
	c1->SetGrid();
	c1->GetFrame()->SetBorderSize(12);

	//only put Ag, Sn, In on it (change n = 3 to n = 4 in case of 4 foils, and adjust other data appropriately)
	const int n = 3;
	
	//Ag, In, Sn
	Float_t x[n] = {22.16291, 24.20975, 25.27136};

	Float_t y[n] = {8.309,9.975,10.78};

	//Float_t ex[n] = {1., 1., 1.};
	//Float_t ey[n] = {1., 1., 1.};

	gStyle->SetOptFit(0001);

	TGraphErrors* gr = new TGraphErrors(n,x,y);
	gr->SetTitle("X-ray Calibration; energy(keV);ToT");
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(21);
	gr->Draw("AP");

	
	
	TF1* linearFit = new TF1("line0","[0]*x+[1]");
	linearFit->SetParameters(7,1);
	gr->Fit(linearFit);
	c1->Modified();
	c1->Update();
}
