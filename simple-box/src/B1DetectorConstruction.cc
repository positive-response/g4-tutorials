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
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"
#include "G4MagneticField.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4VUserDetectorConstruction.hh"


#include "G4VisAttributes.hh"
#include "G4Colour.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  /*
  // Envelope parameters
  //
  //G4double env_sizeXY = 20*cm, env_sizeZ = 30*cm;
  //G4Material* Air = nist->FindOrBuildMaterial("G4_AIR");
  //G4Material* Glass = nist->FindOrBuildMaterial("G4_GLASS_PLATE");
  //G4Material* Iron = nist->FindOrBuildMaterial("G4_Fe");

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeXYZ = 0.75*m;
  
  G4double tracker_xz = 0.55*m;
  G4double tracker_glass_y = 0.05*mm;
  G4double tracker_iron_y = 2.8*cm;

  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* box_mat = nist->FindOrBuildMaterial("G4_Fe");
  G4Material* glass_mat = nist->FindOrBuildMaterial("G4_GLASS_PLATE")

  // World volume  
  G4Box* solidWorld             =  new G4Box("World",world_sizeXYZ, world_sizeXYZ, world_sizeXYZ);     //Solid volume
  G4LogicalVolume* logicWorld   =  new G4LogicalVolume(solidWorld,  world_mat,  "World");            //Logical volume 
  G4VPhysicalVolume* physWorld  =  new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World",  0, false,  0,  checkOverlaps);        // Physical volume


   // Box
  G4Box* solidBox               =  new G4Box("Box",tracker_xz, tracker_iron_y, tracker_xz);     //Solid volume
  G4LogicalVolume* logicBox   =  new G4LogicalVolume(solidBox,  box_mat,  "Box");            //Logical volume, o
  G4VPhysicalVolume* physBox  =  new G4PVPlacement(0, G4ThreeVector(), logicBox, "Box",  logicWorld, false,  0,  checkOverlaps);        // Physical volume

// Glass detector
G4Box* solidBox               =  new G4Box("Glass",tracker_xz, tracker_glass_y, tracker_xz);     //Solid volume
  G4LogicalVolume* logicGlass   =  new G4LogicalVolume(solidBox,  glass_mat,  "Glass");            //Logical volume, o
  G4VPhysicalVolume* physGlass  =  new G4PVPlacement(0, G4ThreeVector(0*cm,8*cm,0*cm), logicGlass, "Glass",  logicWorld, false,  0,  checkOverlaps);        // Physical volume

  return physWorld;
}*/
G4Material* Air = nist->FindOrBuildMaterial("G4_AIR");
G4Material* Glass = nist->FindOrBuildMaterial("G4_GLASS_PLATE");
G4Material* Iron = nist->FindOrBuildMaterial("G4_Fe");
G4bool checkOverlaps = true;
// Create world
// solid volume
G4double world_hx = 1.5*m;
G4double world_hy = 1.5*m;
G4double world_hz = 1.5*m;
G4Box* worldBox = new G4Box("World",world_hx,world_hy,world_hz);
// logical volume
G4LogicalVolume*  worldLog = new G4LogicalVolume(worldBox,Air,"world");
// World physical volume
G4VPhysicalVolume* worldPhys = new G4PVPlacement(0,
                                                 G4ThreeVector(),
                                                  worldLog,
                                                   "World",
                                                   0, 
                                                  false, 
                                                  0,
                                                  checkOverlaps);

 auto visAttributes = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
 visAttributes->SetVisibility(false);
  worldLog->SetVisAttributes(visAttributes);
  //fVisAttributes.push_back(visAttributes);
  
// solid volume of glass detector
G4double tracker2_hx = 0.55*m;
G4double tracker2_hy = 0.05*mm;
G4double tracker2_hz = 0.55*m;
G4Box* GlassBox = new G4Box("Glass",tracker2_hx,tracker2_hy,tracker2_hz);
// logical volume
G4LogicalVolume* GlassLog = new G4LogicalVolume(GlassBox, Glass,"Glass");
G4double pos_x ;
G4double pos_y ;
G4double pos_z ;
//physical volume of  the detector
 pos_x=0.45*m;
 pos_y=5*cm;
 pos_z=0.45*m;
   G4VPhysicalVolume* Glassphy = new G4PVPlacement(0,
                                                    G4ThreeVector(pos_x,pos_y,pos_z),
                                                    GlassLog,
                                                    "Glass",
                                                    worldLog,
                                                    false,
                                                    0,
                                                    checkOverlaps); 

// Iron plate
// solid volume
G4double tracker1_hx = 5*cm;
G4double tracker1_hy = 0.1*mm;
G4double tracker1_hz = 5*cm;

pos_x = 0.0*cm;
pos_y = 0.0*cm;
pos_z = 0.0*cm;

 //physical volume of the geometry

    G4Box* IronBox = new G4Box("Iron",tracker1_hx,tracker1_hy,tracker1_hz); //solid volume of iron cube

int k= 0;
int l = 0;
 
 
 for(int i = 0;i<10;i++)
{
   for(int j =0;j<10;j++)
   {
    IronLog[(i*10)+j]  = new G4LogicalVolume(IronBox, Iron,"Iron"+std::to_string(i)+std::to_string(j));
    
    pos_x = l*cm;
    pos_z = k*cm;

                IronPhy[(i*10)+j] = new G4PVPlacement(0,
                                  G4ThreeVector(pos_x,pos_y,pos_z),
                                  IronLog[(i*10)+j],
                                  "Iron",
                                  worldLog,
                                  false,
                                  0,
                                  checkOverlaps);

   G4cout<<G4endl;
   
   l+=10; 
   
  }
  l=0;
  k+=10;
  G4cout<<G4endl;
  }


   return worldPhys;
   } 
   //G4String current_volume_name  = step->GetPreStepPoint()->GetTouchableHandle() ->GetVolume()->GetLogicalVolume()->GetName();

  void B1DetectorConstruction::ConstructSDandField()
{
  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
int mag =100;

  for(int i=0;i<100;i++)
{
  G4UniformMagField* magField  = new G4UniformMagField(G4ThreeVector(mag*gauss,0.,0.));
   G4FieldManager* fieldMgr = new G4FieldManager(magField);

   fieldMgr->SetDetectorField(magField);
   fieldMgr->CreateChordFinder(magField);

   G4bool allLocal = true ;
  IronLog[i]->SetFieldManager(fieldMgr, allLocal);
  mag+=100;

  // Register the field manager for deleting
 // G4AutoDelete::Register(fieldMgr);
} 
}        

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
