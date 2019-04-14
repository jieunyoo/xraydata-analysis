void exponFit() {


		TFile* file1 = new TFile("file1.root", "READ");
		TH1D *histo1 = (TH1D*)file1->Get("r:191-c:203");


		TCanvas* canvas1 = new TCanvas;

		TF1* exponFit = new TF1("exponFit", "expo", 3500,8500);

		histo1->Fit("exponFit","R");
		
		//Move the stats box to the right-hand corner
		canvas1->Modified();
		canvas1->Update();
		TPaveStats* ps = (TPaveStats*)histo1->FindObject("stats");
		ps->SetX1NDC(ps->GetX1NDC()-0.1);
		ps->SetX2NDC(ps->GetX2NDC()-0.1);
		ps->SetY1NDC(ps->GetY1NDC()-0.6);
		ps->SetY2NDC(ps->GetY2NDC()-0.6);

		//Show statistics
		TList* list = ps->GetListOfLines();
		ps->SetOptFit(1);
		
		canvas1->Modified();
		canvas1->cd();


		//TF1* fitResult = histo1->GetFunction("line0");
		//std::cout << "ChiSquare: " << fitResult->GetChisquare() << endl;
		//std::cout << "NDOF: " << fitResult->GetNDF() << endl;
		//std::cout << "Prob. experiments. give X^2 greater than or equal to above X^2: " << fitResult->GetProb() << endl;
		//std::cout << " " << endl;
				
}
