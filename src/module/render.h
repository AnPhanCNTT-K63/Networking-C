#pragma once

void renderHitBtn()
{
    SDL_Rect destinationRect;
    destinationRect = {800, 440, 150, 65};
    SDL_RenderCopy(gRenderer, hitBtnTexture, NULL, &destinationRect);
}

void renderSkipBtn()
{
    SDL_Rect destinationRect;
    destinationRect = {210, 440, 155, 50};
    SDL_RenderCopy(gRenderer, skipBtnTexture, NULL, &destinationRect);
}
void renderAgainBtn()
{
    SDL_Rect destinationRect;
    destinationRect = {470, 300, 155, 50};
    SDL_RenderCopy(gRenderer, againBtnTexture, NULL, &destinationRect);
}

// history area
void renderHistory(vector<vector<Card>> history)
{
    int padding = 0;
    int len = history.size();
    for (int i = 0; i < len; i++)
    {
        padding += 50;
        for (Card card : history[i])
        {
            card.setWidth(80);
            card.setHeight(115);

            if (i != len - 1)
                card.blackColor();
            else
                card.normalColor();

            card.setX((SCREEN_WIDTH / 4) + padding);
            card.setY(250);

            SDL_RenderCopy(gRenderer, card.getTexture(), NULL, card.getDestinationRect());

            padding += 40;
        }
    }
}

void renderPassWin(SDL_Texture *winTexture)
{
    SDL_Delay(1000);
    SDL_Rect destinationRect;
    destinationRect = {SCREEN_WIDTH / 2 - 280, SCREEN_HEIGHT / 2 - 280, 250, 250};
    SDL_RenderCopy(gRenderer, winTexture, NULL, &destinationRect);
}

//void renderAnimationHit(vector<vector<Card>> history, User& player, vector<Computer>& computers) {
//    int frame = 20;  // 30
//    int tempX = 0;
//    int padding = 0;
//    for (int i = 0; i < history.size(); i++) {
//        padding += 50;
//        tempX = (SCREEN_WIDTH / 4) + padding;
//        for (Card card : history[i]) {
//            if (i >= history.size() - 1) {
//                for (int k = 1;k <= frame;k++) {
//                    card.setWidth(card.getWidth() - 2); //  4
//                    card.setHeight(card.getHeight() - 3); // 6
//                    card.setX(card.getX() + ((tempX - card.getX()) / 2));
//                    card.setY(card.getY() - 14); // 31 
//                    SDL_RenderCopy(gRenderer, card.getTexture(), NULL, card.getDestinationRect());
//                    if (history[i].size() >= 2) {
//                        for (int j = 2;j < history[i].size();j++) {
//                            SDL_RenderCopy(gRenderer, history[i][j].getTexture(), NULL, history[i][j].getDestinationRect());
//                        }
//                    }
//                   SDL_RenderPresent(gRenderer);
//                    SDL_Delay(150);
//                    //SDL_RenderClear(gRenderer);
//                    SDL_RenderCopy(gRenderer, backgroundTexture, NULL, NULL);
//                    for (Computer computer : computers) {
//                        computer.printBackCard();
//                    }
//                    player.printCards();
//                }
//            }
//            padding += 40;
//        }
//
//    }
//}

void renderAnimationHit(vector<vector<Card>> history, User& player, vector<Computer>& computers) {
    int frame = 20;
    int padding = 0;
    vector<int> tempX(history.size());

    for (int i = 0; i < history.size(); i++) {
        padding += 50;
        tempX[i] = (SCREEN_WIDTH / 4) + padding;
    }

    for (int k = 1; k <= frame; k++) {
        for (int i = 0; i < history.size(); i++) {
            if (i >= history.size() - 1) {
                for (Card& card : history[i]) {
                    card.setWidth(card.getWidth() - 2);
                    card.setHeight(card.getHeight() - 3);
                    card.setX(card.getX() + ((tempX[i] - card.getX()) / 2));
                    card.setY(card.getY() - 14);                                                         
                        for (Card& card : history[i]) {
                            SDL_RenderCopy(gRenderer, card.getTexture(), NULL, card.getDestinationRect());             
                        }                       
                    
                   
                    SDL_RenderPresent(gRenderer); 
                    SDL_RenderCopy(gRenderer, backgroundTexture, NULL, NULL);
                    for (Computer& computer : computers) {
                        computer.printBackCard();                     
                    }
                    player.printCards();
                    card.setX(card.getX() + 40);
                }
            }
            
        }       
        SDL_Delay(10);       
    }
}

