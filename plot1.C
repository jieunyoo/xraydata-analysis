void plot1() {


		TFile* file1 = new TFile("file1.root", "READ");
		TH1D *histo1 = (TH1D*)file1->Get("r:191-c:203");


		TCanvas* canvas1 = new TCanvas;

		TF1* linearFit = new TF1("line0","[0]*x+[1]",3500,5500);
		linearFit->SetParameters(1,2);
		histo1->Fit(linearFit,"","",3500,8500);

		
		//Move the stats box to the right-hand corner
		canvas1->Modified();
		canvas1->Update();
		TPaveStats* ps = (TPaveStats*)histo1->FindObject("stats");

		ps->SetX1NDC(ps->GetX1NDC()-0.1);
		ps->SetX2NDC(ps->GetX2NDC()-0.1);
		ps->SetY1NDC(ps->GetY1NDC()-0.6);
		ps->SetY2NDC(ps->GetY2NDC()-0.6);
		canvas1->Modified();
		canvas1->cd();
}
