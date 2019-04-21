//this uses 2 files:
//1) Mo.dat (which is the data for the Mo foil)
//2) MoCu.dat (which is the Cu foil corresponding to the Mo foil).

void foilSubtractionMo() {
	
//	TFile* foil1 = new TFile("foil1.root", "CREATE");

	//open the foil histogram, and plot its contents
	ifstream in;
	
	TH1F* histo1 = new TH1F("histo1", "Mo histo", 16,0,16);
	int x;

	in.open("Mo.dat");

	//histo1->Sumw2();
	for (int i = 0; i < 16; i++) {
			in >> x;
			histo1->SetBinContent(i+1,x);
	}
	//histo1->Draw();

	double foilNonPeak = histo1->Integral(0,6) + histo1->Integral(9,16);
	
	std::cout << "foilNonPeak value  " << foilNonPeak << std::endl;
	std::cout << "number of entries in foil histogram: " << histo1->GetEntries() << std::endl;
	std::cout << "get number bins:  " << histo1->GetNbinsX() << std::endl;
	//std::cout << "get max. bin " << histo1->GetMaximumBin() << std::endl;
	std::cout << "get integral 0 to 6 " << histo1->Integral(0,6) << std::endl;
	std::cout << "get integral 9 to 16 " << histo1->Integral(9,16) << std::endl;
	//std::cout << "getXaxis()->GetBinCenter(binmax) " << histo1->GetXaxis()->GetBinCenter(histo1->GetMaximumBin()) << std::endl;

	//****************************************************************************************
	//Cu histogram
	ifstream in2;
	TH1F* histo2 = new TH1F("histo2", "Mo (Cu background subtracted)", 16,0,16);
	int y;

	in2.open("MoCu.dat");

	//histo2->Sumw2();
	for (int i = 0; i < 16; i++) {
			in2 >> y;
			histo2->SetBinContent(i+1,y);
	}

	//histo2->Draw();

	std::cout << "number of entries in Cu histo: " << histo2->GetEntries() << std::endl;
	std::cout << "get number bins:  " << histo2->GetNbinsX() << std::endl;
	std::cout << "get integral 0 to 1 " << histo2->Integral(0,1) << std::endl;
	std::cout << "get integral 4 to 16 " << histo2->Integral(4,16) << std::endl;

	double copperNonPeak = histo2->Integral(0,1) + histo2->Integral(4,16);


	//****************************************************************************************
	
	std::cout << "foil NonPeak Integral " << foilNonPeak << std::endl;
	std::cout << "copperNonPeak Integral  " << copperNonPeak << std::endl;

	double ratioFactor = foilNonPeak/copperNonPeak;
	std::cout << "ratioFactor: " << ratioFactor << std::endl;
	
	//multiply the copper histogram by the ratio factor
	histo2->Scale(ratioFactor);

	//subtract the copper histogram from the Mo histogram
	histo2->Add(histo2,histo1,-1,1);

	//histo2->Draw();

	//********************************************************************************
	//fit
	TCanvas* canvas1 = new TCanvas;
	
	TF1* gausFit = new TF1("gaussFit", "gaus", 1,15);
	histo2->Fit("gaussFit", "R");
	histo2->GetXaxis()->SetTitle("ToT");
	histo2->GetYaxis()->SetTitle("Number of Hits");

	canvas1->Modified();
	canvas1->Update();

	TPaveStats* ps = (TPaveStats*)histo2->FindObject("stats");

	ps->SetOptFit(1);
		
	canvas1->Modified();
	canvas1->cd();

	canvas1->Print("MillsFitMoCuSubtracted.png");
	//foil1->Write();
	//foil1->Close();
}
