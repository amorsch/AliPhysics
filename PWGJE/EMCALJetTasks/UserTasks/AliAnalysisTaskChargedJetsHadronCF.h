#ifndef ALIANALYSISTASKCHARGEDJETSHADRONCF_H
#define ALIANALYSISTASKCHARGEDJETSHADRONCF_H

// $Id$

class TH1;
class TH2;
class TH3;
class AliJetContainer;
class AliParticleContainer;
class AliClusterContainer;

#include "AliAnalysisTaskEmcalJet.h"

class AliAnalysisTaskChargedJetsHadronCF : public AliAnalysisTaskEmcalJet {
 public:

  AliAnalysisTaskChargedJetsHadronCF();
  AliAnalysisTaskChargedJetsHadronCF(const char *name);
  virtual ~AliAnalysisTaskChargedJetsHadronCF();

  void                        UserCreateOutputObjects();
  void                        Terminate(Option_t *option);

  // ######### SETTERS/GETTERS
  void                        SetJetParticleArrayName(const char* name) { fJetParticleArrayName = name; }

  void                        SetEventCriteriumBackground(Double_t minValue, Double_t maxValue)   {fEventCriteriumMinBackground = minValue; fEventCriteriumMaxBackground = maxValue;}
  void                        SetEventCriteriumLeadingJets(Double_t leading, Double_t subleading) {fEventCriteriumMinLeadingJetPt = leading; fEventCriteriumMinSubleadingJetPt = subleading;}

  void                        SetEventCriteriumSelection(Int_t type);

 protected:
  void                        ExecOnce();
  Bool_t                      FillHistograms()   ;
  Bool_t                      Run()              ;

  AliJetContainer            *fJetsCont;                                //!Jets
  AliParticleContainer       *fTracksCont;                              //!Tracks
  Int_t                       fNumberOfCentralityBins;                  // Number of centrality bins
  TClonesArray               *fJetsOutput;                              //!Array of basic correlation particles attached to the event
  TString                     fJetParticleArrayName;                    // Name of fJetsOutput array

  // Criteria for the selection of jets that are passed to the correlation task
  Int_t                       fEventCriteriumMode;                      // Mode of event selection
  Double_t                    fEventCriteriumMinBackground;             // Minimum background
  Double_t                    fEventCriteriumMaxBackground;             // Maximum background
  Double_t                    fEventCriteriumMinLeadingJetPt;           // Min leading jet
  Double_t                    fEventCriteriumMinSubleadingJetPt;        // Min subleading jet
  // ######### HISTOGRAM FUNCTIONS
  void                        FillHistogram(const char * key, Double_t x);
  void                        FillHistogram(const char * key, Double_t x, Double_t y);
  void                        FillHistogram(const char * key, Double_t x, Double_t y, Double_t add);
  template <class T> T*       AddHistogram1D(const char* name = "CustomHistogram", const char* title = "NO_TITLE", const char* options = "", Int_t xBins = 100, Double_t xMin = 0.0, Double_t xMax = 20.0, const char* xTitle = "x axis", const char* yTitle = "y axis");
  template <class T> T*       AddHistogram2D(const char* name = "CustomHistogram", const char* title = "NO_TITLE", const char* options = "", Int_t xBins = 100, Double_t xMin = 0.0, Double_t xMax = 20.0, Int_t yBins = 100, Double_t yMin = 0.0, Double_t yMax = 20.0,  const char* xTitle = "x axis", const char* yTitle = "y axis", const char* zTitle = "z axis");

  // ######### HELPER FUNCTIONS
  AliEmcalJet*                GetSubleadingJet(const char* opt);


 private:
  AliAnalysisTaskChargedJetsHadronCF(const AliAnalysisTaskChargedJetsHadronCF&);            // not implemented
  AliAnalysisTaskChargedJetsHadronCF &operator=(const AliAnalysisTaskChargedJetsHadronCF&); // not implemented

  ClassDef(AliAnalysisTaskChargedJetsHadronCF, 1) // Charged jet+h analysis task
};
#endif