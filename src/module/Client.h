#pragma once
#include<iostream>
#include<vector>
using namespace std;

vector<string> History;
vector<SDL_Rect> destination;
vector<string> cardImage;
int Distance = 0;
int Distance2 = 50;
int Count = 0;

class Client {

private:

    ENetHost* client;
    ENetAddress address;
    ENetPeer* peer;
    ENetEvent event;

public:
        
    unsigned char* getPacketData() {
        return event.packet->data;
    }
  
    void setPort(int portID) {
        address.port = portID;
    }

    void createHost() {
        client = enet_host_create(NULL, 1, 1, 0,0);

    }

    void setHost(string IP) {
        enet_address_set_host(&address,IP.c_str());
    } 

    void setPeer() {
       peer = enet_host_connect(client, &address, 1, 0);       
    }  

    int setHostService(string types, int time) {
        if (types.c_str() == "CONNECT") {
            event.type = ENET_EVENT_TYPE_CONNECT;
        }
        else if (types.c_str() == "RECEIVE") {
            event.type = ENET_EVENT_TYPE_RECEIVE;
        }
        else if (types.c_str() == "DISCONNECT") {
            event.type = ENET_EVENT_TYPE_DISCONNECT;
        }
        return enet_host_service(client, &event, time);
    }

    void sendCardDataToServer(vector<string> cardSendList){
        for (string cardPath : cardSendList) {
            ENetPacket* packet = enet_packet_create(cardPath.c_str(), cardPath.length() + 1, ENET_PACKET_FLAG_RELIABLE);
            enet_peer_send(peer, 0, packet);
        }
    }

};

Client client;

void renderHistoryVer2(vector<string> history) {

    if (history.size() > 0) {
        for (int i = 0; i < history.size();i++) {
            SDL_Texture* temp = loadTexture(history[i]);
            SDL_SetTextureColorMod(temp, 120, 120, 120);
            SDL_RenderCopy(gRenderer, temp, NULL, &destination[i]);
        }
    }
}

void multiplayer(User& player, vector<Computer>& computers, vector<string> &historyTemp) {

    char buffer[1024] = { '\0' }; 
   
    while (client.setHostService("RECEIVE", 50) > 0) {
        if (Count >= 3) {
            history.clear();
            SDL_RenderClear(gRenderer);
            renderHitBtn();
            renderSkipBtn();
            renderAgainBtn();
            SDL_RenderCopy(gRenderer, backgroundTexture, NULL, NULL);
            for (Computer computer : computers) {
                computer.printBackCard();
            }
            historyTemp.clear();
            player.printCards();
            SDL_RenderPresent(gRenderer);
            Distance = 90;
            Count = 0;         
        }
        sprintf_s(buffer, "%s", client.getPacketData());
        cardImage.push_back(buffer);
        SDL_Rect temp = { (SCREEN_WIDTH / 4) + 50 + Distance , 250 ,80,115 };
        destination.push_back(temp);
        Distance += 90;
    }
    for (string& card : cardImage) {
        cout << "Receiving information from server.....VALID CARD, ready to print Card : " << card << " on screen" << endl;
        historyTemp.push_back(card);
        SDL_Texture* temp = loadTexture(card);
        SDL_RenderCopy(gRenderer, temp, NULL, &destination[Count]);
       // renderHistory(history);
        Count++;
        SDL_RenderPresent(gRenderer);
    }
    // xoa bo nho dem 
    cardImage.clear();
    sendCardList.clear();
}



