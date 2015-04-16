/**
 * \file AliReducedHighPtEventCreator.h
 * \brief Declaration of class AliReducedHighPtEventCreator and AliReducedTrackSelectionContainer
 *
 * \author Markus Fasel <markus.fasel@cern.ch>, Lawrence Berkeley National Laboratory
 * \date Apr 15, 2015
 */
#ifndef ALIREDUCEDHIGHPTEVENTCREATOR_H
#define ALIREDUCEDHIGHPTEVENTCREATOR_H
/* Copyright(c) 1998-2015, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

#include "AliAnalysisTaskEmcal.h"

class TArrayI;
class TTree;
class TObjArray;

class AliVCluster;
class AliVEvent;
class AliVParticle;

namespace EMCalTriggerPtAnalysis{
class AliEMCalPtTaskVTrackSelection;
}

namespace HighPtTracks {

class AliReducedHighPtEvent;
class AliReducedPatchContainer;

/**
 * \class AliReducedTrackSelectionContainer
 * \brief Helper class mapping a virtual track selection to a cut index
 */
class AliReducedTrackSelectionContainer : public TObject{
public:
  AliReducedTrackSelectionContainer();
  AliReducedTrackSelectionContainer(Int_t index, EMCalTriggerPtAnalysis::AliEMCalPtTaskVTrackSelection * sel);
  virtual ~AliReducedTrackSelectionContainer();

  /**
   * Set the index of the track selection
   * \param inde Index of the track selection
   */
  void SetIndex(Int_t index) { fIndex = index; }
  /**
   * Set the underlying track selection
   * \param trackSelection Underlying track selection
   */
  void SetTrackSelection(EMCalTriggerPtAnalysis::AliEMCalPtTaskVTrackSelection *trackSelection) { fTrackSelection = trackSelection;}

  /**
   * Get the index of the track selection
   * \return Index of the track selection
   */
  Int_t GetIndex() const { return fIndex; }
  /**
   * Get the underlying track selection
   * \return underlying track selection
   */
  EMCalTriggerPtAnalysis::AliEMCalPtTaskVTrackSelection *GetTrackSelection() const { return fTrackSelection; }

protected:
  Int_t                                                           fIndex;               ///< Index of the cut
  EMCalTriggerPtAnalysis::AliEMCalPtTaskVTrackSelection           *fTrackSelection;     ///< Virtual track selection

private:
  AliReducedTrackSelectionContainer(AliReducedTrackSelectionContainer &);
  AliReducedTrackSelectionContainer &operator=(AliReducedTrackSelectionContainer &);

  /// \cond CLASSIMP
  ClassDef(AliReducedTrackSelectionContainer, 1);
  /// \endcond
};

/**
 * \class AliReducedHighPtEventCreator
 * \brief Producer task of reduced high-\f$ p_{t} \f$ events
 */
class AliReducedHighPtEventCreator: public AliAnalysisTaskEmcal {
public:
  AliReducedHighPtEventCreator();
  AliReducedHighPtEventCreator(const char *name);
  virtual ~AliReducedHighPtEventCreator();

  virtual void UserCreateOutputObjects();
  virtual Bool_t Run();

  void AddVirtualTrackSelection(EMCalTriggerPtAnalysis::AliEMCalPtTaskVTrackSelection * sel, Int_t index);
  /**
   * Define if trigger thresholds are swapped
   * \param doswap if true then thresholds are swapped
   */
  void SetSwapTriggerThresholds(Bool_t doswap) { fSwapTriggerThresholds = doswap; }
  /**
   * Set the energy range for clusters
   * \param minE Minimum
   * \param maxE Maximum
   */
  void SetClusterEnergyCut(Double_t minE, Double_t maxE) {
    fMinClusterE = minE;
    fMaxClusterE = maxE;
  }
  /**
   * Set the \f$ p_{t} \f$ range for particles and tracks
   * \param minpt Minimum
   * \param maxpt Maximum
   */
  void SetPtRange(Double_t minpt, Double_t maxpt){
    fMinPt = minpt;
    fMaxPt = maxpt;
  }
  /**
   * Set the \f$ \eta \f$ range for particles and tracks
   * \param mineta Minimum
   * \param maxeta Maximum
   */
  void SetEtaRange(Double_t mineta, Double_t maxeta){
    fMinEta = mineta;
    fMaxEta = maxeta;
  }

protected:
  Bool_t SelectEvent(AliVEvent *event) const;
  Bool_t SelectParticle(const AliVParticle *part) const;
  Bool_t SelectCluster(const AliVCluster *clust) const;
  Int_t  SelectTrack(AliVTrack *track, TArrayI &cutindices) const;
  void ConvertTriggerPatches(TClonesArray *patches, AliReducedPatchContainer *cont);
  void FixTrackInputEvent(AliVTrack *trk);
  Int_t GetTPCCrossedRows(const AliVTrack *trk) const;
  TTree                   *fOutputTree;                   ///< Output tree
  AliReducedHighPtEvent   *fOutputEvent;                  ///< Output event
  TObjArray               *fTrackSelections;              ///< List of track selections

  Bool_t                    fSwapTriggerThresholds;       ///< Switch for swapping of the thresholds
  Double_t                  fMinClusterE;                 ///< Min. cluster E
  Double_t                  fMaxClusterE;                 ///< Max. cluster E
  Double_t                  fMinPt;                       ///< Min. track \f$ p_{t} \f$
  Double_t                  fMaxPt;                       ///< Max. track \f$ p_{t} \f$
  Double_t                  fMinEta;                      ///< Min. track \f$ \eta \f$
  Double_t                  fMaxEta;                      ///< Max. track \f$ \eta \f$

private:
  AliReducedHighPtEventCreator(const AliReducedHighPtEventCreator &);
  AliReducedHighPtEventCreator &operator=(const AliReducedHighPtEventCreator &);

  /// \cond CLASSIMP
  ClassDef(AliReducedHighPtEventCreator, 1)
  /// \CLASSIMP
};

} /* namespace HighPtTracks */

#endif /* ALIREDUCEDHIGHPTEVENTCREATOR_H */
