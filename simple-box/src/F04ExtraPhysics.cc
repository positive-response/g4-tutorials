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
//

#include "globals.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4ProcessManager.hh"

#include "G4UserSpecialCuts.hh"
#include "G4StepLimiter.hh"

#include "F04ExtraPhysics.hh"

F04ExtraPhysics::F04ExtraPhysics() 
//    : G4VUserPhysicsList() { }
    : G4VPhysicsConstructor("Extra") { }

F04ExtraPhysics::~F04ExtraPhysics() { }

void F04ExtraPhysics::ConstructParticle() { }

void F04ExtraPhysics::ConstructProcess()
{
    G4cout << "F04ExtraPhysics:: Add Extra Physics Processes" 
              << G4endl;

    auto theParticleIterator = GetParticleIterator();
    theParticleIterator->reset();

    while ( (*theParticleIterator)() ) {
      G4ParticleDefinition* particle = theParticleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        G4String particleName = particle->GetParticleName();
        G4double charge = particle->GetPDGCharge();

        if (!pmanager) {
            std::ostringstream o;
            o << "Particle " << particleName << "without a Process Manager";
            G4Exception("F04ExtraPhysics::ConstructProcess()","",
                         FatalException,o.str().c_str());
        }

        if (charge != 0.0) {
           // All charged particles should have a step limiter
           // to make sure that the steps do not get too long.
           pmanager->AddDiscreteProcess(new G4StepLimiter());
           pmanager->AddDiscreteProcess(new G4UserSpecialCuts());
        } else if (particleName == "neutron") {
          // time cuts for ONLY neutrons:
          pmanager->AddDiscreteProcess(new G4UserSpecialCuts());
        } else {
          // Energy cuts for all other neutral particles
          pmanager->AddDiscreteProcess(new G4UserSpecialCuts());
        }
    }
}