//void renderAnimationHitComputer(vector<vector<Card>> history, User& player, vector<Computer>& computers, int& id) {
//    int frame = 20;
//    int tempX = 0;
//    int padding = 0;
//    int x = 0;
//    int y = 0;
//
//    if (id == 0) {
//        x = 50;
//        y = SCREEN_HEIGHT / 2 - 145;
//    }
//    else if (id == 1) {
//        x = SCREEN_WIDTH / 2 - 100;
//        y = 5;
//    }
//    else {
//        x = SCREEN_WIDTH - 200;
//        y = SCREEN_HEIGHT / 2 - 145;
//    }
//
//    for (int i = 0; i < history.size(); i++) {
//        padding += 50;
//        tempX = (SCREEN_WIDTH / 4) + padding;
//        for (Card card : history[i]) {
//            card.setX(x);
//            card.setY(y);
//            if (i >= history.size() - 1) {
//                for (int k = 1;k <= frame;k++) {
//                    card.setWidth(80);
//                    card.setHeight(115);
//                    if (id == 0) {
//                        card.setX(card.getX() + ((tempX - card.getX()) / 2));
//                        card.setY(card.getY() + 2);
//                    }
//                    else if (id == 1) {
//                        card.setX(card.getX() - ((card.getX() - tempX) / 20));
//                        card.setY(card.getY() + 12);
//                    }
//                    else {
//                        card.setX(card.getX() - ((card.getX() - tempX) / 20));
//                        card.setY(card.getY() + 2);
//                    }
//                    SDL_RenderCopy(gRenderer, card.getTexture(), NULL, card.getDestinationRect());
//                    SDL_RenderPresent(gRenderer);
//                    SDL_Delay(10);
//                    SDL_RenderClear(gRenderer);
//                    renderHitBtn();
//                    renderSkipBtn();
//                    renderAgainBtn();
//                    SDL_RenderCopy(gRenderer, backgroundTexture, NULL, NULL);
//                    for (Computer computer : computers) {
//                        computer.printBackCard();
//                    }
//                    player.printCards();
//                }
//            }
//            padding += 40;
//        }
//    }
//}

void renderAnimationHitComputer(vector<vector<Card>> history, User& player, vector<Computer>& computers, int& id) {
    int frame = 20;
    vector<int> tempX(history.size());
    int padding = 0;
    int x = 0;
    int y = 0;

    if (id == 0) {
        x = 50;
        y = SCREEN_HEIGHT / 2 - 145;
    }
    else if (id == 1) {
        x = SCREEN_WIDTH / 2 - 100;
        y = 5;
    }
    else {
        x = SCREEN_WIDTH - 200;
        y = SCREEN_HEIGHT / 2 - 145;
    }
  
    for (int i = 0; i < history.size(); i++) {
        padding += 50;
        tempX[i] = (SCREEN_WIDTH / 4) + padding;
    }
  
    for (int k = 1; k <= frame; k++) {   
        for (int i = 0; i < history.size(); i++) {
            if (i >= history.size() - 1) {
                for (Card& card : history[i]) {
                    if (k == 1) {
                        card.setX(x);
                        card.setY(y);
                    }
                    card.setHeight(115);
                    card.setWidth(80);                  

                     if (id == 0) {
                        card.setX(card.getX() + ((tempX[i] - card.getX()) / 2));
                        card.setY(card.getY() + 2);
                        
                    }
                     else if (id == 1) {
                       card.setX(card.getX() - ((card.getX() - tempX[i]) / 2));
                       card.setY(card.getY() + 12);
                       
                    }
                    else {
                        card.setX(card.getX() - ((card.getX() - tempX[i]) / 2));
                        card.setY(card.getY() + 2);
                    }

                    for (Card& card : history[i]) {
                        SDL_RenderCopy(gRenderer, card.getTexture(), NULL, card.getDestinationRect());
                    }

                    SDL_RenderPresent(gRenderer);
                    SDL_RenderCopy(gRenderer, backgroundTexture, NULL, NULL);
                    for (Computer& computer : computers) {
                        computer.printBackCard();
                    }
                    player.printCards();
                    card.setX(card.getX() + 40);
                }
            }

        }
        SDL_Delay(10);
    }

}