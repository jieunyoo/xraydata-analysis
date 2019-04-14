import math
from ROOT import gROOT, gStyle, TGaxis, TFile, TH1, TH1D, TH2D, TGraph, TF1, TCanvas

#############
# Constants #
#############

# Fixed
vcalMin           = 0
vcalMax           = 2020
vcalStep          = 20
NROW              = 192
NCOL              = 400
STATIONID         = 3
PLAQID            = 0
ROCID             = 0  

# Set by user
chipName          = "MJ13"
chipDetails       = "2500e_irrad"

# Yarr VCal - charge calibration
def VCal2Charge(VCal) :
  return (-1 + 0.195 * VCal) * 8.2 * 10.0 / 1.6

xMin              = VCal2Charge(vcalMin-vcalStep/2)
xMax              = VCal2Charge(vcalMax-vcalStep/2)
nBins             = (vcalMax - vcalMin)/vcalStep

# Parse text file, return as array
def parsefile(filename) :
  valVsVcal = {} #Dict of 2D arrays per VCal value
  for vcal in range(vcalMin,vcalMax,vcalStep):
    tmpfile = open("%s%d.dat"%(filename,vcal))
    valVsVcal[vcal] = []
    for line in tmpfile.readlines():
      vals = line.split()
      if len(vals) == NCOL:
        vals = [float(val) for val in vals]
        valVsVcal[vcal].append(vals)
    tmpfile.close()
  return valVsVcal

#######################################
# Read .dat files and make .root file #
#######################################

# Load ToT and Occ vs VCal #
totVsVcal = parsefile(chipName+"_MeanTotMap")
print 'Finished loading gain files!'

occVsVcal = parsefile(chipName+"_OccupancyMap-")
print 'Finished loading occupancy files!'

# Book the histograms #
hGainCurves = {}

for i in range(NROW):
  for j in range(NCOL):
    histname = "Station: %d - Plaq: %d - ROC: %d - r: %d - c: %d" % (STATIONID,PLAQID,ROCID,i,j)
    hGainCurves[(i,j)] = TH1D(histname, histname, nBins, xMin, xMax)
    hGainCurves[(i,j)].SetXTitle("charge (electrons)")
    hGainCurves[(i,j)].SetYTitle("ToT")

print 'Finished booking histograms!'
      
# Fill histograms #
for vcal in range(vcalMin,vcalMax,vcalStep):
  injCharge = VCal2Charge(vcal)
  for row in range(NROW):
    for col in range(NCOL):
      tot = totVsVcal[vcal][row][col]
      occ = occVsVcal[vcal][row][col]
      if tot > 0 and occ > 0 :
        hGainCurves[(row,col)].SetBinContent(hGainCurves[(row,col)].FindBin(injCharge),tot)
        hGainCurves[(row,col)].SetBinError(hGainCurves[(row,col)].FindBin(injCharge),math.sqrt(tot/occ))

print 'Finished filling histograms!'

# Write histograms to file #
fileout = TFile(chipName+"_gain_"+chipDetails+".root","RECREATE")

for i in range(NROW):
  for j in range(NCOL):
    hGainCurves[(i,j)].Write()

fileout.Close()

print 'Wrote histograms to file!'

