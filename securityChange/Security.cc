#include "veins/modules/mac/ieee80211p/Mac1609_4.h"
#include <iterator>
#include "veins/modules/phy/DeciderResult80211.h"
#include "veins/base/phyLayer/PhyToMacControlInfo.h"
#include "veins/modules/messages/PhyControlMessage_m.h"
#include "veins/modules/messages/AckTimeOutMessage_m.h"



using namespace veins;


#include <omnetpp.h>
using namespace omnetpp;


class Security : public cSimpleModule
{

    private:
        cMessage *event;        //messaggio utile per ritardare invio messaggio
        cMessage *tictocMsg;   //variabile utile per memorizzare messaggio in attesa che trascorra il tempo di simulazione

    protected:
       // The following redefined virtual function holds the algorithm.
       virtual void initialize() override;
       virtual void handleMessage(cMessage *msg) override;
   };

   Define_Module(Security);

   void Security::initialize(){

       event = new cMessage("event");

       tictocMsg = nullptr;
   }



   void Security::handleMessage(cMessage *msg)
   {

       if(msg == event){
           send(tictocMsg, "lowerLayerOut"); // send out the message
           tictocMsg = nullptr;
       }
       else{
           tictocMsg = msg;
           scheduleAt(simTime()+0.01,event);
       }

   }
