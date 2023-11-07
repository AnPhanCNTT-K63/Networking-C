#pragma once

void renderHitBtn()
{
    SDL_Rect destinationRect;
    destinationRect = { 800, 440, 150, 65 };
    SDL_RenderCopy(gRenderer, hitBtnTexture, NULL, &destinationRect);
}

void renderSkipBtn()
{
    SDL_Rect destinationRect;
    destinationRect = { 210, 440, 155, 50 };
    SDL_RenderCopy(gRenderer, skipBtnTexture, NULL, &destinationRect);
}
void renderAgainBtn()
{
    SDL_Rect destinationRect;
    destinationRect = { 470, 300, 155, 50 };
    SDL_RenderCopy(gRenderer, againBtnTexture, NULL, &destinationRect);
}

// history area
void renderHistory(vector<vector<Card>> history)
{
    int padding = 50;
    int len = history.size();
    for (int i = 0; i < len; i++)
    {
        //  padding += 50;
        for (Card card : history[i])
        {
            card.setWidth(80);
            card.setHeight(116);

            if (i != len - 1)
                card.blackColor();
            else
                card.normalColor();

            card.setX((SCREEN_WIDTH / 4) + padding);
            card.setY(250);

            // SDL_RenderCopy(gRenderer, card.getTexture(), NULL, card.getDestinationRect());

            padding += 90;

        }

    }
}

void renderPassWin(SDL_Texture* winTexture)
{
    SDL_Delay(1000);
    SDL_Rect destinationRect;
    destinationRect = { SCREEN_WIDTH / 2 - 280, SCREEN_HEIGHT / 2 - 280, 250, 250 };
    SDL_RenderCopy(gRenderer, winTexture, NULL, &destinationRect);
}



void renderAnimationHit(vector<vector<Card>> history, User& player, vector<Computer>& computers) {
    int frame = 20;  // 30
    int tempX = 0;
    int padding = 0;
    for (int i = 0; i < history.size(); i++) {
        padding += 50;
        tempX = (SCREEN_WIDTH / 4) + padding;
        for (Card card : history[i]) {
            if (i >= history.size() - 1) {
                for (int k = 1;k <= frame;k++) {
                    card.setWidth(card.getWidth() - 2); //  4
                    card.setHeight(card.getHeight() - 3); // 6
                    card.setX(card.getX() + ((tempX - card.getX()) / 2));
                    card.setY(card.getY() - 14); // 31 
                    SDL_RenderCopy(gRenderer, card.getTexture(), NULL, card.getDestinationRect());
                    SDL_RenderPresent(gRenderer);
                    SDL_Delay(10);
                    SDL_RenderClear(gRenderer);
                    renderHitBtn();
                    renderSkipBtn();
                    renderAgainBtn();
                    SDL_RenderCopy(gRenderer, backgroundTexture, NULL, NULL);
                    for (Computer computer : computers) {
                        computer.printBackCard();
                    }
                    player.printCards();
                }
            }
            padding += 40;
        }
    }
}