//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1SteppingAction.cc
/// \brief Implementation of the B1SteppingAction class

#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "g4csv.hh"

#include "cmath"
#include "cstring"
#include "fstream"


using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::B1SteppingAction(B1EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::~B1SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1SteppingAction::UserSteppingAction(const G4Step* step)
{
  int eid = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
  G4String volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume()->GetMaterial()->GetName();
 // G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
  // G4double KE = step->GetPreStepPoint()->GetKineticEnergy();
  //G4double LOCALTIME = step->GetPreStepPoint()->GetLocalTime();
 //G4ThreeVector momentum = step->GetPreStepPoint()->GetMomentum();
 //G4ThreeVector position = step->GetPreStepPoint()->GetPosition ();

  //G4cout<< position<<endl; //<<" "<< momentum << " "<< LOCALTIME << " "<< KE <<G4endl;
   //int ColId = 0;
    //G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  // Fill ntuple
/*
  G4String current_volume_name  = step->GetPreStepPoint()->GetTouchableHandle() ->GetVolume()->GetLogicalVolume()->GetName();
  analysisManager->FillNtupleDColumn(0, G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID());
  analysisManager->FillNtupleDColumn(1, step->GetPreStepPoint()->GetKineticEnergy());
  analysisManager->FillNtupleDColumn(2, step->GetPreStepPoint()->GetMomentum().x());
  analysisManager->FillNtupleDColumn(3, step->GetPreStepPoint()->GetMomentum().y());
  analysisManager->FillNtupleDColumn(4, step->GetPreStepPoint()->GetMomentum().z());
  analysisManager->AddNtupleRow();*/ // Original steps as told by sir
  //G4String current_volume_name  = step->GetPreStepPoint()->GetTouchableHandle() ->GetVolume()->GetLogicalVolume()->GetName();
  

   /*ofstream fout;
    fout.open("run9.txt",ios::app);
    fout<<step->GetPreStepPoint()-> GetPosition()<<step->GetPreStepPoint()->GetKineticEnergy()<<step->GetPreStepPoint()-> GetMomentum()<<step->GetPreStepPoint()-> GetLocalTime()<<G4endl;
    fout.close();*/
    
  
  //G4cout<<step->GetTrack()->GetParentID()<<endl;
   //G4cout<<step->GetTrack()->GetDefinition()->GetPDGEncoding()<<endl;
  // Fill ntuple
  //G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
  
//if(step->GetTrack()->GetDefinition()->GetPDGEncoding()==-11)
G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
if((volume == "G4_GLASS_PLATE")  &&  (step->GetTrack()->GetDefinition()->GetPDGEncoding()==-11))
{
  int ColId = 0;
  
  {
    
     analysisManager->FillNtupleDColumn(ColId++, eid);
     //analysisManager->FillNtupleDColumn(ColId++, step->GetTrack()->GetDefinition()->GetPDGEncoding());
     //analysisManager->FillNtupleDColumn(ColId++, objName.toLatin1().data());
     //analysisManager->FillNtupleDColumn(ColId++, step->GetTrack()->GetParentID());
     
     analysisManager->FillNtupleDColumn(ColId++, step->GetDeltaTime());
     //analysisManager->FillNtupleDColumn(ColId++, step->GetTrack()->GetGlobalTime());
    // analysisManager->FillNtupleDColumn(ColId++, step->GetTrack()->GetDefinition()->GetPDGEncoding());
  
     //analysisManager->FillNtupleDColumn(ColId++, (step->GetPreStepPoint()->GetPosition().x()));
     //analysisManager->FillNtupleDColumn(ColId++, (step->GetPreStepPoint()->GetPosition().y()));
     //analysisManager->FillNtupleDColumn(ColId++, (step->GetPreStepPoint()->GetPosition().z()));
     
     analysisManager->AddNtupleRow();
     
  
}

   //  const B1DetectorConstruction* detectorConstruction
     // = static_cast<const B1DetectorConstruction*>
    
      //  (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    //fScoringVolume = detectorConstruction->GetScoringVolume();   
  // }

  // get volume of the current step
 // G4LogicalVolume* volume2 
   //  = step->GetPreStepPoint()->GetTouchableHandle()
     //  ->GetVolume()->GetLogicalVolume();
      
  // // check if we are in scoring volume
   //if (volume2 != fScoringVolume) return;

  // // collect energy deposited in this step
 //  G4double edepStep = step->GetTotalEnergyDeposit();
   //fEventAction->AddEdep(edepStep);  
 // G4cout<<"*************Inside stepping action*********"<<G4endl;
  

}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

